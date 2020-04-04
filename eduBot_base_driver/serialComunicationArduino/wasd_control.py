import math as m
import time
import sys, tty, termios, time
import os
#import serial
import serial, time

arduino = serial.Serial("/dev/ttyACM1", 250000)
time.sleep(1)

def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

while True:
    char = getch()
    if(char == "w"):
        print("forward()")
        arduino.write(b'1')
    if(char == " "):
        print("stop()")
        arduino.write(b'9')
    if(char == "s"):
        print("reverse()")
        arduino.write(b'4')
    if(char == "a"):
        print("left()")
        arduino.write(b'7')
    if(char == "d"):
        print("right()")
        arduino.write(b'6')
    if(char == "e"):
        print("quit()")
        quit()
