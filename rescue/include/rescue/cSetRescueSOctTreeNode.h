/*************************************************************************

        cSetRescueSOctTreeNode.h

	Keeps a list of pointers to some RescueSOctTreeNode.

        Rod Hanks               January, 2000

****************************************************************************/

#ifndef cSetRescueSOctTreeNode_H
#define cSetRescueSOctTreeNode_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueSOctTreeNode;
class RescueContext;

class cSetRescueSOctTreeNode
{
protected:
  RescueSOctTreeNode **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueSOctTreeNode();
  ~cSetRescueSOctTreeNode();
  void operator+=(RescueSOctTreeNode *newObject);
  RESCUEBOOL operator-=(RescueSOctTreeNode *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueSOctTreeNode *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueSOctTreeNode *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile, RescueTriangulatedSurface *surface);
private:

  friend class RescueModel;
};

#endif



