/*************************************************************************

        RescueIdTreeNode.h

	Class for tree indexes.  This specialized object keeps track
  of objects, where the key is the void* pointer to the object.

        Rod Hanks               May, 1999

****************************************************************************/
#ifndef RescueIdTreeNode_H
#define RescueIdTreeNode_H
#include "boolSupport.h"
class RescueObject;

class RescueIdTreeNode
{
protected:
  RESCUEINT64 objectCount;
  RESCUEINT64 objectAllocated;
  RescueObject **objects;

  RESCUEINT64 branchCount;
  RESCUEINT64 branchAllocated;
  RescueIdTreeNode **branches;

  RescueIdTreeNode *parentNode;

public:
  ~RescueIdTreeNode();
private:
  RescueObject *Find(RESCUEINT64 identifier);
  RescueIdTreeNode(RescueIdTreeNode *parentNodeIn = 0, RESCUEINT64 numberToAllocate = 20);
  void Add(RescueObject *newObject, RESCUEINT64 numberToFill, RESCUEINT64 memo = 0);
  RescueIdTreeNode(RescueIdTreeNode *parentNodeIn, RescueObject **objectList, 
                 RESCUEINT64 allocateCount, RESCUEINT64 objectCount);
  RESCUEBOOL Find(RescueObject *objectToFind, RESCUEINT64 &ndx);
  void ChildSplit(RescueIdTreeNode *newChild, RescueObject *firstKey, RESCUEINT64 memo);
  RESCUEBOOL LayOffToLeft(RescueObject *object, RESCUEINT64 numberToFill, RESCUEINT64 memo);
  RESCUEBOOL LayOffToRight(RescueObject *object, RESCUEINT64 numberToFill, RESCUEINT64 memo);
  RESCUEBOOL Delete(RescueObject *existingObject, RESCUEINT64 memo = 0);
  void DeleteLeaf(RESCUEINT64 memo);

  friend class RescueIdTree;
};
#endif


