#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct burgers_and_beer{
	int burgers; 
	int beer;
} burgers_and_beer;

burgers_and_beer compute_burgers_and_beer(int m, int n, int t, burgers_and_beer *results);
burgers_and_beer initialize_bb(int t);
void clear_string(char *string, int len);
void set_result(burgers_and_beer *results, burgers_and_beer option, int t);

int main (int argc, const char *argv[])
{
	FILE *test_cases = fopen(argv[1], "r");
	if (test_cases == NULL)
	{
		return 1;
	}
	
	char c;
	char s[6];
	clear_string(s, 5);
	int read_integers = 1;
	int m;
	int n;
	int t;

	do
	{
		c = fgetc(test_cases);
		if (c != ' ' && c != EOF && c != '\n')
		{
			s[strlen(s)] = c;
		}
		else
		{
			s[strlen(s)] = '\0';
			if (read_integers == 3)
			{
				t = atoi(s);
				burgers_and_beer results[t+1];
				int i = 0;
				while (i <= t)
				{
					results[i] = compute_burgers_and_beer(m, n, i, results);
					i++;
				}
				printf("%d ", results[t].burgers);
				if (results[t].beer != 0)
				{
					printf("%d", results[t].beer);
				}
				printf("\n");
				read_integers = 1;
				clear_string(s, strlen(s));
			}
			else if (read_integers == 1)
			{
				m = atoi(s);
				read_integers ++;
				clear_string(s, strlen(s));
			}
			else if (read_integers == 2)
			{
				n = atoi(s);
				read_integers ++;
				clear_string(s, strlen(s));
			}
		}
	} while (c != EOF);
	fclose(test_cases);
	return 0;
}

burgers_and_beer compute_burgers_and_beer(int m, int n, int t, burgers_and_beer *results)
{
	burgers_and_beer option_m = initialize_bb(t);
	burgers_and_beer option_n = option_m;

	if (t == 0)
	{
		return option_m;
	}
	if (t - m >= 0)
	{
		if (results[t-m].beer >= 0)
		{
			option_m = results[t-m];
		}
		option_m.burgers ++;
	}

	if (t - n >= 0)
	{
		if (results[t-n].beer >= 0)
		{
			option_n = results[t-n];
		}
		option_n.burgers ++;
	}

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
		if (option_m.beer < option_n.beer)
		{
			return option_m;
		}
		else
		{
			return option_n;
		}
	}
}

burgers_and_beer initialize_bb(int t)
{
	burgers_and_beer bb;
	bb.burgers = 0;
	bb.beer = t;
	return bb;
}

void clear_string(char *string, int len)
{
	int i = 0;
	while (i <= len)
	{
		string[i] = '\0';
		i++;
	}
}

void set_result(burgers_and_beer *results, burgers_and_beer option, int t)
{
	results[t].burgers = option.burgers;
	results[t].beer = option.beer;
}