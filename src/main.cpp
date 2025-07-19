#include"SysModel.h"
#include"FbootModel.h"
#include<iostream>

void validate(FbootModel fboot, SysModel sys){

    std::vector<FunctionalBlock> fb_fboot = fboot.get_fb();
    std::vector<FunctionalBlock> fb_sys = sys.get_fb();
    bool fb_validate = false;

    for(int i = 0; i < fb_fboot.size(); i++){
        for(int j = 0; j < fb_sys.size(); j++){
            if(fb_fboot[i].get_name() == fb_sys[j].get_name()){
                if(fb_fboot[i].get_type() == fb_sys[j].get_type()){
                    if(fb_fboot[i].get_params() == fb_sys[j].get_params()){
                        if(fb_fboot[i].get_resource() == fb_sys[j].get_resource().substr(fb_sys[j].get_resource().find(".") + 1, std::string::npos)){

                            std::cout << "Fboot" << std::endl << fb_fboot[i].get_name() << " " << fb_fboot[i].get_type() << std::endl;
                            auto iter_fboot = fb_fboot.begin() + i;
                            fb_fboot.erase(iter_fboot);

                            std::cout << "Sys" << std::endl << fb_sys[j].get_name() << " " << fb_sys[j].get_type() << std::endl;
                            auto iter_sys = fb_sys.begin() + j;
                            fb_sys.erase(iter_sys);

                        }
                    }
                }
            }
        }
    }
    if(fb_fboot.size() == 0 and fb_sys.size() == 0) {fb_validate = true;}


    std::vector<Resource> resource_fboot = fboot.get_resource();
    std::vector<Resource> resource_sys = sys.get_resource();
    bool resource_validate = false;

    for(int i = 0; i < resource_fboot.size(); i++){
        for(int j = 0; j < resource_sys.size(); j++){
            if(resource_fboot[i].get_name() == resource_sys[j].get_name().substr(resource_sys[j].get_name().find(".") + 1, std::string::npos)){
                if(resource_fboot[i].get_type() == resource_sys[j].get_type()){

                    std::cout << "Fboot" << std::endl << resource_fboot[i].get_name() << " " << resource_fboot[i].get_type() << std::endl;
                    auto iter_fboot = resource_fboot.begin() + i;
                    resource_fboot.erase(iter_fboot);

                    std::cout << "Sys" << std::endl << resource_sys[j].get_name() << " " << resource_sys[j].get_type() << std::endl;
                    auto iter_sys = resource_sys.begin() + j;
                    resource_sys.erase(iter_sys);

                }
            }
        }
    }
    if(resource_fboot.size() == 0 and resource_sys.size() == 0) {resource_validate = true;}

    std::vector<Connection> connection_fboot = fboot.get_connection();
    std::vector<Connection> connection_sys = sys.get_connection();
    bool connection_validate = false;
    std::cout << "Connection" << std::endl;
    for(int i = 0; i < connection_fboot.size(); i++){
        for(int j = 0; j < connection_sys.size(); j++){
            if(connection_fboot[i].get_start() == connection_sys[j].get_start()){
                if(connection_fboot[i].get_end() == connection_sys[j].get_end()){

                    std::cout << "Fboot" << std::endl << connection_fboot[i].get_start() << " " << connection_fboot[i].get_end() << std::endl;
                    auto iter_fboot = connection_fboot.begin() + i;
                    connection_fboot.erase(iter_fboot);

                    std::cout << "Sys" << std::endl << connection_sys[j].get_start() << " " << connection_sys[j].get_end() << std::endl;
                    auto iter_sys = connection_sys.begin() + j;
                    connection_sys.erase(iter_sys);
                    break;

                }
            }
        }
    }
    if(connection_fboot.size() == 0 and connection_sys.size() == 0) {connection_validate = true;}

    if(fb_validate and resource_validate and connection_validate){
        std::cout << "Fboot-файл совпадает с sys-файлом" << std::endl;
    }
    else{
        std::cout << "Fboot" << std::endl << fb_fboot.size() << resource_fboot.size() << connection_fboot.size() << std::endl;
        std::cout << "Sys" << std::endl << fb_sys.size() << resource_sys.size() << connection_sys.size() << std::endl;
        std::cout << "Fboot-файл не совпадает с sys-файлом" << std::endl;
    } 
}

int main(){
    SysModel sys;
    FbootModel fboot;

    pugi::xml_document doc;
    if (!doc.load_file("/home/ant1ler/check_fbt_fboot_4diac/files/mai_test1.sys")) {
        std::cerr << "Ошибка загрузки XML!" << std::endl;
        return 0;
    }

    std::string sys_filename = "/home/ant1ler/check_fbt_fboot_4diac/files/mai_test1.sys";
    sys.set_filename(sys_filename);
    sys.parse(sys.get_filename());
    //sys.correction();
    sys.print_structure();

    std::cout << std::endl;

    std::string fboot_filename = "/home/ant1ler/check_fbt_fboot_4diac/files/mai_test1_FORTE_PC.fboot";
    fboot.set_filename(fboot_filename);
    fboot.parse(fboot.get_filename());
    //fboot.correction();
    fboot.print_structure();

    validate(fboot, sys);
}