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

import RSA
from Crypto.Hash import MD5
from util_MD5 import *

RSA_Others_Public_Key = [5723, 5]
RSA_Own_Private_Key = [6887, 611]
MOST_NO_OF_DIGITS = 10

def cycle_arduino_to_pc(arduino):

    arduino_encryted_hash = []
    arduino.readline()
    arduino.readline()

    for i in range(16):
        arduino_encryted_hash.append(int(arduino.readline()))

    print "arduino_encryted_hash = ", arduino_encryted_hash
    arduino_msg_length = int(arduino.readline())

    arduino_msg = ''
    for i in range(arduino_msg_length):
        arduino_msg += arduino.readline()[0]

    print "msg =" , arduino_msg

    msg_hash_by_pc = MD5.new(arduino_msg)
    msg_hash_by_pc_string = msg_hash_by_pc.digest()
    print "msg_hash_by_pc_string = ", msg_hash_by_pc_string

    msg_hash_by_pc_int_list = []

    for i in range(len(msg_hash_by_pc_string)):
        msg_hash_by_pc_int_list.append(ord(msg_hash_by_pc_string[i]))

    print  "msg_hash_by_pc_int_list = ", msg_hash_by_pc_int_list


    plain_hash = RSA.rsa_decrypt(arduino_encryted_hash, RSA_Others_Public_Key);

    hash_int_list = []

    for val in plain_hash:
        hash_int_list.append(ord(val))

    print "hash_int_list = ", hash_int_list

    if hash_int_list == msg_hash_by_pc_int_list :
        print "Hash and Message match!"
    else:
        print "Hash and Message do not match!"

def cycle_pc_to_arduino(pc_msg, arduino):
    send_pc_msg_to_arduino(pc_msg, arduino)

    pc_hash = MD5.new(pc_msg)
    pc_hash_string = pc_hash.digest()

    #send_pc_msg_to_arduino(pc_msg)
    print  "pc_hash_string =", pc_hash_string
    pc_hash_int_list = []
    for i in range(len(pc_hash_string)):
        pc_hash_int_list.append(ord(pc_hash_string[i]))             # Packing pc_msg hash as int list for sending to arduino

    print "pc_hash_int_list = ", pc_hash_int_list
    length =  len(pc_hash_int_list)

    encrypted_pc_hash = RSA.rsa_encrypt(pc_hash_string, RSA_Own_Private_Key)    # Encrypting the hash by RSA
    print "encrypted_pc_hash = " ,encrypted_pc_hash
    # Send encrypted hash to Arduino
    for i in range(16):                                                         # Sending the Encrypted Hash
        arduino.write(append_zeros_at_front(encrypted_pc_hash[i], MOST_NO_OF_DIGITS))
        recieved_by_arduino =  arduino.readline()
