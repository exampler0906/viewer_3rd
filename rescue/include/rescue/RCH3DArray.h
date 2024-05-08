/************************************************************************

  RCH3DArray.h

  A RESCUEFLOAT array that can be allocated as a single array, but accessed via
  3 dimensions. Frees the array only if it created it.

  For RESCUE, the array has been switched from C to Fortran ordering.

  Rod Hanks   January, 1997

***********************************************************************/
#include "myHeaders.h"
#ifndef RCH3DArray_H
#define RCH3DArray_H

class RCH3DArray
{
public:
  RCH3DArray(RESCUEINT64 maxI, RESCUEINT64 maxJ, RESCUEINT64 maxK, RESCUEFLOAT *values = 0);
  void Set(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT value);
  RESCUEFLOAT &Ndx(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
  RESCUEFLOAT Value(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
  RESCUEFLOAT *Array() {return values;}
  RESCUEINT64 ArrayLength64() {return maxI * maxJ * maxK;}
  RESCUEINT32 ArrayLength() {return (RESCUEINT32) ArrayLength64();}
  RCH3DArray(RESCUEINT32 maxI, RESCUEINT32 maxJ, RESCUEINT32 maxK, RESCUEFLOAT *values = 0);
  void Set(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k, RESCUEFLOAT value);
  RESCUEFLOAT &Ndx(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k) {return Ndx((RESCUEINT64) i, (RESCUEINT64) j, (RESCUEINT64) k);}
  RESCUEFLOAT Value(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k) {return Value((RESCUEINT64) i, (RESCUEINT64) j, (RESCUEINT64) k);}
  RESCUEINT32 ArrayLength(RESCUEBOOL throwIfTooBig);
  ~RCH3DArray() {if (freeValues) delete [] values;}
private:
  RESCUEINT64 maxI;
  RESCUEINT64 maxJ;
  RESCUEINT64 maxK;
  RESCUEFLOAT *values;
  RESCUEBOOL freeValues;
};

#endif






