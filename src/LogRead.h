#ifndef LogRead_h
#define LogRead_h

#include <fstream>
#include <iostream>
using namespace std;

class LogRead
{
public:
   LogRead();
   ~LogRead();

   int open(const char *lFile);
   int read();
   int close();
private:
   ifstream fIn;
};

#endif
