#pragma once

#include<iostream>
#include<utility> 
#include<vector>
#include<string>

class FunctionalBlock{
public:  
    std::string name;
    std::string type;
    std::vector< std::pair<std::string, std::string> > params;
    std::string resource;

public:

    void get_info();
    
};
