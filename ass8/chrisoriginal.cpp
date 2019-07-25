// Assigment: Create actor graph and visuzlize with BRIDGES. Also, do some fun stuff with the graph
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
#include <unordered_map>
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

	// Create a hash table of <actor name, movies acted>
	// Your code here...
	unordered_multimap<string,string> actorHash; //Set up hash table
	for (int k = 0; k < actor_list.size();k++)
		actorHash.emplace(actor_list.at(k).getActor(),actor_list.at(k).getMovie()); //Popluate hash table

	// Create a list of actor names with no duplicates (Hint: Use set STL)
	// Your code herei...	
	set<string> actorNames; //Set up set
	for (int k = 0; k < actor_list.size();k++)
		actorNames.insert(actor_list.at(k).getActor()); //Populate set
	
	// Fun stuff: Check how many movies has Kevin Bacon acted in
	// Your code here...
	int count = actorHash.count("Kevin_Bacon_(I)"); //See how many movies Keven Bacon has been in
	cout << "The number of movies Kevin Bacon acted in: " << count << endl;

	// Create a GraphAdjList and add vertices corresponding to each actor
	// Your code here...
	GraphAdjList<string, string> graph; //Set up graph
	set<string>::iterator setIterator; //Set up iterator
	unordered_multimap<string,string>::iterator mapIterator;  //Set up iterator
	
	for (setIterator = actorNames.begin(); setIterator != actorNames.end(); setIterator++) {
		graph.addVertex(*setIterator,""); //Assign an actor a vertex
		graph.getVertex(*setIterator)->getVisualizer()->setColor(Color("red"));
				
		for (mapIterator = (actorHash.equal_range(*setIterator)).first; mapIterator != (actorHash.equal_range(*setIterator)).second; mapIterator++) {
			graph.addVertex((*mapIterator).second,""); //Assign a movie a vertex
			graph.getVertex((*mapIterator).second)->getVisualizer()->setColor(Color("blue"));
			graph.addEdge((*mapIterator).second, *setIterator, 1); //Connect movie with actor
			graph.addEdge(*setIterator,(*mapIterator).second, 1); //Connect actor with movie
		}
	}

	// For every actor pair, find the movies that they have in common
	// If they have movies in common, insert an edge between the two actor vertices with edge data as number of movies that they have in common
	// Your code here...
	set<string>::iterator temp; //Set up iterator
	unordered_multimap<string,string>::iterator mapTemp; //Set up iterator
	string actor1; //Keep track of current actor
	string actor2; //Keep track of comparison actor
	string movie1; //Keep track of movie
	string movie2; //Keep track if shared movie
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

	// Display graph
	// Your code here...
	Bridges::setDataStructure(&graph); //Set up visualization
	Bridges::visualize(); //Visualize
	
	// Fun stuff: Find from the graph which actors did Denzel Washinton co-star with and number of movies they costarred in
	// Your code here....
	unordered_map<string,int> costars; //Keep track of costars and movies they were in together
	actor1 = "Denzel_Washington"; //Denzel Washington 
	for (setIterator = actorNames.begin(); setIterator != actorNames.end(); setIterator++) {
		string actor2 = *setIterator; //Assign comparison actor
		if (actor2 == actor1) continue;
		count = 0; //Reset counterd
		for (mapIterator = (actorHash.equal_range(actor1)).first; mapIterator != (actorHash.equal_range(actor1)).second; mapIterator++) {
			movie1 = (*mapIterator).second; //Assign movie
			for (mapTemp = (actorHash.equal_range(actor2)).first; mapTemp != (actorHash.equal_range(actor2)).second; mapTemp++) {
				movie2 = (*mapTemp).second; //Assign comparison movie
				if (movie1 == movie2) 
					count++; //If the movies were the same, increment
			}
		}
		if (count != 0) costars.emplace(actor2,count); //Popluate the Hash table
	}
	
	unordered_map<string,int>::iterator costarIterator; //Set up iterator
	cout << "Denzel Washington's costars and number of movies they costarred together in:" << endl;
	for (costarIterator = costars.begin(); costarIterator != costars.end(); costarIterator++)
		cout << "Actor: " << (*costarIterator).first << ", # of movies together: " << (*costarIterator).second << endl;
	cout << endl;

	// Fun stuff: Pick any actor that Denzel Washington co-starred with, follow the edge, and print all their co-stars 
	// Your code here...
	SLelement<Edge<string>>  *head = graph.getAdjacencyList().at("Morgan_Freeman_(I)"); //Using the vertex of Morgan Freeman
	cout << "Morgan Freeman costars: " << endl;
	for (SLelement<Edge<string>> *sle = head; sle != nullptr;
		sle = sle->getNext() ) { //Changing between the nodes around Morgan freeman
		string term_vertex = sle->getValue().getVertex(); //Getting the value of the vertex visited
		for (setIterator = actorNames.begin(); setIterator != actorNames.end(); setIterator++) //Iterates through the actors names
			if (term_vertex == *setIterator && term_vertex != "Morgan_Freeman_(I)") //Makes sure it's only actors and not movies
				cout << "Actor: " << term_vertex << endl;

	}
	cout << endl;
	
	return 0;
}

string getEnvVar(string const & key) {
    char * val = getenv( key.c_str() );
    return val == NULL ? string("") : string(val);
}


