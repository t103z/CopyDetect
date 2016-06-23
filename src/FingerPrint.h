//
// Created by zhang on 16-6-23.
//

#ifndef COPYDETECT_FINGERPRINT_H
#define COPYDETECT_FINGERPRINT_H


#include <string>

struct Info
{
    std::string file_name;
    size_t      line_number;
};

struct FingerPrint
{
    typedef int hash_t;

    hash_t key;
    Info info;
};


#endif //COPYDETECT_FINGERPRINT_H
