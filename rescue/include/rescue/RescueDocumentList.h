/********************************************************************

  RescueDocumentList.h

  A document of documents attached to a RescueModel.

  Rod Hanks,  June, 2007

*********************************************************************/
#ifndef RescueDocumentList_H
#define RescueDocumentList_H

#include "myHeaders.h"
class RescueDocument;

class RescueDocumentList:public RescueHistoryObject
{
public:
  ~RescueDocumentList();

  RESCUEINT64 Count64() {return count;}
  RESCUEINT32 Count() {return (RESCUEINT32) count;}
  RescueDocument *NthRescueDocument(RESCUEINT64 zeroBasedIndex);
                                // Never directly delete a RescueDocument object.
  cSetString *UniqueMetaKeys(); // This is expensive so don't do it iteratively.
                                // Delete the object when you are thru.
  RescueDocument *NthDocumentWithKey(RESCUEINT64 zeroBasedIndex, const RESCUECHAR *keyToFind);
                                // May return null.
  RESCUEBOOL RemoveDocument(RescueDocument *toRemove); // Archive model afterwards.

private:
  RescueDocumentList(RescueModel *model);
  RescueDocumentList(RescueModel *model, RESCUEINT64 uniqueIdIn); // This one will read.
  void Archive();
  void Archive(FILE *archiveFile);
  void UnArchive(FILE *archiveFile);
  RESCUEBOOL AnyFileTruncated();
  RESCUEBOOL FileTruncated();
  void Add(RescueDocument *newObject);
  void EmptySelf(void);

  RESCUEINT64 fileVersion;
  RESCUEINT64 count;
  RESCUEINT64 allocated;
  RescueDocument **documents;
  RescueModel *model;

  friend class RescueModel;
  friend class RescueDocument;
};
#endif

