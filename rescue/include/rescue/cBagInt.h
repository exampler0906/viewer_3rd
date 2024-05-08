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

        cBagInt.h

  Keeps a list of integers.

    Rod Hanks               December 15th, 1995	 / August 1996

****************************************************************************/

#ifndef cBagInt_H
#define cBagInt_H

#include "boolSupport.h"

class cBagInt
{
protected:
  RESCUEINT64 *objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cBagInt();
  ~cBagInt();
  void operator+=(RESCUEINT64 newObject);
  RESCUEBOOL operator-=(RESCUEINT64 existingObject);
  RESCUEINT64 NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return count;}
  RESCUEINT32 Count(void) {return (RESCUEINT32) count;}
  RESCUEBOOL Contains(RESCUEINT64 example);
};

#endif




