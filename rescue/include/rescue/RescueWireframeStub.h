/********************************************************************

  RescueWireframeStub.h

  A RescuePolyLine, or RescueTrimVertex
  object that has been lazily relinked.
  
  You can preview the object here and trade it for a real one
  later.

  Rod Hanks,  March 2001

*********************************************************************/
#ifndef RescueWireframeStub_H
#define RescueWireframeStub_H

#include "myHeaders.h"
#include "RescueObject.h"
class RescuePolyLine;
class RescueTrimVertex;
class RescuePolyLineNode;
class RescueFaultIntersection;
class RescueModel;
class RescueWireframe;

class RescueWireframeStub:public RescueObject
{
public:
  virtual ~RescueWireframeStub() {}
/******************************************************************

  These methods let you preview the stub. 

******************************************************************/
  RESCUEINT64 WireframeId() {return wireframeId;}
  RESCUEINT64 ObjectId() {return objectId;}
  RescueWireframe *Wireframe(RescueModel *model);
/*************************************************************

  This returns the identifier of the real object, even if the real 
  object is currently stubbed.

***************************************************************/
  virtual RESCUEINT64 BestIdentifier() {return objectId;}
/*****************************************************************

  These methods return the real object that the stub represents,
  first loading it into memory if necessary.  They return 0 if
  either (1) you ask for the wrong method (call PolyLine when
  StubFor() == R_RescueTrimVertex) or (2) for some reason the real
  object is not available (usually would mean that the file that 
  contained it has gone missing or is corrupt).

****************************************************************/
/*****************************************************************

    Normal type-testing method.

*****************************************************************/
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile) {ArchiveStub(context, archiveFile);}
  virtual void ArchiveStub(RescueContext *context, FILE *archiveFile);
  RescueWireframeStub(RescueContext *context, FILE *archiveFile);
  RescueWireframeStub(RescueContext *context, RESCUEINT64 wireframeIdIn, RESCUEINT64 objectIdIn);
  RescueWireframeStub(RescueContext *context, RescueWireframe *wireframeIn, RESCUEINT64 objectIdIn);
  void SetWireframe(RESCUEINT64 wireframeIdIn) {wireframeId = wireframeIdIn;}
  void SetWireframe(RescueWireframe *wireframeIn);
/*
  The object is never instantiated by the user.  The class library instantiates
  it on loading when a relationship to one of the Wireframe objects is read 
  off disk.  When the user wants to, they trade the stub for the real version.
*/
  RESCUEINT64 wireframeId;
  RESCUEINT64 objectId;
  RESCUEINT64 loadNo;
  RescueWireframe *wireframeObj;

  friend class cSetRescueTrimLoopStub;
  friend class cSetRescueEdgeSetStub;
  friend class cSetRescueWireframe;
};

#endif




