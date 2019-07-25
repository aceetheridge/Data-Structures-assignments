// Aaron Etheridge
// 800936351 aetheri2@uncc.edu
// ECGR 3090 Data Structures
// Assignment 8 Graphs

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

string getEnvVar(string const &key);

int main()
{
	unordered_multimap<string, string> acthashtbl;
	set<string> actors;
	GraphAdjList<string, string> graph;
	set<string>::iterator setIt;
	unordered_multimap<string, string>::iterator mapIt;
	set<string>::iterator set2It;
	unordered_multimap<string, string>::iterator set2; //Set up iterator
	unordered_map<string, int> costars;
	unordered_map<string, int>::iterator coIt; //Set up iterator
	string dw = "Charlie_Sheen";
	string as = "Arnold_Schwarzenegger";
	string actor1;
	string actor2;
	int count;
	int kevin = 0;
	Bridges::initialize(8, getEnvVar("BRIDGESUSERNAME"), getEnvVar("BRIDGESKEY"));

	Bridges::setTitle("Actor Graph: IMDB Data");
	vector<ActorMovieIMDB> actor_list = DataSource::getActorMovieIMDBData(1800);

	// Create a hash table of <actor name, movies acted>
	for (int k = 0; k < actor_list.size(); k++)
	{
		acthashtbl.emplace(actor_list.at(k).getActor(), actor_list.at(k).getMovie()); //Popluate hash table
	}
	// Create a list of actor names with no duplicates (Hint: Use set STL)
	// int actorcount= 0;
	for (int k = 0; k < actor_list.size(); k++)
	{
		actors.insert(actor_list.at(k).getActor());
		// actorcount++;
	}
	// cout << actorcount << endl;

	// Fun stuff: Check how many movies has Kevin Bacon acted in
	for (int k = 0; k < actor_list.size(); k++)
	{
		string a = actor_list.at(k).getActor();
		if (a == "Kevin_Bacon_(I)")
		{
			kevin++;
		}
	}
	cout << "Kevin Bacon has stared in " << kevin << " movies" << endl
		 << endl;

	// Create a GraphAdjList and add vertices corresponding to each actor

	for (setIt = actors.begin(); setIt != actors.end(); setIt++)
	{
		graph.addVertex(*setIt, ""); //Assign an actor a vertex
		graph.getVertex(*setIt)->getVisualizer()->setColor(Color("red"));
	}
	Bridges::setDataStructure(&graph);
	Bridges::visualize();

	// For every actor pair, find the movies that they have in common
	// If they have movies in common, insert an edge between the two actor vertices with edge data as number of movies that they have in common

	for (setIt = actors.begin(); setIt != (actors.end()); setIt++) // goes through actors
	{
		for (set2It = setIt; set2It != actors.end(); set2It++)
		{
			count = 0;
			if (*set2It == *setIt) // if they match skip
				continue;
			for (mapIt = (acthashtbl.equal_range(*setIt)).first; mapIt != (acthashtbl.equal_range(*setIt)).second; mapIt++) // steps through every movie for the actor
			{
				for (set2 = (acthashtbl.equal_range(*set2It)).first; set2 != (acthashtbl.equal_range(*set2It)).second; set2++) // steps through second actor
				{
					if ((*mapIt).second == (*set2).second)
					{
						count++; // adds to the count if in same movie
					}
				}
			}
			if (count > 0)
			{ //makes edges between actors for the amount of movies they've had together
				graph.addEdge(*setIt, *set2It, count);
				graph.addEdge(*set2It, *setIt, count);
			}
		}
	}
	Bridges::setDataStructure(&graph);
	Bridges::visualize();

	// Fun stuff: Find from the graph which actors Denzel Washinton co-star with and number of movies they costarred in
	for (setIt = actors.begin(); setIt != actors.end(); setIt++)
	{
		if (*setIt == dw) // if denzel skips
			setIt++;
		count = 0;
		for (mapIt = (acthashtbl.equal_range(dw)).first; mapIt != (acthashtbl.equal_range(dw)).second; mapIt++) // steps through every movie for denzel
		{
			for (set2 = (acthashtbl.equal_range(*setIt)).first; set2 != (acthashtbl.equal_range(*setIt)).second; set2++) // steps through second actor
			{
				if ((*mapIt).second == (*set2).second) // counts if they match
					count++;
			}
		}
		if (count > 0)
		{
			costars.emplace(*setIt, count); // creates a list of costars to denzel
		}
	}
	// outputs all the matches
	for (coIt = costars.begin(); coIt != costars.end(); coIt++)
	{
		cout << dw << " has " << (*coIt).second << " movies with " << (*coIt).first << endl;
	}
	cout << endl;

	// Fun stuff: Pick any actor that Denzel Washington co-starred with, follow the edge, and print all their co-stars
	SLelement<Edge<string>> *arnold = graph.getAdjacencyList().at(as);
	cout << "Arnold Schwarzenegger is in movies with  " << endl;
	for (SLelement<Edge<string>> *sle = arnold; sle != nullptr; sle = sle->getNext())
	{
		for (setIt = actors.begin(); setIt != actors.end(); setIt++) // goes through all the actors
		{
			if (sle->getValue().getVertex() == *setIt && sle->getValue().getVertex() != as) // if the actor matches arnold
			{
				cout << sle->getValue().getVertex() << endl; // outputs the other actors name
			}
		}
	}
	cout << endl;

	return 0;
}

string getEnvVar(string const &key)
{
	char *val = getenv(key.c_str());
	return val == NULL ? string("") : string(val);
}
