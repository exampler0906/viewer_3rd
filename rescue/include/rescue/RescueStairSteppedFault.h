/********************************************************************

  RescueStairSteppedFault.h

  Records the positions within a RescueGeometry in which

  Rod Hanks,  June 2002

*********************************************************************/
#ifndef RescueStairSteppedFault_H
#define RescueStairSteppedFault_H

#include "myHeaders.h"
#include <stdlib.h>
class RescueGeometry;
class RescueIJSurface;
class cSetRescueDataContainer;

struct RescueIJKCellPair
{
  RESCUEINT64 i1;                   // The fault is recorded as a set of
  RESCUEINT64 j1;                   // cell faces within the BUG that touch
  RESCUEINT64 k1;                   // each other.  The area of their mutual
  RESCUEINT64 face1;                // face is the surface.  
  RESCUEINT64 lgrid1;               // 0 if primary geometry.  -1 if old model.
  RESCUEINT64 i2;                   // face1 and face2 values are 
  RESCUEINT64 j2;                   //            1 - positive I face,
  RESCUEINT64 k2;                   //            2 - positive J face,
  RESCUEINT64 face2;                //            3 - positive K face,
                            //           -1 - negative I face,
                            //           -2 - negative J face,
                            //           -3 - negative K face.
                            //            0 - old model or face not given.
  RESCUEINT64 lgrid2;               // 0 if primary geometry.  -1 if old model.
};

class RescueStairSteppedFault:public RescueObject
{
public:
  RescueGeometry *Geometry() {return geometry;}
  RescueIJSurface *Surface() {return surface;}
  RESCUEINT64 CellPairCount64() {return count;}
  RESCUEINT32 CellPairCount() {return (RESCUEINT32) count;}
  RescueIJKCellPair *NthCellPair(RESCUEINT64 zeroBasedOrdinal);
                             // DO NOT delete the structure returned.
  cSetRescueDataContainer *DataContainers();
                             // Will return 0 if properties have not
                             // been defined.
                             // DO NOT delete the class returned.
  cSetRescueDataContainer *DemandDataContainers();
                             // May return an empty container, but
                             // will never return 0.
                             // DO NOT delete the class returned.

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  ~RescueStairSteppedFault();
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueStairSteppedFault(RescueGeometry *geometryIn, 
                          RescueIJSurface *surfaceIn,
                          RescueIJKCellPair *arrayIn, RESCUEINT64 arrayLengthIn);
                  // use RescueGeometry::SetStairSteppedSurface.
  void SetList(RescueIJKCellPair *arrayIn, RESCUEINT64 arrayLengthIn);
  virtual void Archive(FILE *archiveFile);
  RescueStairSteppedFault(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  RESCUEBOOL AnyFileTruncated();

  RescueGeometry *geometry;
  RescueIJSurface *surface;
  RescueIJKCellPair *pairs;
  RESCUEINT64 count;
  cSetRescueDataContainer *properties;
  RESCUEINT64 propertyContainerId;

  RESCUEINT64 surfaceID;   // used only during relinking.

  friend class RescueGeometry;
  friend class cSetRescueStairSteppedFault;
};

#endif




