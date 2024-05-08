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

        cSetRescuePolyLineNodeUV.h

	Keeps a list of pointers to some RescuePolyLineNodeUV.

        Rod Hanks               January 18th, 1995	 /  August 1996

****************************************************************************/

#ifndef cSetRescuePolyLineNodeUV_H
#define cSetRescuePolyLineNodeUV_H

#include "boolSupport.h"
#include <stdlib.h>

class RescuePolyLineNodeUV;
class RescueContext;
class RescueOrientationLedger;

class cSetRescuePolyLineNodeUV
{
protected:
  RescuePolyLineNodeUV **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescuePolyLineNodeUV();
  ~cSetRescuePolyLineNodeUV();
  void operator+=(RescuePolyLineNodeUV *newObject);
  RESCUEBOOL operator-=(RescuePolyLineNodeUV *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescuePolyLineNodeUV *NthObject(RESCUEINT64 ordinal);
  RescuePolyLineNodeUV *ObjectNamed(RESCUECHAR *nameIn);
  RescuePolyLineNodeUV *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescuePolyLineNodeUV *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
private:
  void InsertAt(RESCUEINT64 ndx, RescuePolyLineNodeUV *newObject);
  void SetOrientation(RescueOrientationLedger *ledger);

  friend class RescuePolyLine;
  friend class RescueWireframe;
};

#endif



