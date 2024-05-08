/*************************************************************************

        cBagRescueTriangleVertex.h

	Keeps a list of pointers to RescueTriangleVertex.

        Rod Hanks               June, 1999

****************************************************************************/

#ifndef cBagRescueTriangleVertex_H
#define cBagRescueTriangleVertex_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescueTriangleVertex;
class RescueTriangulatedSurface;
class RescueContext;

class cBagRescueTriangleVertex
{
public:
  cBagRescueTriangleVertex();
  ~cBagRescueTriangleVertex();
  void operator+=(RescueTriangleVertex *newObject);
  RESCUEBOOL operator-=(RescueTriangleVertex *existingObject);
  RescueTriangleVertex *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescueTriangleVertex *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
protected:
  RescueTree *tree;

  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile, RescueTriangulatedSurface *parentSurface);

  friend class RescueSOctTreeNode;
};

#endif




