/*************************************************************************

        cSetRescueSurfaceToGrid.h

	Keeps a list of pointers to some RescueSurfaceToGrid.

        Rod Hanks               June, 1999

****************************************************************************/

#ifndef cSetRescueSurfaceToGrid_H
#define cSetRescueSurfaceToGrid_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueSurfaceToGrid;
class RescueContext;

class cSetRescueSurfaceToGrid
{
protected:
  RescueSurfaceToGrid **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueSurfaceToGrid();
  ~cSetRescueSurfaceToGrid();
  void operator+=(RescueSurfaceToGrid *newObject);
  RESCUEBOOL operator-=(RescueSurfaceToGrid *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueSurfaceToGrid *NthObject(RESCUEINT64 ordinal);
  RescueSurfaceToGrid *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueSurfaceToGrid *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  RESCUEBOOL AnyFileTruncated();
  void FindUniquePropertyNames(cSetString *container);
};

#endif



