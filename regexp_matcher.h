// PL homework: hw2
// regexp_matcher.h

#ifndef _PL_HOMEWORK_REGEXP_MATCHER_H_
#define _PL_HOMEWORK_REGEXP_MATCHER_H_
#define MAX_SIZE 30

#include <vector>
#include <string>

using namespace std;

struct state {
    int next;
    string edge;
};

struct RegExpMatcher {
  // Design your RegExpMatcher structure.
    int init;
    int num_state;
    state nfa[MAX_SIZE][MAX_SIZE];
    int finish[MAX_SIZE];
};

// Homework 1.3
bool BuildRegExpMatcher(const char* regexp, RegExpMatcher* regexp_matcher);

// Homework 1.3
bool RunRegExpMatcher(const RegExpMatcher& regexp_matcher, const char* str);

#endif  //_PL_HOMEWORK_REGEXP_MATCHER_H_

