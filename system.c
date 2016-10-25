#include "header.h"
#include "system/strings.h"


void delay() {
	//TODO
}



void system_parsecommand(char data[]) {
	if (api_comparecommand(creturn, data)) {
		terminal_putchar('\n');
		return;
	}

	if (api_comparecommand(cmagic, data)) {
		terminal_writestring("It's a magic!\n\nYeah!\n");
		return;
	}

	if (api_comparecommand(cclear, data)) {
		terminal_initialize();
		return;
	}

	terminal_writestring("unknown command ");
	terminal_writestring(data);
	terminal_writestring(" \n");
}
