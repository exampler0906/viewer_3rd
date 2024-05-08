/********************************************************************

  RescueArrayShort.h

  A dynamically sized array handler for N dimensional grids of
  floating points for RESCUE's data model. The related grid gives
  the dimensionality.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RescueArrayShort_H
#define RescueArrayShort_H

#include "myHeaders.h"
#include "RescueArray.h"
#include "RescueLookup.h"
class RescueArrayFragment;

class RescueArrayShort:public RescueArray
{
public:
  ~RescueArrayShort();
  RESCUEINT64 NullValue() {return nullValue;}
  RescueLookup *LookupTable() {return lookupTable;}
  RESCUEINT64 ValueLength64() {return valueLength;}
  RESCUEINT32 ValueLength() {return (RESCUEINT32) valueLength;}
  RESCUEINT32 ValueLength(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(valueLength, throwIfTooBig);}
  RESCUEUSHORT *Value() {return value;}
  RESCUEUSHORT *DemandValue();
                                    // Return copies of the contents.  
                                    // Do NOT delete returned objects.
  void AllValues(RESCUEUSHORT *buffer, RESCUEINT64 offset, RESCUEINT64 valueCount);         
  void AllValues(RESCUEUSHORT *buffer, RESCUEINT32 offset, RESCUEINT32 valueCount)
              {AllValues(buffer, (RESCUEINT64) offset, (RESCUEINT64) valueCount);}
                                    // Writes the values into an array allocated by
                                    // the caller.  Better for those who want to do
                                    // their own memory allocation.  Especially good
                                    // for Java RJNI users.  valueCount is the number
                                    // of good values in the buffer (excluding offset).
  void SetValue(RESCUEUSHORT nullValue, RESCUEUSHORT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid.
                                    // The instance makes a copy of the array.
                                    // If fragments are loaded they are dropped,
                                    // not merged.
  void AcceptValue(RESCUEUSHORT nullValue, RESCUEUSHORT *valueArray);
                                    // Same as SetValue, except that the pointer
                                    // must have been created with new [].  Instead
                                    // of copying the array the method copies the
                                    // pointer.  Do NOT delete the pointer after
                                    // passing it to the array.
                                    // If fragments are loaded they are dropped,
                                    // not merged.
  void SetNullValue(RESCUEUSHORT nullValueIn) {nullValue = nullValueIn;}
  virtual RESCUEBOOL IsLoaded() {return value != 0;}
                                    // This method returns true if the entire array
                                    // is loaded.  To see if the array is slab-loaded, 
                                    // attempt to retrieve the cSetRescueArrayFragment
                                    // object.
  RESCUEUSHORT MinValue() {return minValue;}
  RESCUEUSHORT MaxValue() {return maxValue;}
  /**************************************************************************************

  These methods have to do with slab loading.

  **************************************************************************************/
  virtual RescueArrayFragment *Load(RESCUEINT64 iLowBound, RESCUEINT64 iCount,    // Valid function for 2 or 3d grids.
                                    RESCUEINT64 jLowBound, RESCUEINT64 jCount);    // If 3d returns all k layers.
  virtual RescueArrayFragment *Load(RESCUEINT64 iLowBound, RESCUEINT64 iCount,    // Reads the data from the disk file
                                    RESCUEINT64 jLowBound, RESCUEINT64 jCount,    // if it exists.
                                    RESCUEINT64 kLowBound, RESCUEINT64 kCount);    // Use this version on 3d only.

  virtual RescueArrayFragment *Create(RESCUEINT64 iLowBound, RESCUEINT64 iCount,  // Valid function for 2 or 3d grids.
                                      RESCUEINT64 jLowBound, RESCUEINT64 jCount);  // If 3d returns all k layers.
  virtual RescueArrayFragment *Create(RESCUEINT64 iLowBound, RESCUEINT64 iCount,  // Creates a new fragment without
                                      RESCUEINT64 jLowBound, RESCUEINT64 jCount,  // reading the disk.
                                      RESCUEINT64 kLowBound, RESCUEINT64 kCount);  // Use this version on 3d only.
  virtual RescueArrayFragment *Load(RESCUEINT32 iLowBound, RESCUEINT32 iCount,    // Valid function for 2 or 3d grids.
                                    RESCUEINT32 jLowBound, RESCUEINT32 jCount);    // If 3d returns all k layers.
  virtual RescueArrayFragment *Load(RESCUEINT32 iLowBound, RESCUEINT32 iCount,    // Reads the data from the disk file
                                    RESCUEINT32 jLowBound, RESCUEINT32 jCount,    // if it exists.
                                    RESCUEINT32 kLowBound, RESCUEINT32 kCount);    // Use this version on 3d only.

  virtual RescueArrayFragment *Create(RESCUEINT32 iLowBound, RESCUEINT32 iCount,  // Valid function for 2 or 3d grids.
                                      RESCUEINT32 jLowBound, RESCUEINT32 jCount);  // If 3d returns all k layers.
  virtual RescueArrayFragment *Create(RESCUEINT32 iLowBound, RESCUEINT32 iCount,  // Creates a new fragment without
                                      RESCUEINT32 jLowBound, RESCUEINT32 jCount,  // reading the disk.
                                      RESCUEINT32 kLowBound, RESCUEINT32 kCount);  // Use this version on 3d only.
                                                                   // Create functions create arrays
                                                                   // filled with the current null value.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueArrayShort(const RESCUECHAR *propertyNameIn, 
		   const RESCUECHAR *propertyTypeIn,
		   const RESCUECHAR *unitOfMeasureIn,
                    RescueGrid *existingGrid, 
                    RESCUEUSHORT nullValueIn,
                    RescueLookup *lookupIn,
                    RescueModel *parentModelIn,
                    RESCUEBOOL cellCenteredIn = FALSE, RESCUEUSHORT *valueArray = 0)
                    :RescueArray(propertyNameIn, propertyTypeIn, unitOfMeasureIn, 
                                 existingGrid, parentModelIn, cellCenteredIn)
                    ,nullValue(nullValueIn)
                    ,value(valueArray)
                    ,lookupTable(lookupIn) {isA = R_RescueArrayShort; InitMinMax();}
                                    // Create the array with or without the values.
                                    // The pointer must have been created with new.
                                    // The pointer is copied, not the data it
                                    // points to, so it becomes the property of this
                                    // object.
  RescueArrayShort(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  virtual void ArchiveData(FILE *archiveFile, FILE *fragmentFile, RESCUEINT64 fileVersion);
  virtual void CalculateMinMaxData(FILE *fragmentFile, RESCUEINT64 fileVersion);
  virtual void ReadMinMax(RescueContext *context, FILE *archiveFile);
  virtual void WriteMinMax(RescueContext *context, FILE *archiveFile);
  virtual void InitMinMax(void);
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  virtual void DropMemory() {delete [] value; value = 0;}
  virtual void LoadAndSwapArray();
  virtual void SwapAxes(bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes);
  virtual void SwapAxes(bool swapI, RESCUEINT64 iNodes, 
                        bool swapJ, RESCUEINT64 jNodes,
                        bool swapK, RESCUEINT64 kNodes);
  RescueArrayFragment *CreatePrimitive(RESCUEINT64 iLowBound, RESCUEINT64 iCount,  // Valid function for 2 or 3d grids.
                                       RESCUEINT64 jLowBound, RESCUEINT64 jCount); // If 3d returns all k layers.
  RescueArrayFragment *CreatePrimitive(RESCUEINT64 iLowBound, RESCUEINT64 iCount,  // Creates a new fragment without
                                       RESCUEINT64 jLowBound, RESCUEINT64 jCount,  // reading the disk.
                                       RESCUEINT64 kLowBound, RESCUEINT64 kCount); // Use this version on 3d only.

  RESCUEUSHORT nullValue;
  RESCUEUSHORT *value;
  RESCUEINT64 valueLength;
  RescueLookup *lookupTable;
  RESCUEUSHORT minValue;
  RESCUEUSHORT maxValue;

  RESCUEINT64 lookupId;   // used only during relinking.

  friend class RescueProperty;
  friend class RescueWellboreProperty;
};

#endif





