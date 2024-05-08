/********************************************************************

  RescueGridAxis.h

  Grid axis for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEGRIDAXIS_H
#define RESCUEGRIDAXIS_H

#include "myHeaders.h"
class RescueGrid;
class RescueCoordinateSystem;
class RescueCoordinateSystemAxis;

class RescueGridAxis:public RescueObject
{
public:
  typedef enum {I_AXIS, J_AXIS, K_AXIS, UNKNOWN} GridNdx;

  RescueGrid *ParentGrid() {return parentGrid;}
  RESCUEINT64 LowBound64() {return lowBound;}
  RESCUEINT32 LowBound() {return (RESCUEINT32) lowBound;}
  RESCUEINT64 Count64() {return count;}
  RESCUEINT32 Count() {return (RESCUEINT32) count;}
  RESCUEINT32 LowBound(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);
  RESCUEBOOL IsRegular() {return (step == 0.0) ? FALSE : TRUE;}
  RescueCoordinateSystemAxis *RelatedCoordinateSystemAxis() 
                                             {return relatedAxis;}
  RESCUEFLOAT ValueAt(RESCUEINT64 ndx) {return origin + ((RESCUEFLOAT) (ndx - lowBound) * step);}
  RESCUEFLOAT Origin() {return origin;}
  RESCUEFLOAT Step() {return step;}
  void SetOrigin(RESCUEFLOAT originIn) {origin = originIn;}
  void SetStep(RESCUEFLOAT stepIn) {step = stepIn;}
  GridNdx AxisIndex(); 

  RescueGridAxis(RescueContext *context, RESCUEINT64 lowBoundIn, RESCUEINT64 countIn, RESCUEFLOAT originIn, RESCUEFLOAT stepIn)
    :RescueObject(context)                      // This public constructor is for use with abstract RescueDataContainer grids.
    ,parentGrid(0)                              // Model grids are constructed using RescueGrid methods that build axes
    ,relatedAxis(0)                             // using private constructors.
    ,lowBound(lowBoundIn)
    ,count(countIn)
    ,origin(originIn)
    ,step(stepIn) {isA = R_RescueGridAxis;}
    
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueGridAxis(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueGrid *parent, RescueCoordinateSystem *cs);
  virtual void Relink(RescueObject *object) {} 
  void Swap();

  void SetCount(RESCUEINT64 newCount) {count = newCount;}

  RescueGridAxis(RescueContext *context, RescueGrid *parentIn, RESCUEINT64 lowBoundIn, RESCUEINT64 countIn)
                  :RescueObject(context)
                  ,parentGrid(parentIn)
                  ,relatedAxis(0)
                  ,lowBound(lowBoundIn)
                  ,count(countIn)
                  ,origin((RESCUEFLOAT) 0.0)
                  ,step((RESCUEFLOAT) 0.0) {isA = R_RescueGridAxis;}
  RescueGridAxis(RescueContext *context, RescueGrid *parentIn, 
                 RescueCoordinateSystemAxis *axis, 
                 RESCUEFLOAT originIn, RESCUEFLOAT stepIn,
                 RESCUEINT64 lowBoundIn, RESCUEINT64 countIn)
                :RescueObject(context)
                ,parentGrid(parentIn)
                ,relatedAxis(axis)
                ,lowBound(lowBoundIn)
                ,count(countIn)
                ,origin(originIn)
                ,step(stepIn) {isA = R_RescueGridAxis;}
  RescueGridAxis(RescueContext *context, RescueGrid *parentIn, 
                 RESCUEFLOAT originIn, RESCUEFLOAT stepIn,
                 RESCUEINT64 lowBoundIn, RESCUEINT64 countIn)
                :RescueObject(context)
                ,parentGrid(parentIn)
                ,relatedAxis(0)
                ,lowBound(lowBoundIn)
                ,count(countIn)
                ,origin(originIn)
                ,step(stepIn) {isA = R_RescueGridAxis;}
  
  RescueGrid *parentGrid;
  RescueCoordinateSystemAxis *relatedAxis;
  RESCUEINT64 lowBound;
  RESCUEINT64 count;
  RESCUEFLOAT origin;
  RESCUEFLOAT step;

  RESCUEINT64 relatedAxisID;    // Used only during relink.

  friend class RescueGrid;
  friend class cSetRescueGridAxis;
  friend class RescueTripletArray;
  friend class RescueUnstructuredGrid;
  friend class RescueRadialGrid;
  friend class RescueWellboreSampling;
  friend class RescueWellbore;
  friend class RescueIJSurface;
};

#endif




