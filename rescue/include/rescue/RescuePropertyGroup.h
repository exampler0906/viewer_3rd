/********************************************************************

  RescuePropertyGroup.h

  An arbitrary grouping of RescueTimeStepGroups, which themselves
  contain an arbitrary grouping of RescueProperty objects.  The
  property objects don't belong to this object.  If they are in
  this object they should belong to the RescueBlockUnit to which
  this object is attached.

  Rod Hanks,  May 1996 / June 1999

*********************************************************************/
#ifndef RescuePropertyGroup_H
#define RescuePropertyGroup_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueProperty.h"
#include "RCHString.h"
class RescueUnit;
class RescueBlockUnit;
#include "cSetRescueTimeStepGroup.h"
#include "RescueTimeStepGroup.h"
#include "RescueBlockUnit.h"
class RescueGeobody;
class RescueGeobodyPart;
class RescueSurface;
class RescueTimeStepManager;

class RescuePropertyGroup:public RescueHistoryObject
{
public:
                              // Beginning with v37.3, RescuePropertyGroup constructors were
                              // made private.  My mandate was to prevent people from entering
                              // duplicate group names into any single container.  Since groups
                              // are added to their container within their constructor, the only
                              // other way I could have done this was to throw an exception if
                              // an attempt was made to add a duplicate group name.
                              // The static "factories" return a new RescuePropertyGroup,
                              // or zero if the group name is a duplicate.
                              // I thought this was better than a bunch of people running into
                              // exceptions they weren't expecting.
  static RescuePropertyGroup *MakeRescuePropertyGroup(RESCUECHAR *groupNameIn,
                                                       RescueBlockUnit *blockUnitIn);
                              // Use this to group properties on block unit grids.
  static RescuePropertyGroup *MakeRescuePropertyGroup(RESCUECHAR *groupNameIn,
                                                       RescueGeobodyPart *partIn);
                              // Use this to group properties on Geobodies.
  static RescuePropertyGroup *MakeRescuePropertyGroup(RESCUECHAR *groupNameIn,
                                                       RescueSurface *surfaceIn);
                              // Use this to group properties on surfaces.
  static RescuePropertyGroup *MakeRescuePropertyGroup(RESCUECHAR *groupNameIn,
                                                       RescueModel *modelIn);
                              // Use this one to group properties on global grids.
  static RescuePropertyGroup *MakeRescuePropertyGroup(RESCUECHAR *groupNameIn, RescueModel *modelIn,
                                                       RescueDataContainer *containerIn);
                              // Use this one to group properties of data containers.
  virtual ~RescuePropertyGroup();
  RCHString *GroupName() {return groupName;}
                              // Do NOT delete the returned object.
  void SetGroupName(RESCUECHAR *newGroupName);
  RescueUnit *ParentUnit() {return unit;}
                              // Will return 0 if the group is not owned by
                              // a block unit.
  RescueBlockUnit *ParentBlockUnit() {return blockUnit;}
                              // Will return 0 if the group is not owned by
                              // a block unit.
  RescueGeobody *ParentBody() {return body;}
                              // Will return 0 if the group is not owned by
                              // a RescueGeobody.
  RescueGeobodyPart *ParentGeobodyPart() {return bodyPart;}
                              // Will return 0 if the group is not owned by
                              // a RescueGeobody.
  RescueSurface *ParentSurface() {return surface;}
                              // Will return 0 if the group is not owned by
                              // a RescueSurface.
  RescueDataContainer *Container() {return container;}
                              // etc.
  RESCUEINT32 TimeStepCount() {return (RESCUEINT32) timeSteps->Count();}
  RescueTimeStepGroup *NthTimeStepGroup(RESCUEINT32 zeroBasedOrdinal) 
                {return timeSteps->NthObject(zeroBasedOrdinal);}
                                    // DO NOT delete the object returned.  Instead,
                                    // use the corresponding drop method.
  RescueTimeStepGroup *GetStaticGroup();
                                    // Returns "Default Group", creating it if it
                                    // doesn't already exist.
  RescueTimeStepGroup *GetInitializationGroup();
                                    // Returns "Initialization Group", creating it if it
                                    // doesn't already exist.
  RESCUEBOOL DropRescueTimeStepGroup(RescueTimeStepGroup *timeStep)
                {return ((*timeSteps) -= timeStep);}
                                    // This does not affect the RescueProperties which
                                    // were part of this time step.
  RESCUEINT64 RescuePropertyCount64() {return timeSteps->NthObject(0)->RescuePropertyCount64();}
  RESCUEINT32 RescuePropertyCount() {return timeSteps->NthObject(0)->RescuePropertyCount();}
                                    // This function returns the property count
                                    // from the first time step only.  It is kept
                                    // for compatibility with older application code.
                                    // DO NOT use this method in new code.
  RescueProperty *NthRescueProperty(RESCUEINT32 zeroBasedOrdinal) 
                  {return timeSteps->NthObject(0)->NthRescueProperty(zeroBasedOrdinal);}
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
                                    // This function returns properties from the first
                                    // time step only.  It is kept
                                    // for compatibility with older application code.
                                    // DO NOT use this method in new code.
  RESCUEBOOL RemoveRescueProperty(RescueProperty *unitToDrop);
                                     // This method removes the RescueProperty from any
                                     // RescueTimeStepGroups but does not affect the RescueProperty
                                     // or access to it via any other path.
  void AddProperty(RescueProperty *toAdd);
                                     // This is a convienience method for use in situations
                                     // where the property is not time-dependent, and therefore
                                     // RescueTimeStepGroups are overkill.  It finds or creates
                                     // a RescueTimeStepGroup named "Default Group" and adds
                                     // the property to that.
  RescueTimeStepManager *GetTimeStepManager(RESCUEBOOL refresh = FALSE);
                                     // Return a time step manager that is focused on this
                                     // property group.  Delete the manager when finished.

