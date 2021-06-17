// PL homework: hw2
// lr_parser.cc

#include <assert.h>

#include <iostream>
#include <vector>
#include <stdio.h>

#include "lr_parser.h"

#define DISABLE_LOG false
#define LOG \
    if (DISABLE_LOG) {} else std::cerr

using namespace std;

int transform(int a){
    int x;
    x = a*(-1) - 1;
    return x;
}

bool BuildLRParser(const std::vector<LRTableElement>& elements,
                   const std::vector<LRRule>& rules,
                   LRParser* lr_parser) {
    //initialization
    for(int i = 0; i < states; i++){
        for(int j = 0; j < 6; j++){
            lr_parser->act[i][j].action = 0;
            lr_parser->act[i][j].next = 0;
        }
    }
    for(int i = 0; i < states; i++){
        for(int j = 0; j < 3; j++){
            lr_parser->go[i][j] = 0;
        }
    }
    for(int i = 0; i < states; i++){
        lr_parser->rule[i].id = 0;
        lr_parser->rule[i].lhs_symbol = 0;
        lr_parser->rule[i].num_rhs = 0;
    }
    //build actiontable
    for(int i = 0; i < elements.size(); i++){
        switch(elements[i].symbol){
            case 73:
                lr_parser->act[elements[i].state][0].action = elements[i].action;
                lr_parser->act[elements[i].state][0].next = elements[i].next_state;
                break;
            case 43:
                lr_parser->act[elements[i].state][1].action = elements[i].action;
                lr_parser->act[elements[i].state][1].next = elements[i].next_state;
                break;
            case 42:
                lr_parser->act[elements[i].state][2].action = elements[i].action;
                lr_parser->act[elements[i].state][2].next = elements[i].next_state;
                break;
            case 40:
                lr_parser->act[elements[i].state][3].action = elements[i].action;
                lr_parser->act[elements[i].state][3].next = elements[i].next_state;
                break;
            case 41:
                lr_parser->act[elements[i].state][4].action = elements[i].action;
                lr_parser->act[elements[i].state][4].next = elements[i].next_state;
                break;
            case 36:
                lr_parser->act[elements[i].state][5].action = elements[i].action;
                lr_parser->act[elements[i].state][5].next = elements[i].next_state;
                break;
        }
    }
    //build gototable
    for(int i = 0; i < elements.size(); i++){
        if(elements[i].action == 4){
            switch(elements[i].symbol){
                case -1:
                    lr_parser->go[elements[i].state][0] = elements[i].next_state;
                    break;
                case -2:
                    lr_parser->go[elements[i].state][1] = elements[i].next_state;
                    break;
                case -3:
                    lr_parser->go[elements[i].state][2] = elements[i].next_state;
                    break;
            }
        }
    }
    
    //build ruletable
    for(int i = 0; i < rules.size(); i++){
        lr_parser->rule[i].id = rules[i].id;
        lr_parser->rule[i].lhs_symbol = rules[i].lhs_symbol;
        lr_parser->rule[i].num_rhs = rules[i].num_rhs;
    }
    return true;
    
  return false;
}

