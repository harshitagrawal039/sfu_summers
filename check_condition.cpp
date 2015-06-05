#include<iostream>
#include<stdlib.h>

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
	func[0][0][0] = 0;	func[0][1][0] = 1;
	func[0][0][1] = 1;	func[0][1][1] = 1;

	func[1][0][0] = 1;	func[1][1][0] = 1;
	func[1][0][1] = 1;	func[1][1][1] = 1;

	cout <<"f:"<<endl;
	cout <<"    "<< func[0][0][0] <<"\t"<< func[0][1][0] <<endl;
	cout <<"    "<< func[0][0][1] <<"\t"<< func[0][1][1] <<endl << endl;
	cout <<"    "<< func[1][0][0] <<"\t"<< func[1][1][0] <<endl;
	cout <<"    "<< func[1][0][1] <<"\t"<< func[1][1][1] <<endl << endl;

	cout << check_function() <<endl;

	return 0;
}