/********************************************************************

  RescueWireframeOwner.h

  A RescueHistory object which, like RescueBlockUnit and RescueGeobodyPart,
  is capable of owning a RescueWireframe.

  Rod Hanks,  March 2001

*********************************************************************/
#ifndef RescueWireframeOwner_H
#define RescueWireframeOwner_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueWireframe.h"
class RescueModel;

class RescueWireframeOwner:public RescueHistoryObject
{
public:
  virtual RescueModel *ParentModel()=0;
  RescueWireframe *Wireframe();       // Will return zero if the wireframe is not loaded.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  RescueWireframeOwner(RescueContext *context):RescueHistoryObject(context),wireframe(0) {}

  RescueWireframe *wireframe;

  friend class RescueWireframe;
};

#endif

