/*

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

*/

#include <math.h>

long power(long a, long b) {
  long temp = 1;
  for (long i = 0; i < b; ++i) {
    temp = temp * a;
  }
  return temp;
}

int size_string (unsigned char* string )
{   int i;
  for (i = 0; string[i] != '\0'; ++i);
  return i;
}

int size_string (char* string )
{   int i;
  for (i = 0; string[i] != '\0'; ++i);
  return i;
}


char* to_string(long num) {
  char* str;
  if (num == 0) {
    str = new char[2];
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  long num_of_digits = (long) (log10(num)) + 1;
  long rem;
  
  str = new char[num_of_digits + 1];
  
  str[num_of_digits] = '\0';
  for (long i = num_of_digits- 1; i >= 0; --i) {
    
    rem = num % ((long)(10));
   
    char rem_char = (char)(rem + 48); // '0'
    str[i] = rem_char;
    num = num / 10;
  }
  
  return str;
}

long to_num(char* str) {
  int len = size_string(str);
  long num=0;
  int number_is_zero = 1;
  for (int i = 0; i < len; ++i) {
    if (str[i] != '0') {
      number_is_zero = 0;
      break;  
    }
  }
  if (number_is_zero == 1)
    return 0;
  for (int i = 0; i < len; ++i) {
    if (str[i] != '0')
      num += power(10, len - i - 1) * ( str[i] - '0' ); 
  }
  return num;
}

void Serial_print_array(long* arr, long length, char *name) {
  for (int i = 0; i < length; ++i) {
    Serial.write(name);
    Serial.write("[");
    Serial.write(to_string(i));
    Serial.write("] = ");
    Serial.println(to_string(arr[i]));
  }
}

void Serial_print_array(unsigned char* str, long length, char *name) {
  for (int i = 0; i < length; ++i) {
    Serial.write(name);
    Serial.write("[");
    Serial.write(to_string(i));
    Serial.write("] = ");
    Serial.println(str[i]);
  }
}

long raiseto_mod(long a, long b, long c) {
  long temp = 1;
  for (long i = 0; i < b; ++i) {
    temp = (temp * a) % c;
  }
  return temp;
}


