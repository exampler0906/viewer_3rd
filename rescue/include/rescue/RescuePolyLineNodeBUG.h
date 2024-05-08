/********************************************************************

  RescuePolyLineNodeBUG.h

  The description of a point in terms of it's position on some geometry's
  layer.

  Rod Hanks,  December 1999

*********************************************************************/
#ifndef RescuePolyLineNodeBUG_H
#define RescuePolyLineNodeBUGV_H

#include "myHeaders.h"
#include "RescuePolyLineNode.h"

class RescueGeometry;
class RescueContext;
class RescueOrientationLedger;

class RescuePolyLineNodeBUG:public RescueObject
{
public:
  void SetNdxParam(RESCUEFLOAT paramIn) {layerNdxParam = paramIn;}
  RescuePolyLineNode::RescueLayerType Type() {return layerType;} 
  RESCUEFLOAT NdxParam() {return layerNdxParam;} 
  RescueGeometry *Geometry() {return geometry;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  RescuePolyLineNodeBUG(RescueContext *context, 
                        RescueGeometry *geometryIn, 
                        RescuePolyLineNode::RescueLayerType typeIn,
                        RESCUEFLOAT ndxParamIn)
                            :RescueObject(context)
                            ,layerType(typeIn)
                            ,layerNdxParam(ndxParamIn)
                            ,geometry(geometryIn) {isA = R_RescuePolyLineNodeBUG;}
  virtual void Archive(RescueContext *context, 
                        FILE *archiveFile);
  RescuePolyLineNodeBUG(RescueContext *context, 
                        FILE *archiveFile);

private:
  virtual void Relink(RescueObject *object);
  void SetOrientation(RescueOrientationLedger *ledger);
 
  RescuePolyLineNode::RescueLayerType layerType;
  RESCUEFLOAT layerNdxParam;
  RescueGeometry *geometry;

  RESCUEINT64 geometryID;     // Used only for relinking.

  friend class cSetRescuePolyLineNodeBUG;
  friend class RescuePolyLineNode;
};

#endif




