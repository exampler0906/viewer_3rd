/********************************************************************

  RescueUnit.h

  The unit object for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEUNIT_H
#define RESCUEUNIT_H

#include "myHeaders.h"
#include "RescueLogicalOrderEntry.h"
#include "RCHString.h"
#include "RescuePropertyGroup.h"
class RescueModel;
class RescueHorizon;
class RescueEventDescr;
#include "cSetRescuePropertyGroup.h"
#include "cBagRescueBlockUnit.h"

class RescueUnit:public RescueLogicalOrderEntry
{
public:
  RescueUnit(RESCUECHAR *newUnitName, RescueModel *newParentModel);
  virtual ~RescueUnit();
  // Create a new unit.
  // To dispose a unit, use unit->ParentModel()->DropRescueUnit(unit);
  RCHString *UnitName() {return unitName;}
                              // Do NOT delete the returned object.
  void SetUnitName(RESCUECHAR *newUnitName) {(*unitName) = newUnitName;}
  RescueModel *ParentModel() {return parentModel;}
  
  RESCUEINT64 PropertyGroupCount64() {return groups->Count64();}
  RESCUEINT32 PropertyGroupCount() {return groups->Count();}
  RESCUEINT32 PropertyGroupCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(groups->Count(), throwIfTooBig);}
  RescuePropertyGroup *NthRescuePropertyGroup(RESCUEINT64 zeroBasedOrdinal) 
                  {return groups->NthObject(zeroBasedOrdinal);}
  RescuePropertyGroup *PropertyGroupIdentifiedBy(RESCUEINT64 identifier) 
                  {return groups->ObjectIdentifiedBy(identifier);}
                                   // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescuePropertyGroup(RescuePropertyGroup *unitToDrop) 
                          {return ((*groups) -= unitToDrop);}

  void AddBlockUnit(RescueBlockUnit *existingBlockUnit) 
                            {(*blockUnits) += existingBlockUnit;}
  RESCUEBOOL DeleteBlockUnit(RescueBlockUnit *existingBlockUnit); 
  RescueBlockUnit *NthBlockUnit(RESCUEINT64 zeroBasedOrdinal)
    {return (RescueBlockUnit *) (*blockUnits).NthObject(zeroBasedOrdinal);}
                  // RescueUnit does not "own" RescueBlockUnits,
                  // so it does not create or delete them, merely
                  // catalogs relationships to them.
  RESCUEBOOL IsNamed(RESCUECHAR *possibleName);

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(FILE *archiveFile);
  RescueUnit(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  RCHString *unitName;
  RescueModel *parentModel;
  cBagRescueBlockUnit *blockUnits;
  cSetRescuePropertyGroup *groups;

  RESCUEINT64 horizonAboveID;           // Used in reading older models.
  RESCUEINT64 horizonBelowID;
  RESCUEINT64 eventDescrAboveID;
  RESCUEINT64 eventDescrBelowID;

  friend class RescuePropertyGroup;
  friend class cSetRescueUnit;
  friend class RescueBlockUnit;
  friend class RescueVertex;
  friend class RescueProperty;
  friend class RescueHorizon;
  friend class RescueLogicalOrder;
  friend class RescueTimeStepManager;
};

#endif




