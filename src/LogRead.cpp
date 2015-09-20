#include "LogRead.h"

int LogRead::open(const char *lFile)
{
   try {
      fIn.open(lFile);
   }
   catch (exception &e)
   {
      cout << "Error, could not open file" << endl;
      return -1;
   }
   return 0;
}

int LogRead::read()
{
   while (!fIn.eof())
   {
      char line[300];
      fIn.getline(line, 300);

      string lineStr(line);

      lineStr.find("device: ");
      lineStr.substr();

   }
   return 0;
}

int LogRead::close()
{
   try {
      fIn.close();
   }
   catch (exception &e)
   {
      cout << "Error, could not close file" << endl;
      return -1;
   }
   return 0;
}
