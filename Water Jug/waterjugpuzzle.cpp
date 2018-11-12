/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Mathew Seedhom
 * Date        : 10/19/18
 * Description : Gives a path to redistribute water from different jugs ti reach a desired state.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <queue>


using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

vector<string> min_ways(State goal, State initial, State cap){
	/*
	 * This is a function that returns the minimal path to get to a goal state
	 *
	 * Argument goal: The desired states of the water jugs
	 * Argument initial: The starting states of all the water jugs
	 * Argument cap: The capacity state of all the water jugs
	 */
	unordered_set<string> past = {};
	queue<State> priority;
	priority.push(initial);
	while (!priority.empty()){
		State check = priority.front();
		check.directions.push_back(check.to_string());
		if (check.to_string() == goal.to_string()){
			return check.directions;
		}else if (past.find(check.to_string())!=past.end()){
			priority.pop();
		}else{
			past.insert(check.to_string());
			if (check.a != cap.a){
				if (check.c !=0){
					State nextCA(0, 0, 0);
					if (cap.a - check.a >= check.c){
						nextCA.a=check.a+check.c;
						nextCA.b=check.b;
					}else{
						nextCA.a=cap.a;
						nextCA.b=check.b;
						nextCA.c=check.c-(cap.a-check.a);
					}
					nextCA.directions.insert(nextCA.directions.begin(), check.directions.begin(), check.directions.end());
					priority.push(nextCA);
				}
				if (check.b != 0){
					State nextBA(0, 0, 0);
						if (cap.a - check.a >= check.b){
							nextBA.a=check.a+check.b;
							nextBA.c=check.c;
						}else{
							nextBA.a=cap.a;
							nextBA.b=check.b-(cap.a-check.a);
							nextBA.c=check.c;
						}
						nextBA.directions.insert(nextBA.directions.begin(), check.directions.begin(), check.directions.end());
						priority.push(nextBA);
				}
			}
			if (check.b != cap.b){
				if (check.c != 0){
					State nextCB(0, 0, 0);
					if (cap.b - check.b >= check.c){
						nextCB.b=check.b+check.c;
						nextCB.a=check.a;
					}else{
						nextCB.b=cap.b;
						nextCB.c=check.c-(cap.b-check.b);
						nextCB.a=check.a;
					}
					nextCB.directions.insert(nextCB.directions.begin(), check.directions.begin(), check.directions.end());
					priority.push(nextCB);
				}
				if (check.a != 0){
					State nextAB(0, 0, 0);
					if (cap.b - check.b >= check.a){
						nextAB.b=check.b+check.a;
						nextAB.c=check.c;
					}else{
						nextAB.b=cap.b;
						nextAB.a=check.a-(cap.b-check.b);
						nextAB.c=check.c;
					}
					nextAB.directions.insert(nextAB.directions.begin(), check.directions.begin(), check.directions.end());
					priority.push(nextAB);
				}
			}
			if (check.c != cap.c){
				if (check.b != 0){
					State nextBC(0, 0, 0);
					if (cap.c - check.c >= check.b){
						nextBC.c=check.c+check.b;
						nextBC.a=check.a;
					}else{
						nextBC.c=cap.c;
						nextBC.a=check.a;
						nextBC.b=check.b-(cap.c-check.c);
					}
					nextBC.directions.insert(nextBC.directions.begin(), check.directions.begin(), check.directions.end());
					priority.push(nextBC);
				}
				if (check.a != 0){
					State nextAC(0, 0, 0);
					if (cap.c - check.c >= check.a){
						nextAC.c=check.c+check.a;
						nextAC.b=check.b;
					}else{
						nextAC.c=cap.c;
						nextAC.a=check.a-(cap.c-check.c);
						nextAC.b=check.b;
					}
					nextAC.directions.insert(nextAC.directions.begin(), check.directions.begin(), check.directions.end());
					priority.push(nextAC);
				}
			}
			priority.pop();
		}
	}
	vector<string> empty = {"nothing"};
	return empty;
}

