/********************************************************************

  RescueSurface.h

  A surface is a business object that may have a set of representations.

  It may have an alternate triangulated surface representation thru
  a 1-1 relationship to RescueTriangulatedSurface.

  Rod Hanks,  May 1996 / July 1999 / December 1999

*********************************************************************/
#ifndef RESCUESURFACE_H
#define RESCUESURFACE_H

#include "myHeaders.h"
#include "RescueWireframeOwner.h"
#include "cSetRescueProperty.h"
#include "cSetRescuePropertyGroup.h"
#include "cSetRescueIJSurface.h"
#include "RescueCoordinateSystem.h"
class RescueCoordinateSystemAxis;
class RescueSurfaceCell;
class RescueGeometry;
class RescueEdgeSetStub;
class RescueEdgeSet;
class RescueColor;
class RescueTriangulatedSurface;
class cSetRescueTriangleVertex;
class cSetRescueTriangleFace;
class cSetRescueDataContainer;
class RescueOrientationLedger;

class RescueSurface:public RescueWireframeOwner
{
public:
  typedef enum {AUXILLIARY, FAULT, UNCONFORMITY, LEASE_BOUNDARY, HORIZON,
                OIL_CONTACT, GAS_CONTACT, WATER_CONTACT, SALT_DOME} SurfaceType;
  RescueSurface(RescueModel *modelIn,
                RescueCoordinateSystem::Orientation orientation,
                RescueCoordinateSystemAxis *i_axis,
                RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                RescueCoordinateSystemAxis *j_axis,
                RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                RESCUEFLOAT missingValue, 
                SurfaceType type);
  RescueSurface(RescueModel *modelIn,
                RescueCoordinateSystem::Orientation orientation,
                RescueCoordinateSystemAxis *i_axis,
                RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                RescueCoordinateSystemAxis *j_axis,
                RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                RESCUEFLOAT missingValue, 
                RESCUEFLOAT *values,
                SurfaceType type);
          // Creates a new surface with regular x/y geometry.
          // If passed, the values are applied to the Z axis.
  RescueSurface(RescueModel *modelIn,
                RescueCoordinateSystem::Orientation orientation,
                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                RESCUEFLOAT missingValue,
                SurfaceType type);
  RescueSurface(RescueModel *modelIn,
                RescueCoordinateSystem::Orientation orientation,
                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                RESCUEFLOAT missingValue, 
                RESCUEFLOAT *tripletArray,
                SurfaceType type);
          // Creates a new parametric surface.
/****************************************************************************************************

    The stub method lets you find out if you are stepping into a part of the model
    that has not been loaded.  From the stub you can find the
    RescueWireframe involved in the node, and you can find out if that node is
    loaded.

    This method will return zero if RescueModel::LoadWireframe() has not been called.

*************************************************************************************************/
  RescueEdgeSetStub *EdgesObj();
/*********************************************************************************************

    This method will automatically load the wireframe if the part you need for
    the edges is not yet loaded.

    This method will return zero if RescueModel::LoadWireframe() has not been called.

**********************************************************************************************/
  RescueEdgeSet *Edges();

