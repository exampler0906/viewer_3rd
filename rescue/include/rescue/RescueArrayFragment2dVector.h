/********************************************************************

  RescueArrayFragment2dVector.h

  A dynamically sized array handler for part of a 2-3 dimensional grid of
  2d vectors for RESCUE's data model. The related grid gives
  the dimensionality.  We keep lowbound and count for each grid.

  Rod Hanks,  December 2000

*********************************************************************/
#ifndef RescueArrayFragment2dVector_H
#define RescueArrayFragment2dVector_H

#include "myHeaders.h"
#include "RescueArrayFragment.h"
#include "RescueArray2dVector.h"

class RescueArrayFragment2dVector:public RescueArrayFragment
{
public:
  virtual ~RescueArrayFragment2dVector();

  Rescue2dVector *Value() {return value;}
  RESCUEINT64 ValueLength64() {return valueLength;}
  RESCUEINT32 ValueLength() {return (RESCUEINT32) valueLength;}
  RESCUEINT32 ValueLength(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(valueLength, throwIfTooBig);}
                                    // Return copies of the contents.  
                                    // Do NOT delete returned objects.
  void SetValue(Rescue2dVector *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid.
                                    // The instance makes a copy of the array.
  void AcceptValue(Rescue2dVector *valueArray);
                                    // Same as SetValue, except that the pointer
                                    // must have been created with new [].  Instead
                                    // of copying the array the method copies the
                                    // pointer.  Do NOT delete the pointer after
                                    // passing it to the array.
private:
  RescueArrayFragment2dVector(RescueArray *parentArrayIn,
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
  Rescue2dVector Replace(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, Rescue2dVector data);
  void InitializeArray();

  Rescue2dVector *value;
  RESCUEINT64 valueLength;
  friend class RescueArray2dVector;
};

#endif





