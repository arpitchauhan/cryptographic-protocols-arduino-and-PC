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

MOST_NO_OF_DIGITS = 10

def zeropadding(string, block):
    length = len(string)
    no_of_blocks = length/block + 1
    length_last_block = length % block
    if length_last_block == 0:
        return [string, length]
    string = string + (no_of_blocks * block - length_last_block) * "\0"
    return [string, no_of_blocks * block]

def string2ascii_int_list(string):
    ascii_int_list=[]
    for char in string:
        ascii_int_list.append(ord(char))
    return ascii_int_list

def ascii_int_list2string(ascii_int_list):
    string=[]
    for integer in ascii_int_list:
        string.append(chr(integer))
    return ''.join(string)
   
def append_zeros_at_front(num, no_of_digits):
    num_str = str(num)
    length = len(num_str)
    if length >= no_of_digits:
        return num_str
    for i in range(no_of_digits - length):
        num_str = '0' + num_str
    return num_str


def synchronize(str, arduino):
    while arduino.readline() != str:
        pass
    