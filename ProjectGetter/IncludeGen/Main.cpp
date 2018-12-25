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
	FILE * file;

	string filename = "..\\include\\" + line;
	fopen_s(&file, filename.c_str(), "w");

	fprintf_s(file, "#include \"..\\..\\%s\\%s.h\"", line.c_str(), line.c_str());

	fclose(file);
}

const char * RDIncludeDir = "rd ..\\include";
const char * GenIncludeDir = "mkdir ..\\include";
int main() {
	system(RDIncludeDir);
	system(GenIncludeDir);

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