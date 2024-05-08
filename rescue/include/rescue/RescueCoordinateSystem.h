/********************************************************************

  RescueCoordinateSystem.h

  Coordinate system for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUECOORDINATESYSTEM_H
#define RESCUECOORDINATESYSTEM_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RescueCoordinateSystemAxis.h"
class RescueVertex;
class RescueUnit;
class RescueModel;

class RescueCoordinateSystem:public RescueHistoryObject
{
public:
  typedef enum {LUF, LUB, LDF, LDB, RUF, RUB, RDF, RDB} Orientation;

/*
  The displayOrientation shows which corner the origin is located on: 

    Key:	Left/Right
	        Up/Down
	        Front/Back
*/
  RescueCoordinateSystem(RescueContext *context,
                         RESCUECHAR *name,
                         Orientation displayOrientationIn,
                         RescueVertex *vertexIn,
                         const RESCUECHAR *Xproperty, RESCUECHAR *Xuom,
                         const RESCUECHAR *Yproperty, RESCUECHAR *Yuom,
                         const RESCUECHAR *Zproperty, RESCUECHAR *Zuom,
                         RESCUEINT64 insysIn = 0,
                         RESCUEINT64 inzoneIn = 0,
                         RESCUEINT64 inUnitIn = 0,
                         RESCUEINT64 insphIn = 0,
                         RESCUEDOUBLE semiMajorAxisIn = 0.0,
                         RESCUEDOUBLE eccentricityIn = 0.0,
                         RESCUEDOUBLE standardLatIn = 0.0,
                         RESCUEDOUBLE secondLatIn = 0.0,
                         RESCUEDOUBLE centralLongIn = 0.0,
                         RESCUEDOUBLE latOriginIn = 0.0,
                         RESCUEDOUBLE FALSEEastingIn = 0.0,
                         RESCUEDOUBLE FALSENorthingIn = 0.0);
  RESCUEINT64 Dimensions() {return 3;}
  RescueCoordinateSystemAxis *Axis(RESCUEINT64 zeroBasedOrdinal);
  RescueCoordinateSystemAxis *AxisIdentifiedBy(RESCUEINT64 identifier);
  RescueVertex *Vertex() {return vertex;}
                                  // Do NOT free the object passed.
  void SetVertex(RescueVertex *newVertex);

  RCHString *Name() {return coordinateSystemName;}
                              // Do NOT delete the returned object.
  Orientation OrientationIs() {return displayOrientation;}
  RESCUEINT64 InSys() {return insys;}
  RESCUEINT64 InZone() {return inzone;}
  RESCUEINT64 InUnit() {return inUnit;}
  RESCUEINT64 InSpheroid() {return insph;}
  RESCUEDOUBLE SemiMajorAxis() {return semiMajorAxis;}
  RESCUEDOUBLE EccentricityOrSemiMinorAxis() {return eccentricity;}
  RESCUEDOUBLE StandardLat() {return standardLat;}
  RESCUEDOUBLE SecondLat() {return secondLat;}
  RESCUEDOUBLE CentralLong() {return centralLong;}
  RESCUEDOUBLE LatOrigin() {return latOrigin;}
  RESCUEDOUBLE FalseEasting() {return FALSEEasting;}
  RESCUEDOUBLE FalseNorthing() {return FALSENorthing;}

  void SetPublicEPSG(RESCUEINT32 epsgIn) {epsgId = epsgIn;}
  RESCUEINT32 PublicEPSG() {return epsgId;}

  RESCUEINT64 NdxOf(RescueCoordinateSystemAxis *axisIn);
  RescueContext *Context() {return context;}

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  virtual ~RescueCoordinateSystem();
                                  // The Coordinate system "owns" the
                                  // the vertex.  Since a vertex also
                                  // "owns" its coordinate system, you
                                  // can make the whole thing go away
                                  // by deleting the coordinate system
                                  // at the top of the chain.
private:
  RescueCoordinateSystem(RescueContext *contextIn, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void RegisterWith(RescueModel *parentModelIn);

  RescueContext *context;
  RCHString *coordinateSystemName;
  Orientation displayOrientation;
  RescueVertex *vertex;            // May be NULL (otherwise this could go on forever).
  RescueCoordinateSystemAxis *axes[3];
  RESCUEINT64 insys;
  RESCUEINT64 inzone;
  RESCUEINT64 inUnit;
  RESCUEINT64 insph;
  RESCUEDOUBLE semiMajorAxis;
  RESCUEDOUBLE eccentricity;
  RESCUEDOUBLE standardLat;
  RESCUEDOUBLE secondLat;
  RESCUEDOUBLE centralLong;
  RESCUEDOUBLE latOrigin;
  RESCUEDOUBLE FALSEEasting;
  RESCUEDOUBLE FALSENorthing;
  RESCUEINT32 epsgId;

  RescueModel *parentModel;
  friend class RescueModel;
  friend class RescueVertex;
  friend class RescueTrimVertex;
  friend class RescuePolyLine;
  friend class RescueTripletArray;
  friend class RescueWellbore;
  friend class RescueGrid;
};

#endif




