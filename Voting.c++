// ----------------------------
// projects/voting/Voting.c++
// Copyright (C) 2015
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector
#include <cctype>   // isprint

#include "Voting.h"

using namespace std;

// ------------
// voting_read
// ------------

int voting_read (istream& r, vector<Candidate>& c, int& k, bool& f) {
    /*  read an istream block and form a vector of Candidates struct, 
        with their names and a vector of size o their number of votes 
        stored on a vote structure with their index (allowing to follow 
        their position). k is the number of candidates reading from the 
        file, and returning voters as a number of voters. */

    string s;
    int voters = 0;
    
    int t = 0;
    char line_read[80];
    string line;
    if (f) getline(r, s);
    getline(r, s);
    istringstream is(s);
    is >> k;

    assert (k > 0);

    for (int i = 0; i < k; i++) {
        Candidate cand;
        r.getline(line_read, 80);
        string name(line_read);
        cand.name = name;
        cand.eliminated = false;
        cand.votes.resize(0);
        c.push_back(cand);
    }

    while (r.good()) {
        r.getline(line_read, 80);
        string line(line_read);
        if (!isprint(line[0])) break;
        istringstream is(line, istringstream::in);
        Voter v;
        v.idx = 0;
        for (int i = 0; i < k; i++) {
            is >> t;
            v.vote.push_back(t);

        } 
        c[v.vote[0] - 1].votes.push_back(v);

        voters++;  
    }
    
    assert (voters > 0);

    // eliminiting candidate with 0 vote.
    for (int i = 0; i < k; i++)
        if (c[i].votes.size() == 0) c[i].eliminated = true;

    return voters;
}

// ------------
// voting_eval
// ------------

bool voting_eval (vector<Candidate>& c, int& k, int& voters, string& name_, vector<string>& tie_list) {
    /*  read vector of Candidates struct, with their names and a vector 
        of size o their number of votes stored on a vote structure with 
        their index (allowing to follow their position). Then, check if
        there is a candidate with more than 50% of the voters, if not, 
        check if there is a tie, if not, proceed to eliminate the 
        candidate/s with the min number of votes, and then made the
        the adition of the vote lose for the candidate eliminated before
        to the candidate higher ranked for this voter. This process 
        continue recursively until there is a winner or there is a tie */

    vector <int> elim_idx;
    elim_idx.resize(0);
    int max_ = -1;
    int idx_max = 0;
    int min_ = voters;
        
    for (int i = 0; i < k; i++){
        if (!c[i].eliminated) {
            if (int(c[i].votes.size()) < min_) min_= c[i].votes.size();
            if (int(c[i].votes.size()) > max_) max_= c[i].votes.size();
        }
    }

    for (int i = 0; i < k; i++) if (max_ == (int(c[i].votes.size()))) idx_max = i;

    if (max_ > (voters + 1) / 2) {
        name_ = c[idx_max].name;
        return true;
    }

    if (min_ == max_) {
        for (int i = 0; i < k; i++){
            if (!c[i].eliminated)
                tie_list.push_back(c[i].name);
        }
        return true;
    }

    for (int i = 0; i < k; i++) {
        if (!c[i].eliminated && (int(c[i].votes.size())) == min_) {
            elim_idx.push_back(i);
            c[i].eliminated = true;
        }
    }  

    for (int i = 0; i < (int(elim_idx.size())); i++) {
        for (int j = 0; j < (int(c[elim_idx[i]].votes.size())); j++) {
            int idx = c[elim_idx[i]].votes[j].idx;     
            while (c[c[elim_idx[i]].votes[j].vote[idx] - 1].eliminated) idx += 1;
            c[c[elim_idx[i]].votes[j].vote[idx] - 1].votes.push_back(c[elim_idx[i]].votes[j]);
        }
    }

    return voting_eval (c, k, voters, name_, tie_list);
}


// -------------
// voting_print
// -------------

void voting_print (ostream& w, string& name_, vector<string>& tie_list) {
    /*  read the name of the winner and the tie list.
        In the case the name of the winner exist, print it.
        If not then it was a tie and print the list from tie_list.
        output the final result to the writer */

    if (name_.length() > 0) w << name_ << endl;
    else {
        for (int i = 0; i < (int(tie_list.size())); i++) 
            if (tie_list[i] != "") w << tie_list[i] << endl;
   }
   return;
}

// -------------
// voting_solve
// -------------

void voting_solve (istream& r, ostream& w) {
    /*  read n as the number of test cases from the first line on 
        RunVoting.in. Then, call to voting_read, which read each 
        case data, then call to voting_eval, which process the data,
        and then call voting_print which output the data to 
        RunVoting.out. 
        c is an vector of Candidate struct */

    string s;
    vector<string> tie_list;
    vector<Candidate> c;
    bool f = true;
    int n = 0;

    getline(r, s);
    if (!isprint(s[0])) w << "";

    istringstream is(s);
    is >> n;

    assert (n > 0);

    for (int i = 0; i < n; i++) {
        int k = 0;
        c.resize(0);

        int vots = voting_read(r, c, k, f);

        string name_ = "";

        tie_list.resize(0);

        voting_eval(c, k, vots, name_, tie_list);
        voting_print(w, name_, tie_list);

        f = false;
        if (i != n - 1) w << endl;
    }
    return;
}