/********************************************************************

  RescueReservoir.h

  Allows a writer to formally declare a Reservoir as a collection
  of RescueUnits.

  No relinking.  We just keep the id of the unit instead of a pointer
  to the unit.

  Rod Hanks,  September, 2001

*********************************************************************/
#ifndef RescueReservoir_H
#define RescueReservoir_H

#include "myHeaders.h"
#include "RescueObject.h"
#include "RescueUnit.h"
#include "cBagInt.h"

class RescueReservoir:public RescueObject
{
public:
  ~RescueReservoir();
  RescueReservoir(RescueModel *model, RESCUECHAR *reservoirName);
          // Do not delete these objects.  Use RescueModel::DropRescueReservoir.
  RCHString *ReservoirName() {return reservoirName;}
  void AddUnit(RescueUnit *toAdd);
  void DeleteUnit(RescueUnit *toDelete);
  RESCUEINT64 UnitCount64() {return unitIds->Count64();}
  RESCUEINT32 UnitCount() {return unitIds->Count();}
                                  // Returns the number of unit ids that have been
                                  // added.
  RESCUEINT64 NthUnitId64(RESCUEINT64 zeroBasedOrdinal) {return unitIds->NthObject(zeroBasedOrdinal);}
  RESCUEINT32 NthUnitId(RESCUEINT32 zeroBasedOrdinal) {return (RESCUEINT32) unitIds->NthObject(zeroBasedOrdinal);}
                                  // Use RescueModel::UnitIdentifiedBy to get the object.
  RescueUnit *NthUnit(RescueModel *model, RESCUEINT64 zeroBasedOrdinal);
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescueReservoir(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object) {}
private:
  RCHString *reservoirName; 
  cBagInt *unitIds;

  friend class RescueModel;
  friend class cSetRescueReservoir;
};

#endif




