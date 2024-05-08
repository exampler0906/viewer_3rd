/********************************************************************

  RescueTrimLoop.h

  A set of edges which form a loop which may describe the relationship of a top, 
  bottom, or side of a block unit to a set of surfaces.

  Rod Hanks,  September 1997

*********************************************************************/
#ifndef RescueTrimLoop_H
#define RescueTrimLoop_H

#include "myHeaders.h"
#include "RescueTrimEdge.h"
#include "cSetRescueTrimEdge.h"
#include "RCHString.h"
class RescueWireframeOwner;
class RescueProperty;

class RescueTrimLoop:public RescueObject
{
public:
  RescueTrimLoop(RescueWireframeOwner *wireframeIn, RESCUECHAR *loopClassIn = 0);
  ~RescueTrimLoop();
  RescueWireframe *Owner() {return owner;}   // Will return 0 if owned by RescueEdgeSet.
  RescueEdgeSet *OwnerSet() {return ownerSet;} // Will return 0 unless owned by a RescueEdgeSet.
  RescueProperty *OwnerProperty(RescueModel *model);   // Will return 0 unless owned by RescueProperty.
  RCHString *LoopClass() {return loopClass;}
                                             // DO NOT delete or change the returned
                                             // string. If there is no loop class defined
                                             // you will get back a zero length RCHString,
                                             // and therefore stringObject->String() will
                                             // be null.
  void SetLoopClass(RESCUECHAR *newClass) {(*loopClass) = newClass;}
  RESCUEINT64 FaceHint() {return faceHint;}         // If this is a trim loop on a triangulated surface
  void SetFaceHint(RESCUEINT64 hint)                // the face hint is the index number of a RescueTriangleFace
          {faceHint = hint;}                // known to be inside the loop.  -1 if not set.

  void AddLoopEdge(RescueTrimEdge *existingEdge);
  void DropLoopEdge(RescueTrimEdge *existingEdge);
  RescueTrimEdge *NthLoopEdge(RESCUEINT64 zeroBasedOrdinal)
                        {return loopEdges->NthObject(zeroBasedOrdinal);}
  
  RESCUEINT64  CountOfLoopEdge64() { return  loopEdges->Count64(); }
  RESCUEINT32  CountOfLoopEdge() { return  loopEdges->Count(); }
  RESCUEINT32  CountOfLoopEdge(RESCUEBOOL throwIfTooBig);
  RESCUEBOOL IsLoop(RescueModel *model);    // Returns TRUE if the edges are closed and
                    // do progress in a consistent direction.
  
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescueTrimLoop(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass owner.

private:
  RescueTrimLoop(RescueContext *context, cSetRescueTrimEdge *loopEdgesIn);
  RescueTrimLoop(RescueContext *context, RESCUECHAR *classNameIn);
  cSetRescueTrimEdge *loopEdges;
  RCHString *loopClass;
  RESCUEINT64 faceHint;                          // index of associated RescueTriangleFace.
  RescueWireframe *owner;                // Will be null if owned by RescueEdgeSet.
  RescueEdgeSet *ownerSet;               // Will be null UNLESS owned by RescueEdgeSet.
  RESCUEINT64 propertyID;                        // Will be zero unless a trim loop on a property.

  friend class cSetRescueTrimLoop;
  friend class RescueEdgeSet;
  friend class RescueGeometry;
  friend class RescueProperty;
  friend class cSetRescueWireframe;
};

#endif