  RESCUEBOOL TestLock() {return isLocked;} // By convention when you lock a property or group
  void SetLock();                    // you should create a RescueHistory object with a
  void ResetLock()                   // parsable description containing 'write-lock'
                {isLocked = FALSE;}  // See Property Locking
  RescueContext *Context() {return context;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescuePropertyGroup(RESCUECHAR *groupNameIn,
                               RescueBlockUnit *blockUnitIn);
                              // Use this to group properties on block unit grids.
  RescuePropertyGroup(RESCUECHAR *groupNameIn,
                               RescueGeobodyPart *partIn);
                              // Use this to group properties on Geobodies.
  RescuePropertyGroup(RESCUECHAR *groupNameIn,
                               RescueSurface *surfaceIn);
                              // Use this to group properties on surfaces.
  RescuePropertyGroup(RESCUECHAR *groupNameIn,
                               RescueModel *modelIn);
                              // Use this one to group properties on global grids.
  RescuePropertyGroup(RESCUECHAR *groupNameIn, RescueModel *modelIn,
                               RescueDataContainer *containerIn);
                              // Use this one to group properties of data containers.

  virtual void Archive(FILE *archiveFile);
  RescuePropertyGroup(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  RCHString *groupName;
  RescueModel *model;               // Only filled in if RescueModel is the owner.
  RescueUnit *unit;
  RescueBlockUnit *blockUnit;
  RescueGeobody *body;
  RescueGeobodyPart *bodyPart;
  RescueSurface *surface;
  RescueDataContainer *container;
  cSetRescueTimeStepGroup *timeSteps;
  RESCUEBOOL isLocked;
  RescueContext *context;
  RescueTimeStepManager *tsManager;

  RESCUEINT64 blockUnitID;   // used only during relinking.
  cSetRescueProperty* properties; // used only during relinking of old files.

  friend class RescueTimeStepGroup;
  friend class cSetRescuePropertyGroup;
  friend class RescueBlockUnit;
  friend class RescueUnit;
};

#endif




