/********************************************************************

  RescueProperty.h

  Property for RESCUE's data model.  Attach to 

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEPROPERTY_H
#define RESCUEPROPERTY_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RCHString.h"
#include "RescueArray.h"
#include "RescueArray2dVector.h"
#include "RescueArray3dVector.h"
#include "cSetRescueTrimLoopStub.h"
#include "RescueIJSurface.h"
class RescuePropertyGroup;

class RescueLookup;
class RescueColorTable;
class RescueGeobodyPart;
class RescueTrimLoop;
class RescueTriangulatedSurface;
class RescueDataContainer;

class RescueProperty:public RescueHistoryObject
{
public:
/**********************************************************************************************

    Constructors for properties on triangulated representations of RescueTriangulatedSurface.

**********************************************************************************************/
  typedef enum {FRONT, BACK, BOTH, NA} AppliesToSurface;
  typedef enum {CELL_CENTERED, FACE_CENTERED, NODE_CENTERED, 
                I1_FACE, I2_FACE, J1_FACE, J2_FACE, K1_FACE, K2_FACE} AttachmentPoint;
/*********************************************************************************************

  Attachment points.
  Surfaces should be FACE_CENTERED or NODE_CENTERED.
  BUGS     should be CELL_CENTERED, I1_FACE, I2_FACE, J1_FACE, J2_FACE, K1_FACE, K2_FACE.

  I1_FACE - The face of the cell for which the I indexes are constant and are lowest.
  I2_FACE - The face of the cell for which the I indexes are constant and are highest.
  J1_FACE - The face of the cell for which the J indexes are constant and are lowest.
  J2_FACE - The face of the cell for which the J indexes are constant and are highest.
  K1_FACE - The face of the cell for which the K indexes are constant and are lowest.
  K2_FACE - The face of the cell for which the K indexes are constant and are highest.

**********************************************************************************************/

  RescueProperty(RescueTriangulatedSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RESCUEFLOAT nullValue, 
                 RESCUEFLOAT *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for floats,
  RescueProperty(RescueTriangulatedSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RESCUEINT32 nullValue, 
                 RESCUEINT32 *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for ints,
  RescueProperty(RescueTriangulatedSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RescueLookup *lookupTableIn,
                 RESCUEUCHAR nullValue, 
                 RESCUEUCHAR *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for a lookup table
                            // with 255 or fewer entries,
  RescueProperty(RescueTriangulatedSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RescueLookup *lookupTableIn,
                 RESCUEUSHORT nullValue, 
                 RESCUEUSHORT *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for a lookup table
                            // with 2^16-1 or fewer entries,
  RescueProperty(RescueTriangulatedSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 Rescue2dVector nullValue, 
                 Rescue2dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for 2d vectors,
  RescueProperty(RescueTriangulatedSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 Rescue3dVector nullValue, 
                 Rescue3dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for 3d vectors,
/**********************************************************************************************
:
:    Constructors for properties on RescueSurfaces.  If no RescueIJSurface is passed,
:    these constructors attach the property to the first RescueIJSurface for the surface 
:    (they will seg-fault if there is no such representation).  
:
**********************************************************************************************/
  RescueProperty(RescueSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RESCUEFLOAT nullValue, 
                 RESCUEFLOAT *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED,
                 RescueIJSurface *parentIJSurface = 0);
                            // Constructs a property array for floats,
  RescueProperty(RescueSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RESCUEINT32 nullValue, 
                 RESCUEINT32 *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED,
                 RescueIJSurface *parentIJSurface = 0);
                            // Constructs a property array for ints,
  RescueProperty(RescueSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RescueLookup *lookupTableIn,
                 RESCUEUCHAR nullValue, 
                 RESCUEUCHAR *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED,
                 RescueIJSurface *parentIJSurface = 0);
                            // Constructs a property array for a lookup table
                            // with 255 or fewer entries,
  RescueProperty(RescueSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RescueLookup *lookupTableIn,
                 RESCUEUSHORT nullValue, 
                 RESCUEUSHORT *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED,
                 RescueIJSurface *parentIJSurface = 0);
                            // Constructs a property array for a lookup table
                            // with 2^16-1 or fewer entries,
  RescueProperty(RescueSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 Rescue2dVector nullValue, 
                 Rescue2dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED,
                 RescueIJSurface *parentIJSurface = 0);
                            // Constructs a property array for 2d vectors,
  RescueProperty(RescueSurface *parentSurface,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 Rescue3dVector nullValue, 
                 Rescue3dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED,
                 RescueIJSurface *parentIJSurface = 0);
                            // Constructs a property array for 3d vectors,
/**********************************************************************************************

    Constructors for properties in RescueGeobodyPart and RescueBlockUnit.  Pass the
    RescueGeometry object.  This object must not be null.

**********************************************************************************************/
  RescueProperty(RescueGeometry *geometryIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 RESCUEFLOAT nullValue, RESCUEFLOAT *valueArray = 0,
                 AttachmentPoint attachedToIn = CELL_CENTERED);
                            // Constructs a property array for floats,
  RescueProperty(RescueGeometry *geometryIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 RESCUEINT32 nullValue, RESCUEINT32 *valueArray = 0,
                 AttachmentPoint attachedToIn = CELL_CENTERED);
                            // Constructs a property array for ints,
  RescueProperty(RescueGeometry *geometryIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 RescueLookup *lookupTableIn,
                 RESCUEUCHAR nullValue, 
                 RESCUEUCHAR *valueArray = 0,
                 AttachmentPoint attachedToIn = CELL_CENTERED);
                            // Constructs a property array for a lookup table
                            // with 255 or fewer entries,
  RescueProperty(RescueGeometry *geometryIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 RescueLookup *lookupTableIn,
                 RESCUEUSHORT nullValue, 
                 RESCUEUSHORT *valueArray = 0,
                 AttachmentPoint attachedToIn = CELL_CENTERED);
                            // Constructs a property array for a lookup table
                            // with 2^16-1 or fewer entries,
  RescueProperty(RescueGeometry *geometryIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 Rescue2dVector nullValue, 
                 Rescue2dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = CELL_CENTERED);
                            // Constructs a property array for 2d vectors,
  RescueProperty(RescueGeometry *geometryIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 Rescue3dVector nullValue, 
                 Rescue3dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = CELL_CENTERED);
                            // Constructs a property array for 3d vectors,
/**********************************************************************************************

    Constructors for properties in RescueDataContainer

**********************************************************************************************/

  RescueProperty(RescueDataContainer *containerIn,
                 RescueModel *modelIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RESCUEFLOAT nullValue, 
                 RESCUEFLOAT *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for floats,
  RescueProperty(RescueDataContainer *containerIn,
                 RescueModel *modelIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RESCUEINT32 nullValue, 
                 RESCUEINT32 *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for ints,
  RescueProperty(RescueDataContainer *containerIn,
                 RescueModel *modelIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RescueLookup *lookupTableIn,
                 RESCUEUCHAR nullValue, 
                 RESCUEUCHAR *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for a lookup table
                            // with 255 or fewer entries,
  RescueProperty(RescueDataContainer *containerIn,
                 RescueModel *modelIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 RescueLookup *lookupTableIn,
                 RESCUEUSHORT nullValue, 
                 RESCUEUSHORT *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for a lookup table
                            // with 2^16-1 or fewer entries,
  RescueProperty(RescueDataContainer *containerIn,
                 RescueModel *modelIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 Rescue2dVector nullValue, 
                 Rescue2dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for 2d vectors,
  RescueProperty(RescueDataContainer *containerIn,
                 RescueModel *modelIn,
                 const RESCUECHAR *propertyNameIn, 
                 const RESCUECHAR *propertyTypeIn, 
                 const RESCUECHAR *unitOfMeasureIn,
                 AppliesToSurface applies,
                 Rescue3dVector nullValue, 
                 Rescue3dVector *valueArray = 0,
                 AttachmentPoint attachedToIn = FACE_CENTERED);
                            // Constructs a property array for 3d vectors,
  virtual ~RescueProperty();

  RescueBlockUnit *ParentBlockUnit() {return parentBlockUnit;}
                            //  Will return null unless the property is owned by
                            // a RescueBlockUnit.
  RescueGeobodyPart *ParentGeobodyPart() {return parentGeobodyPart;}
                            // Will return null unless the property is owned by
                            // a RescueGeobodyPart.
  RescueSurface *ParentSurface() {return surface;}
                            // Will return null unless the property is owned by
                            // a RescueSurface.
  RescueIJSurface *ParentIJSurface() {return ijSurface;}
                            // Will return null unless the property is owned by
                            // a RescueSurface.  You can get the grid from the ijSurface.
  RescueDataContainer *Container() {return container;}
  RESCUEBOOL TriangulatedSurface() {return triangulatedSurface;}
                            // Returns TRUE if the property is attached to a triangulated
                            // surface.
  RESCUEINT64 TrimLoopCount64() {return ((loops == 0) ? 0 : loops->Count64());}
  RESCUEINT32 TrimLoopCount() {return ((loops == 0) ? 0 : loops->Count());}
                            // Returns the number of trim loops available to show
                            // areas on the surface are covered by the property.
                            // Will be zero for properties not on a surface.
  RescueTrimLoopStub *NthTrimLoop(RESCUEINT64 zeroBasedOrdinal) {return (loops == 0) ? 0 : loops->NthObject(zeroBasedOrdinal);}
                            // Will only return data for properties on surfaces.
  AppliesToSurface HowApplies() {return howApplies;}
                            // Valid only for properties on surfaces.
  AttachmentPoint PropertyAttachedTo() {return attachedTo;}
                            // Valid for all properties.
                            // Surfaces should be FACE_CENTERED or NODE_CENTERED.
                            // BUGS     should be CELL_CENTERED, I1_FACE, I2_FACE, J1_FACE, J2_FACE, K1_FACE, K2_FACE.
  void AddTrimLoop(RescueTrimLoop *existingLoop);
                            // Will accept loops only for properties on surfaces.
  void RelinkTrimLoops(RescueModel *model);
                            // This relinks the backward pointers from RescueTrimLoops to their
                            // owning RescueProperty instances.  It is normally only called
                            // during conversion of pre-v29 files.
  RescueArray *Data() {return data;}
                            // Use data->IsOfType() to discover if the
                            // object is one of RescueArrayFloat, 
                            // RescueArrayByte, or RescueArrayShort.
                            // Then cast the returned pointer and access
                            // accordingly.
  RescueGeometry *Geometry() {return geometry;}
                            // Will return null unless the property is owned by
                            // a RescueBlockUnit or a RescueGeobodyPart.
                            // From the geometry you can get the grid.
                            // If the RescueBlockUnit has multiple geometries
                            // you need to check this value to see if it is
                            // the one you are interested in.
  void SetColorTable(RescueColorTable *newTable);
                            // Assigns the color table to this property.  The table
                            // becomes the property of this property.  Do NOT delete
                            // the RescueColorTable after this.  DO NOT pass a color
                            // table from RescueModel->ColorTableList()->TableFor()
                            // (If you want to do this make a copy using RescueColorTable's
                            // copy constructor first).
                            // If the property already had a color table defined it is
                            // deleted and any application pointers to it become invalid.
                            // To remove an existing table without setting a new one,
                            // pass newTable = 0.
                            // When you replace an existing color table, the file associated
                            // with the current color table is deleted.  If your actual
                            // intention was to transfer the color table to a new property
                            // or to RescueModel's ColorTableList that is okay.  When the
                            // table is next unloaded it will be written out again.  You
                            // may want to use RescueColorTable->MarkChanged().
  RescueColorTable *ColorTable() {return colorTable;}
                            // Returns a color table defined for this property, or
                            // 0 if no color table has been defined (in that case you
                            // may be able to find one for the property type using
                            // model->ColorTableList()->TableFor(
                            //            property->Data()->PropertyType()->String()).
  RESCUEBOOL AnyFileTruncated() {return data->FileTruncated();}
  RESCUEBOOL IsNamed(RESCUECHAR *mayBeName);
  RESCUEBOOL TestLock() {return isLocked;}// By convention when you lock a property or group
  void SetLock() {isLocked = TRUE;} // you should create a RescueHistory object with a
  void ResetLock()                  // parsable description containing 'write-lock'
                {isLocked = FALSE;} // See Property Locking
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(FILE *archiveFile);
  RescueProperty(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void VetIJSurface();
  void Dispose();
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);
  void SwapAxes(bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes); 
  void SwapAxes(bool swapI, RESCUEINT64 iNodes, 
                bool swapJ, RESCUEINT64 jNodes,
                bool swapK, RESCUEINT64 kNodes);

  RescueBlockUnit *parentBlockUnit;      // This pointer is valid for properties in block units.
  RescueGeobodyPart *parentGeobodyPart;  // This pointer is valid for properties in geobodies.
  RescueGeometry *geometry;              // This pointer is valid for properties in block units and
                                         // geobodies.
  RescueDataContainer *container;        // Etc.
  RescueSurface *surface;                // This pointer is valid for properties on surfaces.
  cSetRescueTrimLoopStub *loops;         // This pointer is valid for properties on surfaces.
  AppliesToSurface howApplies;           // Valid only for properties on surfaces.
  AttachmentPoint attachedTo;
  RESCUEBOOL triangulatedSurface;
  RescueIJSurface *ijSurface;
  RESCUEBOOL isLocked;
  RescueContext *context;

  RescueArray *data; 
  RESCUEINT64 propertyVersion;
  RESCUEINT64 geometryId;
  RESCUEINT64 ijSurfaceId;

  RescueColorTable *colorTable;
  friend class cSetRescueProperty;
  friend class RescueBlockUnit;
  friend class RescueGeobodyPart;
  friend class RescueSurface;
  friend class RescueGeometry;
  friend class RescueIJSurface;
};

#endif




