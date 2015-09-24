#include "LogScanner.h"


LogScanner::LogScanner()
{
   mFileName = "";

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

bool LogScanner::open()
{
   if (mFileName == "")
      return false;

   mInFile.open(mFileName.c_str());

   if (mInFile.fail())
      return false;

   return true;
}

bool LogScanner::close()
{
   mInFile.close();

   if (mInFile.fail() && mInFile.bad())
      return false;

   return true;
}

int LogScanner::findQuestionableActivities(activityList &lActivityList)
{
   activityType lActivity;

   if (!open())
      return -1;

   while (!mInFile.eof())
      if (getNextQuestionableActivity(lActivity))
         lActivityList.push_back(lActivity);

   if (!close())
      return -1;

   return lActivityList.size();
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
      //Get domain name because lUrl == https://petsandladys.com/sexbieberporn is not questionable
      string lDomainName;
      lDomainName = lUrl.substr(lUrl.find("//")+2);
      lDomainName = lDomainName.substr(0,lDomainName.find("/"));

      if (lDomainName.find(*it) != string::npos )
         return true;
      ii++;
   };
   return false;
}

string LogScanner::readLine(const string lFindLine)
{
   char line[2000];

   if (!mInFile.eof())
   {
      mInFile.getline(line, 2000);
      string lineStr = string(line);
      if (lineStr.find_first_of(lFindLine) == 0)
         return (lineStr.erase(0, lFindLine.size()));
      else
         return ("");
   }
   return ("");
}
