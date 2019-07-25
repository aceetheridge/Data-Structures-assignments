// Aaron Etheridge 800936351
// Assignment 5 ECGR 3090
// Data Structures and Algorythms
// Finds the mean between two heaps

#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <random>
using namespace std;

const int MAX_VAL = 100;
const int NUM_ELEM = 15;
const int HALF_VAL = (MAX_VAL/2);
int find_median(priority_queue<int, vector<int>, greater<int>>& h_high, priority_queue<int>& h_low, int num);
template<typename T> void print_queue(T& q);

int main() {
    int current_median;
    priority_queue<int> lo; // Bottom half of numbers - max-heap (default) 
    priority_queue<int, vector<int>, greater<int> > hi; // Top half of numbers - min-heap 
    srand(time(0)); // Seed for random number generator
    for (int i = 0; i < NUM_ELEM; i++) {
        int n = rand() % MAX_VAL;
        current_median = find_median(hi, lo, n);
        cout <<  "Inserted " << n << " Median " << current_median << endl << endl;
    }
    return 0;
}

template<typename T> void print_queue(T& q) {
    T q_copy(q);
    while(!q_copy.empty()) {
        std::cout << q_copy.top() << " ";
        q_copy.pop();
    }
    std::cout << '\n';
}
 

int find_median(priority_queue<int, vector<int>, greater<int>>& h_high, priority_queue<int>& h_low, int num) {
int temp = 0;

// temp = h_low.top();
// h_low.pop();
// h_high.push(temp);

int median = 0;
		if(num <= 50){ // Fills the two heaps
			h_low.push(num);
		}
		else if(num >= 50){ // fills the two heaps
			h_high.push(num);
		}
	if((h_low.size() + h_high.size()) % 2 == 0){ // if the two heap sizes are equal
		while(h_low.size() < h_high.size()){
			h_low.push(h_high.top()); // swaps if the tops are on the wrong side
			h_high.pop();
		}
		while(h_high.size() < h_low.size()){ // swaps if the tops are on the wrong
			h_high.push(h_low.top());		//  side.
			h_low.pop();
		}
		median = (h_low.top()+h_high.top()) / 2; // outputs the median inbetween the 
	}											 // two tops of the heaps.	
	
	else if((h_low.size() + h_high.size()) % 2 == 1){ // if the two heap sizes arnt equal
		while(h_low.size() < (h_high.size())){ // sorts the heaps so the top is larger
			h_low.push(h_high.top());
			h_high.pop();			
		}
		while(h_low.size() >= h_high.size()){ // sorts the heaps so the top is larger
			h_high.push(h_low.top());
			h_low.pop();
			}
		if(h_high.top() < h_low.top()){ // makes sure on the last pass that the heaps are 
			temp = h_high.top();        // sorted properly, by comparing both tops
			h_high.pop();				// and swaping them
			h_high.push(h_low.top());
			h_low.pop();
			h_low.push(temp);
			}
		median = h_high.top();	// once ordered properly it picks the top from high
								// beacuse the algorythm makes top have one more		
	}							// which would always be the mean.
	else{
		std::cout << "error" << std::endl; // catch error statement
	}
	cout << "Top " << endl; // couts what is going on
	print_queue(h_high);
	cout << "Bot " << endl;
	print_queue(h_low);


	return median;
}



