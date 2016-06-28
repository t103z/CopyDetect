//
// Created by zhang on 16-6-23.
//

#ifndef COPYDETECT_CALCFINGERPRINTSTRATEGY_H
#define COPYDETECT_CALCFINGERPRINTSTRATEGY_H


#include <vector>
#include "FingerPrint.h"

class CalcFingerPrintStrategy
{
public:
    virtual std::vector<FingerPrint> GetFingerPrint(std::istream &input, const std::string &name, size_t id) = 0;
};

class WinnowingStrategy : public CalcFingerPrintStrategy
{
private:
    int window_len;
    int k_gram_len;
    FingerPrint::hash_t HashBase;
    FingerPrint::hash_t HashValue;
    FingerPrint::hash_t ComputeNextHash(int hash_num, std::string &str);
public:
    virtual std::vector<FingerPrint> GetFingerPrint(std::istream &input, const std::string &name, size_t id);
    void Set_K_gram(int _k_gram_len);
    int Get_K_gram();
    void Set_Window_len(int _window_len);
    int Get_Window_len();
};


#endif //COPYDETECT_CALCFINGERPRINTSTRATEGY_H
