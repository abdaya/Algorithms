/*******************************************************************************
* Name : gcd.cpp
* Author: Mathew Seedhom
* Date: 8/29/18
* Description: Calculate gcd iteratively and recursively
* Pledge: I pledge that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

int gcd_recursive(int m, int n){
	//Recursively calculates the gcd of two number
	n = abs(n);
	m = abs(m);
	if (n == 0){
		return m;
	}
	return gcd_recursive(n, m  % n);
}

int gcd_iterative(int m, int n){
	//Iteratively calculates the gcd of two number
	int r;
	n = abs(n);
	m = abs(m);
	while (n != 0){
		r = m%n;
		m = n;
		n = r;
	}
	return m;
}

int main(int argc, char *argv[]){
	int m = 0;
	int n = 0;
	if (argc != 3){
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	istringstream iss;
	iss.str(argv[1]);
	if ( !(iss >> m)){
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if ( !(iss >> n)){
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m, n) <<endl;
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m, n) <<endl;
}
