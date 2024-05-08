/********************************************************************

  RescueBitArray.h

  A dynamically sized array handler for N dimensional grids of
  bit fields for RESCUE's data model. 
  
  This class is not accessed directly by the
  application.  See RescueGeometry for an example of usage.

  For the moment, we are assuming that sizeof(RESCUEINT64) is an even
  multiple of bitFieldWidth.

  Rod Hanks,  December 1998

*********************************************************************/
#ifndef RescueBitArray_H
#define RescueBitArray_H

#include "myHeaders.h"
class RescueBuffer;

class RescueBitArray:public RescueObject
{
public:
  RESCUEINT32 BitField(RESCUEINT64 zeroBasedNdx);
  RESCUEINT32 BitField(RESCUEINT32 zeroBasedNdx) {return BitField((RESCUEINT64) zeroBasedNdx);}
  void SetBitField(RESCUEINT64 zeroBasedNdx, RESCUEINT32 value);
  void SetBitField(RESCUEINT32 zeroBasedNdx, RESCUEINT32 value) {SetBitField((RESCUEINT64) zeroBasedNdx, value);}
  ~RescueBitArray() {delete [] data;}

private:
  RescueBitArray(RescueContext *context, RESCUEINT64 totalElements, RESCUEINT32 bitFieldWidthIn);
  RescueBitArray(RescueContext *context, RescueBuffer &buf);
  RescueBitArray(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Archive(RescueBuffer &buf);
  void CommonInitialization(RescueContext *context, RESCUEINT64 totalElements, RESCUEINT32 bitFieldWidthIn);
  void SwapAxes(bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes);
  void SwapAxes(bool swapI, RESCUEINT64 iNodes, 
                bool swapJ, RESCUEINT64 jNodes,
                bool swapK, RESCUEINT64 kNodes);

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.

  unsigned RESCUEINT32 *data;
  RESCUEINT32 fieldsPerInt;
  RESCUEINT32 bitFieldWidth;
  RESCUEINT64 bitFieldCount;
  RESCUEINT64 intCount;
  unsigned RESCUEINT32 mask;
  RescueContext *context;

  friend class RescueGeometry;
  friend class RescueIJSurface;
  friend class RescueTriangulatedSurface;
};

#endif





