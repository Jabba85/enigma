# The Enigma Machine Cipher

This is a c++ implemenetation of the Enigma machine.  It has been adapted to allow for both upper and lowercase characters, as well as some special characters ,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?

As each character is read form the input, it is transformed through a set of rotors and reflectors to arrive at the ciphered key. 

Imagine typing the keys on the orginal machine and having the corresponding output light up on above the keyboard

![Enigma](https://en.wikipedia.org/wiki/Bombe#/media/File:EnigmaMachineLabeled.jpg "Enigma Machine")

To reverse the process simply call the Decrypt function.

Note: This version outputs the cipher text in a base64 encoded scheme, and when decrypting assumes the input has been base64 decoded

The main funciton simply reads form stdin and outputs according to the setup-configuration. 

The machine is initialized with a string containing

a) The plugboard configuration (eg: A->Z, B->Y, C->X etc)
b) The Rotor and Reflector Configuration (eg: 3 Rotors, A-31, B-22, and C-13

Background
---

The Enigma machine is a cipher device developed and used in the early- to mid-20th century to protect commercial, diplomatic, and military communication. It was employed extensively by Nazi Germany during World War II, in all branches of the German military. The Enigma machine was considered so secure that it was used to encipher the most top-secret messages.

The security of the system depends on machine settings that were generally changed daily, based on secret key lists distributed in advance, and on other settings that were changed for each message. The receiving station would have to know and use the exact settings employed by the transmitting station to decrypt a message.

Alan Turing and his team at Bletchley Park invented a 'computer' known as the 'Bombe' approx 10 years before the first 'general purpose computer - UNIVAC which was released 1952


