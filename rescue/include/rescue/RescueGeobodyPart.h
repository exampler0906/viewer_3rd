/********************************************************************

  RescueGeobodyPart.h

  A part of a Geobody

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RescueGeobodyPart_H
#define RescueGeobodyPart_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueGrid.h"
#include "cSetRescueGeobodySurface.h"
#include "cSetRescueEdgeSet.h"
#include "RescueCoordinateSystem.h"
#include "RescueGeometry.h"
#include "cSetRescueGeobodyVolume.h"
#include "cSetRescueProperty.h"
#include "cSetRescueGeometry.h"
#include "cBagRescuePropertyGroup.h"
#include "cBagRescueBlockUnit.h"

class RescueSection;
class RescueGeobody;
class cBagInt;
class RescueColor;
class RescueOrientationLedger;

class RescueGeobodyPart:public RescueHistoryObject
{
public:
  RescueGeobodyPart(RescueGeobody *parentBody);   // Structure-only body part, no grid.
  RescueGeobodyPart(RescueCoordinateSystem::Orientation orientation,
                    RescueGeobody *parentBody,    // Geometry may be regular in all 3 directions.
                    RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                    RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                    RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                    RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                    RESCUEFLOAT k_origin, RESCUEFLOAT k_step,
                    RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                    RESCUEFLOAT missingValue);
  RescueGeobodyPart(RescueCoordinateSystem::Orientation orientation,
                    RescueGeobody *parentBody,
                    RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                    RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                    RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                    RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                    RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                    RESCUEFLOAT missingValue);
  RescueGeobodyPart(RescueCoordinateSystem::Orientation orientation,
                    RescueGeobody *parentBody,
                    RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                    RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                    RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                    RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                    RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                    RESCUEFLOAT missingValue,
                    RescueReferenceSurface *topSurfaceIn, RESCUEFLOAT topOffsetIn,
                    RescueReferenceSurface *bottomSurfaceIn, RESCUEFLOAT  bottomOffsetIn);
                                            // Constructor for a grid whose z values are 
                                            // determined by the reference surfaces and offsets.
                                            // Each k-layer is proportional to the distance between
                                            // the top and bottom reference surfaces, after the
                                            // offsets are applied. This applies only to vertexes
                                            // of type R_EQUAL_AXIS.
  RescueGeobodyPart(RescueCoordinateSystem::Orientation orientation,
                    RescueGeobody *parentBody,
                    RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                    RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                    RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                    RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                    RESCUEINT64 k_lowbound, RESCUEINT64 k_count,
                    RESCUEFLOAT missingValue,
                    RescueReferenceSurface *referenceSurfaceIn, RESCUEFLOAT referenceOffsetIn, 
                    RESCUEFLOAT thicknessIn, RescueGeometry::RescueLapType onOffLapIn);
                                            // Constructor for a grid whose z values are 
                                            // determined by the reference surface and offset.
                                            // Each k-layer is of the same thickness, determined
                                            // by the thickness argument. This applies only to vertexes
                                            // of type R_EQUAL_AXIS.
  virtual ~RescueGeobodyPart();

  RescueGeobody *Body() {return body;}

  RescueGeobodyVolume *AddGeobodyVolume();
  void DropGeobodyVolume(RescueGeobodyVolume *existingVolume);
  RescueGeobodyVolume *NthGeobodyVolume(RESCUEINT64 zeroBasedOrdinal)
                        {return (*bodyVolumes).NthObject(zeroBasedOrdinal);}

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
                  // RescueGeobodyPart does not "own" RescuePropertyGroup,
                  // so it does not create or delete them, merely
                  // catalogs relationships to them.

  void AddBlockUnit(RescueBlockUnit *existingBlockUnit);
  RESCUEBOOL DropBlockUnit(RescueBlockUnit *existingBlockUnit);
  RESCUEINT64 BlockUnitCount64() {return blockUnits->Count64();}
  RESCUEINT32 BlockUnitCount() {return blockUnits->Count();}
  RescueBlockUnit *NthBlockUnit(RESCUEINT64 zeroBasedOrdinal) {return blockUnits->NthObject(zeroBasedOrdinal);}

  RescueGeometry *GridGeometry(RESCUEINT64 zeroBasedOrdinal = 0) {return gridGeometries->NthObject(zeroBasedOrdinal);}
  RescueGeometry *GeometryIdentifiedBy(RESCUEINT64 identifier) 
                                      {return gridGeometries->ObjectIdentifiedBy(identifier);}
  RESCUEINT64 GeometryCount64() {return gridGeometries->Count64();}
  RESCUEINT32 GeometryCount() {return gridGeometries->Count();}
  RESCUEINT32 GeometryCount(RESCUEBOOL throwIfTooBig);
  void AddGeometry(RescueGeometry *newGeometry);
  void DropGeometry(RescueGeometry *toDrop);

  RESCUEINT64 PropertyCount64();
  RESCUEINT32 PropertyCount() {return (RESCUEINT32) PropertyCount64();}

  RESCUEINT64  CountOfPropertyGroup64() {return (*propertyGroups).Count64();}
  RESCUEINT64  CountOfVolumes64() { return  (*bodyVolumes).Count64(); }
  RESCUEINT32  CountOfPropertyGroup() {return (*propertyGroups).Count();}
  RESCUEINT32  CountOfVolumes() { return  (*bodyVolumes).Count(); }

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
  RescueGeobodyVolume *GeobodyVolumeIdentifiedBy(RESCUEINT64 id) {return bodyVolumes->ObjectIdentifiedBy(id);}
  RescueGeobodySurface *GeobodySurfaceIdentifiedBy(RESCUEINT64 id);
  RESCUEBOOL AnyFileTruncated();            // Checks all subfiles in the instantiated model.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueGeobodyPart(RescueContext *contextIn, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  RescueGeometry *GeometryWithId(RESCUEINT64 id);
  void Dispose();

  void DropWireframeMemory() {bodyVolumes->DropWireframeMemory();}
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile) {bodyVolumes->UnArchiveWireframeData(model, archiveFile);}
  void RelinkWireframeData(RescueObject *parent) {bodyVolumes->RelinkWireframeData(parent);}
  void ArchiveWireframeData(FILE *archiveFile) {bodyVolumes->ArchiveWireframeData(archiveFile);}
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RescueGeobody *body;
  cSetRescueGeobodyVolume *bodyVolumes;
  cBagRescuePropertyGroup *propertyGroups;
  cSetRescueGeometry *gridGeometries;
  cBagInt *propertyGroupsID;
  cBagRescueBlockUnit *blockUnits;
  cBagInt *blockUnitsID;
  RescueColor *color;

  friend class cSetRescueGeobodyPart;
  friend class RescueGrid;
  friend class RescueGeobody;
  friend class RescueProperty;
  friend class RescueTimeStepManager;
};

#endif





