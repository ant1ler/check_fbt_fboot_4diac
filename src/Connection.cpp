#include"Connection.h"
#include<iostream>

void Connection::get_info(){
    std::cout << "FB " << start << " connected to FB " << end << '\n';
}