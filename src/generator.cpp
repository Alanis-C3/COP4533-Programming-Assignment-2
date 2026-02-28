#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <random>

using namespace std;

vector<string> generator(vector<int> kMaxValues){ // = {0, 8, 64, 512}
    vector<string> fileList;
    string fileName = "";
    mt19937 gen(random_device{}());


    // generate one file per k
    for (int i = 1; i<kMaxValues.size(); i++){
        uniform_int_distribution<> distK(kMaxValues[i-1]+1, kMaxValues[i]);
        int k = distK(gen);
        uniform_int_distribution<> distM(k, k*10); // for k = 8, m will be between 8 and 80
        int m = distM(gen);


        // write to the file
        fileName = "../inputs/example" + to_string(k) + "in.txt"; // for k = 512, file name is example512in.txt
        ofstream outFile(fileName);
        if (!outFile.is_open()){
            cout << "Error in creating file!" << endl;
        } else{
            fileList.push_back(fileName);
            // first line of every file is "k m"
            outFile << to_string(k) << " " << to_string(m)<< "\n";
            // second line of every file is "r1 r2... rm"
            for (int j = 1; j<=m; j++){
                outFile << "r" << to_string(j);
                if (j != m) outFile << " "; // add a space if it's not the last value
            }
        }
        outFile.close();
    }

    return fileList;
}