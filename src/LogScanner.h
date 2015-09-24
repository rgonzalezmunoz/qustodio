#ifndef LogScanner_h
#define LogScanner_h

#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class LogScanner
{
public:
   struct activityType {
      string device;
      string url;
      string timestamp;
      activityType(): device(""), url(""), timestamp("") {}
      string getActivityString() { return (device + "\n" + url + "\n" + timestamp + "\n"); };
   };

   typedef vector<activityType> activityList;

public:
   LogScanner();
   ~LogScanner();

   void setLogFileName(const string lFileName);
   int findQuestionableActivities(activityList &lActivityList);

private:
   int open();
   int close();
   string readLine(const string mFindLine);
   bool getNextQuestionableActivity(activityType &lActivity);
   bool isQuestionable(const string lUrl);

private:
   string         mFileName;
   ifstream       fIn;
   vector<string> mQuestionableWords;
};

#endif
