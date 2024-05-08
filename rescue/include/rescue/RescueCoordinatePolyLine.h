/********************************************************************

  RescueCoordinatePolyLine.h

  An object used by RescueGeometry for condition 4, ij vertices
  where a coordinate poly line is given.

  Rod Hanks,  January	1997

*********************************************************************/
#ifndef RESCUECOORDINATEPOLYLINE_H
#define RESCUECOORDINATEPOLYLINE_H

#include "myHeaders.h"
#include "RescueGeometryObject.h"

class RescueCoordinatePolyLine:public RescueGeometryObject
{
private:
  RescueCoordinatePolyLine(RescueGeometry *geometry, RESCUEFLOAT *stackValuesIn);

  RescueGeometry::RescueVertexType VertexIs() {return RescueGeometry::R_COORDINATE_POLYLINE;}			
  void ZStack(RescueGeometry *geometry, RESCUEFLOAT *newZValues);
  void ZValue(RESCUEINT64 k, RESCUEFLOAT newZValue);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RESCUEINT64 k, RESCUEFLOAT &z); 
  void SwapKAxis(RESCUEINT64 kNodes);
public:
  ~RescueCoordinatePolyLine() {delete [] value;}
private:
  void Archive(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress);
  RescueCoordinatePolyLine(RescueContext *context, RESCUEINT64 klayers, FILE *archiveFile, RESCUEBOOL compress);

  RESCUEFLOAT *value;   // a two dimensional array with k and x=0,y=1,z=2.
  RESCUEINT64 kLayers;

  friend class RescueGeometry;
};

#endif




