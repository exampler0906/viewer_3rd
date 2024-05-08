/********************************************************************

  RescueIJSurface.h

  An IJ surface in RESCUE terms is a parametric 2d grid (i,j), with the
  geometry described by an (x,y,z) triplet for each node of the grid.
  The coordinate system of the triplet is the global coordinate system 
  of the model.

  All IJ representations of a surface share the same trim loop. 
  Ideally, this would be parameterized against both surfaces.

  Rod Hanks,  May 1996 / July 1999 / December 1999

*********************************************************************/
#ifndef RESCUEIJSURFACE_H
#define RESCUEIJSURFACE_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueGrid.h"
#include "RescueTripletArray.h"
#include "cBagRescueSurfaceCell.h"
#include "cBagRescueSurfaceToGrid.h"
#include "cBagRescueStairSteppedFault.h"
#include "cBagRescueWellboreSurface.h"
#include "RescueCoordinateSystem.h"
#include "cSetRescueProperty.h"
class RescueCoordinateSystemAxis;
class RescueSurfaceCell;
class RescueGeometry;
class RescueSurface;
class RescueBitArray;
class RescueOrientationLedger;

class RescueIJSurface:public RescueHistoryObject
{
public:
  typedef enum {R_FACE_ACTIVE,                  // Face is completely inside the surface
                R_FACE_INACTIVE,                // Face is completely outside the surface
                R_FACE_TRUNCATED}               // Cell is inactivated by a Y Fault.
                    RescueFaceStatus;
  RescueIJSurface(RescueSurface *surfaceIn,
                  RescueCoordinateSystem::Orientation orientation,
                  RescueCoordinateSystemAxis *i_axis,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RescueCoordinateSystemAxis *j_axis,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEFLOAT missingValue);
  RescueIJSurface(RescueSurface *surfaceIn,
                  RescueCoordinateSystem::Orientation orientation,
                  RescueCoordinateSystemAxis *i_axis,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RescueCoordinateSystemAxis *j_axis,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEFLOAT missingValue, 
                  RESCUEFLOAT *values);
          // Creates a new surface with regular x/y geometry.
          // If passed, the values are applied to the Z axis.
  RescueIJSurface(RescueSurface *surfaceIn,
                  RescueCoordinateSystem::Orientation orientation,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEFLOAT missingValue);
  RescueIJSurface(RescueSurface *surfaceIn,
                  RescueCoordinateSystem::Orientation orientation,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEFLOAT missingValue, 
                  RESCUEFLOAT *tripletArray);
          // Creates a new parametric surface.
  RescueGrid *Grid() {return surfaceGrid;}
  RescueTripletArray *Geometry() {return surfaceGeometry;}
  RESCUEINT64 SurfaceCellCount64() {return surfaceCell->Count64();}
  RESCUEINT32 SurfaceCellCount() {return surfaceCell->Count();}
  RescueSurfaceCell *NthSurfaceCell(RESCUEINT64 zeroBasedOrdinal)
                        {return surfaceCell->NthObject(zeroBasedOrdinal);}
                  // RescueBlockUnit does not "own" RescueSurfaceCells,
                  // so it does not create or delete them, merely
                  // catalogs relationships to them.  These intersections are
                  // managed from RescueGeometry.
  RESCUEINT64 SurfaceGridCount64() {return surfaceToGrid->Count64();}
  RESCUEINT32 SurfaceGridCount() {return surfaceToGrid->Count();}
  RescueSurfaceToGrid *NthSurfaceGrid(RESCUEINT64 zeroBasedOrdinal)
                    {return surfaceToGrid->NthObject(zeroBasedOrdinal);}
                  // DO NOT delete the object returned.  Interrogate it for the
                  // intersection points.
  RESCUEINT64 StairSteppedFaultCount64() {return stairSteps->Count64();}
  RESCUEINT32 StairSteppedFaultCount() {return stairSteps->Count();}
  RescueStairSteppedFault *NthStairSteppedFault(RESCUEINT64 zeroBasedOrdinal)
                  {return stairSteps->NthObject(zeroBasedOrdinal);}
                  // DO NOT delete the object returned. 

