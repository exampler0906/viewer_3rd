/********************************************************************

  RescueGeometryLGRList.h

  Returns a table-and-column style listing of LGR's in a
  RescueGeometry tree that places LGR's within context of groupings 
  and times.

  This class is ephemeral.  It is accurate at the moment it is 
  created but any editing events after that point are not reflected
  in it's values.  It is not persistent.

  The order is either : by group, by time step, by geometry
               or     : by time step, by group, by geometry

  LGRs that are in more than one group and/or timestep may appear
  more than once.

  LGRs that are not in a timestep will not appear.

  The geometry that you pass must be a root geometry, not an LGR.

  Rod Hanks,  October, 2006

*********************************************************************/
#ifndef RescueGeometryLGRList_H
#define RescueGeometryLGRList_H

class RescueGeometry;
class RescueProperty;
class RescueBlockUnit;
class RescueGeobodyPart;
class RescueTimeStepGroup;

class RescueGeometryLGRList
{
public:
  RescueGeometryLGRList(RescueGeometry *geometry, 
                             RESCUEBOOL byTimeStep,             // TRUE if order of rows is by time step, by group, by geometry.
                                                                // FALSE for by group, by time step by geometry.  Of course,
                                                                // if you limit to a single group or time step this
                                                                // is immaterial.
                             RescuePropertyGroup *nullOrGroup,  // Non-null, limit to particular RescuePropertyGroup.
                             RESCUECHAR *nullOrTimeStepName);   // Non-null, limit to particular time step name.
                                                                // See the time manager.
  ~RescueGeometryLGRList();

  RESCUEINT32 Count() {return count;}              // Number of rows.
                                                   // The following return data from a particular row.
  RescueGeometry *NthRowGeometry(RESCUEINT32 zbn);
  RescueTimeStepGroup *NthRowTimeStepGroup(RESCUEINT32 zbn);
  RescuePropertyGroup *NthRowPropertyGroup(RESCUEINT32 zbn);
private:
  void AddGeometry(RescueGeometry *geometry, RESCUECHAR *nullOrTimeStepName);
  void AddGroup(RescuePropertyGroup *group, RescueGeometry *geometry, 
                RESCUECHAR *nullOrTimeStepName);
  void AddRow(RescueGeometry *geom,
              RescueTimeStepGroup *ts, 
              RescuePropertyGroup *group);
  RESCUEINT64 NdxOf(RescueGeometry *geom,
                  RescueTimeStepGroup *ts, 
                  RescuePropertyGroup *group);
  RESCUEINT64 CompareRow(RESCUEINT64 ndx, 
                       RescueGeometry *geom,
                       RescueTimeStepGroup *ts, 
                       RescuePropertyGroup *group);
  static RESCUEINT64 IDCompare(RESCUEINT64 id1, RESCUEINT64 id2);

  RESCUEBOOL byTimeStep;
  RESCUEINT32 allocated;
  RESCUEINT32 count;
  RescueGeometry **geometries;
  RescueTimeStepGroup **timeSteps;
  RescuePropertyGroup **groups;
};

#endif



