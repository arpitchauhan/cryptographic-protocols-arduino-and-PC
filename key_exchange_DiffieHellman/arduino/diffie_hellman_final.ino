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

#include <LiquidCrystal.h>
#include "aes.h"

const long a = 6;
const long q = 761;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

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
    if (i % 2 ) {
      delay(delay_time);
      if (i != no_of_lines)
        lcd.clear();
    }
  }
}


unsigned char Diffie_Hellman_num_exchange(){

  long X, Y, Y_other, K, temp;
  char Y_other_str[MOST_NO_OF_DIGITS + 1], incByte;
  
  X = random(2, q-1);
  
  Y = raiseto_mod(a, X, q);
  
  Serial.readBytes(Y_other_str, MOST_NO_OF_DIGITS);
  Serial.println(to_string(Y));
  
  Y_other_str[MOST_NO_OF_DIGITS] = '\0';

  Y_other = to_num(Y_other_str);
  
  K = raiseto_mod(Y_other, X, q);
  int diffie_hellman_num = K % 256;
  return (unsigned char) diffie_hellman_num;
}


void cycle_arduino_to_PC(unsigned char *AES_Key) {
  unsigned char ptext[100] = "North Korea invaded the United States today", *ctext;
   
  int FINAL_LENGTH = size_string(ptext);  
  ctext = ECB_AES_encrypt(ptext, AES_Key, FINAL_LENGTH);
  
  Serial.println(to_string(FINAL_LENGTH));
  
  for (int i = 0; i < FINAL_LENGTH; ++i) {
    Serial.println(ctext[i]);
  }
}


void cycle_PC_to_arduino(unsigned char* AES_Key) {
  unsigned char ctext[100], *ptext, AES_Key_uc[178];
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
  }
  ctext[i] = '\0'; 

  ptext = ECB_AES_decrypt(ctext, AES_Key);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd_print_string(ptext, lcd);
  delay(10000);  
}

void BenchmarkAES() {
  unsigned char AES_key[16], ptext[100], *ctext;
  unsigned long start_time_en, end_time_en, time_taken_en;
  unsigned long start_time_de, end_time_de, time_taken_de;
  int FINAL_LENGTH;
  for (int i = 0; i < 16; ++i) {
    AES_key[i] = random(1,255); 
  }
  for (int i = 0; i < 48; ++i) {
    ptext[i] = random(1,255);
  }
  start_time_en = micros();
  ctext = ECB_AES_encrypt(ptext, AES_key, FINAL_LENGTH);
  end_time_en = micros();
  time_taken_en = end_time_en - start_time_en;
  unsigned char *ptext2;
  start_time_de = micros();
  ptext2 = ECB_AES_decrypt(ctext, AES_key);
  end_time_de = micros();
  time_taken_de = end_time_de - start_time_de;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Encrypt:");
  lcd.print(time_taken_en);
  unsigned char mu;
  mu = 230;
  lcd.print("mcs");  
  lcd.setCursor(0,1);
  lcd.print("Decrypt:");
  lcd.print(time_taken_de);
  lcd.print("mcs");
  delay(10000);
}

void setup() {
  lcd.begin(16, 2);
 
  Serial.begin(115200);
  // synchronization
  Serial.write("TkSOzZU9Wd*!byau$U2a\n");
  unsigned char AES_key[177];
  AES_key[176] = '\0';
  
  
  char mode[14];
  mode[13] = '\0';
  Serial.readBytes(mode, 13);
  if (strcmp(mode, "PC_TO_ARDUINO") == 0) {
    lcd.clear();
    for (int i = 0; i < 16; ++i) {
    AES_key[i] = Diffie_Hellman_num_exchange();
    }
    // read key starts again
    char indication[MOST_NO_OF_DIGITS + 1];
    Serial.readBytes(indication, MOST_NO_OF_DIGITS);
    indication[MOST_NO_OF_DIGITS] = '\0';
    while (strcmp(indication, "2&g&xb3leL") != 0) {
      for (int i = 0; i < 16; ++i) {
        AES_key[i] = Diffie_Hellman_num_exchange();
       }
      Serial.readBytes(indication, MOST_NO_OF_DIGITS);
   
    }
    
  cycle_PC_to_arduino(AES_key);
  }
  else if (strcmp(mode, "ARDUINO_TO_PC") == 0) {
    lcd.clear();
    lcd.print("ARDUINO TO PC");
    
    for (int i = 0; i < 16; ++i) {
    AES_key[i] = Diffie_Hellman_num_exchange();
    }
    
    cycle_arduino_to_PC(AES_key);
  }
  else if (strcmp(mode, "BENCHMARK_AES") == 0) {
    lcd.clear();
    lcd.print("BENCHMARKING AES");

    BenchmarkAES();

  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    
    lcd.print("NO MODE SELECTED");
 
    delay(10000);
  }


}



void loop() { }
