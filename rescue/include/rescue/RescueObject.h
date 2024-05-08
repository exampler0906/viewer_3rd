/********************************************************************

  RescueObject.h

	An abstract class for all of the objects in the application view,
	the main purpose being initialization, run-time typing of objects, 
	and tombstones.

  Rod Hanks

*********************************************************************/
#ifndef RESCUEOBJECT_H
#define RESCUEOBJECT_H

#include <stdio.h>
#include "RescueContext.h"

class RescueHistory;
class cBagRescueHistory;

typedef enum {R_TOMBSTONE, 
	            R_RescueObject,
              R_RescueModel,
              R_RescueBlock,
              R_RescueUnit,
              R_RescueHorizon,
              R_RescueSection,
              R_RescueBlockUnit,
              R_RescueBlockUnitSide,
              R_RescueProperty,
              R_RescuePropertyGroup,
              R_RescueBlockUnitHorizonSurface,
              R_RescueWellbore,
              R_RescueWellboreProperty,
              R_RescueGrid,
              R_RescueGridAxis,
              R_RescueArray,
              R_RescueTripletArray,
              R_RescueCoordinateSystemAxis,
              R_RescueVertex,
              R_RescueCoordinateSystem,
              R_RescueSurface,
              R_RescueDoubletArray,
              R_RescueTrimVertex,
              R_RescueEdgeSet,
              R_RescueTrimEdge,
              R_RescuePolyLine,
              R_RescuePolyLineNode,
              R_RescuePolyLineNodeUV,
      			  R_RescueGeometry,
			        R_RescueSurfaceCell,
              R_RescueWellboreSampling,
              R_RescueWellboreSurface,
              R_RescueWellboreCell,
              R_RescueReferenceSurface,
              R_RescueLookup,
              R_RescueLookupItem,
              R_RescueLookupString,
              R_RescueLookupTable,
              R_RescueArrayDouble,
              R_RescueArrayByte,
              R_RescueArrayShort,
              R_RescueTrimLoop,
              R_RescueArrayFloat,
              R_RescueMacroVolume,
              R_RescueModelPropertyGroup,
              R_RescueTimeStepGroup,
              R_RescueBitArray,
              R_RescueColor,
              R_RescueHistory,
              R_RescueHistoryObject,
              R_RescueArray2dVector,
              R_RescueArray3dVector,
              R_RescueColorTable,
              R_RescueColorTableList,
              R_RescueGeobody,
              R_RescueGeobodyPart,
              R_RescueGeobodySurface,
              R_RescueGeobodyVolume,
              R_RescueSurfaceToGrid,
              R_RescuePolyLineNodeBUG,
              R_RescueIJSurface,
              R_RescueCellShape,
              R_RescueEventDescr,
              R_RescueLogicalOrder,
              R_RescueFaultIntersection,
              R_RescuePolyLineNodeAvatar,
              R_RescueWireframeStub,
              R_RescuePolyLineStub,
              R_RescuePolyLineNodeAvatarStub,
              R_RescueTrimVertexStub,
              R_RescueEdgeSetStub,
              R_RescueTrimLoopStub,
              R_RescueWireframe,
              R_RescueWireframeOwner,
              R_RescueArrayInt,
              R_RescueGeometryUnit,
              R_RescueReservoir,
              R_RescueQuadrupletArray,
              R_RescuePolyLineNodeUVT,
              R_RescueStairSteppedFault,
              R_RescueLogicalOrderEntry,
              R_RescueDataContainer,
              R_RescueDocument,
              R_RescueDocumentList,
              R_LAST_OBJECT_TYPE} _RescueObjectType;

/************************* R e s c u e O b j e c t *************************/
/*
	An abstract class for all of the objects in the application view,
	the main purpose being initialization, run-time typing of objects, 
	and tombstones.
*/
class RescueObject
{
public:
  RESCUEBOOL IsIdentifiedBy(RESCUEINT64 possibleID) {return (uniqueID == possibleID);}
  RESCUEINT64 Identifier() {return uniqueID;}
  virtual RESCUEBOOL IsNamed(RESCUECHAR *mayBeName) {return FALSE;}
  _RescueObjectType IsA() {return isA;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType)
				{return (thisType == R_RescueObject);}
					                            // Returns TRUE if the object is a
					                            // member of the specified class.
/************************** H o u s e k e e p i n g **********************/
  virtual ~RescueObject() {}
  RescueObject(RescueContext *context) {uniqueID = (context->uniqueIDCounter)++;}

/************************** L o c a l   O p t i o n ***********************/
#ifdef LOCAL_OPTIONS
  void *memo;                         // Individual readers and writers can
                                      // add any members to RescueObjects that
                                      // they find handy, as long as they don't
                                      // archive or unarchive them.
#endif

/************************** P r i v a t e *********************************/
protected:
  void ReadId(RescueContext *context, FILE *archiveFile); 
  virtual void Relink(RescueObject *object) {} 

  volatile _RescueObjectType isA;
  RESCUEINT64 uniqueID;

  friend class RescueEdgeSetStub;
  friend class RescueEdgeSet;
};

#endif




