#pragma once
#include <iostream>
#include <string>
using namespace std;


enum type_of_lex {
    LEX_NULL, //пустая лексема    
    LEX_LPAREN,    // (
    LEX_RPAREN,    // )
    LEX_NOT,       // !
    LEX_OR,        // |
    LEX_AND,       // &
    LEX_IMP,       // ->
    LEX_SBSTR,     // ( inside )
    LEX_VAR,       // variable
};


class Lex {
    type_of_lex t_lex; // type
    string v_lex;      // value

public: 
    Lex (type_of_lex t = LEX_NULL, string value = "") {
        t_lex = t;
        v_lex = value;
    }

    type_of_lex get_type() const { return t_lex; }
    string get_value() const { return v_lex; }

    friend ostream & operator <<(ostream & out, const Lex & l ) {
        out<<'('<<l.t_lex<<','<<l.v_lex << ')'<<endl;
        return out; 
    }
};
