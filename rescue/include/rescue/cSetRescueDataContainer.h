/*************************************************************************

        cSetRescueDataContainer.h

	Keeps a list of pointers to some RescueDataContainer.

        Rod Hanks               Feb 2006

****************************************************************************/

#ifndef cSetRescueDataContainer_H
#define cSetRescueDataContainer_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueDataContainer;
class RescueContext;

class cSetRescueDataContainer
{
protected:
  RescueDataContainer **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;
  RESCUEINT64 identifier;
  RESCUEINT64 fileVersion;
  RescueModel *model;

public:
  RESCUEINT64 Identifier() {return identifier;}
  cSetRescueDataContainer(RescueModel *modelIn);
  ~cSetRescueDataContainer();
  void operator+=(RescueDataContainer *newObject);
  RESCUEBOOL operator-=(RescueDataContainer *existingObject); // Will dispose the RescueDataContainer.
  RESCUEBOOL operator-=(RESCUEINT64 ndx);                             // Will dispose the RescueDataContainer.
  RescueDataContainer *NthObject(RESCUEINT64 ordinal);
  RescueDataContainer *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueDataContainer *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void Archive(FILE *archiveFile);
  void UnArchive(FILE *archiveFile);
  void Relink(RescueObject *parent);
  RESCUEBOOL AnyFileTruncated();
  RESCUEBOOL FileTruncated();
  RESCUEINT64 FileVersion()  {return fileVersion;} // Bumps when file is written.
  void FindUniquePropertyNames(cSetString *container);
private:
  void EmptySelf(void);                                       // Will dispose all the RescueDataContainer.
  void Archive();
  cSetRescueDataContainer(RescueModel *modelIn, RESCUEINT64 containerId);

  friend class RescueStairSteppedFault;
  friend class RescueSurfaceToGrid;
  friend class RescueInterfaceSurfaceDesc;
  friend class RescueParametricLGRMap;
  friend class RescueModel;
  friend class RescueGeometry;
  friend class RescueSurface;
};

#endif



