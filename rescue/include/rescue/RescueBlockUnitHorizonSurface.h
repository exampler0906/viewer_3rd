/********************************************************************

  RescueBlockUnitHorizonSurface.h

  Holds the horizon which bounds a particular block unit
  for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEBLOCKUNITHORIZONSURFACE_H
#define RESCUEBLOCKUNITHORIZONSURFACE_H

#include "myHeaders.h"
#include "RescueReferenceSurface.h"
#include "RescueEdgeSet.h"
class RescueHorizon;
class RescueBlockUnit;

class RescueBlockUnitHorizonSurface:public RescueReferenceSurface
{
public:
  RescueBlockUnitHorizonSurface(RescueCoordinateSystem::Orientation orientation,
                                RescueHorizon *parentHorizon,
                                RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                                RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                                RESCUEFLOAT missingValue,
                                RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON);
  RescueBlockUnitHorizonSurface(RescueCoordinateSystem::Orientation orientation,
                                RescueHorizon *parentHorizon,
                                RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                                RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                                RESCUEFLOAT missingValue,
                                RESCUEFLOAT *valueTriplets,
                                RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON);
  RescueBlockUnitHorizonSurface(RescueCoordinateSystem::Orientation orientation,
                                RescueHorizon *parentHorizon,
                                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                                RESCUEFLOAT missingValue,
                                RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON);
  RescueBlockUnitHorizonSurface(RescueCoordinateSystem::Orientation orientation,
                                RescueHorizon *parentHorizon,
                                RESCUEFLOAT missingValue,
                                RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON);
                  // Use of the constructor above makes the model incompatible with
                  // the Rescue v9 software.
  RescueBlockUnitHorizonSurface(RescueCoordinateSystem::Orientation orientation,
                                RescueHorizon *parentHorizon,
                                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                                RESCUEFLOAT missingValue,
                                RESCUEFLOAT *valueTriplets,
                                RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON);
  RescueHorizon *ParentHorizon() {return parentHorizon;}
  RescueBlockUnit *BlockUnitAboveMe() {return unitAboveMe;}
  RescueBlockUnit *BlockUnitBelowMe() {return unitBelowMe;}

  void SetBlockUnitAboveMe(RescueBlockUnit *existingUnit)
                                      {unitAboveMe = existingUnit;}
  void SetBlockUnitBelowMe(RescueBlockUnit *existingUnit)
                                      {unitBelowMe = existingUnit;}
  
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueBlockUnitHorizonSurface(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentObject);


  RescueHorizon *parentHorizon;
  RescueBlockUnit *unitAboveMe;
  RescueBlockUnit *unitBelowMe;


  RESCUEINT64 unitAboveID;  // Used only during relinking.
  RESCUEINT64 unitBelowID;
  RescueEdgeSet *edges;  // Used only when reading a version 4 or 5 file.

  friend class cSetRescueBlockUnitHorizonSurface;
  friend class RescueHorizon;
  friend class RescueBlockUnit;
};

#endif




