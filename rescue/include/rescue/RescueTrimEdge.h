/********************************************************************

  RescueTrimEdge.h

  An edge of a trim loop.  It contains a pointer to a PolyLine and
  a direction.

  Rod Hanks,  July 1996

  April, 2005 - Added ownership flags for left and right vertex to
  clean up memory leaks.

*********************************************************************/
#ifndef RESCUETRIMEDGE_H
#define RESCUETRIMEDGE_H

#include "myHeaders.h"
#include "RescuePolyLineStub.h"
#include "RescuePolyLine.h"
#include "RescueTrimVertex.h"

typedef enum {R_RIGHT_TO_LEFT, R_LEFT_TO_RIGHT} _RescueLineDirection;
                                  // As seen from outside the object.

class RescueTrimEdge:public RescueObject
{
public:
  ~RescueTrimEdge();
  RescueTrimEdge(RescuePolyLine *polyLineIn, _RescueLineDirection directionIn);
  _RescueLineDirection Direction() {return direction;}
/******************************************************************************

    These methods automatically load the wireframe information if it
    is not currently loaded.

*******************************************************************************/
  RescueTrimVertex *StartingPoint(RescueModel *model); 
  RescueTrimVertex *EndingPoint(RescueModel *model);
  RESCUEINT64 NodeCount64();
  RESCUEINT32 NodeCount() {return (RESCUEINT32) NodeCount64();}
  RescuePolyLineNode *NthNode(RESCUEINT64 zeroBasedOrdinal);
                                // These do not include vertexes at the end.
  RescuePolyLine *PolyLine(RescueModel *model);
                                          // Owner of trim edge is owner of
                                          // trim loop it is used in.
  RescueTrimLoop *ParentLoop() {return ownerLoop;}
                                          // Could return zero when building a model
                                          // if you have not added it to a loop yet.
 /*******************************************************************************
 
  These methods let you examine the objects and determine if you want
  to load to get them.  StartingPointObj() and EndingPointObj() will be
  null unless the model is v29.  Otherwise they will never be null.
  If the model was copied over from a v28 or earlier model, the stubs will
  not be null, but the vertex will not be recoverable from them 
  (RescueTrimVertexStub::TrimVertex will return null).  In either case, the
  problem can be fixed by calling RescueTrimEdge::NodeCount(), then trying
  again.  If you then save the model as version 29 or later, the problem will
  be fixed permanently.

****************************************************************************/
  RescueTrimVertexStub *StartingPointObj();
  RescueTrimVertexStub *EndingPointObj();
  RescuePolyLineStub *PolyLineObj() {return polyLine;}
  
  RESCUEBOOL  SurfaceOnEdge( RescueIJSurface&  surf );
                                          // If this edge lies on the given
                                          // surface return TRUE
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescueTrimEdge(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass owner.
private:
  void FixupStubs(RescuePolyLine *line);

  RescuePolyLineStub *polyLine;
  RescueTrimVertexStub *leftVertex;
  RESCUEBOOL leftVertexLocalOwner;
  RescueTrimVertexStub *rightVertex;
  RESCUEBOOL rightVertexLocalOwner;
  RescueTrimLoop *ownerLoop;
  _RescueLineDirection direction;

  friend class cSetRescueTrimEdge;
  friend class RescueTrimLoop;
  friend class cSetRescueWireframe;
};

#endif




