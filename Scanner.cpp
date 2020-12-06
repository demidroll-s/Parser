#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <list>

#include "Lex.cpp"

using namespace std;

class Scanner
{
    enum state { START, IDENT, BR}; // состояния
    state CS;                       //текущее состояние
    char c;                         //текущий символ
    int index;
    string buf;
    string file;
    int depth;

    void add () {
        if(c != EOF) {
            buf += c;
        }
    }

    bool is_letter(char c);
    bool is_digit(char c);
    bool is_valid(char c);

    void gc();


public:
    Lex get_lex ();

    Scanner (const string file) {
        if(file == "") {
            printf ("Error file.\n");
            exit(1); 
        }
        this->file = file;
        index = 0;
        CS = START;
    }
};

void Scanner::gc() {
    if(index < file.length())
        c = file[index++];
    else 
        c = EOF;
}

bool Scanner::is_letter(char c) {
    if (((c >= 'A') && (c <= 'Z')) || (c == '\''))
        return true;
    else
        return false;
}

bool Scanner::is_digit(char c) {
    if ((c >= '0') && (c <= '9'))
        return true;
    else
        return false;
}

bool Scanner::is_valid(char c) {
    return c == ')' || c == '(' || isspace(c);
}

Lex Scanner::get_lex () {
    depth = 0;
    CS = START;
    gc();
    
    do {
        if(index > file.length()) {
            
            return Lex(LEX_NULL, "EOF");
        }
        if(c == EOF) {
            index++;
            c = 'a';
            if(buf == "") {
                return Lex(LEX_NULL, "EOF");
            }
            return Lex(LEX_VAR, buf);
        }
        
        switch (CS) {
            case START:
                if (isspace(c)) { 
                    gc();
                }
                else if (is_letter(c)) {
                    CS = IDENT;
                }
                else if ( c == '!' ) {
                    return Lex(LEX_NOT, "!");
                }
                else if (c == '|') {
                    return Lex(LEX_OR, "|");
                }
                else if (c == '&') {
                    return Lex(LEX_AND, "&");
                } 
                else if (c == '-') {
                    gc();
                    if(c == '>') {
                        return Lex(LEX_IMP, "->");
                    }
                    else {
                        return Lex(LEX_NULL, "ERROR");
                    }
                }
                else if (c == '(') {
                    depth++;
                    gc();
                    CS = BR;
                }
               
                break;

            case IDENT:
                if ((is_letter(c) || is_digit(c))) {
                    add ();
                    gc ();
                }
                else {
                    Lex tmp = Lex(LEX_VAR, buf);
                    buf = "";
                    index--;
                    return tmp;
                }
            
                break;
            case BR:
                if (c == '(') {
                    depth++;
                    add();
                    gc();
                    
                } 
                else if (c == ')') {
                    depth--;
                    gc();
                }
                else {
                    add();
                    gc();
                }

                if(depth == 0) {
                    Lex tmp = Lex(LEX_SBSTR, buf);
                    buf = "";
                    return tmp;
                }
                break;

        }
    }
    while (true);
}
