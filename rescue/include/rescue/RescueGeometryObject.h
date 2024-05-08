/***************** R e s c u e G e o m e t r y O b j e c t *****************/
/*
		An abstract class for the objects which hold vertex data for RescueGeometry.
		This avoids the overhead of RescueObject.

		Rod Hanks,	January, 1997
*/
#ifndef RescueGeometryObject_H
#define RescueGeometryObject_H

#include "RescueGeometry.h"

class RescueGeometryObject
{
public:
  virtual ~RescueGeometryObject() {}
  virtual RescueGeometry::RescueVertexType VertexIs()=0;
	virtual void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z)=0;
	virtual void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z)=0;
	virtual void Values(RESCUEINT64 k, RESCUEFLOAT &z)=0;
  virtual void ZStack(RescueGeometry *geometry, RESCUEFLOAT *newZValues)=0;
  virtual void ZValue(RESCUEINT64 k, RESCUEFLOAT newZValues)=0;
  virtual void Archive(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress)=0;
private:
  virtual void SwapKAxis(RESCUEINT64 kNodes) {};
	friend class RescueGeometry;
};

#endif




