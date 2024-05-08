/********************************************************************

  RescueArrayFragment.h

  A dynamically sized array handler for part of an 2-3 dimensional grid of
  values for RESCUE's data model. The related grid gives
  the dimensionality.  We keep lowbound and count for each grid.

  This abstract superclass can be instantiated as one of it's subclasses.

  Rod Hanks,  December 2000

*********************************************************************/
#ifndef RescueArrayFragment_H
#define RescueArrayFragment_H

#include "myHeaders.h"
#include "RescueArray.h"

class RescueArrayFragment
{
public:
  RescueArray *ParentArray() {return parentArray;}
  RESCUEINT64 Dimensions64() {return dimensions;}
  RESCUEINT64 ILowBound64()  {return iLowBound;}
  RESCUEINT64 ICount64()     {return iCount;}
  RESCUEINT64 JLowBound64()  {return jLowBound;}
  RESCUEINT64 JCount64()     {return jCount;}
  RESCUEINT64 KLowBound64()  {return kLowBound;}
  RESCUEINT64 KCount64()     {return kCount;}
  RESCUEINT64 NodeCount64();

  RESCUEINT32 Dimensions() {return RescueContext::Return32For64(dimensions, false);}
  RESCUEINT32 ILowBound()  {return RescueContext::Return32For64(iLowBound, false);}
  RESCUEINT32 ICount()     {return RescueContext::Return32For64(iCount, false);}
  RESCUEINT32 JLowBound()  {return RescueContext::Return32For64(jLowBound, false);}
  RESCUEINT32 JCount()     {return RescueContext::Return32For64(jCount, false);}
  RESCUEINT32 KLowBound()  {return RescueContext::Return32For64(kLowBound, false);}
  RESCUEINT32 KCount()     {return RescueContext::Return32For64(kCount, false);}
  RESCUEINT32 NodeCount()  {return RescueContext::Return32For64(NodeCount64(), false);}

  RESCUEINT32 ILowBound(RESCUEBOOL throwIfTooBig)  {return RescueContext::Return32For64(iLowBound, throwIfTooBig);}
  RESCUEINT32 ICount(RESCUEBOOL throwIfTooBig)     {return RescueContext::Return32For64(iCount, throwIfTooBig);}
  RESCUEINT32 JLowBound(RESCUEBOOL throwIfTooBig)  {return RescueContext::Return32For64(jLowBound, throwIfTooBig);}
  RESCUEINT32 JCount(RESCUEBOOL throwIfTooBig)     {return RescueContext::Return32For64(jCount, throwIfTooBig);}
  RESCUEINT32 KLowBound(RESCUEBOOL throwIfTooBig)  {return RescueContext::Return32For64(kLowBound, throwIfTooBig);}
  RESCUEINT32 KCount(RESCUEBOOL throwIfTooBig)     {return RescueContext::Return32For64(kCount, throwIfTooBig);}
  RESCUEINT32 NodeCount(RESCUEBOOL throwIfTooBig);
  virtual ~RescueArrayFragment() {};
protected:
  RescueArrayFragment(RescueArray *parentArrayIn,
                      RESCUEINT64 dimensionsIn, RESCUEINT64 iLowBoundIn, RESCUEINT64 iCountIn,
                                        RESCUEINT64 jLowBoundIn, RESCUEINT64 jCountIn,
                                        RESCUEINT64 kLowBoundIn, RESCUEINT64 kCountIn)
                                        :parentArray(parentArrayIn)
                                        ,dimensions(dimensionsIn)
                                        ,iLowBound(iLowBoundIn)
                                        ,iCount(iCountIn)
                                        ,jLowBound(jLowBoundIn)
                                        ,jCount(jCountIn)
                                        ,kLowBound(kLowBoundIn)
                                        ,kCount(kCountIn) {};
  virtual void DropMemory()=0;
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion)=0;

  RescueArray *parentArray;
  RESCUEINT64 dimensions;
  RESCUEINT64 iLowBound;
  RESCUEINT64 iCount;
  RESCUEINT64 jLowBound;
  RESCUEINT64 jCount;
  RESCUEINT64 kLowBound;
  RESCUEINT64 kCount;

  friend class RescueArray;
};

#endif





