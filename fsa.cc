// PL homework: hw1
// fsa.cc

#include <iostream>
#include <stdio.h>
#include <deque>

#include "fsa.h"

#define DISABLE_LOG true
#define LOG \
    if (DISABLE_LOG) {} else std::cerr

using namespace std;

void epsilon(const FiniteStateAutomaton& fsa, vector<int>& store, int state, char str, int pass){
    int block;
    for(int i = 0; i < MAX_SIZE; i++){
        if(fsa.states[state - 1][i].next == 0)
            break;
        if(fsa.states[state - 1][i].edge.size() == 0){
            for(int k = 0; k < store.size(); k++){
                if(store[i] == state)
                    block++;
            }
            if(block == 0)
                epsilon(fsa, store, fsa.states[state - 1][i].next, str, pass);
        }
        if(fsa.states[state - 1][i].edge.size() != 0 && pass == 0){
            if(str == fsa.states[state - 1][i].edge.at(0)){
                store.push_back(fsa.states[state - 1][i].next);
            }
        }
    }
}
void epsiloninit(const FiniteStateAutomaton& fsa, vector<int>& store, int state){
    int block;
    store.push_back(state);
    for(int i = 0; i < MAX_SIZE; i++){
        if(fsa.states[state - 1][i].next == 0)
            break;
        if(fsa.states[state - 1][i].edge.size() == 0){
            for(int k = 0; k < store.size(); k++){
                if(store[i] == state)
                    block++;
            }
            if(block == 0)
                epsiloninit(fsa, store, fsa.states[state - 1][i].next);
        }
    }
}


bool RunFSA(const FiniteStateAutomaton& fsa, const string& str) {
  // Implement this function.
    int size;
    int cnt;
    int pass;
    vector<int> store;
    store.clear();
    store.push_back(fsa.init);
    for(int i = 0; i < MAX_SIZE; i++){
        if(fsa.states[fsa.init - 1][i].next == 0)
            break;
        if(fsa.states[fsa.init - 1][i].edge.size() == 0){
            epsiloninit(fsa, store, fsa.states[fsa.init - 1][i].next);
            
        }
    }
    
    for(int i = 0; i < str.size(); i++){
        size = store.size();
        cnt = 0;
        pass = 0;
        for(int j = 0; j < size; j++){
            for(int k = 0; k < MAX_SIZE; k++){
                if(fsa.states[store[0] - 1][k].next == 0)
                    break;
                if(fsa.states[store[0] - 1][k].edge.size() == 0){
                    epsilon(fsa, store, fsa.states[store[0] - 1][k].next, str[i], pass);
                }
                if(fsa.states[store[0] - 1][k].edge.size() != 0){
                    if(str[i] == fsa.states[store[0] - 1][k].edge.at(0)){
                        store.push_back(fsa.states[store[0] - 1][k].next);
                        pass++;
                        for(int m = 0; m < MAX_SIZE; m++){
                            if(fsa.states[store.size() - 1][m].next == 0)
                                break;
                            if(fsa.states[store.size() - 1][m].edge.size() == 0){
                                epsilon(fsa, store, fsa.states[store.size() - 1][m].next, str[i], pass);
                            }
                        }
                    }
                }
            }
            store.erase(store.begin());
        }
        for(int l = 0; l < MAX_SIZE; l++){
            for(int m = 0; m < MAX_SIZE; m++){
                if(fsa.states[l][m].edge.size() != 0){
                    if(str[i] == fsa.states[l][m].edge.at(0))
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
                if (store[i] == fsa.finish[j]) {
                    return true;
                }
            }
		}
	}

  return false;
}

bool BuildFSA(const std::vector<FSATableElement>& elements,
              const std::vector<int>& accept_states,
              FiniteStateAutomaton* fsa) {
  // Implement this function.
	int k;
	for (int i = 0; i < MAX_SIZE; i++) {
		fsa->finish[i] = 0;
		for (int j = 0; j < 10; j++) {
			fsa->states[i][j].next = 0;
			fsa->states[i][j].edge = " ";
		}
	}
    
	for (int i = 0; i < accept_states.size() - 1; i++) {
		fsa->finish[i] = accept_states[i];
	}

	for (int i = 0; i < MAX_SIZE; i++) {
		k = 0;
		for (int j = 0; j < elements.size(); j++) {
			if (elements[j].state == i + 1) {
				fsa->states[i][k].next = elements[j].next_state;
				fsa->states[i][k].edge = elements[j].str;
				k++;
			}
		}
	}
	return true;

  LOG << "num_elements: " << elements.size()
      << ", accept_states: " << accept_states.size() << endl;
  return false;
}

