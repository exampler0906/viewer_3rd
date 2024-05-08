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

        cSetRescueWellboreProperty.h

	Keeps a list of pointers to some RescueWellboreProperty.

        Rod Hanks               January 18th, 1995	 /  August 1996

****************************************************************************/

#ifndef cSetRescueWellboreProperty_H
#define cSetRescueWellboreProperty_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueWellboreProperty;
class RescueContext;

class cSetRescueWellboreProperty
{
protected:
  RescueWellboreProperty **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueWellboreProperty();
  ~cSetRescueWellboreProperty();
  void operator+=(RescueWellboreProperty *newObject);
  RESCUEBOOL operator-=(RescueWellboreProperty *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueWellboreProperty *NthObject(RESCUEINT64 ordinal);
  RescueWellboreProperty *ObjectNamed(RESCUECHAR *nameIn);
  RescueWellboreProperty *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueWellboreProperty *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  void Dispose();
  RESCUEBOOL AnyFileTruncated();
};

#endif



