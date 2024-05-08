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

        cSetString.h

	Keeps a list of RCHSTrings.

        Rod Hanks               May 1998

****************************************************************************/

#ifndef cSetString_H
#define cSetString_H

#include "boolSupport.h"
class RCHString;

class cSetString
{
protected:
  RCHString **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetString();
  ~cSetString();
  void operator+=(RCHString *newObject);
  RESCUEBOOL operator-=(RCHString * existingObject);
  RCHString *NthObject(RESCUEINT64 ordinal);
  RCHString *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT64 Count64(void) {return count;}
  RESCUEINT32 Count(void) {return (RESCUEINT32) count;}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RESCUEBOOL Contains(RCHString *example);
  void EmptySelf();
  void AddIfUnique(const RESCUECHAR *toAdd);
};

#endif




