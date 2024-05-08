/********************************************************************

  RescueWireframe.h

  The EdgeSet, TrimLoop, Polyline and Vertex objects.

  Rod Hanks,  March 2001

*********************************************************************/
#ifndef RescueWireframe_H
#define RescueWireframe_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RCHString.h"
#include "cSetRescuePolyLine.h"
#include "cSetRescueTrimVertex.h"
#include "cSetRescueEdgeSet.h"
#include "cSetRescueTrimLoop.h"
class RescueEdgeSet;
class RescueWireframeOwner;
class RescueModel;
class RescueOrientationLedger;

class RescueWireframe:public RescueHistoryObject
{
public:
/**********************************************************************************

  Functions that can be used when the wireframe is not loaded.

***********************************************************************************/
  ~RescueWireframe();
  //If the program attempts to add an object to a RescueWireframe that is not loaded, it
  //is automatically loaded first.

  RESCUEINT64 PolyLineCount64();                // When called before loading, these should be regarded
  RESCUEINT64 VertexCount64();                  // as an estimate.  After loading they are exact.
  RESCUEINT64 EdgeSetCount64();
  RESCUEINT64 TrimLoopCount64();                // Does not include RescueTrimLoop objects which
                                                // are part of RescueEdgeSet objects.  Only RescueTrimLoop
                                                // instances used directly, such as those in
                                                // RescueProperty and RescueFaultIntersection.
  RESCUEINT32 PolyLineCount() {return (RESCUEINT32) PolyLineCount64();}
  RESCUEINT32 VertexCount() {return (RESCUEINT32) VertexCount64();}
  RESCUEINT32 EdgeSetCount() {return (RESCUEINT32) EdgeSetCount64();}
  RESCUEINT32 TrimLoopCount() {return (RESCUEINT32) TrimLoopCount64();}

  RESCUEINT32 PolyLineCount(RESCUEBOOL throwIfTooBig); 
  RESCUEINT32 VertexCount(RESCUEBOOL throwIfTooBig);  
  RESCUEINT32 EdgeSetCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 TrimLoopCount(RESCUEBOOL throwIfTooBig);      

