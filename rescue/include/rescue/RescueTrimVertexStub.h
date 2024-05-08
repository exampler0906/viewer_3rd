/********************************************************************

  RescueTrimVertexStub.h

  A RescueTrimVertex object that has been lazily relinked.
  
  You can preview the object here and trade it for a real one
  later.

  Rod Hanks,  March 2001

*********************************************************************/
#ifndef RescueTrimVertexStub_H
#define RescueTrimVertexStub_H

#include "myHeaders.h"
#include "RescueWireframeStub.h"
class RescuePolyLine;

class RescueTrimVertexStub:public RescueWireframeStub
{
public:
  virtual ~RescueTrimVertexStub() {}
/******************************************************************

  These methods let you find out if the polyline is equal to
  another polyline, whether you have the polyline stub or the
  actual polyline.  Unlike polylines, you can't find out if two
  stubs are the same object by comparing the pointers.

******************************************************************/
  RESCUEBOOL Equals(RescueTrimVertexStub *other);
  RESCUEBOOL Equals(RescueTrimVertex *other);
/*****************************************************************

  This method returns the real object that the stub represents,
  first loading it into memory if necessary.  It returns 0 if
  for some reason the real object is not available.  If you pass
  false for loadIfNeeded this may simply mean that the object you
  want is not loaded.  If you pass true, usually it would 
  mean that the object represented by the stub is no longer a
  member of the model.

****************************************************************/
  RescueTrimVertex *TrimVertex(RescueModel *model, RESCUEBOOL loadIfNeeded=TRUE);
/*****************************************************************

    Normal type-testing method.

*****************************************************************/
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  RescueTrimVertexStub(RescueContext *context, FILE *archiveFile);
  RescueTrimVertexStub(RescueContext *context, RESCUEINT64 wireframeIdIn, RESCUEINT64 objectIdIn);
  RescueTrimVertexStub(RescueContext *context, RescueTrimVertexStub *copyStub);
  RescueTrimVertexStub(RescueTrimVertex *actualVertexIn);
/*
  The object is never instantiated by the user.  The class library instantiates
  it on loading when a relationship to one of the Wireframe objects is read 
  off disk.  When the user wants to, they trade the stub for the real version.
*/
  void CopyFrom(RescueTrimVertexStub *other);

  RescueTrimVertex *actualVertex;

  friend class RescuePolyLine;
  friend class RescueTrimEdge;
  friend class cSetRescueWireframe;
};

#endif




