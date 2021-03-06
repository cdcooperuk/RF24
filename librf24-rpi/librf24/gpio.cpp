/* 
 * https://github.com/mrshu/GPIOlib
 *
 * see https://www.kernel.org/doc/Documentation/gpio.txt
 *
 * Copyright (c) 2011, Copyright (c) 2011 mr.Shu
 * All rights reserved. 
 * 
 * Modified on 24 June 2012, 11:06 AM
 * File:   gpio.cpp
 * Author: purinda (purinda@gmail.com)
 * 
 *
 */

#include "gpio.h"
#include "errno.h"
#include <stdlib.h>

GPIO::GPIO() {
}

GPIO::~GPIO() {
}

/*
 * export pin and set its direction.
 */
void GPIO::open(int port, int DDR)
{
	// write the pin number to gpio
	FILE *f;
	f = fopen("/sys/class/gpio/export", "w");
	if (f == NULL) {
		perror("open gpio failed");
		exit(1);
	}
	fprintf(f, "%d\n", port);
	fclose(f);

	char file[128];
	sprintf(file, "/sys/class/gpio/gpio%d/direction", port);
	f = fopen(file, "w");
	if (DDR == DIRECTION_IN)	fprintf(f, "in\n");
	else		fprintf(f, "out\n");
	fclose(f);
}

/**
 * unexport the pin.
 */
void GPIO::close(int port)
{
	FILE *f;
	f = fopen("/sys/class/gpio/unexport", "w");
	fprintf(f, "%d\n", port);
	fclose(f);
}

/**
 *
 * TODO is it efficient to constantly open/close?
 */
int GPIO::read(int port)
{
	FILE *f;
	
	char file[128];
	sprintf(file, "/sys/class/gpio/gpio%d/value", port);
	f = fopen(file, "r");

	int i;
	fscanf(f, "%d", &i);
	fclose(f);
	return i;

}
void GPIO::write(int port, int value){
	FILE *f;

	char file[128];
	sprintf(file, "/sys/class/gpio/gpio%d/value", port);
	f = fopen(file, "w");
	
	if (value == 0)	fprintf(f, "0\n");
	else		fprintf(f, "1\n");
	
	fclose(f);
}
