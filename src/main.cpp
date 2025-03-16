#include <stdio.h>
#include <stdlib.h>
#include "enigma.h"
#include "base64.h"

void showoutput(char *input)
{
for (int i=0;i<strlen(input);i++)
{
 unsigned char m;
 m=input[i];
 fprintf(stdout,"%c",m);
}
}

int main(int argc, char **argv)
{
char Line[255];
char *L=fgets(Line,254,stdin);
char config[60];
strcpy (config,"azbycxdwevfugthsirjqkplomn\n3\n31a\n22b\n13c\nc");
Enigma Engine = Enigma();
Engine.Initialize(config);
char EncryptedHex[400];
char plaintext[400];
if (argc > 1) Engine.setFirstFlag(0);
while (L != NULL)
{
if (argc > 1)
{

 L[strlen(L)-1]='\0';
  Engine.Decrypt(L,plaintext);
  fprintf (stdout,"%s\n",plaintext);
}
else
{
   L[strlen(L)-1]='\0';
  Engine.Encrypt(L,EncryptedHex);
 fprintf (stdout,"%s\n",EncryptedHex);

 }
L=fgets(Line,254,stdin);


}
return 1;
}

