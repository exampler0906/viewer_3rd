/********************************************************************

  RescueSurfaceToGrid.h

  The record of an intersect between a grid cell and a surface.

  Rod Hanks,  January 1997

*********************************************************************/
#ifndef RescueSurfaceToGrid_H
#define RescueSurfaceToGrid_H

#include "myHeaders.h"
#include <stdlib.h>
class RescueGeometry;
class RescueIJSurface;
class cSetRescueDataContainer;

class RescueSurfaceToGrid:public RescueObject
{
public:
  RescueGeometry *Geometry() {return geometry;}
  RescueIJSurface *Surface() {return surface;}
  RESCUEINT64 *IList64() {return iList;} // DO NOT delete the list returned.
  RESCUEINT64 *JList64() {return jList;} // DO NOT delete the list returned.
  RESCUEINT32 *IList() {return IList(false);}
  RESCUEINT32 *JList() {return JList(false);}
  RESCUEINT32 *IList(RESCUEBOOL throwIfTooBig);   // DO delete the list returned.
  RESCUEINT32 *JList(RESCUEBOOL throwIfTooBig);   // DO delete the list returned.
  RESCUEINT64 IListLength64() {return listLength;}
  RESCUEINT64 JListLength64() {return listLength;}
  RESCUEINT64 ListLength64() {return listLength;}
  RESCUEINT32 IListLength() {return (RESCUEINT32) listLength;}
  RESCUEINT32 JListLength() {return (RESCUEINT32) listLength;}
  RESCUEINT32 ListLength() {return (RESCUEINT32) listLength;}

  cSetRescueDataContainer *DataContainers();
                             // Will return 0 if properties have not
                             // been defined.
                             // DO NOT delete the class returned.
  cSetRescueDataContainer *DemandDataContainers();
                             // May return an empty container, but
                             // will never return 0.
                             // DO NOT delete the class returned.
  RESCUEBOOL AnyFileTruncated();
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  ~RescueSurfaceToGrid();
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueSurfaceToGrid(RescueGeometry *geometryIn, 
                      RescueIJSurface *surfaceIn,
                      RESCUEINT64 *iListIn, RESCUEINT64 *jListIn, RESCUEINT64 listLengthIn);
                  // use RescueGeometry::SetSurfaceIntersection.
  void SetList(RESCUEINT64 *iListIn, RESCUEINT64 *jListIn, RESCUEINT64 listLengthIn);
  virtual void Archive(FILE *archiveFile);
  RescueSurfaceToGrid(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  RescueGeometry *geometry;
  RescueIJSurface *surface;
  RESCUEINT64 *iList;
  RESCUEINT64 *jList;
  RESCUEINT64 listLength;

  cSetRescueDataContainer *properties;
  RESCUEINT64 propertyContainerId;

  RESCUEINT64 surfaceID;   // used only during relinking.

  friend class RescueGeometry;
  friend class cSetRescueSurfaceToGrid;
};

#endif




