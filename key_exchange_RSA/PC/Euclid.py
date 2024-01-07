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

def gcd(a,b):
    """ Returns greatest common denominator by using recursive Euclidean algorithm  """
    if b==0:
        return a
    return gcd(b, a % b)

def extended_gcd(a, b):
    """ Recursive extended Euclidean algorithm """
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = extended_gcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    """ Returns the inverse of a modulo m """
    g, x, y = extended_gcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return pow(x, 1, m)

def getrelprime(num):
    """ Returns the smallest relative prime number to num """
    for i in xrange(2, num):
        if gcd(i, num) == 1:
            return i
