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

        cBagRescueGeometry.h

	Keeps a list of pointers to RescueGeometry.

        Rod Hanks               December 15th, 1995	 / August 1996

****************************************************************************/

#ifndef cBagRescueGeometry_H
#define cBagRescueGeometry_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescueGeometry;

class cBagRescueGeometry
{
protected:
  RescueTree *tree;
public:
  cBagRescueGeometry();
  ~cBagRescueGeometry();
  void operator+=(RescueGeometry *newObject);
  RESCUEBOOL operator-=(RescueGeometry *existingObject);
  RescueGeometry *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescueGeometry *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
};

#endif




