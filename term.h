#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<termios.h>

#define clear() send_serial_single("[2J")
#define clearline() send_serial_single("[K")
#define move(y,x) send_serial_double(y,x,"H")
#define reset() send_serial_single("[0m")
#define restore_curs() send_serial_single("8")
#define restore_screen() send_serial_single("[?47l")
#define rev() send_serial_single("[7m")
#define save_curs() send_serial_single("7")
#define save_screen() send_serial_single("[?47h")
#define set_curs(x) send_serial_single(x?"[?25h":"[?25l")

// No bracket
void send_serial_single(char*s);
// Uses bracket
void send_serial_double(uint32_t y,uint32_t x,char*s);
// Toggle canon/raw mode
void canon(int b);
// Toggle echo
void echo(int b);
