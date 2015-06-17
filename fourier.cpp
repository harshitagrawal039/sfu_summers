//=======================================================================
// fourier.cpp
// checks if the specified condition preserves also
// for summation over f.
//=======================================================================

#include "helper.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>

using namespace std;

extern int arity;

double alpha, beta;	// Global variables alpha, beta
bool flag_for_single_fn = false;
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

// Checks whether the specified condition is satisfied for function fn
// for given value of vextor x.
bool check_sec_condition(void* fn, int* x)
{
	if (f(fn,x)>=0){
		return true;
	}
	else{
		return false;
	}
}

// Checks whether f.t.[(fn(x)^alpha)(fn(x_bar)^beta)] >=0
// for all possible values of vector x
bool check_sec_function(void* fn, bool (*bool_f)(void*, int*))
{
	//bool flag = true;
	int x[arity];
	if(arity == 1){
		double *fun = (double *)fn;
		double fun2[2];
		for(int x0=0; x0<2; x0++){
			fun2[x0] = pow(fun[x0], alpha)*pow(fun[not(x0)], beta);
		}
		double f_t[2];
		fourier_transform_2((void *)fun2, (void *)f_t);
		int x0;
		for (x0=0; x0<2; x0++){
			x[0] = x0;
			if ((*bool_f)((void *)f_t, x) == false){
				return false;
			}
		}
		return true;
	}

	else if(arity == 2){
		double (*fun)[2] = (double(*)[2])fn;
		double fun2[2][2];
		for(int x0=0; x0<2; x0++){
			for(int x1=0; x1<2; x1++){
				fun2[x0][x1] = pow(fun[x0][x1], alpha)*pow(fun[not(x0)][not(x1)], beta);
			}
		}
		double f_t[2][2];
		fourier_transform_2((void *)fun2, (void *)f_t);
		// cout<<f_t[0][0]<<"  "<<f_t[0][1]<<endl;
		// cout<<f_t[1][0]<<"  "<<f_t[1][1]<<endl;
		int x0,x1;
		for (x0=0; x0<2; x0++){
			x[0] = x0;
			for(x1=0; x1<2; x1++){
				x[1] = x1;
				if ((*bool_f)((void *)f_t, x) == false){
					return false;
				}
			}
		}
		return true;
	}

	else if(arity == 3){
		double (*fun)[2][2] = (double(*)[2][2])fn;
		double fun2[2][2][2];
		for(int x0=0; x0<2; x0++){
			for(int x1=0; x1<2; x1++){
					for(int x2=0; x2<2; x2++){
						fun2[x0][x1][x2] = pow(fun[x0][x1][x2], alpha)*pow(fun[not(x0)][not(x1)][not(x2)], beta);
					}
			}
		}
		double f_t[2][2][2];
		fourier_transform_2((void *)fun2, (void *)f_t);
		int x0,x1,x2;
		for (x0=0; x0<2; x0++){
			x[0] = x0;
			for(x1=0; x1<2; x1++){
				x[1] = x1;
				for(x2=0; x2<2; x2++){
					x[2] = x2;
					if ((*bool_f)((void *)f_t, x) == false){
						return false;
					}
				}
			}
		}
		// cout <<"Atleast some single fn satisfies!" << endl;
		// double (*fun)[2][2] = (double(*)[2][2])fn;
		// cout <<"f:" << endl;
		// cout <<"    "<< fun[0][0][0] <<"\t"<< fun[0][1][0] <<endl;
		// cout <<"    "<< fun[0][0][1] <<"\t"<< fun[0][1][1] <<endl;
		// cout <<"    "<< fun[1][0][0] <<"\t"<< fun[1][1][0] <<endl;
		// cout <<"    "<< fun[1][0][1] <<"\t"<< fun[1][1][1] <<endl << endl;
		// cout <<"f_t" << endl;
		// cout <<"    "<< f_t[0][0][0] <<"\t"<< f_t[0][1][0] <<endl;
		// cout <<"    "<< f_t[0][0][1] <<"\t"<< f_t[0][1][1] <<endl;
		// cout <<"    "<< f_t[1][0][0] <<"\t"<< f_t[1][1][0] <<endl;
		// cout <<"    "<< f_t[1][0][1] <<"\t"<< f_t[1][1][1] <<endl << endl;
		flag_for_single_fn = true;
		return true;
	}
}

/* Returns false only when function of arity 3 satisfies, but that of arity 2(i.e.
   after summation) does not, otherwise returns true.*/
