#include"SysModel.h"
#include<iostream>


void SysModel::add_func_block(FunctionalBlock func_block){
    fb.push_back(func_block);
}

void SysModel::add_resource(Resource res){
    resource.push_back(res);
}

void SysModel::add_connection(Connection connect){
    connection.push_back(connect);
}

void SysModel::add_mapping(Mapping mapp){
    mapping.push_back(mapp);
}

void SysModel::print_structure(){

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

    std::cout << "Mapping:" << std::endl;
    for(int i = 0; i < mapping.size(); i++){
        mapping[i].print_info();
    }
    std::cout  << std::endl;
}

FunctionalBlock SysModel::parse_fb(std::string project_name, pugi::xml_node fb_node){
    FunctionalBlock FB;

    FB.set_name(project_name + "App." + fb_node.attribute("Name").as_string());
    FB.set_type(fb_node.attribute("Type").as_string());

    for(pugi::xml_node param_node : fb_node.children("Parameter")){
        FB.push_params({param_node.attribute("Name").as_string(), param_node.attribute("Value").as_string()});
    }

    return FB;
}

Resource SysModel::parse_res(std::string device_name, pugi::xml_node res_node){
    Resource res;

    res.set_name(device_name + "." + res_node.attribute("Name").as_string());
    res.set_type(res_node.attribute("Type").as_string());

    return res;

}

Connection SysModel::parse_resource_connect(pugi::xml_node connect_node){
    Connection con;

    con.set_start(connect_node.attribute("Source").as_string());
    con.set_end(connect_node.attribute("Destination").as_string());

    return con;

}

Connection SysModel::parse_fb_connect(std::string project_name, pugi::xml_node connect_node){
    Connection con;

    con.set_start(project_name + "App." + connect_node.attribute("Source").as_string());
    con.set_end(project_name + "App." + connect_node.attribute("Destination").as_string());

    return con;

}

Mapping SysModel::parse_mapping(pugi::xml_node mapping_node){
    Mapping mapp;

    mapp.set_from(mapping_node.attribute("From").as_string());
    mapp.set_to(mapping_node.attribute("To").as_string());
    for(int i = 0; i < fb.size(); i++){
        if(fb[i].get_name() == mapp.get_from()){
            fb[i].set_resource(mapp.get_to());
        }
    }

    return mapp;
}

void SysModel::parse(std::string sys_filename){

    pugi::xml_document doc;
    doc.load_file(sys_filename.c_str());
    pugi::xml_node system_node = doc.child("System");
    std::string project_name = system_node.attribute("Name").as_string();

    pugi::xml_node app_node = system_node.child("Application");
    pugi::xml_node sub_app_node = app_node.child("SubAppNetwork");

    for(pugi::xml_node node : sub_app_node.children("FB")){
        add_func_block(parse_fb(project_name, node));
        
    }

    pugi::xml_node event_con_node = sub_app_node.child("EventConnections");
    for(pugi::xml_node node : event_con_node.children("Connection")){
        add_connection(parse_fb_connect(project_name, node));
    }

    pugi::xml_node data_con_node = sub_app_node.child("DataConnections");
    for(pugi::xml_node node : data_con_node.children("Connection")){
        add_connection(parse_fb_connect(project_name, node));
    }

    pugi::xml_node device_node = system_node.child("Device");
    std::string device_name = device_node.attribute("Name").as_string();

    for(pugi::xml_node node : device_node.children("Resource")){
        add_resource(parse_res(device_name, node));

        pugi::xml_node fb_network_node = node.child("FBNetwork");
        pugi::xml_node dev_even_con = fb_network_node.child("EventConnections");
        for(pugi::xml_node node_temp : dev_even_con.children("Connection")){
            add_connection(parse_resource_connect(node_temp));
        }
    }

    for(pugi::xml_node mapp_node : system_node.children("Mapping")){
        add_mapping(parse_mapping(mapp_node));
    }
}
