/********************************************************************

  RescueBlock.h

  The block object for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEBLOCK_H
#define RESCUEBLOCK_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RCHString.h"
#include "RescueBlockUnit.h"
#include "cSetRescueBlockUnit.h"
class RescueModel;
class RescueUnit;
class RescueProperty;
class RescueBlockUnitSide;
class RescueMacroVolume;
class RescueOrientationLedger;

class RescueBlock:public RescueHistoryObject
{
public:
  RescueBlock(const RESCUECHAR *newBlockName, RescueModel *newBlockParent);
                              // Create a new block.
                              // To dispose a block, use
                              // block->ParentModel()->DropRescueBlock(block);
  virtual ~RescueBlock();
  RCHString *BlockName() {return blockName;}
                              // Do NOT delete the returned object.
  void SetBlockName(RESCUECHAR *newBlockName) {(*blockName) = newBlockName;}
  RescueModel *ParentModel() {return parentModel;}
  RESCUEBOOL IsNamed(RESCUECHAR *possibleName);

  RESCUEINT64 BlockUnitCount64() {return blockUnits->Count64();}  
  RESCUEINT32 BlockUnitCount() {return (RESCUEINT32) blockUnits->Count64();}  
  RESCUEINT32 BlockUnitCount(RESCUEBOOL throwIfTooBig);

  RescueBlockUnit *NthRescueBlockUnit(RESCUEINT64 zeroBasedOrdinal) 
                              {return blockUnits->NthObject(zeroBasedOrdinal);}
  RescueBlockUnit *NthRescueBlockUnit(RESCUEINT32 zeroBasedOrdinal) 
                              {return blockUnits->NthObject(zeroBasedOrdinal);}
  RescueBlockUnit *BlockUnitIdentifiedBy(RESCUEINT64 identifier) 
                           {return blockUnits->ObjectIdentifiedBy(identifier);}
  RescueBlockUnit *BlockUnitIdentifiedBy(RESCUEINT32 identifier) 
                           {return blockUnits->ObjectIdentifiedBy(identifier);}
  RescueBlockUnit *BlockUnitForUnit(RescueUnit *unitToFind);
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropBlockUnit(RescueBlockUnit *blockUnitToDrop) 
                         {return  ((*blockUnits) -= blockUnitToDrop);}
                                    // Mustn't drop an owned object directly.
                                    // Use the owner's drop method instead.
                                    // These return FALSE if the object passed
                                    // is not a member of the set (and in that
                                    // case the object IS NOT dropped.
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 id);
  RescueProperty *PropertyIdentifiedBy(RESCUEINT32 id) {return PropertyIdentifiedBy((RESCUEINT64) id);}
  RescueMacroVolume *MacroVolumeIdentifiedBy(RESCUEINT64 id);
  RescueMacroVolume *MacroVolumeIdentifiedBy(RESCUEINT32 id) {return MacroVolumeIdentifiedBy((RESCUEINT64) id);}
  RescueBlockUnitSide *BlockUnitSideIdentifiedBy(RESCUEINT64 id);
  RescueBlockUnitSide *BlockUnitSideIdentifiedBy(RESCUEINT32 id) {return BlockUnitSideIdentifiedBy((RESCUEINT64) id);}
  RescueGeometry *GeometryIdentifiedBy(RESCUEINT64 identifier) {return blockUnits->GeometryIdentifiedBy(identifier);}
  RescueGeometry *GeometryIdentifiedBy(RESCUEINT32 identifier) {return blockUnits->GeometryIdentifiedBy((RESCUEINT64) identifier);}
  RESCUEBOOL AnyFileTruncated() {return blockUnits->AnyFileTruncated();}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueBlock(RescueContext *, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void PrepareModelDelete() {blockUnits->PrepareModelDelete();}
  void DropWireframeMemory() {blockUnits->DropWireframeMemory();}
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile) {blockUnits->UnArchiveWireframeData(model, archiveFile);}
  void RelinkWireframeData(RescueObject *parent) {blockUnits->RelinkWireframeData(parent);}
  void ArchiveWireframeData(FILE *archiveFile) {blockUnits->ArchiveWireframeData(archiveFile);}
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RCHString *blockName;
  RescueModel *parentModel;
  cSetRescueBlockUnit *blockUnits;

  friend class RescueBlockUnit;
  friend class cSetRescueBlock;
  friend class RescueModel;
};

#endif





