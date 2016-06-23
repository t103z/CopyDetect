//
// Created by zhang on 16-6-23.
//

#ifndef COPYDETECT_LEXER_H
#define COPYDETECT_LEXER_H

#include <iostream>
#include "FlexLexer.h"

class Lexer
{
public:
    Lexer(std::istream* in_stream, std::ostream* out_stream);
    virtual void Lex() = 0;
    virtual bool ChangeStream(std::istream* in_stream, std::ostream* out_stream);
    virtual const std::string name() const = 0;
    virtual ~Lexer();
protected:
    std::istream* _input;
    std::ostream* _output;
};


class CPPLexer : public Lexer, private yyFlexLexer
{
public:
    CPPLexer(std::istream *in_stream, std::ostream *out_stream) : Lexer(in_stream, out_stream),
    yyFlexLexer(in_stream, out_stream){ }

    virtual void Lex();
    virtual const std::string name() const;

    virtual ~CPPLexer() {}

protected:

};


class NaiveLexer : public Lexer
{
public:
    NaiveLexer(std::istream *in_stream, std::ostream *out_stream) : Lexer(in_stream, out_stream) { }
    virtual void Lex();
    virtual const std::string name() const;
};

#endif //COPYDETECT_LEXER_H
