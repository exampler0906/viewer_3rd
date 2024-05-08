/*************************************************************************

        cSetRescueHistory.h

	Keeps a list of pointers to some RescueHistory.

        Rod Hanks               May, 1999

****************************************************************************/

#ifndef cSetRescueHistory_H
#define cSetRescueHistory_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueHistory;
class RescueContext;

class cSetRescueHistory
{
protected:
  RescueHistory **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueHistory();
  ~cSetRescueHistory();
  void operator+=(RescueHistory *newObject);
  RESCUEBOOL operator-=(RescueHistory *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueHistory *NthObject(RESCUEINT64 ordinal);
  RescueHistory *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueHistory *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
};

#endif




