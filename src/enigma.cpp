#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "enigma.h"
#include "base64.h"
int Enigma::Encrypt(char *plaintext, char *encrypted)
{
if (first_flag == 1)
{
reset();
SetRotorPositions();
first_flag=0;
}

char *output=enigma(plaintext);
char *base64_data1 = base64_encode((const unsigned char *) output,strlen(output));
	
strcpy(encrypted,base64_data1);
		
return 1;
}
//take ina  base64 string of encrypted text and return hte unencypreted plaintaext


int Enigma::Decrypt(char *encrypted, char *plaintext)
{
char *plaintext1 = (char *)malloc(sizeof(char)*255);
int status=base64_decode((const char *) encrypted, (unsigned char *) plaintext1,strlen(encrypted),161);
if (status != 1)
{
fprintf(stdout,"Decode Error!");
}
if (first_flag == 0)
{
reset();
SetRotorPositions();
first_flag=1;
}
int c=decryptsize(encrypted);
plaintext1[c]='\0';

char *output=enigma(plaintext1);
strcpy(plaintext,output);
return 1;
}

int Enigma::decryptsize(char *v)
{
//get the length of the base64 encrypted size
int done=0;
int q=strlen(v);
int p=q-1;
int count=0;
while (!done)
{
  if (p < 0) { done=1;continue;}
  if (v[p] == '=') count++;
  if (v[p] != '=')
  {
   done=1;
   continue;
  }
p--;
}
return (3 * (q / 4)) - count;
}


void Enigma::Initialize(char *Setup)
{
   InitEnigma();
   TryUserSetup(Setup);


}

