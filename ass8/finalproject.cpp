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
// set<string> findmovies(string findactor, unordered_multimap<string,string> acthash);
// set<string> findactors(string movie, unordered_multimap<string,string> movhash);
// int seperation(string actor1, string actor2, unordered_multimap<string,string>, unordered_multimap<string,string>, int);

// Given two user input actors, find the degree of separation.
//  If they have co-starred in a movie they have one degree of separation.
//   If they have not co-starred in any movie,
//    but if there is another findactor with whom both the input actors 
//    have co-starred in, the degree of separation is two.
//  The definition can be extended to higher degrees of separation.
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
	string dw = "Denzel_Washington";
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

	for (int k = 0; k < actor_list.size(); k++)
	{
		actors.insert(actor_list.at(k).getActor());
	}

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
    return 0;
}










































//     // set<string> actorNames;
//     // set<string> movieNames; //Set up setunordered_multimap<string,string>
//     // set<string>:: iterator setIt;
// 	// for (int k = 0; k < actor_list.size();k++){
// 	// 	actorNames.insert(actor_list.at(k).getActor());
//     //     movieNames.insert(actor_list.at(k).getMovie());
//     //     }
//     // set<string> test = findmovies("Arnold_Schwarzenegger", actorHash);
//     // for(setIt = test.begin(); setIt != test.end();setIt++){
//     //     cout << *setIt << endl;
//     // }
//     // set<string> test2 = findactors("Glory_(1989)", movieHash);
//     // for(setIt = test2.begin(); setIt != test2.end();setIt++){
//     //     cout << *setIt << endl;
//     // }
//     int x = seperation("Christian_Bale", "Denzel_Washington", actorHash, movieHash,1);
//     cout << x << endl;


//     return 0;
// }

// int seperation(string actor1, string actor2, unordered_multimap<string,string> act2hash, unordered_multimap<string,string> mov2hash, int num ){
//     // set<string>:: iterator movIt;
//     // set<string>:: iterator actIt;
//     // set<string> allacts;
//     // set<string> finalacts;
//     // set<string> temp2;

//     // if(actor1 == actor2){
//     //     return num;
//     // }
//     // else if(actor1 != actor2){
//     //     set<string> temp = findmovies(actor1,act2hash);
//     //     for(movIt = temp.begin(); movIt != temp.end(); movIt++){
//     //         temp2 = findactors(*movIt, mov2hash);
//     //         set_union(allacts.begin(), allacts.end(),temp2.begin(), temp2.end(), inserter(finalacts, finalacts.begin()));
//     //         for(actIt = temp2.begin(); actIt != temp2.end(); actIt++){
//     //             if (*actIt == actor2){
//     //                 return num;
//     //             }
//     //         }
//     //     }
//     //     for(actIt = finalacts.begin();actIt != finalacts.end();actIt++){
//     //         cout << *actIt << endl;
//     //     }


//     // }
//     int count = 0;
//     set<string>:: iterator movIt;
//     set<string>:: iterator actIt;
//     set<string> temp = findmovies(actor1,act2hash);
//         for(movIt = temp.begin(); movIt != temp.end(); movIt++){
//             set<string>temp2 =findactors(*movIt, mov2hash);
//             for(actIt = temp2.begin();actIt != temp2.end();actIt++){
//                 if(*actIt == actor2) {
//                     return num;
//                 }
//                 else{
//                     seperation(*actIt, actor2, act2hash, mov2hash, num+1);
//                 }
//             }
//         }
   
// }

// set<string> findmovies(string findactor, unordered_multimap<string,string> acthash){
//     unordered_multimap<string, string>:: iterator mapIt;
//     set<string>movieset;
//     for(mapIt = (acthash.equal_range(findactor)).first;mapIt != (acthash.equal_range(findactor)).second; mapIt++){
//         movieset.insert((*mapIt).second);
//     }
//     return movieset;
// }
// set<string> findactors(string movie, unordered_multimap<string,string> movhash){
//     unordered_multimap<string, string>:: iterator mapIt;
//     set<string>actorset;
//     for(mapIt = (movhash.equal_range(movie)).first;mapIt != (movhash.equal_range(movie)).second; mapIt++){
//         actorset.insert((*mapIt).second);
//     }
//     return actorset;
// }
string getEnvVar(string const & key) {
    char * val = getenv( key.c_str() );
    return val == NULL ? string("") : string(val);
}