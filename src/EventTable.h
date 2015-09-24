#ifndef EventTable_h
#define EventTable_h

#include <pthread.h>
#include <set>
#include <string>
#include <vector>
using namespace std;

class EventTable
{
public:
   EventTable();

   bool insertEvent(string lEvent, unsigned long int &lEvtCounter);
   vector<string> getLastEvents();

private:
   set<string>    mEventSet;           // Unique events insertion table - set
   vector<string> mLastEvents;         // Last received events list
   unsigned long int mEvtCounter;

   pthread_mutex_t mMutexEvtCounter;
};

#endif
