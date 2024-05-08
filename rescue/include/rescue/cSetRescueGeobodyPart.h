/*************************************************************************

        cSetRescueGeobodyPart.h

	Keeps a list of pointers to some RescueGeobodyPart.

        Rod Hanks               June, 1999

****************************************************************************/

#ifndef cSetRescueGeobodyPart_H
#define cSetRescueGeobodyPart_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueGeobodyPart;
class RescueGeometry;
class RescueContext;

class cSetRescueGeobodyPart
{
protected:
  RescueGeobodyPart **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueGeobodyPart();
  ~cSetRescueGeobodyPart();
  void operator+=(RescueGeobodyPart *newObject);
  RESCUEBOOL operator-=(RescueGeobodyPart *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueGeobodyPart *NthObject(RESCUEINT64 ordinal);
  RescueGeobodyPart *ObjectNamed(RESCUECHAR *nameIn);
  RescueGeobodyPart *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RescueGeometry *GeometryIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueGeobodyPart *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);
  RESCUEBOOL AnyFileTruncated();
  void FindUniquePropertyNames(cSetString *container);

  friend class RescueGeobody;
};

#endif



