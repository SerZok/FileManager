#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

bool FileExists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void ReadFile(std::string filename) {
	std::cout << filename << " is exist: " << std::boolalpha << FileExists(filename) << std::endl;
	std::cout << "---Start reading---\n";
	std::ifstream infile(filename);
	std::string buffer;
	if (infile.is_open()) {
		while (std::getline(infile, buffer)) {
			std::cout << buffer << std::endl;
		}
	}
	else {
		std::cout << "Can't open file\n";
		return;
	}

	std::cout << "---End of reading--\n\n";
	infile.close();
}

void WriteFile(std::string filename) {
	bool exists = FileExists(filename);
	std::cout << filename << " is exist: " << std::boolalpha << exists << std::endl;
	std::ofstream ofile;
	if (exists == true) {
		char ch;
		while (1) {
			std::cout << "Заменить(C) или Добавить(A)" << filename << "? (C / A) : ";
			std::cin >> ch;
			if (ch == 'C') {
				ofile.open(filename);
				break;
			}
			else if (ch == 'A') {
				ofile.open(filename,std::ios_base::app);
				break;
			}
		}
	}
	else
		ofile.open(filename);

	std::cout << "---Запись в файл (Для завершения записи ввести \'/q\')---\n";
	if (!ofile.is_open()) {
		std::cout << "Can't open file\n";
		return;
	}

	std::string buffer = "";
	while (1) {
		std::getline(std::cin, buffer);
		if (buffer.find("/q") == 0) {
			std::cout << "---Запись завершена---\n\n";
			break;
		}
		ofile << buffer << std::endl;
	}
	ofile.close();
}

void F2F(std::string file1, std::string file2) {
	std::cout <<file1 <<" is exist: " << std::boolalpha << FileExists(file1) << std::endl;
	std::ifstream ifile(file1);
	if (!ifile.is_open()) {
		std::cout << "Can't open: " << file1 << std::endl;
		return;
	}
	bool exists2 = FileExists(file2);
	std::cout << file2 << " is exist: " << std::boolalpha << exists2 << std::endl;
	std::ofstream ofile;
	if (exists2 == true) {
		char ch;
		while (1) {
			std::cout << "Заменить(C) или Добавить(A)"<< file2 << "? (C / A) : ";
			std::cin >> ch;
			if (ch == 'C') {
				ofile.open(file2);
				break;
			}
			else if (ch == 'A') {
				ofile.open(file2, std::ios_base::app);
				break;
			}
		}
	}
	else
		ofile.open(file2);

	if (!ofile.is_open()) {
		std::cout << "Can't open: " << file2 << std::endl;
		return;
	}

	std::string buffer;
	while (std::getline(ifile, buffer)) {
		std::cout << buffer << std::endl;
		ofile << buffer << std::endl;
	}
	ifile.close();
	ofile.close();
}

void ShowInfo(std::string filename) {
	std::fstream file(filename);
	if (file.is_open()) {
		file.seekg(0, std::ios_base::end);
		std::cout << "Размер файла: " << file.tellg()<<" Bytes\n";
	}
	file.close();
}

int main(){
	setlocale(LC_ALL, "rus");
	std::string filename, filename2;
	char variation;
	
	while (1) {
		std::cout << "R-read | W-write | E-Запись из одного файла в другой \nS-показать информацию о файле | Q-quit\n";
		std::cin >> variation;
		std::cin.ignore();
		switch (variation)
		{
		case 'R':
			std::cout << "Название файла для чтения: \n";
			std::getline(std::cin, filename);
			ReadFile(filename);
			break;
		case 'W':
			std::cout << "Название файла для записи: \n";
			std::getline(std::cin, filename);
			WriteFile(filename);
			break;
		case 'E':
			std::cout << "Название файла для чтения: \n";
			std::getline(std::cin, filename);
			std::cout << "Название файла для записи: \n";
			std::getline(std::cin, filename2);
			std::cout << '\n';
			F2F(filename, filename2);
			break;
		case 'S':
			std::cout << "Название файла для получения информации: \n";
			std::getline(std::cin, filename);
			ShowInfo(filename);
			break;
		case 'Q':
			return 0;
		default:
			break;
		}
	}
}
