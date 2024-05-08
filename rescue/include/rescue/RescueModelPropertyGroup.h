/********************************************************************

  RescueModelPropertyGroup.h

  A grouping of RescuePropertyGroups for some application
  purpose.  The grouping may cross RescueBlockUnit boundaries.

  Rod Hanks,  June 1998

*********************************************************************/
#ifndef RescueModelPropertyGroup_H
#define RescueModelPropertyGroup_H

#include "myHeaders.h"
class RescueModel;
#include "RescueHistoryObject.h"
#include "RescuePropertyGroup.h"
#include "RCHString.h"
#include "cBagRescuePropertyGroup.h"

class RescueModelPropertyGroup:public RescueHistoryObject
{
public:
  RescueModelPropertyGroup(RESCUECHAR *groupNameIn,
                           RescueModel *modelIn);
  virtual ~RescueModelPropertyGroup();
  RCHString *GroupName() {return groupName;}
                              // Do NOT delete the returned object.
  void SetGroupName(RESCUECHAR *newGroupName) {(*groupName) = newGroupName;}
  RESCUEBOOL IsNamed(RESCUECHAR *possibleName) {return ((*groupName) == possibleName);}

  RESCUEINT64 GroupCount64() {return groups->Count64();}
  RESCUEINT32 GroupCount() {return groups->Count();}
  void AddGroup(RescuePropertyGroup *toAdd) {((*groups) += toAdd);}
  RescuePropertyGroup *NthGroup(RESCUEINT64 zeroBasedOrdinal) 
                  {return groups->NthObject(zeroBasedOrdinal);}
                                    // Do NOT delete the object returned.
  RESCUEBOOL RemoveGroup(RescuePropertyGroup *groupToDrop) 
                          {return ((*groups) -= groupToDrop);}
                                    // This removes the RescuePropertyGroup
                                    // from this RescueModelPropertyGroup but does
                                    // not delete the RescuePropertyGroup
                                    // or affect its accessibility from any other
                                    // path.
  RESCUEBOOL TestLock() {return isLocked;}// See Property Locking
                                    // By convention when you lock a property or group
  void SetLock();                   // you should create a RescueHistory object with a
  void ResetLock()                  // parsable description containing 'write-lock'
                {isLocked = FALSE;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(FILE *archiveFile);
  RescueModelPropertyGroup(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  RescueModel *parentModel;
  RCHString *groupName;
  cBagRescuePropertyGroup *groups;
  RESCUEBOOL isLocked;
                             
  cBagInt *propertyGroupsID; // Used only during relinking.

  friend class cSetRescueModelPropertyGroup;
};

#endif




