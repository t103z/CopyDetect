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
    _stream.clear();
    _stream.seekg(0, _stream.beg);
    _lexer = new NaiveLexer(&_stream, &_token_stream);
    tokenize();

//    std::ofstream fout(filename + ".out");
//    fout << _token_stream.str();


    _fingerprint_strategy = new WinnowingStrategy();
    _token_stream.clear();
    _token_stream.seekg(0, _stream.beg);
    _finger_prints = _fingerprint_strategy->GetFingerPrint(_token_stream, _name, _id);

//    for (auto fp : _finger_prints)
//    {
//        fout << fp.key << " : " << fp.info.line_number << std::endl;
//    }
//
//    fout.close();
}

