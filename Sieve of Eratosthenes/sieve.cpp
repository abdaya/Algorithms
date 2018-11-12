/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Mathew Seedhom
 * Date        : 9/17/2018
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
	//Constructor that initializes a list of boolean trues, and sieves.
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
    	for(int i = 2; i <= limit; i++){
    		is_prime_[i] = true;
    	}
        sieve();
        num_primes_ = count_num_primes();
    }
    //Frees up the stack
    ~PrimesSieve() {
        delete [] is_prime_;
    }
    //Method that returns that total number of primes up to a limit.
    inline int num_primes() const {
        return num_primes_;
    }
    //Displays all the primes in an organized manner
    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
    	const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    	int prow = 0;
    	cout << endl <<"Number of primes found: " << num_primes() <<endl;
    	cout << "Primes up to " << limit_ <<":"<<endl;
    	if (max_prime_width*num_primes() <= 80){
    		for (int i = 2; i < max_prime_; i++){
    			if (is_prime_[i]){
    				cout << i << " ";
    			}
    		}
    	cout << max_prime_;
    	}
    	else{
    		for (int i = 2; i < max_prime_; i++){
    			if (is_prime_[i] and prow == primes_per_row-1){
					cout << setw(max_prime_width) << i << endl;
					prow=0;
    			}
    			else{
    				if (is_prime_[i]){
    					prow++;
    					cout << setw(max_prime_width) << i<< " " ;
    				}
				}
    		}
    		cout << max_prime_;
    	}

    }

private:
    //Private Variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    //Counts the total number of primes in the list
    int count_num_primes(){
        // TODO: write code to count the number of primes found
    	int sum = 0;
    	for (int i=2; i<=limit_+1; i++){
    		if (is_prime_[i]){
    			max_prime_=i;
    			sum++;
    		}
    	}
    	return sum;
    }

    //Counts the total number of digits a number has
    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
    	int tot = 0;
    	while (num !=0){
    		num = num/10;
    		tot++;
    	}
    	return tot;
    }

    //Turns all composite numbers to a boolean false.
    void sieve() {
        // TODO: write sieve algorithm
    	for (int i = 2; i <= sqrt(limit_); i++){
    		if (is_prime_[i]){
    			int j=pow(i,2);
    			while (j <= limit_){
    				is_prime_[j] = false;
    				j = j+i;
    			}
    		}
    	}
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve(limit).display_primes();
    return 0;
}
