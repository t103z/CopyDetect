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
    virtual std::vector<FingerPrint> &&GetFingerPrint(std::istream &input, const std::string &name, size_t id) = 0;
};

class WinnowingStrategy : public CalcFingerPrintStrategy
{
public:
    virtual std::vector<FingerPrint> &&GetFingerPrint(std::istream &input, const std::string &name, size_t id);
};


#endif //COPYDETECT_CALCFINGERPRINTSTRATEGY_H
