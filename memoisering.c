#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct burgers_and_beer{
	int burgers; 
	int beer;
} burgers_and_beer;

burgers_and_beer compute_burgers_and_beer(int m, int n, int t, burgers_and_beer *results);
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
		burgers_and_beer *results = malloc((t+1) * sizeof(burgers_and_beer));
		int i = 0;
		while (i <= t)
		{
			results[i] = initialize_bb(-1);
			i++;
		}
		result = compute_burgers_and_beer(m, n, t, results);
		printf("%d", result.burgers);
		if (result.beer != 0)
		{
			printf(" %d", result.beer);
		}
		printf("\n");
		free(results);
	}
	return 0;
}

burgers_and_beer compute_burgers_and_beer(int m, int n, int t, burgers_and_beer *results)
{
	burgers_and_beer option_m = initialize_bb(t);
	burgers_and_beer option_n = option_m;

	if (t == 0)
	{
		put_result_in_array(results, option_m, t);
		return option_m;
	}
	
	if (t - m >= 0)
	{
		if (results[t-m].beer != -1)
		{
			option_m = results[t-m];
		}
		else
		{
			option_m = compute_burgers_and_beer(m, n, t-m, results);
		}
		option_m.burgers ++;
	}


	if (t - n >= 0)
	{
		if (results[t-n].beer != -1)
		{
			option_n = results[t-n];
		}
		else
		{
			option_n = compute_burgers_and_beer(m, n, t-n, results);
		}
		option_n.burgers ++;
	}

	if (option_n.beer != option_m.beer)
	{
		if (option_n.beer < option_m.beer)
		{
			put_result_in_array(results, option_n, t);
			return option_n;
		}
		else
		{
			put_result_in_array(results, option_m, t);
			return option_m;
		}
	}
	else
	{
		if (option_n.burgers < option_m.burgers)
		{
			put_result_in_array(results, option_m, t);
			return option_m;
		}
		else
		{
			put_result_in_array(results, option_n, t);
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

void put_result_in_array(burgers_and_beer *results, burgers_and_beer option, int t)
{
	results[t].burgers = option.burgers;
	results[t].beer = option.beer;
}