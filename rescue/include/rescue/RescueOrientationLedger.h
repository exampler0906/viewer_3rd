/********************************************************************

  RescueOrientationLedger.h

  Private use of Rescue during SetOrientation method.

  Rod Hanks,  May 2006

*********************************************************************/
#ifndef RescueOrientationLedger_H
#define RescueOrientationLedger_H

#include "myHeaders.h"
#include "RescueCoordinateSystem.h"

class RescueIJSurface;
class RescueGeometry;

class RescueOrientationLedger
{
public:
  RescueOrientationLedger();
  bool GetIJFor(RescueIJSurface *face, 
                RESCUEINT64 &iLowBound, RESCUEINT64 &iCount, 
                RESCUEINT64 &jLowBound, RESCUEINT64 &jCount,
                bool &swapI, bool &swapJ);
  void SetIJFor(RescueIJSurface *face, 
                RESCUEINT64 iLowBound, RESCUEINT64 iCount, 
                RESCUEINT64 jLowBound, RESCUEINT64 jCount,
                bool swapI, bool swapJ);
  bool GetKFor(RescueGeometry *geom, 
                RESCUEINT64 &kLowBound, RESCUEINT64 &kCount, 
                bool &swapK);
  void SetKFor(RescueGeometry *geom,
               RESCUEINT64 kLowBound, RESCUEINT64 kCount, bool swapK);
  ~RescueOrientationLedger();
private:
  class GeomK
  {
    RescueGeometry *geom;
    RESCUEINT64 kLowBound;
    RESCUEINT64 kCount;
    bool swapK;
    GeomK *next;

    GeomK(RescueGeometry *geom,
               RESCUEINT64 kLowBound, RESCUEINT64 kCount, bool swapK);
    ~GeomK();

    friend class RescueOrientationLedger;
  };

  class SurfaceIJ
  {
    RescueIJSurface *face;
    RESCUEINT64 iLowBound;
    RESCUEINT64 iCount;
    bool swapI;
    RESCUEINT64 jLowBound;
    RESCUEINT64 jCount;
    bool swapJ;
    SurfaceIJ *next;

    SurfaceIJ(RescueIJSurface *face, 
                RESCUEINT64 iLowBound, RESCUEINT64 iCount, 
                RESCUEINT64 jLowBound, RESCUEINT64 jCount,
                bool swapI, bool swapJ);
    ~SurfaceIJ();

    friend class RescueOrientationLedger;
  };

  GeomK *kList;
  SurfaceIJ *ijList;
};

#endif




