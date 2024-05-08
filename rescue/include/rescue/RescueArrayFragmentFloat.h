/********************************************************************

  RescueArrayFragmentFloat.h

  A dynamically sized array handler for part of a 2-3 dimensional grid of
  floating points for RESCUE's data model. The related grid gives
  the dimensionality.  We keep lowbound and count for each grid.

  Rod Hanks,  December 2000

*********************************************************************/
#ifndef RescueArrayFragmentFloat_H
#define RescueArrayFragmentFloat_H

#include "myHeaders.h"
#include "RescueArrayFragment.h"

class RescueArrayFragmentFloat:public RescueArrayFragment
{
public:
  virtual ~RescueArrayFragmentFloat();
  RESCUEINT64 ValueLength64() {return valueLength;}
  RESCUEINT32 ValueLength() {return (RESCUEINT32) valueLength;}
  RESCUEINT32 ValueLength(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(valueLength, throwIfTooBig);}
  RESCUEFLOAT *Value() {return value;}
                                    // Return copies of the contents.  
                                    // Do NOT delete returned objects.
  void AllValues(RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 valueCount);         
                                    // Writes the values into an array allocated by
                                    // the caller.  Better for those who want to do
                                    // their own memory allocation.  Especially good
                                    // for Java RJNI users.  valueCount is the number
                                    // of good values in the buffer (excluding offset).
  void SetValue(RESCUEFLOAT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid.
                                    // The instance makes a copy of the array.
  void AcceptValue(RESCUEFLOAT *valueArray);
                                    // Same as SetValue, except that the pointer
                                    // must have been created with new [].  Instead
                                    // of copying the array the method copies the
                                    // pointer.  Do NOT delete the pointer after
                                    // passing it to the array.
private:
  RescueArrayFragmentFloat(RescueArray *parentArrayIn,
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
  void PrepareRead();
  RESCUEFLOAT ReadFloat(FILE *stream, RESCUEBOOL compress);
  void EndRead();
  RESCUEFLOAT Replace(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEFLOAT data);
  void InitializeArray();

  RESCUEFLOAT *value;
  RESCUEINT64 valueLength;
  RESCUEFLOAT *readAheadBuffer;
  RESCUEUINT64 readAheadAllocated;
  RESCUEUINT64 readAheadCount;
  RESCUEUINT64 readAheadPos;
  friend class RescueArrayFloat;
};

#endif





