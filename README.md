# lcd_hello_world
A simple program to test the linksprite LCD arduino shield.

User key presses are detected and a string written to the LCD.
A timer interrupt (from the [TimerOne][1] library) is used to refresh the LCD display.
This results in a responsive program with a reasonable LCD refresh rate.

[1]: http://playground.arduino.cc/Code/Timer1
