#pragma once
#include <iostream>
#include <list>
#include <vector>

#include "Scanner.cpp"

using namespace std;

class Parser {
    Scanner S;
    Lex lex;
    string file;
    vector<Lex> tmp;

    string expression(int left, int right);
    string my_and(int left, int right);
    string my_or(int left, int right);
    string my_not(int left, int right);
    void fiin();
    int findr(type_of_lex t, int left, int right);
    int findl(type_of_lex t, int left, int right);

public:
    Parser(const string file) : S(file) {
        this->file = file;
        lex = Lex(LEX_AND, "");
    }

    string run() {
        fiin();
        return expression(0, tmp.size());
        
    } 

};

void Parser::fiin() {
    lex = S.get_lex();
    while (lex.get_type() != LEX_NULL) {        
        tmp.push_back(lex);
        lex = S.get_lex();
    }
}

int Parser::findr(type_of_lex t, int left, int right) {
    for (int i = right; i > left; i--) {
        if (tmp[i].get_type() == t) return i;
    }
    return -1;
}


int Parser::findl(type_of_lex t, int left, int right) {
    for (int i = left; i < right; i++) {
        if (tmp[i].get_type() == t) return i;
    }
    return -1;
}

string Parser::expression(int left, int right) {
    int lm = findl(LEX_IMP, left, right);
    if(lm == -1) {
        return my_or(left, right);
    } else {
        return ("(->," + my_or(left, lm-1) + "," + expression(lm+1, right) + ")");
    }
}

string Parser::my_or(int left, int right) {
    int lm = findr(LEX_OR, left, right);
    if(lm == -1) {
        return my_and(left, right);
    } else {
        return ("(|," + my_or(left, lm-1) + "," + my_and(lm+1, right) + ")");
    }
}

string Parser::my_and(int left, int right) {
    int lm = findr(LEX_AND, left, right);
    if(lm == -1) {
        return my_not(left, right);
    } else {
        return ("(&," + my_and(left, lm-1) + "," + my_not(lm+1, right) + ")");
    }
}

string Parser::my_not(int left, int right) {
    if (tmp[left].get_type() == LEX_NOT) {
        return ("(!," + my_not(left+1, right) + ")");
    } else if (tmp[left].get_type() == LEX_SBSTR) {
        return Parser(tmp[left].get_value()).run();
    } else if (tmp[left].get_type() == LEX_VAR) {
        return tmp[left].get_value();
    }
}