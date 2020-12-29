#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

template <class Container>
void Divider(const std::string& str, Container& cont)
{

	std::istringstream iss(str);

	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(cont));
}

bool Point = true;

void consolewriting(std::vector<std::string>& consoledata) {

	std::string str;

	do {

		std::cout << "---->";

		getline(std::cin, str);

		if (str.size() > 0) {

			if ((str.find("\\q") != std::string::npos) | (str.find("\\quit") != std::string::npos)) {

				Point = false;
				return;
			}

			Divider(str, consoledata);

			for (auto& Local_variable : consoledata) {

				if (Local_variable.find(';') != std::string::npos) {

					auto it = std::find(consoledata.begin(), consoledata.end(), Local_variable);

					*it = Local_variable.erase(Local_variable.find(';'), 1);
				}
				else if (Local_variable.find('=') != std::string::npos) {

					auto it = std::find(consoledata.begin(), consoledata.end(), Local_variable);

					consoledata.erase(it);

					if (Local_variable.find(';') != std::string::npos) {

						auto it = std::find(consoledata.begin(), consoledata.end(), Local_variable);

						*it = Local_variable.erase(Local_variable.find(';'), 1);

					}

				}

			}
			
		}
		else {

			
		}

	} while (str.size() > 0);

}

void filewritten(std::string& name_file, std::vector<std::vector<std::string>>& data_file) {

	vector<string> strBuff;
	
	string str;

	ifstream fs(name_file);

	if (!fs.is_open()) {

		std::cout << "Error! Could not find a file: *.csv";
	}
	else
	{
		if (fs.eof()) {

			std::cout << "File - empty";
			return;
		}

		while (!fs.eof())
		{
			getline(fs, str);

			std::stringstream s_1(str);
			vector<string> strBuff;

			while (!s_1.eof())
			{
				getline(s_1, str, ';');
				strBuff.push_back(str);
			}

			data_file.push_back(strBuff);
		}

	
	}
}

void Handling(vector<string>& data_console, vector<vector<string>>& data_file) {


	for (auto Local_variable : data_console) {

		if (Local_variable.find("FROM") != std::string::npos) {

			auto it = Local_variable.find("FROM");

			auto part = (*(++(std::find(data_console.begin(), data_console.end(), Local_variable))));

			
			filewritten(part, data_file);

			for (auto Local_variableN : data_console) {

				if (Local_variableN.find('*') != std::string::npos) {

					for (int i = 0; i < data_file.size(); i++)
					{
						for (int j = 0; j < data_file[i].size(); j++)
							std::cout << data_file[i][j] << " ";

							std::cout << endl;
					}

				}if (Local_variableN.find("SELECT") != std::string::npos) {

					auto it = Local_variableN.find("SELECT");

					auto part = (*(++(std::find(data_console.begin(), data_console.end(), Local_variableN))));

					

					int i = 0;

					for (auto Local_variableR : data_file[0]) {

						++i;

						if (Local_variableR == part) {
							break;
							
						}

					}

					

					for (int j = 0; j <= data_file[i - 1].size(); ++j) {

						std::cout << data_file[j][i - 1] << std::endl;

					}

				}

			}
		}

	}


	
}

int main()
{
	setlocale(LC_ALL, "Russian");

	vector<string> data_console;
	vector<vector<string>> data_file;

	while (Point) {

		

		consolewriting(data_console);
		

		if (data_console.size() > 1) {

			Handling(data_console, data_file);
		}
	}

}