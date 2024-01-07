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

#include "md5.h"
#include "rsa.h"
#include <iostream>
#include <LiquidCrystal.h>
#define MAX_DIGITS_IN_PC_MSG_LENGTH 10
#define MOST_NO_OF_DIGITS 10

long RSA_Own_Private_Key[2] = {5723, 3341};
long RSA_Others_Public_Key[2] = {6887, 11};

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

using namespace std;

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
    lcd.print((char *)(text + i * lcd_half_size));
    if (i % 2 ) {
      delay(delay_time);
      if (i != no_of_lines)
        lcd.clear();
    }
  }
}


void cycle_arduino_to_pc(){
	char ch;
	char msg[500]="The meme for blind faith secures its won perpertuation by the simple unconscious expedient of discouraging ratinonal enquiry. -- Richard Dawkins";
	uint8_t *hash;
	long *cipher_text;

	long length;

	hash = md5sum(msg);                                  	// Hashing message

	cipher_text=rsa_encrypt(hash, RSA_Own_Private_Key);		// Encrypting the hash
	for(int i = 0; i < 16; ++i ){
	    Serial.println(cipher_text[i]);  					// Sending the Encrypted hash
	}
	int len = size_string(msg);
	Serial.println(to_string(len));									// Sending msg length to PC

	for(int i = 0; i < len; ++i ){
		Serial.println(msg[i]);								// Sending the msg

	}

}




void cycle_pc_to_arduino(){
	char len_str[MAX_DIGITS_IN_PC_MSG_LENGTH + 1];       						// Reading the length of pc_msg
	Serial.readBytes(len_str, MAX_DIGITS_IN_PC_MSG_LENGTH);

	len_str[MAX_DIGITS_IN_PC_MSG_LENGTH] = '\0';
	long pc_msg_length;
	pc_msg_length = to_num(len_str);
  lcd.setCursor(0,0);
	char *pc_msg;
    pc_msg = new char[pc_msg_length + 1];
    pc_msg[pc_msg_length] = '\0';
    for(long j = 0 ;j < pc_msg_length; ++j){
      char num_str[4];
      Serial.readBytes(num_str,3);
      num_str[3] = '\0';
      long pc_msg_i_int = to_num(num_str);
      pc_msg[j] = char(pc_msg_i_int);
    }

    Serial.println(pc_msg);

    long encrypted_hash_pc[16];
    for (long j = 0; j< 16; ++j) {
      char val_str[MOST_NO_OF_DIGITS + 1];
      Serial.readBytes(val_str, MOST_NO_OF_DIGITS);

      val_str[MOST_NO_OF_DIGITS] ='\0';
      if (j >-1){
      encrypted_hash_pc[j] = to_num(val_str);     // Reading Encrypted hash from PC.

      Serial.println(encrypted_hash_pc[j]);
      }

    }

    long *rsa_ptext;
    rsa_ptext = rsa_decrypt(encrypted_hash_pc, RSA_Others_Public_Key, 16);

    uint8_t* pc_msg_hash;
    lcd.clear();
    lcd_print_string(pc_msg,lcd);
    delay(2000);
    pc_msg_hash = md5sum((char*)pc_msg);
    int i = 0;
    for(i = 0; i< 16;++i){
    	if (pc_msg_hash[i] != rsa_ptext[i]){
    		lcd.setCursor(0,0);
                lcd.clear();
    		lcd.print("Hash mismatch");
            delay(2000);
                break;
    	}
    }
    if (i == 16){
    	lcd.setCursor(0,0);
        lcd.clear();
    	lcd.print("Hash match");
        delay(2000);

    }
}


void setup() {
    lcd.begin(16,2);
    lcd.clear();
    Serial.begin(115200);
    Serial.write("Ready\n");
    lcd.print("Ready>>>");

    char mode[14];
    mode[13] = '\0';
    Serial.readBytes(mode,13);
    if (strcmp(mode, "PC_TO_ARDUINO") == 0){
      cycle_pc_to_arduino();
    }
    else if (strcmp( mode, "ARDUINO_TO_PC") == 0){
      cycle_arduino_to_pc();
    }
    else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("NO MODE SELECTED");
    }
}

void loop() {

}
