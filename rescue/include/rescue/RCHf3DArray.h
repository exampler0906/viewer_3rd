/************************************************************************

  RCHf3DArray.h

  A 3d array that can be allocated as a single array, but accessed via
  3 dimensions, in fortran order. Frees the array only if it created it.

  Templates can be bad trouble, they tend not to travel well, so we don't
  include any templates in the core Rescue Library.  You don't need to
  use these templates if you don't want to.  No Rescue function requires
  them.  I use them as a convienience in making exerciser code.

  Rod Hanks   June, 1999

***********************************************************************/
#include "myHeaders.h"

template <class cType> class RCHf3DArray
{
public:
  RCHf3DArray(RESCUEINT64 maxI, RESCUEINT64 maxJ, RESCUEINT64 maxK, cType *values = 0);
  cType &Ndx(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
  cType Value(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
  cType *Array() {return values;}
  RESCUEINT64 ArrayLength64() {return maxI * maxJ * maxK;}
  RESCUEINT32 ArrayLength() {return (RESCUEINT32) ArrayLength64();}
  ~RCHf3DArray() {if (freeValues) delete [] values;}
private:
  RESCUEINT64 maxI;
  RESCUEINT64 maxJ;
  RESCUEINT64 maxK;
  cType *values;
  RESCUEBOOL freeValues;
};


template <class cType> RCHf3DArray<cType>::RCHf3DArray(RESCUEINT64 maxIin, RESCUEINT64 maxJin, RESCUEINT64 maxKin,
                                                       cType *valuesIn)
                                                      :maxI(maxIin)
                                                      ,maxJ(maxJin)
                                                      ,maxK(maxKin)
                                                      ,values(valuesIn)
{
  if (values == 0)
  {
    values = new cType[maxI * maxJ * maxK];
    freeValues = TRUE;
  }
  else
  {
    freeValues = FALSE;
  }
}

template <class cType> cType& RCHf3DArray<cType>::Ndx(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k)
{
  RESCUEINT64 ndx = (k * (maxJ * maxI))
         + (j * maxI)
         +  i;
  return values[ndx];
}

template <class cType> cType RCHf3DArray<cType>::Value(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k)
{
  RESCUEINT64 ndx = (k * (maxJ * maxI))
         + (j * maxI)
         +  i;
  return values[ndx];
}



