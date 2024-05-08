/********************************************************************

  RescueQuadrupletArray.h

  Adds to RescueTripletArray the ability to hold an MD value for
  each xyz value.  The MD value is never evenly sampled.

  Rod Hanks,  May 2002

*********************************************************************/
#ifndef RescueQuadrupletArray_H
#define RescueQuadrupletArray_H

#include "myHeaders.h"
class RescueGrid;
class RescueModel;

class RescueQuadrupletArray: public RescueTripletArray
{
public:
  RescueQuadrupletArray(RescueContext *context, 
                        RescueGrid *existingGrid, RESCUEFLOAT missingValueIn, RescueModel *parentModelIn)
                                              :RescueTripletArray(context, existingGrid, missingValueIn, parentModelIn)
                                              ,mdValue(0),mdValueLength(0)
                                  {isA = R_RescueQuadrupletArray;}
  RescueQuadrupletArray(RescueGrid *existingGrid, RESCUEFLOAT missingValueIn, 
                        RESCUEFLOAT *valueArray, RescueModel *parentModelIn);
                                    // Create the array with or without the triplets.
  ~RescueQuadrupletArray();
  void SetValue(RESCUEFLOAT nullValueIn, RESCUEFLOAT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid, plus an extra dimension with count
                                    // of 4, corresponding to x, y, z, and md.
                                    // The instance makes a copy of the array.
                                    // if the grid has regular axes, then values
                                    // corresponding to the regular axis dimensions
                                    // are ignored.
  void AssignMDValue(RESCUEFLOAT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid. The pointer is copied, meaning the
                                    // array must have been created with new RESCUEFLOAT [].
                                    // The pointer becomes the property of the object.
  void SetMDValue(RESCUEFLOAT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid.  
  RESCUEINT64 MDValueLength64() {return mdValueLength;}
  RESCUEINT32 MDValueLength() {return (RESCUEINT32) mdValueLength;}
  RESCUEFLOAT *MDValue() {return mdValue;}
                                    // Returns a pointer to an array for the
                                    // coordinate system axis desired.  Do NOT
                                    // delete the array when you are done with it.
                                    // If no array was defined because the axis is
                                    // regular, RescueTripletArray will build one.
  void MDValues(RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 valueCount);
                                    // Writes the values into an array allocated by
                                    // the caller.  Better for those who want to do
                                    // their own memory allocation.  Especially good
                                    // for Java RJNI users.  valueCount is the number
                                    // of good values in the buffer (excluding offset).  
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  void XYZMDAt(RESCUEINT64 i, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z, RESCUEFLOAT &md);
                                  // For 1d grids, For an i grid address, return
                                  // x, y, z, md.
private:
  RescueQuadrupletArray(RescueContext *context, FILE *archiveFile);
  virtual void ArchiveData(FILE *archiveFile);
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  virtual void DropMemory();
  virtual void SwapArraysEndForEnd();
  void WriteWITSML(FILE *file, RescueWellbore *wellbore, RCHString *uom, RCHString *csName);

  RESCUEFLOAT *mdValue;                
  RESCUEINT64 mdValueLength;
  friend class RescueWellbore;
  friend class RescueRadialGrid;
  friend class RescueModel;
};

#endif




