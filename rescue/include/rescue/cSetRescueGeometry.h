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

        cSetRescueGeometry.h

	Keeps a list of pointers to some RescueGeometry.

        Rod Hanks               February, 1999

****************************************************************************/

#ifndef cSetRescueGeometry_H
#define cSetRescueGeometry_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueGeometry;
class RescueContext;

class cSetRescueGeometry
{
protected:
  RescueGeometry **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueGeometry();
  ~cSetRescueGeometry();
  void operator+=(RescueGeometry *newObject);
  RESCUEBOOL operator-=(RescueGeometry *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueGeometry *NthObject(RESCUEINT64 ordinal);
  RescueGeometry *ObjectNamed(RESCUECHAR *nameIn);
  RescueGeometry *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT32 Count(void);
  RESCUEINT64 Count64(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueGeometry *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  void Dispose();
  RESCUEBOOL AnyFileTruncated();
  void FindUniquePropertyNames(cSetString *container);
};

#endif



