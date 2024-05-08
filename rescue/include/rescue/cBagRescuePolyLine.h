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

        cBagRescuePolyLine.h

	Keeps a list of pointers to RescuePolyLine.

        Rod Hanks               December 15th, 1995	 / August 1996

****************************************************************************/

#ifndef cBagRescuePolyLine_H
#define cBagRescuePolyLine_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescuePolyLine;

class cBagRescuePolyLine
{
protected:
  RescueTree *tree;
public:
  cBagRescuePolyLine();
  ~cBagRescuePolyLine();
  void operator+=(RescuePolyLine *newObject);
  RESCUEBOOL operator-=(RescuePolyLine *existingObject);
  RescuePolyLine *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescuePolyLine *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
};

#endif




