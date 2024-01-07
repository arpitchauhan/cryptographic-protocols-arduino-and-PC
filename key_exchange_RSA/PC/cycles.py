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

from util import *
from Crypto.Cipher import AES
from time import sleep

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
    #AES_Key = [234, 225, 2, 127, 90, 164, 181, 96, 150, 105, 99, 180, 55, 218, 185, 11]
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
