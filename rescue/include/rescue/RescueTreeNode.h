/*************************************************************************

        RescueTreeNode.h

	Class for tree indexes.  This specialized object keeps track
  of objects, where the key is the void* pointer to the object.

        Rod Hanks               May, 1999

****************************************************************************/
#ifndef RescueTreeNode_H
#define RescueTreeNode_H
#include "boolSupport.h"

class RescueTreeNode
{
protected:
  RESCUEINT64 objectCount;
  RESCUEINT64 objectAllocated;
  Leaf **objects;

  RESCUEINT64 branchCount;
  RESCUEINT64 branchAllocated;
  RescueTreeNode **branches;

  RescueTreeNode *parentNode;

public:
  RescueTreeNode(RescueTreeNode *parentNodeIn = 0, RESCUEINT64 numberToAllocate = 20);
  ~RescueTreeNode();
  void Add(Leaf *newObject, RESCUEINT64 numberToFill, RESCUEINT64 memo = 0);
  RESCUEBOOL Delete(void *existingObject, RescueTree *tree, RESCUEINT64 memo = 0);
private:
  RescueTreeNode(RescueTreeNode *parentNodeIn, Leaf **objectList, 
                 RESCUEINT64 allocateCount, RESCUEINT64 objectCount);
  RESCUEBOOL Find(void *objectToFind, RESCUEINT64 &ndx);
  void ChildSplit(RescueTreeNode *newChild, Leaf *firstKey, RESCUEINT64 memo);
  RESCUEBOOL LayOffToLeft(Leaf *object, RESCUEINT64 numberToFill, RESCUEINT64 memo);
  RESCUEBOOL LayOffToRight(Leaf *object, RESCUEINT64 numberToFill, RESCUEINT64 memo);
  void DeleteLeaf(RESCUEINT64 memo);

  friend class RescueTree;
  friend class RescuePolyLineNodeAvatar;
};
#endif