Enigma::Enigma()
{
first_flag=1;
lastsize=-1;
alphabet = new char[75];
strcpy(alphabet,"abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?");
for (int i=0;i<11;i++)
{
ROTOR[i] = new char[75];
if (i < 6) REFLECTOR[i] = new char[75];
}
strcpy(ROTOR[0],alphabet);
strcpy(ROTOR[1],"ekmflgdqvzntowyhxuspaibrcj4.:5,63)-&;' +*7/\"](081[29?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[2],"ajdksiruxblhwtmcqgznpyfvoe093.]8[\"/1,7+':2)6&;(*5- 4?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[3],"bdfhjlcprtxvznyeiwgakmusqo13579,2(['/-&;*48+60.:\"]) ?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[4],"esovpzjayquirhxlnftgkdcmwb4] -(&90*)\"8[7/,;5'6.32:+1?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[5],"vzbrgityupsdnhlxawmjqofeck-&1[68'*\"(]3;7,/0+:9) 542.?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[6],"jpgvoumfyqbenhzrdkasxlictw9(6- \":5*)14;7&[3.0]/,82'+?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[7],"nzjhgrcxmyswboufaivlpekqdt;&976[2/:*]+1 \"508-,(4.)3'?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[8],"fkqhtlxocbjspdzramewniuygv5.)7',/ 219](3&[0:4+;8\"*6-?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[9],"leyjvcnixwpbqmdrtakzgfuhos,4*9-2;8/+(1):3['0.&65\"7 ]?><\\|}{=^_%$#@!`~");
strcpy(ROTOR[10],"fsokanuerhmbtiycwlqpzxvgjd5] .0;\"4[7:1'8*2+,)(&/-693?><\\|}{=^_%$#@!`~");

// Position in which each rotor causes its left neighbor to turn
// (The beta and gamma rotors could only be used in the Naval-Enigma
//  fourth position, and did not have knock-on effect.  So, their
//  notch positions are meaningless)
//NOTCH = new char[12];
NOTCH[0]='z';
NOTCH[1]='q';
NOTCH[2]='e';
NOTCH[3]='v';
NOTCH[4]='j';
NOTCH[5]='z';
NOTCH[6]='z';
NOTCH[7]='z';
NOTCH[8]='z';
NOTCH[9]='z';
NOTCH[10]='a';
NOTCH[11]='a';


strcpy(REFLECTOR[0],"abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?");
strcpy(REFLECTOR[1],"yruhqsldpxngokmiebfzcwvjat*[\"7)],3(/;6 .:8415&2+-90'?<>\\|}{=_^%$#@`!~");
strcpy(REFLECTOR[2],"yruhqsldpxngokmiebfzcwvjat*[\"7)],3(/;6 .:8415&2+-90'?<>\\|}{=_^%$#@`!~");
strcpy(REFLECTOR[3],"fvpjiaoyedrzxwgctkuqsbnmhl5-(980 *43[&/+62'.\")]1;:7,?<>\\|}{=_^%$#@`!~");
strcpy(REFLECTOR[4],"enkqeuywjicopblmdxzvfthrgs4;.)0\"*+982 (1,:3/&-5'7[6]?<>\\|}{=_^%$#@`!~");
strcpy(REFLECTOR[5],"rdobjntkvehmlfcwzrxgyipsuq[3 19;'.-47:,52+&0/6*8(]\")?<>\\|}{=_^%$#@`!~");
PLUGBOARD = new char[75];
strcpy(PLUGBOARD,"abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?");

}



int checkUpper(unsigned char X)
{
if (isupper(X)) return 1;
if (X > 128) return 1;
return 0;
}

unsigned char lower_case(unsigned char X)
{
unsigned char retval;
retval=tolower(X);
if (retval != X && X < 128)
{
retval=X+128;
return retval;
}
return retval;
}

unsigned char upper_case(unsigned char X)
{
unsigned char retval;
retval=toupper(X);
if (retval != X) return retval;
if (X > 128)
{
return X-128;
}
return X+128;
}

void Enigma::InitEnigma() // Default initialization
{
   int i;

   mRotors = 3;
   mSteps = (mRotors << 1) + 3;
   strcpy( plugboard, PLUGBOARD );
   for ( i = 0; i <= mRotors; ++i ) {
      RotWiring[ i ] = ROTOR[ i ];
      RotNotch[ i ] = NOTCH[ i ];
      RotNumber[ i ] = i;
      Iwindow[ i ] = window[ i ] = 'a';
   }
   reflector = REFLECTOR[ 1 ];
   ReflType = 1;
}
void Enigma::TryUserSetup(char *CONFIG)
// Attempt initialization from user file
{
  if (CONFIG == NULL) return;
  else
   {
      SetPlugboard(CONFIG);
      SetRotorsAndReflector(CONFIG);
   }
}

void Enigma::reset()
{
   for ( int i = 1; i <= mRotors; ++i )
      window[ i ] = Iwindow[ i ];
}

void Enigma::SetPlugboard(char *CONFIG)  // make connections on the plug board
{
    int i, n, x;
   char p1, p2, ch;

   // Read a line containing pairs of letters corresponding to pairs of
   // plugs connected by a wire.  The length of the line is assumed to be even.
   char *SETUP= (char *) malloc(sizeof(char) * strlen(CONFIG)+1);
   strcpy(SETUP,CONFIG);
   char *iNline= strtok(SETUP, "\n");
   if (iNline == NULL) return;
   n = strlen( iNline );

   for ( i = 0; i < n; i += 2 ) {
      p1 = iNline[ i ];
      p2 = iNline[ i+1 ];
      x = fetch_index( p1 );
      if ( (ch = plugboard[ x ]) != p1 ) { // occupied? -> disconnect
	 plugboard[ fetch_index( ch ) ] = ch;
	 plugboard[ x ] = p1;
      }
      plugboard[ x ] = p2;                 // plug in
      x = fetch_index( p2 );
      if ( (ch = plugboard[ x ]) != p2) { // occupied? -> disconnect
	 plugboard[ fetch_index( ch ) ] = ch;
	 plugboard[ x ] = p1;
      }
      plugboard[ x ] = p1;                // plug in
   }

}

void Enigma::SetRotorsAndReflector(char *CONFIG)
{
    int i, n, rotor, rotPos;
   char ch, ringPos;
    char *iNline;

   // Read the actual number of rotors "mRotors", compute the total
   // number of encryption steps "mSteps", and read "mRotors" lines,
   // each one containing three characters denoting
   //
   //   (a) rotor ID (1-8,b,g)
   //   (b) rotor position (1-mRotors), and
   //   (c) ring character (position)

   char *SETUP= (char *) malloc(sizeof(char) * strlen(CONFIG)+1);
   strcpy(SETUP,CONFIG);
//   iNline= strtok(SETUP, "\n");
   iNline= strtok(NULL, "\n");
   if (iNline == NULL) return;
   mRotors = ChrToInt( iNline[ 0 ] );
   if ( mRotors > 4 )
      mRotors = 4;
   mSteps = (mRotors << 1) + 3;
   for ( i = 1; i <= mRotors; ++i ) {
   iNline= strtok(NULL, "\n");
   if (iNline == NULL) return;
      ch = iNline[ 0 ];
      if ( isdigit( (int)ch ) )
	 rotor = ChrToInt( ch );
      else {
	 ch = tolower( ch );
	 rotor = ch == 'b' ? 9
			   : ch == 'g' ? 10 : 0;
      }
      rotPos = ChrToInt( iNline[ 1 ] );
      ringPos = iNline[ 2 ];
      Iwindow[ rotPos ] = window[ rotPos ] = ringPos;
      PlaceRotor( rotPos, rotor );
   }


   // Read a line containing the designation of the reflector (t,b,c,B,C)
   iNline= strtok(NULL, "\n");
   if (iNline == NULL) return;
   ch = iNline[ 0 ];
   switch ( ch ) {
      case 't': n = 0; break;      case 'b': n = 1; break;
      case 'c': n = 2; break;      case 'B': n = 3; break;
      case 'C': n = 4; break;       default: n = 0; break;
   }
   reflector = REFLECTOR[ n ];
   ReflType = i;
}

int Enigma::fetch_index( char c )
{
   // c in alphabet

   int i = 0;

   while ( (i < Nchars) && (c != alphabet[ i ]) )
      ++i;
   return i;
}

int Enigma::ChrToInt( char c )
{
   // '0' <= c <= '9'

   return (int)( c - '0' );
}

void Enigma::PlaceRotor( int position, int r )
// set wirings of a single rotor
{
   RotWiring[ position ] = ROTOR[ r ];
   RotNotch[ position ] = NOTCH[ r ];
   RotNumber[ position ] = r;
}

void Enigma::SetRotorPositions()
{
    int i, j, k;
   char *Rwiring, ch;

   for ( i = 1; i <= mRotors; ++i ) {
      j = RotNumber[ i ];
      ch = window[ j ];
      Rwiring = RotWiring[ j ];
      k = 0;
      while ( Rwiring[ k ] != ch )
	 ++k;
      RotPos[ j ] = k;
   }
}

int Enigma::mod( int n, int modulus )  // simple modulo function
{
   while ( n >= modulus )
      n -= modulus;
   while ( n < 0 )
      n += modulus;
   return n;
}

char * Enigma::enigma(char *input)
{
    int i, n;
    char *iNline = (char *) malloc(sizeof(char) * strlen(input)+1);
    strcpy(iNline,input);
    char *outLine = (char *) malloc(sizeof(char) * strlen(iNline)+2);

   unsigned char c1, c2;

      n = strlen( iNline );
      iNline[ n ] = '\0';


	bool wasUpper=false;

      for ( i = 0; i < n; ++i ) {
	 c1 = iNline[ i ];
	 if ( checkUpper( c1 ) )
	 {
	 wasUpper=true;
	 if (c1 < 128) c1 = tolower( c1 );
	 else c1=c1-128;
	 }

	 c2 = encrypt( c1 );
     if (wasUpper) { c2=upper_case(c2); wasUpper=false;}
	 // ShowRotors();
	 ShowWindow();
	 ShowSteps();
	 outLine[ i ] = c2;
      }
      outLine[ i ] = '\0';
      return outLine;
}

void Enigma::ShowWindow()
{
   int i;

   for ( i = mRotors; i >= 1; --i );
}

void Enigma::ShowSteps()
{
   int i;

   for ( i = 0; i < mSteps; ++i );
}

 char Enigma::encrypt( char c )
    {
       int i, r;

       turn();                                          // move rotors
       i = 0;                                           // pass through:
       step[ i++ ] = plugboard[ fetch_index( c ) ];           //    plugboard
       for ( r = 1; r <= mRotors; ++r )
	  step[ i++ ] = RtoLpath( step[ i-1 ], r );     //    right-to-left path
       step[ i++ ] = reflector[ fetch_index( step[ i-1 ] ) ]; //    reflector
       for ( r = mRotors; r >= 1; --r )                 //    left-to-right path
	  step[ i++ ] = LtoRpath( step[ i-1 ], r );
       step[ i ] = plugboard[ fetch_index( step[ i-1 ] ) ];   //    plugboard

       return step[ i ];
    }

void Enigma::turn()   // determine which rotors must turn
{
    int doit[ Nrotors ], n;
   char *r1 = RotWiring[ 1 ];
   char *r2 = RotWiring[ 2 ];
   char *r3;

   if ( mRotors > 3 )
      r3 = RotWiring[ 3 ];

    // calculate stepwidth for each rotor
    doit[ 1 ] = 1;
    for (int i = 2; i <= mRotors; ++i )
       doit[ i ] = 0;
    if ( (RotNotch[ 1 ] == r1[ RotPos[ 1 ] ])
	 ||
	 (RotNotch[ 2 ] == r2[ RotPos[ 2 ] ]) )  // double stepping
       doit[ 2 ] = 1;
    if ( RotNotch[ 2 ] == r2[ RotPos[ 2 ] ] )
       doit[ 3 ] = 1;
    if ( mRotors > 3 ) {
       if ( RotNotch[ 3 ] == r3[ RotPos[ 3 ] ] )
	  doit[ 4 ] = 1;
    }

    // turn rotors "simultaneously"
    for ( n = 1; n <= mRotors; ++n )
       TurnRot( n, doit[ n ] );
}

void Enigma::TurnRot( int n, int width )   // Turn rotor "n" "width" times
{                                  // wrapping around if necessary
   char *r;

   if ( width > 0 ) {
      RotPos[ n ] = mod( RotPos[ n ] + width, Nchars );
      r = RotWiring[ n ];
      window[ n ] = r[ RotPos[ n ] ];
   }
}

char Enigma::RtoLpath( char c, int r )  // transform character "c" with rotor "r"
{
    int n, offset, idx, ret;
   char *CurRotor;

   CurRotor = RotWiring[ r ];
   n = fetch_index( c );
   offset = fetch_index( CurRotor[ RotPos[ r ] ] );
   idx = mod( n + offset, Nchars );
   ret = mod( fetch_index( CurRotor[ idx ] ) - offset, Nchars );
   return alphabet[ ret ];
}

// Transform on left-to-right path through rotors

char Enigma::LtoRpath( char c, int r ) // transform character "c" with rotor "r"
{
    int n, m, offset, idx, newchar;
   char *CurRotor;

   CurRotor = RotWiring[ r ];
   n = fetch_index( c );
   offset = fetch_index( CurRotor[ RotPos[ r ] ] );
   newchar = alphabet[ mod( n+offset, Nchars ) ];

   m = 0;
   while ( m < Nchars && CurRotor[ m ] != newchar )
      ++m;
   idx = mod( m - offset, Nchars );
   return alphabet[ idx ];
}



