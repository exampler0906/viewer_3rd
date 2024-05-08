/********************************************************************

  RescueGeobodyVolume.h

  The volume decription for a RescueGeobodyPart.

  Rod Hanks,  June 1999

*********************************************************************/
#ifndef RescueGeobodyVolume_H
#define RescueGeobodyVolume_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "cBagInt.h"
#include "RescueCoordinateSystem.h"
#include "RescueGeobodySurface.h"
#include "cSetRescueGeobodySurface.h"
#include "cSetRescueEdgeSetStub.h"
class RescueEdgeSetStub;

class RescueGeobodyVolume:public RescueHistoryObject
{
public:
  void AddGeobodySurface(RescueSurface *existingSurface, RescueGeobodySurface::Role role);
                  // The surface should already be owned by some other object in the
                  // model (for example, it could be a RescueSection or a RescueReferenceSurface
                  // owned by RescueModel.  This adds top, bottom, side, and interior surfaces.
  void DropGeobodySurface(RescueSurface *existingSurface);
  void DropGeobodySurface(RescueGeobodySurface *existingSurface) {(*surfaces) -= existingSurface;}
                  // These deletes our relationship to the surface, but not the surface itself.
                  // You MUST do this prior to dropping the surface itself, or you end up with
                  // an invalid pointer to the surface.
  RESCUEINT64 SurfaceCount64() {return surfaces->Count64();}
  RESCUEINT32 SurfaceCount() {return surfaces->Count();}
  RescueGeobodySurface *NthGeobodySurface(RESCUEINT64 zeroBasedOrdinal)
                        {return surfaces->NthObject(zeroBasedOrdinal);}
  RescueGeobodySurface *GeobodySurfaceIdentifiedBy(RESCUEINT64 id)
                        {return surfaces->ObjectIdentifiedBy(id);}
  RescueGeobodyPart *ParentPart() {return parentPart;}

  void AddKLayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteKLayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteKLayerEdge(RescueEdgeSetStub *existingEdgeSet)
      {return ((*kLayerEdges) -= existingEdgeSet);}
  RescueEdgeSetStub *NthKLayerEdge(RESCUEINT64 zeroBasedOrdinal)
      {return kLayerEdges->NthObject(zeroBasedOrdinal);}
  RESCUEINT64 KLayerEdgeCount64() {return kLayerEdges->Count64();}
  RESCUEINT32 KLayerEdgeCount() {return kLayerEdges->Count();}

  virtual ~RescueGeobodyVolume();
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  void FindUniquePropertyNames(cSetString *container);
private:
  RescueGeobodyVolume(RescueGeobodyPart *parentPart);
  RescueGeobodyVolume(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);

  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);
  void WriteActualEdgeSet(RescueContext *context, FILE *archiveFile);

  RescueGeobodyPart *parentPart;
  cSetRescueGeobodySurface *surfaces;
  /*
    boundary surfaces which are marked as SIDE are arranged as nearly as possible 
    counter-clockwise around the volume they enclose.

    Note that section surfaces are ordinarily described with counter-clockwise
    trim loops, as seen from outside the volume which they enclose.  However,
    if a section surface is used as the boundary of two adjacent volumes it
    can only be correctly described in relation to one of them.  Of course, the
    problem is worse for interior sections, since there is not even a convention
    for how they are constructed.
    
    Therefore, software must examine the trim loops to determine which way round 
    the description of the surface is built with respect to any particular boundary.

    If this is insufficient, we could include a "normal" point with respect to
    each surface in RescueSurface.
  */
  cSetRescueEdgeSetStub *kLayerEdges;
  /*
	  The kLayerEdges is a set of trim edge sets, one for each k layer of the 3 dimensional
	  block unit grid.  The edges are arranged in order by increasing k index.  That is,
	  the first RescueEdgeSet in kLayerEdges relates to the edge having the lowest k
	  index.

	  Note that pinched out layers can share RescuePolyLines, but they cannot share
	  RescueEdgeSets - because we own the edge set we will try to delete it when
	  we are deleted, and if we try twice we will meet with disaster.
*/

  friend class cSetRescueGeobodyVolume;
  friend class RescueBlockUnit;
  friend class RescueGeometry;
  friend class RescueGeobodyPart;
};

#endif






