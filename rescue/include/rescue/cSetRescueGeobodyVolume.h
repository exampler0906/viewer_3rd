/*************************************************************************

        cSetRescueGeobodyVolume.h

	Keeps a list of pointers to some RescueGeobodyVolume.

        Rod Hanks               June, 1999

****************************************************************************/

#ifndef cSetRescueGeobodyVolume_H
#define cSetRescueGeobodyVolume_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueGeobodyVolume;
class RescueContext;

class cSetRescueGeobodyVolume
{
protected:
  RescueGeobodyVolume **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueGeobodyVolume();
  ~cSetRescueGeobodyVolume();
  void operator+=(RescueGeobodyVolume *newObject);
  RESCUEBOOL operator-=(RescueGeobodyVolume *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueGeobodyVolume *NthObject(RESCUEINT64 ordinal);
  RescueGeobodyVolume *ObjectNamed(RESCUECHAR *nameIn);
  RescueGeobodyVolume *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueGeobodyVolume *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  void FindUniquePropertyNames(cSetString *container);
private:
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);

  friend class RescueGeobodyPart;
};

#endif



