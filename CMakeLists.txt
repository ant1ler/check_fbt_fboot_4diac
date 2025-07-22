cmake_minimum_required(VERSION 3.14)
project(CHECK_FBT_FBOOT_4DIAC)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем модуль FetchContent для управления зависимостями
include(FetchContent)

# Настройка и загрузка pugixml
FetchContent_Declare(
  pugixml
  GIT_REPOSITORY https://github.com/zeux/pugixml.git
  GIT_TAG v1.15
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")
set(PUGIXML_BUILD_TESTS OFF CACHE BOOL "Disable tests")
FetchContent_MakeAvailable(pugixml)

# Настройка и загрузка argparse
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG v3.2
)
FetchContent_MakeAvailable(argparse)

# Список исходных файлов проекта
set(SOURCES
    src/main.cpp
    src/Connection.cpp
    src/FunctionalBlock.cpp
    src/Resource.cpp
    src/SysModel.cpp
    src/Mapping.cpp
    src/FbootModel.cpp
)

# Список заголовочных файлов проекта
set(HEADERS
    include/Connection.h
    include/FunctionalBlock.h
    include/Resource.h
    include/SysModel.h
    include/Mapping.h
    include/FbootModel.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключаем необходимые библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE 
    pugixml
    argparse::argparse
)

# Указываем пути к заголовочным файлам проекта
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Опционально: установка выходного каталога для исполняемого файла
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)