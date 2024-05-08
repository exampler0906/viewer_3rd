/********************************************************************

  RescueArrayFragmentShort.h

  A dynamically sized array handler for part of a 2-3 dimensional grid of
  unsigned shorts for RESCUE's data model. The related grid gives
  the dimensionality.  We keep lowbound and count for each grid.

  Rod Hanks,  December 2000

*********************************************************************/
#ifndef RescueArrayFragmentShort_H
#define RescueArrayFragmentShort_H

#include "myHeaders.h"
#include "RescueArrayFragment.h"

class RescueArrayFragmentShort:public RescueArrayFragment
{
public:
  virtual ~RescueArrayFragmentShort();

  RESCUEINT64 ValueLength64() {return valueLength;}
  RESCUEINT32 ValueLength() {return (RESCUEINT32) valueLength;}
  RESCUEINT32 ValueLength(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(valueLength, throwIfTooBig);}
  RESCUEUSHORT *Value() {return value;}
                                    // Return copies of the contents.  
                                    // Do NOT delete returned objects.
  void SetValue(RESCUEUSHORT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid.
                                    // The instance makes a copy of the array.
  void AcceptValue(RESCUEUSHORT *valueArray);
                                    // Same as SetValue, except that the pointer
                                    // must have been created with new [].  Instead
                                    // of copying the array the method copies the
                                    // pointer.  Do NOT delete the pointer after
                                    // passing it to the array.
private:
  RescueArrayFragmentShort(RescueArray *parentArrayIn,
                           RESCUEINT64 dimensionsIn, RESCUEINT64 iLowBoundIn, RESCUEINT64 iCountIn,
                                             RESCUEINT64 jLowBoundIn, RESCUEINT64 jCountIn,
                                             RESCUEINT64 kLowBoundIn, RESCUEINT64 kCountIn)
                                             :RescueArrayFragment(parentArrayIn,
                                                                  dimensionsIn, iLowBoundIn, iCountIn,
                                                                                jLowBoundIn, jCountIn,
                                                                                kLowBoundIn, kCountIn)
                                                    {value = 0; valueLength = 0;}
  virtual void DropMemory() {delete [] value; value = 0;}
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  RESCUEUSHORT Replace(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEUSHORT data);
  void InitializeArray();

  RESCUEUSHORT *value;
  RESCUEINT64 valueLength;
  friend class RescueArrayShort;
};

#endif





