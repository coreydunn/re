#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<termios.h>

#define clear() send_serial_single("[2J")
#define move(y,x) send_serial_double(y,x,"H")
#define restore_curs() send_serial_single("8")
#define restore_screen() send_serial_single("[?47l")
#define save_curs() send_serial_single("7")
#define save_screen() send_serial_single("[?47h")

// No bracket
void send_serial_single(char*s);
// Uses bracket
void send_serial_double(uint32_t y,uint32_t x,char*s);
// Toggle canon/raw mode
void canon(int b);
// Toggle echo
void echo(int b);
