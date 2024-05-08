/********************************************************************

  RescueHorizon.h

  The horizon object for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEHORIZON_H
#define RESCUEHORIZON_H

#include "myHeaders.h"
#include "RescueLogicalOrderEntry.h"
#include "RCHString.h"
#include "RescueBlockUnitHorizonSurface.h"
#include "cSetRescueBlockUnitHorizonSurface.h"
class RescueModel;
class RescueUnit;
class RescueEventDescr;
class RescueOrientationLedger;

class RescueHorizon:public RescueLogicalOrderEntry
{
public:
  RescueHorizon(RESCUECHAR *horizonNameIn, RescueModel *parentModelIn);
  virtual ~RescueHorizon();
  RCHString *HorizonName() {return horizonName;}
                              // Do NOT delete the returned object.
  void SetHorizonName(RESCUECHAR *newHorizonName) {(*horizonName) = newHorizonName;}
  RescueModel *ParentModel() {return parentModel;}

  RESCUEINT64 BlockUnitHorizonSurfaceCount64() {return (*surfaces).Count64();}
  RESCUEINT32 BlockUnitHorizonSurfaceCount() {return (*surfaces).Count();}
  RescueBlockUnitHorizonSurface *NthRescueBlockUnitHorizonSurface(RESCUEINT64 zeroBasedOrdinal) 
                  {return (*surfaces).NthObject(zeroBasedOrdinal);}
  RescueBlockUnitHorizonSurface *HorizonSurfaceIdentifiedBy(RESCUEINT64 identifier)
            {return (*surfaces).ObjectIdentifiedBy(identifier);}
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RescueIJSurface *SurfaceIJIdentifiedBy(RESCUEINT64 identifier);
  RescueTriangulatedSurface *SurfaceTriangulatedIdentifiedBy(RESCUEINT64 identifier);
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 identifier);
  RESCUEBOOL DropRescueBlockUnitHorizonSurface(RescueBlockUnitHorizonSurface *unitToDrop) 
                          {return ((*surfaces) -= unitToDrop);}
  RESCUEBOOL AnyFileTruncated() {return surfaces->AnyFileTruncated();}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  RESCUEBOOL IsNamed(RESCUECHAR *possibleName);
  RESCUEINT64 UnitAboveID() {return unitAboveID;}
  RESCUEINT64 UnitBelowID() {return unitBelowID;}
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueHorizon(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentObject);
  void DropWireframeMemory() {surfaces->DropWireframeMemory();}
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile) {surfaces->UnArchiveWireframeData(model, archiveFile);}
  void RelinkWireframeData(RescueObject *parent) {surfaces->RelinkWireframeData(parent);}
  void ArchiveWireframeData(FILE *archiveFile) {surfaces->ArchiveWireframeData(archiveFile);}
  void Dispose() {surfaces->Dispose();}
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RCHString *horizonName;
  RescueModel *parentModel;
  cSetRescueBlockUnitHorizonSurface *surfaces;

  RESCUEINT64 unitAboveID;                          // These are used only in reading
  RESCUEINT64 unitBelowID;                          // older models.
  RESCUEINT64 eventDescrAboveID;
  RESCUEINT64 eventDescrBelowID;

  friend class RescueBlockUnitHorizonSurface;
  friend class cSetRescueHorizon;
  friend class RescueModel;
};

#endif




