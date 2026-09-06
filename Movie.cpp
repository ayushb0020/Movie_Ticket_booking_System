// SOLID: Single Responsibility Principle (SRP
#pragma once

#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration; 

public:
    Movie(string title, string language, int duration) 
    {
        this->title = title;
        this->language = language;
        this->duration = duration;
    }

    string getTitle()    
    { 
        return title;
    }
    string getLanguage() 
    { 
        return language; 
    }
    int getDuration()    
    { 
        return duration; 
    }
};
