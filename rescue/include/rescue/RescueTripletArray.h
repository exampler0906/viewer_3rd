/********************************************************************

  RescueTripletArray.h

  A dynamically sized array handler for n dimensional grids of
  floating point triplets for RESCUE's data model.

  The dimensionality of the underlying grid is available from
  the associated grid.

  The RescueTripletArray knows how to deal with these situations,
  (1) n-dimensional arrays in which all axes are parametric
  (2) 2 and 3 dimensional arrays in which the i and j axis are
  regular and thus determine the values of the x and y members of
  the triplet.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUETRIPLETARRAY_H
#define RESCUETRIPLETARRAY_H

#include "myHeaders.h"
class RescueGrid;
class RescueModel;
class RescueSplitPoint;

class RescueTripletArray:public RescueObject
{
public:
  RescueTripletArray(RescueContext *context, 
                     RescueGrid *existingGrid, RESCUEFLOAT missingValueIn, RescueModel *parentModelIn)
                                              :RescueObject(context)
                                              ,grid(existingGrid)
                                              ,missingValue(missingValueIn)
                                              ,xValue(0)
                                              ,yValue(0)
                                              ,zValue(0)
                                              ,hasChanged(TRUE)
                                              ,loaded(TRUE)
                                              ,parentModel(parentModelIn)
                                              ,arrayVersion(0)
                                              ,iNodes(0)
                                              ,jNodes(0)
                                              ,vertices(0)
                                  {isA = R_RescueTripletArray;}
  RescueTripletArray(RescueGrid *existingGrid, RESCUEFLOAT missingValueIn, 
                     RESCUEFLOAT *valueArray, RescueModel *parentModelIn);
                                    // Create the array with or without the triplets.
  ~RescueTripletArray();
  RescueGrid *Grid() {return grid;}
  RESCUEFLOAT MissingValue() {return missingValue;}
  void SetValue(RESCUEFLOAT nullValueIn, RESCUEFLOAT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid, plus an extra dimension with count
                                    // of 3, corresponding to x, y, and z.
                                    // The instance makes a copy of the array.
                                    // if the grid has regular axes, then values
                                    // corresponding to the regular axis dimensions
                                    // are ignored.
  void AssignXValue(RESCUEFLOAT *valueArray);
  void AssignYValue(RESCUEFLOAT *valueArray);
  void AssignZValue(RESCUEFLOAT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid. The pointer is copied, meaning the
                                    // array must have been created with new RESCUEFLOAT [].
                                    // The pointer becomes the property of the object.
  void SetXValue(RESCUEFLOAT *valueArray);
  void SetYValue(RESCUEFLOAT *valueArray);
  void SetZValue(RESCUEFLOAT *valueArray);
                                    // The array has the number of dimensions in
                                    // the grid.  
  RESCUEFLOAT *RescueGetXValue();         // Returns a pointer to an array for the
  RESCUEFLOAT *RescueGetYValue();         // coordinate system axis desired.  Do NOT
  RESCUEFLOAT *RescueGetZValue();         // delete the array when you are done with it.
                                    // If no array was defined because the axis is
                                    // regular, RescueTripletArray will build one.
  RESCUEINT64 RescueGetXValueLength64();
  RESCUEINT64 RescueGetYValueLength64();
  RESCUEINT64 RescueGetZValueLength64();
  RESCUEINT32 RescueGetXValueLength() {return (RESCUEINT32) RescueGetXValueLength64();}
  RESCUEINT32 RescueGetYValueLength() {return (RESCUEINT32) RescueGetYValueLength64();}
  RESCUEINT32 RescueGetZValueLength() {return (RESCUEINT32) RescueGetZValueLength64();}
  void XValues(RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 valueCount);         
  void YValues(RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 valueCount);         
  void ZValues(RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 valueCount);         
                                    // Writes the values into an array allocated by
                                    // the caller.  Better for those who want to do
                                    // their own memory allocation.  Especially good
                                    // for Java RJNI users.  valueCount is the number
                                    // of good values in the buffer (excluding offset).
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  RESCUEBOOL IsRegular(RESCUEINT64 which);      // Where i = 0, j = 1, k = 2
  RESCUEBOOL IsCalculated(RESCUEINT64 which);   // Where x = 0, y = 1, z = 2
  void XYZAt(RESCUEINT64 i, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                  // For 1d grids, For an i grid address, return
                                  // x, y, z.
  void XYZAt(RESCUEINT64 i, RESCUEINT64 j, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                  // For 2d grids, For an i,j grid address, return
                                  // x, y, z.
  void XYZAt(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                  // For 3d grids, For an i,j,k grid address, return
                                  // x, y, z.
  RescueModel *ParentModel() {return parentModel;}
/***********************************************************************************

  The next six methods support split node surfaces.

***********************************************************************************/
  void XYZCornerAt(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 faceNumber, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                    // For 2d grids. See documentation for a description
                                    // of face number.  For non-split nodes all face numbers
                                    // will return the same value.
  RESCUEBOOL HasSplitNodes();       // Returns TRUE if there is at least one split node.
  RESCUEBOOL IsSplit(RESCUEINT64 i, RESCUEINT64 j); // Returns TRUE if the given ij node is split.
  void SetXYZCorner(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 faceNumber, RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
                                    // Sets the value of a split node corner.  If the
                                    // corner has been truncated away, pass FLT_MAX.
  void ClearSplitNode(RESCUEINT64 i, RESCUEINT64 j);// Removes split node information for a specific
                                    // node.
  void ClearSplitNodes();           // Removes all split node information.
/***********************************************************************************

  The next five methods have to do with loading and unloading RescueTripletArrays
  separately.

***********************************************************************************/
  RESCUEBOOL IsLoaded() {return loaded;}
  RESCUEBOOL Load();
  void EnsureLoaded();
  RESCUEBOOL FileTruncated();
  RESCUEBOOL Unload();
  RESCUEBOOL HasChanged() {return hasChanged;}
  void MarkChanged() {hasChanged = TRUE;}
/***********************************************************************************/
  RESCUEINT32 Version(RESCUEBOOL reload = FALSE); // These methods return a version number for the file which
                                    // starts at zero and increments each time the file is
                                    // written.  Applications can use this as a quick check to
                                    // see if the file has been updated (by saving the version
                                    // number AFTER a write operation). If reload is TRUE the library
                                    // always goes back to the disk to read the version number,
                                    // in case it has been recently changed.  Therefore, the
                                    // version number returned is the version which would be
                                    // available if the data were loaded now, not the version which
                                    // IS loaded now (if any). If false, the version number returned
                                    // is the version of the last data loaded (if any).
protected:
  RescueTripletArray(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void SetGrid(RescueGrid *newGrid) {grid = newGrid;}
  virtual void ArchiveData(FILE *archiveFile);
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  virtual void DropMemory();
  RESCUEBOOL WriteData();
  RESCUEBOOL ReadData(RESCUECHAR *basePathName, RESCUEBOOL versionOnly = FALSE);
  RESCUEFLOAT *MakeArray(RESCUEFLOAT **arrayToMake, RESCUEINT64 axisNdxOfArray);
  void RescueDeleteFile();
  static void SendBuffer(RESCUEFLOAT *value, RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);
  virtual void SwapArraysEndForEnd();
  virtual void SwapAxes(bool swapI, bool swapJ);

  RescueGrid *grid;
  RESCUEFLOAT missingValue;            
  RESCUEFLOAT *xValue;                 // I am aware that rendering packages ordinarily need
  RESCUEFLOAT *yValue;                 // triplets.  I was reluctantly forced into storing the
  RESCUEFLOAT *zValue;                 // data as separate arrays because of equal axis grids.
  RESCUEINT64 xValueLength;
  RESCUEINT64 yValueLength;
  RESCUEINT64 zValueLength;
  RESCUEBOOL hasChanged;
  RESCUEBOOL loaded;
  RescueModel *parentModel;
  RESCUEINT32 arrayVersion;
  RESCUEINT64 iNodes;
  RESCUEINT64 jNodes;
  RescueSplitPoint **vertices;
  friend class RescueBlockUnit;
  friend class RescueIJSurface;
  friend class RescueSurface;
  friend class RescueWellbore;
  friend class RescueRadialGrid;
};

#endif




