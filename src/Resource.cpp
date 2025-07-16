#include"Resource.h"

#include<iostream>
#include<string>
#include<vector>


void Resource::get_info(){
    std::cout << "Resource Name: " << Resource::name << ";" << " Resource Type: " << Resource::type << '\n';
}
