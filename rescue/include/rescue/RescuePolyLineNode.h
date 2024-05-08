/********************************************************************

  RescuePolyLineNode.h

  A point on a polyline.

  The point is described by two kinds of values.  A u,v pair gives the
  address of the point in terms of the i,j values of the some face's
  two dimensional grid.

  The x,y,z triplet gives the address of the point within the model's
  3 dimensional coordinate system.  It is calculated from the u,v pair.

  Rod Hanks,  June 1996

*********************************************************************/
#ifndef RESCUEPOLYLINENODE_H
#define RESCUEPOLYLINENODE_H

#include "myHeaders.h"
#include "RescueObject.h"
#include "RescuePolyLineNodeUV.h"
#include "cSetRescuePolyLineNodeUV.h"
#include "cSetRescuePolyLineNodeBUG.h"
#include "cSetRescuePolyLineNodeUVT.h"
class RescueIJSurface;
class RescueGeometry;
class RescuePolyLineNodeBUG;
class RescueTriangulatedSurface;

class RescuePolyLineNode:public RescueObject
{
public:
  ~RescuePolyLineNode();
  RescuePolyLineNode(RescueContext *context, RESCUEDOUBLE x, RESCUEDOUBLE y, RESCUEDOUBLE z);
  RescuePolyLineNode(RescueContext *context, RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
  void SetXYZValue(RESCUEDOUBLE x, RESCUEDOUBLE y, RESCUEDOUBLE z)
                          {xValue = x; yValue = y; zValue = z;}
  void SetXYZValue(RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z)
                          {xValue = (RESCUEDOUBLE) x; yValue = (RESCUEDOUBLE) y; zValue = (RESCUEDOUBLE) z;}
  RESCUEDOUBLE X() {return xValue;}     
  RESCUEDOUBLE Y() {return yValue;}     
  RESCUEDOUBLE Z() {return zValue;}     
/****************************************************************

  Parameterization against an IJ surface.

*****************************************************************/
  void SetUVValue(RescueIJSurface *face, RESCUEFLOAT u, RESCUEFLOAT v);
              // If face is already listed, uv is changed.
              // If not, face is added to the list.
  RESCUEINT64 FaceCount64() {return (surfaceUVs == 0) ? 0 : surfaceUVs->Count64();}
  RESCUEINT32 FaceCount() {return (surfaceUVs == 0) ? 0 : surfaceUVs->Count();}
  RESCUEINT32 FaceCount(RESCUEBOOL throwIfTooBig);
  RescueIJSurface *NthFace(RESCUEINT64 zeroBasedOrdinal); 
  RESCUEFLOAT U(RescueIJSurface *face); 
  RESCUEFLOAT V(RescueIJSurface *face); 
                  // Return u and v for a particular
                  // face (FLT_MAX if face not present).
  RESCUEBOOL  SurfaceOnNode( RescueIJSurface&  surf );
                                          // If the node has UV coords on the
                                          // given surface return TRUE
/****************************************************************

  Parameterization against a triangulated surface.

*****************************************************************/
  void SetUVValue(RescueTriangulatedSurface *surface, RESCUEINT64 faceNdx, RESCUEFLOAT u, RESCUEFLOAT v);
              // If surface is already listed, faceNdx and uv is changed.
              // If not, surface is added to the list.
  RESCUEINT64 TSurfCount64() {return (tSurfUVs == 0) ? 0 : tSurfUVs->Count64();}
  RESCUEINT32 TSurfCount() {return (tSurfUVs == 0) ? 0 : tSurfUVs->Count();}
  RescueTriangulatedSurface *NthTSurf(RescueModel *model, RESCUEINT64 zeroBasedOrdinal); 
  RESCUEFLOAT U(RescueTriangulatedSurface *tSurf); 
  RESCUEFLOAT V(RescueTriangulatedSurface *tSurf); 
                  // Return u and v for a particular
                  // face (FLT_MAX if face not present).
  RESCUEINT64 FaceNdx64(RescueTriangulatedSurface *tSurf);
  RESCUEINT32 FaceNdx(RescueTriangulatedSurface *tSurf) {return (RESCUEINT32) FaceNdx64(tSurf);}
                  // Return faceNdx for a particular face 
                  // (INT_MAX if face not present).
  RESCUEBOOL  SurfaceOnNode( RescueTriangulatedSurface&  surf );
                                          // If the node has UV coords on the
                                          // given surface return TRUE
/****************************************************************

  Parameterization against a geometry.

*****************************************************************/
  typedef enum {I_SECTION,
                J_SECTION,
                K_SLICE}                
                      RescueLayerType;
  void SetLayerValue(RescueGeometry *geometry,
                     RescueLayerType layerType,
                     RESCUEFLOAT layerNdxParam);
              // If the geometry and layerType already exist
              // the layerValue is changed, otherwise the
              // geometry and layer is added to the list.
  RESCUEINT64 LayerCount64() {return (layerParams == 0) ? 0 : layerParams->Count64();}
  RESCUEINT32 LayerCount() {return (layerParams == 0) ? 0 : layerParams->Count();}
  RESCUEINT32 LayerCount(RESCUEBOOL throwIfTooBig);
  RescuePolyLineNodeBUG *NthLayer(RESCUEINT64 zeroBasedOrdinal) 
          {return (layerParams == 0) ? 0 : layerParams->NthObject(zeroBasedOrdinal);}
  RescuePolyLineNodeBUG *ParamOn(RescueGeometry *geometry, RescueLayerType layerType);
              // Return layer ndx parameter for the given geometry
              // and layerType.
/****************************************************************/  
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescuePolyLineNode(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass RescueModel.
  RescuePolyLineNodeUV *UVForFace(RescueIJSurface *face);
  RescuePolyLineNodeUVT *UVForFace(RescueTriangulatedSurface *face);
  RESCUEDOUBLE xValue;
  RESCUEDOUBLE yValue;
  RESCUEDOUBLE zValue;

  cSetRescuePolyLineNodeUV *surfaceUVs;
  cSetRescuePolyLineNodeBUG *layerParams;
  cSetRescuePolyLineNodeUVT *tSurfUVs;

  friend class cSetRescuePolyLineNode;
  friend class RescuePolyLine;
  friend class RescueWireframe;
};

#endif




