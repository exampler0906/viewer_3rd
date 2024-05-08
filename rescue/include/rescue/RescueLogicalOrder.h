/********************************************************************

  RescueLogicalOrder.h

  This object is used to declare the logical ordering of 
  RescueUnit, RescueHorizon, and RescueEventDescr (unconformity
  and diapir).

  Rod Hanks,  June 2002

*********************************************************************/
#ifndef RescueLogicalOrder_H
#define RescueLogicalOrder_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
class RescueEventDescr;

class RescueLogicalOrder:public RescueHistoryObject
{
public:
  RESCUEINT64 Count64() {return count;}
  RESCUEINT32 Count() {return (RESCUEINT32) count;}
  RescueLogicalOrderEntry *NthObject(RESCUEINT32 zeroBasedOrdinal);
                                // Returns objects from base to top, with
                                // the zeroth object being the base.  Returns
                                // 0 if the ordinal is out of bounds.  Use
                                // RescueObject::IsOfType() to determine what
                                // kind of object you got (RescueUnit, RescueHorizon,
                                // or RescueEventDescr).
  RESCUEINT32 NdxOf(RescueLogicalOrderEntry *object);
                                // Returns the index of the given object
                                // (RescueUnit, RescueHorizon, or RescueEventDescr)
                                // within the logical ordering or -1 if the
                                // object is not currently contained in the
                                // logical ordering.
  RescueUnit *NthUnit(RESCUEINT32 zeroBasedOrdinal);
                                // Returns units from base to top, where the
                                // zeroth unit is the base unit.  Returns 0 if
                                // the ordinal is out of bounds.
  RescueHorizon *NthHorizon(RESCUEINT32 zeroBasedOrdinal);
                                // Returns horizons from base to top where the
                                // zeroth horizon is the base horizon.  Returns
                                // 0 if the ordinal is out of bounds.
  RescueUnit *BottomUnit();
  RescueUnit *TopUnit();
  RescueHorizon *BottomHorizon();
  RescueHorizon *TopHorizon();

  RescueHorizon *HorizonAbove(RescueLogicalOrderEntry *existingObject);
  RescueHorizon *HorizonBelow(RescueLogicalOrderEntry *existingObject);
  RescueUnit *UnitAbove(RescueLogicalOrderEntry *existingObject);
  RescueUnit *UnitBelow(RescueLogicalOrderEntry *existingObject);
  RescueEventDescr *EventAbove(RescueLogicalOrderEntry *existingObject);
  RescueEventDescr *EventBelow(RescueLogicalOrderEntry *existingObject);
                                // These find the object of the correct type
                                // which is above or below the named object
                                // before an object of the same type as the
                                // named object is passed.
  RescueLogicalOrderEntry *UnconformityEventAbove(RescueEventDescr *existingObject);
  RescueLogicalOrderEntry *UnconformityEventBelow(RescueEventDescr *existingObject);
                                // These look for old style "RescueEvents",
                                // which are either RescueHorizon or
                                // RescueEventDescr which are between the
                                // existing object and the next RescueUnit.
  ~RescueLogicalOrder();        // Don't delete this object.  Let RescueModel
                                // Take care of it.
  void InsertAtBase(RescueLogicalOrderEntry *unit);
                                // Inserts the given object into the list at
                                // the base of the structure.  If the object
                                // is already in the list it is moved to the
                                // new location.
  void InsertAtTop(RescueLogicalOrderEntry *unit);
                                // Inserts the given object into the list at
                                // the top of the structure.  If the object
                                // is already in the list it is moved to the
                                // new location.
  RESCUEBOOL InsertAbove(RescueLogicalOrderEntry *existingObject, RescueLogicalOrderEntry *unit);
                                // Inserts the given object into the list
                                // above the existing object, if the existing
                                // object is in the list.  If not it does
                                // nothing.  Returns TRUE if the object was inserted.
  RESCUEBOOL InsertBelow(RescueLogicalOrderEntry *existingObject, RescueLogicalOrderEntry *unit);
                                // Inserts the given object into the list
                                // below the existing object, if the existing
                                // object is in the list.  If not it does
                                // nothing.  Returns TRUE if the object was inserted.
  RESCUEBOOL Remove(RescueLogicalOrderEntry *existingObject);
private:
  RescueLogicalOrder(RescueContext *context);
                                // The class is constructed automatically
                                // when needed by RescueModel::LogicalOrder();
  RescueLogicalOrder(RescueModel *model, FILE *archiveFile);
                                // Since the class is read and written last
                                // it can relink as it is reading.  No need
                                // to hold the id's and try later.
  void Archive(RescueContext *context, FILE *archiveFile);
  void EnsureCapacity();
  void BuildFrom(RescueModel *model);

  RESCUEINT64 allocated;
  RESCUEINT64 count;
  RescueLogicalOrderEntry **orderedItems;

  friend class RescueModel;
};

#endif


