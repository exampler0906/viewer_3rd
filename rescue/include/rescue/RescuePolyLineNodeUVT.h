/********************************************************************

  RescuePolyLineNodeUVT.h

  The description of a point in terms of it's position on some 
  the face of some triangle in a RescueTriangulatedSurface

  Rod Hanks,  May 2002

*********************************************************************/
#ifndef RescuePolyLineNodeUVT_H
#define RescuePolyLineNodeUVT_H

#include "myHeaders.h"

class RescueTriangulatedSurface;

class RescuePolyLineNodeUVT:public RescueObject
{
public:
  RescuePolyLineNodeUVT(RescueContext *context, RescueTriangulatedSurface *faceIn, RESCUEINT64 faceNdxIn, 
                          RESCUEFLOAT u, RESCUEFLOAT v)
                            :RescueObject(context)
                            ,uValue(u)
                            ,vValue(v)
                            ,faceNdx(faceNdxIn) 
                            ,face(faceIn)
                            ,faceID(0) {isA = R_RescuePolyLineNodeUVT;}
  void SetUVValue(RESCUEINT64 faceNdxIn, RESCUEFLOAT u, RESCUEFLOAT v) {faceNdx = faceNdxIn; uValue = u; vValue = v;}
  RESCUEFLOAT U() {return uValue;} 
  RESCUEFLOAT V() {return vValue;} 
  RESCUEINT64 FaceNdx64() {return faceNdx;}
  RESCUEINT32 FaceNdx() {return (RESCUEINT32) faceNdx;}
  RESCUEBOOL CompareFace(RescueTriangulatedSurface *toCompare);
                                     // Returns TRUE if the surface passed is the one
                                     // we are parameterized against.
  RescueTriangulatedSurface *Face(RescueModel *model);
                                    // Model pointer needed for just-in-time relinking.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					                          // Returns TRUE if the object is a
					                          // member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescuePolyLineNodeUVT(RescueContext *context, FILE *archiveFile);

private:
  RESCUEFLOAT uValue;
  RESCUEFLOAT vValue;
  RESCUEINT64 faceNdx;
  RescueTriangulatedSurface *face;

  RESCUEINT64 faceID;     // Used for just-in-time relink.

  friend class cSetRescuePolyLineNodeUVT;
};

#endif




