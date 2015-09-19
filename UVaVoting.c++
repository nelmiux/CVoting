// --------------------------
// projects/voting/Voting.h
// Copyright (C) 2015
// --------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
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

/*  read an istream block and form an array of Candidates struct, 
    with their names and their vector data representing their number of 
    votes per preference positions, how many votes on first, second, etc.
    in case of three candidates the positions per preference will be 0, 1, 2
    where 0 is first, 1 second and 2 third choice.
    where k is the number of candidates reading from the file*/
int voting_read (istream& r, Candidate c[], int& k, bool f); 

// ------------
// voting_eval
// ------------

/*  read an array of Candidates struct, with their names and their vector 
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


void initCandidatesArray (Candidate c[]) {
    for (int i = 0; i < 20; i++) {
        c[i].name = "";
        c[i].total_votes = 0;
        c[i].eliminated = false;
        for (int pos = 0; pos < MAX_CANDIDATES; pos++)
            c[i].votes[pos] = 0;
        c[i].prev.resize(0);
    }
}


// ------------
// voting_read
// ------------

int voting_read (istream& r, Candidate c[], int& k, bool f) {
    /*  read an istream block and form an array of Candidates struct, 
        with their names and their vector data representing their number of 
        votes per preference positions, how many votes on first, second, etc.
        in case of three candidates the positions per preference will be 0, 1, 2
        where 0 is first, 1 second and 2 third choice.
        where k is the number of candidates reading from the file*/
    string s;
    int pos = 0;
    int t = 0;
    int voters = 0;
    int prev;
    if (f) getline(r, s);
    getline(r, s);
    istringstream is(s);
    is >> k;
    for (int i = 0; i < k; i++) {
        getline(r, c[i].name);
        c[i].prev.resize(k);
        for (int j = 0; j < k; j++) c[i].prev[j].push_back(-1);
    }
    getline(r, s);
    while (s.length() > 1) {
        istringstream is(s);
        while(is >> t) {
            int i = t - 1;
            c[i].votes[pos] = c[i].votes[pos] + 1;
            if (pos == 0) c[i].total_votes = c[i].votes[pos];
            else {
                for (int p = 0; p < k; p++) {
                    if (c[i].prev[pos][p] == -1) c[i].prev[pos][p] = prev;
                    //cout << c[i].prev[pos][p] << " ";
                    break;
                }
                    
            }
            //cout << i << " ";
            prev = i;
            pos++;
        }
        pos = 0;
        voters++;
        getline(r, s);   
    }
    return voters;
}

bool winners (Candidate c[], int& k, int& voters, string& name) {
    bool b = false;
    for (int i = 0; i < k; i++) {
        if (c[i].total_votes > ((voters + 1) / 2)) {
            b = true;
            name = c[i].name;
            break;
            //cout << c[i].name;
        }
        //cout << c[i].total_votes << " ";
    }
    return b;
}


// ------------
// voting_eval
// ------------

void voting_eval (Candidate c[], int& k, int voters, string win_list[], string& name) {
    /*  read an array of Candidates struct, with their names and their vector 
        data representing their number of votes per preference positions, how 
        many votes on first, second, etc. e.g. in case of three candidates the 
        positions per preference will be 0, 1, 2 where 0 is first, 1 second and 
        2 third choice. 
        return a vector of winners*/
    int pos = 0;
    bool b = false;
    name = "";
    int e, last_votes;
    while (!b) {
        e = 0;
        last_votes = 0;
        for (pos = 0; pos < k; pos++) {
            int min = 99999;
            for (int i = 0; i < k; i++) if ((pos != 0) && (!c[i].eliminated)) c[i].total_votes = c[i].total_votes + c[i].votes[pos];
            b = winners(c, k, voters, name);
            if (b) {
                //cout << name << endl;
                return;
            }
            for (int i = 0; i < k; i++) if ((c[i].total_votes != 0) && (c[i].total_votes < min) && (!c[i].eliminated)) min = c[i].total_votes;
            for (int i = 0; i < k; i++) {
                if (((c[i].total_votes == 0) || (c[i].total_votes == min)) && (!c[i].eliminated)) {
                    c[i].eliminated = true;
                    e++;
                    last_votes = c[i].total_votes;
                    //cout << v[0];
                    if (pos != 0) {
                        for (int j =0; j < int(c[i].prev[pos].size()); j++) {
                            if ((c[i].prev[pos][j] != -1) && (c[c[i].prev[pos][j]].eliminated)) {
                                c[i].votes[pos] = c[i].votes[pos] + 1;
                                //cout << c[i].prev[pos][j] << " " << i;
                            }
                        }
                    }
                }
            }
            if (e >= k) {
                for (int i = 0; i < k; i++) {
                    if (last_votes == c[i].total_votes) 
                        win_list[i] = (c[i].name);
                }
                b = true;
                break;
            }
        }

        /*for(int l =  0; l < int(v.size()); l++) 
            cout << v[l] << endl;*/
    }
    //for (int i = 0; i < int(v.size()); i++) cout << v[i] << "\n";
    return;
}


// -------------
// voting_print
// -------------

void voting_print (ostream& w, string win_list[], string& name) {
    /*  read a vector of winners
        output the final result to the writer*/
    if (name.length() > 0) w << name << endl;
    else {
        for(int i =  0; i < MAX_CANDIDATES; i++) 
            if (win_list[i] != "") w << win_list[i] << endl;
   }
}

// -------------
// voting_solve
// -------------

void voting_solve (istream& r, ostream& w) {
    /*  n is the number of text cases readed from the first line on RunVoting.in
        The max the number of candidates is 20 + 1, in order to start on 1
        c is an array of candidates by text cases
        */
    Candidate c[20];
    string name = "";
    string s;
    string t;
    string win_list[MAX_CANDIDATES];
    bool f = true;
    int n = 0;
    getline(r, s);
    if (s.empty()) w << "";
    istringstream is(s);
    is >> n;
    for (int i = 0; i < n; i++) {
        int k = 0;
        for (int j = 0; j < MAX_CANDIDATES; j++)
            win_list[j] = "";
        initCandidatesArray (c);
        int vots = voting_read(r, c, k, f);
        voting_eval(c, k, vots, win_list, name);
        //if (v.size() > 0) cout << v[0];
        voting_print(w, win_list, name);
        f = false;
        w << endl;
    }
}

// ----
// main
// ----

int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}