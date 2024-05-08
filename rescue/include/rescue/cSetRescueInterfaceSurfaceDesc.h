/*************************************************************************

        cSetRescueInterfaceSurfaceDesc.h

	Keeps a list of pointers to RescueInterfaceSurfaceDesc.

        Rod Hanks               June 2003

****************************************************************************/

#ifndef cSetRescueInterfaceSurfaceDesc_H
#define cSetRescueInterfaceSurfaceDesc_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueInterfaceSurfaceDesc;
class RescueContext;

class cSetRescueInterfaceSurfaceDesc
{
protected:
  RescueInterfaceSurfaceDesc **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueInterfaceSurfaceDesc();
  ~cSetRescueInterfaceSurfaceDesc();
  void operator+=(RescueInterfaceSurfaceDesc *newObject);
  RESCUEBOOL operator-=(RescueInterfaceSurfaceDesc *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueInterfaceSurfaceDesc *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueInterfaceSurfaceDesc *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  RESCUEBOOL AnyFileTruncated();
  void Relink(RescueObject *parent);
  void FindUniquePropertyNames(cSetString *container);
};

#endif



