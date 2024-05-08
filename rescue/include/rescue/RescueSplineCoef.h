/********************************************************************

  RescueSplineCoef.h

  Spline Coefficients to support RescuePillar.

  Rod Hanks,  October 2003

*********************************************************************/
#ifndef RescueSplineCoef_H
#define RescueSplineCoef_H

#include "RescuePillar.h"
#include "RescueModel.h"
#include <float.h>

class cSetRescuePoint;
class cSetRescueSplineCoef;

class RescueSplineCoef
{
private:
  RESCUEFLOAT b;
  RESCUEFLOAT c;
  RESCUEFLOAT d;

  static RESCUEINT64 getNextBarrierIndex(cSetRescuePoint *points, RESCUEINT64 prev_index);
public:
  RescueSplineCoef():b(FLT_MAX),c(FLT_MAX),d(FLT_MAX) {}
  RESCUEFLOAT B() {return b;}
  RESCUEFLOAT C() {return c;}
  RESCUEFLOAT D() {return d;}
  void SetB(RESCUEFLOAT bIn) {b = bIn;}
  void SetC(RESCUEFLOAT cIn) {c = cIn;}
  void SetD(RESCUEFLOAT dIn) {d = dIn;}
  RESCUEFLOAT interpolate(RESCUEFLOAT zmin, RESCUEFLOAT dz) const;
  RESCUEFLOAT derive(RESCUEFLOAT dz) const;
  //<--
  static void rebuild(RescueSplineCoef splines[], 
                      cSetRescuePoint *points,
                      RESCUEINT64 index);
  //-->
protected:
  void Archive(RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);

  friend class RescuePillar;
};

#endif

