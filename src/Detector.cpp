//
// Created by zhang on 16-6-23.
//

#include <list>
#include <map>
#include <algorithm>
#include <cstring>
#include "Detector.h"

void Detector::Check(std::ostream &output)
{
    using namespace std;

    map<FingerPrint::hash_t, vector<Info>> mapping; //fingerprint - document line mapping

    // step 1: get fingerprint mapping
    for (auto doc : _docs)
    {
        for (auto fp : doc->FingerPrints())
        {
            FingerPrint::hash_t key = fp.key;
            Info info = fp.info;
            mapping[key].push_back(info);
        }
    }

//    // sort in order to use binary search
//    for (auto mp : mapping)
//    {
//        sort(mp.second.begin(), mp.second.end(), [](const Info &a, const Info &b)->bool
//        {
//            return a.file_name < b.file_name;
//        });
//    }

    // step 2: find matching
    size_t **matches = new size_t*[_docs.size()];
    for (int i = 0; i < _docs.size(); i++)
    {
        matches[i] = new size_t[_docs.size()];
        memset(matches[i], 0, sizeof(size_t) * _docs.size());
    }

    for (auto doc : _docs)
    {
        size_t id = doc->id();
        for (auto fp : doc->FingerPrints())
        {
            FingerPrint::hash_t key = fp.key;
            for (auto match : mapping[key])
                if (match.id != id)
                    matches[id][match.id]++;
        }
    }

    // find top matching
    size_t max_times = 0, f1 = 0, f2 = 0;
    for (size_t i = 0; i < _docs.size(); ++i)
        for (size_t j = i; j < _docs.size(); ++j)
            if (matches[i][j] > max_times)
            {
                f1 = i;
                f2 = j;
                max_times = matches[i][j];
            }

    // find matches in f1 and f2
    struct Matching
    {
        size_t line1, line2;
    };
    Matching *line_matches = new Matching[max_times];
    size_t cnt = 0;
    for (auto fp1 : _docs[f1]->FingerPrints())
        for (auto fp2 : _docs[f2]->FingerPrints())
            if (fp1.key == fp2.key)
            {
                line_matches[cnt].line1 = fp1.info.line_number;
                line_matches[cnt].line2 = fp2.info.line_number;
                cnt++;
            }

    sort(line_matches, line_matches + max_times, [](const Matching &a, const Matching &b) -> bool
    {
        return a.line1 == b.line1 ? a.line1 < b.line1 : a.line2 < b.line2;
    });

    // find paragraph using consecutive matching
    struct Paragraph
    {
        size_t beg1, beg2, end1, end2;
        size_t size;
    };
    vector<Paragraph> para_matches;
    size_t num1, num2;
    Paragraph para;
    num1 = para.beg1 = para.end1 = line_matches[0].line1;
    num2 = para.beg2 = para.end2 = line_matches[0].line2;
    para.size = 1;
    for (int i = 0; i < max_times; ++i)
    {
        if (line_matches[i].line1 == num1 && line_matches[i].line2 == num2)
            continue;
        else if (line_matches[i].line1 == num1 && line_matches[i].line2 != num2)
            continue;
        else if (line_matches[i].line1 == num1 + 1 && line_matches[i].line2 == num2 + 1)
        {
            para.end1 = ++num1;
            para.end2 = ++num2;
            para.size++;
        }
        else
        {
            para_matches.push_back(para);
            num1 = para.beg1 = para.end1 = line_matches[i].line1;
            num2 = para.beg2 = para.end2 = line_matches[i].line2;
            para.size = 1;
        }
    }
    para_matches.push_back(para);

    // output
    sort(para_matches.begin(), para_matches.end(), [](const Paragraph &a, const Paragraph &b)-> bool
    {
        return a.size > b.size;
    });
    string name1 = _docs[f1]->name();
    string name2 = _docs[f2]->name();
    for (auto it = para_matches.begin(); it != para_matches.end(); it++)
    {
        output << "------------------------------------------------------------------" << endl;
        output << "Match from line " << it->beg1 << " in file " << name1 << " and line " << it->beg2
                << " in file " << name2 << " :" << endl;
        for (int i = 0; i < it->size; ++i)
        {
            output << "1:\t" << _docs[f1]->GetLine(it->beg1 + i) << endl;
            output << "2:\t" << _docs[f2]->GetLine(it->beg2 + i) << endl;
        }
        output << "------------------------------------------------------------------" << endl;
    }
}

