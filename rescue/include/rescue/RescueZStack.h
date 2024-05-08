/********************************************************************

  RescueZStack.h

  An object used by RescueGeometry for condition 2, ij vertices
  where Z is given.

  Rod Hanks,  January	1997

*********************************************************************/
#ifndef RESCUEZSTACK_H
#define RESCUEZSTACK_H

#include "myHeaders.h"
#include "RescueGeometryObject.h"

class RescueGeometry;

class RescueZStack:public RescueGeometryObject
{
private:
  RescueZStack(RescueGeometry *geometry);
				// stackValuesIn must have been created with new RESCUEFLOAT[].
			  // Becomes property of this object.
  RescueZStack(RescueGeometry *geometry, RESCUEFLOAT *stackValuesIn)
				:value(stackValuesIn) {}
				// stackValuesIn must have been created with new RESCUEFLOAT[].
			  // Becomes property of this object.
  void ZStack(RescueGeometry *geometry, RESCUEFLOAT *newZValues);
  void ZValue(RESCUEINT64 k, RESCUEFLOAT newZValues);
  RescueGeometry::RescueVertexType VertexIs() {return RescueGeometry::R_UNEQUAL_AXIS;}			
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RESCUEINT64 k, RESCUEFLOAT &z) {z = value[k];}
  void SwapKAxis(RESCUEINT64 kNodes);
public:
  ~RescueZStack();
private:
  RescueZStack(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress);
  void Archive(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress);

  RESCUEFLOAT *value;

  friend class RescueGeometry;
	friend class RescueCoordinateLine;
	friend class RescueCoordinatePolyLine;
	friend class RescueSplitLine;
};

#endif




