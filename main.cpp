#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "Parser.cpp"

using namespace std;

int main() {
    string all_text = "";
    
    char buf[255];
    while(not (cin.eof())) { 
        cin.getline(buf, 255);
        all_text+= string(buf);
    }
    
    cout <<Parser(all_text).run();

    return 0;   
}

