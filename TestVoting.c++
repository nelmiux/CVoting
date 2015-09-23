// --------------------------------
// projects/voting/TestVoting.c++
// Copyright (C) 2015
// --------------------------------


// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

int k = 0;
bool f = true;
vector<string> tie_list;
vector<Candidate> c;

// -----------
// TestVoting
// -----------

// ----
// read
// ----

TEST(VotingFixture, read_1) {
    c.resize(0);
    k = 0;
    istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nzhenya\n1 2 3 4\n1 2 3 4\n1 2 3 4\n3 4 2 1\n2 1 3 4\n2 1 3 4\n");
    int vots = voting_read(r, c, k, f);
    ASSERT_EQ(6, vots);
    ASSERT_EQ(4, k);
    ASSERT_EQ(c[0].name.compare("John Doe"), 0);
    ASSERT_EQ(c[1].name.compare("Jane Smith"), 0);
    ASSERT_EQ(c[2].name.compare("Sirhan Sirhan"), 0);
    ASSERT_EQ(c[3].name.compare("zhenya"), 0);}

TEST(VotingFixture, read_2) {
    c.resize(0);
    k = 0;
    istringstream r("\n2\nA\nB\n1 2\n2 1\n2 1\n2 1\n");
    int vots = voting_read(r, c, k, f);
    ASSERT_EQ(4, vots);
    ASSERT_EQ(2, k);
    ASSERT_EQ(c[0].name.compare("A"), 0);
    ASSERT_EQ(c[1].name.compare("B"), 0);}

TEST(VotingFixture, read_3) {
    c.resize(0);
    k = 0;
    istringstream r("\n3\nA\nB\nC\n1 2 3\n2 3 1\n1 3 2\n");
    int vots = voting_read(r, c, k, f);
    ASSERT_EQ(3, vots);
    ASSERT_EQ(3, k);
    ASSERT_EQ(c[0].name.compare("A"), 0);
    ASSERT_EQ(c[1].name.compare("B"), 0);
    ASSERT_EQ(c[2].name.compare("C"), 0);}


TEST(VotingFixture, read_4) {
    c.resize(0);
    k = 0;
    istringstream r("\n1\nA\n1\n1\n1\n1\n1\n1\n1\n");
    int vots = voting_read(r, c, k, f);
    ASSERT_EQ(7, vots);
    ASSERT_EQ(1, k);
    ASSERT_EQ(c[0].name.compare("A"), 0);}

TEST(VotingFixture, read_5) {
    c.resize(0);
    istringstream r("\n3\nA\nB\nC\n2 3 1\n3 1 2\n2 3 1\n2 1 3\n1 3 2\n3 1 2\n3 2 1\n3 2 1\n");
    int vots = voting_read(r, c, k, f);
    ASSERT_EQ(8, vots);
    ASSERT_EQ(3, k);
    ASSERT_EQ(c[0].name.compare("A"), 0);
    ASSERT_EQ(c[1].name.compare("B"), 0);
    ASSERT_EQ(c[2].name.compare("C"), 0);}

TEST(VotingFixture, read_6) {
    c.resize(0);
    k = 0;
    istringstream r("\n4\nA\nB\nC\nD\n2 4 3 1\n2 3 1 4\n1 4 2 3\n3 4 2 1\n4 2 3 1\n3 4 2 1\n3 2 1 4\n3 1 2 4\n");
    int vots = voting_read(r, c, k, f);
    ASSERT_EQ(8, vots);
    ASSERT_EQ(4, k);
    ASSERT_EQ(c[0].name.compare("A"), 0);
    ASSERT_EQ(c[1].name.compare("B"), 0);
    ASSERT_EQ(c[2].name.compare("C"), 0);
    ASSERT_EQ(c[3].name.compare("D"), 0);}


TEST(VotingFixture, read_7) {
    c.resize(0);
    k = 0;
    istringstream r("\n2\nA\nB\n1 2\n2 1\n2 1\n1 2\n");
    int vots = voting_read(r, c, k, f);
    ASSERT_EQ(4, vots);
    ASSERT_EQ(2, k);
    ASSERT_EQ(c[0].name.compare("A"), 0);
    ASSERT_EQ(c[1].name.compare("B"), 0);
    }

// ----
// eval
// ----

