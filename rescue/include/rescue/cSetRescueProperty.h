/****************************************************************************

Copyright 1995 Petrotechnical Open Software Corporation

POSC grants permission to copy or reproduce this material in its original
form for internal use only.

This software is subject to the provision of the "POSC Software License
Agreement" which states in part:

1) Licensee accepts a non-exclusive, non-transferable, license  to use,
display, modify and distribute works derived from the licensed documentation
and Software Product.

2) Licensee shall have no right to distribute in its original form any
Software Product or documentation licensed under this agreement.

****************************************************************************/
/*************************************************************************

        cSetRescueProperty.h

	Keeps a list of pointers to some RescueProperty.

        Rod Hanks               January 18th, 1995	 /  August 1996

****************************************************************************/

#ifndef cSetRescueProperty_H
#define cSetRescueProperty_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueProperty;
class RescueModel;
class RescueContext;

class cSetRescueProperty
{
protected:
  RescueProperty **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueProperty();
  ~cSetRescueProperty();
  void operator+=(RescueProperty *newObject);
  RESCUEBOOL operator-=(RescueProperty *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueProperty *NthObject(RESCUEINT64 ordinal);
  RescueProperty *ObjectNamed(RESCUECHAR *nameIn);
  RescueProperty *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueProperty *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  void Dispose();
  RESCUEBOOL AnyFileTruncated();
  void Relinquish(RescueProperty *existingObject);
  void RelinquishAll();
  void FindUniquePropertyNames(cSetString *container);
private:
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);

  friend class RescuePropertyGroup;
  friend class RescueSurface;
};

#endif



