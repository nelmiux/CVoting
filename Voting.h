// --------------------------
// projects/voting/Voting.h
// Copyright (C) 2015
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>

using namespace std;

#define MAX_CANDIDATES 20
#define MAX_VOTERS     1000

struct Candidate {
    string name;
    int total_votes;
    bool eliminated;
    int votes[MAX_CANDIDATES];
    vector<vector<int>> prev;
};


// ------------
// voting_read
// ------------

/*	read an istream block and form an array of Candidates struct, 
    with their names and their vector data representing their number of 
    votes per preference positions, how many votes on first, second, etc.
    in case of three candidates the positions per preference will be 0, 1, 2
    where 0 is first, 1 second and 2 third choice.
    where k is the number of candidates reading from the file*/
int voting_read (istream& r, Candidate c[], int& k, bool f); 

// ------------
// voting_eval
// ------------

/*	read an array of Candidates struct, with their names and their vector 
    data representing their number of votes per preference positions, how 
    many votes on first, second, etc. e.g. in case of three candidates the 
    positions per preference will be 0, 1, 2 where 0 is first, 1 second and 
    2 third choice. 
    return a vector of winners*/
vector<string> voting_eval (Candidate c[], int& k, int voters, vector<string> v, string& name);

// -------------
// voting_print
// -------------

/*  read a vector of winners
    output the final result to the writer*/
void voting_print (ostream& w, vector<string> v, string& name);

// -------------
// voting_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve (istream& r, ostream& w);

#endif // Voting_h
