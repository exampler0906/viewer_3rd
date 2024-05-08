/********************************************************************

  RescueEdgeSet.h

  A set of edges which describe the relationship of a top, bottom, or
  side of a block unit to a set of surfaces.

  Rod Hanks,  July 1996

*********************************************************************/
#ifndef RescueEdgeSet_H
#define RescueEdgeSet_H

#include "myHeaders.h"
#include "RescueTrimLoop.h"
#include "cSetRescueTrimLoop.h"
class RescueWireframeOwner;

class RescueEdgeSet:public RescueObject
{
public:
  RescueEdgeSet(RescueWireframeOwner *ownerIn);
  ~RescueEdgeSet();

  void AddBoundaryLoop(RescueTrimLoop *existingLoop);
  void DropBoundaryLoop(RescueTrimLoop *existingLoop);
  RescueTrimLoop *NthBoundaryLoop(RESCUEINT64 zeroBasedOrdinal)
                        {return (*boundaryLoops).NthObject(zeroBasedOrdinal);}
  void AddInteriorLoop(RescueTrimLoop *existingLoop);
  void DropInteriorLoop(RescueTrimLoop *existingLoop);
  RescueTrimLoop *NthInteriorLoop(RESCUEINT64 zeroBasedOrdinal) 
                        {return (*interiorLoops).NthObject(zeroBasedOrdinal);}

  RescueTrimLoop *TrimLoopIdentifiedBy(RESCUEINT64 identifier);
  RescueObject *RescueBusinessOwner(RescueModel *model);  
                                              // Will return null unless the file
                                              // was originally created under v29 or
                                              // later or was properly converted from
                                              // an earlier file.
  
  RESCUEINT64  CountOfBoundaryLoop64() { return  (*boundaryLoops).Count(); }
  RESCUEINT64  CountOfInteriorLoop64() { return  (*interiorLoops).Count(); }
  RESCUEINT32  CountOfBoundaryLoop() { return (RESCUEINT32) (*boundaryLoops).Count(); }
  RESCUEINT32  CountOfInteriorLoop() { return (RESCUEINT32) (*boundaryLoops).Count(); }
  RESCUEINT32  CountOfBoundaryLoop(RESCUEBOOL throwIfTooBig);
  RESCUEINT32  CountOfInteriorLoop(RESCUEBOOL throwIfTooBig);
  RescueWireframe *Owner() {return owner;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(FILE *archiveFile);
  RescueEdgeSet(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass RescueModel.

private:
/*********************************************************************************

  Since these RescueTrimLoops are never associated with any object but us, they are always in
  the same wireframe file and we have real relationships to them, not stubs.

**********************************************************************************/
  cSetRescueTrimLoop *boundaryLoops;   
  cSetRescueTrimLoop *interiorLoops;
  RescueWireframe *owner;

  _RescueObjectType ownerIsA;     // These are used to maintain RescueEdgeSet's
  RESCUEINT64 ownerId;                    // backward pointer to its owner.
public:
  void SetRescueBusinessOwner(RescueObject *ownerIn);
                                  // Users should not call this function, but
                                  // conversion programs need to call it in order
                                  // to link models that were built prior to v29.

  friend class RescueMacroVolume;
  friend class RescueBlockUnitHorizonSurface;
  friend class RescueBlockUnitSide;
  friend class cSetRescueEdgeSet;
  friend class RescueSurface;
  friend class RescueGeobodySurface;
  friend class RescueGeobodyVolume;
  friend class cSetRescueWireframe;
};

#endif




