#include"SysModel.h"
#include"FbootModel.h"
#include<iostream>

int main(){
    SysModel sys;
    FbootModel fboot;

    pugi::xml_document doc;
    if (!doc.load_file("/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1.sys")) {
        std::cerr << "Ошибка загрузки XML!" << std::endl;
        return 0;
    }

    std::string sys_filename = "/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1.sys";
    sys.set_filename(sys_filename);
    sys.parse(sys.get_filename());
    sys.print_structure();

    std::cout << std::endl;

    std::string fboot_filename = "/home/ant1ler/check_fbt_fboot_4diac/build/mai_test1_FORTE_PC.fboot";
    fboot.set_filename(fboot_filename);
    fboot.parse(fboot.get_filename());
    fboot.print_structure();
}