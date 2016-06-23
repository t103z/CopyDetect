//
// Created by zhang on 16-6-23.
//

#include "Document.h"
#include <fstream>
#include <iostream>

Document::Document(Document &&doc) : _lines(std::move(doc._lines)), _name(std::move(doc._name)),
                                     _line_num(std::move(doc._line_num)), _good(std::move(doc._good))
{
    _stream << doc._stream.str();
}

Document::Document(const Document &doc) : _lines(doc._lines),
                                          _name(doc._name), _line_num(doc._line_num), _good(doc._good)
{
    _stream << doc._stream.str();
}

bool Document::Load(const std::string &filename)
{
    using namespace std;
    ifstream fin(filename);
    if (!fin)
    {
        cerr << "Cannot open file: " << filename << endl;
        _good = false;
        return false;
    }

    _name = filename;
    _stream << fin.rdbuf();
    fin.close();

    string line;
    _lines.push_back(string()); //skip line number 0
    while (getline(_stream, line))
    {
        _line_num++;
        _lines.push_back(line);
    }
    _good = true;
    return true;

}

inline bool Document::good() const
{
    return _good;
}

inline const std::string Document::name() const
{
    return _name;
}

std::string Document::GetLine(int linenum) const
{
    using namespace std;
    if (!_good || linenum > _line_num)
        return std::basic_string<char, char_traits<char>, allocator<char >>();

    return _lines[linenum];
}

Document::Document(const std::string &filename) : _good(false), _line_num(0)
{
    Load(filename);
}

std::ostream &operator<<(std::ostream &os, const Document &doc)
{
    os << doc._stream.rdbuf();
    return os;
}

std::size_t Document::line_number() const
{
    return _line_num;
}

