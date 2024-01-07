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

#Public Key = {e, n} and Private Key = {d, n}

def rsa_encrypt(plaintext, key):
    n, e = key
    plaintext_list = string2ascii_int_list(plaintext)
    ciphertext_list = []

    for M in plaintext_list:
        C = pow(M, e, n) # pow (a,b[,c]) returns (a**b) mod c
        ciphertext_list.append(C)

    return ciphertext_list


def rsa_decrypt(ciphertext_list, key):
    n, d = key
    plaintext_list = []

    for C in ciphertext_list:
        M = pow(C, d, n)
        plaintext_list.append(M)
    plaintext = ascii_int_list2string(plaintext_list)
    return plaintext
