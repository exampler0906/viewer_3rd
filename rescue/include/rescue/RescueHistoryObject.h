/********************************************************************

  RescueHistoryObject.h

  This abstract object contains the behaviour for RescueObjects that
  can be added to a RescueHistor record.

  This abstract superclass can be instantiated as one of it's subclasses.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RescueHistoryObject_H
#define RescueHistoryObject_H

#include "myHeaders.h"
#include "RCHString.h"

class RescueHistoryObject:public RescueObject
{
public:
  RescueHistoryObject(RescueContext *context):RescueObject(context),objectChanges(0),objectRelated(0) {}
  virtual ~RescueHistoryObject();

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  RescueHistory *NthObjectChanges(RESCUEINT64 zeroBasedOrdinal);
  RescueHistory *NthRelatedChanges(RESCUEINT64 zeroBasedOrdinal);
private:
  void AddObjectChanged(RescueHistory *history);
  void AddRelatedChange(RescueHistory *history);
  void RemoveObjectChanged(RescueHistory *history);
  void RemoveRelatedChange(RescueHistory *history);

  cBagRescueHistory *objectChanges;
  cBagRescueHistory *objectRelated;

  friend class RescueHistory;
};

#endif





