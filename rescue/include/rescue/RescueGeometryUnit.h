/********************************************************************

  RescueGeometryUnit.h

  This object, owned by RescueGeometry, records an intersect between
  a RescueGeometry which contains a global grid and a RescueUnit which
  is part of that grid.

  Rod Hanks,  June 2001

*********************************************************************/
#ifndef RescueGeometryUnit_H
#define RescueGeometryUnit_H

#include "myHeaders.h"
#include "RescueObject.h"
class RescueGeometry;
class RescueUnit;

class RescueGeometryUnit:public RescueObject
{
public:
  RescueGeometryUnit(RescueGeometry *parentGeometry, RescueUnit *relatedUnit, 
                     RESCUEINT64 topLayerNdx, RESCUEINT64 bottomLayerNdx);
  // Create a new unit.
  // To dispose a unit, use parentGeometry->DropUnitIntersect(unit);
  RescueUnit *RelatedUnit();
  void SetRelatedUnit(RescueUnit *unitIn);
  RESCUEINT64 TopLayerNdx() {return topLayerNdx;}
  void SetTopLayerNdx(RESCUEINT64 ndxIn) {topLayerNdx = ndxIn;}
  RESCUEINT64 BottomLayerNdx() {return bottomLayerNdx;}
  void SetBottomLayerNdx(RESCUEINT64 ndxIn) {bottomLayerNdx = ndxIn;}

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(FILE *archiveFile);
  RescueGeometryUnit(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  RescueGeometry *parentGeometry;
  RescueUnit *relatedUnit;
  RESCUEINT64 topLayerNdx;
  RESCUEINT64 bottomLayerNdx;
  RESCUEINT64 unitID;  

  friend class RescueUnit;
  friend class cSetRescueGeometryUnit;
  friend class RescueGeometry;
};

#endif




