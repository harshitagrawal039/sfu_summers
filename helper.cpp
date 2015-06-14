//========================================================================
// helper.cpp
// contains the functions and global variables to be used by other programs
//========================================================================

#include <iostream>
#include "helper.h"
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

int arity = 3;		// Arity of the function (Global)
double func[2][2][2];		// Global declaration of the function

int count;			// How many partitions of interval [0,1] (Global)

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
	return false;

}

/* Check whether the global function 'func' satisfies the given conditon
   for all values of x and y or not.
   Needs to be modified for functions of arity other than 3.*/
bool check_function(bool (*bool_f)(int*, int*))
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
								if ((*bool_f)(x, y) == false){
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

/* Returns false only when function of arity 3 satisfies, but that of arity 2 does not,
   otherwise returns true.*/
bool check_function_2()
{
	// If function satisfies the condition, then check the condition for summation
	if (check_function(&check_condition)){
		if( (func[0][0][0]+func[0][0][1])*(func[0][0][0]+func[0][0][1])*(func[0][0][0]+func[0][0][1])*(func[1][1][0]+func[1][1][1]) 
			< (func[1][0][0]+func[1][0][1])*(func[1][0][0]+func[1][0][1])*(func[0][1][0]+func[0][1][1])*(func[0][1][0]+func[0][1][1])){
			return false;
		}
	}
	return true;
}

// Tries to find a counter example that does bot satisfy the specified 
// condition.
void find_a_function()
{
	int i0, i1, i2, i3, i4, i5, i6, i7;
	bool flag = false;
	for (i0 = 0; i0 < count; i0++){
		func[0][0][0] = (i0+0.5)/count;
		for (i1 = 0; i1 < count; i1++){
			func[0][0][1] = (i1+0.5)/count;
			for (i2 = 0; i2 < count; i2++){
				func[0][1][0] = (i2+0.5)/count;
				for (i3 = 0; i3 < count; i3++){
					func[0][1][1] = (i3+0.5)/count;
					for (i4 = 0; i4 < count; i4++){
						func[1][0][0] = (i4+0.5)/count;
						for (i5 = 0; i5 < count; i5++){
							func[1][0][1] = (i5+0.5)/count;
							for (i6 = 0; i6 < count; i6++){
								func[1][1][0] = (i6+0.5)/count;
								for (i7 = 0; i7 < count; i7++){
									func[1][1][1] = (i7+0.5)/count;

									/* We have a new function now, check whether it satisfies or not.*/
									// only print those who are counter examples
									if (check_function_2()== false) {
										flag = true;
										cout <<"f:     ( does not satisfy)" << endl;
										cout <<"    "<< func[0][0][0] <<"\t"<< func[0][1][0] <<endl;
										cout <<"    "<< func[0][0][1] <<"\t"<< func[0][1][1] <<endl;
										cout <<"    "<< func[1][0][0] <<"\t"<< func[1][1][0] <<endl;
										cout <<"    "<< func[1][0][1] <<"\t"<< func[1][1][1] <<endl << endl;
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

//======================================================================
// function sign returns (-1)^(num_of_1s)
//======================================================================
int sign(int num_of_1s){
	if (num_of_1s%2==0)
		return 1;
	else
		return -1;
}

//========================================================================
// Computes the fourier transform of the given function and returns
// a pointer to the newly made fourier transform
//========================================================================
void * fourier_transform(void * g)
{
	if (arity == 2){
		//double** old_f = (double **) g;
		double (*old_f)[2] = (double(*)[2]) g;
		double** new_f = (double **) calloc(2,sizeof(double *));
		for (int i = 0; i < 2; ++i)
		{
			new_f[i] = (double *) calloc(2,sizeof(double));
		}

		int i0,i1,j0,j1,num_of_1s;
		double sum;
		for(i0=0; i0<2 ;i0++){
			for(i1=0; i1<2 ;i1++){
				sum = 0; num_of_1s = 0;
				for(j0=0; j0<2 ;j0++){
					for(j1=0; j1<2 ;j1++){
						num_of_1s = i0*j0 + i1*j1;
						sum = sum + sign(num_of_1s)*old_f[j0][j1];
					}
				}
				new_f[i0][i1] = sum;
			}
		}
		return (void *) new_f;
	}

	else if (arity == 3){
		//double*** old_f = (double ***) g;
		double(*old_f)[2][2] = (double(*)[2][2]) g;
		double*** new_f = (double ***) calloc(2,sizeof(double **));

		for (int i = 0; i < 2; ++i)
		{
			new_f[i] = (double **) calloc(2,sizeof(double *));
			for (int j = 0; j < 2; ++j)
			{
				new_f[i][j] = (double *) calloc(2,sizeof(double));
			}
		}

		int i0,i1,i2,j0,j1,j2,num_of_1s;
		double sum;
		for(i0=0; i0<2 ;i0++){
			for(i1=0; i1<2 ;i1++){
				for(i2=0; i2<2; i2++){
					sum = 0; num_of_1s = 0;
					for(j0=0; j0<2 ;j0++){
						for(j1=0; j1<2 ;j1++){
							for(j2=0; j2<2; j2++){
								num_of_1s = i0*j0 + i1*j1 + i2*j2;
								sum = sum + sign(num_of_1s)*old_f[j0][j1][j2];
							}
						}
					}
					new_f[i0][i1][i2] = sum;
				}
			}
		}
		return (void *) new_f;
	}
}

//========================================================================
// Computes the fourier transform of the given function, but does not
// create a new memory, makes changes in place.
//========================================================================
void fourier_transform_2(void *my_f, void *my_f_t)
{
	if (arity==2){
		double(*old_f)[2] = (double(*)[2]) my_f;
		double(*new_f)[2] = (double(*)[2]) my_f_t;

		int i0,i1,j0,j1,num_of_1s;
		double sum;
		for(i0=0; i0<2 ;i0++){
			for(i1=0; i1<2 ;i1++){
				sum = 0; num_of_1s = 0;
				for(j0=0; j0<2 ;j0++){
					for(j1=0; j1<2 ;j1++){
						num_of_1s = i0*j0 + i1*j1;
						sum = sum + sign(num_of_1s)*old_f[j0][j1];
					}
				}
				new_f[i0][i1] = sum;
			}
		}
	}

	else if (arity==3){
		double(*old_f)[2][2] = (double(*)[2][2]) my_f;
		double(*new_f)[2][2] = (double(*)[2][2]) my_f_t;

		int i0,i1,i2,j0,j1,j2,num_of_1s;
		double sum;
		for(i0=0; i0<2 ;i0++){
			for(i1=0; i1<2 ;i1++){
				for(i2=0; i2<2; i2++){
					sum = 0; num_of_1s = 0;
					for(j0=0; j0<2 ;j0++){
						for(j1=0; j1<2 ;j1++){
							for(j2=0; j2<2; j2++){
								num_of_1s = i0*j0 + i1*j1 + i2*j2;
								sum = sum + sign(num_of_1s)*old_f[j0][j1][j2];
							}
						}
					}
					new_f[i0][i1][i2] = sum;
				}
			}
		}
	}
}
