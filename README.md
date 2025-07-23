# check_fbt_fboot_4diac

The project was created as part of a student internship at RTSoft.  
It is used to compare .sys and .fboot files, which is important for further correct work with them.  
The project is implemented as a console application and accepts several required parameters as input.

## Installation

For the project to work correctly, C++11 or higher must be installed.  
After installing C++, go to the directory where you want to place the project and run:  
```commandline
git clone https://github.com/ant1ler/check_fbt_fboot_4diac
```
Next, go to the /check_fbt_fboot_4diac/ directory to get started.

## Usage

When you have moved to the desired directory, assemble the project, to do this, write in the terminal:
```commandline
mkdir build
cd build
cmake ..
make
```
Next, to launch the project, write in the terminal:
```commandline
./CHECK_FBT_FBOOT_4DIAC -s /your_path_to_file.sys -f /your_path to_file.fboot
```
Instead of the -s and -f arguments, you can use --sys-file and --fboot-file, respectively. The functionality of the program will not change in any way.  
Also, you can write -v or --verbose at the end of the line, and then the program will output the contents to the terminal.sys and .fboot files.  
Example:
```commandline
./CHECK_FBT_FBOOT_4DIAC -s /your_path_to_file.sys -f /your_path to_file.fboot -v
```