  RESCUEBOOL AnyFileTruncated();            // Checks all subfiles in the instantiated model.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  virtual ~RescueSurface();
  SurfaceType Type() {return type;}

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
  RESCUEINT64 PropertyCount64() {return properties->Count64();}
  RESCUEINT32 PropertyCount() {return properties->Count();}
  RescueProperty *NthRescueProperty(RESCUEINT64 zeroBasedOrdinal) 
                  {return properties->NthObject(zeroBasedOrdinal);}
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 identifier) 
                  {return properties->ObjectIdentifiedBy(identifier);}
  RescueProperty *PropertyNamed(RESCUECHAR *name) {return properties->ObjectNamed(name);}
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescueProperty(RescueProperty *unitToDrop); 
                                   // The property is automatically dropped from
                                   // any RescueTimeStepGroups of which it was a
                                   // member, and any application pointers to it
                                   // become invalid. 
  RESCUEINT64 IJSurfaceCount64() {return ijSurfaces->Count64();}
  RESCUEINT32 IJSurfaceCount() {return ijSurfaces->Count();}
  RescueIJSurface *NthIJSurface(RESCUEINT64 zeroBasedOrdinal)
                  {return ijSurfaces->NthObject(zeroBasedOrdinal);}
  RescueIJSurface *SurfaceIJIdentifiedBy(RESCUEINT64 identifier)
                  {return ijSurfaces->ObjectIdentifiedBy(identifier);}
  RescueTriangulatedSurface *SurfaceTriangulatedIdentifiedBy(RESCUEINT64 identifier);
  RESCUEBOOL DropIJSurface(RescueIJSurface *toDrop);
                                    // Any properties on this surface are automatically dropped.
                                    // Won't drop the final IJSurface
                                    // (there must always be one).
  RescueModel *ParentModel() {return parentModel;}
  RESCUEINT64  CountOfPropertyGroup64() {return (*groups).Count64();}
  RESCUEINT32  CountOfPropertyGroup() {return (*groups).Count();}
  void AddPropertyGroup(RescuePropertyGroup *existingPropertyGroup)
              {(*groups) += existingPropertyGroup;} 
  RESCUEBOOL DeletePropertyGroup(RescuePropertyGroup *group);
                                   // The group is automatically dropped from
                                   // any RescueModelPropertyGroups of which it was a
                                   // member, and any application pointers to it
                                   // become invalid.  However, the RescueProperties
                                   // which it contained are unaffected.
  RescuePropertyGroup *NthPropertyGroup(RESCUEINT64 zeroBasedOrdinal)
  {return (RescuePropertyGroup *) (*groups).NthObject(zeroBasedOrdinal);}

  RescueTriangulatedSurface *CreateTriangulatedSurface(cSetRescueTriangleVertex *verticesIn,
                                                       cSetRescueTriangleFace *facesIn);
  RescueTriangulatedSurface *CreateTriangulatedSurface(RESCUEINT64 vertexCount,
                                                       RESCUEFLOAT **coordinates,
                                                       RESCUEINT64 faceCount,
                                                       RESCUEINT64 **faces);
  RescueTriangulatedSurface *CreateTriangulatedSurface(RESCUEINT64 vertexCount,
                                                       RESCUEFLOAT *coordinates,
                                                       RESCUEINT64 faceCount,
                                                       RESCUEINT64 *faces);
  RescueTriangulatedSurface *CreateTriangulatedSurface(RESCUEINT32 vertexCount,
                                                       RESCUEFLOAT **coordinates,
                                                       RESCUEINT32 faceCount,
                                                       RESCUEINT32 **faces);
  RescueTriangulatedSurface *CreateTriangulatedSurface(RESCUEINT32 vertexCount,
                                                       RESCUEFLOAT *coordinates,
                                                       RESCUEINT32 faceCount,
                                                       RESCUEINT32 *faces);
  RescueTriangulatedSurface *TriangulatedSurface() {return triangulatedSurface;}
/****************************************************************************************

    Methods dealing with RescueDataContainers.

*******************************************************************************************/
  cSetRescueDataContainer *DataContainers();
                             // Will return 0 if properties have not
                             // been defined.
                             // DO NOT delete the class returned.
  cSetRescueDataContainer *DemandDataContainers();
                             // May return an empty container, but
                             // will never return 0.
                             // DO NOT delete the class returned.
/*******************************************************************************************/
  void FindUniquePropertyNames(cSetString *container);
protected:
  RescueSurface(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentModel);
private:
  void Dispose(); /* Call surfaceGeometry->RescueDeleteFile() for all subfiles */
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);
  void AutoEdgeSet();
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RescueModel *parentModel;
  RescueEdgeSetStub *edges;          
  SurfaceType type;
  RescueColor *color;
  cSetRescueProperty *properties;
  cSetRescuePropertyGroup *groups;
  RescueTriangulatedSurface *triangulatedSurface;
  cSetRescueIJSurface *ijSurfaces;

  cSetRescueDataContainer *propertyContainers;
  RESCUEINT64 propertyContainerId;

  friend class RescueBlockUnitHorizonSurface;
  friend class RescueSection;
  friend class RescueSurfaceCell;
  friend class RescueWellboreSurface;
  friend class RescueModel;
  friend class RescuePolyLine;
  friend class RescueGrid;
  friend class cSetRescueWellboreSurface;
  friend class RescueMacroVolume;
  friend class cSetRescueSurfaceCell;
  friend class cSetRescueBlockUnitHorizonSurface;
  friend class cSetRescueSection;
  friend class cSetRescueReferenceSurface;
  friend class RescueSurfaceToGrid;
  friend class RescueProperty;
  friend class RescuePropertyGroup;
  friend class RescueIJSurface;
  friend class RescueHorizon;
  friend class RescueTimeStepManager;
};

#endif





