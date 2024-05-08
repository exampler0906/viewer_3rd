/********************************************************************

  RescueTimeStepGroup.h

  A bag of RescueProperty instances which belong to a particular
  time step.

  Rod Hanks,  June 1998

*********************************************************************/
#ifndef RescueTimeStepGroup_H
#define RescueTimeStepGroup_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueProperty.h"
#include "RCHString.h"
class RescuePropertyGroup;
#include "cBagRescueProperty.h"
#include "cBagRescueGeometry.h"
class cBagInt;

class RescueTimeStepGroup:public RescueHistoryObject
{
public:
  RescueTimeStepGroup(const RESCUECHAR *timeStepNameIn,
                      RescuePropertyGroup *groupIn);
  virtual ~RescueTimeStepGroup();
  RCHString *TimeStepName() {return timeStepName;}
                              // Do NOT delete the returned object.
  void SetTimeStepName(RESCUECHAR *newTimeStepName) {*timeStepName = newTimeStepName;}
  RescuePropertyGroup *ParentGroup() {return group;}

  RESCUEINT64 RescuePropertyCount64();
  RESCUEINT32 RescuePropertyCount() {return (RESCUEINT32) RescuePropertyCount64();}
  void AddProperty(RescueProperty *toAdd);
  RescueProperty *NthRescueProperty(RESCUEINT64 zeroBasedOrdinal);
                                    // Do NOT delete the object returned.
  RescueProperty *PropertyNamed(RESCUECHAR *nameToFind);
  RescueProperty *GetProperty(RescueGeometry *geom, RESCUECHAR *propertyName);
                                    // Do NOT delete the object returned.
                                    // Returns 0 if the object does not exist.
  RESCUEBOOL RemoveRescueProperty(RescueProperty *unitToDrop);
                                    // This removes the property from the
                                    // time step group.  It is still available
                                    // thru the RescueBlockUnit or any other
                                    // groupings of which it is still a member.
  RESCUEINT64 RescueGeometryCount64();
  RESCUEINT32 RescueGeometryCount() {return (RESCUEINT32) RescueGeometryCount64();}
  void AddGeometry(RescueGeometry *toAdd); // Add it to the timestep
                                           // LGRs added to RescueTimeStepGroups need a unique 
                                           // non-zero reference id
  RescueGeometry *NthRescueGeometry(RESCUEINT64 zeroBasedOrdinal);
                                    // Do NOT delete the object returned.
  RESCUEBOOL RemoveRescueGeometry(RescueGeometry *unitToDrop);
                                    // This removes the geometry from the
                                    // time step group.  It is still available
                                    // thru the RescueBlockUnit or any other
                                    // groupings of which it is still a member.
  RESCUEBOOL TestLock() {return isLocked;}// By convention when you lock a property or group
  void SetLock();                   // you should create a RescueHistory object with a
  void ResetLock()                  // parsable description containing 'write-lock'
                {isLocked = FALSE;} // See Property Locking
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(FILE *archiveFile);
  RescueTimeStepGroup(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void LatentRelink();

  RCHString *timeStepName;
  RescuePropertyGroup *group;
  cBagRescueProperty *properties;
  cBagRescueGeometry *geometries;
  RESCUEBOOL isLocked;

  cBagInt *propertyID; // Used only during relinking.
  cBagInt *geometryID;
  RescueModel *relinkingModel;

  friend class cSetRescueTimeStepGroup;
};

#endif




