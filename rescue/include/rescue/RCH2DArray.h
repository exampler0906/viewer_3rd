/************************************************************************

  RCH2DArray.h

  A RESCUEFLOAT array that can be allocated as a single array, but accessed via
  2 dimensions. Frees the array only if it created it.

  For RESCUE, the array has been switched from C to Fortran ordering.

  Rod Hanks   January, 1997

***********************************************************************/
#include "myHeaders.h"

class RCH2DArray
{
public:
  RCH2DArray(RESCUEINT64 maxI, RESCUEINT64 maxJ, RESCUEFLOAT *values = 0);
  void Set(RESCUEINT64 i, RESCUEINT64 j, RESCUEFLOAT value);
  RESCUEFLOAT &Ndx(RESCUEINT64 i, RESCUEINT64 j);
  RESCUEFLOAT Value(RESCUEINT64 i, RESCUEINT64 j);
  RESCUEFLOAT *Array() {return values;}
  RESCUEINT64 ArrayLength64() {return maxI * maxJ;}
  RESCUEINT32 ArrayLength() {return (RESCUEINT32) ArrayLength64();}
  RCH2DArray(RESCUEINT32 maxI, RESCUEINT32 maxJ, RESCUEFLOAT *values = 0);
  void Set(RESCUEINT32 i, RESCUEINT32 j, RESCUEFLOAT value) {Set((RESCUEINT64) i, (RESCUEINT64) j, value);}
  RESCUEFLOAT &Ndx(RESCUEINT32 i, RESCUEINT32 j) {return Ndx((RESCUEINT64) i, (RESCUEINT64) j);}
  RESCUEFLOAT Value(RESCUEINT32 i, RESCUEINT32 j) {return Value((RESCUEINT64) i, (RESCUEINT64) j);}
  RESCUEINT32 ArrayLength(RESCUEBOOL throwIfTooBig);
  ~RCH2DArray() {if (freeValues) delete [] values;}
private:
  RESCUEINT64 maxI;
  RESCUEINT64 maxJ;
  RESCUEFLOAT *values;
  RESCUEBOOL freeValues;
};





