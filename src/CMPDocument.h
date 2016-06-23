//
// Created by zhang on 16-6-23.
//

#ifndef COPYDETECT_CMPDOCUMENT_H
#define COPYDETECT_CMPDOCUMENT_H

#include <memory>
#include "Document.h"
#include "Lexer.h"
#include "FingerPrint.h"
#include "CalcFingerPrintStrategy.h"

class CMPDocument : public Document
{

public:
    CMPDocument(const CMPDocument &doc);
    CMPDocument(CMPDocument &&doc);
    virtual ~CMPDocument() {  }

    void PrintToken(std::ostream &os) const;
    virtual const std::vector<FingerPrint> FingerPrints() const = 0;
    std::size_t id() const { return _id; }


protected:
    std::vector<FingerPrint> _finger_prints;
    std::stringstream _token_stream;
    Lexer *_lexer;
    CalcFingerPrintStrategy *_fingerprint_strategy;
    size_t _id;

    CMPDocument(const std::string &filename, std::size_t id) : Document(filename), _id(id) {}
    virtual void tokenize();
};

class CPPDocument : public CMPDocument
{
public:
    CPPDocument(const std::string &filename, std::size_t id);
    CPPDocument(const CPPDocument &doc) : CMPDocument(doc) {}
    CPPDocument(CPPDocument &&doc) : CMPDocument(std::move(doc)) {}

    virtual const std::vector<FingerPrint> FingerPrints() const { return _finger_prints; }
    virtual ~CPPDocument() {}
};


#endif //COPYDETECT_CMPDOCUMENT_H
