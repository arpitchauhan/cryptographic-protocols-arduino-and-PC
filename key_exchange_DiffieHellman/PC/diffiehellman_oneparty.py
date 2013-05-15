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

from random import randint
import serial
from cycles import *
from util import *
from time import sleep

COMPORT = 6
a = 6
q = 761
MOST_NO_OF_DIGITS = 10

def Diffie_Hellman_num_exchange(arduino):
    X = randint(2, q-1)
    Y = (a ** X) % q
    arduino.write(append_zeros_at_front(str(Y), MOST_NO_OF_DIGITS))
    
    Y_other = int(arduino.readline())
    
    K = (Y_other ** X ) % q
    Diffie_Hellman_num = K % 256    
    return Diffie_Hellman_num

def Diffie_Hellman_AES_Key_exchange(arduino):
    AES_key = []
    for i in range(16):
        AES_key.append(Diffie_Hellman_num_exchange(arduino))
    return AES_key
    

def main():
    arduino = serial.Serial(COMPORT, 115200)
    arduino.timeout = 1.5
    
    print "1. Send Encrypted Text from PC to Arduino"
    print "2. Send Encrypted Text from Arduino to PC"
    print "3. Benchmark AES"
    
    choice = raw_input("\nEnter your choice: ")
    
    while choice not in ['1','2','3']:
        choice = raw_input("Wrong choice. Enter again: ")
    if choice == '1':
        plaintext = "Guido van Rossum created the language Python"
        synchronize("TkSOzZU9Wd*!byau$U2a\n", arduino)
        
        arduino.write("PC_TO_ARDUINO")
        cycle_PC_to_arduino_executer(plaintext, Diffie_Hellman_AES_Key_exchange , arduino)
    elif choice == '2':
        synchronize("TkSOzZU9Wd*!byau$U2a\n", arduino)
        arduino.write("ARDUINO_TO_PC")
        
        cycle_arduino_to_PC(Diffie_Hellman_AES_Key_exchange, arduino)
    elif choice=='3':
        synchronize("TkSOzZU9Wd*!byau$U2a\n", arduino)
        arduino.write("BENCHMARK_AES")

main()


