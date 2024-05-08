/********************************************************************

  RescueCoordinateLine.h

  An object used by RescueGeometry for condition 3, ij vertices
  where a coordinate line is given.

  Rod Hanks,  January	1997

*********************************************************************/
#ifndef RESCUECOORDINATELINE_H
#define RESCUECOORDINATELINE_H

#include "myHeaders.h"
#include "RescueGeometryObject.h"

class RescueGeometry;

class RescueCoordinateLine:public RescueGeometryObject
{
private:
  RescueCoordinateLine(RescueGeometry *geometry, 
                       RESCUEFLOAT xTop, RESCUEFLOAT yTop, RESCUEFLOAT zTop,
                       RESCUEFLOAT xBottom, RESCUEFLOAT yBottom, RESCUEFLOAT zBottom,
                       RESCUEFLOAT *middleValues=0);
  RescueGeometry::RescueVertexType VertexIs() {return RescueGeometry::R_COORDINATE_LINE;}			
  void ZStack(RescueGeometry *geometry, RESCUEFLOAT *newZValues);
  void ZValue(RESCUEINT64 k, RESCUEFLOAT newZValues);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RESCUEINT64 k, RESCUEFLOAT &z);
  void SwapKAxis(RESCUEINT64 kNodes);
public:
  ~RescueCoordinateLine() {delete middleZs;}
private:
  void Archive(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress);
  RescueCoordinateLine(RescueContext *context, FILE *archiveFile, RESCUEBOOL compress);

	RESCUEFLOAT xTop;
	RESCUEFLOAT yTop;
	RESCUEFLOAT zTop;
	RESCUEFLOAT xBottom;
	RESCUEFLOAT yBottom;
	RESCUEFLOAT zBottom;
  RESCUEFLOAT *middleZs;
	RESCUEINT64 middleLayers;

  friend class RescueGeometry;
};

#endif




