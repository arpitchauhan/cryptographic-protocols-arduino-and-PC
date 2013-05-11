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

from Euclid import *
from random import randint

def findkq(n):
    """ Find k and q such that n = (2**k)*q  """
    if n % 2 == 0 or n<0:
        return "Error"
    n_new = n-1;

    # 1.Find integers k, q with k>0 and q odd, such that N = (2^k)*q
    k = 0
    q = 0
    while (n_new):
        n_new /= 2
        k += 1
        if n_new % 2 != 0:
            q = n_new
            break    
    return [k,q]

def isprime(n, iterations = 1):
    """ Primality test using Miller-Rabin algorithm"""
    if n % 2 == 0:
        return False
    # 1. Find integers k,q with k>0, q odd, so that n - 1 = (2**k)*q
    k, q = findkq(n)
    
    
    # 2. Select a random integer a, 1 < a < n-1
    for i in range(iterations):
        result = test3(n, k, q)
         
        if result =="composite":
            return False
        
    return True

def test3(n, k, q):
    a = randint(2, n-2)
        # 3. if a**q mod n = 1, then return "inconclusive"
    if (a**q) % n == 1:
        return "inconclusive"
    # 4. and 5.     
    for j in range(k):
        if a**(q*(2**j)) % n  == n - 1:
            return "inconclusive"
    return "composite" 