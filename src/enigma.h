#ifndef ENIGMA_H
#define ENIGMA_H

#define Nchars 69  // Total number of encipherable characters
#define Mchars 70  // Buffer size for strings containing Nchars
#define Nrotors 11 // Maximum number of rotors (1-based: 1-10)
#define Nrefls 5   // Total number of reflectors (1-based: 1-4)
#define Nsteps 11  // Maximum total number of encryption steps
#define bool int
#define false 0
#define true 1
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "cipher.h"

class Enigma : Cipher
{
int lastsize;
int first_flag;
char *ROTOR[ Nrotors ];
char NOTCH[ Nrotors ];
char *REFLECTOR[ Nrefls ];
char *PLUGBOARD;  // Default wirings of the plugboard
char *alphabet;  // Input alphabet
void InitEnigma();
int mRotors,                // Number of rotors placed in the machine
		    // (1-based: 1-4)
     mSteps;                // Actual number of encryption steps
			    // = 2*mRotors + 2 (plugboard) + 1 (reflector)
 int RotPos[ Nrotors ];     // Rotor placed in each position
char window[ Nrotors ],     // Characters in window
     Iwindow[ Nrotors ];    // Initial values in 'window' (for resetting)
char *RotWiring[ Nrotors ]; // Rotor wirings
char RotNotch[ Nrotors ];   // Rotor switching positions
 int RotNumber[ Nrotors ];  // Which physical rotor (t,1-8,b,g)
char *reflector,            // Wiring of the reflector
     plugboard[ Mchars ];   // Wirings of the plugboard
 int ReflType;              // Reflector used
char step[ Nsteps ];        // Array to store encryption steps
void reset();
void SetPlugboard(char *);
void SetRotorsAndReflector(char *);
int fetch_index(char);
int ChrToInt(char);
void PlaceRotor(int,int);
void SetRotorPositions();
int mod(int,int);
char *enigma(char *);
void ShowWindow();
void ShowSteps();
char encrypt(char);
void turn();
void TurnRot(int,int);
char RtoLpath(char,int);
char LtoRpath(char,int);
// Files and variables for setup and reporting
void TryUserSetup(char *);
public:
Enigma();
~Enigma() { }
int Encrypt(char *plaintext, char *encrypted);
//take ina  base64 string of encrypted text and return hte unencypreted plaintaext
int Decrypt(char *encrypted, char *plaintext);
void Initialize(char *Setup);
int decryptsize(char *v);
int setFirstFlag(int newflag) { first_flag=newflag; return 0;}
};

#define Nline 255
#endif
