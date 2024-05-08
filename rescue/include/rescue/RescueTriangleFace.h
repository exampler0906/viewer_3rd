/********************************************************************

  RescueTriangleFace.h

  A face on a triangulated surface.  We don't need the overhead
  so this is not a RescueObject.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RescueTriangleFace_H
#define RescueTriangleFace_H

#include "myHeaders.h"
class RescueTriangleVertex;

class RescueTriangleFace
{
public:
  RescueTriangleFace(RescueTriangleVertex *v1, RescueTriangleVertex *v2, RescueTriangleVertex *v3);
  RescueTriangleFace(RescueTriangleVertex **v);
  virtual ~RescueTriangleFace() {};

  virtual RescueTriangleVertex *NthVertex(RESCUEINT64 ordinal);
/*
  Pass an ordinal of 0, 1, 2.
*/
  virtual RescueTriangleFace *CrossFace(RESCUEINT64 ordinal);
/*
  Pass an ordinal of 0, 1, 2 to recieve (if it exists) the
  RescueTriangle face with which this face shares vertices
  (0,1),(1,2) or (2,0).
*/
protected:
  RescueTriangleFace() {vertices[0].obj = vertices[1].obj = vertices[2].obj = 0;}
/*
  This constructor does not produce a good face, but is useful for
  subclasses.
*/
  RescueTriangleFace(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *triangulatedSurface);
  virtual void DropSelf();

  union verticesInfo
  {
    long ndxOrId;
    RescueTriangleVertex *obj;
  };

  verticesInfo vertices[3];
/*
  The corners of our triangle, counter-clockwise.
*/
  RESCUEINT64 ndx;
/*
  Position in set, used in archiving/relinking.
*/
  friend class RescueTriangleVertex;
  friend class cSetRescueTriangleFace;
  friend class RescueTriangulatedSurface;
};

#endif

