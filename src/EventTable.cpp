#include "EventTable.h"

EventTable::EventTable()
{
   mEvtCounter = 0;
};

bool EventTable::insertEvent(string lEvent, unsigned long int &lEvtCounter)
{
   pair<set<string>::iterator,bool> ret;

   pthread_mutex_lock(&mMutexEvtCounter);
   ret = mEventSet.insert(lEvent);
   mLastEvents.push_back(lEvent);
   lEvtCounter = ++mEvtCounter;
   pthread_mutex_unlock(&mMutexEvtCounter);

   return (ret.second);
};

vector<string> EventTable::getLastEvents()
{
   vector<string> lLastEvents;

   pthread_mutex_lock(&mMutexEvtCounter);
   lLastEvents = mLastEvents;
   mLastEvents.clear();
   pthread_mutex_unlock(&mMutexEvtCounter);

   return (lLastEvents);
}
