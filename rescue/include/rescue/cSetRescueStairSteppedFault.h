/*************************************************************************

        cSetRescueStairSteppedFault.h

	Keeps a list of pointers to some RescueStairSteppedFault.

        Rod Hanks               June, 1999

****************************************************************************/

#ifndef cSetRescueStairSteppedFault_H
#define cSetRescueStairSteppedFault_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueStairSteppedFault;
class RescueContext;

class cSetRescueStairSteppedFault
{
protected:
  RescueStairSteppedFault **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueStairSteppedFault();
  ~cSetRescueStairSteppedFault();
  void operator+=(RescueStairSteppedFault *newObject);
  RESCUEBOOL operator-=(RescueStairSteppedFault *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueStairSteppedFault *NthObject(RESCUEINT64 ordinal);
  RescueStairSteppedFault *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEBOOL AnyFileTruncated();
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueStairSteppedFault *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  void FindUniquePropertyNames(cSetString *container);
};

#endif



