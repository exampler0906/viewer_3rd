/********************************************************************

  RescueSurfaceCell.h

  The record of an intersect between a grid cell and a surface.

  Rod Hanks,  January 1997

*********************************************************************/
#ifndef RESCUESURFACECELL_H
#define RESCUESURFACECELL_H

#include "myHeaders.h"
#include <stdlib.h>
class RescueGeometry;
class RescueIJSurface;
class RescueGridAxis;

class RescueSurfaceCell:public RescueObject
{
public:
  typedef enum {FRONT,BACK} SurfaceSide;

  RescueGeometry *Geometry() {return geometry;}
  RescueIJSurface *Surface() {return surface;}
  SurfaceSide Side() {return side;}
  RESCUEINT64 CellFaceNumber() {return cellFaceNumber;}
  RESCUEFLOAT *UVArray() {return uvs;} // DO NOT free the array that is returned.
  RESCUEINT32 UVArrayLength() {return 8;}
  void CellIndex(RescueGeometry *geometry, RESCUEINT64 &i, RESCUEINT64 &j, RESCUEINT64 &k);
  void CellIndex(RescueGeometry *geometry, RESCUEINT32 &i, RESCUEINT32 &j, RESCUEINT32 &k);
  void CellIndex(RescueGeometry *geometry, RESCUEINT64 *returnArray, RESCUEINT64 returnArraySize);
  void CellIndex(RescueGeometry *geometry, RESCUEINT32 *returnArray, RESCUEINT32 returnArraySize);
          // Pass an array with at least 3 members.  array[0] = i,
          // array[1] = j, array[2] = k.

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  ~RescueSurfaceCell();
private:
  RescueSurfaceCell(RescueGeometry *geometryIn, 
                    RescueIJSurface *surfaceIn,
                    RESCUEINT64 cellNumber,
                    RESCUEINT64 cellFaceNumberIn, SurfaceSide sideIn,
                    RESCUEFLOAT *uvsIn = 0);
                  // use RescueGeometry::SetSurfaceIntersection.
  virtual void Archive(FILE *archiveFile);
  RescueSurfaceCell(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void Swap(bool swapI, RescueGridAxis *iAxis, bool swapJ, RescueGridAxis *jAxis);

  RescueGeometry *geometry;
  RescueIJSurface *surface;
  RESCUEINT64 cellNumber;
  RESCUEINT64 cellFaceNumber;
  SurfaceSide side;
  RESCUEFLOAT *uvs;    // array is 2 x 4 in which the first index is u=0, v=1,
                  // and the second index is the face corner number (see
                  // document).

  RESCUEINT64 surfaceID;   // used only during relinking.

  friend class RescueGeometry;
  friend class cSetRescueSurfaceCell;
  friend class RescueIJSurface;
};

#endif




