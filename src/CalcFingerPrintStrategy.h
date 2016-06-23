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
    virtual std::vector<FingerPrint>&& GetFingerPrint(std::istream &input) = 0;
};

class WinnowingStrategy : public CalcFingerPrintStrategy
{
public:
    virtual std::vector<FingerPrint>&& GetFingerPrint(std::istream &input);
};


#endif //COPYDETECT_CALCFINGERPRINTSTRATEGY_H