bool RunLRParser(const LRParser& lr_parser, const std::string& str) {
    int size;
    int temp;
    int dir;
    vector<int> stack;
    vector<int> input;
    stack.clear();
    stack.push_back(0);
    for(int i = 0; i < str.size(); i++){
        input.push_back(str[i]);
    }
    
    while(1){
        if(input[0] == 73){
            if(lr_parser.act[stack[stack.size() - 1]][0].action == 1){
                size = stack.size();
                stack.push_back(input[0]);
                input.erase(input.begin());
                stack.push_back(lr_parser.act[stack[size - 1]][0].next);
            } else if(lr_parser.act[stack[stack.size() - 1]][0].action == 2){
                size = stack.size();
                temp = stack[size - 1];
                for(int i = 0; i < (lr_parser.rule[lr_parser.act[temp][0].next - 1].num_rhs) * 2; i++){
                    stack.pop_back();
                }
                dir = stack[stack.size() - 1];
                stack.push_back(lr_parser.rule[lr_parser.act[temp][0].next - 1].lhs_symbol);
                stack.push_back(lr_parser.go[dir][transform(lr_parser.rule[lr_parser.act[temp][0].next - 1].lhs_symbol)]);
            } else if(lr_parser.act[stack[stack.size() - 1]][0].action == 3){
                return true;
            } else if(lr_parser.act[stack[stack.size() - 1]][0].action == 0){
                return false;
            }
        } else if(input[0] == 43){
            if(lr_parser.act[stack[stack.size() - 1]][1].action == 1){
                size = stack.size();
                stack.push_back(input[0]);
                input.erase(input.begin());
                stack.push_back(lr_parser.act[stack[size - 1]][1].next);
            } else if(lr_parser.act[stack[stack.size() - 1]][1].action == 2){
                size = stack.size();
                temp = stack[size - 1];
                for(int i = 0; i < (lr_parser.rule[lr_parser.act[temp][1].next - 1].num_rhs) * 2; i++){
                    stack.pop_back();
                }
                dir = stack[stack.size() - 1];
                stack.push_back(lr_parser.rule[lr_parser.act[temp][1].next - 1].lhs_symbol);
                stack.push_back(lr_parser.go[dir][transform(lr_parser.rule[lr_parser.act[temp][1].next - 1].lhs_symbol)]);
            } else if(lr_parser.act[stack[stack.size() - 1]][1].action == 3){
                return true;
            } else if(lr_parser.act[stack[stack.size() - 1]][1].action == 0){
                return false;
            }
        } else if(input[0] == 42){
            if(lr_parser.act[stack[stack.size() - 1]][2].action == 1){
                size = stack.size();
                stack.push_back(input[0]);
                input.erase(input.begin());
                stack.push_back(lr_parser.act[stack[size - 1]][2].next);
            } else if(lr_parser.act[stack[stack.size() - 1]][2].action == 2){
                size = stack.size();
                temp = stack[size - 1];
                for(int i = 0; i < (lr_parser.rule[lr_parser.act[temp][2].next - 1].num_rhs) * 2; i++){
                    stack.pop_back();
                }
                dir = stack[stack.size() - 1];
                stack.push_back(lr_parser.rule[lr_parser.act[temp][2].next - 1].lhs_symbol);
                stack.push_back(lr_parser.go[dir][transform(lr_parser.rule[lr_parser.act[temp][2].next - 1].lhs_symbol)]);
            } else if(lr_parser.act[stack[stack.size() - 1]][2].action == 3){
                return true;
            } else if(lr_parser.act[stack[stack.size() - 1]][2].action == 0){
                return false;
            }
        } else if(input[0] == 40){
            if(lr_parser.act[stack[stack.size() - 1]][3].action == 1){
                size = stack.size();
                stack.push_back(input[0]);
                input.erase(input.begin());
                stack.push_back(lr_parser.act[stack[size - 1]][3].next);
            } else if(lr_parser.act[stack[stack.size() - 1]][3].action == 2){
                size = stack.size();
                temp = stack[size - 1];
                for(int i = 0; i < (lr_parser.rule[lr_parser.act[temp][3].next - 1].num_rhs) * 2; i++){
                    stack.pop_back();
                }
                dir = stack[stack.size() - 1];
                stack.push_back(lr_parser.rule[lr_parser.act[temp][3].next - 1].lhs_symbol);
                stack.push_back(lr_parser.go[dir][transform(lr_parser.rule[lr_parser.act[temp][3].next - 1].lhs_symbol)]);
            } else if(lr_parser.act[stack[stack.size() - 1]][3].action == 3){
                return true;
            } else if(lr_parser.act[stack[stack.size() - 1]][3].action == 0){
                return false;
            }
        } else if(input[0] == 41){
            if(lr_parser.act[stack[stack.size() - 1]][4].action == 1){
                size = stack.size();
                stack.push_back(input[0]);
                input.erase(input.begin());
                stack.push_back(lr_parser.act[stack[size - 1]][4].next);
            } else if(lr_parser.act[stack[stack.size() - 1]][4].action == 2){
                size = stack.size();
                temp = stack[size - 1];
                for(int i = 0; i < (lr_parser.rule[lr_parser.act[temp][4].next - 1].num_rhs) * 2; i++){
                    stack.pop_back();
                }
                dir = stack[stack.size() - 1];
                stack.push_back(lr_parser.rule[lr_parser.act[temp][4].next - 1].lhs_symbol);
                stack.push_back(lr_parser.go[dir][transform(lr_parser.rule[lr_parser.act[temp][4].next - 1].lhs_symbol)]);
            } else if(lr_parser.act[stack[stack.size() - 1]][4].action == 3){
                return true;
            } else if(lr_parser.act[stack[stack.size() - 1]][4].action == 0){
                return false;
            }
        } else if(input[0] == 36){
            if(lr_parser.act[stack[stack.size() - 1]][5].action == 1){
                size = stack.size();
                stack.push_back(input[0]);
                input.erase(input.begin());
                stack.push_back(lr_parser.act[stack[size - 1]][5].next);
            } else if(lr_parser.act[stack[stack.size() - 1]][5].action == 2){
                size = stack.size();
                temp = stack[size - 1];
                for(int i = 0; i < (lr_parser.rule[lr_parser.act[temp][5].next - 1].num_rhs) * 2; i++){
                    stack.pop_back();
                }
                dir = stack[stack.size() - 1];
                stack.push_back(lr_parser.rule[lr_parser.act[temp][5].next - 1].lhs_symbol);
                stack.push_back(lr_parser.go[dir][transform(lr_parser.rule[lr_parser.act[temp][5].next - 1].lhs_symbol)]);
            } else if(lr_parser.act[stack[stack.size() - 1]][5].action == 3){
                return true;
            } else if(lr_parser.act[stack[stack.size() - 1]][5].action == 0){
                return false;
            }
        } else {
            return false;
        }
    }

    
  return false;
}

