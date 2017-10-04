#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>

void testAes(char inString[], int inLen, char passwd[], int pwdLen)
{
	int i, j, len, nLoop, nRes;
	char enString[1024];
	char deString[1024];
	unsigned char buf[16];
	unsigned char buf2[16];
	unsigned char aes_keybuf[32];
	AES_KEY aeskey;

	memset(aes_keybuf, 0x90, 32);
	len = pwdLen < 32 ? pwdLen : 32;

	for (i = 0; i < len; i++)
		aes_keybuf[i] = passwd[i];

	nLoop = inLen / 16;
	nRes = inLen % 16;

	AES_set_encrypt_key(aes_keybuf, 256, &aeskey);

	for (i = 0; i < nLoop; i++)
	{
		memset(buf, 0, 16);
		for (j = 0; j < 16; j++)
			buf[j] = inString[i * 16 + j];
		AES_encrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			enString[i * 16 + j] = buf2[j];
	}

	if (nRes > 0)
	{
		memset(buf, 0, 16);
		for (j = 0; j < nRes; j++)
			buf[j] = inString[i * 16 + j];
		AES_encrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			enString[i * 16 + j] = buf2[j];
		puts("encrypt");
	}
	enString[i * 16 + j] = 0;

	// Decrypt
	AES_set_decrypt_key(aes_keybuf, 256, &aeskey);
	for (i = 0; i < nLoop; i++)
	{
		memset(buf, 0, 16);
		for (j = 0; j < 16; j++)
			buf[j] = enString[i * 16 + j];
		AES_decrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			deString[i * 16 + j] = buf2[j];
	}
	if (nRes > 0)
	{
		memset(buf, 0, 16);
		for (j = 0; j < 16; j++)
			buf[j] = enString[i * 16 + j];
		AES_decrypt(buf, buf2, &aeskey);
		for (j = 0; j < 16; j++)
			deString[i * 16 + j] = buf2[j];
		puts("decrypt");
	}
	deString[i * 16 + nRes] = 0;

	// Compare
	if (!memcmp(inString, deString, strlen(inString)))
		printf("test success\n");
	else
		printf("test fail\n");

	printf("The original string is: \t%s\n", inString);
	printf("The encrypted string is:\t%s\n", enString);
	printf("The decrypted string is:\t%s\n", deString);
}

int main(int argc, char * argv[])
{
	char inString[] = "This is a sample. I am a programmer.\n";
	char passwd[] = "0123456789ABCDEFGHIJK";
	testAes(inString, strlen(inString), passwd, strlen(passwd));
	return 0;
}
