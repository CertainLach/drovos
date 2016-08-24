#include "header.h"
#include "system/strings.h"


void delay() {
	uint32_t hax = 1, cracks = 1, fix = 1, vitalya = 1, ebu_dal = 1;

	for (; ebu_dal<60000; ebu_dal++)
	for (; vitalya<30000; vitalya++)
	for (; fix<65000; fix++)
	for (; hax<65000; hax++)
	for (; cracks<65000; cracks++)
	{
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
		terminal_writestring("");
	}
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

