/****************************************************************************

Copyright 1995 Petrotechnical Open Software Corporation

POSC grants permission to copy or reproduce this material in its original
form for internal use only.

This software is subject to the provision of the "POSC Software License
Agreement" which states in part:

1) Licensee accepts a non-exclusive, non-transferable, license  to use,
display, modify and distribute works derived from the licensed documentation
and Software Product.

2) Licensee shall have no right to distribute in its original form any
Software Product or documentation licensed under this agreement.

****************************************************************************/
/*************************************************************************

        cSetRescueWireframe.h

	Keeps a list of pointers to some RescueWireframe.

        Rod Hanks               January 18th, 1995	 /  August 1996

****************************************************************************/

#ifndef cSetRescueWireframe_H
#define cSetRescueWireframe_H

#include "boolSupport.h"
#include <stdlib.h>

class RescueWireframe;
class RescueContext;
class RescueWireframeStub;
class RescueTrimVertexStub;

class cSetRescueWireframe
{
  struct Triplet
  {
    RescueObject *wireframeObj;
    RescueObject *userObj;
    RescueWireframeStub *stub;
  };
protected:
  Triplet **savedCompatible;
  RESCUEINT64 compatibleAllocated;
  RESCUEINT64 compatibleCount;

  RescueWireframe **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueWireframe();
  ~cSetRescueWireframe();
  void operator+=(RescueWireframe *newObject);
  RESCUEBOOL operator-=(RescueWireframe *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueWireframe *NthObject(RESCUEINT64 ordinal);
  RescueWireframe *ObjectNamed(RESCUECHAR *nameIn);
  RescueWireframe *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueWireframe *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void UnloadWireframe();
  void CopyWireframeData(RESCUECHAR *oldPathName);
  void DropWireframeMemory();
  void UpdateWireframeData();
  void Relink(RescueObject *parent);
  RESCUEBOOL AnyFileTruncated();

private:
  void ArchiveCompatiblePolyLines(RescueContext *context, FILE *archiveFile);
  void ArchiveCompatibleTrimVertexes(RescueContext *context, FILE *archiveFile);
  void UnArchiveCompatiblePolyLines(RescueContext *context, FILE *archiveFile);
  void UnArchiveCompatibleTrimVertexes(RescueContext *context, FILE *archiveFile);
  void FindWireframeForCompatibles();
  void SaveCompatibleEdgeSet(RescueEdgeSet *set, RescueObject *user, RescueWireframeStub *stub);
  void SaveCompatibleTrimLoop(RescueTrimLoop *loop, RescueObject *user, RescueWireframeStub *stub);
  void Relinquish(RescueWireframe *existingObject);
  void SaveTriplet(Triplet *toSave);
  void ExtendFromWireframe(RescueWireframe *wireframe, RescueTrimVertexStub *stub);
  void ExtendFromWireframe(RescueWireframe *wireframe, RescuePolyLine *line);
  void ExtendFromWireframe(RescueWireframe *wireframe, RescueTrimEdge *edge);
  void ExtendFromWireframe(RescueWireframe *wireframe, RescueTrimLoop *loop);
  void ExtendFromWireframe(RescueWireframe *wireframe, cSetRescueTrimLoop *loopSet);
  void ExtendFromWireframe(RescueWireframe *wireframe, RescueEdgeSet *edges);
  void CopyFromVertex(RescuePolyLine *line);
  void RadiateFrom(RescueTrimVertex *vertex);

  cSetRescuePolyLine *oldPolyLines;
  cSetRescueTrimVertex *oldTrimVertexes;

  friend class RescueWireframe;
  friend class RescueModel;
  friend class RescueGeometry;
  friend class RescueSurface;
  friend class RescueBlockUnitSide;
  friend class RescueGeobodySurface;
  friend class RescueGeobodyVolume;
  friend class RescueMacroVolume;
  friend class RescueProperty;
};

#endif



