/********************************************************************

  RescueSection.h

  The sections for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUESECTION_H
#define RESCUESECTION_H

#include "myHeaders.h"
#include "RescueSurface.h"
#include "RCHString.h"
class RescueModel;
class RescueCoordinateSystemAxis;

class RescueSection:public RescueSurface
{
public:
  ~RescueSection();
  RescueSection(RescueCoordinateSystem::Orientation orientation,
                RESCUECHAR *newSectionName,
                RescueModel *parentModel,
                RescueSurface::SurfaceType typeIn,
                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                RESCUEFLOAT missingValue);
           // Create an empty section.  Use RescueTripletArray's SetValues
           // to assign values to all three simultaneously, or assign X, Y, 
           // and Z individually via RescueTripletArray's
           // methods.  All three axes must be assigned.
           // Drop with section->ParentModel()->DropRescueSection(section);
  RescueSection(RescueCoordinateSystem::Orientation orientation,
                RESCUECHAR *newSectionName,
                RescueModel *parentModel,
                RescueSurface::SurfaceType typeIn,
                RESCUEFLOAT missingValue);
           // Create an empty section.  This version creates a dummy RescueIJSection
           // and is usually used to create RescueTriangulatedSurface representations
           // (though this can also be used with NON-DUMMY RescueIJSections)
           // Drop with section->ParentModel()->DropRescueSection(section);
  RescueSection(RescueCoordinateSystem::Orientation orientation,
                RESCUECHAR *newSectionName,
                RescueModel *parentModel,
                RescueSurface::SurfaceType typeIn,
                RESCUEINT64 i_lowbound, RESCUEINT64 i_count, 
                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                RESCUEFLOAT missingValue, RESCUEFLOAT *tripletArray);
           // Create a new section.  The array has 3 dimensions.  The first
           // two are i and j, the third corresponds to x, y, z.
           // Drop with section->ParentModel()->DropRescueSection(section);
  RescueSection(RescueCoordinateSystem::Orientation orientation,
                RESCUECHAR *newSectionName,
                RescueModel *modelIn,
                SurfaceType type,
                RescueCoordinateSystemAxis *i_axis,
                RESCUEFLOAT i_origin, RESCUEFLOAT i_step,
                RESCUEINT64 i_lowbound, RESCUEINT64 i_count,
                RescueCoordinateSystemAxis *j_axis,
                RESCUEFLOAT j_origin, RESCUEFLOAT j_step,
                RESCUEINT64 j_lowbound, RESCUEINT64 j_count,
                RESCUEFLOAT missingValue);
           // Create an empty section. The section is regular along the i
           // and/or j direction.  For each regular axis dimension, one coordinate
           // system coordinate (x, y, or z) is calculated from the axis index
           // using an origin and step.  WHICH coordinate is calculated depends
           // upon which RescueCoordinateSystemAxis is passed.  Pass one of the
           // RescueCoordinateSystemAxis objects from the RescueModel's CoordinateSystem()
           // where axis 0 = x, axis 1 = y, axis 2 = z.  If you have only one regular
           // dimension pass 0, 0.0, 0.0 for axis, origin, and step for the other one.
           // You must use RescueTripletArray's methods to assign values to any dimension
           // which is not regular.
           // Drop with section->ParentModel()->DropRescueSection(section);
  RCHString *SectionName() {return sectionName;}
                              // Do NOT delete the returned object.
  void SetSectionName(RESCUECHAR *newSectionName) {(*sectionName) = newSectionName;}
  RescueModel *ParentModel() {return parentModel;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  RESCUEBOOL IsNamed(RESCUECHAR *possibleName);
private:
  RescueSection(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentObject);

  RCHString *sectionName;
  //RescueModel *parentModel;

  friend class cSetRescueSection;
  friend class RescueBlockUnitSide;
};

#endif




