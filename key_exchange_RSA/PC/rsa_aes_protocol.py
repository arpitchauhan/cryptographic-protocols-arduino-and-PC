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

#from Crypto import Random
import RSA
from Crypto.Cipher import AES
from random import randint
from util import *
#from cycles import *
import serial
from time import sleep

RSA_Others_Public_Key = [5723, 5]
MOST_NO_OF_DIGITS_IN_LENGTH = 10
COMPORT = 6

def choose_COM_port():
    global COMPORT
    print "Enter the COM port name. It could be an integer for COM%d, or a path like '/dev/ttyACM0'"
    COM_input = raw_input("COM port name (default is '%s'): " %COMPORT)
    if COM_input.isdigit():
        COMPORT = int(COM_input)
    elif COM_input:
        COMPORT = COM_input
    return

def cycle_arduino_to_PC(AES_key_exchange_function, arduino, caller="DiffieHellman"):
    #receiving ciphertext
    ctext = []

    AES_Key = AES_key_exchange_function(arduino)
    if caller == "RSA":
        arduino.readline()

    length = int(arduino.readline())
    AES_Key_string = ascii_int_list2string(AES_Key)

    pycrypto_AES = AES.new(AES_Key_string, AES.MODE_ECB)

    ptext_actual = zeropadding("Drones are hovering over your head", 16)[0]

    print "length = ", length

    for i in range(length):
        x = int(arduino.readline())
        ctext.append(x)

    ctext_string = ascii_int_list2string(ctext)

    ptext_string = pycrypto_AES.decrypt(ctext_string)

    print "ciphertext (string) = ", ctext_string
    print "ciphertext (ASCII values) = ", ctext
    print "plaintext (string) = ", ptext_string
    print "plaintext (ASCII values) = ", string2ascii_int_list(ptext_string)

def cycle_PC_to_arduino(AES_Key, plaintext, arduino, caller = "DiffieHellman"):

    ptext_string = plaintext
    ptext_string = zeropadding(ptext_string, 16)[0]
    AES_Key_string = ascii_int_list2string(AES_Key)
    pycrypto_AES = AES.new(AES_Key_string, AES.MODE_ECB)
    ctext_string = pycrypto_AES.encrypt(ptext_string)
    ctext = string2ascii_int_list(ctext_string)

    if 0 in ctext:
        return 0
    else:
        arduino.write("2&g&xb3leL")

    print "AES Key = ", AES_Key
    print "Actual length = ", len(ctext)
    arduino.write(append_zeros_at_front(len(ctext), MOST_NO_OF_DIGITS))

    print "Ciphertext (int list) = ", ctext
    print "Ciphertext = ", ctext_string

    for i in range(len(ctext)):
        sleep(0.002)
        arduino.write(append_zeros_at_front(ctext[i], 3))
        if caller == "RSA":
            arduino.readline()
    return 1

def cycle_PC_to_arduino_executer(plaintext, AES_key_exchange_function, arduino, caller="DiffieHellman"):
    flag = 0
    while flag == 0:
        AES_key = AES_key_exchange_function(arduino)

        flag = cycle_PC_to_arduino(AES_key, plaintext, arduino, caller)

        if flag == 0:
            arduino.write("K2qkR^ICGU")



#
def generate_PR_key(length = 16):
    key = []
    for i in range(length):
        key.append(randint(1,255)); #randint(a,b) gives a <= N <= b
    return key

def synchronize(str, arduino):
    while arduino.readline() != str:
        pass

AES_KEY_LENGTH = 16
BIGGEST_CIPHERTEXT_LENGTH = 10
def generate_AES_Key_and_exchange(arduino):

    AES_Key = generate_PR_key()
    print "Generated Random AES Key = ", AES_Key
    AES_Key_string = ascii_int_list2string(AES_Key)
    AES_Key_encrypted = RSA.rsa_encrypt(AES_Key_string, RSA_Others_Public_Key)
    print "Encrypted AES Key (with RSA) = ", AES_Key_encrypted

    for i in range(AES_KEY_LENGTH):
        arduino.write(append_zeros_at_front(AES_Key_encrypted[i], BIGGEST_CIPHERTEXT_LENGTH))
    return AES_Key

def main():
    choose_COM_port()
    arduino = serial.Serial(COMPORT, 115200)
    arduino.timeout = 1.5

    print "1. Send Encrypted Text from PC to Arduino"
    print "2. Send Encrypted Text from Arduino to PC"

    choice = raw_input("\nEnter your choice: ")

    while choice not in ['1','2']:
        choice = raw_input("Wrong choice. Enter again: ")
    print "Executing ", choice
    if choice == '1':

        plaintext="I don't know how it gets better than this"
        synchronize("TkSOzZU9Wd*!byau$U2a\n", arduino)
        arduino.write("PC_TO_ARDUINO")
        cycle_PC_to_arduino_executer(plaintext, generate_AES_Key_and_exchange, arduino, "RSA")
    elif choice == '2':
        synchronize("TkSOzZU9Wd*!byau$U2a\n", arduino)
        arduino.write("ARDUINO_TO_PC")
        cycle_arduino_to_PC(generate_AES_Key_and_exchange, arduino, "RSA")

main()
