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
	std::vector<std::string> virus_strings;

	void read_data_of_dangerous_files() {
		std::ifstream fin("C:\\Users\\Asus\\Desktop\\carantin\\data.txt");
		std::string str;
		
		while (std::getline(fin, str)) {
			virus_strings.push_back(str);
		}
		fin.close();
	}

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
				if (extension == ".exe") {
					if (is_dangerous(x.path().generic_string())) {
						move_file(x.path().generic_string(), x.path().filename().generic_string());
					}
				}
			}
		}
	}

	bool checking_file(std::string & buf, int length) {

		for (auto i : virus_strings) {
			if ( buf.find(i) != std::string::npos )
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
		ifile.read((char*)buffer, length);

		std::string str;
		for (auto i = 0; i < length; ++i) {
			str += buffer[i];
		}

		succsess = checking_file(str, length);

		delete buffer;
		ifile.close();
		return succsess;
	}

public:

	void scan_filesystem() {
		read_data_of_dangerous_files();
		checking_dyrectory();
	}

};

int main()
{
	antivirus_scaner scaner;
	scaner.scan_filesystem();

	return 0;
}
