/**************************************************************************

	RescueWireframeCallBack.h

	An abstract class which may be subclassed to report the loading of
  a RescueWireframe object during RESCUE operations.  Create an instance 
  of the subclass and pass it to RescueModel::RegisterWireframeCallBack.

	Rod Hanks,	January, 2002

**************************************************************************/

#ifndef RescueWireframeCallBack_H
#define RescueWireframeCallBack_H
#include "myHeaders.h"

class RescueWireframeCallBack

{
public:
  virtual void LoadingWireframe(RescueWireframe *beingLoaded)=0;
/*
  Called just prior to reading the wireframe contents from the file
  into memory.  You should avoid unloading memory during this function
  if at all possible . . . unless you are sure the RescueLibrary is not
  in the middle of a process that requires it.  It is better to set a
  semaphore for later action, if any is required.
*/
  virtual void UnloadingWireframe(RescueWireframe *beingUnloaded)=0;
/*
  Called just prior to removing the wireframe contents from memory.
  If you are managing memory this mostly allows you to keep your
  recordkeeping straight.

  Note this is called even on RescueWireframe objects that have never
  been loaded, but is NOT called when RescueWireframe objects are
  destructed along with the model.
*/
};

#endif




