/********************************************************************

  RescueTrimVertex.h

  The TrimVertex anchors an end of a polyline.  It is just like a
  regular PolyLineNode, except that it keeps a list of the PolyLines
  of which it is a member.  This list can be used to navigate along
  wireframes.

  Because the objects in this list might not be in the same 
  RescueWireframe object, it keeps pointers to RescuePolyLineStub
  rather than RescuePolyLine itself.

  Rod Hanks,  July 1996 / March 2001

*********************************************************************/
#ifndef RESCUETRIMVERTEX_H
#define RESCUETRIMVERTEX_H

#include "myHeaders.h"
#include "RescuePolyLineNode.h"
#include "cSetRescuePolyLineStub.h"
#include "cBagInt.h"

class RescuePolyLine;
class RescueModel;
class RescueGeometry;
class RescueTriangleVertex;
class cBagRescueTriangleVertex;
class RescueTrimVertexStub;
class RescueWireframe;
class RescueWireframeOwner;

class RescueTrimVertex:public RescuePolyLineNode
{
public:
  RescueTrimVertex(RescueWireframeOwner *ownerIn,
                   RESCUEDOUBLE x, RESCUEDOUBLE y, RESCUEDOUBLE z);
  RescueTrimVertex(RescueWireframeOwner *ownerIn,
                   RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
  ~RescueTrimVertex();
  RescuePolyLineStub *NthPolyLine(RESCUEINT64 zeroBasedOrdinal)
                {return (*lines).NthObject(zeroBasedOrdinal);}
  virtual RescueWireframe *Owner() {return owner;}
  virtual RESCUEBOOL Equals(RescueTrimVertexStub *other);
  virtual RESCUEBOOL Equals(RescueTrimVertex *other) {return other==this;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescueTrimVertex(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass owner.
private:
  cSetRescuePolyLineStub *lines;      // We own the stubs.  We just don't own the
                                      // RescuePolyLines they represent.
  RescueWireframe *owner;
  RESCUEINT64 ndx;

  friend class cSetRescueTrimVertex;
  friend class RescuePolyLine;
  friend class RescueTriangleVertex;
  friend class cSetRescueWireframe;
  friend class RescueWireframe;
};

#endif




