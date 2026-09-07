#pragma once
#include "Screen.cpp"
#include <vector>
#include <string>
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    Cinema(string name) {
        this->name = name;
    }

    void addScreen(const Screen& screen) 
    {
        screens.push_back(screen);
    }

    string getName() 
    { 
        return name; 
    }
    vector<Screen>& getScreens() 
    {
         return screens; 
    }
};
