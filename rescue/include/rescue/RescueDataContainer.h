/********************************************************************

  RescueDataContainer.h

  A container for properties on semi-arbitrary objects in a Rescue
  Model.

  Rod Hanks,  Feb, 2006

*********************************************************************/
#ifndef RescueDataContainer_H
#define RescueDataContainer_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueGridAxis.h"
#include "RescueCoordinateSystem.h"
#include "cSetRescueGridAxis.h"
#include "RCHString.h"

class cNameValuePair;
class cSetRescueProperty;
class cSetRescuePropertyGroup;

class RescueDataContainer:public RescueHistoryObject
{
public:
  RescueDataContainer(RescueModel *model, RescueGrid *customGrid); 
                                               // Don't reuse a grid.
                                               // RescueDataContainer becomes it's owner.
  cNameValuePair *NamedData() {return namedData;}
  RescueGrid *PropertyGrid() {return propertyGrid;}
  cSetRescueProperty *Properties() {return properties;}
  cSetRescuePropertyGroup *PropertyGroups() {return propertyGroups;}
  RescueProperty *NthRescueProperty(RESCUEINT64 zeroBasedOrdinal) 
                  {return properties->NthObject(zeroBasedOrdinal);}
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 identifier) 
                  {return properties->ObjectIdentifiedBy(identifier);}
  RescueProperty *PropertyNamed(RESCUECHAR *name) {return properties->ObjectNamed(name);}
  RescueGrid *Grid() {return propertyGrid;}
  RescueModel *ParentModel() {return model;}
  ~RescueDataContainer();
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueDataContainer(RescueModel *model,
                      FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);  // Needs RescueModel.
  RESCUEBOOL AnyFileTruncated();
  void Dispose();

  RescueModel *model;
  cNameValuePair *namedData;
  RescueGrid *propertyGrid;
  cSetRescueProperty *properties;
  cSetRescuePropertyGroup *propertyGroups;

  friend class cSetRescueDataContainer;
  friend class RescueProperty;
  friend class RescuePropertyGroup;
};

#endif




