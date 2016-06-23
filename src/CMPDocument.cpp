//
// Created by zhang on 16-6-23.
//

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
    _lexer = new CPPLexer(&_stream, &_token_stream);
    tokenize();

    _fingerprint_strategy = new WinnowingStrategy();
    _stream.clear();
    _stream.seekg(0, _stream.beg);
    _finger_prints = _fingerprint_strategy->GetFingerPrint(_stream, _name, _id);
}

