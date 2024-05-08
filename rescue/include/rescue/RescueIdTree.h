/*************************************************************************

        RescueIdTree.h

	Head of a tree of RescueIdTreeNodes.

        Rod Hanks               May, 1999

****************************************************************************/

#ifndef RescueIdTree_H
#define RescueIdTree_H

#include "boolSupport.h"
class RescueIdTreeNode;
class RescueObject;

class RescueIdTree
{
protected:
  RescueIdTreeNode *rootNode;
  RESCUEINT64 count;

public:
  RescueIdTree();
  ~RescueIdTree();
  void Add(RescueObject *newObject);
  RESCUEBOOL Delete(RescueObject *existingObject);
  RescueObject *Find(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void) {return count;}
  RESCUEINT32 Count(void) {return (RESCUEINT32) count;}
};

#endif




