//======================================================================
// Check whether a function satisfies a given condition or not.
// Has to be modified for the functions other than arity 3.
//======================================================================
#include <iostream>
#include <sys/time.h>
#include "helper.h"

using namespace std;

int main(int argc, char const *argv[])
{
	struct timeval tp_start, tp_end;

	/* Input the function */
	func[0][0][0] = 0.9;	func[0][1][0] = 0.9;
	func[0][0][1] = 0.3;	func[0][1][1] = 0.1;

	func[1][0][0] = 0.3;	func[1][1][0] = 0.1;
	func[1][0][1] = 0.3;	func[1][1][1] = 0.1;

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
