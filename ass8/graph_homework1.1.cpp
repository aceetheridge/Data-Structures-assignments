// Assigment: Create actor graph and visuzlize with BRIDGES. Also, do some fun stuff with the graph
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <vector>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/ActorMovieIMDB.h"
#include "GraphAdjList.h"

using namespace std;
using namespace bridges;

string getEnvVar(string const & key);
set<string> actors;
set<string> :: iterator itr;


int main() {							//aetheri2 523459773336
	Bridges::initialize(1, getEnvVar("BRIDGESUSERNAME"), getEnvVar("BRIDGESKEY"));


	Bridges::setTitle("Actor Graph: IMDB Data");
	vector<ActorMovieIMDB> actor_list = DataSource::getActorMovieIMDBData(1800);
	unordered_map<string,vector<string>> actorhash;
	vector<vector<string>> movies;
	vector<string> vecactors;
	GraphAdjList<string, string> graph;
	int kevin = 0;



    for(int i = 0; i < actor_list.size(); i++){
        actors.insert(actor_list.at(i).getActor());
    }

	for (int k = 0; k < actor_list.size(); k++) {
		// from the actor movie data, get an actor-movie pair
		string a = actor_list.at(k).getActor();
		if (a == "Kevin_Bacon_(I)"){
			kevin++;
		}
		string m = actor_list.at(k).getMovie();
		vector<string> vecmovies;
		vecmovies.push_back(m);
		actorhash.insert(make_pair(a,vecmovies));
	}
	cout << "Kevin Bacon has acted in " << kevin << " movies." << endl;
	
	for(itr = actors.begin(); itr != actors.end(); ++itr){
		graph.addVertex(*itr, "");
        graph.getVertex(*itr)->getVisualizer()->setColor(Color("red"));
    	}
	Bridges::setDataStructure(&graph);
	Bridges::visualize();
	graph.addEdge("Kevin_Bacon_(I)", "Denzel_Washington", 1);

	
	//for(int i = 0; i < actor_list.size(); i++){
		for(int j = 0; j < actor_list.size(); j++){
			//string ia = actor_list.at(i).getActor();
			string ja = actor_list.at(j).getActor();
			//string im = actor_list.at(i).getMovie();
			string jm = actor_list.at(j).getMovie();
			graph.addVertex(jm, "");
			graph.addEdge(ja,jm,1);
			graph.addEdge(jm,ja,1);
			// if (ja == jm){
			// 	graph.addVertex(im,"");
			// 	graph.addEdge(ia, jm, 1);
			// 	graph.addEdge(jm, ia, 1);
			// }
			graph.getVertex(jm)->getVisualizer()->setOpacity(0.5f);
		}
	//}
		// provide BRIDGES the  handle to the tree structure
	Bridges::setDataStructure(&graph);
	// Visualize the graph
	Bridges::visualize();





    // for(itr = actors.begin(); itr != actors.end(); itr++){
    //     cout << *itr << endl;
    // }

	// vector<vector<string>> findAnagrams(const vector<string>& dict)
	// {
    //  vector<vector<string>> bucket;             //bucket that contains the words that match the same key
    //  unordered_map<string,vector<string>> hash; //Unordered map that will link the keys to the buckets
    //  string temp;                               //holds temp string value to sort so dict isnt changed
     
    //  for (auto words : dict){
    //         temp = words;                       //stores the temp before sorting
    //         sort(words.begin(),words.end());    //sorts from be gining to end of vector in alphabetical order
    //         hash[words].push_back(temp);        //creates a new hash based on what words is
            
    //  }
     
    //  for (auto list : hash){
    //         bucket.push_back(list.second);      //steps through hash table and assigns anagrams to the keys
    //  }
     
    //  return bucket;
	// }
	// for (int k = 0; k < actor_list.size(); k++) {
	// 	// from the actor movie data, get an actor-movie pair
	// 	string a = actor_list.at(k).getActor();
	// 	string m = actor_list.at(k).getMovie();
		


	// 	//actorhash[a] = m;
	// }
	// for(auto& x: actorhash){
	// 	cout << x.first << ": " << x.second << endl;
	// }






	// Create a hash table of <actor name, movies acted>
	// Your code here...

	// Create a list of actor names with no duplicates (Hint: Use set STL)
	// Your code herei...	

	// Fun stuint kevin = 0;int kevin = 0;int kevin = 0;int kevin = 0;int kevin = 0;int kevin = 0;int kevin = 0;int kevin = 0;ff: Check how many movies has Kevin Bacon acted in
	// Your code here...

	// Create a GraphAdjList and add vertices corresponding to each actor
	// Your code here...


	// For every actor pair, find the movies that they have in common
	// If they have movies in common, insert an edge between the two actor vertices with edge data as number of movies that they have in common
	// Your code here...


	// Display graph
	// Your code here...

	// Fun stuff: Find from the graph which actors did Denzel Washinton co-star with and number of movies they costarred in
	// Your code here....

	// Fun stuff: Pick any actor that Denzel Washington co-starred with, follow the edge, and print all their co-stars 
	// Your code here...

	return 0;
}
// int main() {				//aetheri2 523459773336
// 	Bridges::initialize(12, "aetheri2", "523459773336");

