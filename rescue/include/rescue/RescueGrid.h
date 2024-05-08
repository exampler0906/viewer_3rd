/********************************************************************

  RescueGrid.h

  Grid for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEGRID_H
#define RESCUEGRID_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueGridAxis.h"
#include "RescueCoordinateSystem.h"
class RescueCoordinateSystemAxis;
class RescueBlockUnit;
#include "cSetRescueGridAxis.h"
#include "RCHString.h"

/*
  The displayOrientation shows which corner the origin is located on: 
  LUF, LUB, LDF, LDB, RUF, RUB, RDF, and RDB.

    Key:	Left/Right
	        Up/Down
	        Front/Back
*/
class RescueGrid:public RescueHistoryObject
{
public:
  virtual ~RescueGrid();
  RescueGrid(RescueContext *context,
             RescueCoordinateSystem::Orientation displayOrientationIn, 
             RESCUEINT64 i_lowbound, RESCUEINT64 i_count);
  RescueGrid(RescueContext *context,
             RescueCoordinateSystem::Orientation displayOrientationIn, 
             RESCUEFLOAT i_origin, RESCUEFLOAT i_step, RESCUEINT64 i_lowbound, RESCUEINT64 i_count);
  RescueGrid(RescueContext *context,
             RescueCoordinateSystem::Orientation displayOrientationIn, 
             RESCUEINT64 i_lowbound, RESCUEINT64 i_count, 
             RESCUEINT64 j_lowbound, RESCUEINT64 j_count);
  RescueGrid(RescueContext *context,
             RescueCoordinateSystem::Orientation displayOrientationIn, 
             RescueCoordinateSystemAxis *i_axis,
             RESCUEFLOAT i_origin, RESCUEFLOAT i_step, RESCUEINT64 i_lowbound, RESCUEINT64 i_count, 
             RescueCoordinateSystemAxis *j_axis,
             RESCUEFLOAT j_origin, RESCUEFLOAT j_step, RESCUEINT64 j_lowbound, RESCUEINT64 j_count);
  RescueGrid(RescueContext *context,
             RescueCoordinateSystem::Orientation displayOrientationIn, 
             RESCUEINT64 i_lowbound, RESCUEINT64 i_count, 
             RESCUEINT64 j_lowbound, RESCUEINT64 j_count, 
             RESCUEINT64 k_lowbound, RESCUEINT64 k_count);
  RescueGrid(RescueContext *context,
             RescueCoordinateSystem::Orientation displayOrientationIn, 
             RescueCoordinateSystemAxis *i_axis,
             RESCUEFLOAT i_origin, RESCUEFLOAT i_step, RESCUEINT64 i_lowbound, RESCUEINT64 i_count, 
             RescueCoordinateSystemAxis *j_axis,
             RESCUEFLOAT j_origin, RESCUEFLOAT j_step, RESCUEINT64 j_lowbound, RESCUEINT64 j_count, 
             RESCUEINT64 k_lowbound, RESCUEINT64 k_count);
  RescueGrid(RescueContext *context,
             RescueCoordinateSystem::Orientation displayOrientationIn, 
             RescueCoordinateSystemAxis *i_axis,
             RESCUEFLOAT i_origin, RESCUEFLOAT i_step, RESCUEINT64 i_lowbound, RESCUEINT64 i_count, 
             RescueCoordinateSystemAxis *j_axis,
             RESCUEFLOAT j_origin, RESCUEFLOAT j_step, RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
             RESCUEFLOAT k_origin, RESCUEFLOAT k_step, RESCUEINT64 k_lowbound, RESCUEINT64 k_count);
                              // Create 1d, 2d, 3d grids.
  RESCUEINT32 Dimensions() {return (RESCUEINT32) axes->Count();}
  RESCUEINT64 NodeCount64(RESCUEBOOL cellCentered = FALSE);   // Return number of nodes in the grid.
  RESCUEINT32 NodeCount(RESCUEBOOL cellCentered = FALSE) {return (RESCUEINT32) NodeCount64(cellCentered);}
	RESCUEINT64 Vertices64();							// Number of ij vertexes in the grid.
  RESCUEINT32 Vertices() {return (RESCUEINT32) Vertices64();}
	RESCUEINT32 Vertices(RESCUEBOOL throwIfTooBig);							// Number of ij vertexes in the grid.
  RescueGridAxis *Axis(RESCUEINT64 zeroBasedOrdinal) {return axes->NthObject(zeroBasedOrdinal);}
  RescueCoordinateSystem::Orientation DisplayOrientation() {return displayOrientation;}

  RescueGrid(RescueContext *context);  // Create an empty grid.  Then add axes to it.
  void AddAxis(RescueGridAxis *axis);  // This may be used for abstract RescueDataContainer
                                       // grids, but should not be used for model grids.

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  RESCUEBOOL IsRegular(RESCUEINT64 which);      // Where i = 0, j = 1, k = 2.
private:
  RescueGrid(RescueContext *context,
             FILE *archiveFile);
  virtual void Archive(RescueContext *context,
             FILE *archiveFile);
  virtual void Relink(RescueObject *parentModel);
  void SetOrientation(RescueCoordinateSystem::Orientation orientIn, bool swapI, bool swapJ, bool swapK);
  void SetOrientation(RescueCoordinateSystem::Orientation orientIn) {displayOrientation = orientIn;}

  RescueCoordinateSystem::Orientation displayOrientation;
  cSetRescueGridAxis *axes;

  friend class RescueBlockUnit;
  friend class RescueSurface;
  friend class RescueWellbore;
  friend class RescueWellboreSampling;
  friend class RescueProperty;
  friend class RescueGeometry;
  friend class RescueWellboreProperty;
  friend class cSetRescueWellboreCell;
  friend class RescueIJSurface;
  friend class RescueGridAxis;
  friend class RescueRadialGrid;
  friend class RescueDataContainer;
};

#endif




