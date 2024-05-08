/********************************************************************

  RescueGeobodySurface.h

  An association between a RescueSurface and a RescueGeobodyVolume.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RescueGeobodySurface_H
#define RescueGeobodySurface_H

#include "myHeaders.h"
#include "RescueObject.h"
class RCHString;
class RescueSurface;
class RescueEdgeSet;
class RescueEdgeSetStub;
class RescueModel;
class RescueGeobodyVolume;

class RescueGeobodySurface:public RescueObject
{
public:
  typedef enum {TOP, BOTTOM, SIDE, INTERIOR, UNKNOWN} Role;
  ~RescueGeobodySurface();
/****************************************************************************************************

    The stub method lets you find out if you are stepping into a part of the model
    that has not been loaded.  From the stub you can find the
    RescueWireframe involved in the node, and you can find out if that node is
    loaded.

    This method will return zero if RescueModel::LoadWireframe() has not been called.

*************************************************************************************************/
  RescueEdgeSetStub *EdgesObj();
/*********************************************************************************************

    This method will automatically load the wireframe if the part you need for
    the edges is not yet loaded.

    This method will return zero if RescueModel::LoadWireframe() has not been called.

**********************************************************************************************/
  RescueEdgeSet *Edges();
  RescueSurface *Surface() {return surface;}
  Role SurfaceRole() {return role;}
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueGeobodySurface(RescueGeobodyVolume *parentVolumeIn, RescueSurface *existingSurface, Role roleIn);
  RescueGeobodySurface(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);
  void AutoEdgeSet();

  RescueEdgeSetStub *edges;
  RescueSurface *surface;
  RescueGeobodyVolume *parentVolume;
  Role role;
  RESCUEINT64 surfaceID;  // only during relinking.
  _RescueObjectType surfaceType;

  friend class cSetRescueGeobodySurface;
  friend class RescueGeobodyVolume;
  friend class cSetRescueWireframe;
};

#endif


