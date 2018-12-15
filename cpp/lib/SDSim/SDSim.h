#ifndef SDSIM_H
#define SDSIM_H

#ifndef SIMULATOR
#include <SD.h>
#else
#include <fstream>

enum openMode {FILE_READ, FILE_WRITE};

class File
{
private:
    std::fstream file;
    char filename[30];
    openMode mode;
public:
    File();
    File(char* filename, openMode mode=FILE_READ);
    File(const File&);
    operator bool();
    File& operator=(const File&);
    // Open/Close
    void open();
    void close();
    unsigned long size();
    // Position
    void seek(unsigned long);
    unsigned long position();
    // Write
    void write(char);
    void print(char*);
    void print(int);
    void println(char*);
    void println(int);
    // Read
    char read();
    bool available();
    bool good();
};

class SDClass
{
public:
    void begin(int);
    File open(char* filename, openMode mode=FILE_READ);
    bool exists(char*);
    void mkdir(char*);
    void remove(char*);
    void completeFilename(char* filename, char* dest);
};
extern SDClass SD;

#endif
#endif
