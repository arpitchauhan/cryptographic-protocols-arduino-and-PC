This project demonstrates how an Arduino board and a PC can implement cryptographic protocols.

The protocols implemented are 
(i) Digital Signature
(ii) Key Exchange using Diffie-Hellman algorithm
(iii) Key Exchange using RSA (a public-key encryption algorithm)

In the digital signature protocol, either of the entities can digitally sign a message and
send it to the other entity. The signature asserts the integrity of the message. If the message
is tampered in any way while in transit, the receiving entity will come to know about it.

In the second protocol, viz. key exchange using Diffie-Hellman algorithm, the entity which is willing
to exchange data can initiate the exchange of an AES-128 key. Once both the entities possess the
AES key, they can exchange data by encrypting it with that key.

In the third protocol, the key exchange is done prior to exchange of data, by using RSA. Again, after
the entities have exchange an AES-128 key, they can exchange data by first encrypting it with that key.

In-depth discussion of the project can be found at: https://dl.dropboxusercontent.com/u/83966315/cryptographic-protocols-between-arduino-and-PC/cryptographic-protocols-between-arduino-and-PC.pdf

COPYRIGHT NOTICE

Copyright (C) 2013 Arpit Chauhan, Inderjit Sidhu and Archit Pandey

cryptographic-protocols-arduino-and-PC is free software: you can redistribute it and/or modify 
it under the terms of the GNU General Public License as published by 
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version.

cryptographic-protocols-arduino-and-PC is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with the software. It is in the file LICENSE.MD. 
If not available there, see <http://www.gnu.org/licenses/>
   



