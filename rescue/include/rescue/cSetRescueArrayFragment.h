/*************************************************************************

        cSetRescueArrayFragment.h

	Keeps a list of pointers to some RescueArrayFragment.

        Rod Hanks               December, 2000

****************************************************************************/

#ifndef cSetRescueArrayFragment_H
#define ccSetRescueArrayFragment_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueArrayFragment;

class cSetRescueArrayFragment
{
protected:
  RescueArrayFragment **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueArrayFragment();
  ~cSetRescueArrayFragment();
  void operator+=(RescueArrayFragment *newObject);
  RESCUEBOOL operator-=(RescueArrayFragment *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueArrayFragment *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueArrayFragment *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
};

#endif




