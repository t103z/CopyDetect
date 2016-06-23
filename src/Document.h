//
// Created by zhang on 16-6-23.
//

#ifndef COPYDETECT_DOCUMENT_H
#define COPYDETECT_DOCUMENT_H

#include <sstream>
#include <vector>

class Document
{
public:
    Document(const Document &doc);
    Document(Document &&doc);

    virtual ~Document() {}
    virtual std::string GetLine(int linenum) const;
    virtual bool Load(const std::string &filename);
    virtual bool good() const;
    virtual const std::string name() const;
    std::size_t line_number() const;

    friend std::ostream& operator<<(std::ostream& os, const Document &doc);

protected:
    Document(const std::string &filename);
    std::vector<std::string> _lines;
    std::stringstream _stream;
    std::string _name;
    std::size_t _line_num;
    bool _good;

};


#endif //COPYDETECT_DOCUMENT_H
