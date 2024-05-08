/************************************************************************

  RCHf2DArray.h

  A 2d array that can be allocated as a single array, but accessed via
  2 dimensions, in fortran order. Frees the array only if it created it.

  Templates can be bad trouble, they tend not to travel well, so we don't
  include any templates in the core Rescue Library.  You don't need to
  use these templates if you don't want to.  No Rescue function requires
  them.  I use them as a convienience in making exerciser code.

  Rod Hanks   June, 1999

***********************************************************************/
#include "myHeaders.h"

template <class cType> class RCHf2DArray
{
public:
  RCHf2DArray(RESCUEINT64 maxI, RESCUEINT64 maxJ, cType *values = 0);
  cType &Ndx(RESCUEINT64 i, RESCUEINT64 j);
  cType Value(RESCUEINT64 i, RESCUEINT64 j);
  cType *Array() {return values;}
  RESCUEINT64 ArrayLength64() {return maxI * maxJ;}
  RESCUEINT32 ArrayLength() {return (RESCUEINT32) ArrayLength64();}
  ~RCHf2DArray() {if (freeValues) delete [] values;}
private:
  RESCUEINT64 maxI;
  RESCUEINT64 maxJ;
  cType *values;
  RESCUEBOOL freeValues;
};


template <class cType> RCHf2DArray<cType>::RCHf2DArray(RESCUEINT64 maxIin, RESCUEINT64 maxJin, cType *valuesIn)
                                                      :maxI(maxIin)
                                                      ,maxJ(maxJin)
                                                      ,values(valuesIn)
{
  if (values == 0)
  {
    values = new cType[maxI * maxJ];
    freeValues = TRUE;
  }
  else
  {
    freeValues = FALSE;
  }
}

template <class cType> cType& RCHf2DArray<cType>::Ndx(RESCUEINT64 i, RESCUEINT64 j)
{
  RESCUEINT64 ndx = (j * maxI)
         +  i;
  return values[ndx];
}

template <class cType> cType RCHf2DArray<cType>::Value(RESCUEINT64 i, RESCUEINT64 j)
{
  RESCUEINT64 ndx = (j * maxI)
         +  i;
  return values[ndx];
}



