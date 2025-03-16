class Cipher
{
public:
//take a string of plain text and get the base64 encoded string
virtual int Encrypt(char *plaintext, char *encrypted) { return 1; }
//take ina  base64 string of encrypted text and return hte unencypreted plaintaext
virtual int Decrypt(char *encrypted, char *plaintext) { return 1; }
virtual void Initialize(char *Setup) { }
Cipher() { }
~Cipher() { }
};
