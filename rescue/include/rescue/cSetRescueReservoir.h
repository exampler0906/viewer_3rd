/*************************************************************************

        cSetRescueReservoir.h

	Keeps a list of pointers to some RescueReservoir.

        Rod Hanks               May, 1999

****************************************************************************/

#ifndef cSetRescueReservoir_H
#define cSetRescueReservoir_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueReservoir;
class RescueContext;

class cSetRescueReservoir
{
protected:
  RescueReservoir **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueReservoir();
  ~cSetRescueReservoir();
  void operator+=(RescueReservoir *newObject);
  RESCUEBOOL operator-=(RescueReservoir *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueReservoir *NthObject(RESCUEINT64 ordinal);
  RescueReservoir *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueReservoir *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
};

#endif




