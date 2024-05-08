/********************************************************************

  RescueDocument.h

  A document attached to a RescueModel.

  Rod Hanks,  June, 2007

*********************************************************************/
#ifndef RescueDocument_H
#define RescueDocument_H

#include "myHeaders.h"

class RescueDocumentList;
class RescueModel;

class RescueDocument:public RescueHistoryObject
{
public:
  RescueDocument(RescueModel *model); // Is added to the model automatically, but you must
                                      // subsequently archive the model.
  ~RescueDocument();                  // Never directly delete a RescueDocument object.

  bool ImportDocument(const RESCUECHAR *pathName);
  void SetDocumentName(const RESCUECHAR *documentName);
  void ClearMetaKeywords();
  void AddMetaKeyword(const RESCUECHAR *keywordToAdd);

  RCHString *DocumentName();          // DO NOT Delete the returned object.
  cSetString *MetaKeywords();         // DO NOT Delete the returned object.
  RESCUEBOOL ContainsMetaKey(const RESCUECHAR *keyToFind);
  RESCUEINT64 DocumentLength64();
  RESCUEINT32 DocumentLength() {return (RESCUEINT32) DocumentLength64();}
  bool ExportAs(const RESCUECHAR *pathName);
private:
  RescueDocument(RescueDocumentList *list, RescueModel *model, FILE *archiveFile);
  void Archive(FILE *archiveFile);    // Writes only meta-information.
  RESCUEBOOL AnyFileTruncated();
  void UniqueMetaKeys(cSetString *toFill);

  RescueModel *model;
  RCHString *documentName;
  cSetString *metaKeywords;
  RESCUEINT64 documentLength;

  friend class RescueDocumentList;
};
#endif