  void SetFaceStatus(RESCUEINT64 i, RESCUEINT64 j, RescueFaceStatus newStatus = R_FACE_ACTIVE);
  RescueFaceStatus FaceStatus(RESCUEINT64 i, RESCUEINT64 j);

  RESCUEBOOL AnyFileTruncated();            // Checks all subfiles in the instantiated model.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  virtual ~RescueIJSurface();
  RescueModel *ParentModel() {return surfaceGeometry->ParentModel();}
  RescueSurface *ParentSurface() {return parentSurface;}
  RESCUEFLOAT ZValueAt(RESCUEINT64 i, RESCUEINT64 j);
protected:
  RescueIJSurface(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentModel);
private:
  RESCUEINT64 *AddVertexToArray(RESCUEINT64 *arrayIn, RESCUEINT64 i, RESCUEINT64 j, 
                        RESCUEINT64 &allocated, RESCUEINT64 &arrayLength);
  void AddWellboreSurface(RescueWellboreSurface *existingIntersect)
                        {(*surfaceWellbore) += existingIntersect;}
  void DropWellboreSurface(RescueWellboreSurface *existingIntersect)
                        {(*surfaceWellbore) -= existingIntersect;}
                                     // Constructor for RescueWellboreSurface will connect
                                     // both ends.
  void AddSurfaceCell(RescueSurfaceCell *existingCell)
                        {(*surfaceCell) += existingCell;}
  void DropSurfaceCell(RescueSurfaceCell *existingCell)
                        {(*surfaceCell) -= existingCell;}
                                     // Surface cell intersections are managed from
                                     // the geometry side. See RescueGeometry.
  void AddSurfaceToGrid(RescueSurfaceToGrid *existingToGrid)
                        {(*surfaceToGrid) += existingToGrid;}
  void DropSurfaceToGrid(RescueSurfaceToGrid *existingToGrid)
                        {(*surfaceToGrid) -= existingToGrid;}
                                     // Surface to grid intersections are managed from
                                     // the geometry side. See RescueGeometry.
  void AddStairSteps(RescueStairSteppedFault *existingFault)
                        {(*stairSteps) += existingFault;}
  void DropSurfaceToGrid(RescueStairSteppedFault *existingFault)
                        {(*stairSteps) -= existingFault;}
                                     // Stair stepped fault intersections are managed from
                                     // the geometry side. See RescueGeometry.
  void DropBags() {surfaceCell->EmptySelf();}
  void Dispose() {surfaceGeometry->RescueDeleteFile();}
  void SwapAxes(RescueOrientationLedger *ledger, bool swapI, bool swapJ);
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RescueSurface *parentSurface;
  RescueGrid *surfaceGrid;            // 2d grid.
  RescueTripletArray *surfaceGeometry;
  cBagRescueSurfaceCell *surfaceCell;
  cBagRescueSurfaceToGrid *surfaceToGrid;
  cBagRescueStairSteppedFault *stairSteps;
  cBagRescueWellboreSurface *surfaceWellbore;
  RescueBitArray *faceStatus;

  friend class RescueBlockUnitHorizonSurface;
  friend class RescueSection;
  friend class RescueSurfaceCell;
  friend class RescueWellboreSurface;
  friend class RescueModel;
  friend class RescuePolyLine;
  friend class RescueGrid;
  friend class cSetRescueWellboreSurface;
  friend class RescueMacroVolume;
  friend class cSetRescueSurfaceCell;
  friend class cSetRescueBlockUnitHorizonSurface;
  friend class cSetRescueSection;
  friend class cSetRescueReferenceSurface;
  friend class cSetRescueIJSurface;
  friend class RescueSurfaceToGrid;
  friend class RescueProperty;
  friend class RescuePropertyGroup;
  friend class RescueSurface;
  friend class RescueStairSteppedFault;
};

#endif





