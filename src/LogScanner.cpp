#include "LogScanner.h"


LogScanner::LogScanner()
{
   mFileName = "";
   mActivityList.clear();

   mQuestionableWords.push_back("porn");
   mQuestionableWords.push_back("xxx");
   mQuestionableWords.push_back("sex");
   mQuestionableWords.push_back("Bieber");
}

LogScanner::~LogScanner()
{
}

void LogScanner::setLogFileName(const string lFileName)
{
   mFileName = lFileName;
}

int LogScanner::open()
{
   if (mFileName == "")
   {
      cout << "Error, log file name not set" << endl;
      return -1;
   }

   try {
      fIn.open(mFileName.c_str());
   }
   catch (exception &e)
   {
      cout << "Error, could not open file" << endl;
      return -1;
   }

   return 0;
}

int LogScanner::close()
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

int LogScanner::findQuestionableActivities()
{
   activityType lActivity;

   if (open() < 0)
   {
      cout << "Error open, invalid log file" << endl;
      return -1;
   }

   while (!fIn.eof())
      if (getNextQuestionableActivity(lActivity))
         mActivityList.push_back(lActivity);

   if (close() < 0)
   {
      cout << "Error close log file" << endl;
      return -1;
   }

   return mActivityList.size();
}

bool LogScanner::getNextQuestionableActivity(activityType &lActivity)
{
   //Important: keep this sequence order as depicted in the log file

   lActivity.device    = readLine("device: ");
   if (lActivity.device == "")
      return false;

   lActivity.url       = readLine("url: ");
   if (lActivity.url == "")
      return false;

   lActivity.timestamp = readLine("timestamp: ");
   if (lActivity.timestamp == "")
      return false;

   if (isQuestionable(lActivity.url))
      return true;

   return false;
}

bool LogScanner::isQuestionable(const string lUrl)
{
   int ii = 0;
   for ( vector<string>::iterator it=mQuestionableWords.begin(); it!=mQuestionableWords.end(); ++it)
   {
      if (lUrl.find(*it) != string::npos )
      {
         //cout << "QUESTURL[" << *it << "]: " << lUrl << endl;
         return true;
      }
      ii++;
   };
   return false;
}

string LogScanner::readLine(const string mFindLine)
{
   char line[2000];

   if (!fIn.eof())
   {
      fIn.getline(line, 2000);
      string lineStr = string(line);
      if (lineStr.find_first_of(mFindLine) == 0)
         return (lineStr.erase(0, mFindLine.size()));
      else
         return ("");
   }
   return ("");
}

string LogScanner::getQuestionableActivityList()
{
   string lActivities = "";

   for ( activityList::iterator it=mActivityList.begin(); it!=mActivityList.end(); ++it)
   {
      lActivities += "device : ";
      lActivities += it->device;
      lActivities += "\n";

      lActivities += "url : ";
      lActivities += it->url;
      lActivities += "\n";

      lActivities += "timestamp : ";
      lActivities += it->timestamp;
      lActivities += "\n";
   }

   return (lActivities);
}
