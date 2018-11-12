/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Mathew Seedhom
 * Version     : 1.0
 * Date        : 11/4/2018
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);
/**
 * Counts the number of inversions in an array in theta(n^2) time.
 *
 */
long count_inversions_slow(int array[], int length) {
	/*
	 * Loops through an array and checks for the number inversions in a slow manner.
	 */
    long count = 0;
	for (int i = 0; i<length-1; i++){
		for (int j = i + 1; j < length; j++){
			if (array[i] > array[j]){
				count++;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	/*
	 * Uses mergesort to count the number of inversions in a quick manner
	 */
	if (length == 1){
		return 0;
	}
	int* scratch = new int[length];
	long inversions = mergesort(array, scratch, 0, length - 1);
	delete [] scratch;
	return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	/*
	 * mergesorts the array while also counting the number of inversions
	 */
	long count = 0;
	if (low < high){
		int mid = low + (high-low)/2;
		int upper = mid+1;
		int lower = low;
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid+1, high);
		for (int k = low; k <= high; k++){
			if (lower <= mid && (upper > high || array[lower]<= array[upper])){
				scratch[k] = array[lower];
				lower++;
			}else{
				scratch[k] = array[upper];
				count += (mid - lower + 1);
				upper++;
			}
		}
		for (int k = low; k <= high; k++){
			array[k] = scratch[k];
		}
	}
	return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	if (argc > 1){
		if (argc > 2){
			cerr << "Usage: ./inversioncounter [slow]";
			return 1;
		}
		if (strcmp(argv[1], "slow") != 0){
			cerr << "Error: Unrecognized option '" << argv[1] << "'.";
			return 1;
		}
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;
	istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

	if (values.empty()){
		cerr << "Error: Sequence of integers not received.";
		return 1;
	}
    if (argc == 2){
		cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size());
	}else{
		cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size());
	}
    return 0;
}
