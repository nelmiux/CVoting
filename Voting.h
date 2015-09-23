/** --------------------------
 * projects/voting/Voting.h
 * Copyright (C) 2015
 * --------------------------*/

#ifndef Voting_h
#define Voting_h

/** --------
 * includes
 * --------*/

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>

using namespace std;

struct Voter {
    int idx;
    vector<int> vote;
};

struct Candidate {
    string name;
    vector<Voter> votes;
    bool eliminated;
};

/** ------------
 * voting_read
 * ------------*/

/**	read an istream block and form a vector of Candidates struct, 
 *   with their names and a vector of size o their number of votes 
 *   stored on a vote structure with their index (allowing to follow 
 *   their position). k is the number of candidates reading from the 
 *   file, and returning voters as a number of voters. */
int voting_read (istream& r, vector<Candidate>& c, int& k, bool& f); 

/** ------------
 * voting_eval
 * ------------*/

/**	read vector of Candidates struct, with their names and a vector 
 *   of size o their number of votes stored on a vote structure with 
 *   their index (allowing to follow their position). Then, check if
 *   there is a candidate with more than 50% of the voters, if not, 
 *   check if there is a tie, if not, proceed to eliminate the 
 *   candidate/s with the min number of votes, and then made the
 *   the adition of the vote lose for the candidate eliminated before
 *   to the candidate higher ranked for this voter. This process 
 *   continue recursively until there is a winner or there is a tie */
bool voting_eval (vector<Candidate>& c, int& k, int& voters, string& name_, vector<string>& tie_list);

/** -------------
 * voting_print
 * -------------*/

/**  read the name of the winner and the tie list.
 *   In the case the name of the winner exist, print it.
 *   If not then it was a tie and print the list from tie_list.
 *   output the final result to the writer */
void voting_print (ostream& w, string& name_, vector<string>& tie_list);

/** -------------
 * voting_solve
 * -------------*/

/**  @param r an istream
 *   @param w an ostream
 *   read n as the number of test cases from the first line on 
 *   RunVoting.in. Then, call to voting_read, which read each 
 *   case data, then call to voting_eval, which process the data,
 *   and then call voting_print which output the data to 
 *   RunVoting.out. 
 *   c is an vector of Candidate struct */
void voting_solve (istream& r, ostream& w);

#endif // Voting_h
