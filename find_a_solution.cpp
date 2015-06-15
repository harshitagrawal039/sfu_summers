//===========================================================================================
// Tries to find a counter example that does bot satisfy the specified 
// condition.
//===========================================================================================

#include <iostream>
#include <sys/time.h>
#include "helper.h"

using namespace std;

/* Check whether particular input vectors x and y satisfy the condition */
bool check_condition(void* fn, int *x, int *y)
{
	// Specify the main condition here
	int x_and_y[arity];
	int x_or_y[arity];

	//void * fn = (void *) func;
	for (int i = 0; i < arity; i++)
	{
		x_and_y[i] = x[i] and y[i];
		x_or_y[i] = x[i] or y[i];
	}

	if (f(fn,x)*f(fn,x)*f(fn,y)*f(fn,y) <= f(fn,x_and_y)*f(fn,x_and_y)*f(fn,x_and_y)*f(fn,x_or_y)){		// Main condition

		return true;
	}
	else {
		return false;
	}
	return false;

}


int main(int argc, char const *argv[])
{
	cout << "Enter the number of partitions in which you want to divide the interval [0,1]:"<<endl;
	cin >> count;
	struct timeval tp_start, tp_end;
	// /* Input the function */
	// func[0][0][0] = 3;	func[0][1][0] = 1;
	// func[0][0][1] = 1;	func[0][1][1] = 1;

	// func[1][0][0] = 1;	func[1][1][0] = 1;
	// func[1][0][1] = 1;	func[1][1][1] = 0;

	// cout <<"f:"<<endl;
	// cout <<"    "<< func[0][0][0] <<"\t"<< func[0][1][0] <<endl;
	// cout <<"    "<< func[0][0][1] <<"\t"<< func[0][1][1] <<endl << endl;
	// cout <<"    "<< func[1][0][0] <<"\t"<< func[1][1][0] <<endl;
	// cout <<"    "<< func[1][0][1] <<"\t"<< func[1][1][1] <<endl << endl;

	gettimeofday(&tp_start, NULL);

	// cout << check_function() <<endl;

	find_a_function((void *)func, &check_condition);
	
	gettimeofday(&tp_end, NULL);
	//printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
    cout << "Total time: "<< tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec) <<" microseconds"<< endl;

	return 0;
}
