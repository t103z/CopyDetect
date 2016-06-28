#include <iostream>
#include <fstream>
#include "CMPDocument.h"
#include "Detector.h"

using namespace std;

int main(int argc, char *argv[])
{
    // check input
    if (argc < 2)
    {
        cout << "Usage: ./CopyDetect [file1] [file2] ..." << endl;
        return 1;
    }
    else if (argc < 3)
    {
        cout << "At least 2 files required!" << endl;
        return 1;
    }

    ifstream fin;
    for (int i = 1; i < argc; ++i)
    {
        fin.open(argv[i]);
        if (!fin)
        {
            cout << "Cannot open file: " << argv[i];
            cout << "! Please check your input!" << endl;
            return 1;
        }
        fin.close();
        fin.clear();
    }

    vector<CMPDocument *> docs;
    docs.reserve(static_cast<size_t>(argc));
    for (int i = 1; i < argc; ++i)
    {
        CMPDocument *doc = new CPPDocument(argv[i], static_cast<size_t>(i - 1));
        docs.push_back(doc);
    }

    // detect
    Detector detector(docs);
    detector.Check(cout);

    return 0;
}