/*************************************************************************

        RescueListNode.h

	Class for lists.  This specialized object keeps track
  of objects, where the key is the void* pointer to the object.

        Rod Hanks               May, 1999

****************************************************************************/
#ifndef RescueListNode_H
#define RescueListNode_H
#include "boolSupport.h"
class RescueTree;

class RescueListNode
{
protected:
  RESCUEINT64 objectCount;
  void **objects;
  RescueListNode *leftNode;
  RescueListNode *rightNode;
public:
  RescueListNode *Add(void *newObject);
  void Delete(void *existingObject, RescueTree *tree);
  ~RescueListNode();
private:
  RescueListNode(RescueListNode *leftNodeIn = 0);
  RESCUEINT64 Find(void *objectToFind);
  void Destroy();
  friend class RescueTree;
};
#endif


