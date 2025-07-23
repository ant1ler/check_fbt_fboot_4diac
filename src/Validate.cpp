#include"SysModel.h"
#include"FbootModel.h"
#include<iostream>

#include "SysModel.h"
#include "FbootModel.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "SysModel.h"
#include "FbootModel.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

void validate(const FbootModel& fboot, const SysModel& sys) {
    bool isValid = true;
    bool sectionValid = true;
    
    auto printSectionHeader = [](const std::string& title) {
        std::cout << "\n=== " << title << " ===\n";
    };

    // 1. Сравнение функциональных блоков
    printSectionHeader("Functional Blocks Comparison");
    sectionValid = true;
    const auto& fboot_fbs = fboot.get_fb();
    const auto& sys_fbs = sys.get_fb();

    // Проверка FB из SYS, которых нет в FBOOT
    for (const auto& fb_sys : sys_fbs) {
        bool found = false;
        for (const auto& fb_fboot : fboot_fbs) {
            if (fb_sys.get_name() == fb_fboot.get_name()) {
                found = true;
                if (fb_sys.get_type() != fb_fboot.get_type()) {
                    std::cout << "Mismatch in FB type:\n";
                    std::cout << "FBOOT: " << fb_fboot.get_fb_line() << "\n";
                    std::cout << "SYS: <FB Name=\"" << fb_sys.get_name().substr(fb_sys.get_name().find(".") + 1, fb_sys.get_name().size()) 
                              << "\" Type=\"" << fb_sys.get_type() << "...>\n";
                    isValid = sectionValid = false;
                }
                break;
            }
        }
        if (!found) {
            std::cout << "FB missing in FBOOT (present in SYS):\n";
            std::cout << "SYS: <FB Name=\"" << fb_sys.get_name().substr(fb_sys.get_name().find(".") + 1, fb_sys.get_name().size()) 
                      << "\" Type=\"" << fb_sys.get_type() << "...>\n";
            isValid = sectionValid = false;
        }
    }

    // Проверка FB из FBOOT, которых нет в SYS
    for (const auto& fb_fboot : fboot_fbs) {
        bool found = false;
        for (const auto& fb_sys : sys_fbs) {
            if (fb_fboot.get_name() == fb_sys.get_name()) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "FB missing in SYS (present in FBOOT):\n";
            std::cout << "FBOOT: " << fb_fboot.get_fb_line() << "\n";
            isValid = sectionValid = false;
        }
    }

    if (sectionValid) {
        std::cout << "All functional blocks match - OK\n";
    }

    // 2. Сравнение параметров FB
    printSectionHeader("Parameters Comparison");
    sectionValid = true;

    for (const auto& fb_sys : sys_fbs) {
        for (const auto& fb_fboot : fboot_fbs) {
            if (fb_sys.get_name() == fb_fboot.get_name()) {
                // Проверка параметров из SYS
                for (const auto& param_sys : fb_sys.get_params()) {
                    bool paramFound = false;
                    for (const auto& param_fboot : fb_fboot.get_params()) {
                        if (param_sys.first == param_fboot.first) {
                            paramFound = true;
                            if (param_sys.second != param_fboot.second) {
                                std::cout << "Mismatch in parameter values:\n";
                                std::cout << "FBOOT: " << fb_fboot.get_params_line() << "\n";
                                std::cout << "SYS: <Parameter Name=\"" << param_sys.first 
                                          << "\" Value=\"" << param_sys.second << "...>\n";
                                isValid = sectionValid = false;
                            }
                            break;
                        }
                    }
                    if (!paramFound) {
                        std::cout << "Parameter missing in FBOOT (present in SYS):\n";
                        std::cout << "SYS: <Parameter Name=\"" << param_sys.first 
                                  << "\" Value=\"" << param_sys.second << "...>\n";
                        isValid = sectionValid = false;
                    }
                }

                // Проверка параметров из FBOOT, которых нет в SYS
                for (const auto& param_fboot : fb_fboot.get_params()) {
                    bool paramFound = false;
                    for (const auto& param_sys : fb_sys.get_params()) {
                        if (param_fboot.first == param_sys.first) {
                            paramFound = true;
                            break;
                        }
                    }
                    if (!paramFound) {
                        std::cout << "Parameter missing in SYS (present in FBOOT):\n";
                        std::cout << "FBOOT: " << fb_fboot.get_params_line() << "\n";
                        isValid = sectionValid = false;
                    }
                }
                break;
            }
        }
    }

    if (sectionValid) {
        std::cout << "All parameters match - OK\n";
    }

    // 3. Сравнение соединений
    printSectionHeader("Connections Comparison");
    sectionValid = true;
    const auto& fboot_conn = fboot.get_connection();
    const auto& sys_conn = sys.get_connection();

    // Проверка соединений из SYS, которых нет в FBOOT
    for (const auto& conn_sys : sys_conn) {
        bool found = false;
        for (const auto& conn_fboot : fboot_conn) {
            if (conn_sys.get_start() == conn_fboot.get_start() && 
                conn_sys.get_end() == conn_fboot.get_end()) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Connection missing in FBOOT (present in SYS):\n";
            std::cout << "SYS: <Connection Source=\"" << conn_sys.get_start().substr(conn_sys.get_start().find(".") + 1, conn_sys.get_start().size())
                      << "\" Destination=\"" << conn_sys.get_end().substr(conn_sys.get_end().find(".") + 1, conn_sys.get_end().size()) << "...>\n";
            isValid = sectionValid = false;
        }
    }

    // Проверка соединений из FBOOT, которых нет в SYS
    for (const auto& conn_fboot : fboot_conn) {
        bool found = false;
        for (const auto& conn_sys : sys_conn) {
            if (conn_fboot.get_start() == conn_sys.get_start() && 
                conn_fboot.get_end() == conn_sys.get_end()) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Connection missing in SYS (present in FBOOT):\n";
            std::cout << "FBOOT: " << conn_fboot.get_line() << "\n";
            isValid = sectionValid = false;
        }
    }

    if (sectionValid) {
        std::cout << "All connections match - OK\n";
    }

    // 4. Сравнение ресурсов
    printSectionHeader("Resources Comparison");
    sectionValid = true;
    const auto& fboot_res = fboot.get_resource();
    const auto& sys_res = sys.get_resource();

    // Проверка ресурсов из SYS, которых нет в FBOOT
    for (const auto& res_sys : sys_res) {
        bool found = false;
        std::string sysResName = res_sys.get_name();
        size_t dotPos = sysResName.find_last_of('.');
        std::string sysResNameShort = (dotPos != std::string::npos) ? 
                                    sysResName.substr(dotPos + 1) : sysResName;
        
        for (const auto& res_fboot : fboot_res) {
            if (res_fboot.get_name() == sysResNameShort) {
                found = true;
                if (res_fboot.get_type() != res_sys.get_type()) {
                    std::cout << "Mismatch in resource type:\n";
                    std::cout << "FBOOT: " << res_fboot.get_line() << "\n";
                    std::cout << "SYS: <Resource Name=\"" << sysResNameShort 
                              << "\" Type=\"" << res_sys.get_type() << "...>\n";
                    isValid = sectionValid = false;
                }
                break;
            }
        }
        if (!found) {
            std::cout << "Resource missing in FBOOT (present in SYS):\n";
            std::cout << "SYS: <Resource Name=\"" << sysResNameShort 
                      << "\" Type=\"" << res_sys.get_type() << "...>\n";
            isValid = sectionValid = false;
        }
    }

    // Проверка ресурсов из FBOOT, которых нет в SYS
    for (const auto& res_fboot : fboot_res) {
        bool found = false;
        for (const auto& res_sys : sys_res) {
            std::string sysResName = res_sys.get_name();
            size_t dotPos = sysResName.find_last_of('.');
            std::string sysResNameShort = (dotPos != std::string::npos) ? 
                                        sysResName.substr(dotPos + 1) : sysResName;
            
            if (res_fboot.get_name() == sysResNameShort) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Resource missing in SYS (present in FBOOT):\n";
            std::cout << "FBOOT: " << res_fboot.get_line() << "\n";
            isValid = sectionValid = false;
        }
    }

    if (sectionValid) {
        std::cout << "All resources match - OK\n";
    }

    // Итоговый вывод
    printSectionHeader("Validation Summary");
    if (isValid) {
        std::cout << "Validation PASSED: All elements match - OK\n";
    } else {
        std::cout << "Validation FAILED: Found differences between models\n";
    }
}