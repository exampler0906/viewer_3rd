/*************************************************************************

        cSetRescuePoint.h

	Keeps a list of pointers to some RescuePoint.

        Rod Hanks              Oct 2003

****************************************************************************/

#ifndef cSetRescuePoint_H
#define cSetRescuePoint_H

#include "boolSupport.h"
#include <stdlib.h>


class RescuePoint;
class RescueContext;

class cSetRescuePoint
{
protected:
  RescuePoint **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescuePoint();
  ~cSetRescuePoint();
  void operator+=(RescuePoint *newObject);
  RESCUEBOOL operator-=(RescuePoint *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescuePoint *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescuePoint *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  RESCUEINT64 IndexOf(RescuePoint *existingObject);
};

#endif



