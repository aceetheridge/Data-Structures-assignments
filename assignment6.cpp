// Aaron Etheridge 800936351
// ECGR 3090 Data Structures and Algorythms
// Assignment 6 Hash tables and Anagrams
// This program needs to be compiled using g++ -std=c++11 assignment6.cpp -o test1

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<string>> findAnagrams(const vector<string>& dict);

int main()
{
  vector<string> word_list = {"debitcard", "elvis", "silent", "badcredit", "lives", "freedom", "listen", "levis"};
   vector<vector<string>> result = findAnagrams(word_list);
   for (auto anagrams: result) {
      for (auto words: anagrams)
         cout << words << " ";
         cout << endl;
    }
   return 0;
}

vector<vector<string>> findAnagrams(const vector<string>& dict)
{
     vector<vector<string>> bucket;             //bucket that contains the words that match the same key
     unordered_map<string,vector<string>> hash; //Unordered map that will link the keys to the buckets
     string temp;                               //holds temp string value to sort so dict isnt changed
     
     for (auto words : dict){
            temp = words;                       //stores the temp before sorting
            sort(words.begin(),words.end());    //sorts from be gining to end of vector in alphabetical order
            hash[words].push_back(temp);        //creates a new hash based on what words is
            
     }
     
     for (auto list: hash){
            bucket.push_back(list.second);      //steps through hash table and assigns anagrams to the keys
     }
     
     return bucket;
}
