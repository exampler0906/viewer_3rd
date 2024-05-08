/*************************************************************************

        RescueTree.h

	Head of a tree of RescueTreeNodes.

        Rod Hanks               May, 1999

****************************************************************************/

#ifndef RescueTree_H
#define RescueTree_H

#include "boolSupport.h"
class RescueTreeNode;
class RescueListNode;

struct Leaf
{
  void *object;
  RescueListNode *listNode;
};

class RescueTree
{
protected:
  RescueTreeNode *rootNode;
  RescueListNode *listHead;
  RescueListNode *listFoot;
  RESCUEINT64 count;
  RescueListNode *traversalNode;
  RESCUEINT64 traversalNdx;
  RESCUEINT64 traversalOrdinal;
  RescueTreeNode *traversal2Node;
  RESCUEINT64 traversal2Ndx;
  RESCUEINT64 traversal2Ordinal;
public:
  RescueTree();
  ~RescueTree();
  void Add(void *newObject);
  RESCUEBOOL Delete(void *existingObject);
  void *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count(void) {return count;}
  void *TreeTraversal(RESCUEINT64 ordinal);

  friend class RescueListNode;
};

#endif




