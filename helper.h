//======================================================================================
// hepler.h
//======================================================================================

#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <sys/time.h>

extern int arity;		// Arity of the function (Global)
extern double func[2][2][2];		// Global declaration of the function

extern int count;			// How many partitions of interval [0,1] (Global)

/* Computes func(x) */
double f(int *x);

/* Check whether particular input vectors x and y satisfy the condition */
bool check_condition(int *x, int *y);

/* Check whether the global function 'func' satisfies the given conditon
   for all values of x and y or not.
   Needs to be modified for functions of arity other than 3.*/
bool check_function();

/* Returns false only when function of arity 3 satisfies, but that of arity 2 does not,
   otherwise returns true.*/
bool check_function_2();

// Tries to find a counter example that does bot satisfy the specified 
// condition.
void find_a_function();

#endif	//HELPER_H