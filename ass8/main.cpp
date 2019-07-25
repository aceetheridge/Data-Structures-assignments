//Aaron Etheridge 800936351 aetheri2@uncc.edu	
//Rober Fodell 800856813 rfodell1@uncc.edu
//ECGR 3090 Data Structures and Algorithms

// Final Project

////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////OLD CODE START///////////////////////////////////////////////////////////////
#include <iostream>
#include <queue>
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

unordered_map<string, vector<string>> movie_map; //list of movies sorted by actors
unordered_map<string, vector<string>> actor_map; //list of actors sorted by movies
GraphAdjList<string, string> graph;

string getEnvVar(string const & key);
int findSeparation(string actor1, string actor2);
void topThree();
int findNumMovies(string actor1, string actor2);

int main() {
	Bridges::initialize(2, getEnvVar("BRIDGESUSERNAME"), getEnvVar("BRIDGESKEY"));


	Bridges::setTitle("Data Structures Project");
	vector<ActorMovieIMDB> actor_list = DataSource::getActorMovieIMDBData(1800);

	// Create a hash table of <actor name, movies acted>
	// Your code here...

	for (int i = 0; i < actor_list.size(); i++) { 

        	string actor = actor_list.at(i).getActor();                      
        	             

        	if (movie_map.find(actor) == movie_map.end()) {          

            		vector<string> temp_vec;                
            		temp_vec.push_back(actor_list.at(i).getMovie());            
            		movie_map.insert(make_pair(actor, temp_vec));  
        	} 
        	else {					    
            		vector<string> temp_vec = movie_map[actor]; 
            		temp_vec.push_back(actor_list.at(i).getMovie()); 	    
            		movie_map[actor] = temp_vec; 		    
        	} 
    	} 
	

	for (int i = 0; i < actor_list.size(); i++) { 

        	string movie = actor_list.at(i).getMovie();                      
        	             

        	if (actor_map.find(movie) == actor_map.end()) {          

            		vector<string> temp_vec;                
            		temp_vec.push_back(actor_list.at(i).getActor());            
            		actor_map.insert(make_pair(movie, temp_vec));  
        	} 
        	else {					    
            		vector<string> temp_vec = actor_map[movie]; 
            		temp_vec.push_back(actor_list.at(i).getActor()); 	    
            		actor_map[movie] = temp_vec; 		    
        	} 
    	} 

	// Create a GraphAdjList and add vertices corresponding to each actor
	// Your code here...
	
	
	for (auto act : movie_map)
	{
		graph.addVertex(act.first,"");	
		graph.getVertex(act.first)->getVisualizer()->setColor(Color("red"));
	}
	

	// For every actor pair, find the movies that they have in common
	// If they have movies in common, insert an edge between the two actor vertices with edge data as 
	//number of movies that they have in common
	// Your code here...
	int numMovs = 0;

	for (auto actor : movie_map)
	{
		for(auto actor2 : movie_map)
		{
			numMovs = 0;
			if (actor == actor2)
			{
				 continue;
			}
			for (auto movie : actor.second)
			{						
				for (auto movie2 : actor2.second)
				{		
					if (movie == movie2)
					{
						numMovs++;
					}
				}
			} 
			if (numMovs != 0)
			{
				graph.addEdge(actor.first, actor2.first, numMovs);				
			}
		}
	}


	int count = 0;
	for (unordered_map<string, vector<string>>::iterator actors = movie_map.begin(); actors != movie_map.end(); actors++) // displays total number of actors
	{
		count++;
	}
	cout << "number of total actors: " << count << endl; 


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////End of Old Code////////////////////////////////////////////////////////////////////////
	// Display graph
	// Your code here...
	
	
	
	topThree();

	string ac1, ac2; // actors for degree of seperation
	unordered_map<string,vector<string>>::const_iterator got1; // iter for the first actor map
	unordered_map<string,vector<string>>::const_iterator got2; // iter for the second actor map
	string ac3, ac4; // actors to find minimum sum
	unordered_map<string,vector<string>>::const_iterator got3;
	unordered_map<string,vector<string>>::const_iterator got4;

	// MAIN PART OF THE PROGRAM //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (got1 == movie_map.end() || got2 == movie_map.end()) // This is the part of the program that takes the input from the user for Degree of seperation
	{	
		cout << "Enter Actor 1: " << endl;
		cin >> ac1;
		cout << "Enter Actor 2: " << endl;
		cin >> ac2;
		got1 = movie_map.find(ac1);
		got2 = movie_map.find(ac2);	
		if (got1 == movie_map.end() || got2 == movie_map.end()) // makes sure the 
		{
			cout << "Actor not found: enter again." << endl; 
		}
		else
			cout << "Degree of Separation is " << findSeparation(ac1, ac2) << endl;
			cout << endl;
	}


	cout << endl;
	
	while (got3 == movie_map.end() || got4 == movie_map.end()) // Calls the function to find minimum sum of movies to watch
	{	
		cout << "Enter Actor 1: " << endl;
		cin >> ac3;
		cout << "Enter Actor 2: " << endl;
		cin >> ac4;
		got3 = movie_map.find(ac3);
		got4 = movie_map.find(ac4);	
		if (got3 == movie_map.end() || got4 == movie_map.end())
		{
			cout << "Actor not found: enter again." << endl;
		}
		else
		cout <<  "The minimum number of movies to watch between is " << ac3 << " and " << ac4 << " is " << findNumMovies(ac3,ac4) << endl;
	}	
	
	// SLelement<Edge<string>>  *head = graph.getAdjacencyList().at("Clark_Gable");
	// for (SLelement<Edge<string>> *sle = head; sle != nullptr;
	// 	sle = sle->getNext() ) {	
	// 	string term_vertex = sle->getValue().getVertex();
	// 	//cout << term_vertex << " : " << sle->getValue().getWeight() << endl;
	// }
			
		
	
	Bridges::setDataStructure(&graph); // builds the visualization
	Bridges::visualize();
	
	return 0;
}
//////////////////END OF MAIN ////////////////////////////////////////////////////////////////////////////////////////////////////


