
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);

	t = TimeCode::ComponentsToSeconds(3, 17, 289);
	assert(t == 12109);
	
	t = TimeCode::ComponentsToSeconds(3, 62, 42);
	assert(t == 14562);
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	tc = TimeCode(3, 14, 25);
	assert(tc.ToString() == "3:14:25");

	cout << "Testing Reset" << endl;
	tc.reset();
	assert(tc.ToString() == "0:0:0");
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	tc = TimeCode(10, 6, 29);
	tc.GetComponents(h, m, s);
	assert(h == 10 && m == 6 && s == 29);
	
	cout << "PASSED!" << endl << endl;

	cout << "Testing Get functions" << endl;
	tc = TimeCode(15, 8, 45);
	assert(tc.GetHours() == 15);
	assert(tc.GetMinutes() == 8);
	assert(tc.GetSeconds() == 45);

	cout << "PASSED!" << endl << endl;
}


void TestOperators(){

	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}
	cout << "Testing Addition" << endl;
	tc1 = TimeCode(1, 0, 3);
	tc2 = TimeCode(0, 50, 48);
	tc3 = tc1 + tc2;
	assert(tc3.ToString()=="1:50:51");

	tc1 = TimeCode(1, 15, 17);
	tc2 = TimeCode(0, 50, 48);
	tc3 = tc1 + tc2;
	assert(tc3.ToString()=="2:6:5");

	cout << "Testing Multiplication" << endl;
	tc1 = TimeCode(1,30,0);
	tc2 = tc1 * 0.5;
	assert(tc2.ToString()=="0:45:0");

	
	tc1 = TimeCode(2,10,15);
	tc2 = tc1 * 2;
	assert(tc2.ToString()=="4:20:30");

	cout << "Testing Division" << endl;
	tc1 = TimeCode(6,18, 42);
	tc2 = tc1 / 6 ; 
	assert(tc2.ToString()== "1:3:7");
	cout << "PASSED!" << endl << endl;

	cout <<"Testing Comparison Operators" << endl;
	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(6, 18, 42);
	bool result = tc1 == tc2;
	assert(result == true);

	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(5, 30, 42);
	result = tc1 == tc2;
	assert(result == false);

	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(5, 30, 42);
	result = tc1 != tc2;
	assert(result == true);

	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(6, 18, 42);
	result = tc1 != tc2;
	assert(result == false);

	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(7, 20, 50);
	result = tc1 < tc2;
	assert(result == true);

	tc2 = TimeCode(6,18, 42);
	tc1 = TimeCode(7, 20, 50);
	result = tc1 < tc2;
	assert(result == false);

	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(6, 18, 42);
	result = tc1 <= tc2;
	assert(result == true);

	tc2 = TimeCode(6,18, 42);
	tc1 = TimeCode(7, 20, 50);
	result = tc1 > tc2;
	assert(result == true);

	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(7, 20, 50);
	result = tc1 > tc2;
	assert(result == false);

	tc1 = TimeCode(6,18, 42);
	tc2 = TimeCode(6, 18, 42);
	result = tc1 >= tc2;
	assert(result == true);

	cout << "PASSED!" << endl << endl;
}


void TestSet()
{
	cout << "Testing SetMinutes" << endl;
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");
	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{   }
	cout << "PASSED!" << endl << endl;

	cout << "Testing SetHours" << endl;
	tc = TimeCode(8, 5, 9);
	tc.SetHours(15); // test valid change
	assert(tc.ToString() == "15:5:9");
	
	cout << "PASSED!" << endl << endl;

	cout << "Testing SetSeconds" << endl;
	tc = TimeCode(8, 5, 9);
	tc.SetSeconds(15); // test valid change
	assert(tc.ToString() == "8:5:15");
	try
	{
		tc.SetSeconds(60);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{   }
	cout << "PASSED!" << endl << endl;
}




	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestOperators();
	TestSet();
	
	// Many othere test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	
	return 0;
}
