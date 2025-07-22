#include"FbootModel.h"
#include<iostream>
#include <fstream>

void FbootModel::add_func_block(FunctionalBlock func_block){
    fb.push_back(func_block);
}

void FbootModel::add_resource(Resource res){
    resource.push_back(res);
}

void FbootModel::add_connection(Connection connect){
    connection.push_back(connect);
}

void FbootModel::print_structure(){

    std::cout << "Functional Blocks:" << std::endl;
    for(int i = 0; i < fb.size(); i++){
        fb[i].print_info();
    }
    std::cout  << std::endl;

    std::cout << "Resources:" << std::endl;
    for(int i = 0; i < resource.size(); i++){
        resource[i].print_info();
    }
    std::cout  << std::endl;

    std::cout << "Connections:" << std::endl;
    for(int i = 0; i < connection.size(); i++){
        connection[i].print_info();
    }
    std::cout  << std::endl;
}

Resource FbootModel::parse_resource(std::string line){
    Resource res;

    res.set_name(line.substr(line.find("FB Name") + 9, line.find("Type") - line.find("FB Name") - 11));
    res.set_type(line.substr(line.find("Type") + 6, line.rfind("/>") - line.find("Type") - 8));
    res.set_line(line);

    return res;
}

FunctionalBlock FbootModel::parse_create_fb(std::string line){
    FunctionalBlock fb;

    std::string res = "";
    for(int i = 0; i < line.find(";"); i++){
        res += line[i];
    }
    fb.set_resource(res);

    fb.set_name(line.substr(line.find("FB Name") + 9, line.find("Type") - line.find("FB Name") - 11));
    fb.set_type(line.substr(line.find("Type") + 6, line.rfind("/>") - line.find("Type") - 8));
    fb.set_fb_line(line);

    return fb;
}

void FbootModel::parse_write_connection(std::string line){
    std::string name = "";
    std::string value = "";
    std::string func_block = "";

    value = line.substr(line.find("Source") + 8, line.find("Destination") - line.find("Source") - 10);

    while(value.find("&apos;") != std::string::npos){
        value.replace(value.find("&apos;"), 6, "'");
    }
    while(value.find("&quot;") != std::string::npos){
        value.replace(value.find("&quot;"), 6, "\"");
    }

    if(value.find("16#") != std::string::npos){
        std::string hex = value.substr(value.find("16#") + 3, hex.size());
        int dec = 0;

        for(int i = 0; i < hex.size(); i++){
            int digit;
            if(hex[i] >= 'A' and hex[i] <= 'F'){
                digit = 10 + (hex[i] - 'A');
            }
            if(hex[i] >= '0' and hex[i] <= '9'){
                digit = hex[i] -'0';
            }

            dec = dec * 16 + digit;
        }
        std::string decimal = std::to_string(dec);
        value = decimal;
    }

    func_block = line.substr(line.find("Destination") + 13, line.rfind("/>") - line.find("Destination") - 15);

    name = func_block.substr(func_block.rfind(".") + 1, std::string::npos);

    func_block.erase(func_block.rfind("."), std::string::npos);

    for(int i = 0; i < fb.size(); i++){
        if(fb[i].get_name() == func_block){
            fb[i].push_params({name, value});
            fb[i].set_params_line(line);
        }
    }
}

Connection FbootModel::parse_create_connection(std::string line){
    Connection con;

    con.set_start(line.substr(line.find("Source") + 8, line.find("Destination") - line.find("Source") - 10));
    con.set_end(line.substr(line.find("Destination") + 13, line.rfind("/>") - line.find("Destination") - 15));
    con.set_line(line);


    return con;
}

void FbootModel::parse(std::string filename){
    std::ifstream file(filename);
    std::string line;
    int counter = 0;

    while(std::getline(file, line)){

        for(int i = 0; i < line.size(); i++){
            if(line[i] == '"'){
                line[i] = '/';
            }
        }

        if (line.empty() || line.find("Request") == 0) {
            continue;
        }

        if(line[0] == ';'){
            add_resource(parse_resource(line));
            continue;
        }

        else if(line.find("Action=/CREATE/><FB Name") != std::string::npos){
            add_func_block(parse_create_fb(line));
        }

        if(line.find("Action=/WRITE/><Connection") != std::string::npos){
            parse_write_connection(line);
        }

        if(line.find("Action=/CREATE/><Connection") != std::string::npos){
            add_connection(parse_create_connection(line));
        }

        if(line.find("Action=/START") != std::string::npos){counter++;}
    }

    if(counter != resource.size()) {flag_start = false;}
}

void FbootModel::correction(){
    std::vector<Connection> connect = connection;
    for(int i = 0; i < connect.size(); i++){
        if(connect[i].get_start().find("START") == std::string::npos){
            std::string fb_start_name;
            std::string fb_end_name;
            
            fb_start_name = connect[i].get_start().substr(0, connect[i].get_start().rfind("."));
            fb_end_name = connect[i].get_end().substr(0, connect[i].get_end().rfind("."));

            bool fb1 = false, fb2 = false;

            for(int j = 0; j < fb.size(); j++){
                if(fb[j].get_name() == fb_start_name) fb1 = true;
                if(fb[j].get_name() == fb_end_name) fb2 = true;
            }

            if(fb1 && fb2 == false){
                auto iter = connect.begin() + i;
                connect.erase(iter); 
            } 
        }
    }
    connection = connect;
}