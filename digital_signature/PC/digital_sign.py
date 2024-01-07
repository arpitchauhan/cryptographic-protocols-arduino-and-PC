"""
Copyright (C) 2013 Arpit Chauhan, Inderjit Sidhu and Archit Pandey

This file is part of cryptographic-protocols-arduino-and-PC source code.

cryptographic-protocols-arduino-and-PC is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

cryptographic-protocols-arduino-and-PC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the software.  If not, see <http://www.gnu.org/licenses/>.
"""

import serial
from time import sleep
from cycles_md5 import *

COMPORT = 6

def synchronize(str, arduino):
    while arduino.readline() != str:
        pass

def main():
	arduino = serial.Serial(COMPORT, 115200)
	arduino.timeout = 1.5

	print "1. Digitally sign a message and send it to Arduino from PC."
	print "2. Digitally sign a message and sent it to PC from Arduino."

	choice = raw_input("\n Enter your choice: ")

	while choice not in ['1','2']:
		choice = raw_input("Wrong choice. Enter again: ")
	if choice =='1':
		pc_msg = "Sheryl Sandberg is the author of Lean In"
		synchronize("Ready\n", arduino)
		arduino.write("PC_TO_ARDUINO")
		cycle_pc_to_arduino(pc_msg, arduino)
	elif choice == '2':
		synchronize("Ready\n", arduino)
		arduino.write("ARDUINO_TO_PC")
		cycle_arduino_to_pc(arduino)

	arduino.close()

main()
