/********************************************************************

  RescueGeometryPropertyList.h

  Returns a table-and-column style listing of properties in a
  RescueGeometry (and possibly it's LGR's) that places properties
  within context of groupings and times.

  This class is ephemeral.  It is accurate at the moment it is 
  created but any editing events after that point are not reflected
  in it's values.  It is not persistent.

  The order is either : by group, by time step, by geometry, by property
               or     : by time step, by group, by geometry, by property

  Properties that are in more than one group and/or timestep may appear
  more than once.

  Properties that are not in a timestep will not appear.

  The geometry you pass to the constructor must be a root geometry,
  not an LGR.  LGRs that are listed in the Geometry column are not
  necessarily included in the RescueTimeStep group of the same row,
  but they do have a property which is included in that group so
  presumably they do have something to do with that time step.

  Rod Hanks,  October, 2006

*********************************************************************/
#ifndef RESCUEGEOMETRYPROPERTYLIST_H
#define RESCUEGEOMETRYPROPERTYLIST_H

class RescueGeometry;
class RescueProperty;
class RescueBlockUnit;
class RescueGeobodyPart;
class RescueTimeStepGroup;

class RescueGeometryPropertyList
{
public:
  RescueGeometryPropertyList(RescueGeometry *geometry, 
                             RESCUEBOOL byTimeStep,             // TRUE if order of rows is by time step, by group, by geometry.
                                                                // FALSE for by group, by time step by geometry.  Of course,
                                                                // if you limit to a single group or time step this
                                                                // is immaterial.
                             RESCUEBOOL includeLGRs,            // TRUE if properties of LGRs are included.
                             RescuePropertyGroup *nullOrGroup,  // Non-null, limit to particular RescuePropertyGroup.
                             RESCUECHAR *nullOrTimeStepName);   // Non-null, limit to particular time step name.
                                                                // See the time manager.
  ~RescueGeometryPropertyList();

  RESCUEINT32 Count() {return count;}                      // Number of rows.
                                                   // The following return data from a particular row.
  RescueProperty *NthRowProperty(RESCUEINT32 zbn);
  RescueGeometry *NthRowGeometry(RESCUEINT32 zbn);
  RescueTimeStepGroup *NthRowTimeStepGroup(RESCUEINT32 zbn);
  RescuePropertyGroup *NthRowPropertyGroup(RESCUEINT32 zbn);
private:
  void AddGeometry(RescueGeometry *geometry, RESCUECHAR *nullOrTimeStepName);
  void AddGroup(RescuePropertyGroup *group, RescueGeometry *geometry, 
                RESCUECHAR *nullOrTimeStepName);
  void AddRow(RescueProperty *property, 
              RescueGeometry *geom,
              RescueTimeStepGroup *ts, 
              RescuePropertyGroup *group);
  RESCUEINT64 NdxOf(RescueProperty *property, 
                  RescueGeometry *geom,
                  RescueTimeStepGroup *ts, 
                  RescuePropertyGroup *group);
  RESCUEINT64 CompareRow(RESCUEINT64 ndx, 
                       RescueProperty *property, 
                       RescueGeometry *geom,
                       RescueTimeStepGroup *ts, 
                       RescuePropertyGroup *group);
  static RESCUEINT64 IDCompare(RESCUEINT64 id1, RESCUEINT64 id2);

  RESCUEBOOL includeLGRs;
  RESCUEBOOL byTimeStep;
  RESCUEINT32 allocated;
  RESCUEINT32 count;
  RescueProperty **properties;
  RescueGeometry **geometries;
  RescueTimeStepGroup **timeSteps;
  RescuePropertyGroup **groups;
};

#endif



