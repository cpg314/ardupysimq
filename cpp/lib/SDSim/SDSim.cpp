#include "SDSim.h"
#ifdef SIMULATOR
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

File::File()
    : mode(FILE_READ)
{}
File::File(char* filename, openMode mode):
    mode(mode)
{
    SD.completeFilename(filename,this->filename);
    open();
}
File& File::operator=(const File& f)
{
    strcpy(filename,f.filename);
    mode=f.mode;
    open();
    return *this;
}
File::File(const File& f)
{
    strcpy(filename,f.filename);
    mode=f.mode;
    open();
}
void File::open()
{
    if (mode==FILE_READ)
        file.open(filename, std::fstream::in);
    else
    {
        file.open(filename, std::fstream::out | std::fstream::in);
        if (!good())
        {
            // Create file and reopen, see http://stackoverflow.com/questions/8835888/stdfstream-doesnt-create-file?noredirect=1&lq=1
            file.open(filename, std::fstream::out);
            file.close();
            open();
        }
	else
	    file.seekg (0, file.end); // Write mode starts at the *end* of the file, see https://www.arduino.cc/en/Reference/SDopen
    }
}
File::operator bool()
{
    return file.is_open();
}
void File::close()
{
    file.close();
}
void File::print(char* s)
{
    file<<s;
}
void File::print(int i)
{
    file<<i;
}
void File::println(char* s)
{
    file<<s<<std::endl;
}
void File::println(int i)
{
    file<<i<<std::endl;
}
bool File::available()
{
    return !file.eof();
}
bool File::good()
{
    return file.good();
}
char File::read()
{
    char c;
    file.get(c);
    return c;
}
unsigned long File::size()
{
    unsigned long begin=file.tellg();
    file.seekg(0, std::ios::end);
    unsigned long end=file.tellg();
    file.seekp(begin);
    return (end-begin);
}
void File::seek(unsigned long pos)
{
    file.seekp(pos);
}
unsigned long File::position()
{
    return file.tellp();
}
void File::write(char c)
{
    file.put(c);
}
bool SDClass::exists(char* filename)
{
    return File(filename).good();
}
void SDClass::begin(int pin)
{
}
File SDClass::open(char* filename, openMode mode)
{
    return File(filename, mode);
}
void SDClass::mkdir(char* name)
{
    char name2[30];
    completeFilename(name,name2);
    ::mkdir(name2, 0700);
}
void SDClass::remove(char* name)
{
    char name2[30];
    completeFilename(name,name2);
    unlink(name2);
}
void SDClass::completeFilename(char* filename, char* dest)
{
    sprintf(dest,"SD/%s",filename);
}

SDClass SD;
#endif

