#ifndef LogScanner_h
#define LogScanner_h

#include <fstream>
#include <vector>

using namespace std;

class LogScanner
{
public:
   struct activityType
   {
      string device;
      string url;
      string timestamp;

      activityType(): device(""), url(""), timestamp("") {}
      string getActivityString()
      {
         return (device + "\n" + url + "\n" + timestamp + "\n");
      };
   };

   typedef vector<activityType> activityList;

public:
   LogScanner();
   ~LogScanner();

   void setLogFileName(const string lFileName);
   int findQuestionableActivities(activityList &lActivityList);

private:
   bool open();
   bool close();
   string readLine(const string lFindLine);
   bool getNextQuestionableActivity(activityType &lActivity);
   bool isQuestionable(const string lUrl);

private:
   string         mFileName;
   ifstream       mInFile;
   static const char * mQuestionableWords[];
};

#endif