bool check_sec_function_2(void* fn, bool (*bool_f)(void*, int*))
{
	// If function satisfies the condition, then check the condition for summation
	if (check_sec_function(fn, bool_f)){
		double new_f[2][2];
		double (*my_f)[2][2] = (double (*)[2][2]) fn;
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j< 2; ++j)
			{
				new_f[i][j] = my_f[i][j][0] + my_f[i][j][1];
			}
		}
		// if( (func[0][0][0]+func[0][0][1])*(func[0][0][0]+func[0][0][1])*(func[0][0][0]+func[0][0][1])*(func[1][1][0]+func[1][1][1]) 
		// 	< (func[1][0][0]+func[1][0][1])*(func[1][0][0]+func[1][0][1])*(func[0][1][0]+func[0][1][1])*(func[0][1][0]+func[0][1][1])){
		// 	return false;
		// }
		arity = 2;		// change global arity
		if (check_sec_function((void *)new_f, bool_f)== false){
			arity = 3;
			return false;
		}
	}
	arity = 3;		// restore global arity
	return true;
}

// Tries to find a counter example that does not satisfy the specified 
// condition(only for arity 3)
void find_a_sec_function(void* fn, bool (*bool_f)(void*, int*))
{
	int i0, i1, i2, i3, i4, i5, i6, i7;
	bool flag = false;
	double (*fun)[2][2] = (double (*)[2][2]) fn;
	for (i0 = 0; i0 < count; i0++){
		fun[0][0][0] = (i0+0.5)/count;
		for (i1 = 0; i1 < count; i1++){
			fun[0][0][1] = (i1+0.5)/count;
			for (i2 = 0; i2 < count; i2++){
				fun[0][1][0] = (i2+0.5)/count;
				for (i3 = 0; i3 < count; i3++){
					fun[0][1][1] = (i3+0.5)/count;
					for (i4 = 0; i4 < count; i4++){
						fun[1][0][0] = (i4+0.5)/count;
						for (i5 = 0; i5 < count; i5++){
							fun[1][0][1] = (i5+0.5)/count;
							for (i6 = 0; i6 < count; i6++){
								fun[1][1][0] = (i6+0.5)/count;
								for (i7 = 0; i7 < count; i7++){
									fun[1][1][1] = (i7+0.5)/count;

									/* We have a new function now, check whether it satisfies or not.*/
									// only print those who are counter examples
									if (check_sec_function_2(fn, bool_f)== false) {
										flag = true;
										cout <<"f:     ( does not satisfy)" << endl;
										cout <<"    "<< fun[0][0][0] <<"\t"<< fun[0][1][0] <<endl;
										cout <<"    "<< fun[0][0][1] <<"\t"<< fun[0][1][1] <<endl;
										cout <<"    "<< fun[1][0][0] <<"\t"<< fun[1][1][0] <<endl;
										cout <<"    "<< fun[1][0][1] <<"\t"<< fun[1][1][1] <<endl << endl;
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
	cout << "Choose your alpha and beta:" << endl;
	cin >> alpha;
	cin >> beta;
	cout << "Enter the number of partitions in which you want to divide the interval [0,1]:"<<endl;
	cin >> count;

	struct timeval tp_start, tp_end;

	double func[2][2][2];
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

    find_a_sec_function((void *)func, &check_sec_condition);

	// cout <<"f_t:"<<endl;
	// cout <<"    "<< f_t[0][0][0] <<"\t"<< f_t[0][1][0] <<endl;
	// cout <<"    "<< f_t[0][0][1] <<"\t"<< f_t[0][1][1] <<endl << endl;
	// cout <<"    "<< f_t[1][0][0] <<"\t"<< f_t[1][1][0] <<endl;
	// cout <<"    "<< f_t[1][0][1] <<"\t"<< f_t[1][1][1] <<endl << endl;
    if(flag_for_single_fn){
    	cout <<"Atleast some single fn satisfies."<<endl;
    }
    else{
    	cout <<"Not even a single fn satisfies."<<endl;
    }

 //    double my_f[2][2];
 //    my_f[0][0] = 0.8; my_f[0][1] = 0.4;
 //    my_f[1][0] = 0.4; my_f[1][1] = 0.6;

 //    //double func[2][2][2], f_t[2][2][2];
	// func[0][0][0] = 0.525;	func[0][1][0] = 0.025;
	// func[0][0][1] = 0.025;	func[0][1][1] = 0.025;

	// func[1][0][0] = 0.025;	func[1][1][0] = 0.075;
	// func[1][0][1] = 0.025;	func[1][1][1] = 0.075;



 //    if(check_sec_function_2((void *)func, &check_sec_condition)){
 //    	cout<<"True"<<endl;
 //    }
 //    else{
 //    	cout<<"False"<<endl;
 //    }

    // arity = 2;
    // int x[2], y[2];
    // x[0] = 0; x[1] = 0;
    // y[0] = 0; y[1] = 1;
    // if(check_sec_condition((void *)my_f,x,y ))
    // 	cout<<"Hello"<<endl;
    // else
    // 	cout<<"Hi"<<endl;

	gettimeofday(&tp_end, NULL);
	//printf("Total time: %lld microseconds\n", tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec));
    cout << "Total time: "<< tp_end.tv_sec*1000000+tp_end.tv_usec - (tp_start.tv_sec*1000000+tp_start.tv_usec) <<" microseconds"<< endl;

	return 0;
}