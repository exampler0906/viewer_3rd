/********************************************************************

  RescueVertex.h

  Vertex (used for Coordinate system) for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEVERTEX_H
#define RESCUEVERTEX_H

#include "myHeaders.h"
#include "RescueCoordinateSystem.h"
class RescueUnit;

class RescueVertex:public RescueObject
{
public:
  RescueVertex(const RESCUECHAR *name, 
               RescueCoordinateSystem *existingCoordinateSystem,
               RESCUEDOUBLE xIn, RESCUEDOUBLE yIn, RESCUEDOUBLE zIn);
  RESCUEINT64 Dimensions() {return 3;}
  RCHString *VertexName() {return vertexName;}
  void SetVertexName(RESCUECHAR *newName) {vertexName->Replace(newName);}
  RescueCoordinateSystem *CoordinateSystem() {return coordinateSystem;}
  void SetXYZ(RESCUEFLOAT xIn, RESCUEFLOAT yIn, RESCUEFLOAT zIn);
  RESCUEDOUBLE X() {return x;}
  RESCUEDOUBLE Y() {return y;}
  RESCUEDOUBLE Z() {return z;}

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  ~RescueVertex();
private:
  RescueVertex(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  void RegisterWith(RescueModel *parentModelIn);
  RCHString *vertexName;           // Is this necessary?
  RescueCoordinateSystem *coordinateSystem;
  RESCUEDOUBLE x;
  RESCUEDOUBLE y;
  RESCUEDOUBLE z;
  RescueModel *parentModel;

  friend class RescueCoordinateSystem;
  friend class RescueGrid;
  friend class RescueSurface;
  friend class RescueBlockUnit;
  friend class RescueGeobodyPart;
  friend class RescueIJSurface;
};

#endif




