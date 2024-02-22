#pragma once
#include <SFML/System/InputStream.hpp>

struct PHYSFS_File;

class PhysFsStream : public sf::InputStream
{
public:
    PhysFsStream(const char * filename = 0x0);
    virtual ~PhysFsStream();
    bool isOpen() const;
    bool open(const char * filename);
    void close();
    virtual int64_t read(void * data, int64_t size);
    virtual int64_t seek(int64_t position);
    virtual int64_t tell();
    virtual int64_t getSize();

private:
    PHYSFS_File * m_File;

};