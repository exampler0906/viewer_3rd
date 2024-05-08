/********************************************************************

  RescueFaultIntersection.h

  This object allows the classification of horizons in a model
  by age, by declaring a depositional ordering of horizons.

  Rod Hanks,  June 2000

*********************************************************************/
#ifndef RESCUEFaultIntersection_H
#define RESCUEFaultIntersection_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueSection.h"
#include "cBagRescueSection.h"

class RescueFaultIntersection:public RescueHistoryObject
{
public:
  ~RescueFaultIntersection();
  RescueFaultIntersection(RescueModel *model,
                          RescueSection *majorSection, 
                          RescueSection *minorSection);
                     //   majorSection and minorSection must be valid sections.
          // Do not delete these objects.  Use RescueModel::DropRescueFaultIntersection.
  RescueModel *ParentModel() {return parentModel;}
  RescueSection *MajorSection() {return majorSection;}
  RescueSection *MinorSection() {return minorSection;}

  void SetMajorSection(RescueSection *newMajorSection) {majorSection = newMajorSection;}
  void SetMinorSection(RescueSection *newMinorSection) {minorSection = newMinorSection;}
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
  RescueFaultIntersection(RescueContext *contextIn, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass RescueModel.

  static void UnArchiveWireframeData(RescueModel *model, FILE *archiveFile);
  void ArchiveWireframeData(FILE *archiveFile);
  void RelinkWireframeData(RescueObject *model);
  void AutoEdgeSet();
private:
  RescueModel *parentModel;
  RescueSection *majorSection; 
  RescueSection *minorSection; 
  RescueEdgeSetStub *edges;      
  RESCUEINT64 loopId;                     
  RescueContext *context;

  RESCUEINT64 majorId;            // These are used during relinking.
  RESCUEINT64 minorId;

  RescueEdgeSetStub *sectionEdges;  // These are used in reading an older model.
  RESCUEINT64 tloopId;

  friend class cSetRescueFaultIntersection;
  friend class RescueModel;
};

#endif




