/********************************************************************

  RescueGeobody.h

  The geobody object for RESCUE's data model.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RescueGeobody_H
#define RescueGeobody_H

#include "myHeaders.h"
#include "RescueWireframeOwner.h"
#include "RCHString.h"
#include "RescuePropertyGroup.h"
class RescueModel;
class RescueHorizon;
#include "cSetRescuePropertyGroup.h"
#include "cBagRescueBlockUnit.h"
class RescueGeobodyPart;
#include "cSetRescueGeobodyPart.h"
class RescueGeobodyVolume;
class RescueGeobodySurface;
class RescueOrientationLedger;

class RescueGeobody:public RescueWireframeOwner
{
public:
  RescueGeobody(RESCUECHAR *newBodyName, RescueModel *newParentModel);
  virtual ~RescueGeobody();
  // Create a new unit.
  // To dispose a unit, use unit->ParentModel()->DropGeobody(unit);
  RCHString *BodyName() {return bodyName;}
                              // Do NOT delete the returned object.
  void SetBodyName(RESCUECHAR *newBodyName) {(*bodyName) = newBodyName;}
  RescueModel *ParentModel() {return parentModel;}

  RESCUEINT64 PropertyGroupCount64() {return groups->Count64();}
  RESCUEINT32 PropertyGroupCount() {return groups->Count();}
  RescuePropertyGroup *NthRescuePropertyGroup(RESCUEINT64 zeroBasedOrdinal) 
                  {return groups->NthObject(zeroBasedOrdinal);}
  RescuePropertyGroup *PropertyGroupIdentifiedBy(RESCUEINT64 identifier) 
                  {return groups->ObjectIdentifiedBy(identifier);}
                                   // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescuePropertyGroup(RescuePropertyGroup *unitToDrop) 
                          {return ((*groups) -= unitToDrop);}

  RESCUEBOOL DeleteBodyPart(RescueGeobodyPart *existingBodyPart);
                                  // Any application pointers to existingBodyPart
                                  // become invalid after this.
  RESCUEINT64 GeobodyPartCount64() {return bodyParts->Count64();}
  RESCUEINT32 GeobodyPartCount() {return bodyParts->Count();}
  RESCUEINT32 GeobodyPartCount(RESCUEBOOL throwIfTooBig);
  RescueGeobodyPart *NthBodyPart(RESCUEINT64 zeroBasedOrdinal)
              {return (RescueGeobodyPart *) (*bodyParts).NthObject(zeroBasedOrdinal);}
  RESCUEBOOL IsNamed(RESCUECHAR *possibleName);
  RescueGeometry *GeometryIdentifiedBy(RESCUEINT64 identifier) {return bodyParts->GeometryIdentifiedBy(identifier);}
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 identifier);
  RescueGeobodyVolume *GeobodyVolumeIdentifiedBy(RESCUEINT64 identifier);
  RescueGeobodySurface *GeobodySurfaceIdentifiedBy(RESCUEINT64 identifier);

  RESCUEBOOL AnyFileTruncated();            // Checks all subfiles in the instantiated model.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  void FindUniquePropertyNames(cSetString *container);
private:
  virtual void Archive(FILE *archiveFile);
  RescueGeobody(RescueContext *contextIn, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void Dispose();

  void DropWireframeMemory() {bodyParts->DropWireframeMemory();}
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile) {bodyParts->UnArchiveWireframeData(model, archiveFile);}
  void RelinkWireframeData(RescueObject *parent) {bodyParts->RelinkWireframeData(parent);}
  void ArchiveWireframeData(FILE *archiveFile) {bodyParts->ArchiveWireframeData(archiveFile);}
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RCHString *bodyName;
  RescueModel *parentModel;
  cSetRescuePropertyGroup *groups;
  cSetRescueGeobodyPart *bodyParts;

  friend class cSetRescueGeobody;
  friend class RescueModel;
  friend class RescueGeobodyPart;
  friend class RescuePropertyGroup;
  friend class RescueTimeStepManager;
};

#endif




