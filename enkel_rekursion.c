#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct burgers_and_beer{
	int burgers; 
	int beer;
} burgers_and_beer;

burgers_and_beer compute_burgers_and_beer(int m, int n, int t);
burgers_and_beer initialize_bb(int t);
void clear_string(char *string);

int main (int argc, const char *argv[])
{
	FILE *test_cases = fopen(argv[1], "r");

	burgers_and_beer result;
	
	char c;
	char s[6];
	int read_integers = 1;
	int m;
	int n;
	int t;
	do
	{
		c = fgetc(test_cases);
		if (c != ' ' && c != EOF)
		{
			s[strlen(s)] = c;
		}
		else
		{
			s[strlen(s)] = '\0';
			if (read_integers == 3)
			{
				t = atoi(s);
				result = compute_burgers_and_beer(m, n, t);
				printf("%d %d ", result.burgers, result.beer);
				read_integers = 1;
				clear_string(s);
			}
			else if (read_integers == 1)
			{
				m = atoi(s);
				read_integers ++;
				clear_string(s);
			}
			else if (read_integers == 2)
			{
				n = atoi(s);
				read_integers ++;
				clear_string(s);
			}
		}
	} while (c != EOF);
}

burgers_and_beer compute_burgers_and_beer(int m, int n, int t)
{
	burgers_and_beer option_m = initialize_bb(t);
	burgers_and_beer option_n = option_m;

	if (t == 0)
	{
		return option_m;
	}
	
	if (t - m >= 0)
	{
		option_m = compute_burgers_and_beer(m, n, t-m);
	}
	option_m.burgers ++;


	if (t - n >= 0)
	{
		option_n = compute_burgers_and_beer(m, n, t-n);
	}
	option_n.burgers ++;

	if (option_m.burgers != 0 && option_n.burgers != 0)
	{
		if (option_m.beer == option_n.beer)
		{
			if (option_m.burgers > option_n.burgers)
			{
				return option_m;
			}
			else
			{
				return option_n;
			}
		}
		else if (option_m.beer < option_n.beer)
		{
			return option_m;
		}
		else
		{
			return option_n;
		}
	}
	else
	{

	}
}

burgers_and_beer initialize_bb(int t)
{
	burgers_and_beer bb;
	bb.burgers = 0;
	bb.beer = t;
	return bb;
}

void clear_string(char *string)
{
	int l = strlen(string);
	for (int i = 0; i <= l; i++)
	{
		string[i] = '\0';
	}
}