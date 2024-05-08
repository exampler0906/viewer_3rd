/********************************************************************

  RescueModel.h

  The main object for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEMODEL_H
#define RESCUEMODEL_H

#include "myHeaders.h"

#include "RCHString.h"
#include "RescueUnit.h"
#include "RescueBlock.h"
#include "RescueHorizon.h"
#include "RescueWellbore.h"
#include "RescueSection.h"
#include "cSetRescueUnit.h"
#include "cSetRescueBlock.h"
#include "cSetRescueHorizon.h"
#include "cSetRescueWellbore.h"
#include "cSetRescueSection.h"
#include "cSetRescuePolyLine.h"
#include "cSetRescueTrimVertex.h"
#include "cSetRescueReferenceSurface.h"
#include "cSetRescueLookup.h"
#include "RescueProgressReporter.h"
#include "cSetString.h"
#include "cSetRescueModelPropertyGroup.h"
#include "cSetRescueHistory.h"
#include "cSetRescueGeobody.h"
#include "RescueHistoryObject.h"
#include "RescueEventDescr.h"
#include "cSetRescueEventDescr.h"
#include "cSetRescueFaultIntersection.h"
#include "cSetRescueReservoir.h"
#include "cSetRescueWireframe.h"
#include "cSetRescuePropertyGroup.h"
#include "RescueDocumentList.h"

class RescueCoordinateSystem;
class cNameValuePair;
class RescueColorTableList;
class RescueIdTree;
class RescueWireframeCallBack;
class RescueContext;
class RescueLogicalOrder;
class RescueGeobodyVolume;
class RescueGeobodySurface;

#define FILE_SUBVERSION 7
#define FILE_VERSION 37
// Note you cannot use version 70, 80, or 81.  These
// correspond to 'F', 'P' or 'R', the first letter of ascii files.
// version 8 - cNameValuePair
// version 9 - RescueEdgeSet added to RescueSurface - An ILAB release and first commercial products.
// version 10 - SectionType becomes SurfaceType
// version 11 - New property grouping scenario.
// version 12 - Properties are in separate files. - An ILAB release.
// superstitous skipping of model 13.
// version 14 - RescueTripletArray, RescueGeometry, and RescueTrimVertexes and their
// ilk all moved RESCUEINTo separate files.
// version 15 - Added colors to RescueGeometry and RescueSurface.
// version 16 - Compression of RESCUEFLOAT and RESCUEDOUBLE arrays.
// version 17 - KLayer edges in Wireframe files.
// version 18 - Multiple RescueGeometries per RescueBlockUnit.
// version 19 - No physical file differences.  This is basis for next commercial release.
// version 20 - RescueColorTable, RescueHistory, etc. 
// version 21 - Property locking, face or node-centered properties, single block unit color.
// version 22 - RescueColor moved from RescueGeometry to RescueBlockUnit and RescueGeobodyPart.
// version 23 - New triangulated surface code, geometry of truncated cells,  different
//              resolutions for surface properties, oct trees, classification of
//              RescueTrimLoops.
// version 24 - RescueUncoformity and RescueEvent, RescueFaultIntersection.
// version 25 - RescueUnconformity gets a name, RescueUnit gets unconformities above and below,
//              RescueModel gets a global rotation.
// version 26 - RescueUnconformity may have null RescueEvents.
// version 27 - RescuePolyLineNodeAvatar.
// version 28 - RescueWireframe.
// version 29 - Boxes on RescueWireframe and some other minor changes.
// version 30 - RescueDiapir, RescueLogicalOrder, flavors.
// version 32 - Removed RescuePolyLineNodeAvatar and rotation.
// version 33 - RescueIJKCellPair change, LGR.
// version 34 - RescuePillar and associated classes.
// version 35 - RescuePillar with split nodes.
// version 36 - RescueGeometry x,y,z weight arrays went to RESCUEDOUBLE.
// version 37 - Introduced self-descriptive areas in many parts of the file.
class RescueModel:public RescueHistoryObject
{
public:
  RescueWireframeCallBack *RegisterWireframeCallBack(RescueWireframeCallBack *newCallBackObject);
                                       // Will inform this object each time a RescueWireframe loads.
  RESCUEBOOL AnyFileTruncated();      // Checks all subfiles in the instantiated model.
  void Commit();                      // Deletes all automatically created bak files for this model,
                                      // deletes files scheduled for deletion, emptys the list
                                      // of created files.
  void Rollback();                    // Returns to any existing bak files for this model,
                                      // emptys the list of deleted files (saving them from deletion),
                                      // deletes created files.  Delete your poRESCUEINTer to the model
                                      // and reacquire it after this.
  static RescueModel *UnarchiveModel(RescueContext *context, RESCUECHAR *pathName);        
                                      // Create an instance from an  
                                      // exchange file.  Rescue determines
                                      // the file format by examining the file itself.
  RESCUEBOOL ArchiveModel(RESCUECHAR *pathName, RESCUEBOOL binary = FALSE, RESCUEINT32 version = FILE_VERSION, RESCUEBOOL write32 = true);  
                                      // Write an exchange file from an instance.  
                                      // Normally used to create a new model. Applications
                                      // can pass 9, >= 19 for file version, which
                                      // will cause an older file format to be
                                      // written.  There is a possible data loss.  Other
                                      // values are not supported. If the model is an
                                      // existing model whose file version is being changed
                                      // all files which are part of the model will be
                                      // read and rewritten.  This is also true for an
                                      // existing model whose name is being changed.
                                      // write32 is true to write RESCUEINT64 and RESCUEUINT64 datatypes
                                      // as RESCUEINT32 and RESCUEUINT32.  This should be done for
                                      // all versions prior to v37, and is best done anytime unless
                                      // there is a chance your model requires 64 bits for ids and indexes.
  RESCUEBOOL ArchiveModel();                // Used to update a model which was previously
                                      // unarchived.  Will return FALSE if the model is a
                                      // new one. If the model was an older version it will
                                      // be updated to the new version, and all files which
                                      // are part of the model will be read and re-written.
  RESCUEBOOL ExistingModel() {return currentPathName != 0;}
                                      // Returns TRUE if the model was Unarchived (and therefore
                                      // can be updated using the argumentless form of ArchiveModel).
  RescueModel(RescueContext *context, RESCUECHAR *modelNameIn);     // Create an empty model.
  RescueModel(RESCUECHAR *modelNameIn, RescueCoordinateSystem *coordinateSystemIn);     
  virtual ~RescueModel();                     // Drop existing model (will drop all
                                      // associated class instances).

  RCHString *ModelName() {return modelMoniker;}
                                    // Do NOT drop the object returned.
  void SetWriter(const RESCUECHAR *vendorName, const RESCUECHAR *vendorVersion, 
                                         const RESCUECHAR *modelDate, const RESCUECHAR *userName);
  RCHString *VendorName();          // Delete the returned object when thru for these 4.
  RCHString *VendorVersion();
  RCHString *ModelDate();
  RCHString *UserName();

  void SetIJKPreference(RescueCoordinateSystem::Orientation preferredOrientation);
  RESCUECHAR *IJKPreference();                              // Returns NULL if none was defined.
                                                            // Delete the returned object.
  RescueCoordinateSystem::Orientation IJKPreferenceEnum();  // Throws an exception if none was defined.

  RESCUEINT64 UnitCount64() {return units->Count64();}
  RESCUEINT64 BlockCount64() {return blocks->Count64();}
  RESCUEINT64 HorizonCount64() {return horizons->Count64();}
  RESCUEINT64 WellboreCount64() {return wellbores->Count64();}
  RESCUEINT64 SectionCount64() {return sections->Count64();}
  RESCUEINT64 PropertyGroupCount64() {return propertyGroup->Count64();}
  RESCUEINT64 HistoryCount64() {return history->Count64();}
  RESCUEINT64 GeobodyCount64() {return geoBodies->Count64();}
  RESCUEINT64 ReferenceSurfaceCount64() {return referenceSurfaces->Count64();}
  RESCUEINT64 LookupCount64() {return lookups->Count64();}
  RESCUEINT64 EventDescrCount64() {return eventDescr->Count64();}
  RESCUEINT64 FaultIntersectionCount64() {return faultIntersections->Count64();}
  RESCUEINT64 ReservoirCount64() {return reservoirs->Count64();}
  RESCUEINT64 WireframeCount64() {return wireframes->Count64();}

  RESCUEINT32 UnitCount() {return units->Count();}
  RESCUEINT32 BlockCount() {return blocks->Count();}
  RESCUEINT32 HorizonCount() {return horizons->Count();}
  RESCUEINT32 WellboreCount() {return wellbores->Count();}
  RESCUEINT32 SectionCount() {return sections->Count();}
  RESCUEINT32 PropertyGroupCount() {return propertyGroup->Count();}
  RESCUEINT32 HistoryCount() {return history->Count();}
  RESCUEINT32 GeobodyCount() {return geoBodies->Count();}
  RESCUEINT32 ReferenceSurfaceCount() {return referenceSurfaces->Count();}
  RESCUEINT32 LookupCount() {return lookups->Count();}
  RESCUEINT32 EventDescrCount() {return eventDescr->Count();}
  RESCUEINT32 FaultIntersectionCount() {return faultIntersections->Count();}
  RESCUEINT32 ReservoirCount() {return reservoirs->Count();}
  RESCUEINT32 WireframeCount() {return wireframes->Count();}

  RESCUEINT32 UnitCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(units->Count64(), throwIfTooBig);}
  RESCUEINT32 BlockCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(blocks->Count64(), throwIfTooBig);}
  RESCUEINT32 HorizonCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(horizons->Count64(), throwIfTooBig);}
  RESCUEINT32 WellboreCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(wellbores->Count64(), throwIfTooBig);}
  RESCUEINT32 SectionCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(sections->Count64(), throwIfTooBig);}
  RESCUEINT32 PropertyGroupCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(propertyGroup->Count64(), throwIfTooBig);}
  RESCUEINT32 HistoryCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(history->Count64(), throwIfTooBig);}
  RESCUEINT32 GeobodyCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(geoBodies->Count64(), throwIfTooBig);}
  RESCUEINT32 ReferenceSurfaceCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(referenceSurfaces->Count64(), throwIfTooBig);}
  RESCUEINT32 LookupCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(lookups->Count64(), throwIfTooBig);}
  RESCUEINT32 EventDescrCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(eventDescr->Count64(), throwIfTooBig);}
  RESCUEINT32 FaultIntersectionCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(faultIntersections->Count64(), throwIfTooBig);}
  RESCUEINT32 ReservoirCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(reservoirs->Count64(), throwIfTooBig);}
  RESCUEINT32 WireframeCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(wireframes->Count64(), throwIfTooBig);}

  RescueEventDescr *MakeUnconformity(RESCUECHAR *name = 0);
  RescueEventDescr *MakeDiapir(RESCUECHAR *name = 0);

  RescueUnit *NthRescueUnit(RESCUEINT64 zeroBasedOrdinal) {return units->NthObject(zeroBasedOrdinal);}
  RescueBlock *NthRescueBlock(RESCUEINT64 zeroBasedOrdinal) {return blocks->NthObject(zeroBasedOrdinal);}
  RescueHorizon *NthRescueHorizon(RESCUEINT64 zeroBasedOrdinal) {return horizons->NthObject(zeroBasedOrdinal);}
  RescueWellbore *NthRescueWellbore(RESCUEINT64 zeroBasedOrdinal) {return wellbores->NthObject(zeroBasedOrdinal);}
  RescueSection *NthRescueSection(RESCUEINT64 zeroBasedOrdinal) {return sections->NthObject(zeroBasedOrdinal);}
  RescueReferenceSurface *NthRescueReferenceSurface(RESCUEINT64 zeroBasedOrdinal) {return referenceSurfaces->NthObject(zeroBasedOrdinal);}
  RescueModelPropertyGroup *NthRescueModelPropertyGroup(RESCUEINT64 zeroBasedOrdinal) {return propertyGroup->NthObject(zeroBasedOrdinal);}
  RescueHistory *NthRescueHistory(RESCUEINT64 zeroBasedOrdinal) {return history->NthObject(zeroBasedOrdinal);}
  RescueGeobody *NthRescueGeobody(RESCUEINT64 zeroBasedOrdinal) {return geoBodies->NthObject(zeroBasedOrdinal);}
  RescueLookup *NthRescueLookup(RESCUEINT64 zeroBasedOrdinal) {return lookups->NthObject(zeroBasedOrdinal);}
  RescueEventDescr *NthRescueEventDescr(RESCUEINT64 zeroBasedOrdinal) {return eventDescr->NthObject(zeroBasedOrdinal);}
  RescueFaultIntersection *NthRescueFaultIntersection(RESCUEINT64 zeroBasedOrdinal) {return faultIntersections->NthObject(zeroBasedOrdinal);}
  RescueReservoir *NthRescueReservoir(RESCUEINT64 zeroBasedOrdinal) {return reservoirs->NthObject(zeroBasedOrdinal);}
  RescueWireframe *NthRescueWireframe(RESCUEINT64 zeroBasedOrdinal) {return wireframes->NthObject(zeroBasedOrdinal);}
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.

  RESCUEBOOL DropRescueUnit(RescueUnit *unitToDrop) {return ((*units) -= unitToDrop);}
  RESCUEBOOL DropRescueBlock(RescueBlock *blockToDrop) {return ((*blocks) -= blockToDrop);}
  RESCUEBOOL DropRescueHorizon(RescueHorizon *horizonToDrop);
  RESCUEBOOL DropRescueWellbore(RescueWellbore *wellboreToDrop);
  RESCUEBOOL DropRescueSection(RescueSection *sectionToDrop);
  RESCUEBOOL DropRescueReferenceSurface(RescueReferenceSurface *surfaceToDrop);
  RESCUEBOOL DropRescueLookup(RescueLookup *lookupToDrop) {return ((*lookups) -= lookupToDrop);}
  RESCUEBOOL DropRescueModelPropertyGroup(RescueModelPropertyGroup *groupToDrop) {return ((*propertyGroup) -= groupToDrop);}
  RESCUEBOOL DropRescueHistory(RescueHistory *historyToDrop) {return ((*history) -= historyToDrop);}
  RESCUEBOOL DropRescueGeobody(RescueGeobody *bodyToDrop);
  RESCUEBOOL DropRescueEventDescr(RescueEventDescr *eventDescrToDrop);
  RESCUEBOOL DropRescueFaultIntersection(RescueFaultIntersection *RESCUEINTersectionToDrop);
  RESCUEBOOL DropRescueReservoir(RescueReservoir *reservoirToDrop);
  RESCUEBOOL DropRescueWireframe(RescueWireframe *wireframeToDrop);
                                    // Mustn't drop an owned object directly.
                                    // Use the owner's drop method instead.
                                    // These return FALSE if the object passed is
                                    // not a member of the set (and in that case the
                                    // object IS NOT dropped.
  RescueUnit *UnitNamed(RESCUECHAR *identifier) {return units->ObjectNamed(identifier);}
  RescueBlock *BlockNamed(RESCUECHAR *identifier) {return blocks->ObjectNamed(identifier);}
  RescueHorizon *HorizonNamed(RESCUECHAR *horizonName) {return horizons->ObjectNamed(horizonName);}
  RescueSection *SectionNamed(RESCUECHAR *sectionName) {return sections->ObjectNamed(sectionName);}
  RescueGeobody *GeobodyNamed(RESCUECHAR *bodyName) {return geoBodies->ObjectNamed(bodyName);}
  
  RescueUnit *UnitIdentifiedBy(RESCUEINT64 identifier) {return units->ObjectIdentifiedBy(identifier);}
  RescueBlock *BlockIdentifiedBy(RESCUEINT64 identifier) {return blocks->ObjectIdentifiedBy(identifier);}
  RescueHorizon *HorizonIdentifiedBy(RESCUEINT64 identifier) {return horizons->ObjectIdentifiedBy(identifier);}
  RescueWellbore *WellboreIdentifiedBy(RESCUEINT64 identifier) {return wellbores->ObjectIdentifiedBy(identifier);}
  RescueSection *SectionIdentifiedBy(RESCUEINT64 identifier) {return sections->ObjectIdentifiedBy(identifier);}
  RescueBlockUnitHorizonSurface *HorizonSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueBlockUnit *BlockUnitIdentifiedBy(RESCUEINT64 identifier);
  RescueReferenceSurface *ReferenceSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueLookup *LookupIdentifiedBy(RESCUEINT64 identifier) {return lookups->ObjectIdentifiedBy(identifier);}
  RescueGeobody *GeobodyIdentifiedBy(RESCUEINT64 identifier) {return geoBodies->ObjectIdentifiedBy(identifier);}
  RescueSurface *SurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueIJSurface *IJSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueIJSurface *HorizonIJSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueIJSurface *SectionIJSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueTriangulatedSurface *TriangulatedSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueTriangulatedSurface *HorizonTriangulatedSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueTriangulatedSurface *SectionTriangulatedSurfaceIdentifiedBy(RESCUEINT64 identifier);
  RescueGeobodyVolume *GeobodyVolumeIdentifiedBy(RESCUEINT64 identifier);
  RescueMacroVolume *MacroVolumeIdentifiedBy(RESCUEINT64 identifier);
  RescueBlockUnitSide *BlockUnitSideIdentifiedBy(RESCUEINT64 identifier);
  RescueGeobodySurface *GeobodySurfaceIdentifiedBy(RESCUEINT64 identifier);

  RescueProperty *GlobalPropertyIdentifiedBy(RESCUEINT64 identifer);

  cSetString *UniquePropertyNames();    // Returns a set of unique property names found in
                                        // the model.  Geometries, surfaces, and
                                        // Data containers may be loaded and
                                        // unloaded by this process.
                                        // Delete the object returned.
/*********************************************************************************

  If RescueModel::LoadWireframe() has been called, you can get the wireframe object
  and can discover certian things about it, such as its owner and if its file is
  truncated, even though the wireframe information within it is not loaded.

**********************************************************************************/
  RescueWireframe *WireframeIdentifiedBy(RESCUEINT64 identifier) {return wireframes->ObjectIdentifiedBy(identifier);}
  RescueHistory *HistoryIdentifiedBy(RESCUEINT64 identifier) {return history->ObjectIdentifiedBy(identifier);}
  RescueGeometry *GeometryIdentifiedBy(RESCUEINT64 identifier);
  RescueCoordinateSystem *CoordinateSystemIdentifiedBy(RESCUEINT64 identifier);
  RescueEventDescr *EventDescrIdentifiedBy(RESCUEINT64 identifier) {return eventDescr->ObjectIdentifiedBy(identifier);}
  RescueFaultIntersection *FaultIntersectionIdentifiedBy(RESCUEINT64 identifier) {return faultIntersections->ObjectIdentifiedBy(identifier);}
  RescueReservoir *ReservoirIdentifiedBy(RESCUEINT64 identifier) {return reservoirs->ObjectIdentifiedBy(identifier);}

	RescueTrimVertex *TrimVertexLocatedBy(RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
  RescuePolyLine *PolyLineBetween(RescueTrimVertex *end1, RescueTrimVertex *end2);
                                    // The above only work on loaded wireframe elements.  They
                                    // do not load unloaded elements.
  RescueLookup *LookupNamed(RESCUECHAR *name) {return lookups->ObjectNamed(name);}
  RescueModelPropertyGroup *PropertyGroupNamed(RESCUECHAR *name) {return propertyGroup->ObjectNamed(name);}
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RescueLogicalOrder *LogicalOrder(); // Returns an object that displays the logical ordering
                                      // of Units, Horizons, Unconformities, and Diapirs
                                      // in the model.
  RescueColorTableList *ColorTableList() {return colorTableList;}
                                    // Return an object used to keep track of color tables defined
                                    // for specific property types.

  RESCUEFLOAT Rotation() {return rotation;}
  void SetRotation(RESCUEFLOAT rotationIn) {rotation = rotationIn;}
/***********************************************************************************

  WITSML

***********************************************************************************/
  RescueDocumentList *Documents();
  bool WriteWITSML(const RESCUECHAR *pathName); // Writes XML for trajectories and logs.
  bool ReadWITSML(const RESCUECHAR *pathName, RescueProgressReporter *loggingObject = 0);  
                                                // Reads XML for same.  Any errors are
                                                // written to the loggingObject with
                                                // a prefix of "ERROR:".  Informational
                                                // messages go there too.
/***********************************************************************************

  The next five methods have to do with loading and unloading the wireframe model
  separately.

***********************************************************************************/
  RESCUEBOOL IsWireframeLoaded() {return wireframeLoaded;}
  RESCUEBOOL LoadWireframe();
  RESCUEBOOL UnloadWireframe();
  RESCUEBOOL WireframeHasChanged();
  void MarkWireframeChanged() {wireframeHasChanged = TRUE;}
  RESCUEBOOL WireframeFileTruncated();
/***********************************************************************************/

  RescueCoordinateSystem *CoordinateSystem() {return coordinateSystem;}
                                    // Do NOT delete the returned object.
  void SetCoordinateSystem(RescueCoordinateSystem *newCoordinateSystem)
                            {coordinateSystem = newCoordinateSystem;}
                                    // Coordinate systems are not considered owned objects.
  cNameValuePair *NameValuePairs() {return nameValuePairs;}
                                    // Interrogate the object returned to manipulate name/value pairs
                                    // belonging to this model.  DO NOT delete the object, it belongs
                                    // permanently to the model.
  RESCUEINT32 Version(RESCUEBOOL reload = FALSE);
  RESCUEINT32 WireframeVersion(RESCUEBOOL reload = FALSE);
                                    // These methods return a version number for the file which
                                    // starts at zero and increments each time the file is
                                    // written.  Applications can use this as a quick check to
                                    // see if the file has been updated (by saving the version
                                    // number AFTER a write operation). If reload is TRUE the library
                                    // always goes back to the disk to read the version number,
                                    // in case it has been recently changed.  Therefore, the
                                    // version number returned is the version which would be
                                    // available if the data were loaded now, not the version which
                                    // IS loaded now (if any). If false, the version number returned
                                    // is the version of the last data loaded (if any).
/****************************************************************************************

    Methods dealing with global grid geometries.

*******************************************************************************************/
  RescueGeometry *GridGeometry(RESCUEINT64 zeroBasedOrdinal = 0) {return gridGeometries->NthObject(zeroBasedOrdinal);}
                                    // May return null, even with ordinal = 0.
  RescueGeometry *GridGeometryIdentifiedBy(RESCUEINT64 identifier) {return gridGeometries->ObjectIdentifiedBy(identifier);}
  RESCUEINT64 GeometryCount64() {return gridGeometries->Count64();}
  RESCUEINT32 GeometryCount() {return gridGeometries->Count();}
  void AddGeometry(RescueGeometry *newGeometry) {(*gridGeometries) += newGeometry;}
  void DropGeometry(RescueGeometry *toDrop);
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 id);
/****************************************************************************************

    Methods dealing with grouping of properties on global grid geometries.

*******************************************************************************************/
  RESCUEINT64 RescuePropertyGroupCount64() {return localGroups->Count64();}
  RESCUEINT32 RescuePropertyGroupCount() {return localGroups->Count();}
  RescuePropertyGroup *NthRescuePropertyGroup(RESCUEINT64 zeroBasedOrdinal) 
                  {return localGroups->NthObject(zeroBasedOrdinal);}
  RescuePropertyGroup *PropertyGroupIdentifiedBy(RESCUEINT64 identifier) 
                  {return localGroups->ObjectIdentifiedBy(identifier);}
                                   // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescuePropertyGroup(RescuePropertyGroup *unitToDrop) 
                          {return ((*localGroups) -= unitToDrop);}

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
  RescueContext *Context() {return context;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
/****************************************************************************************

    Methods dealing with Orientation.

*******************************************************************************************/
  static int SetOrientation(RescueContext *context, 
                            char *modelFileName, 
                            RescueCoordinateSystem::Orientation orientation);
                                    // Model should not be open.  Model will be re-written as the 
                                    // new orientation.
private:
  RescueContext *Context(bool setContext);
  RescueModel(RescueContext *context, FILE *archiveFile);
  void RelinkNoArgs();
  RESCUEBOOL ArchiveModelPrimitive(RESCUECHAR *pathName, RESCUEBOOL binary);  
  void Archive(FILE *archiveFile);
  void UnArchive(FILE *archiveFile);
  void CommonInitialization(RescueContext *context, const RESCUECHAR *nameIn);
  void DeletePropertyGroup(RescuePropertyGroup *existingPropertyGroup);

  RESCUEBOOL WriteWireframeData();
  RESCUEBOOL ReadWireframeData(RESCUECHAR *pathName, RESCUEBOOL versionOnly = FALSE);
  void DropWireframeMemory();
  void UnArchiveWireframeData(FILE *archiveFile);
  void ArchiveWireframeData(FILE *archiveFile);
  void RelinkWireframeData();


  void RegisterObject(RescueObject *toRegister);
  void UnRegisterObject(RescueObject *toUnregister);

  void ScheduleDeleteFile(RESCUECHAR *fileName);
  void MakeBackupFile(RESCUECHAR *fileName);
  cSetString *ListBakFiles();

  RescueHistory *GetWriterHistory();
  RCHString *VendorSegment(const RESCUECHAR *beginKey, const RESCUECHAR *endKey);

  void LoadContext();
  void SaveContext();
  void Set32();
  void Set64();
  int SetOrientationPrimitive(RescueCoordinateSystem::Orientation orientation);
  void WriteEOFMarks(FILE *archiveFile);

  RCHString *modelMoniker;
  RescueCoordinateSystem *coordinateSystem;
  cSetRescueUnit *units;
  cSetRescueBlock *blocks;
  cSetRescueHorizon *horizons;
  cSetRescueWellbore *wellbores;
  cSetRescueSection *sections;
  cSetRescueWireframe *wireframes;
  cSetRescueReferenceSurface *referenceSurfaces;
  cSetRescueLookup *lookups;
  cNameValuePair *nameValuePairs;
  cSetRescueModelPropertyGroup *propertyGroup;
  cSetRescueHistory *history;
  cSetRescueGeobody *geoBodies;
  cSetRescueEventDescr *eventDescr;
  cSetRescueFaultIntersection *faultIntersections;
  cSetRescueReservoir *reservoirs;
  cSetRescueGeometry *gridGeometries;
  cSetRescuePropertyGroup *localGroups;

  RescueTree *registeredObjects;

  RescueLogicalOrder *logicalOrder;

  RESCUECHAR *currentPathName;
  RESCUECHAR *oldPathName;
  RESCUEBOOL currentBinary;
  RESCUEINT32 currentFileVersion;
  RESCUEINT32 desiredFileVersion;
  RESCUEINT32 mainFileVersion;
  RESCUEINT32 wireframeVersion;
  RESCUEINT32 readFileMainSoftwareVersion;    // These are the versions that wrote the software.
  RESCUEINT32 readFileSubSoftwareVersion;     // Valid only during unarchive operations.

  RescueColorTableList *colorTableList;

  RESCUEBOOL propertyActionImmediate;
  RESCUEBOOL geometryActionImmediate;
  RESCUEBOOL wireframeLoaded;
  RESCUEBOOL wireframeHasChanged;
  cSetString filesDeleted;
  cSetString filesCreated;
  RescueWireframeCallBack *wireframeCallBackObject;

  RescueContext *context;

  RESCUEFLOAT rotation;

  cSetRescueDataContainer *properties;
  RESCUEINT64 propertyContainerId;

  RescueDocumentList *documents;
  RESCUEINT64 documentListId;

  size_t uintSize;
  RESCUEBOOL uintSwap;
  size_t intSize;
  RESCUEBOOL intSwap;
  RESCUEBOOL write32;

  friend class RescueBlock;
  friend class RescueHorizon;
  friend class RescueUnit;
  friend class RescueWellbore;
  friend class RescueSection;
  friend class RescuePolyLine;
  friend class RescueTrimVertex;
  friend class RescueReferenceSurface;
  friend class RescueLookup;
  friend class RescueBlockUnit;
  friend class RescuePropertyGroup;
  friend class cSetRescueReferenceSurface;
  friend class cSetRescueSection;
  friend class RescueBlockUnitHorizonSurface;
  friend class cSetRescueTrimEdge;
  friend class cSetRescueTrimLoop;
  friend class cSetRescueEdgeSet;
  friend class cSetRescueLookup;
  friend class cSetRescueBlockUnitHorizonSurface;
  friend class cSetRescueHorizon;
  friend class cSetRescueWellboreSurface;
  friend class cSetRescueWellboreProperty;
  friend class cSetRescueWellboreSampling;
  friend class cSetRescueWellbore;
  friend class cSetRescueBlockUnitSide;
  friend class RescueMacroVolume;
  friend class cSetRescuePolyLine;
  friend class RescueModelPropertyGroup;
  friend class RescueArray;
  friend class RescueTripletArray;
  friend class RescueGeometry;
  friend class RescueArrayByte;
  friend class RescueArrayShort;
  friend class RescueArrayDouble;
  friend class RescueArrayFloat;
  friend class RescueArrayInt;
  friend class RescueCoordinateSystem;
  friend class RescueVertex;
  friend class RescueGrid;
  friend class RescueWellboreProperty;
  friend class RescueTimeStepGroup;
  friend class RescueProperty;
  friend class RescueHistory;
  friend class RescueColorTable;
  friend class RescueGeobody;
  friend class RescueGeobodyPart;
  friend class RescueSurface;
  friend class RescueBlockUnitSide;
  friend class RescueGeobodyVolume;
  friend class RescueTriangulatedSurface;
  friend class cSetRescueTriangleVertex;
  friend class cSetRescueTriangleFace;
  friend class RescueSOctTreeNode;
  friend class RescueEventDescr;
  friend class cSetRescueSOctTreeNode;
  friend class RescueFaultIntersection;
  friend class RescueTriangleVertex;
  friend class RescueWireframeStub;
  friend class RescueWireframe;
  friend class RescueGeobodySurface;
  friend class RescueReservoir;
  friend class RescueStairSteppedFault;
  friend class cSetRescueDataContainer;
  friend class RescueSurfaceToGrid;
  friend class RescueInterfaceSurfaceDesc;
  friend class RescueParametricLGRMap;
  friend class RescueTimeStepManager;
  friend class RescueDocumentList;
  friend class RescueDocument;
};

#endif





