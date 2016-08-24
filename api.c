#include "header.h"

uint8_t api_length_array(const char arr[]){
	uint8_t i = 0;

	char *myIntPtr = &arr[0];
	while( *myIntPtr != '^' )
	{
		i++;
    	myIntPtr++;
	}


	return (i);
}

char *api_inttostring(unsigned int value, int leading){
	/* Biggest number is 4294967295 (10 digits) */
	static char buffer[11];
	static char leadchar;

	unsigned int offset = 10;
	unsigned char ch;

	if(leading <0)
	{
		leading = -leading;
		leadchar = ' ';
	}
	else
	{
		leadchar = '0';
	}

	if(leading>10)
		return "error";

	buffer[offset] = 0;

	while(value || (offset == 10))
	{
		offset--;
		leading--;
		ch = 48 + (value % 10);
		buffer[offset] = ch;

		value = value/10;
	}

	while(leading>0)
	{
		offset--;
		leading--;
		buffer[offset] = leadchar;
	}

	return &buffer[offset];
}

bool api_comparecommand(const char mask[], char data[]) {
	int i = 0;

	for (; i<api_length_array(mask); i++){
		if (data[i]!=mask[i]) return false;
	}

	return true;
}




