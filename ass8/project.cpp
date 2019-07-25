// Assigment: Create actor graph and visuzlize with BRIDGES. Also, do some fun stuff with the graph
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <queue>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/ActorMovieIMDB.h"
#include "GraphAdjList.h"

using namespace std;
using namespace bridges;

string getEnvVar(string const & key);


int main() {
	Bridges::initialize(8, getEnvVar("BRIDGESUSERNAME"), getEnvVar("BRIDGESKEY"));


	Bridges::setTitle("Actor Graph: IMDB Data");
	vector<ActorMovieIMDB> actor_list = DataSource::getActorMovieIMDBData(1800);

	// Setup
	int count; //Set up counter
	multimap<int, string> inCommon; // Set up for ordered multimap for costars
	multimap<int, string>::iterator tempIterator; //Set up iterator
	multimap<int, string>::iterator tempIterator2; //Set up iterator
	multimap<int, string>::iterator tempTemp; //Set up iterator
	set<string>::iterator setIterator; //Set up iterator
	unordered_multimap<string,string>::iterator mapIterator;  //Set up iterator
	set<string>::iterator temp; //Set up iterator
	unordered_multimap<string,string>::iterator mapTemp; //Set up iterator
	string actor1; //Keep track of current actor
	string actor2; //Keep track of comparison actor
	string movie1; //Keep track of movie
	string movie2; //Keep track if shared movie

	// Create a hash table of <actor name, movies acted>
	unordered_multimap<string,string> actorHash; //Set up hash table
	for (int k = 0; k < actor_list.size();k++)
		actorHash.emplace(actor_list.at(k).getActor(),actor_list.at(k).getMovie()); //Popluate hash table

	// Create a list of actor names with no duplicates (Hint: Use set STL)
	// Your code herei...	
	set<string> actorNames; //Set up set
	for (int k = 0; k < actor_list.size();k++)
		actorNames.insert(actor_list.at(k).getActor()); //Populate set
	
	
	// Create a GraphAdjList and add vertices corresponding to each actor
	GraphAdjList<string, string> graph; //Set up graph
	
	for (setIterator = actorNames.begin(); setIterator != actorNames.end(); setIterator++) {
		graph.addVertex(*setIterator,""); //Assign an actor a vertex
		graph.getVertex(*setIterator)->getVisualizer()->setColor(Color("blue"));
	}

	// Connect actors that worked together
	for (setIterator = actorNames.begin(); setIterator != (actorNames.end()); setIterator++) {
		actor1 = *setIterator; //Assign actor
		for (temp = setIterator; temp != actorNames.end(); temp++) {
			actor2 = *temp; //Assign comparison actor
			count = 0; //Reset counting number of movies
			if (actor2 == actor1) continue;
			for (mapIterator = (actorHash.equal_range(actor1)).first; mapIterator != (actorHash.equal_range(actor1)).second; mapIterator++) {
				movie1 = (*mapIterator).second; //Assign movie
				for (mapTemp = (actorHash.equal_range(actor2)).first; mapTemp != (actorHash.equal_range(actor2)).second; mapTemp++) {
					movie2 = (*mapTemp).second; //Assign movie comparision
					if (movie1 == movie2) 
						count++; //If the movies are the same, increment
				}
			}
			if (count != 0) {
				graph.addEdge(actor1,actor2, count); //Connect the two actors
				graph.addEdge(actor2,actor1, count);
			}
		}
	}	
	
	// Degree of separation
	unordered_map<string, int> degreeMap; //Set up for degree setting
	queue<string> actorQueue1; //Set up queue
	queue<string> actorQueue2; //Set up alt queue
	count = 0;
	string queueString;
	int check1 = 0, check2 = 0, check3 = 0, whichQueue = 0;
	do {
		cout << "Input an actor:\n";
		cin >> actor1;
		cout << "\nInput another actor:\n";
		cin >> actor2;
		cout << endl;
		for (setIterator = actorNames.begin(); setIterator != actorNames.end(); setIterator++) {
			degreeMap.emplace(*setIterator, -1);
			if (actor1 == *setIterator) check1 = 1;
			if (actor2 == *setIterator) check2 = 1;
		}
	} while (check1 == 1 && check2 == 1);
	actorQueue1.push(actor1);
	degreeMap[actor1] = 0;
	do {
		count++;
		while((actorQueue1.size() > 0 && whichQueue == 0) || (actorQueue2.size() > 0 && whichQueue == 1)) {
			if (whichQueue == 0) {
				queueString = actorQueue1.front();
				actorQueue1.pop();
			}
			else {
				queueString = actorQueue2.front();
				actorQueue2.pop();
			}
			SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(queueString); //Using the vertex of actor
			for (SLelement<Edge<string>> *sle = head; sle != nullptr;
				sle = sle->getNext() ) { //Changing between the nodes around actor
				string term_vertex = sle->getValue().getVertex(); //Getting the value of the vertex visited
				if (term_vertex != queueString) {//Makes sure it's not same actor
					if (degreeMap[term_vertex] == -1) {
						degreeMap[term_vertex] = count;
						if (whichQueue == 0) actorQueue2.push(term_vertex);
						else actorQueue1.push(term_vertex);

						if (term_vertex == actor2) check3 = 1;
					}
				}
			}		
		}
		if (whichQueue == 0) whichQueue = 1;
		else whichQueue = 0;
	} while (check3 == 0);
	cout << "Degree of separation between: " << actor1 << " & " << actor2 <<": " << degreeMap[actor2] << endl << endl;
	
	// Number of costars
	cout << "Top three actors for number of costars\n";
	count = 0;
	for (setIterator = actorNames.begin(); setIterator != actorNames.end(); setIterator++) { //Iterates through the actors names
		SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(*setIterator); //Using the vertex of actor
		for (SLelement<Edge<string>> *sle = head; sle != nullptr;
			sle = sle->getNext() ) { //Changing between the nodes around actor
			string term_vertex = sle->getValue().getVertex(); //Getting the value of the vertex visited
			if (term_vertex != *setIterator) //Makes sure it's not same actor
				count++;
		}
		inCommon.emplace(count,*setIterator);
		count = 0;
	}
	tempIterator2 = inCommon.end(); tempIterator2--; tempTemp = tempIterator2; tempIterator2--; tempIterator2--; tempIterator2--;
	for (tempIterator = tempTemp; tempIterator != tempIterator2; tempIterator--)
		cout << "Actor: " << (*tempIterator).second << ", # of costars: " << (*tempIterator).first << endl;
	cout << endl;

/*
	// Display graph
	Bridges::setDataStructure(&graph); //Set up visualization
	Bridges::visualize(); //Visualize
*/
	
	return 0;
}

string getEnvVar(string const & key) {
    char * val = getenv( key.c_str() );
    return val == NULL ? string("") : string(val);
}


