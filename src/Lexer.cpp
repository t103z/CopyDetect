//
// Created by zhang on 16-6-23.
//

#include "Lexer.h"

Lexer::Lexer(std::istream *in_stream, std::ostream *out_stream) : _input(in_stream), _output(out_stream)
{
}

bool Lexer::ChangeStream(std::istream* in_stream, std::ostream* out_stream)
{
    _input = in_stream;
    _output = out_stream;
}

Lexer::~Lexer()
{
}


void CPPLexer::Lex()
{
    while (yylex())
    {
        std::cout << yytext;
    }
}

const std::string CPPLexer::name() const
{
    return "C++ Lexer";
}


void NaiveLexer::Lex()
{
    // naive lexer simply copy original file content to tokenized file content
    *_output << _input->rdbuf();
}

const std::string NaiveLexer::name() const
{
    return "Naive Lexer";
}
