//
// Created by zhang on 16-6-23.
//

#ifndef COPYDETECT_DETECTOR_H
#define COPYDETECT_DETECTOR_H

#include "CMPDocument.h"


class BaseDetector
{
public:
    BaseDetector(std::vector<CMPDocument*> &docs) : _docs(docs) { }

    virtual void Check(std::ostream &output) = 0;

protected:
    std::vector<CMPDocument *> &_docs;
};

class Detector : public BaseDetector
{

public:
    Detector(std::vector<CMPDocument*> &docs) : BaseDetector(docs) { }

    virtual void Check(std::ostream &output) override;


};


#endif //COPYDETECT_DETECTOR_H
