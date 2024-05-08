/*************************************************************************

        cBagRescueHistory.h

	Keeps a list of pointers to RescueHistory.

        Rod Hanks               May, 1999

****************************************************************************/

#ifndef cBagRescueHistory_H
#define cBagRescueHistory_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescueHistory;

class cBagRescueHistory
{
protected:
  RescueTree *tree;
public:
  cBagRescueHistory();
  ~cBagRescueHistory();
  void operator+=(RescueHistory *newObject);
  RESCUEBOOL operator-=(RescueHistory *existingObject);
  RescueHistory *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescueHistory *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
};

#endif




