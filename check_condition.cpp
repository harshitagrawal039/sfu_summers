//======================================================================
// Check whether a function satisfies a given condition or not.
// Has to be modified for the functions other than arity 3.
//======================================================================
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

int arity = 3;		// Arity of the function
double func[2][2][2];		// Global declaration of the function

/* Computes func(x) */
double f(int *x)
{
	void * result;
	if (arity==1){
		 result = (void *)(func + x[0]);
	}
	else if (arity==2){
		result = (void *)(*(func + x[0]) + x[1]);
	}
	else if (arity==3){
		result = (void *)(*(*(func + x[0]) + x[1]) + x[2]);
	}
	return *((double *)result);
}

/* Check whether particular input vectors x and y satisfy the condition */
bool check_condition(int *x, int *y)
{
	// Specify the main condition here
	int x_and_y[arity];
	int x_or_y[arity];

	for (int i = 0; i < arity; i++)
	{
		x_and_y[i] = x[i] and y[i];
		x_or_y[i] = x[i] or y[i];
	}

	if (f(x)*f(x)*f(y)*f(y) <= f(x_and_y)*f(x_and_y)*f(x_and_y)*f(x_or_y)){		// Main condition
		return true;
	}
	else {
		return false;
	}

}

/* Check whether the global function 'func' satisfies the given conditon
   for all values of x and y or not.
   Needs to be modified for functions of arity other than 3.*/
bool check_function()
{
	//bool flag = true;
	int x[arity], y[arity];

	if(arity == 3){
		int x1, x2, x0, y1, y2, y0;
		for (x0=0; x0<2; x0++){
			x[0] = x0;
			for (x1=0; x1<2; x1++){
				x[1] = x1;
				for (x2=0; x2<2; x2++){
					x[2] = x2;
					for (y0=0; y0<2; y0++){
						y[0] = y0;
						for (y1=0; y1<2; y1++){
							y[1] = y1;
							for (y2=0; y2<2; y2++){
								y[2] = y2;
								//cout << "here !!" << endl;
								if (check_condition(x, y) == false){
									return false;
								}
							}
						}
					}
				}
			}
		}
		return true;
	}
}

int main(int argc, char const *argv[])
{
	struct timeval tp_start, tp_end;

	/* Input the function */
	func[0][0][0] = 3;	func[0][1][0] = 1;
	func[0][0][1] = 1;	func[0][1][1] = 1;

	func[1][0][0] = 1;	func[1][1][0] = 1;
	func[1][0][1] = 1;	func[1][1][1] = 0;

	cout <<"f:"<<endl;
	cout <<"    "<< func[0][0][0] <<"\t"<< func[0][1][0] <<endl;
	cout <<"    "<< func[0][0][1] <<"\t"<< func[0][1][1] <<endl << endl;
	cout <<"    "<< func[1][0][0] <<"\t"<< func[1][1][0] <<endl;
	cout <<"    "<< func[1][0][1] <<"\t"<< func[1][1][1] <<endl << endl;

	gettimeofday(&tp_start, NULL);

	cout << check_function() <<endl;

	gettimeofday(&tp_end, NULL);
    //printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
    cout << "Total time: "<< tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec) <<" microseconds"<< endl;

	return 0;
}