string getEnvVar(string const & key) {
    char * val = getenv( key.c_str() );
    return val == NULL ? string("") : string(val);
}


// Finds the degree of seperation between two input actors
int findSeparation(string actor1, string actor2)
{
	
	queue<string> q1, q2; // sets up two queues to hold names of actors
	unordered_map<string, int> degreeOfSeparation; // holds the name of actor and a degree
	string currentActor; // holds current actor
	int count = 0;
	bool isFirstQueue = true; // starts the function in first que
	bool finished = false; // disables the output

	if (actor1 == actor2) // if actors are the same then the result is zero
	{
		return 0;
	}

	for (auto actors : movie_map) // iterates through all actors in movie map
	{
		degreeOfSeparation.emplace(actors.first, -1); //  sets the degree to -1 to start because this also marks whether the actor has been visited yet
	}

	q1.push(actor1); // pushes the first actor into the first queue to start the loop
	degreeOfSeparation[actor1] = 0; //  sets the first actors degree to himself to 0
	
	while (finished == false)
	{
		++count; // always iterates the count when the queues flop
		while ((q1.size() > 0 && isFirstQueue == true) || (q2.size() > 0 && isFirstQueue == false)) // makes sure there is something in the queue
		{
			if (isFirstQueue == true) // when in the first queue
			{
				currentActor = q1.front(); // saves the current actor being looked at from the selected queue
				q1.pop(); // removes the top
			}
			else //  when in the second queue
			{
				currentActor = q2.front(); // saves the current actor being looked at from the selected queue
				q2.pop(); // removes the top
			}
	
			SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(currentActor); // starts at a vertex and looks at every branch
			for (SLelement<Edge<string>> *sle = head; sle != nullptr;
				sle = sle->getNext() ) {
				string term_vertex = sle->getValue().getVertex();
				if (term_vertex != currentActor) // makes sure not looking back at same actor
					{
						if (degreeOfSeparation[term_vertex] == -1) // if the vertex isnt checked
						{
							degreeOfSeparation[term_vertex] = count; // sets the degree of that vertex to current count
							if (isFirstQueue == true)
							{
								q2.push(term_vertex); // pushes all the branches of the current actor onto the opposite queue
							}
							else // if in the second queue
							{
								q1.push(term_vertex); // pushes all the branches of the current actor onto the opposite queue
							}
							if (term_vertex == actor2) // once the second actor is found in either queue it exits the program.
								finished = true;
						}
					}
				}		
		}
		if (isFirstQueue == true) //  flops the queues
		{
			isFirstQueue = false;
		}
		else
			isFirstQueue = true;
	}

	return degreeOfSeparation[actor2]; // returns the int value of the degree of seperation for actor 2.
	
}

//////////////////////////////////////PART 2//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//finds the top 3 actors that have acted with the most other actors
void topThree()
{	
	int count = 0;
	int most_costars = 0;
	int second_most_costars = 0;
	int third_most_costars = 0;

	string fir, sec, third;

	unordered_map<string, int> top_three_map;
	for (auto actors : movie_map) // finds all actors in the movie list
	{
		top_three_map.emplace(actors.first, 0); // makes a map of all actors with 0
	}
	for (auto it = top_three_map.begin(); it != top_three_map.end(); it++) // steps through the map 
	{
		count = 0;
		SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(it->first); // sets the vertex being checked
		for (SLelement<Edge<string>> *sle = head; sle != nullptr; sle = sle->getNext() ) // counts all the 
		{
			string term_vertex = sle->getValue().getVertex();
			Element<string> *el = graph.getVertex(term_vertex);			
			count++;
		}
		it->second = count; // sets an iterator to the count
		if (it->second > most_costars) // sets three tiers of most costars after it finds the counts
		{
			most_costars = it->second;
			fir = it->first;
			continue; // if it doesnt beat the most it goes to next
		}
		if (it->second > second_most_costars)
		{
			second_most_costars = it->second;
			sec = it->first; // if it doesnt beat the second it goes to next
			continue;		
		}
		if (it->second > third_most_costars)
		{
			third_most_costars = it->second; // if it beats the third
			third = it->first;
		}
	}
	cout << "\nTop 3: " << endl; //  outputs the top three
	cout << fir << " : " << most_costars << endl;
	cout << sec << " : " << second_most_costars << endl;
	cout << third << " : " << third_most_costars << endl;
	cout << endl;
}



