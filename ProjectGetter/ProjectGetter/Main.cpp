#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

std::string ReadAllData(const std::string& url) {
	std::ifstream ifile(url);
	std::stringstream buf;
	buf << ifile.rdbuf();
	return buf.str();
}
std::map<string, int> resultMap;
void ParseLine(const string & line) {
	cout << "\nInProcess: " << line << endl;
	string RDDir = "rd ..\\..\\" + line;
	if (!system(RDDir.c_str())) {
		cout << "\tNot find dir: " << line << endl;
		//return;
	}

	string CTDir = "mkdir ..\\..\\" + line;
	if (system(CTDir.c_str()) < 0) {
		cout << "\tCreate dir: " << line << " Failed! Jump...(CMD:"<< CTDir<<")." << endl;
		return;
	}
	cout << line << endl;
	string url = "\"https://github.com/niuliu222/";
	url += line;
	url += ".git/\"";

	string path = " \"../../";
	path += line;
	path += "/\"";

	string all_path = "git.exe clone --progress -v ";
	all_path += url;
	all_path += path;

	cout << all_path << endl;
	int return_value = system(all_path.c_str());
	if (return_value != 0) {
		resultMap[line] = return_value;
	}
}

int main() {
	string data = ReadAllData("./ini.txt");
	int index = data.find('\n');
	int curr_index = 0;
	while (index > -1) {
		auto str = data.substr(curr_index, index - curr_index);

		ParseLine(str);

		curr_index = index + 1;
		index = data.find('\n', curr_index);
	}

	if (curr_index < data.length()) {
		auto str = data.substr(curr_index);
		ParseLine(str);
	}


	cout << "====================\n";
	cout << "=========OK=========\n";
	cout << "====================\n";

	cout << "\n\t" << resultMap.size() << " have(has) failed!!!";
	if (resultMap.size() > 0) {
		cout << "\n\t" << "those are(is):";
		for (auto a : resultMap) {
			cout << a.first << endl;
		}
	}
	cin.get();
	return 0;
}