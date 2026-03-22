/*
 * DV2 - 5DV204
 * Spring 2026
 * OU4 Algoritmiskt tänkande
 *
 * File:         memoisering.c
 * Description:  A solution of the problem UVA - 10465 - Homer Simpson, using memoization
 * Author:       Hanna Sjöström - ens24ham
				 Rebecca Burström - ens24rbm
 * Date:         22/03-2026
 * Input:        An amount of test cases on the format "m n t\n" terminated by EOF, with m being the amount of time it takes to
 *               eat a Krusty-burger, n being the amount of time it takes to eat a Kwik-e-Mart burger and t being the time
 *               allocated to eat the burgers
 * Output:       Prints the ideal amount of burgers that can be eaten and the neccesary remaining beer time for each test case
*/

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

/* Description: Computes the ideal amount of burgers that can be eaten in t minutes 
 * if the time taken to eat the burgers is m and n
 * Input: The time it takes to eat a Krusty-burger, the time it takes to eat a Kwik-e-Mart-burger 
 * and the time alloted for eating burgers in minutes
 * Output: Returns the ideal amount of burgers and remaining beer time.
 */
burgers_and_beer compute_burgers_and_beer(int m, int n, int t, burgers_and_beer *results)
{
	burgers_and_beer option_m = initialize_bb(t);
	burgers_and_beer option_n = option_m;

	if (t == 0)
	{
		//0 burgers and t beer time is set as result and returned, since no burgers can be eaten
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

/* Description: Returns an burger_and_beer structure in which the amount of burgers is set to 0 and time set to t
 * Input: The time which is to be inserted as beer time in the struct.
 * Output: Returns the created and initialized struct.
 */
burgers_and_beer initialize_bb(int t)
{
	burgers_and_beer bb;
	bb.burgers = 0;
	bb.beer = t;
	return bb;
}

/* Description: Sets the given option as the result in the given array at index t
 * Input: The result array in which the option is to be set as result, the option and the index
 * Output: An array in which the result has been set at index t
 */
void put_result_in_array(burgers_and_beer *results, burgers_and_beer option, int t)
{
	results[t].burgers = option.burgers;
	results[t].beer = option.beer;
}