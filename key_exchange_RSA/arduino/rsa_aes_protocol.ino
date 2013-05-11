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

long RSA_Own_Private_Key[2] = {5723, 3341};
const int MOST_NO_OF_DIGITS = 10;

#include "rsa.h"
#include "aes.h"
#include <string.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,10,11,12,13);

void lcd_print_string(char *text, LiquidCrystal lcd, int delay_time = 2000, int lcd_size = 32) {
  int length = size_string(text);
  int lcd_half_size = lcd_size / 2;
  int no_of_lines = length / lcd_half_size;
  int length_last_line = length % lcd_half_size;
  lcd.clear();

  for (int i = 0; i < no_of_lines + 1; ++i) {
    if (i % 2 == 0) 
      lcd.setCursor(0,0);
    else
      lcd.setCursor(0,1);
    lcd.print(text + i * lcd_half_size);
    if (i % 2) {
      delay(delay_time);
      if (i != no_of_lines)
        lcd.clear();
    }
  }
}

void lcd_print_string(unsigned char *text, LiquidCrystal lcd, int delay_time = 2000, int lcd_size = 32) {
  int length = size_string(text);
  int lcd_half_size = lcd_size / 2;
  int no_of_lines = length / lcd_half_size;
  int length_last_line = length % lcd_half_size;
  lcd.clear();

  for (int i = 0; i < no_of_lines + 1; ++i) {
    if (i % 2 == 0) 
      lcd.setCursor(0,0);
    else
      lcd.setCursor(0,1);
    lcd.print((char *)(text + i * lcd_half_size));
    if (i % 2) {
      delay(delay_time);
      if (i != no_of_lines)
        lcd.clear();
    }
  }
}

void cycle_arduino_to_PC(long *AES_Key) {
  unsigned char ptext[100] = "You with your switching sides and your walk-by lies and humiliation", *ctext;
  
  int FINAL_LENGTH = size_string(ptext);
  unsigned char AES_Key_uc[178];
  AES_Key_uc[176]='\0';
  for (int i = 0; i < 16; ++i) {
    AES_Key_uc[i] = AES_Key[i];
  }
  
  ctext = ECB_AES_encrypt(ptext, AES_Key_uc, FINAL_LENGTH);
  
  Serial.println(to_string(FINAL_LENGTH));
  
  for (int i = 0; i < FINAL_LENGTH; ++i) {
    Serial.println(ctext[i]);
  }
}
  
void cycle_PC_to_arduino(long* AES_Key) {
  unsigned char ctext[100], *ptext, AES_Key_uc[178];
  AES_Key_uc[176] = '\0';
  int length;
  char length_string[MOST_NO_OF_DIGITS + 1];
  Serial.readBytes(length_string, MOST_NO_OF_DIGITS);
  length_string[MOST_NO_OF_DIGITS] = '\0';
  length = to_num(length_string);
  int i;
  for (i = 0; i < length; ++i) {
    char num_str[4]; 
    Serial.readBytes(num_str, 3);
    num_str[3] = '\0';
    ctext[i] = to_num(num_str);
    Serial.println(ctext[i]);
  }
  ctext[i] = '\0';

  for (int j = 0; j < 16; ++j) {
    AES_Key_uc[j] = AES_Key[j]; 
  } 

  ptext = ECB_AES_decrypt(ctext, AES_Key_uc);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd_print_string(ptext, lcd);
  
  delay(10000);  
}

long* get_AES_Key() {
  long *AES_Key_Encrypted;
  long *AES_Key;
  AES_Key_Encrypted = new long[17];
  AES_Key_Encrypted[16] = '\0';
  for (int i = 0; i < 16; ++i) {
    char num_str[MOST_NO_OF_DIGITS + 1];
    num_str[MOST_NO_OF_DIGITS] = '\0';
    Serial.readBytes(num_str, MOST_NO_OF_DIGITS);
    AES_Key_Encrypted[i] = to_num(num_str);
  }
  AES_Key = rsa_decrypt(AES_Key_Encrypted, RSA_Own_Private_Key, 16);
  delete[] AES_Key_Encrypted;
  return AES_Key;
}

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  
  Serial.begin(115200);
  Serial.write("TkSOzZU9Wd*!byau$U2a\n");
  long *AES_Key;

    
  
  char mode[14];
  mode[13] = '\0';
  Serial.readBytes(mode, 13);
  if (strcmp(mode, "PC_TO_ARDUINO") == 0) {
    lcd.setCursor(0,1);
    lcd.print("PC TO ARDUINO");
    AES_Key = get_AES_Key();
    
    char indication[MOST_NO_OF_DIGITS + 1];
    Serial.readBytes(indication, MOST_NO_OF_DIGITS);
    indication[MOST_NO_OF_DIGITS] = '\0';
    while (strcmp(indication, "2&g&xb3leL") != 0) {
      AES_Key = get_AES_Key();
      Serial.readBytes(indication, MOST_NO_OF_DIGITS);
    }
    cycle_PC_to_arduino(AES_Key);
  }
  else if (strcmp(mode, "ARDUINO_TO_PC") == 0) {
    lcd.setCursor(0,0);
    lcd.print("ARDUINO TO PC");
    AES_Key = get_AES_Key();
    cycle_arduino_to_PC(AES_Key);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("NO MODE SELECTED");
    delay(10000);
  }
}

void loop() {
  
  
}

