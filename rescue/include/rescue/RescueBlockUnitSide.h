/********************************************************************

  RescueBlockUnitSide.h

  The side of a macro volume, described by a relationship to a section
  and a set of trim edges on that section.

  Rod Hanks,  July 1996

*********************************************************************/
#ifndef RESCUEBLOCKUNITSIDE_H
#define RESCUEBLOCKUNITSIDE_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueEdgeSetStub.h"
#include "RescueSection.h"
class RescueEdgeSet;
class RescueMacroVolume;

class RescueBlockUnitSide:public RescueHistoryObject
{
public:
  RescueBlockUnitSide(RescueSection *existingSection);
  virtual ~RescueBlockUnitSide();

  RescueSection *Section() {return section;}
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

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(FILE *archiveFile);
  RescueBlockUnitSide(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass RescueModel.

private:
  void DropWireframeMemory();
  void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void RelinkWireframeData(RescueObject *parent);
  void ArchiveWireframeData(FILE *archiveFile);
  void AutoEdgeSet();

  RescueSection *section;   
  RescueMacroVolume *parentVolume;
  RescueEdgeSetStub *edges;           //Interior edges are used to define the
                                      //intersection of the sections.

  RESCUEINT64 sectionID;           // Used only during relinking.
  friend class RescueBlock;
  friend class cSetRescueBlockUnitSide;
  friend class cSetRescueWireframe;
  friend class RescueMacroVolume;
};

#endif




