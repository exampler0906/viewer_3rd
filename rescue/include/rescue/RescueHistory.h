/********************************************************************

  RescueHistory.h

  A record of a change to the model, including a human-readable string,
  a parsable string, and relationships to model objects and other
  changes.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RESCUEHISTORY_H
#define RESCUEHISTORY_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
class RCHString;
class cBagRescueHistoryObject;
#include "cBagRescueHistoryObject.h"
#include "cBagRescueHistory.h"
class cBagInt;
class RescueModel;

class RescueHistory:public RescueHistoryObject
{
public:
  RescueHistory(RescueModel *parentModelIn, RESCUECHAR *changeDescription, 
                                            RESCUECHAR *parsableDescription = 0);
                                          // The object becomes the property of the model passed.
                                          // The strings, however, are copied, so if you allocated
                                          // them you should free them.
  void AddObjectChanged(RescueHistoryObject *newObjectChanged);
  void AddRelatedObject(RescueHistoryObject *newRelatedObject);
  void AddRelatedHistory(RescueHistory *newRelatedHistory);
  void RemoveObjectChanged(RescueHistoryObject *newObjectChanged);
  void RemoveRelatedObject(RescueHistoryObject *newRelatedObject);
  void RemoveRelatedHistory(RescueHistory *newRelatedHistory);

  void SetChangeDescription(const RESCUECHAR *newChangeDescription);
  void SetParsableDescription(const RESCUECHAR *newParsableDescription);

  RescueModel *ParentModel() {return parentModel;}
  RCHString *ChangeDescription() {return changeDescription;}
  RCHString *ParsableDescription() {return parsableDescription;}
  RCHString *TimeStamp() {return timeStamp;}
  RescueHistory *NthForwardRelatedHistory(RESCUEINT64 zeroBasedOrdinal) 
                                {return forwardRelatedChanges->NthObject(zeroBasedOrdinal);}
  RescueHistory *NthBackwardRelatedHistory(RESCUEINT64 zeroBasedOrdinal) 
                                {return backwardRelatedChanges->NthObject(zeroBasedOrdinal);}
  RescueHistoryObject *NthChangedObject(RESCUEINT64 zeroBasedOrdinal) 
                                {return objectsChanged->NthObject(zeroBasedOrdinal);}
  RescueHistoryObject *NthRelatedObject(RESCUEINT64 zeroBasedOrdinal) 
                                {return relatedObjects->NthObject(zeroBasedOrdinal);} 
                                          // Never delete an RCHString returned by RescueHistory.
                                          // You can delete the other objects returned by following
                                          // the instructions for the object.  For example, RescueHistory
                                          // are deleted via 
                                          // rescueHistory->ParentModel()->DropRescueHistory(rescueHistory);
  virtual ~RescueHistory();
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueHistory(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *object);  // Pass RescueModel.

  static RescueHistoryObject *FindObject(RescueModel *model, _RescueObjectType objectType, 
                                         RESCUEINT64 objectId); 

  RCHString *changeDescription;
  RCHString *parsableDescription;
  RCHString *timeStamp;
  cBagRescueHistoryObject *objectsChanged;
  cBagRescueHistoryObject *relatedObjects;
  cBagRescueHistory *forwardRelatedChanges;
  cBagRescueHistory *backwardRelatedChanges;
  RescueModel *parentModel;

  cBagInt *forwardHistory;                // These all used only during relinking.
  cBagInt *objectTypes;
  cBagInt *objectIds;
  cBagInt *relatedTypes;
  cBagInt *relatedIds;


  friend class cSetRescueHistory;
  friend class cBagRescueHistory;
  friend class RescueGeobodySurface;
  friend class RescueModelPropertyGroup;
  friend class RescueGeobodyPart;
  friend class RescueBlockUnit;
  friend class RescueWireframe;
};

#endif


