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

        cSetRescueIJSurface.h

	Keeps a list of pointers to some RescueIJSurface.

        Rod Hanks               December, 1999

****************************************************************************/

#ifndef cSetRescueIJSurface_H
#define cSetRescueIJSurface_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueIJSurface;
class RescueContext;

class cSetRescueIJSurface
{
protected:
  RescueIJSurface **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueIJSurface();
  ~cSetRescueIJSurface();
  void operator+=(RescueIJSurface *newObject);
  RESCUEBOOL operator-=(RescueIJSurface *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueIJSurface *NthObject(RESCUEINT64 ordinal);
  RescueIJSurface *ObjectNamed(RESCUECHAR *nameIn);
  RescueIJSurface *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueIJSurface *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
  RESCUEBOOL AnyFileTruncated();
private:

  friend class RescueModel;
};

#endif



