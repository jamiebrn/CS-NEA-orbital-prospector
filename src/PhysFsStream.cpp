#include "PhysFsStream.hpp"
#include <physfs.h>

PhysFsStream::PhysFsStream(const char * filename) : m_File(0x0)
{
    if(filename)
        open(filename);
}

PhysFsStream::~PhysFsStream()
{
    close();
}

bool PhysFsStream::isOpen() const
{
    return (m_File != 0x0);
}

bool PhysFsStream::open(const char * filename)
{
    close();
    m_File = PHYSFS_openRead(filename);
    return isOpen();
}

void PhysFsStream::close()
{
    if(isOpen())
        PHYSFS_close(m_File);
    m_File = 0x0;
}

int64_t PhysFsStream::read(void * data, int64_t size)
{
    if(!isOpen())
        return -1;

    // PHYSFS_readBytes returns the number of bytes read or -1 on error.
    // We request to read size amount of bytes.
    return PHYSFS_readBytes(m_File, data, static_cast<PHYSFS_uint32>(size));
}

int64_t PhysFsStream::seek(int64_t position)
{
    if(!isOpen())
        return -1;

    // PHYSFS_seek return 0 on error and non zero on success
    if(PHYSFS_seek(m_File, position))
        return tell();
    else
        return -1;
}

int64_t PhysFsStream::tell()
{
    if(!isOpen())
        return -1;

    // PHYSFS_tell returns the offset in bytes or -1 on error just like SFML wants.
    return PHYSFS_tell(m_File);
}

int64_t PhysFsStream::getSize()
{
    if(!isOpen())
        return -1;

    // PHYSFS_fileLength also the returns length of file or -1 on error just like SFML wants.
    return PHYSFS_fileLength(m_File);
}