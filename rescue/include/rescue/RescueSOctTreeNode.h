/*************************************************************************

        RescueSOctTreeNode.h

	Node of a tree of RescueOctTreeNodes, used for triangulated surfaces.

        Rod Hanks               January, 2000

****************************************************************************/

#ifndef RescueSOctTreeNode_H
#define RescueSOctTreeNode_H

#include "boolSupport.h"
#include "cBagRescueTriangleVertex.h"
class RescueTriangulatedSurface;
class RescueTriangleVertex;

class RescueSOctTreeNode
{
public:
  typedef enum {BOTTOM_LEFT_FRONT, BOTTOM_RIGHT_FRONT,
                BOTTOM_RIGHT_REAR, BOTTOM_LEFT_REAR,
                TOP_LEFT_FRONT   , TOP_RIGHT_FRONT,
                TOP_RIGHT_REAR   , TOP_LEFT_REAR} OctTreeBranches;
/*
  Topological key to Oct Tree branches.
*/
  RescueSOctTreeNode(RescueTriangulatedSurface *parent,
                     RESCUEFLOAT minX, RESCUEFLOAT maxX, 
                     RESCUEFLOAT minY, RESCUEFLOAT maxY,
                     RESCUEFLOAT minZ, RESCUEFLOAT maxZ,
                     RESCUEINT64 xDivisions, RESCUEINT64 yDivisions, RESCUEINT64 zDivisions);
                                      // Use the divisions to determine which way to
                                      // slice the cube.  It continues to slice while
                                      // at least one division is > 1.
                                      // Automatically added to the octTrees member
                                      // of the parent surface.  Drop using
                                      // RescueTriangulatedSurface::DropOctTree.
  ~RescueSOctTreeNode();
  virtual RESCUEINT64 VertexCount64() {return (vertices == 0) ? 0 : vertices->Count64();}
  virtual RESCUEINT32 VertexCount() {return (vertices == 0) ? 0 : vertices->Count();}
  virtual RescueTriangleVertex *NthVertex(RESCUEINT64 zeroBasedOrdinal) 
                    {return (vertices == 0) ? 0 : vertices->NthObject(zeroBasedOrdinal);}
                                      // These will return 0 unless this is a
                                      // terminal node.
  virtual RescueSOctTreeNode *Leaf(OctTreeBranches which) {return leaf[(RESCUEINT64) which];}
                                      // Do not delete any object returned by
                                      // RescueSOctTreeNode.  Leaf() may return 0.
                                      // Branching nodes may not have a leaf at
                                      // every location.
  virtual RESCUEBOOL TerminalNode();        // Returns TRUE if the node does not branch.
  RESCUEFLOAT MinX() {return minX;}
  RESCUEFLOAT MaxX() {return maxX;}
  RESCUEFLOAT MinY() {return minY;}
  RESCUEFLOAT MaxY() {return maxY;}
  RESCUEFLOAT MinZ() {return minZ;}
  RESCUEFLOAT MaxZ() {return maxZ;}
protected:
  void CommonInitialization(RESCUEFLOAT minX, RESCUEFLOAT maxX, 
                            RESCUEFLOAT minY, RESCUEFLOAT maxY,
                            RESCUEFLOAT minZ, RESCUEFLOAT maxZ); // Called during constructor, so cannot polymorph.
  RescueSOctTreeNode(FILE *archiveFile, RescueTriangulatedSurface *parentTriangulatedSurface);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
/*
  We use the position for the RescueTrimVertex so it will be easy to relink.
*/
  RescueSOctTreeNode(RescueSOctTreeNode *parent,
                     RESCUEFLOAT minX, RESCUEFLOAT maxX, 
                     RESCUEFLOAT minY, RESCUEFLOAT maxY,
                     RESCUEFLOAT minZ, RESCUEFLOAT maxZ,
                     RESCUEINT64 xDivisions, RESCUEINT64 yDivisions, RESCUEINT64 zDivisions);
  void Split(RESCUEINT64 xDivisions, RESCUEINT64 yDivisions, RESCUEINT64 zDivisions);
  RescueSOctTreeNode *LeafNode(RescueSOctTreeNode *parent,
                               RESCUEFLOAT minX, RESCUEFLOAT maxX, 
                               RESCUEFLOAT minY, RESCUEFLOAT maxY,
                               RESCUEFLOAT minZ, RESCUEFLOAT maxZ,
                               RESCUEINT64 xDivisions, RESCUEINT64 yDivisions, RESCUEINT64 zDivisions);
  RescueSOctTreeNode *LeafNode(FILE *archiveFile, RescueTriangulatedSurface *parentTriangulatedSurface);

  RescueSOctTreeNode *leaf[8];
  cBagRescueTriangleVertex *vertices;  // zero unless terminal node.
  RESCUEFLOAT minX;
  RESCUEFLOAT maxX;
  RESCUEFLOAT minY;
  RESCUEFLOAT maxY;
  RESCUEFLOAT minZ;
  RESCUEFLOAT maxZ;

  friend class cSetRescueSOctTreeNode;
};

#endif


