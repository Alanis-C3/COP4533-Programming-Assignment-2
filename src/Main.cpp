#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "LRU.cpp"
using namespace std;

int main() {
	vector<string> cacheInput;
	int cacheCapacity;
	int m;
	ifstream inFile;
	inFile.open("../examplein.txt");
	if (!inFile.is_open()){
            cout << "Error opening file" << endl;
            return -1;
        }
	string km;
	string strM;
	string strK;

	//getting k & m
	getline(inFile, km);
	istringstream iss(km);
	// separates k and m into sep str
	iss >> strK >> strM;
	// convert k and m into int types
	cacheCapacity = stoi(strK);
	m = stoi(strM);

	string str;
	getline(inFile, str);
	stringstream ss(str);
	// load request into vector cacheInput
	for (int i = 0; i < m; i++) {
		getline(ss, str, ' ');
		cacheInput.push_back(str);
	}

	cout << "cache capacity: " << cacheCapacity << endl;
	cout << "m : " << m << endl;
	for(int i = 0; i <= m; i++){
    cout << cacheInput[i] << endl;


}
	int missed = LRU(cacheInput, cacheCapacity);
	cout << "LRU misses : " << missed<<endl;


return 0;}