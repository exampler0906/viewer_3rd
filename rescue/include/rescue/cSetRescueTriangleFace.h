/*************************************************************************

        cSetRescueTriangleFace.h

	Keeps a list of pointers to some RescueTriangleFace.

        Rod Hanks              June, 1999

****************************************************************************/

#ifndef cSetRescueTriangleFace_H
#define cSetRescueTriangleFace_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueTriangleFace;
class RescueContext;

class cSetRescueTriangleFace
{
protected:
  RescueTriangleFace **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueTriangleFace();
  ~cSetRescueTriangleFace();
  void operator+=(RescueTriangleFace *newObject);
  RESCUEBOOL operator-=(RescueTriangleFace *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueTriangleFace *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueTriangleFace *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  RESCUEINT64 IndexOf(RescueTriangleFace *existingObject);
  RESCUEINT32 IndexOf(RescueTriangleFace *existingObject, RESCUEBOOL throwIfTooBig);
};

#endif



