// PL homework: hw2
// regexp_matcher.cc

#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "regexp_matcher.h"

void epsilon(const RegExpMatcher& regexp_matcher, vector<int>& store, int state, char str, int pass){
    int block;
    for(int i = 0; i < MAX_SIZE; i++){
        if(regexp_matcher.nfa[state - 1][i].next == 0)
            break;
        if(regexp_matcher.nfa[state - 1][i].edge.size() == 0){
            for(int k = 0; k < store.size(); k++){
                if(store[i] == state)
                    block++;
            }
            if(block == 0)
                epsilon(regexp_matcher, store, regexp_matcher.nfa[state - 1][i].next, str, pass);
        }
        if(regexp_matcher.nfa[state - 1][i].edge.size() != 0 && pass == 0){
            if(str == regexp_matcher.nfa[state - 1][i].edge.at(0)){
                store.push_back(regexp_matcher.nfa[state - 1][i].next);
            }
        }
    }
}
void epsiloninit(const RegExpMatcher& regexp_matcher, vector<int>& store, int state){
    int block;
    store.push_back(state);
    for(int i = 0; i < MAX_SIZE; i++){
        if(regexp_matcher.nfa[state - 1][i].next == 0)
            break;
        if(regexp_matcher.nfa[state - 1][i].edge.size() == 0){
            for(int k = 0; k < store.size(); k++){
                if(store[i] == state)
                    block++;
            }
            if(block == 0)
                epsiloninit(regexp_matcher, store, regexp_matcher.nfa[state - 1][i].next);
        }
    }
}


bool BuildRegExpMatcher(const char* regexp, RegExpMatcher* regexp_matcher) {
    //buildFSA
    
  return true;
}

bool RunRegExpMatcher(const RegExpMatcher& regexp_matcher, const char* str) {
    int size;
    int cnt;
    int pass;
    vector<int> store;
    vector<char> input;
    store.clear();
    for(int i = 0; i < (sizeof(str) / sizeof(str[0])); i++){
        input.push_back(str[i]);
    }
    store.push_back(regexp_matcher.init);
    for(int i = 0; i < MAX_SIZE; i++){
        if(regexp_matcher.nfa[regexp_matcher.init - 1][i].next == 0)
            break;
        if(regexp_matcher.nfa[regexp_matcher.init - 1][i].edge.size() == 0){
            epsiloninit(regexp_matcher, store, regexp_matcher.nfa[regexp_matcher.init - 1][i].next);
            
        }
    }
    
    for(int i = 0; i < input.size(); i++){
        size = store.size();
        cnt = 0;
        pass = 0;
        for(int j = 0; j < size; j++){
            for(int k = 0; k < MAX_SIZE; k++){
                if(regexp_matcher.nfa[store[0] - 1][k].next == 0)
                    break;
                if(regexp_matcher.nfa[store[0] - 1][k].edge.size() == 0){
                    epsilon(regexp_matcher, store, regexp_matcher.nfa[store[0] - 1][k].next, str[i], pass);
                }
                if(regexp_matcher.nfa[store[0] - 1][k].edge.size() != 0){
                    if(str[i] == regexp_matcher.nfa[store[0] - 1][k].edge.at(0)){
                        store.push_back(regexp_matcher.nfa[store[0] - 1][k].next);
                        pass++;
                        for(int m = 0; m < MAX_SIZE; m++){
                            if(regexp_matcher.nfa[store.size() - 1][m].next == 0)
                                break;
                            if(regexp_matcher.nfa[store.size() - 1][m].edge.size() == 0){
                                epsilon(regexp_matcher, store, regexp_matcher.nfa[store.size() - 1][m].next, str[i], pass);
                            }
                        }
                    }
                }
            }
            store.erase(store.begin());
        }
        for(int l = 0; l < MAX_SIZE; l++){
            for(int m = 0; m < MAX_SIZE; m++){
                if(regexp_matcher.nfa[l][m].edge.size() != 0){
                    if(str[i] == regexp_matcher.nfa[l][m].edge.at(0))
                        cnt++;
                }
            }
        }
    }
    
    if(cnt == 0)
        return false;
    
    for (int i = 0; i < store.size(); i++) {
        for (int j = 0; j < store.size(); j++) {
            if(store[i] != 0){
                if (store[i] == regexp_matcher.finish[j]) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

