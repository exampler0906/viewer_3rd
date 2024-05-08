/*************************************************************************

        cSetRescueTriangleVertex.h

	Keeps a list of pointers to some RescueTriangleVertex.

        Rod Hanks              June, 1999

****************************************************************************/

#ifndef cSetRescueTriangleVertex_H
#define cSetRescueTriangleVertex_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueTriangleVertex;
class RescueContext;

class cSetRescueTriangleVertex
{
protected:
  RescueTriangleVertex **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueTriangleVertex();
  ~cSetRescueTriangleVertex();
  void operator+=(RescueTriangleVertex *newObject);
  RESCUEBOOL operator-=(RescueTriangleVertex *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueTriangleVertex *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueTriangleVertex *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  RESCUEINT64 IndexOf(RescueTriangleVertex *existingObject);
};

#endif



