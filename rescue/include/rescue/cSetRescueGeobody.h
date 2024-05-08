/*************************************************************************

        cSetRescueGeobody.h

	Keeps a list of pointers to some RescueGeobody.

        Rod Hanks               June, 1999

****************************************************************************/

#ifndef cSetRescueGeobody_H
#define cSetRescueGeobody_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueGeobody;
class RescueGeometry;
class RescueContext;

class cSetRescueGeobody
{
protected:
  RescueGeobody **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueGeobody();
  ~cSetRescueGeobody();
  void operator+=(RescueGeobody *newObject);
  RESCUEBOOL operator-=(RescueGeobody *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueGeobody *NthObject(RESCUEINT64 ordinal);
  RescueGeobody *ObjectNamed(RESCUECHAR *nameIn);
  RescueGeobody *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RescueGeometry *GeometryIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueGeobody *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  RESCUEBOOL AnyFileTruncated();
  void FindUniquePropertyNames(cSetString *container);
private:
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);

  friend class RescueModel;
};

#endif



