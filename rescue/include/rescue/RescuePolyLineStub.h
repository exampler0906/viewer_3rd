/********************************************************************

  RescuePolyLineStub.h

  A RescuePolyLine object that has been lazily relinked.
  
  You can preview the object here and trade it for a real one
  later.

  Rod Hanks,  March 2001

*********************************************************************/
#ifndef RescuePolyLineStub_H
#define RescuePolyLineStub_H

#include "myHeaders.h"
#include "RescueWireframeStub.h"
class RescuePolyLine;

class RescuePolyLineStub:public RescueWireframeStub
{
public:
  virtual ~RescuePolyLineStub() {}
/******************************************************************

  These methods let you find out if the polyline is equal to
  another polyline, whether you have the polyline stub or the
  actual polyline.  Unlike polylines, you can't find out if two
  stubs are the same object by comparing the pointers.

******************************************************************/
  RESCUEBOOL Equals(RescuePolyLineStub *other);
  RESCUEBOOL Equals(RescuePolyLine *other);
/*****************************************************************

  This method returns the real object that the stub represents,
  first loading it into memory if necessary.  It returns 0 if
  for some reason the real object is not available.  If you pass
  false for loadIfNeeded this may simply mean that the object you
  want is not loaded.  If you pass true, usually it would 
  mean that the object represented by the stub is no longer a
  member of the model.

****************************************************************/
  RescuePolyLine *PolyLine(RescueModel *model, RESCUEBOOL loadIfNeeded=TRUE);
/*****************************************************************

    Normal type-testing method.

*****************************************************************/
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  RescuePolyLineStub(RescueContext *context, FILE *archiveFile);
  RescuePolyLineStub(RescueContext *context, RESCUEINT64 wireframeIdIn, RESCUEINT64 objectIdIn);
  RescuePolyLineStub(RescueContext *context, RescuePolyLine *lineIn);
/*
  The object is never instantiated by the user.  The class library instantiates
  it on loading when a relationship to one of the Wireframe objects is read 
  off disk.  When the user wants to, they trade the stub for the real version.
*/
  RescuePolyLine *actualLine;

  friend class cSetRescuePolyLineStub;
  friend class RescuePolyLine;
  friend class RescueTrimVertex;
  friend class RescueTrimEdge;
  friend class cSetRescueWireframe;
};

#endif




