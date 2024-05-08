/********************************************************************

  RescueTrimLoopStub.h

  A RescueTrimLoop object that has been lazily relinked.
  
  You can preview the object here and trade it for a real one
  later.

  Rod Hanks,  March 2001

*********************************************************************/
#ifndef RescueTrimLoopStub_H
#define RescueTrimLoopStub_H

#include "myHeaders.h"
#include "RescueWireframeStub.h"
class RescueTrimLoop;

class RescueTrimLoopStub:public RescueWireframeStub
{
public:
  virtual ~RescueTrimLoopStub() {}
/******************************************************************

  These methods let you find out if the polyline is equal to
  another polyline, whether you have the polyline stub or the
  actual polyline.  Unlike polylines, you can't find out if two
  stubs are the same object by comparing the pointers.

******************************************************************/
  RESCUEBOOL Equals(RescueTrimLoopStub *other);
  RESCUEBOOL Equals(RescueTrimLoop *other);
/*****************************************************************

  This method returns the real object that the stub represents,
  first loading it into memory if necessary.  It returns 0 if
  for some reason the real object is not available.  If you pass
  false for loadIfNeeded this may simply mean that the object you
  want is not loaded.  If you pass true, usually it would 
  mean that the object represented by the stub is no longer a
  member of the model.

****************************************************************/
  RescueTrimLoop *TrimLoop(RescueModel *model, RESCUEBOOL loadIfNeeded=TRUE);
/*****************************************************************

    Normal type-testing method.

*****************************************************************/
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  RescueTrimLoopStub(RescueContext *context, FILE *archiveFile);
  RescueTrimLoopStub(RescueContext *context, RESCUEINT64 wireframeIdIn, RESCUEINT64 objectIdIn);
  RescueTrimLoopStub(RescueContext *context, RescueTrimLoop *actualLoopIn);
/*
  The object is never instantiated by the user.  The class library instantiates
  it on loading when a relationship to one of the Wireframe objects is read 
  off disk.  When the user wants to, they trade the stub for the real version.
*/
  RescueTrimLoop *actualLoop;

  friend class cSetRescueTrimLoopStub;
  friend class RescueProperty;
  friend class RescueFaultIntersection;
};

#endif




