//
// Created by zhang on 16-6-23.
//

#include <fstream>
#include "CMPDocument.h"

void CMPDocument::tokenize()
{
    _lexer->Lex();
}

void CMPDocument::PrintToken(std::ostream &os) const
{
    os << _token_stream.str();
}

CMPDocument::CMPDocument(CMPDocument &&doc) : Document(std::move(doc)),
                                              _lexer(std::move(doc._lexer))
{
    _token_stream << doc._token_stream.str();
}

CMPDocument::CMPDocument(const CMPDocument &doc) : Document(doc), _lexer(doc._lexer)
{
    _token_stream << doc._token_stream.str();
}


CPPDocument::CPPDocument(const std::string &filename, std::size_t id) : CMPDocument(filename, id)
{
    //取消本函数中的注释可以将转换后的文本和fingerprint输出到文件

    _stream.clear();
    _stream.seekg(0, _stream.beg);


    //调试时如果需要输出原文，将下面这一行注释掉，然后把再下面一行取消注释,否则输出的是转换后的文本
    //_lexer = new CPPLexer(&_stream, &_token_stream);
    _lexer = new NaiveLexer(&_stream, &_token_stream);
    tokenize();

    std::ofstream fout(filename + ".out");
    fout << _token_stream.str();


    _fingerprint_strategy = new WinnowingStrategy();
    _token_stream.clear();
    _token_stream.seekg(0, _stream.beg);
    _finger_prints = _fingerprint_strategy->GetFingerPrint(_token_stream, _name, _id);

    for (auto fp : _finger_prints)
    {
        fout << fp.key << " : " << fp.info.line_number << std::endl;
    }

    fout.close();
}

