/********************************************************************

  RescueWellboreSampling.h

  Defines the sampling rate for a group of attached properties,
  in terms of distance along the parent wellbore's geometry.

  Rod Hanks,  January, 1997

*********************************************************************/
#ifndef RescueWellboreSampling_H
#define RescueWellboreSampling_H

#include "myHeaders.h"
class RescueWellbore;
#include "RescueGrid.h"
#include "cSetRescueWellboreProperty.h"

class RescueWellboreSampling:public RescueObject
{
public:
  ~RescueWellboreSampling();
  RescueWellboreSampling(RescueWellbore *parentWellbore,
                         RESCUEINT64 count, RESCUEFLOAT origin, RESCUEFLOAT step);
  RescueWellboreSampling(RescueWellbore *parentWellbore,
                         RESCUEINT64 count,
                         RESCUEFLOAT *values);
  // Create a Wellbore sampling.  First is regular, second is irregular.
  // Points are defined in measured depth.
  // Delete with this->ParentWellbore()->DropRescueWellboreSampling(this);
  // values becomes the property of RescueWellboreSampling.
  RescueWellbore *ParentWellbore() {return parentWellbore;}
  RCHString *TimeStamp() {return timeStamp;}

  RescueGrid *SampleGrid() {return grid;}
  RESCUEINT64 Count64() {return grid->Axis(0)->Count64();}
  RESCUEINT32 Count() {return grid->Axis(0)->Count();}
  RESCUEINT64 WellborePropertyCount64() {return properties->Count64();}
  RESCUEINT32 WellborePropertyCount() {return properties->Count();}
  RescueWellboreProperty *NthRescueWellboreProperty(RESCUEINT64 zeroBasedOrdinal) 
                  {return properties->NthObject(zeroBasedOrdinal);}
  RescueWellboreProperty *PropertyDescribedBy(const RESCUECHAR *name,
                                              const RESCUECHAR *type,
                                              const RESCUECHAR *uom);
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescueWellboreProperty(RescueWellboreProperty *unitToDrop); 

  
  RESCUEFLOAT MeasuredDepthAt(RESCUEINT64 ndx);
  void SetValues(RESCUEFLOAT *values); // values becomes the property of RescueWellboreSampling.

  RESCUEBOOL AnyFileTruncated();            // Checks all subfiles in the instantiated model.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueWellboreSampling(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentObject);
  void Dispose();
  void WriteWITSML(FILE *file, RescueWellbore *wellbore, RCHString *uom);
  void Swap();
  cSetRescueWellboreProperty *properties;

  RCHString *timeStamp;
  RescueWellbore *parentWellbore;
  RescueGrid *grid;
  RESCUEFLOAT *values; // grid is parentWellbore->wellboreGrid

  friend class cSetRescueWellboreSampling;
  friend class RescueWellboreProperty;
  friend class RescueWellbore;
  friend class RescueModel;
};

#endif