  RescueWireframeOwner *Owner() {return owner;} // Returns the RescueWireframeOwner
                                           // that this wireframe is associated with.
  RESCUEBOOL IsWireframeLoaded() {return wireframeLoaded;}
  RESCUEBOOL LoadWireframe();
  void DeleteWireframe();               // All wireframe objects will be deleted, but the RescueWireframe
                                        // itself is not deleted until the RescueModel file is written
                                        // out, so use the IsDeleted() method when traversing the
                                        // list of RescueWireframe instances.
  RESCUEBOOL IsDeleted() {return (RESCUEBOOL) isDeleted;}
  RESCUEBOOL WireframeFileTruncated();
  RescueModel *ParentModel() {return model;}
  RESCUEINT64 WireframeVersion(RESCUEBOOL reload = FALSE);
                                    // This methods return a version number for the file which
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
  RESCUEUINT64 WireframeFileSize();   
	RescueTrimVertex *TrimVertexLocatedBy(RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
  RescuePolyLine *PolyLineBetween(RescueTrimVertex *end1, RescueTrimVertex *end2);
                                    // These return null if the wireframe is not loaded or is deleted.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
/***********************************************************************************************

    Functions that should be called only after a wireframe is loaded.

***********************************************************************************************/

  RescuePolyLine *NthRescuePolyLine(RESCUEINT64 zeroBasedOrdinal) {return polyLines->NthObject(zeroBasedOrdinal);}
  RescueTrimVertex *NthRescueTrimVertex(RESCUEINT64 zeroBasedOrdinal) {return trimVertexes->NthObject(zeroBasedOrdinal);}
  RescueEdgeSet *NthRescueEdgeSet(RESCUEINT64 zeroBasedOrdinal) {return edgeSets->NthObject(zeroBasedOrdinal);}
  RescueTrimLoop *NthRescueTrimLoop(RESCUEINT64 zeroBasedOrdinal) {return trimLoops->NthObject(zeroBasedOrdinal);}

  RESCUEBOOL DropRescuePolyLine(RescuePolyLine *polyLineToDrop) {return ((*polyLines) -= polyLineToDrop);}
  RESCUEBOOL DropRescueTrimVertex(RescueTrimVertex *trimVertexToDrop) {return ((*trimVertexes) -= trimVertexToDrop);}
  RESCUEBOOL DropRescueEdgeSet(RescueEdgeSet *edgeSetToDrop) {return ((*edgeSets) -= edgeSetToDrop);}
  RESCUEBOOL DropRescueTrimLoop(RescueTrimLoop *trimLoopToDrop) {return ((*trimLoops) -= trimLoopToDrop);}

  RescuePolyLine *PolyLineIdentifiedBy(RESCUEINT64 identifier) {return polyLines->ObjectIdentifiedBy(identifier);}
  RescueTrimVertex *TrimVertexIdentifiedBy(RESCUEINT64 identifier) {return trimVertexes->ObjectIdentifiedBy(identifier);}
  RescueEdgeSet *EdgeSetIdentifiedBy(RESCUEINT64 identifier) {return edgeSets->ObjectIdentifiedBy(identifier);}
  RescueTrimLoop *TrimLoopIdentifiedBy(RESCUEINT64 identifier) {return trimLoops->ObjectIdentifiedBy(identifier);}

  RESCUEBOOL UnloadWireframe();
  RESCUEBOOL WireframeHasChanged() {return wireframeHasChanged;}
  RESCUEINT64 LoadNo() {return loadNo;}     // This number is incremented each time the wireframe is loaded
                                    // into memory during a session.
  void MarkWireframeChanged() {wireframeHasChanged = TRUE;}
/***************************************************************************************************

    The following bounding coordinates are as good as the last time the Wireframe object was
    unloaded.  They can be read after calling RescueModel::LoadWireFrame().  You don't have to
    load the individual RescueWireframe object to read these.

****************************************************************************************************/
  RESCUEFLOAT X1() {return x1;}                           // Minimum x coordinate.
  RESCUEFLOAT X2() {return x2;}                           // maximum x coordinate.
  RESCUEFLOAT X3() {return x3;}                           // Minimum x coordinate at y1 of 45-degree angle box.
  RESCUEFLOAT X4() {return x4;}                           // Maximum x coordinate at y1 of 45-degree angle box.
  RESCUEFLOAT Y1() {return y1;}                           // Minimum y coordinate.
  RESCUEFLOAT Y2() {return y2;}                           // Maximum y coordinate.
  RESCUEFLOAT Y3() {return y3;}                           // Minimum y coordinate at x1 of 45-degree angle box.
  RESCUEFLOAT Y4() {return y4;}                           // Maximum y coordinate at x1 of 45-degree angle box.
  RESCUEFLOAT Z1() {return z1;}                           // Minimum z coordinate.
  RESCUEFLOAT Z2() {return z2;}                           // Maximum z coordinate.
private:
  RescueWireframe(RescueModel *modelIn, RescueWireframeOwner *associatedBlockUnit);
  RescueWireframe(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parentModel);
  void Archive(FILE *archiveFile);
  RESCUEBOOL WriteWireframeData();
  RESCUEBOOL ReadWireframeData(RESCUECHAR *pathName, RESCUEBOOL versionOnly = FALSE);
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void ArchiveWireframeData(FILE *archiveFile);
  void UpdateWireframeData();
  void CopyWireframeData(RESCUECHAR *oldPathName);
  void CalculateBox(RESCUEBOOL &firstIteration, RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);

  void AddPolyLine(RescuePolyLine *toAdd);
  void AddTrimVertex(RescueTrimVertex *toAdd);
  void AddEdgeSet(RescueEdgeSet *toAdd);
  void AddTrimLoop(RescueTrimLoop *toAdd);

  void UnarchivePolyLines(FILE *archiveFile);
  void UnarchiveTrimVertexes(FILE *archiveFile);
  void SetOrientation(RescueOrientationLedger *ledger);

  RescueModel *model;
  RescueWireframeOwner *owner;
  cSetRescuePolyLine *polyLines;
  cSetRescueTrimVertex *trimVertexes;
  cSetRescueEdgeSet *edgeSets;
  cSetRescueTrimLoop *trimLoops;
  RESCUEINT64 wireframeVersion;
  RESCUEBOOL wireframeLoaded;
  RESCUEBOOL wireframeHasChanged;
  RESCUEINT64 loadNo;
  RESCUEINT64 isDeleted;                      // We don't actually remove the object until we unload
  RESCUEINT64 ownerIsA;                       // the wireframe, because we have lots of pointers to
  RESCUEINT64 ownerId;                        // it in the stubs.  Should not delete the zeroth wireframe
  RESCUEINT64 lastTrimVertexCount;            // if you intend to write earlier version files, because
  RESCUEINT64 lastPolyLineCount;              // we tend to use it as a catchall for compatibility
  RESCUEINT64 lastEdgeSetCount;               // purposes.
  RESCUEINT64 lastTrimLoopCount;

  RESCUEFLOAT x1;                           // Minimum x coordinate.
  RESCUEFLOAT x2;                           // maximum x coordinate.
  RESCUEFLOAT x3;                           // Minimum x coordinate at y1 of 45-degree angle box.
  RESCUEFLOAT x4;                           // Maximum x coordinate at y1 of 45-degree angle box.
  RESCUEFLOAT y1;                           // Minimum y coordinate.
  RESCUEFLOAT y2;                           // Maximum y coordinate.
  RESCUEFLOAT y3;                           // Minimum y coordinate at x1 of 45-degree angle box.
  RESCUEFLOAT y4;                           // Maximum y coordinate at x1 of 45-degree angle box.
  RESCUEFLOAT z1;                           // Minimum z coordinate.
  RESCUEFLOAT z2;                           // Maximum z coordinate.

  friend class RescuePolyLine;
  friend class RescueTrimVertex;
  friend class cSetRescueWireframe;
  friend class RescueTrimLoop;
  friend class RescueSurface;
  friend class RescueProperty;
  friend class RescueEdgeSet;
  friend class RescueMacroVolume;
  friend class RescueGeobodyVolume;
  friend class RescueGeobodySurface;
  friend class RescueBlockUnitSide;
  friend class RescueModel;
  friend class RescueWireframeOwner;
  friend class RescueBlockUnitHorizonSurface;
};

#endif




