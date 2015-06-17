//=======================================================================
// fourier2.cpp
// checks whether condition f_t(x)<=pow(f_t(y),alpha) whenever x<=y preserves also
// for multiplication on f and g.
// (now only for arity 2)
//=======================================================================

#include "helper.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>

using namespace std;

extern int arity;
double alpha;		//Global variable alpha
bool a_fn_flag = false;

//double f_t[2][2][2];	/*fourier transform (Global)*/

/* Returns true if (vector x <= vector y) */
bool less_than(int* x, int* y)
{
	int i;
	for(i=0; i<arity; i++){
		if(x[i] <= y[i])
			continue;
		else
			return false;
	}
	return true;
}

// Returns false when x <=y but f_t(x)> f_t(y)
bool check_sec_condition(void* fn, int* x, int* y)
{
	if (less_than(x,y)){
		if(f(fn,x) > pow(f(fn,y), alpha)){
			return false;
		}
	}
	return true;
}

/* Check whether the global function 'func' satisfies the given conditon
   for all values of x and y or not.
   Needs to be modified for functions of arity other than 3.*/
bool check_sec_function(void* fn, bool (*bool_f)(void*, int*, int*))
{
	//bool flag = true;
	int x[arity], y[arity];

	if(arity == 1){
		double f_t[2];
		fourier_transform_2(fn, (void *)f_t);
		int x0, y0;
		for (x0=0; x0<2; x0++){
			x[0] = x0;
			for (y0=0; y0<2; y0++){
				y[0] = y0;
				//cout << "here !!" << endl;
				if ((*bool_f)((void *)f_t, x, y) == false){
					return false;
				}
			}
		}
		return true;
	}

	else if(arity == 2){
		double f_t[2][2];
		fourier_transform_2(fn, (void *)f_t);
		int x1, x0, y1, y0;
		for (x0=0; x0<2; x0++){
			x[0] = x0;
			for (x1=0; x1<2; x1++){
				x[1] = x1;
				for (y0=0; y0<2; y0++){
					y[0] = y0;
					for (y1=0; y1<2; y1++){
						y[1] = y1;
						//cout << "here !!" << endl;
						if ((*bool_f)((void *)f_t, x, y) == false){
							return false;
						}
					}
				}
			}
		}
		return true;
	}

	else if(arity == 3){
		double f_t[2][2][2];
		fourier_transform_2(fn, (void *)f_t);
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
								if ((*bool_f)((void *)f_t, x, y) == false){
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


// Tries to find a counter example that does not satisfy the specified 
// condition(only for arity 2)
void find_two_functions(bool (*bool_f)(void*, int*, int*))
{
	int i0, i1, i2, i3, j0, j1, j2, j3;
	bool flag = false;
	double fun[2][2]; double fun2[2][2];
	for (i0 = 0; i0 < count; i0++){
		fun[0][0] = (i0+0.5)/count;
		for (i1 = 0; i1 < count; i1++){
			fun[0][1] = (i1+0.5)/count;
			for (i2 = 0; i2 < count; i2++){
				fun[1][0] = (i2+0.5)/count;
				for (i3 = 0; i3 < count; i3++){
					fun[1][1] = (i3+0.5)/count;
					/* Now we have a new fun[2][2], check if it satisfies or not */
					if(check_sec_function((void *) fun, bool_f)== true){
						a_fn_flag= true;
						//cout << "There is a function!" << endl;
						for (j0 = 0; j0 < count; j0++){
							fun2[0][0] = (j0+0.5)/count;
							for (j1 = 0; j1 < count; j1++){
								fun2[0][1] = (j1+0.5)/count;
								for (j2 = 0; j2 < count; j2++){
									fun2[1][0] = (j2+0.5)/count;
									for (j3 = 0; j3 < count; j3++){
										fun2[1][1] = (j3+0.5)/count;
										/* We have a new fun2[2][2] now, check whether it satisfies or not.*/
										if (check_sec_function((void *)fun2, bool_f)== true) {
											// Now check if product satisfies or not
											fun2[0][0] = fun[0][0]*fun2[0][0];
											fun2[0][1] = fun[0][1]*fun2[0][1];
											fun2[1][0] = fun[1][0]*fun2[1][0];
											fun2[1][1] = fun[1][1]*fun2[1][1];
											//cout << "I am here" << endl;
											if (check_sec_function((void *)fun2, bool_f)== false){
												flag = true;
												cout <<"f:     ( does not satisfy)" << endl;
												cout <<"    "<< fun2[0][0] <<"\t"<< fun2[0][1] <<endl;
												cout <<"    "<< fun2[1][0] <<"\t"<< fun2[1][1] <<endl<<endl;
												// cout <<"    "<< fun[1][0][0] <<"\t"<< fun[1][1][0] <<endl;
												// cout <<"    "<< fun[1][0][1] <<"\t"<< fun[1][1][1] <<endl << endl;
											}
										}
										
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (flag) {
		cout << "Atleast one does not satisfy"<<endl;
	}
	else{
		cout << "All combinations satisfy" << endl;
	}
}


int main(int argc, char const *argv[])
{
	cout << "Choose your alpha:"<< endl;
	cin >> alpha;
	cout << "Enter the number of partitions in which you want to divide the interval [0,1]:"<<endl;
	cin >> count;
	struct timeval tp_start, tp_end;

	arity = 2;
	/* Input the function */
	// func[0][0][0] = 0.9;	func[0][1][0] = 0.9;
	// func[0][0][1] = 0.3;	func[0][1][1] = 0.1;

	// func[1][0][0] = 0.3;	func[1][1][0] = 0.1;
	// func[1][0][1] = 0.3;	func[1][1][1] = 0.1;

	// cout <<"f:"<<endl;
	// cout <<"    "<< func[0][0][0] <<"\t"<< func[0][1][0] <<endl;
	// cout <<"    "<< func[0][0][1] <<"\t"<< func[0][1][1] <<endl << endl;
	// cout <<"    "<< func[1][0][0] <<"\t"<< func[1][1][0] <<endl;
	// cout <<"    "<< func[1][0][1] <<"\t"<< func[1][1][1] <<endl <<endl;

    // double f_t[2][2][2];	/*fourier trnsform*/

    gettimeofday(&tp_start, NULL);
	
	//double ***f_t = (double ***) fourier_transform((void *) func);
	//fourier_transform_2((void *)func, (void *)f_t);
    find_two_functions( &check_sec_condition);

    if(a_fn_flag)
    	cout<<"Atleast a single fn is there"<<endl;
    else
    	cout<<"Even a single fn is not there"<<endl;
	// cout <<"f_t:"<<endl;
	// cout <<"    "<< f_t[0][0][0] <<"\t"<< f_t[0][1][0] <<endl;
	// cout <<"    "<< f_t[0][0][1] <<"\t"<< f_t[0][1][1] <<endl << endl;
	// cout <<"    "<< f_t[1][0][0] <<"\t"<< f_t[1][1][0] <<endl;
	// cout <<"    "<< f_t[1][0][1] <<"\t"<< f_t[1][1][1] <<endl << endl;

	gettimeofday(&tp_end, NULL);
	//printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
    cout << "Total time: "<< tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec) <<" microseconds"<< endl;

	return 0;
}