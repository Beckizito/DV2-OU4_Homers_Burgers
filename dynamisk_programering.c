#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct burgers_and_beer{
	int burgers; 
	int beer;
} burgers_and_beer;

burgers_and_beer compute_burgers_and_beer(int m, int n, int t);
burgers_and_beer initialize_bb(int t);
void put_result_in_array(burgers_and_beer *results, burgers_and_beer option, int t);

int main (int argc, const char *argv[])
{
	
	burgers_and_beer result;
	int m;
	int n ;
	int t ;

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
	burgers_and_beer results[t+1];
	int i = 0;
	while (i <= t)
	{
		results[i] = initialize_bb(-1);
		i++;
	}
	i = 0;
	while (i <= t)
	{
		burgers_and_beer option_m = initialize_bb(i);
		burgers_and_beer option_n = option_m;

		if (i == 0)
		{
			put_result_in_array(results, option_m, i);
		}
		if (i - m >= 0)
		{
			if (results[i-m].beer != -1)
			{
				option_m = results[i-m];
				option_m.burgers ++;
			}
		}

		if (i - n >= 0)
		{
			if (results[i-n].beer != -1)
			{
				option_n = results[i-n];
				option_n.burgers ++;
			}
		}

		if (option_n.beer != option_m.beer)
		{
			if (option_n.beer < option_m.beer)
			{
				put_result_in_array(results, option_n, i);
			}
			else
			{
				put_result_in_array(results, option_m, i);
			}
		}
		else
		{
			if (option_n.burgers < option_m.burgers)
			{
				put_result_in_array(results, option_m, i);
			}
			else
			{
				put_result_in_array(results, option_n, i);
			}
		}
		i++;
	}
	i = 0;
	return results[t];
}

burgers_and_beer initialize_bb(int t)
{
	burgers_and_beer bb;
	bb.burgers = 0;
	bb.beer = t;
	return bb;
}

void set_result(burgers_and_beer *results, burgers_and_beer option, int t)
{
	results[t].burgers = option.burgers;
	results[t].beer = option.beer;
}