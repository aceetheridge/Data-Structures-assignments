// Aaron Etheridge 800936351
// ECGR 3090 Data Structures and Algorithms
// Assignment 4 Inverstion Sort
// Finds the number of inversions required to sort a vector array

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cassert>

using namespace std;

const int NUM_ELEM = 15;
const int MAX_VAL = 100;

int countInv(vector<int> &in_vec, vector<int> &out_vec, int begin, int end); 

int main(int argc, char **argv)
{
    vector<int> my_vec;
    vector<int>::iterator it;
    srand(time(0)); // Seed for random number generator
    assert(argc == 2);
    switch(atoi(argv[1])) {
        case 1:
                // Input vector of positive and negative random ints
                for (int i = 0; i < NUM_ELEM; i++)
                    my_vec.push_back(rand() % MAX_VAL - (MAX_VAL/2));
                break;
        case 2:
                // Input vector of sorted ints
                for (int i = 0; i < NUM_ELEM; ++i)
                    my_vec.push_back(i);
                break;
        case 3: 
                // Input vector of reverse sorted ints
                for (int i = 0; i < NUM_ELEM; ++i)
                    my_vec.push_back(NUM_ELEM-i);
                break;
        case 4:
                // Custom input
                my_vec.push_back(4);
                my_vec.push_back(5);
                my_vec.push_back(6);
                my_vec.push_back(1);
                my_vec.push_back(2);
                my_vec.push_back(3);
                break;
        default: 
                cout << "Invalid input" << endl;
                return -1;
        
    }
    
    // Print vector
    for (it = my_vec.begin(); it !=  my_vec.end(); ++it)
        cout << *it << " ";
    cout << endl << endl;
    
    vector<int> sort_vec(my_vec);
    cout << "Number of inversions " << countInv(my_vec, sort_vec, 0, my_vec.size()) << endl;

    // Sorted array
    for (it = sort_vec.begin(); it != sort_vec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int countInv(vector<int> &in_vec, vector<int> &out_vec, int begin, int end) {
    int rightcount = 0;
    int leftcount = 0; 
	int index = 0;
	int total = 0; 
	int finalcount = 0;
	int mid = (end / 2);
    vector<int> r, l;
    if(end == 0){
        return 0;    
    }
	else if(end == 1){
		return 0;
	}
    else{
		for(int i = 0; i < end; i++){ // fills both left and right arrays
			if(i < mid){
				l.push_back(out_vec[i]);
			}
			else if(i >= mid){
				r.push_back(out_vec[i]);
			}
        }


        vector<int> l2(l), r2(r);
        leftcount = countInv(l, l2, 0, l.size()); // gets inversion counts for left and
        rightcount = countInv(r, r2, 0, r.size()); // right sides 
        

		int x = 0;
        int y = 0;
        while (index < end){ // steps through out_vec index
            if((x < l2.size() && y < r2.size()) && (r2[y] < l2[x])){ // when right is smaller within bounds
                out_vec[index] =r2[y];
                index++;
                y++;
                total += l2.size() - x; // adds to the total size but subtracts from the sorted portion of the output vector
            }
			else if((x < l2.size() && y < r2.size()) && (l2[x] <= r2[y])){ // when left is smaller within bounds
                out_vec[index] = l2[x];
                index++;
                x++;
            }
            else if(x < l2.size() && y >= r2.size()){ // increments left side when already sorted 
                out_vec[index] = l2[x];
                index++;
                x++;
            }
            else{ // increments right side when already sorted
                out_vec[index] = r2[y];
                index++;
                y++;
            }

        }
		finalcount = rightcount +leftcount + total; // sums counts
        return finalcount;
    }


}
