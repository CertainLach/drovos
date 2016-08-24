
#include "header.h"
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

//char* buffer = ""; 
/* Hardware text mode color constants. */

 
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

void update_cursor(); 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

 
void terminal_putchar(char c) {
	if (c=='\n'){
		terminal_column=0;
		if (++terminal_row == VGA_HEIGHT) {
                        terminal_row = 0;
                }
		update_cursor(terminal_row, terminal_column+1);

		return;
	}
	if(c!='^'){
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
			}
		}
	}
	update_cursor(terminal_row, terminal_column+1);
}

void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);
}



#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

char getScancode(){
	char c=0;
	do {
		if(inb(0x60)!=c)
		{
			c=inb(0x60);
			if(c>0)
				return c;
		}
	}while(1);
}
uint8_t getchar(){
	return getScancode();
}


char buffer[128]="";
uint8_t point = 0;


void terminal_wait() {
	char lowercase[]="##1234567890-*##qwertyuiop[]\n#asdfghjkl;'###zxcvbnm,./";
	uint8_t n = getchar();
	char c = lowercase[n];
	terminal_putchar(c);
	if (c=='\n'){
		system_parsecommand(buffer);
		uint8_t tmp;
		for (tmp = 0; tmp < 127; tmp++)
			buffer[tmp] = '^';
		point = 0;
	} else {
		buffer[point++] = c;
	}

 	
	delay();
	
	terminal_wait();

}

void kernel_main() {
	/* Initialize terminal interface */
	terminal_initialize();
 
	terminal_writestring("Hello, kernel World!\n");
	
	terminal_wait();
}
 void update_cursor(int row, int col) {
 	unsigned short position=(row*80) + col-1;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position&0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}
