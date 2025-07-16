#include"FunctionalBlock.h"
#include<iostream>
#include<string>
#include<vector>

void FunctionalBlock::get_info(){
    std::cout << "FB Name: " << FunctionalBlock::name << "; " << "FB Type: " << FunctionalBlock::type << '\n';
    if(FunctionalBlock::params.size() != 0){
        std::cout << "FB Parameters:" << '\n';
        for(int i = 0; i < FunctionalBlock::params.size(); i++){
            std::cout << "Name: " << FunctionalBlock::params[i].first << "; " << "Value: " << FunctionalBlock::params[i].second << '\n';
        }
    }
    
    std::cout << std::endl;
}
