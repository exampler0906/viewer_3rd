/********************************************************************

  RescueTriangleVertex.h

  A point on a triangulated surface.  We have to be a subclass of
  RescueObject, despite the overhead, because we need the unique ID
  feature to maintain relationships during storage and retrieval.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RescueTriangleVertex_H
#define RescueTriangleVertex_H

#include "myHeaders.h"
class RescueTriangleFace;
class cSetRescueTriangleFace;

class RescueTriangleVertex:public RescueObject
{
public:
  RescueTriangleVertex(RescueContext *context, RESCUEFLOAT xIn, RESCUEFLOAT yIn, RESCUEFLOAT zIn)
                            :RescueObject(context)
                            ,faceCount(0)
                            ,faceAllocated(0)
                            ,faces(0)
                            ,x(xIn)
                            ,y(yIn)
                            ,z(zIn)
                            ,u((RESCUEFLOAT) -999)
                            ,v((RESCUEFLOAT) -999) {};
  RescueTriangleVertex(RescueContext *context, RESCUEFLOAT xIn, RESCUEFLOAT yIn, RESCUEFLOAT zIn, RESCUEFLOAT uIn, RESCUEFLOAT vIn)
                            :RescueObject(context)
                            ,faceCount(0)
                            ,faceAllocated(0)
                            ,faces(0)
                            ,x(xIn)
                            ,y(yIn)
                            ,z(zIn)
                            ,u(uIn)
                            ,v(vIn) {};
  ~RescueTriangleVertex();

  RESCUEFLOAT X() {return x;}
  RESCUEFLOAT Y() {return y;}
  RESCUEFLOAT Z() {return z;}
  RESCUEFLOAT U() {return u;}
  RESCUEFLOAT V() {return v;}
/*
  I didn't make these virtual because I wanted them to be inlined.
*/
  virtual void SetUV(RESCUEFLOAT uIn, RESCUEFLOAT vIn) {u = uIn; v = vIn;}

  virtual RESCUEINT64 FaceCount64() {return faceCount;}
  virtual RESCUEINT32 FaceCount() {return (RESCUEINT32) faceCount;}
  virtual RescueTriangleFace *NthFace(RESCUEINT64 zeroBasedOrdinal);
protected:
  virtual void AddToFace(RescueTriangleFace *newFace);
  virtual void RemoveFromFace(RescueTriangleFace *oldFace);
  virtual void DropSelf(cSetRescueTriangleFace *faces);

  RescueTriangleVertex(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *triangulatedSurface) {};

  RescueTriangleVertex(RescueContext *context):RescueObject(context) {};
/*
  This constructor doesn't make a good vertex, but is useful
  for subclasses.
*/

  RESCUEINT64 faceCount;
  RESCUEINT64 faceAllocated;
  RescueTriangleFace **faces;
/*
  These three variables give us a simple list of faces to which we
  belong.
*/
  RESCUEFLOAT x;
  RESCUEFLOAT y;
  RESCUEFLOAT z;
/*
  Our position in 3 space.
*/
  RESCUEFLOAT u;
  RESCUEFLOAT v;
/*
  Our position on the IJ grid.
*/
  RESCUEINT64 ndx;
/*
  Position in set, used in archiving/relinking.
*/
  friend class RescueTriangleFace;
  friend class RescueTriangulatedSurface;
  friend class cSetRescueTriangleVertex;
  friend class cBagRescueTriangleVertex;
};

#endif

