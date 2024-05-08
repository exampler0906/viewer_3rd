/*************************************************************************

        cSetRescuePolyLineNodeUVT.h

	Keeps a list of pointers to some RescuePolyLineNodeUVT.

        Rod Hanks               May 2002

****************************************************************************/

#ifndef cSetRescuePolyLineNodeUVT_H
#define cSetRescuePolyLineNodeUVT_H

#include "boolSupport.h"
#include <stdlib.h>

class RescuePolyLineNodeUVT;
class RescueContext;

class cSetRescuePolyLineNodeUVT
{
protected:
  RescuePolyLineNodeUVT **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescuePolyLineNodeUVT();
  ~cSetRescuePolyLineNodeUVT();
  void operator+=(RescuePolyLineNodeUVT *newObject);
  RESCUEBOOL operator-=(RescuePolyLineNodeUVT *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescuePolyLineNodeUVT *NthObject(RESCUEINT64 ordinal);
  RescuePolyLineNodeUVT *ObjectNamed(RESCUECHAR *nameIn);
  RescuePolyLineNodeUVT *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescuePolyLineNodeUVT *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
private:
  void InsertAt(RESCUEINT64 ndx, RescuePolyLineNodeUVT *newObject);

  friend class RescuePolyLine;
};

#endif



