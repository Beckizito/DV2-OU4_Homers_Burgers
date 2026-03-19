#include <stdio.h>
#include <stdlib.h>

typedef struct burgers_and_beer{
	int burgers; 
	int beer;
} burgers_and_beer;

burgers_and_beer compute_burgers_and_beer(int m, int n, int t);
void initialize_bb(burgers_and_beer bb, int t);

int main (int argc, const char *argv[])
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

	burgers_and_beer result;
	
	char c;
	int read_integers;
	int m;
	int n;
	int t;
	while ((c = fgetc(test_cases) != EOF))
	{
		if (c != ' ')
		{
			read_integers ++;
			if (read_integers == 3)
			{
				t = atoi(&c);
				result = compute_burgers_and_beer(m, n, t);
				printf("%d %d", result.burgers, result.beer);
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

burgers_and_beer compute_burgers_and_beer(int m, int n, int t)
{
	burgers_and_beer option_m;
	burgers_and_beer option_n;

	initialize_bb(option_m, t);
	initialize_bb(option_n, t);

	if (t - m >= 0)
	{
		option_m.beer -= m;
		option_m = compute_burgers_and_beer(m, n, t-m);
		option_m.burgers ++;
	}

	if (t - n >= 0)
	{
		option_m.beer -= n;
		option_m = compute_burgers_and_beer(m, n, t-n);
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
		
	}
}

void initialize_bb(burgers_and_beer bb, int t)
{
	bb.burgers = 0;
	bb.beer = t;
}