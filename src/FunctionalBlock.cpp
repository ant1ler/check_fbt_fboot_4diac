#include"FunctionalBlock.h"
#include<iostream>
#include<string>
#include<vector>

void FunctionalBlock::get_info(){
    std::cout << "FB Name: " << name << "; " << "FB Type: " << type << '\n';
    if(params.size() != 0){
        std::cout << "FB Parameters:" << '\n';
        for(int i = 0; i < params.size(); i++){
            std::cout << "Name: " << params[i].first << "; " << "Value: " << params[i].second << '\n';
        }
    }

    std::cout << "FB Resource: " << resource << std::endl;
    
    std::cout << std::endl;
}
