/********************************************************************

  RescueBlockUnit.h

  block unit for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEBLOCKUNIT_H
#define RESCUEBLOCKUNIT_H

#include "myHeaders.h"
#include "RescueWireframeOwner.h"
#include "RescueGrid.h"
#include "RescueBlock.h"
#include "RescueBlockUnitSide.h"
#include "cSetRescueBlockUnitSide.h"
#include "cBagInt.h"
#include "cBagRescuePropertyGroup.h"
#include "cBagRescueSection.h"
#include "cSetRescueEdgeSet.h"
#include "RescueCoordinateSystem.h"
#include "RescueGeometry.h"
#include "cSetRescueMacroVolume.h"
#include "cSetRescueGeometry.h"
#include "cBagRescueGeobodyPart.h"

class RescueUnit;
class RescueBlock;
class RescueSection;
class RescueBlockUnitHorizonSurface;
class RescuePropertyGroup;
class RescueReferenceSurface;
class RescueMacroVolume;
class RescueColor;
class RescueWireframe;
class RescueOrientationLedger;

class RescueBlockUnit:public RescueWireframeOwner
{
public:
  RescueBlockUnit(RescueBlock *parentBlock,     // Structure-only BU, no BUG.
                  RescueUnit *parentUnit);
  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,     // Geometry may be regular in all 3 directions.
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEFLOAT k_origin, RESCUEFLOAT k_step,
                  RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                  RESCUEFLOAT missingValue);
  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,     // Geometry may be regular in all 3 directions.
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT32 i_lowbound, RESCUEINT32 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT32 j_lowbound, RESCUEINT32 j_count,
                  RESCUEFLOAT k_origin, RESCUEFLOAT k_step,
                  RESCUEINT32 k_lowbound, RESCUEINT32 k_count,
                  RESCUEFLOAT missingValue);

  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,      // Geometry may be regular in i and j.
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                  RESCUEFLOAT missingValue);
  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,      // Geometry may be regular in i and j.
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT32 i_lowbound, RESCUEINT32 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT32 j_lowbound, RESCUEINT32 j_count,
                  RESCUEINT32 k_lowbound, RESCUEINT32 k_count,
                  RESCUEFLOAT missingValue);

  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                  RESCUEFLOAT missingValue,
                  RescueReferenceSurface *topSurfaceIn, RESCUEFLOAT topOffsetIn,
                  RescueReferenceSurface *bottomSurfaceIn, RESCUEFLOAT  bottomOffsetIn);
  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT32 i_lowbound, RESCUEINT32 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT32 j_lowbound, RESCUEINT32 j_count,
                  RESCUEINT32 k_lowbound, RESCUEINT32 k_count,
                  RESCUEFLOAT missingValue,
                  RescueReferenceSurface *topSurfaceIn, RESCUEFLOAT topOffsetIn,
                  RescueReferenceSurface *bottomSurfaceIn, RESCUEFLOAT  bottomOffsetIn);
                                            // Constructor for a grid whose z values are 
                                            // determined by the reference surfaces and offsets.
                                            // Each k-layer is proportional to the distance between
                                            // the top and bottom reference surfaces, after the
                                            // offsets are applied. This applies only to vertexes
                                            // of type R_EQUAL_AXIS.
  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                  RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                  RESCUEFLOAT missingValue,
                  RescueReferenceSurface *referenceSurfaceIn, RESCUEFLOAT referenceOffsetIn, 
                  RESCUEFLOAT thicknessIn, RescueGeometry::RescueLapType onOffLapIn);
  RescueBlockUnit(RescueCoordinateSystem::Orientation orientation,
                  RescueBlock *parentBlock,
                  RescueUnit *parentUnit,
                  RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                  RESCUEINT32 i_lowbound, RESCUEINT32 i_count,
                  RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                  RESCUEINT32 j_lowbound, RESCUEINT32 j_count,
                  RESCUEINT32 k_lowbound, RESCUEINT32 k_count,
                  RESCUEFLOAT missingValue,
                  RescueReferenceSurface *referenceSurfaceIn, RESCUEFLOAT referenceOffsetIn, 
                  RESCUEFLOAT thicknessIn, RescueGeometry::RescueLapType onOffLapIn);
                                            // Constructor for a grid whose z values are 
                                            // determined by the reference surface and offset.
                                            // Each k-layer is of the same thickness, determined
                                            // by the thickness argument. This applies only to vertexes
                                            // of type R_EQUAL_AXIS.
  virtual ~RescueBlockUnit();

  RescueUnit *Unit() {return unit;}
  RescueBlock *Block() {return block;}
  RescueModel *ParentModel();
  RescueBlockUnitHorizonSurface *SurfaceAboveMe() {return surfaceAboveMe;}
  RescueBlockUnitHorizonSurface *SurfaceBelowMe() {return surfaceBelowMe;}

  void SetSurfaceAboveMe(RescueBlockUnitHorizonSurface *existingSurface)
                                      {surfaceAboveMe = existingSurface;}
  void SetSurfaceBelowMe(RescueBlockUnitHorizonSurface *existingSurface)
                                      {surfaceBelowMe = existingSurface;}

  RescueMacroVolume *AddMacroVolume();
  void DropMacroVolume(RescueMacroVolume *existingVolume);
  RescueMacroVolume *NthMacroVolume(RESCUEINT64 zeroBasedOrdinal)
                        {return (*macroVolumes).NthObject(zeroBasedOrdinal);}
  RescueMacroVolume *NthMacroVolume(RESCUEINT32 zeroBasedOrdinal)
                        {return (*macroVolumes).NthObject(zeroBasedOrdinal);}
  RescueMacroVolume *MacroVolumeIdentifiedBy(RESCUEINT64 id)
                        {return (*macroVolumes).ObjectIdentifiedBy(id);}
  RescueBlockUnitSide *BlockUnitSideIdentifiedBy(RESCUEINT64 id);
  RescueBlockUnitSide *BlockUnitSideIdentifiedBy(RESCUEINT32 id) {return BlockUnitSideIdentifiedBy((RESCUEINT64) id);}

  void AddPropertyGroup(RescuePropertyGroup *existingPropertyGroup)
              {(*propertyGroups) += existingPropertyGroup;} 
  RESCUEBOOL DeletePropertyGroup(RescuePropertyGroup *existingPropertyGroup);
                                   // The group is automatically dropped from
                                   // any RescueModelPropertyGroups of which it was a
                                   // member, and any application pointers to it
                                   // become invalid.  However, the RescueProperties
                                   // which it contained are unaffected.
  RescuePropertyGroup *NthPropertyGroup(RESCUEINT64 zeroBasedOrdinal)
  {return (RescuePropertyGroup *) (*propertyGroups).NthObject(zeroBasedOrdinal);}
  RescuePropertyGroup *NthPropertyGroup(RESCUEINT32 zeroBasedOrdinal)
  {return (RescuePropertyGroup *) (*propertyGroups).NthObject(zeroBasedOrdinal);}
                  // RescueBlockUnit does not "own" RescuePropertyGroups,
                  // so it does not create or delete them, merely
                  // catalogs relationships to them.

  RescueGrid *BlockUnitGrid(RESCUEINT64 zeroBasedOrdinal = 0);
  RescueGeometry *GridGeometry(RESCUEINT64 zeroBasedOrdinal = 0) {return gridGeometries->NthObject(zeroBasedOrdinal);}
  RESCUEINT64 GeometryCount64() {return gridGeometries->Count64();}
  RESCUEINT32 GeometryCount() {return (RESCUEINT32) gridGeometries->Count64();}
  RESCUEINT32 GeometryCount(RESCUEBOOL throwIfTooBig);
  void AddGeometry(RescueGeometry *newGeometry);
  void DropGeometry(RescueGeometry *toDrop);

  RESCUEINT64 PropertyCount64();
  RESCUEINT32 PropertyCount();

  RESCUEINT64  CountOfPropertyGroup64() {return (*propertyGroups).Count64();}
  RESCUEINT64  CountOfVolumes64() { return  (*macroVolumes).Count64(); }
  RESCUEINT64 CountOfGeobodies64() { return (*geobodyParts).Count64(); }

  RESCUEINT32  CountOfPropertyGroup() {return (RESCUEINT32) (*propertyGroups).Count();}
  RESCUEINT32  CountOfVolumes() { return  (RESCUEINT32) (*macroVolumes).Count(); }
  RESCUEINT32 CountOfGeobodies() { return (RESCUEINT32) (*geobodyParts).Count(); }

  RESCUEINT32 PropertyCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32  CountOfPropertyGroup(RESCUEBOOL throwIfTooBig);
  RESCUEINT32  CountOfVolumes(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 CountOfGeobodies(RESCUEBOOL throwIfTooBig);

  RescueGeobodyPart *NthPart(RESCUEINT64 zeroBasedOrdinal) {return geobodyParts->NthObject(zeroBasedOrdinal);}
                                    // The relationship is maintained on the RescueGeobodyPart end.

  RescueGeometry *GeometryIdentifiedBy(RESCUEINT64 identifier) 
                                      {return gridGeometries->ObjectIdentifiedBy(identifier);}
  RESCUEBOOL AnyFileTruncated();
  void SetColor(RescueColor &colorIn); // Makes a copy of the color.  This is preferred.
  void SetColor(RescueColor *colorIn); // The color object becomes the property of the RescueGeometry
                                       // object.  DO NOT delete the object, nor use it to SetColor
                                       // for any other object (if you need to use the same color in
                                       // multiple places, copy it using RescueColor's constructor
                                       // takes a RescueColor object as input).  You may pass NULL
                                       // to deassign a color without assigning a new one.
  RescueColor *Color() {return color;} // Will return NULL if no color has been assigned.  DO NOT
                                       // delete the object, nor use it to SetColor for any other
                                       // object (copy it if you want to do this).
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 id);
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueBlockUnit(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void PrepareModelDelete();
  RescueGeometry *GeometryWithId(RESCUEINT64 id);
  void Dispose();
  void DropWireframeMemory() {macroVolumes->DropWireframeMemory();}
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile) {macroVolumes->UnArchiveWireframeData(model, archiveFile);}
  void RelinkWireframeData(RescueObject *parent) {macroVolumes->RelinkWireframeData(parent);}
  void ArchiveWireframeData(FILE *archiveFile) {macroVolumes->ArchiveWireframeData(archiveFile);}
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RescueBlock *block;
  RescueUnit *unit;
  RescueBlockUnitHorizonSurface *surfaceAboveMe;
  RescueBlockUnitHorizonSurface *surfaceBelowMe;
  cSetRescueMacroVolume *macroVolumes;
  cBagRescuePropertyGroup *propertyGroups;
  cSetRescueGeometry *gridGeometries;
  RESCUEINT64 blockID;
  RESCUEINT64 unitID;
  RESCUEINT64 surfaceAboveMeID;
  RESCUEINT64 surfaceBelowMeID;
  cBagInt *propertyGroupsID;
  cBagRescueGeobodyPart *geobodyParts;
  RescueColor *color;

  friend class cSetRescueBlockUnit;
  friend class RescueBlock;
  friend class RescueGrid;
  friend class RescueBlockUnitHorizonSurface;
  friend class RescueProperty;
  friend class RescuePropertyGroup;
  friend class RescueUnit;
  friend class RescueGeobodyPart;
  friend class RescueWireframe;
  friend class RescueTimeStepManager;
};

#endif





