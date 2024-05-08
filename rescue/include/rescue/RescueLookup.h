/********************************************************************

  RescueLookup.h

  A table of lookups for properties. Individual lookup items are
  accessed by their index in the array.

  Rod Hanks,  May 1997

*********************************************************************/
#ifndef RescueLookup_H
#define RescueLookup_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RCHString.h"
class RescueLookupItem;
class RescueModel;

class RescueLookup:public RescueHistoryObject
{
public:
  RescueLookup(RESCUECHAR *newName, RESCUEINT64 size, RescueModel *newParentModel);
  // Create a new lookup.
  virtual ~RescueLookup();
  // To dispose a lookup, use lookup->ParentModel()->DropRescueLookup(lookup);
  RCHString *LookupName() {return name;}
                              // Do NOT delete the returned object.
  void SetName(RESCUECHAR *newName) {(*name) = newName;}
  RescueModel *ParentModel() {return parentModel;}

  RESCUEBOOL IsNamed(RESCUECHAR *possibleName) {return ((*name) == possibleName);}
  RESCUEINT64 Count64() {return count;}
  RESCUEINT32 Count() {return (RESCUEINT32) count;}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);
  RescueLookupItem *NthItem(RESCUEINT64 zeroBasedIndex);
  void SetNthItem(RESCUEINT64 zeroBasedIndex, RescueLookupItem *newItem);

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(FILE *archiveFile);
  RescueLookup(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  RCHString *name;
  RescueModel *parentModel;
  RESCUEINT64 count;
  RescueLookupItem **lookups;

  friend class cSetRescueLookup;
  friend class RescueModel;
  friend class RescueProperty;
  friend class RescueWellboreProperty;
};

#endif




