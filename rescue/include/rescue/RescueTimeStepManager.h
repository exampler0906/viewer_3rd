/********************************************************************

  RescueTimeStepManager.h

  Finds all of the RescueTimeStepGroup instances in the model and
  arranges them in order.  Time steps are in alphabetical order,
  except for the special name "Default Group", which is always first.
  Because compliant RescueModels have only timesteps named
  "Default Group" and timesteps in ISO format (YYYY-MM-DDTHH:MM:SS Z) 
  with the time always in Greenwich mean time (IE Z is always 0),
  this puts the timesteps of compliant models in proper order.

  Rod Hanks,  October, 2006

*********************************************************************/
#ifndef RescueTimeStepManager_H
#define RescueTimeStepManager_H

class RescueGeometry;
class RescueProperty;
class RescueBlockUnit;
class RescueGeobodyPart;
class RescueTimeStepGroup;
class cBagRescueTimeStepGroup;
class cSetString;

class RescueTimeStepManager
{
public:
  ~RescueTimeStepManager();

  RESCUEINT64 Count64() {return count;}                        // Number of unique time steps.
  RESCUEINT32 Count() {return (RESCUEINT32) count;}
  RESCUECHAR **UniqueTimestepNames() {return timeStepNames;} // An array of Count() timestep names.
  cSetString *UniqueTimestepNames(RESCUECHAR *from, RESCUECHAR *to);
                                                             // A set of timestep names between
                                                             // the given times, inclusive.  Times
                                                             // are in "YYYY-MM-DDTHH:MM:SS Z" format.
                                                             // The return is never null but it may
                                                             // be empty.  Delete it when you are done.
  RescueTimeStepGroup **TimeSteps() {return steps;}          // A related array of Count() time step
                                                             // bags, each of which has one or more
                                                             // RescueTimeStepGroup objects.

  RescueTimeStepGroup *GroupForTime(RESCUECHAR *timeToFind);
                                                   // Return the bag that goes with the time
                                                   // or 0 if none.
  RescueTimeStepGroup *MakeTimeStepGroup(RESCUEINT32 year, RESCUEINT32 month, RESCUEINT32 day);
  RescueTimeStepGroup *MakeTimeStepGroup(RESCUEINT32 year, RESCUEINT32 month, RESCUEINT32 day,
                                                                     RESCUEINT32 hour, RESCUEINT32 minute, RESCUEINT32 second);
  RescueTimeStepGroup *MakeTimeStepGroup(const RESCUECHAR *timeName); 
                                                   // Will return 0 if name is not standard format.
  RESCUEINT64 UniquePropertyNameCount64() {return pCount;}
  RESCUEINT32 UniquePropertyNameCount() {return (RESCUEINT32) pCount;}
  RESCUECHAR **UniquePropertyNames() {return propertyNames;}
private:
  RescueTimeStepManager(RescuePropertyGroup *group);
  void AddPropertyGroup(RescuePropertyGroup *toAdd);
  void AddTimeStep(const char *timeStepName, RescueTimeStepGroup *toAdd);
  RESCUEINT32 NdxOf(const char *timeStepName);
  RESCUEINT32 CompareRow(RESCUEINT64 ndx, const RESCUECHAR *timeStepName);

  RescuePropertyGroup *ownerGroup;

  RESCUEINT32 count;
  RESCUEINT32 allocated;
  RESCUECHAR **timeStepNames;
  RescueTimeStepGroup **steps;

  RESCUEINT32 pCount;
  RESCUEINT32 pAllocated;
  RESCUECHAR **propertyNames;

  friend class RescuePropertyGroup;
};

#endif



