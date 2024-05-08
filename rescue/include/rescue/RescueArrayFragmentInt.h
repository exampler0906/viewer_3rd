/********************************************************************

  RescueArrayFragmentInt.h

  A dynamically sized array handler for part of a 2-3 dimensional grid of
  4 byte ints for RESCUE's data model. The related grid gives
  the dimensionality.  We keep lowbound and count for each grid.

  Rod Hanks,  December 2000

*********************************************************************/
#ifndef RescueArrayFragmentInt_H
#define RescueArrayFragmentInt_H

#include "myHeaders.h"
#include "RescueArrayFragment.h"

class RescueArrayFragmentInt:public RescueArrayFragment
{
public:
  virtual ~RescueArrayFragmentInt();

  RESCUEINT32 *Value() {return value;}
  RESCUEINT32 ValueLength(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(valueLength, throwIfTooBig);}
  RESCUEINT64 ValueLength64() {return valueLength;}
  RESCUEINT32 ValueLength() {return (RESCUEINT32) valueLength;}
                                    // Return copies of the contents.  
                                    // Do NOT delete returned objects.
  void SetValue(RESCUEINT32 *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid.
                                    // The instance makes a copy of the array.
  void AcceptValue(RESCUEINT32 *valueArray);
                                    // Same as SetValue, except that the pointer
                                    // must have been created with new [].  Instead
                                    // of copying the array the method copies the
                                    // pointer.  Do NOT delete the pointer after
                                    // passing it to the array.
private:
  RescueArrayFragmentInt(RescueArray *parentArrayIn,
                           RESCUEINT64 dimensionsIn, RESCUEINT64 iLowBoundIn, RESCUEINT64 iCountIn,
                                             RESCUEINT64 jLowBoundIn, RESCUEINT64 jCountIn,
                                             RESCUEINT64 kLowBoundIn, RESCUEINT64 kCountIn)
                                             :RescueArrayFragment(parentArrayIn,
                                                                  dimensionsIn, iLowBoundIn, iCountIn,
                                                                                jLowBoundIn, jCountIn,
                                                                                kLowBoundIn, kCountIn)
                                                    {value = 0;}
  virtual void DropMemory() {delete [] value; value = 0;}
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  void PrepareRead();
  RESCUEINT32 ReadInt(FILE *stream, RESCUEBOOL compress);
  void EndRead();
  RESCUEINT32 Replace(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEINT32 data);
  void InitializeArray();

  RESCUEINT32 *value;
  RESCUEINT64 valueLength;
  RESCUEINT32 *readAheadBuffer;
  RESCUEUINT64 readAheadAllocated;
  RESCUEUINT64 readAheadCount;
  RESCUEUINT64 readAheadPos;
  friend class RescueArrayInt;
};

#endif





