/********************************************************************

  RescueEdgeSetStub.h

  A RescueEdgeSet object that has been lazily relinked.
  
  You can preview the object here and trade it for a real one
  later.

  Rod Hanks,  March 2001

*********************************************************************/
#ifndef RescueEdgeSetStub_H
#define RescueEdgeSetStub_H

#include "myHeaders.h"
#include "RescueWireframeStub.h"
#include "RescueCoordinateSystem.h"
class RescueEdgeSet;

class RescueEdgeSetStub:public RescueWireframeStub
{
public:
  virtual ~RescueEdgeSetStub() {}
/******************************************************************

  These methods let you find out if the edge set is equal to
  another edge set, whether you have the edge set stub or the
  actual edge set.  Unlike edge sets, you can't find out if two
  stubs are the same object by comparing the pointers.

******************************************************************/
  RESCUEBOOL Equals(RescueEdgeSetStub *other);
  RESCUEBOOL Equals(RescueEdgeSet *other);
/*****************************************************************

  This method returns the real object that the stub represents,
  first loading it into memory if necessary.  It returns 0 if
  for some reason the real object is not available.  If you pass
  false for loadIfNeeded this may simply mean that the object you
  want is not loaded.  If you pass true, usually it would 
  mean that the object represented by the stub is no longer a
  member of the model.

****************************************************************/
  RescueEdgeSet *EdgeSet(RescueModel *model, RESCUEBOOL loadIfNeeded=TRUE);

/*****************************************************************

    Normal type-testing method.

*****************************************************************/
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  RescueEdgeSetStub(RescueContext *context, FILE *archiveFile);
  RescueEdgeSetStub(RescueContext *context, RESCUEINT64 wireframeIdIn, RESCUEINT64 objectIdIn);
  RescueEdgeSetStub(RescueContext *context, RescueEdgeSet *actualVertexIn);
/*
  The object is never instantiated by the user.  The class library instantiates
  it on loading when a relationship to one of the Wireframe objects is read 
  off disk.  When the user wants to, they trade the stub for the real version.
*/
  RescueEdgeSet *actualEdgeSet;

  friend class RescueSurface;
  friend class cSetRescueEdgeSetStub;
  friend class RescueMacroVolume;
  friend class RescueGeobodyVolume;
  friend class RescueGeobodySurface;
  friend class RescueBlockUnitSide;
  friend class RescueFaultIntersection;
};

#endif