vector<string> find_change(string first, string second){
	/*
	 * This is a function that returns a vector in the format of
	 * 		[Amount of displaced water, Jug water was taken from, Jug water was taken to]
	 * 	Argument first: The state of the water jugs before moving water.
	 * 	Argument second: The state of the water jugs after moving water.
	 */
	stringstream ss1;
	stringstream ss2;
	vector<int> firstVals;
	vector<int> secondVals;
	vector<string> change(3);
	firstVals.reserve(3);
	secondVals.reserve(3);
	ss1 << first;
	string temp;
	int found;
	while (!ss1.eof()) {
		ss1 >> temp;
		if (stringstream(temp) >> found)
		  firstVals.push_back(found);
	}
	ss2 << second;
	while (!ss2.eof()) {
		ss2 >> temp;
		if (stringstream(temp) >> found)
		  secondVals.push_back(found);
	}

	if (firstVals[0] - secondVals[0] < 0){
		change[0] = to_string(secondVals[0] - firstVals[0]);
		change[2] = "A";
	}
	if(firstVals[0] - secondVals[0] > 0){
		change[1] = "A";
	}
	if (firstVals[1] - secondVals[1] < 0){
		change[0] = to_string(secondVals[1] - firstVals[1]);
		change[2] = "B";
	}
	if(firstVals[1] - secondVals[1] > 0){
		change[1] = "B";
	}
	if (firstVals[2] - secondVals[2] < 0){
		change[0] = to_string(secondVals[2] - firstVals[2]);
		change[2] = "C";
	}
	if(firstVals[2] - secondVals[2] > 0){
		change[1] = "C";
	}
	return change;
}


void print_path(vector<string> path){
	/*
	 * This is a function that prints the distributions of water in a reable format
	 * Argument path: A vector of string that contains all states used to reach the goal state
	 */
	if (path[0] == "nothing"){
		cout << "No solution.";
	} else {
		cout << "Initial state. " << path[0] << endl;
		for (unsigned int i = 1; i < path.size(); i++){
			string before = path[i-1];
			string after = path[i];
			vector<string> change = find_change(before.substr(1, before.size()-1), after.substr(1, after.size()-1));
			if (change[0] == "1"){
				cout << "Pour " << change[0] << " gallon from " << change[1] << " to " << change[2] << ". " << path[i] << endl;
			} else{
				cout << "Pour " << change[0] << " gallons from " << change[1] << " to " << change[2] << ". " << path[i] << endl;

			}
		}
	}

}

int main(int argc, char * const argv[]) {
	int capA, capB, capC, goalA, goalB, goalC, test;
	string letter[6] = {"A", "B", "C", "A", "B", "C"};
    if (argc != 7){
    	cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
    	return 1;
    }
    capA = atoi(argv[1]);
    capB = atoi(argv[2]);
    capC = atoi(argv[3]);
    goalA = atoi(argv[4]);
    goalB = atoi(argv[5]);
    goalC = atoi(argv[6]);
    istringstream iss;
    for (int i = 1; i < 4; i++){
    	iss.str(argv[i]);
		if (!(iss >> test)){
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letter[i-1]<<".";
			return 1;
		} else if (test < 0){
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letter[i-1]<<".";
			return 1;
		} else if (i == 3 && test == 0){
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letter[i-1]<<".";
			return 1;
		}
		iss.clear();
    }
    for (int i = 4; i < 7; i++){
		iss.str(argv[i]);
		if (!(iss >> test)){
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << letter[i-1]<<".";
			return 1;
		} else if (test < 0){
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << letter[i-1]<<".";
			return 1;
		}
		iss.clear();
	}
    string let="good";
	if (capA < goalA || goalA < 0){
		let = "A.";
	}
	else if (capB < goalB || goalB < 0){
		let = "B.";
	}
	else if (capC < goalC || goalC < 0){
		let = "C.";
	}
	if (let != "good"){
		cerr << "Error: Goal cannot exceed capacity of jug " << let;
		return 1;
	}
    if (capC != goalA+goalB+goalC){
    	cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
    	return 1;
    }
    State cap(capA, capB, capC);
	State goal(goalA, goalB, goalC);
	State initial(0, 0, capC);
    print_path(min_ways(goal, initial, cap));
    return 0;
}
