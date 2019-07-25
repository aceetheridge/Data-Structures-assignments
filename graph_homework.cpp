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
	int similar;
	int count;
	int kevin;
	set<string> actorset;
	unordered_multimap<string, string> acthashtbl;
	GraphAdjList<string, string> graph;
	set<string>::iterator setIt;
	unordered_multimap<string, string>::iterator hashIt;
	set<string>::iterator pairsetit;
	unordered_map<string, int> costars;
	unordered_map<string, int>::iterator costarIt;
	unordered_multimap<string, string>::iterator pairMapIt;
	string mainactor;
	string costar;
	string ethan = "Ethan_Hawke";
	string movie1;
	string movie2;
	Bridges::initialize(8, getEnvVar("BRIDGESUSERNAME"), getEnvVar("BRIDGESKEY"));

	Bridges::setTitle("Actor Graph: IMDB Data");
	vector<ActorMovieIMDB> actor_list = DataSource::getActorMovieIMDBData(1800);

	// Create a hash table of <actor name, movies acted>

	for (int k = 0; k < actor_list.size(); k++)
	{
		acthashtbl.emplace(actor_list.at(k).getActor(), actor_list.at(k).getMovie());
	}

	// Create a list of actor names with no duplicates (Hint: Use set STL)
	for (int k = 0; k < actor_list.size(); k++)
	{
		actorset.insert(actor_list.at(k).getActor());
	}
	// Fun stuff: Check how many movies has Kevin Bacon acted in
	for (int k = 0; k < actor_list.size(); k++)
	{
		string a = actor_list.at(k).getActor();
		if (a == "Kevin_Bacon_(I)")
		{
			kevin++;
		}

		// Create a GraphAdjList and add vertices corresponding to each actor

		for (setIt = actorset.begin(); setIt != actorset.end(); setIt++)
		{
			graph.addVertex(*setIt, "");
			graph.getVertex(*setIt)->getVisualizer()->setColor(Color("red"));

			for (hashIt = (acthashtbl.equal_range(*setIt)).first; hashIt != (acthashtbl.equal_range(*setIt)).second; hashIt++)
			{
				graph.addVertex((*hashIt).second, "");
				graph.getVertex((*hashIt).second)->getVisualizer()->setColor(Color("blue"));
				graph.addEdge(*setIt, (*hashIt).second, 1);
				graph.addEdge((*hashIt).second, *setIt, 1);
			}
		}

		// For every actor pair, find the movies that they have in common
		// If they have movies in common, insert an edge between the two actor vertices with edge data as number of movies that they have in common
		for (setIt = actorset.begin(); setIt != (actorset.end()); setIt++)
		{
			mainactor = *setIt;
			for (pairsetit = setIt; pairsetit != actorset.end(); pairsetit++)
			{
				costar = *pairsetit;
				similar = 0;
				if (costar == mainactor)
				{
					pairsetit++;
				}
				//continue;
				for (hashIt = (acthashtbl.equal_range(mainactor)).first; hashIt != (acthashtbl.equal_range(mainactor)).second; hashIt++)
				{
					movie1 = (*hashIt).second; //Assign movie
					for (pairMapIt = (acthashtbl.equal_range(costar)).first; pairMapIt != (acthashtbl.equal_range(costar)).second; pairMapIt++)
					{
						movie2 = (*pairMapIt).second; //Assign movie comparision
						if (movie1 == movie2)
							similar++;
					}
				}
				if (similar > 0)
				{
					graph.addEdge(mainactor, costar, similar); //inserts edge
					graph.addEdge(costar, mainactor, similar);
				}
			}
		}

		// Display graph
		Bridges::setDataStructure(&graph);
		Bridges::visualize();

		// Fun stuff: Find from the graph which actors did Denzel Washinton co-star with and number of movies they costarred in

		mainactor = "Denzel_Washington"; //Denzel Washington
		for (setIt = actorset.begin(); setIt != actorset.end(); setIt++)
		{
			string costar = *setIt; //Assign comparison actor
			if (costar == mainactor)
			{
				setIt++
			}		   //continue;
			count = 0; //Reset counterd
			for (hashIt = (acthashtbl.equal_range(mainactor)).first; hashIt != (acthashtbl.equal_range(mainactor)).second; hashIt++)
			{
				movie1 = (*hashIt).second; //Assign movie
				for (pairMapIt = (acthashtbl.equal_range(costar)).first; pairMapIt != (acthashtbl.equal_range(costar)).second; pairMapIt++)
				{
					movie2 = (*pairMapIt).second;
					if (movie1 == movie2)
					{
						count++;
					}
				}
			}
			if (count > 0)
				costars.emplace(costar, count);
		}

		 //Set up iterator
		cout << "Denzel Washington's costars:" << endl;
		for (costarIt = costars.begin(); costarIt != costars.end(); costarIt++)
		{
			cout << "Actor: " << (*costarIt).first << ", # of movies together: " << (*costarIt).second << endl;
		}
		cout << endl;

		// Fun stuff: Pick any actor that Denzel Washington co-starred with, follow the edge, and print all their co-stars
		SLelement<Edge<string>> *head = graph.getAdjacencyList().at(ethan); // sets ethan hawke
		cout << "Ethan Hawke costars: " << endl;
		for (SLelement<Edge<string>> *sle = head; sle != nullptr; sle = sle->getNext())
		{																	 
			for (setIt = actorset.begin(); setIt != actorset.end(); setIt++)
				if (sle->getValue().getVertex() == *setIt && sle->getValue().getVertex() != ethan)
					cout << "Actor: " << sle->getValue().getVertex() << endl;
		}
		cout << endl;

		return 0;
	}

	string getEnvVar(string const &key)
	{
		char *val = getenv(key.c_str());
		return val == NULL ? string("") : string(val);
	}