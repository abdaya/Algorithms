/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Mathew Seedhom
 * Date        : 10/02/18
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


vector< vector<int>> get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	// Returns a vector of vectors containing the different ways of climbing the stairs.
	vector<vector<int>> ways, result;
	vector<int> empty;
	if (num_stairs <= 0){
		ways.push_back(empty);
	} else {
		for (int i = 1; i<= 3; i++){
			if (num_stairs >= i){
				result = get_ways(num_stairs - i);
				for (unsigned int j=0; j < result.size(); j++){
					result[j].insert(result[j].begin(), i);
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

	// Creates a uniform display for the ways to climb stairs
	int max_width = ways.size();
	int count = 0;
	while (max_width != 0){
		max_width = max_width / 10;
		count ++;
	}
	if (ways[0].size()==1){
		cout << ways.size() << " way to climb " << ways[0].size()<< " stair." << endl;
	}else{
		cout << ways.size() << " ways to climb " << ways[0].size()<< " stairs." << endl;
	}
	for (unsigned int i = 0; i < ways.size(); i++){
		cout << setw(count) << i+1 << ". [";
		unsigned int j = 0;
		while (j< ways[i].size()-1){
			cout << ways[i][j] << ", ";
			j++;
		}
		cout << ways[i][j] << "]" << endl;
	}
}


int main(int argc, char * const argv[]) {
	int m;
	if (argc != 2){
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	istringstream iss(argv[1]);
	if (!(iss >> m) || atoi(argv[1])< 1){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	display_ways(get_ways(atoi(argv[1])));
	return 0;
}
