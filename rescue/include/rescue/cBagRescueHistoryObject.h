/*************************************************************************

        cBagRescueHistoryObject.h

	Keeps a list of pointers to RescueHistoryObject.

        Rod Hanks               December 15th, 1995	 / August 1996

****************************************************************************/

#ifndef cBagRescueHistoryObject_H
#define cBagRescueHistoryObject_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescueHistoryObject;

class cBagRescueHistoryObject
{
protected:
  RescueTree *tree;
public:
  cBagRescueHistoryObject();
  ~cBagRescueHistoryObject();
  void operator+=(RescueHistoryObject *newObject);
  RESCUEBOOL operator-=(RescueHistoryObject *existingObject);
  RescueHistoryObject *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescueHistoryObject *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
};

#endif


