/********************************************************************

  RescueReferenceSurface.h

  Holds a horizontal surface which may be used to reference z values
  on a RescueGeometry (block unit grid).

  This is mostly necessary because some children of RescueSurface,
  notably RescueSection, would NOT be good candidates for reference
  surfaces.

  Rod Hanks,  June 1997

*********************************************************************/
#ifndef RescueReferenceSurface_H
#define RescueReferenceSurface_H

#include "myHeaders.h"
#include "RescueSurface.h"
#include "RescueEdgeSet.h"
class RescueHorizon;
class RescueBlockUnit;

class RescueReferenceSurface:public RescueSurface
{
public:
  RescueReferenceSurface(RescueModel *model,
                         RescueCoordinateSystem::Orientation orientation,
                         RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                         RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                         RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                         RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                         RESCUEFLOAT missingValue, 
                         RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON);
  RescueReferenceSurface(RescueModel *model,
                         RescueCoordinateSystem::Orientation orientation,
                         RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                         RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                         RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                         RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                         RESCUEFLOAT missingValue, 
                         RESCUEFLOAT *values, 
                         RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON);
         // Creates a new surface with regular x/y geometry.
          // If passed, the values are applied to the Z axis.
  RescueReferenceSurface(RescueModel *model,
                         RescueCoordinateSystem::Orientation orientation,
                          RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                          RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                          RESCUEFLOAT missingValue, RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON)
                :RescueSurface(model, orientation, i_lowbound, i_count, j_lowbound, j_count, missingValue,
                                typeIn)
                                    {CommonInitialization(model);}
  RescueReferenceSurface(RescueModel *model,
                         RescueCoordinateSystem::Orientation orientation,
                          RESCUEFLOAT missingValue, RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON)
                :RescueSurface(model, orientation, 0, 0, 0, 0, missingValue,
                                typeIn)
                                    {CommonInitialization(model);}
  RescueReferenceSurface(RescueModel *model,
                         RescueCoordinateSystem::Orientation orientation,
                         RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                         RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                         RESCUEFLOAT missingValue, 
                         RESCUEFLOAT *tripletArray, RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON)
               :RescueSurface(model, orientation, i_lowbound, i_count, j_lowbound, 
                              j_count, missingValue, tripletArray,
                                typeIn)
                                    {CommonInitialization(model);}
          // Creates a new parametric surface.
  
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  RescueReferenceSurface(RescueModel *modelIn,
                         RescueCoordinateSystem::Orientation orientation,
                         RescueCoordinateSystemAxis *i_axis,
                         RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                         RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                         RescueCoordinateSystemAxis *j_axis,
                         RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                         RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                         RESCUEFLOAT missingValue, 
                         RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON)
                :RescueSurface(modelIn, orientation, i_axis, i_origin, i_step,
                               i_lowbound, i_count, j_axis, j_origin, j_step,
                               j_lowbound, j_count, missingValue, 
                               typeIn) 
                                    {}
  RescueReferenceSurface(RescueModel *modelIn,
                         RescueCoordinateSystem::Orientation orientation,
                         RescueCoordinateSystemAxis *i_axis,
                         RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                         RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                         RescueCoordinateSystemAxis *j_axis,
                         RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                         RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                         RESCUEFLOAT missingValue, 
                         RESCUEFLOAT *values, 
                         RescueSurface::SurfaceType typeIn = RescueSurface::HORIZON)
                 :RescueSurface(modelIn, orientation, i_axis, i_origin, i_step, i_lowbound, 
                                i_count, j_axis, j_origin, j_step, j_lowbound, j_count,
                                missingValue, values, typeIn) 
                                     {}
  RescueReferenceSurface(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
private:
  void CommonInitialization(RescueModel *model);
  RescueReferenceSurface(RescueContext *context, FILE *archiveFile, RESCUEINT64 flag):RescueSurface(context, archiveFile) {}        
/*  
  Used by RescueBlockUnitHorizonSurface when unarchiving.  We don't want to go thru the
  RescueReferenceSurface initialization, since it is skipped on writing.
*/
  friend class cSetRescueReferenceSurface;
  friend class RescueBlockUnitHorizonSurface;
};

#endif




