/********************************************************************

  RescueArray.h

  A dynamically sized array handler for N dimensional grids of
  data for RESCUE's data model. The related grid gives
  the dimensionality.

  This abstract superclass can be instantiated as one of it's subclasses.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEARRAY_H
#define RESCUEARRAY_H

#include "myHeaders.h"
#include "RCHString.h"
#include "RescueGrid.h"
class cSetRescueArrayFragment;
class RescueArrayFragment;

class RescueArray:public RescueObject
{
public:
  RescueArray(const RESCUECHAR *propertyNameIn, 
              const RESCUECHAR *propertyTypeIn,
              const RESCUECHAR *unitOfMeasureIn,
              RescueGrid *existingGrid,
              RescueModel *parentModelIn,
              RESCUEBOOL cellCenteredIn = FALSE);
  virtual ~RescueArray();
  RCHString *PropertyName() {return propertyName;}
  void SetPropertyName(RESCUECHAR *newPropertyName) {(*propertyName) = newPropertyName;}
  RCHString *PropertyType() {return propertyType;}
                                    // Do NOT drop the objects returned.
  void SetPropertyType(RESCUECHAR *newPropertyType) {(*propertyType) = newPropertyType;}
  RCHString *UnitOfMeasure() {return unitOfMeasure;}
                                    // Do NOT drop the object returned.
  void SetUnitOfMeasure(RESCUECHAR *newUnitOfMeasure) {(*unitOfMeasure) = newUnitOfMeasure;}
  RescueGrid *Grid() {return grid;}
  RESCUEBOOL CellCentered() {return cellCentered;}

  RescueModel *ParentModel() {return parentModel;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  virtual RESCUEBOOL IsLoaded()=0;  // Returns FALSE if fragments are loaded.
  RESCUEBOOL FileTruncated();
  RESCUEBOOL Load();                // If there are fragments in memory these will be merged,
                                    // not overridden.
  RESCUEBOOL Unload();              // If fragments are loaded these will be merged into the
                                    // the archived file if we write the file.
  RESCUEBOOL HasChanged() {return hasChanged;}
  RESCUEBOOL MinMaxDirty() {return dirtyMinMax;}
  void CalculateMinMax();
  void MarkChanged() {hasChanged = TRUE; dirtyMinMax = TRUE;}
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
  /**************************************************************************************

  These methods have to do with slab loading.

  **************************************************************************************/
  virtual RescueArrayFragment *Load(RESCUEINT64 iLowBound, RESCUEINT64 iCount,      // Valid function for 2 or 3d grids.
                                    RESCUEINT64 jLowBound, RESCUEINT64 jCount)=0;   // If 3d returns all k layers.
  virtual RescueArrayFragment *Load(RESCUEINT64 iLowBound, RESCUEINT64 iCount,      // Reads the data from the disk file
                                    RESCUEINT64 jLowBound, RESCUEINT64 jCount,      // if it exists.
                                    RESCUEINT64 kLowBound, RESCUEINT64 kCount)=0;   // Use this version on 3d only.

  virtual RescueArrayFragment *Create(RESCUEINT64 iLowBound, RESCUEINT64 iCount,    // Valid function for 2 or 3d grids.
                                      RESCUEINT64 jLowBound, RESCUEINT64 jCount)=0; // If 3d returns all k layers.
  virtual RescueArrayFragment *Create(RESCUEINT64 iLowBound, RESCUEINT64 iCount,    // Creates a new fragment without
                                      RESCUEINT64 jLowBound, RESCUEINT64 jCount,    // reading the disk.
                                      RESCUEINT64 kLowBound, RESCUEINT64 kCount)=0; // Use this version on 3d only.
  virtual RescueArrayFragment *Load(RESCUEINT32 iLowBound, RESCUEINT32 iCount,      // Valid function for 2 or 3d grids.
                                    RESCUEINT32 jLowBound, RESCUEINT32 jCount)=0;   // If 3d returns all k layers.
  virtual RescueArrayFragment *Load(RESCUEINT32 iLowBound, RESCUEINT32 iCount,      // Reads the data from the disk file
                                    RESCUEINT32 jLowBound, RESCUEINT32 jCount,      // if it exists.
                                    RESCUEINT32 kLowBound, RESCUEINT32 kCount)=0;   // Use this version on 3d only.

  virtual RescueArrayFragment *Create(RESCUEINT32 iLowBound, RESCUEINT32 iCount,    // Valid function for 2 or 3d grids.
                                      RESCUEINT32 jLowBound, RESCUEINT32 jCount)=0; // If 3d returns all k layers.
  virtual RescueArrayFragment *Create(RESCUEINT32 iLowBound, RESCUEINT32 iCount,    // Creates a new fragment without
                                      RESCUEINT32 jLowBound, RESCUEINT32 jCount,    // reading the disk.
                                      RESCUEINT32 kLowBound, RESCUEINT32 kCount)=0; // Use this version on 3d only.

  
  RESCUEBOOL HasFragments();                        // Will return TRUE if there is at least 1 fragment.
  cSetRescueArrayFragment *Fragments() {return fragments;}             
                                                    // Will return null if there have never
                                                    // been fragments.  Even if it returns
                                                    // non-null, the Count() method of the
                                                    // object may return 0.  Do NOT delete
                                                    // the object returned.
  /*************************************************************************************/

protected:
  RescueArray(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  virtual void ArchiveData(FILE *archiveFile, FILE *fragmentFile, RESCUEINT64 fileVersion)=0;
  virtual void CalculateMinMaxData(FILE *fragmentFile, RESCUEINT64 fileVersion)=0;
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion)=0;
  virtual void WriteMinMax(RescueContext *context, FILE *archiveFile)=0;
  virtual void InitMinMax(void)=0;
  virtual void ReadMinMax(RescueContext *context, FILE *archiveFile)=0;
  virtual void DropMemory()=0;
  void DropFragments();
  void DemandFragments();
  RESCUEBOOL ReadData(RESCUECHAR *basePathName, RESCUEBOOL versionOnly = FALSE, RescueArrayFragment *toLoad = 0);
  void LoadFragment(RescueArrayFragment *toLoad);
private:
  void SetGrid(RescueGrid *newGrid) {grid = newGrid;}
  RESCUEBOOL WriteData();
  void RescueDeleteFile();
  virtual void LoadAndSwapArray()=0;
  virtual void SwapAxes(bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes)= 0;
  virtual void SwapAxes(bool swapI, RESCUEINT64 iNodes, 
                        bool swapJ, RESCUEINT64 jNodes,
                        bool swapK, RESCUEINT64 kNodes)= 0;

protected:
  RCHString *propertyName;
  RCHString *propertyType;
  RCHString *unitOfMeasure;
  RescueGrid *grid;
  RESCUEBOOL cellCentered;
  RESCUEBOOL hasChanged;
  RESCUEBOOL dirtyMinMax;
  RescueModel *parentModel;
  RESCUEINT32 arrayVersion;
  cSetRescueArrayFragment *fragments;

  friend class RescueProperty;
  friend class RescueWellboreProperty;
  friend class RescueTriangulatedSurface;
};

#endif





