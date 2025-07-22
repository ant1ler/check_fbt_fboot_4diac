#include"SysModel.h"
#include"FbootModel.h"
#include"Validate.cpp"
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<fstream>
#include<argparse/argparse.hpp>


int main(int argc, char* argv[]){

    // Создаем парсер аргументов
    argparse::ArgumentParser program("fboot_sys_comparator", "1.0");
    // Добавляем аргументы с флагами
    program.add_argument("-s", "--sys-file")
        .help("path to .sys file (required)")
        .required()
        .metavar("PATH");

    program.add_argument("-f", "--fboot-file")
        .help("path to .fboot file (required)")
        .required()
        .metavar("PATH");

    program.add_argument("-v", "--verbose")
        .help("enable verbose output")
        .default_value(false)
        .implicit_value(true);

    // Парсим аргументы
    program.parse_args(argc, argv);

    // Получаем значения аргументов
    std::string sys_filename = program.get<std::string>("--sys-file");
    std::string fboot_filename = program.get<std::string>("--fboot-file");
    bool verbose = program.get<bool>("--verbose");

    // Проверяем существование файлов
    auto file_exists = [](const std::string& path) {
        std::ifstream f(path);
        return f.good();
    };

    if (!file_exists(sys_filename)) {
        std::cerr << "Error: .sys file not found: " << sys_filename << std::endl;
        return 1;
    }

    if (!file_exists(fboot_filename)) {
        std::cerr << "Error: .fboot file not found: " << fboot_filename << std::endl;
        return 1;
    }


    SysModel sys;
    FbootModel fboot;

    sys.set_filename(sys_filename);
    sys.parse(sys.get_filename());
    sys.correction();

    fboot.set_filename(fboot_filename);
    fboot.parse(fboot.get_filename());
    fboot.correction();

    if (verbose) {
        std::cout << "Comparing files:\n";
        std::cout << "  SYS (-s):   " << sys_filename << "\n";
        sys.print_structure();
        std::cout << "  FBOOT (-f): " << fboot_filename << "\n\n";
        fboot.print_structure();
    }

    validate(fboot, sys);
}