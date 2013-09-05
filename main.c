/********************************************************************
* libarduino example
********************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "libarduino.h"

#define RELAY_1		8
#define RELAY_2		9
#define RELAY_3		10
#define RELAY_4		11

void init_relays(void)
{
	pinMode(RELAY_1, OUTPUT);
	pinMode(RELAY_2, OUTPUT);
	pinMode(RELAY_3, OUTPUT);
	pinMode(RELAY_4, OUTPUT);
	
	// relay command is active low
	digitalWrite(RELAY_1, HIGH);
	digitalWrite(RELAY_2, HIGH);
	digitalWrite(RELAY_3, HIGH);
	digitalWrite(RELAY_4, HIGH);
}

void wait_command()
{
	char cmd[16];
	char target[16];
	char address[8];
	char value[8];
	
	scanf("%s", cmd);
	if (strcmp(cmd, "set") == 0) {
		scanf("%s", target);
		if (strcmp(target, "relay") == 0) {
			scanf("%s", address);
			if (strcmp(address, "1") == 0) {
				scanf("%s", value);
				if (strcmp(value, "on") == 0) {
					digitalWrite(RELAY_1, LOW);
				}
				else if (strcmp(value, "off") == 0) {
					digitalWrite(RELAY_1, HIGH);
				}
				else goto error;
			}
			else if (strcmp(address, "2") == 0) {
				scanf("%s", value);
				if (strcmp(value, "on") == 0) {
					digitalWrite(RELAY_2, LOW);
				}
				else if (strcmp(value, "off") == 0) {
					digitalWrite(RELAY_2, HIGH);
				}
				else goto error;
			}
			else if (strcmp(address, "3") == 0) {
				scanf("%s", value);
				if (strcmp(value, "on") == 0) {
					digitalWrite(RELAY_3, LOW);
				}
				else if (strcmp(value, "off") == 0) {
					digitalWrite(RELAY_3, HIGH);
				}
				else goto error;
			}
			else if (strcmp(address, "4") == 0) {
				scanf("%s", value);
				if (strcmp(value, "on") == 0) {
					digitalWrite(RELAY_4, LOW);
				}
				else if (strcmp(value, "off") == 0) {
					digitalWrite(RELAY_4, HIGH);
				}
				else goto error;
			}
			else goto error;
		}
		else goto error;
	}
	else {
error:
		printf("error\r\n");
		return;
	}
ok:
	printf("ok\r\n");
}

int main (void)
{
	serial_init();
	fdevopen(serial_putchar, serial_getchar);
	
	init_relays();
	
	sei(); /* enable interrupts */

	while (1)
	{
		printf("\r\n");
		wait_command();
	}

	return 1;
}
