/*
 * This program helps solve the following problem:
 * You have 40 bowls, all placed in a line at exact intervals of 1 meter.
 * You also have 9 oranges. You wish to place all the oranges in the bowls,
 * no more than one orange in each bowl, so that there are no three oranges
 * A, B, and C such that the distance between A and B is equal to the distance
 * between B and C.
 * How many ways can you arrange the oranges in the bowls?
 *
 * This problem is from bittorrents.com's developer challenge.
 *
 * main.cpp
 *
 *  Created on: May 26, 2011
 *      Author: sadanjon
 */

#include <sys/time.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

/**
 * globals.
 * It is a small utility program so what the heck?
 */
int g_num_bowls;
int g_num_oranges;
bool *g_bowls;
bool **g_bowls_p;
bool *g_bowls_end;

int g_solutions = 0;

/**
 * the calculator of the program.
 * Works in a backtracking/recursive fashion, as it iterates across
 * all the possible arrangements.
 *
 * @param where a pointer to the start of the bowl array
 * @param orange the current orange "ID". Should be set to 0.
 */
void pick_recursive(bool *where, int orange);

/**
 * Prints the bowls array. (for debugging)
 */
void print_bowls();

int main(int argc, char **argv) {
	// get arguments
	if (argc != 3) {
		printf("usage: main <number of bowls> <number of oranges>\n");
		return 1;
	}
	g_num_bowls = atoi(argv[1]);
	g_num_oranges = atoi(argv[2]);

	if (g_num_bowls <= 0 || g_num_oranges >= g_num_bowls) {
		printf("error: illegal arguments.\nMake sure: 0 < oranges < bowls\n");
		return 1;
	}

	// set globals
	g_bowls = new bool[g_num_bowls];
	g_bowls_p = new bool*[g_num_oranges];
	g_bowls_end = g_bowls + g_num_bowls;
	memset(g_bowls, false, g_num_bowls * sizeof(bool));
	memset(g_bowls_p, 0, g_num_oranges * sizeof(bool*));

	// start cooking
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	pick_recursive(g_bowls, 0);
	gettimeofday(&tv2, NULL);

	// calculate time
	double utime_diff = tv2.tv_usec - tv1.tv_usec;
	double time_diff = tv2.tv_sec - tv1.tv_sec + utime_diff / 1000000;

	// print results
	printf("solutions: %d\n", g_solutions);
	printf("time: %lf\n", time_diff);

	return 0;
}

void pick_recursive(bool *where, int orange) {
	if (where == g_bowls_end || orange == g_num_oranges) {
		if (orange == g_num_oranges) {
			++g_solutions;
			//print_bowls();
		}
		return;
	}

	for (bool *i = where; i < g_bowls_end; ++i) {
		if (g_bowls_end - i < g_num_oranges - orange) {
			return;
		}
		bool skip = false;

		for (int j = 0; j < orange; ++j) {
			for (int k = j + 1; k < orange; ++k) {
				if (i - g_bowls_p[k] == g_bowls_p[k] - g_bowls_p[j]) {
					skip = true;
					break;
				}
			}
			if (skip == true)
				break;
		}

		if (!skip) {
			*i = true;
			g_bowls_p[orange] = i;
			pick_recursive(i + 1, orange + 1);
			*i = false;
		}
	}

}

void print_bowls() {
	for (int i = 0; i < g_num_bowls; ++i) {
		if (g_bowls[i])
			printf("0 ");
		else
			printf("_ ");
	}
	printf("\n");
}

