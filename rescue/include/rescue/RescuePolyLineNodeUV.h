/********************************************************************

  RescuePolyLineNodeUV.h

  The description of a point in terms of it's position on some face's
  two dimensional grid.

  Rod Hanks,  July 1996

*********************************************************************/
#ifndef RescuePolyLineNodeUV_H
#define RescuePolyLineNodeUV_H

#include "myHeaders.h"

class RescueIJSurface;
class RescueOrientationLedger;

class RescuePolyLineNodeUV:public RescueObject
{
public:
  RescuePolyLineNodeUV(RescueContext *context, RescueIJSurface *faceIn, RESCUEFLOAT u, RESCUEFLOAT v)
                            :RescueObject(context)
                            ,uValue(u)
                            ,vValue(v)
                            ,face(faceIn) {isA = R_RescuePolyLineNodeUV;}
  void SetUVValue(RESCUEFLOAT u, RESCUEFLOAT v) {uValue = u; vValue = v;}
  RESCUEFLOAT U() {return uValue;} 
  RESCUEFLOAT V() {return vValue;} 
  RescueIJSurface *Face() {return face;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescuePolyLineNodeUV(RescueContext *context, FILE *archiveFile);
  void SetOrientation(RescueOrientationLedger *ledger);

private:
  virtual void Relink(RescueObject *object);
 
  RESCUEFLOAT uValue;
  RESCUEFLOAT vValue;
  RescueIJSurface *face;

  RESCUEINT64 faceID;     // Used only for relinking.

  friend class cSetRescuePolyLineNodeUV;
  friend class RescuePolyLine;
};

#endif




