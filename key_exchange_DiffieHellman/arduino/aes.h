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

unsigned char sbox[256] = 
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
unsigned char inv_sbox[256] = 
{
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

unsigned char rcon[11] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,0x36};
const int block = 16; // 16 bytes = 128 bits (AES-128)

//________________ENCRYPT SECTION START

void schedule_core(unsigned char *in, unsigned char i) {
    unsigned char a;
    // Rotate the input 8 bits to the left 
    unsigned char c;
    a = in[0];
    for(c=0;c<3;c++) 
            in[c] = in[c + 1];
    in[3] = a;
		// Apply Rijndael's S-box on all 4 bytes 
		for(a = 0; a < 4; a++) 
      in[a] = sbox[in[a]];
    in[0] ^= rcon[i];
}

void expand_key(unsigned char *key) {
    unsigned char t[4];
    //first sub-key is the user-supplied key 
    unsigned char c = 16;
    unsigned char i = 1;
    unsigned char a;

         
    while(c < 176) {             
        for(a = 0; a < 4; a++) 
        t[a] = key[a + c - 4];
     
            if(c % 16 == 0) {
                schedule_core(t,i);
                i++;
		        }

        for(a = 0; a < 4; a++) {
            key[c] = key[c - 16] ^ t[a];
            c++;
        }
    }
}

void addroundkey(unsigned char *state,unsigned char *key,unsigned short int& Round)
{
  	unsigned short int index=0;
  	index=Round; index=(index*16);
  	for(unsigned short int i=0;i<16;i++)
  	{
  		
  		state[i]^=key[index];
  		
  		index++;
  	}
}
void substitution_byte(unsigned char *state)
{
  	unsigned short int row,col;
  	for(unsigned int i=0;i<16;i++)
  	{
  		row=state[i] & 0xf0;
  		row = row >> 4; 
  		col=state[i]&0x0f;
  		state[i]=sbox[16*row+col];
  	
  	}
}

void shift_rows(unsigned char *state)
{
  	unsigned char temp_state[17];
  	unsigned short int loopcount=0,state_index;
  	for(;loopcount<4;loopcount++)
  	{
  		state_index=loopcount*4;
  		temp_state[loopcount*4]=state[state_index];
  		
  		for(unsigned short int temp_index=((loopcount*4)+1);temp_index<((loopcount*4)+4);temp_index++)
  		{
  			state_index=state_index+5;
  			if(state_index>15)
  			state_index=state_index-16;
  			temp_state[temp_index]=state[state_index];
  			
  		}
  	}
  	for(unsigned short int i=0;i<16;i++)
  		state[i]=temp_state[i];
}

void gmix_column(unsigned char *r) {
    unsigned char a[4];
    unsigned char b[4];
  	unsigned char c;
  	unsigned char h;	
  	for(c=0;c<4;c++) {
  		a[c] = r[c];
  		h = r[c] & 0x80; 
  		b[c] = r[c] << 1;
  		if(h == 0x80) 
  			b[c] ^= 0x1b; 
  		}
  	r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
  	r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
  	r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
  	r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}

void mix_column(unsigned char *state) {
  	for ( int i = 0; i < 4; ++i) 
  		gmix_column(state + (i*4));
}

void genericround(unsigned char* state, unsigned char* expandedkey, unsigned short int& Round) {
  	substitution_byte(state);
  	shift_rows(state);
  	mix_column(state);
  	addroundkey(state, expandedkey, Round);			
}

void lastround(unsigned char* state, unsigned char* expandedkey, unsigned short int& Round) {
  	substitution_byte(state);
  	shift_rows(state);
    addroundkey(state, expandedkey, Round);
}

void AES_encrypt(unsigned char *state, unsigned char *key) {
  	// First phase: addRoundKey call once
  	unsigned short int Round = 0;
  	addroundkey(state, key, Round);
  	
  	Round++;
  	//Second phase: call genericround() 9 times
  	for (unsigned short int i = 1; i<= 9 ; ++i) {
  		genericround(state, key, Round);
  		Round++;
  	}
  	// Third phase: call an incomplete round
  	lastround(state,key,Round);
    	//return state;
}

/*
Commented out as zeropadding was included in the ECB_AES_encrypt function itself

unsigned char* zeropadding(unsigned char *string, int block, int& adjusted_length) {
    // length_last_block is 0 if the length is a multiple of block and the length of the last block otberwise
  	
  	int length = size_string(string);
    
    int no_of_blocks = length / block + 1;

    int length_last_block = length % block;
    if (length_last_block == 0) 
      return string;
    int pos = block * (no_of_blocks - 1) + length_last_block;
    
    for (int i = 0; i < block - length_last_block; ++i) {
      //pos = block * no_of_blocks;
      string[pos] = 0;
      
      ++pos;   
    }
    string[pos] = '\0';
    length = pos;
    adjusted_length = pos;
    
    return string;
}
*/