// 	Bridges::setTitle("Graph Adj List Example: IMDB Data");
// 	vector<ActorMovieIMDB> actor_list = DataSource::getActorMovieIMDBData(1800);

// 	GraphAdjList<string, string> graph;


// 	// first create vertices for two actors
// 	string bacon = "Kevin_Bacon_(I)", washington = "Denzel_Washington";
// 	// add them to the graph
// 	graph.addVertex(bacon, "");
// 	graph.addVertex(washington, "");

// 	// color the nodes
// 	graph.getVertex(bacon)->getVisualizer()->setColor(Color("red"));
// 	graph.getVertex(washington)->getVisualizer()->setColor(Color("red"));
// 	graph.addEdge(bacon, washington, 1);

// 	// we will find the first 15 immediate neighbors of of the two actors
// 	// and color those links and nodes by followng their adjacency lists
// 	int cnt1 = 0, cnt2 = 0;
// 	for (int k = 0; k < actor_list.size(); k++) {
// 		// from the actor movie data, get an actor-movie pair
// 		string a = actor_list.at(k).getActor();
// 		string m = actor_list.at(k).getMovie();

// 		if ((a == "Kevin_Bacon_(I)") && (cnt1 < 15)) {

// 			// add vertices for this movie  and an edge for the link
// 			graph.addVertex(m, "");
// 			graph.addEdge(bacon, m, 1);
// 			graph.addEdge(m, bacon, 1);

// 			// make the movie node a bit transparent
// 			graph.getVertex(m)->getVisualizer()->setOpacity(0.5f);
// 			cnt1++;
// 		}
// 		else if ((a == "Denzel_Washington") && (cnt2 < 15)) {
// 			// add vertices for this movie  and an edge for the link
// 			graph.addVertex(m, "");
// 			graph.addEdge(washington, m, 1);
// 			graph.addEdge(m, washington, 1);
// 			// make the movie node a bit transparent
// 			graph.getVertex(m)->getVisualizer()->setOpacity(0.5f);
// 			cnt2++;
// 		}
// 	}


// 	// Next, we illustrate traversing the adacency list and color the
// 	// movie nodes adjacent to the Kevin Bacon node.

// 	// first get the adjacency list for Kevin Bacon
// 	SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(bacon);
// 	// traverse the adjacency list
// 	for (SLelement<Edge<string>> *sle = head; sle != nullptr;
// 		sle = sle->getNext() ) {
// 		// get the terminating vertex
// 		string term_vertex = sle->getValue().getVertex();
// 		// find the corresponding element
// 		Element<string> *el = graph.getVertex(term_vertex);
// 		// set the  color of the node except the Denzel W. node
// 		if (term_vertex != "Denzel_Washington")
// 			el->getVisualizer()->setColor(Color("green"));
// 	}

// 	// provide BRIDGES the  handle to the tree structure
// 	Bridges::setDataStructure(&graph);
// 	// Visualize the graph
// 	Bridges::visualize();

// 	return 0;
// }


string getEnvVar(string const & key) {
    char * val = getenv( key.c_str() );
    return val == NULL ? string("") : string(val);
}


