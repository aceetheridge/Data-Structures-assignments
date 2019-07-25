// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

//include "stdafx.h"
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
	switch (atoi(argv[1])) {
	case 1:
		// Input vector of positive and negative random ints
		for (int i = 0; i < NUM_ELEM; i++)
			my_vec.push_back(rand() % MAX_VAL - (MAX_VAL / 2));
		break;
	case 2:
		// Input vector of sorted ints
		for (int i = 0; i < NUM_ELEM; ++i)
			my_vec.push_back(i);
		break;
	case 3:
		// Input vector of reverse sorted ints
		for (int i = 0; i < NUM_ELEM; ++i)
			my_vec.push_back(NUM_ELEM - i);
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
	for (it = my_vec.begin(); it != my_vec.end(); ++it)
		cout << *it << " ";
	cout << endl << endl;

	vector<int> sort_vec(my_vec);
	cout << "Number of inversions " << countInv(my_vec, sort_vec, 0, my_vec.size()) << endl;

	// Sorted array
	for (it = sort_vec.begin(); it != sort_vec.end(); ++it)
		cout << *it << " ";
	cout << endl;
	system("PAUSE");
	return 0;
}

int countInv(vector<int> &in_vec, vector<int> &out_vec, int begin, int end) {
	vector<int> l; //lefthalf firsthalf
	vector<int> r; //righthalf secondhalf
	int c = 0;
	if (end == 0 || end == 1 ){
	return 0;
	}
	else {
		for (int i = begin; i < end/2; i++) {
			l.push_back(out_vec[i]);
		}
		for (int j = end/2; j < end; j++) {
			r.push_back(out_vec[j]);
		}
		vector<int> l2(l), r2(r);
		int a = countInv(l, l2, 0, l.size());
		int b = countInv(r, r2, 0, r.size());
		int i = 0;
		int j = 0;
		int counter = 0;
		while (counter < end) {
			if (l2[i] <= r2[j] && (i < l2.size() && j < r2.size())) {
				out_vec[counter] = l2[i];
				counter++;
				i++;
			}
			else if (l2[i] > r2[j] && (i <l2.size() && j < r2.size())) {
				counter++;
				i++;
				c = (c + l2.size() - i);
			}
			else if (i < l2.size() && j >= r2.size()) {
				out_vec[counter] = l2[i];
				counter++, j++;
			}
			else {
				out_vec[counter] = r2[j];
				counter++, j++;
			}
		}
		return a + b + counter;
	}
}
