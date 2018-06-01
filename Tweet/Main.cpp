
#include <iostream>
#include <cstdlib>
#include "FileHandling.h"

using namespace std;

int main() {
    FileHandling fileHandling;

    string filename;
    string stopfile;
    cout<<"This is Cosine Similarity Program"<<endl;
    cout << "Enter input filename" << endl;
    getline(cin, filename);
    fileHandling.ReadInputFile(filename);

    cout << "Enter stopwords filename" << endl;
    getline(cin, stopfile);
    fileHandling.ReadStopWordsFile(stopfile);
    fileHandling.FileWriter();
   

    return 0;
}