TEST(VotingFixture, eval_1) {
    c.resize(0);
    tie_list.resize(0);
    string name_ = "";
    k = 0;
    istringstream r("\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nzhenya\n1 2 3 4\n1 2 3 4\n1 2 3 4\n3 4 2 1\n2 1 3 4\n2 1 3 4\n");
    int vots = voting_read(r, c, k, f);
    bool b = voting_eval (c, k, vots, name_, tie_list);
    ASSERT_EQ(true, b);
    ASSERT_EQ(tie_list[0].compare("John Doe"), 0);
    ASSERT_EQ(tie_list[1].compare("Jane Smith"), 0);}

TEST(VotingFixture, eval_2) {
    c.resize(0);
    tie_list.resize(0);
    string name_ = "";
    k = 0;
    istringstream r("\n2\nA\nB\n1 2\n2 1\n2 1\n2 1\n");
    int vots = voting_read(r, c, k, f);
    bool b = voting_eval (c, k, vots, name_, tie_list);
    ASSERT_EQ(true, b);
    ASSERT_EQ(name_, "B");}

TEST(VotingFixture, eval_3) {
    c.resize(0);
    tie_list.resize(0);
    string name_ = "";
    k = 0;
    istringstream r("\n4\nA\nB\nC\nD\n2 4 3 1\n2 3 1 4\n1 4 2 3\n3 4 2 1\n4 2 3 1\n3 4 2 1\n3 2 1 4\n3 1 2 4\n");
    int vots = voting_read(r, c, k, f);
    bool b = voting_eval (c, k, vots, name_, tie_list);
    ASSERT_EQ(true, b);
    ASSERT_EQ(tie_list[0].compare("B"), 0);
    ASSERT_EQ(tie_list[1].compare("C"), 0);}

TEST(VotingFixture, eval_4) {
    c.resize(0);
    tie_list.resize(0);
    string name_ = "";
    k = 0;
    istringstream r("\n1\nA\n1\n1\n1\n1\n1\n1\n1\n");
    int vots = voting_read(r, c, k, f);
    bool b = voting_eval (c, k, vots, name_, tie_list);
    ASSERT_EQ(true, b);
    ASSERT_EQ(name_, "A");}

// -----
// print
// -----

TEST(VotingFixture, print_1) {
    tie_list.resize(0);
    ostringstream w;
    string name_ = "A";
    voting_print(w, name_, tie_list);
    ASSERT_EQ("A\n", w.str());}

TEST(VotingFixture, print_2) {
    tie_list.resize(0);
    ostringstream w;
    string name_ = "B";
    voting_print(w, name_, tie_list);
    ASSERT_EQ("B\n", w.str());}

TEST(VotingFixture, print_3) {
    tie_list.resize(0);
    ostringstream w;
    string name_ = "John Doe";
    voting_print(w, name_, tie_list);
    ASSERT_EQ("John Doe\n", w.str());}

TEST(VotingFixture, print_4) {
    tie_list.resize(0);
    string name_ = "";
    tie_list.push_back("Jane Smith");
    tie_list.push_back("Sirhan Sirhan");
    tie_list.push_back("zhenya");
    ostringstream w;
    voting_print(w, name_, tie_list);
    ASSERT_EQ("Jane Smith\nSirhan Sirhan\nzhenya\n", w.str());}

TEST(VotingFixture, print_5) {
    tie_list.resize(0);
    string name_ = "";
    tie_list.push_back("A");
    tie_list.push_back("B");
    ostringstream w;
    voting_print(w, name_, tie_list);
    ASSERT_EQ("A\nB\n", w.str());}

// -----
// solve
// -----

TEST(VotingFixture, solve_1) {
    c.resize(0);
    tie_list.resize(0);
    istringstream r("1\n\n2\nA\nB\n1 2\n2 1\n2 1\n2 1\n");
    ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("B\n", w.str());}

TEST(VotingFixture, solve_2) {
    c.resize(0);
    tie_list.resize(0);
    istringstream r("3\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nzhenya\n1 2 3 4\n1 2 3 4\n1 2 3 4\n3 4 2 1\n2 1 3 4\n2 1 3 4\n\n4\nA\nB\nC\nD\n2 4 3 1\n2 3 1 4\n1 4 2 3\n3 4 2 1\n4 2 3 1\n3 4 2 1\n3 2 1 4\n3 1 2 4\n\n1\nA\n1\n1\n1\n1\n1\n1\n1\n");
    ostringstream w;
    voting_solve (r, w);
    ASSERT_EQ("John Doe\nJane Smith\n\nB\nC\n\nA\n", w.str());}
