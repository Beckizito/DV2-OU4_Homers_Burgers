#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct burgers_and_beer{
	int burgers; 
	int beer;
} burgers_and_beer;

burgers_and_beer compute_burgers_and_beer(int m, int n, int t);
burgers_and_beer initialize_bb(int t);

int main (int argc, const char *argv[])
{
	burgers_and_beer result;
	int m;
	int n;
	int t;

	while (scanf("%d %d %d", &m, &n, &t) != EOF)
	{
		result = compute_burgers_and_beer(m, n, t);
		printf("%d", result.burgers);
		if (result.beer != 0)
		{
			printf(" %d", result.beer);
		}
		printf("\n");
	}
	return 0;
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
		option_m.burgers ++;
	}


	if (t - n >= 0)
	{
		option_n = compute_burgers_and_beer(m, n, t-n);
		option_n.burgers ++;
	}

	if (option_n.beer != option_m.beer)
	{
		if (option_n.beer < option_m.beer)
		{
			return option_n;
		}
		else
		{
			return option_m;
		}
	}
	else
	{
		if (option_n.burgers < option_m.burgers)
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