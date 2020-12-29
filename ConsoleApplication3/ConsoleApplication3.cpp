#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

template <class Container>
void Divider(const std::string& anotherline, Container& cont)
{

	std::istringstream iss(anotherline);

	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(cont));
}

bool Point = true;

void consolewriting(std::vector<std::string>& consoledata) {

	std::string line;

	do {

		std::cout << "---->";

		getline(std::cin, line);

		if (line.size() > 0) {

			if ((line.find("\\q") != std::string::npos) | (line.find("\\quit") != std::string::npos)) {

				Point = false;
				return;
			}

			Divider(line, consoledata);

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

	} while (line.size() > 0);

}

void filewritten(std::string& nameoffile, std::vector<std::vector<std::string>>& data_file) {

	vector<string> strBuff;
	
	string anotheranotherline;

	ifstream f(nameoffile);

	if (!f.is_open()) {

		std::cout << "Error! Could not find a file: *.csv";
	}
	else
	{
		if (f.eof()) {

			std::cout << "File - empty";
			return;
		}

		while (!f.eof())
		{
			getline(f, anotheranotherline);

			std::stringstream s_1(anotheranotherline);
			vector<string> strBuff;

			while (!s_1.eof())
			{
				getline(s_1, anotheranotherline, ';');
				strBuff.push_back(anotheranotherline);
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

	vector<string> dataofcon;
	vector<vector<string>> dataoffs;

	while (Point) {

		

		consolewriting(dataofcon);
		

		if (dataofcon.size() > 1) {

			Handling(dataofcon, dataoffs);
		}
	}

}