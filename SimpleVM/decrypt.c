#include <stdio.h>
#include <string.h>

void main()
{
	int i;
	char one_char_buf;
	char enc[] = {0x42, 0x6D, 0x71, 0x76, 0x60, 0x65, 0x73, 0x29, 0x3, 0x00};

	for (i = 1; i <= strlen(enc); ++i )
    {
      one_char_buf = enc[i - 1] ^ i;
      printf("%c", one_char_buf);
    }
}