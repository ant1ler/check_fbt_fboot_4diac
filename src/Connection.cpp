#include"Connection.h"
#include<iostream>

void Connection::print_info(){
    std::cout  << start << " connected to " << end << '\n';
}