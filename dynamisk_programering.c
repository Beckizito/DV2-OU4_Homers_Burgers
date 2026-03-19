#include <stdio.h>
#include <stdlib.h>

typedef struct burgers_and_beer{
	int burgers; 
	int beer;
} burgers_and_beer;

void compute_burgers_and_beer(int m, int n, int t);
void initialize_bb(burgers_and_beer bb, int t);

int main (int argc, char *argv[], FILE **test_cases)
{
	FILE *test_cases = fopen(argv[1], "r");

	if (argc == 1)
	{
		if (*test_cases == NULL)
		{
			fprintf(stderr, "Could not open the file: %s\n", argv[1]);
			return 1;
		}
	}

	char c;
	int read_integers = 0;
	int m;
	int n;
	int t;

	//ändra f. ett tecken till att läsa alla tecken till ' ' 
	//hittas, så att m,n > 9 fungerar
	//om fler än 3 tal finns i filen läses dessa 
	while ((c = fgetc(test_cases) != EOF))
	{
		if (c != ' ')
		{
			read_integers ++;
			if (read_integers == 3)
			{
				t = atoi(&c);
				results = calloc(t, sizeof(burgers_and_beer));
				for (int i = 0; i < t; i++)
				{
					results[i] = compute_burgers_and_beer(m, n, t);
				}
				printf("%d %d", results[t-1].burger, results[t-1].beer);
				free(results);
				read_integers = 0;
			}
			else if (read_integers == 1)
			{
				m = atoi(&c);
			}
			else if (read_integers == 2)
			{
				n = atoi(&c);
			}
		}
	}
}

void compute_burgers_and_beer(int m, int n, int t)
{
	burgers_and_beer option_m;
	burgers_and_beer option_n;
	initialize_bb(option_m, t);
	initialize_bb(option_n, t);

	if (t - m >= 0)
	{
		if (results[t-m] >= 0)
		{
			option_m = results[t-m]
		}
		option_m.burgers ++;
	}

	if (t - n >= 0)
	{
		if (results[t-n] >= 0)
		{
			option_n = results[t-n]
		}
		option_n.burgers ++;
	}

	if (option_m.burgers != 0 && option_n.burgers != 0)
	{
		if (option_m.beer == option_n.beer)
		{
			if (option_m.burgers > option_n.burgers)
			{
				results[t] = option_m;
			}
			else
			{
				results[t] = option_n;
			}
		}
		else if (option_m.beer < option_n.beer)
		{
			results[t] = option_m;
		}
		else
		{
			results[t] = option_n;
		}
	}
}

void initialize_bb(burgers_and_beer bb, int t);
{
	bb.burgers = 0;
	bb.beer = t;
}