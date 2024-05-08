/********************************************************************

  RescueSplitLine.h

  An object used by RescueGeometry for condition 5, ij vertices
  where individual corners of cells may each have their own xyz
  triplet.  Each k-layer node may therefore have up to 8 triplets.
  To save space, a default triplet is re-used if possible.

  Rod Hanks,  January	1997

*********************************************************************/
#ifndef RESCUESPLITLINE_H
#define RESCUESPLITLINE_H

#include "myHeaders.h"
#include "RescueGeometryObject.h"

class RescueSplitLine:public RescueGeometryObject
{
private:
  RescueSplitLine(RescueGeometry *geometry, 
                                 RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT step, RESCUEFLOAT origin,
                                 RESCUEFLOAT *stackValuesIn=0);
  RescueSplitLine(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RescueGeometryObject *previous);

  RescueGeometry::RescueVertexType VertexIs() {return RescueGeometry::R_SPLIT_LINE;}			
  void ZStack(RescueGeometry *geometry, RESCUEFLOAT *newZValues);
  void ZValue(RESCUEINT64 k, RESCUEFLOAT newZValue);
  void SetCornerNode(RescueGeometry *geometry,
                     RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
	void SetXValue(RescueGeometry *geometry,
                     RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT value);
	void SetYValue(RescueGeometry *geometry,
                     RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT value);
	void SetZValue(RescueGeometry *geometry,
                     RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT value);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z) {}
	void Values(RESCUEINT64 k, RESCUEFLOAT &z) {}
  void SwapKAxis(RESCUEINT64 kNodes);
  void SwapAxes(bool swapI, bool swapJ, bool swapK, RESCUEINT64 kNodes);
public:
  ~RescueSplitLine() {delete [] addresses;}
private:
  RESCUEINT64 GenerateAddress(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 iPrime, RESCUEINT64 jPrime, RESCUEINT64 kPrime);
  void Archive(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress);
  RescueSplitLine(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress);

  RESCUEFLOAT *addresses;  // 8 * 3 * k-layers.

  friend class RescueGeometry;
};

#endif




