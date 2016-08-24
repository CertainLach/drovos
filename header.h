#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>

enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};




bool api_comparecommand(const char mask[], char data[]);

void delay();
void terminal_writestring(const char* data);
void system_parsecommand(char data[]);
void terminal_putchar(char c);
void terminal_initialize();

char *api_inttostring(unsigned int value, int leading);


// defines to memory management
//#define ARR_LEN(a) (sizeof(a) / sizeof(a[0]))
#define UNUSED(x) (void)(x)

void init_heap(uint32_t start, uint32_t end);
void* kmalloc(uint32_t nbytes);
void kfree(void *ptr);

uint8_t api_length_array(const char array[]);
