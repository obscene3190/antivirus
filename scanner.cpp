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

	void move_file(std::string filname, std::string name) {
		const char * from, *to;
		from = filname.c_str();
		name = "C:\\Users\\Asus\\Desktop\\carantin\\" + name;
		to = name.c_str();
		rename(from, to);
	}

	void checking_dyrectory(const path & checking = "C:\\Users\\Asus\\Desktop\\kurs" ) {
		path name_of_directory = checking;
		for (const directory_entry& x : directory_iterator{ name_of_directory }) {
			if ( is_directory( x.path() ) ) {
				checking_dyrectory( x.path() );
			}
			else {
				std::string name = x.path().stem().generic_string(), extension = x.path().extension().generic_string();
				if (extension == ".exe" && name.find("3") != std::string::npos) {
					if (is_dangerous(x.path().generic_string())) {
						move_file(x.path().generic_string(), x.path().filename().generic_string());
					}
				}
			}
		}
	}

	bool checking_file(const char * buf, int length) {
		//поиск вредоносной подпоследовательности

		std::string str = "is_dangerous";
		const char * b = str.c_str();

		for (auto i = 0; i < length; ++i) {
			if (b[i] == buf[i])
				if (i == length - 1)
					return true;
		}
		return false;
	}

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

	void scan_filesystem() {
		checking_dyrectory();
	}

};

int main()
{
	antivirus_scaner scaner;
	scaner.scan_filesystem();
	return 0;
}