///////////////////////////////////////PART 3//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//finds every movie an two actors have been in together and returns that.
//If two actors have not been in a movie together it will find the shortest path between the two actors.
 int findNumMovies(string actor1, string actor2)
{
	queue<string> q1, q2, q3; // sets up three queues 2 for flopping one for the path of actors
	unordered_map<string, int> shortestPath; // map of shortest paths
	unordered_multimap<string, string> prevActor; // map of actors visited
	unordered_map<string, bool> visited; // map of visited or not visited
	string currentActor; // current actor
	int count = 0;
	int temp = 0;
	string nextActor;
	bool isFirstQueue = true;	
	bool finished = false;

	if (actor1 == actor2) // if actors are the same
	{
		for (auto mov : movie_map[actor1])
		{
			count++;
		}
		graph.getVertex(actor1)->getVisualizer()->setColor(Color("green"));
		return count;
	}
	graph.getVertex(actor1)->getVisualizer()->setColor(Color("black")); // Colors the nodes in the path
	graph.getVertex(actor2)->getVisualizer()->setColor(Color("black"));
	
	for (auto actors : movie_map) // sets all the distances to -1 for flag
	{
		shortestPath.emplace(actors.first, -1);
	}

	q1.push(actor1); // puts the first actor in first queue to start
	shortestPath.emplace(actor1, 0); // sets shortest path from actor 1 to 0
	
	while (finished == false) // while not finished
	{
		while ((q1.size() > 0 && isFirstQueue == true) || (q2.size() > 0 && isFirstQueue == false)) // while there is something in the queue
		{
			if (isFirstQueue == true) // flops between two queues
			{
				currentActor = q1.front(); // saves the actor to current 
				q1.pop();
			}
			else
			{
				currentActor = q2.front(); // saves the actor to current
				q2.pop();
			}
			
			SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(currentActor); // goes through all the branches of the current actor
			for (SLelement<Edge<string>> *sle = head; sle != nullptr;
				sle = sle->getNext() ) {
				string term_vertex = sle->getValue().getVertex();
				if (term_vertex != currentActor) // makes sure not looking back at same node
				{
					if ((shortestPath[term_vertex] >= shortestPath[currentActor] + sle->getValue().getWeight()) || shortestPath[term_vertex] == -1) // if the shortest path
					{
						shortestPath[term_vertex] = shortestPath[currentActor] + sle->getValue().getWeight(); // sets the shortest path if shorter
						
						if (isFirstQueue == true) // 
						{
							q2.push(term_vertex); // pushes actors into the flipping queues
						}
						else
						{
							q1.push(term_vertex);
						}
						if (term_vertex == actor2) // if the second actor is found exits
							finished = true;
						prevActor.emplace(currentActor, term_vertex); // ties the current actor to the previous actor for pathing
					}	
				}
			}		
		}
		if (isFirstQueue == true) // flops the queues
		{
			isFirstQueue = false;
		}
		else
			isFirstQueue = true;
	}
	
	/*
	for (auto it = prevActor.begin(); it != prevActor.end(); it++) {
				cout << it->first << " : " << it->second << endl;
			}
	
	for (auto iter = shortestPath.begin(); iter != shortestPath.end(); iter++)
	{
		cout << iter->first << " : " << iter->second << endl;
	}
	*/
	
	unordered_multimap<string,string>::iterator it;
	
	finished = false; // resets finished
		
	q3.push(actor2); // pushes actor 2 into the queue
	while (finished == false) 
	{
		while(q3.size() > 0) // while the queue has something in it
		{
			nextActor = q3.front(); // sets the front of the queue and pops
			
			q3.pop(); // pops
			graph.getVertex(nextActor)->getVisualizer()->setColor(Color("black")); // makes the connecting actors black dots
			
			for (it = prevActor.begin(); it != prevActor.end(); it++) // steps through all of the possible paths that were found
			{
				if (it->first == actor1){ // once it finds the second actor

					finished = true;
				}
				else if (it->second == nextActor) //  if not the second actor finds next actor in path
				{
					cout << it->second << endl;
					q3.push(it->first); // pushes the actor
				}
			}
		}
	}
	cout << nextActor << endl; // couts the last actor in the queue
	cout << actor2 << endl; //  couts the final destination


	return shortestPath[actor2]; // returns the shortest path as an int
	
}


