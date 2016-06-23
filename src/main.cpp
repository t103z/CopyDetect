#include <iostream>
#include <fstream>
#include "CMPDocument.h"

using namespace std;

int main(int argc, char* argv[])
{

    // check input
    if (argc < 2)
        cout << "Usage: ./CopyDetect [file1] [file2] ..." << endl;

    ifstream fin;
    for (int i = 0; i < argc - 1; ++i)
    {
        fin.open(argv[i]);
        if (!fin.good())
        {
            cout << "Cannot open file: " << argv[i];
            cout << "! Please check your input!" << endl;
            return 1;
        }
        fin.close();
        fin.clear();
    }

    vector<CPPDocument> docs;
    docs.reserve(static_cast<size_t>(argc));
    for (int i = 1; i < argc; ++i)
    {
        docs.push_back(std::move(CPPDocument(argv[i])));
    }


    return 0;
}