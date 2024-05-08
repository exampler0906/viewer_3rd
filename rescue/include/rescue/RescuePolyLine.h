/********************************************************************

  RescuePolyLine.h

  An edge on a wireframe drawing.  It contains RescueTrimVertexStub
  objects for the ends, because they might be stored in a separate
  Wireframe object, but it contains the actual RescuePolyLineNode 
  objects, because they will always be in the same RescueWireframe object.

  Rod Hanks,  July 1996 / March 2001

*********************************************************************/
#ifndef RESCUEPOLYLINE_H
#define RESCUEPOLYLINE_H

#include "myHeaders.h"
#include "RescuePolyLineNode.h"
#include "RescueObject.h"
class RescueTrimVertex;
class RescueModel;
class RescueGeometry;
class RescueWireframe;
class RescueWireframeStub;
class RescuePolyLineStub;
class RescueTrimVertexStub;
class RescueWireframeOwner;
#include "cSetRescuePolyLineNode.h"
#include "RescueWireframe.h"

class RescuePolyLine:public RescueObject
{
public:
  ~RescuePolyLine();
  RescuePolyLine(RescueWireframeOwner *ownerIn, 
                 RescueTrimVertex *leftVertexIn, 
                 RescueTrimVertex *rightVertexIn);
  virtual RESCUEBOOL Equals(RescuePolyLineStub *other);
  virtual RESCUEBOOL Equals(RescuePolyLine *other) {return other==this;}
  RescueWireframe *Owner() {return owner;}
  RescueModel *ParentModel() {return owner->ParentModel();}
  cSetRescuePolyLineNode *PolyLineNodes() {return polyLineNodes;}
/****************************************************************************************************

    The stub methods let you find out if you are stepping into a part of the model
    that has not been loaded.  From the RescueTrimVertexStub you can find the
    RescueWireframe involved in the node, and you can find out if that node is
    loaded.

*************************************************************************************************/
  RescueTrimVertexStub *LeftVertexObj() {return leftVertex;}
  RescueTrimVertexStub *RightVertexObj() {return rightVertex;}
/*********************************************************************************************

    These methods will automatically load the wireframe if the part you need for
    the traversal is not yet loaded.

**********************************************************************************************/
  RescueTrimVertex *LeftVertex();
  RescueTrimVertex *RightVertex();
/*********************************************************************************************

  Caution: RescueTrimEdge keeps a copy of the RescueTrimVertexStub information for the left
           and right vertex of its polyline.  If there was ever a way to modify the vertex of
           an existing RescuePolyLine we would need to update these as well . . . a potentially
           impossible task, since they may not be in the same RescueWireframe.
**********************************************************************************************/
  RescuePolyLineNode *Traverse(RESCUEINT64 zeroBasedOrdinal);
  RESCUEINT64 InnerNodeCount64() {return polyLineNodes->Count64();}  // Does not include vertexes at the ends.
  RESCUEINT32 InnerNodeCount() {return polyLineNodes->Count();}  // Does not include vertexes at the ends.
  RESCUEINT32 InnerNodeCount(RESCUEBOOL throwIfTooBig);
  RescuePolyLineNode *NthInnerNode(RESCUEINT64 zeroBasedNdx) {return polyLineNodes->NthObject(zeroBasedNdx);}
/**********************************************************************************************

    Normal type-handling function.

********************************************************************************************/
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(FILE *archiveFile);
  virtual void ArchiveStub(FILE *archiveFile);
  RescuePolyLine(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass owner.
private:
  cSetRescuePolyLineNode *polyLineNodes;
  RescueTrimVertexStub *leftVertex;
  RescueTrimVertexStub *rightVertex;
  RescueWireframe *owner;

  friend class cSetRescuePolyLine;
  friend class RescueTrimEdge;
  friend class RescueTrimLoop;
  friend class RescueTriangleVertex;
  friend class cSetRescueWireframe;
  friend class RescueWireframe;
};

#endif




