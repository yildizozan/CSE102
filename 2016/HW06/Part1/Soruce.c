#include <stdio.h>

void freg(char *str, int *fr);

int main(void)
{
	int c = 0;
	int fr[37] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	char str[80] = "11111abdozanc12xxx3ABCD9124";

	freg(str, fr);

	for (c = 0; c < 36; c++)
	{
		if (c < 26)
			printf("%d\t%c\t%d\n", c, c + 'a', fr[c]);

		else if (25 < c && c < 36)
			printf("%d\t%d\t%d\n", c, c - 26, fr[c]);
	}

	return 0;
}

void freg(char *str, int *fr)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if ('a' <= str[i] && str[i] <= 'z')
			fr[str[i] - 'a']++;

		if ('A' <= str[i] && str[i] <= 'Z')
			fr[str[i] - 'A']++;

		if (48 <= str[i] && str[i] <= 57)
			fr[str[i] - 22]++;
	}
}