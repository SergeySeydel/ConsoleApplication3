#include <iostream>
#include <fstream> // ifstream
#include <string>
#include <vector>
#include <sstream>

using namespace std;


template <class Container>
void Split(const std::string& str, Container &cont)
{

    std::istringstream iss(str);

    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(cont));
}

bool FLAG = true;

void write_console(std::vector<std::string>& data_con) {
	
	std::string str;

	do {
	
		std::cout << "\x1b[0;32;40m"<< ">>>" <<"\x1b[0m";

		getline(std::cin, str);
	
		if (str.size() > 0) {

			if ((str.find("\\q") != std::string::npos) | (str.find("\\quit") != std::string::npos)) {

				FLAG = false;
				return;
			}

			Split(str, data_con);

			for (auto& DC : data_con) {

				if (DC.find(';') != std::string::npos) {

					auto it = std::find(data_con.begin(), data_con.end(), DC);

					*it = DC.erase(DC.find(';'), 1);
				}
				else if (DC.find('=') != std::string::npos) {

					auto it = std::find(data_con.begin(), data_con.end(), DC);

					data_con.erase(it);

					if (DC.find(';') != std::string::npos) {

						auto it = std::find(data_con.begin(), data_con.end(), DC);

						*it = DC.erase(DC.find(';'), 1);

					}

				}

			}
			///
		}
		else {
		
			///return;
		}
	
	} while (str.size() > 0);

}

void write_file(std::string& name_file ,std::vector<std::vector<std::string>>& data_file) {

	vector<string> strBuff;
	//vector <vector<string>> data;
	string str;

	ifstream fs(name_file);

	if (!fs.is_open()) {
	
		std::cout << "Error! Not file: *.csv";
	}
	else 
	{

		if (fs.eof()) {
			
			std::cout << "File is empty!!!";
			return;
		}

		while (!fs.eof())
		{
			getline(fs, str);

			std::stringstream s_1(str);
			vector<string> strBuff;

			while (!s_1.eof())
			{
				getline(s_1, str, ',');
				strBuff.push_back(str);
			}

			data_file.push_back(strBuff);
		}

		/*
		for (int i = 0; i < data_file.size(); i++)
		{
			for (int j = 0; j < data_file[i].size(); j++)
				cout << data_file[i][j] << " ";

			cout << endl;
		}
		*/
	}
}

void Processing(vector<string>& data_console, vector<vector<string>>& data_file) {


	for(auto DC: data_console) {
	
		if(DC.find('*') != std::string::npos) {
		
			for (int i = 0; i < data_file.size(); i++)
			{
				for (int j = 0; j < data_file[i].size(); j++)
					cout << data_file[i][j] << " ";

				cout << endl;
			}
		
		}
		else if (DC.find("FROM") != std::string::npos) {
		
			auto it = DC.find("FROM");

			auto elem = (*(++(std::find(data_console.begin(), data_console.end(), DC))));

			//elem;
			write_file(elem, data_file);
		}
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");

	vector<string> data_console;
	vector<vector<string>> data_file;

	while (FLAG) {

		//FROM data.csv

		write_console(data_console);
		// \q +
		//SELECT * FROM data.csv WHERE id_dept=101;
		// \q // \quit

		if (data_console.size() > 1) {

			Processing(data_console, data_file);
		}
	}

}