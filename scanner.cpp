#include "pch.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <filesystem>
using namespace std::filesystem;

class antivirus_scaner {
private:

	//перемещение файла
	void move_file(std::string filname, std::string name) {
		const char * current, *new_;
		current = filname.c_str();
		name = "C:\\Users\\Asus\\Desktop\\carantin\\" + name;
		new_ = name.c_str();
		rename(current, new_); //на винде перемещение = переименовывание
	}

	//проверка директории (в качестве аргумента задается любая директория, это просто для примера)
	void checking_dyrectory(const path & name_of_directory) {
		for (const directory_entry& x : directory_iterator{ name_of_directory }) {
			if ( is_directory( x.path() ) ) {
				checking_dyrectory( x.path() );
			}
			else {
				if (x.path().extension().generic_string(); == ".exe") {
					if (is_dangerous(x.path().generic_string())) {
						move_file(x.path().generic_string(), x.path().filename().generic_string());
					}
				}
			}
		}
	}

	//поиск вредоносной подпоследовательности алгоритмом
	bool checking_file(const char * buf, int length) {
		
	}

	//проверка, является ли файл зараженным
	bool is_dangerous(std::string name) {
		bool succsess = false;
		std::ifstream ifile(name, std::ofstream::binary);

		ifile.seekg(0, ifile.end);
		int length = ifile.tellg();
		ifile.seekg(0, ifile.beg);
		char * buffer = new char[++length];
		buffer[length - 1] = '\0';
		ifile.read(buffer, length);

		succsess = checking_file(buffer, length);

		delete buffer;
		ifile.close();
		return succsess;
	}

public:

	void scan_filesystem(std::string name_of_directory) {
		path dyrectory(name_of_directory);
		checking_dyrectory(dyrectory);
	}

};

int main()
{
	std::string str = "";
	antivirus_scaner scaner;
	scaner.scan_filesystem(str);
	return 0;
}
