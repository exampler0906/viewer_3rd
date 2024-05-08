/********************************************************************

  RescueMacroVolume.h

  The macro model description for a volume in a block unit.

  Rod Hanks,  September 1997

*********************************************************************/
#ifndef RescueMacroVolume_H
#define RescueMacroVolume_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueBlockUnitSide.h"
#include "cSetRescueBlockUnitSide.h"
#include "cBagInt.h"
#include "cBagRescueSection.h"
#include "cSetRescueEdgeSet.h"
#include "cSetRescueEdgeSetStub.h"
#include "RescueCoordinateSystem.h"
#include "RescueBlockUnit.h"
#include "RescueBlock.h"

class RescueSection;

class RescueMacroVolume:public RescueHistoryObject
{
public:
  RescueBlockUnit *ParentBlockUnit() {return parentBU;}
  RescueModel *ParentModel() {return parentBU->Block()->ParentModel();}
  void AddBlockUnitSide(RescueBlockUnitSide *existingSide);
  void DropBlockUnitSide(RescueBlockUnitSide *existingSide)
                        {(*blockUnitSides) -= existingSide;}
  RescueBlockUnitSide *NthBlockUnitSide(RESCUEINT64 zeroBasedOrdinal)
                        {return blockUnitSides->NthObject(zeroBasedOrdinal);}
  RescueBlockUnitSide *BlockUnitSideIdentifiedBy(RESCUEINT64 id)
                      {return blockUnitSides->ObjectIdentifiedBy(id);}
  void AddInteriorSection(RescueSection *existingSection)
                        {(*interiorSections) += existingSection;}
  void DropInteriorSection(RescueSection *existingSection)
                        {(*interiorSections) -= existingSection;}
  RescueSection *NthInteriorSection(RESCUEINT64 zeroBasedOrdinal) 
                        {return interiorSections->NthObject(zeroBasedOrdinal);}
                  // RescueMacroVolume does not "own" RescueSections,
                  // so it does not create or delete them, merely
                  // catalogs relationships to them. However, it does
                  // own block unit sides (but not the sections which
                  // they refer to).

  void AddKLayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteKLayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteKLayerEdge(RescueEdgeSetStub *existingEdgeSet)
      {return ((*kLayerEdges) -= existingEdgeSet);}
  RescueEdgeSetStub *NthKLayerEdge(RESCUEINT64 zeroBasedOrdinal)
      {return kLayerEdges->NthObject(zeroBasedOrdinal);}

  void AddILayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteILayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteILayerEdge(RescueEdgeSetStub *existingEdgeSet)
      {return ((*iLayerEdges) -= existingEdgeSet);}
  RescueEdgeSetStub *NthILayerEdge(RESCUEINT64 zeroBasedOrdinal)
      {return iLayerEdges->NthObject(zeroBasedOrdinal);}

  void AddJLayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteJLayerEdge(RescueEdgeSet *existingEdgeSet);
  RESCUEBOOL DeleteJLayerEdge(RescueEdgeSetStub *existingEdgeSet)
      {return ((*jLayerEdges) -= existingEdgeSet);}
  RescueEdgeSetStub *NthJLayerEdge(RESCUEINT64 zeroBasedOrdinal)
      {return jLayerEdges->NthObject(zeroBasedOrdinal);}

  void SetTopEdge(RescueEdgeSet *topEdge);
  void SetBottomEdge(RescueEdgeSet *bottomEdge);
  /*
    RescueMacroVolume has a curious relationship with its top and bottom RescueEdgeSets.
    It isn't sure whether it owns them or not.  RescueEdgeSet keeps a usage count.  RescueMacroVolume
    increments and decrements this count via RescueEdgeSet's RegisterUser and UnregisterUser
    methods.  UnregisterUser deletes the edge set when the usage falls to zero.

    Do not delete RescueEdgeSets.  If you don't want one anymore, simply replace it everyplace
    it is used with a new one.  It will delete itself.
  */
  RescueEdgeSetStub *TopEdgesObj() {return topEdges;}        // These may return 0.
  RescueEdgeSetStub *BottomEdgesObj() {return bottomEdges;}  //
  RescueEdgeSet *TopEdges();                                 // The RescueEdgeSet forms will load
  RescueEdgeSet *BottomEdges();                              // the wireframe object automatically.

  RESCUEINT64  CountOfSides64() { return  blockUnitSides->Count64(); }
  RESCUEINT32  CountOfSides() { return  blockUnitSides->Count(); }
  RESCUEINT32  CountOfSides(RESCUEBOOL throwIfTooBig);

  virtual ~RescueMacroVolume();
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueMacroVolume(RescueBlockUnit *parentBuIn);
  RescueMacroVolume(RescueContext *context, FILE *archiveFile);
  void PartialRead(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);
  void WriteActualEdgeSet(FILE *archiveFile);
  void WriteActualEdgeSet(FILE *archiveFile, RescueEdgeSetStub *toWrite);

  RescueBlockUnit *parentBU;
  cSetRescueBlockUnitSide *blockUnitSides;
  cBagRescueSection *interiorSections;
  /*
    boundary sections are arranged as nearly as possible counter-clockwise
    around the volume they enclose.

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
  RescueEdgeSetStub *topEdges;
  RescueEdgeSetStub *bottomEdges;
  /*
    Trims the intersection between this volume and it's top and bottom RescueBlockUnitHorizonSurface.
    If the two intersections are trimmed the same, these may point to the same object.  Also, the
    objects pointed to here may also be pointed to by some other RescueMacroVolume.
  */
  cSetRescueEdgeSetStub *kLayerEdges;
  /*
	The kLayerEdges is a set of trim edge sets, one for each k layer of the 3 dimensional
	block unit grid.  The edges are arranged in order by increasing k index.  That is,
	the first RescueEdgeSet in kLayerEdges relates to the edge having the lowest k
	index.

  Beginning with v28, pinched out layers can share RescueEdgeSets if they wish.
*/
  cSetRescueEdgeSetStub *iLayerEdges;
  cSetRescueEdgeSetStub *jLayerEdges;
/*
  Defining trim edge sets on each layer in each dimension is new with v32.  It is always
  optional.  If done it gives a very good description of the boundaries of the volume.
*/
  cBagInt *interiorSectionIDs;
  cSetRescueEdgeSet *oldEdgeSets;
  RescueEdgeSet *oldTopEdge;
  RescueEdgeSet *oldBottomEdge;
/*
  Temporary relinking stuff.
*/
  friend class cSetRescueMacroVolume;
  friend class RescueBlockUnit;
  friend class RescueGeometry;
};

#endif