unsigned char* ECB_AES_encrypt(unsigned char* plaintext, unsigned char* key, int& FINAL_LENGTH) {
    expand_key(key);   
    int length = size_string(plaintext);
    int no_of_blocks;  
    int length_last_block = length % block;
    if (length_last_block == 0)
  	  no_of_blocks = length / block;
    else
  	  no_of_blocks = length / block + 1;
    
    unsigned char* ciphertext; // = zeropadding(plaintext, block, FINAL_LENGTH ); 
    
    // ZERO PADDING STARTS
    int pos;
    if (length_last_block != 0) {
      pos = block * (no_of_blocks - 1) + length_last_block;
      for (int i = 0; i < block - length_last_block; ++i) {
      //pos = block * no_of_blocks;
      plaintext[pos] = 0;
      
      ++pos;   
    }
    plaintext[pos] = '\0';
    FINAL_LENGTH = pos;
    }
    
    // ZERO PADDING ENDS

    ciphertext = plaintext;
    unsigned char *pointer_to_first_element_of_block;
    pointer_to_first_element_of_block = ciphertext;
    for (int i = 0; i < no_of_blocks; ++i) {
      
      AES_encrypt(pointer_to_first_element_of_block, key);
      pointer_to_first_element_of_block += block;
      
    }
    
    return ciphertext;

}
//_____________________ENCRYPT SECTION END_______________
//_____________________DECRYPT SECTION START_____________ 

void inverse_shiftrows(unsigned char *state)
{
    unsigned char temp_state[17];
    unsigned short int loopcount=0,cipher_index;
    for(;loopcount<4;loopcount++)
    {
    cipher_index=loopcount*4;
    for(unsigned short int temp_index=(loopcount*4);temp_index<((loopcount*4)+4);temp_index++)
      {
         temp_state[temp_index]=state[cipher_index];
         cipher_index=cipher_index+13;
         if(cipher_index>16)
            cipher_index=cipher_index-16;
      }
    }
    for(unsigned short int i=0;i<16;i++)
      state[i]=temp_state[i];
} 
void inverse_substitutionbytes(unsigned char *state)
{
    unsigned short int row,col;
    for(unsigned int i=0;i<16;i++)
    {
      row=state[i] & 0xf0;
      row = row >> 4; 
      col=state[i]&0x0f;
      state[i]=inv_sbox[16*row+col];

    }
}
unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for(counter = 0; counter < 8; counter++) {
    	if((b & 1) == 1) 
    		p ^= a;
    	hi_bit_set = (a & 0x80);
    	a <<= 1;
    	if(hi_bit_set == 0x80) 
    		a ^= 0x1b;		
    	b >>= 1;
    }
    return p;
}
void inv_mix_column(unsigned char *r) {
    unsigned char a[4];
    unsigned char c;
    for(c=0;c<4;c++) {
            a[c] = r[c];
            }
    r[0] = gmul(a[0],14) ^ gmul(a[3],9) ^ gmul(a[2],13) ^ gmul(a[1],11);
    r[1] = gmul(a[1],14) ^ gmul(a[0],9) ^ gmul(a[3],13) ^ gmul(a[2],11);
    r[2] = gmul(a[2],14) ^ gmul(a[1],9) ^ gmul(a[0],13) ^ gmul(a[3],11);
    r[3] = gmul(a[3],14) ^ gmul(a[2],9) ^ gmul(a[1],13) ^ gmul(a[0],11);
}
void inverse_mix(unsigned char *state)
{
    for(unsigned short int i=0;i<4;i++)
    inv_mix_column((state+i*4));
}
void decrypt_generic_round(unsigned char *state,unsigned char *key,unsigned short int& Round)
{
   inverse_shiftrows(state);
   inverse_substitutionbytes(state);
   addroundkey(state,key,Round);
   inverse_mix(state);
}

void decrypt_lastround(unsigned char *state,unsigned char *key,unsigned short int& Round)
{
    inverse_shiftrows(state);
    inverse_substitutionbytes(state);
    addroundkey(state,key,Round);
}
void AES_decrypt(unsigned char *ciphertext,unsigned char *key, int length)
{  
    unsigned short int Round = 10;

    addroundkey(ciphertext,key,Round);
    Round--;
    for(;Round>=1;Round--)
      decrypt_generic_round(ciphertext,key,Round);
    decrypt_lastround(ciphertext,key,Round); 
  
}

unsigned char* ECB_AES_decrypt(unsigned char *ciphertext, unsigned char *key) {
    expand_key(key);
    int length = size_string(ciphertext);
    int length_last_block = length % block;
    int no_of_blocks;
    if (length_last_block == 0)
      no_of_blocks = length / block;
    else
      no_of_blocks = length / block + 1;

    unsigned char * pointer_to_first_element_of_block;
    pointer_to_first_element_of_block = ciphertext;
    for (int i = 0; i < no_of_blocks; ++i) {
      
      AES_decrypt(pointer_to_first_element_of_block, key, block);
      pointer_to_first_element_of_block += block;
      

    }

    return ciphertext;
}


char* int2string(long num) {
    char* str;
    int num_of_digits = (int) (log10(num)) + 1;
    int remainder;
    str = new char[num_of_digits + 1];
    str[num_of_digits] = '\0';
    for (int i = num_of_digits-1; i >= 0; --i) {
        remainder = num % 10;
        char rem_char = (char)(remainder + '0'); //ASCII value of '0' = 48
        str[i] = rem_char;
        num = num / 10;
    }
    return str;
}