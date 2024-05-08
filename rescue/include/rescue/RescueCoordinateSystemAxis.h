/********************************************************************

  RescueCoordinateSystemAxis.h

  CoordinateSystem axis for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUECoordinateSystemAXIS_H
#define RESCUECoordinateSystemAXIS_H

#include "myHeaders.h"
#include "RCHString.h"
class RescueCoordinateSystem;

class RescueCoordinateSystemAxis:public RescueObject
{
public:
  RescueCoordinateSystem *ParentCoordinateSystem() {return parentCoordinateSystem;}
  ~RescueCoordinateSystemAxis();
  RCHString *AxisName() {return axisName;}
                                  // Do NOT delete the returned object.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  RCHString *UnitOfMeasure() {return unitOfMeasure;}
                               // to be currently valid.
private:
  RescueCoordinateSystemAxis(RescueCoordinateSystem *parentIn,
			     const RESCUECHAR *nameIn,
			     const RESCUECHAR *uomIn);
  void Archive(FILE *archiveFile);
  RescueCoordinateSystemAxis(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parentObject);


  RescueCoordinateSystem *parentCoordinateSystem;
  RCHString *axisName;
  RCHString *unitOfMeasure;

  friend class RescueCoordinateSystem;
  friend class RescueGridAxis;
  friend class RescuePolyLine;
  friend class RescueTripletArray;
};

#endif




