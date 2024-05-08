/********************************************************************

  RescueWellboreProperty.h

  Property for wellbores RESCUE's data model.  Attach to 

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEWELLBOREPROPERTY_H
#define RESCUEWELLBOREPROPERTY_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueArray.h"
#include "RescueWellboreSampling.h"

class RescueLookup;
class RescueWellbore;

class RescueWellboreProperty:public RescueHistoryObject
{
public:
  RescueWellboreProperty(RescueWellboreSampling *parentSampling,
                         const RESCUECHAR *propertyName,
                         const RESCUECHAR *propertyType,
                         const RESCUECHAR *unitOfMeasure,
                         RESCUEFLOAT nullValue,
                         RESCUEFLOAT *values=0);
  // Create a Wellbore property for an array of floats.
  RescueWellboreProperty(RescueWellboreSampling *parentSampling,
                         const RESCUECHAR *propertyName,
                         const RESCUECHAR *propertyType,
                         const RESCUECHAR *unitOfMeasure,
                         RESCUEINT32 nullValue,
                         RESCUEINT32 *values=0);
  // Create a Wellbore property for an array of ints.
  RescueWellboreProperty(RescueWellboreSampling *parentSampling,
                         const RESCUECHAR *propertyName,
                         const RESCUECHAR *propertyType,
                         const RESCUECHAR *unitOfMeasure,
                         RESCUEUCHAR nullValue,
                         RescueLookup *lookupIn,
                         RESCUEUCHAR *values=0);
  // Create a Wellbore property using a lookup table where there
  // are 255 or fewer entries in the table.
  RescueWellboreProperty(RescueWellboreSampling *parentSampling,
                         const RESCUECHAR *propertyName,
                         const RESCUECHAR *propertyType,
                         const RESCUECHAR *unitOfMeasure,
                         RESCUEUSHORT nullValue,
                         RescueLookup *lookupIn,
                         RESCUEUSHORT *values=0);
  // Create a Wellbore property using a lookup table where there
  // are 2^16-1 or fewer entries in the table.
  virtual ~RescueWellboreProperty() {delete data;}
  // Delete with this->ParentSampling()->DropRescueWellboreProperty(this);
  RescueWellbore *ParentWellbore() {return parentSampling->ParentWellbore();}
  RescueWellboreSampling *ParentWellboreSampling() {return parentSampling;}
  RescueArray *Data() {return data;}
  RESCUEBOOL AnyFileTruncated() {return data->FileTruncated();}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueWellboreProperty(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentObject);
  void Dispose() {data->RescueDeleteFile();}
  void Swap() {data->LoadAndSwapArray();}

  RescueWellboreSampling *parentSampling;
  RescueArray *data;   // One value for each

  friend class cSetRescueWellboreProperty;
  friend class RescueWellboreSampling;
};

#endif




