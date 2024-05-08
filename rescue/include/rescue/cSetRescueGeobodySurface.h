/*************************************************************************

        cSetRescueGeobodySurface.h

	Keeps a list of pointers to some RescueGeobodySurface.

        Rod Hanks               June, 1999

****************************************************************************/

#ifndef cSetRescueGeobodySurface_H
#define cSetRescueGeobodySurface_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueGeobodySurface;
class RescueContext;

class cSetRescueGeobodySurface
{
protected:
  RescueGeobodySurface **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueGeobodySurface();
  ~cSetRescueGeobodySurface();
  void operator+=(RescueGeobodySurface *newObject);
  RESCUEBOOL operator-=(RescueGeobodySurface *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueGeobodySurface *NthObject(RESCUEINT64 ordinal);
  RescueGeobodySurface *ObjectNamed(RESCUECHAR *nameIn);
  RescueGeobodySurface *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueGeobodySurface *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
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

  friend class RescueGeobodyVolume;
};

#endif



