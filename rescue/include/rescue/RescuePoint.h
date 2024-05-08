/********************************************************************

  RescuePoint.h

  A point on a Pillar grid.  We don't need the overhead
  so this is not a RescueObject.

  Rod Hanks,  Oct, 2003

*********************************************************************/
#ifndef RescuePoint_H
#define RescuePoint_H

#include "myHeaders.h"

class RescuePoint
{
public:
  RESCUEFLOAT x;
  RESCUEFLOAT y;
  RESCUEFLOAT z;
  RescuePoint(RESCUEFLOAT xIn, RESCUEFLOAT yIn, RESCUEFLOAT zIn):x(xIn),y(yIn),z(zIn) {}
  RescuePoint(RescuePoint *in):x(in->x),y(in->y),z(in->z) {}
  RescuePoint(const RescuePoint &in):x(in.x),y(in.y),z(in.z) {}
  ~RescuePoint() {};
/*
  Need a public destructor to get a Java dispose() method.
*/
  RESCUEFLOAT X() {return x;}
  RESCUEFLOAT Y() {return y;}
  RESCUEFLOAT Z() {return z;}
  void SetX(RESCUEFLOAT xIn) {x = xIn;}
  void SetY(RESCUEFLOAT yIn) {y = yIn;}
  void SetZ(RESCUEFLOAT zIn) {z = zIn;}
  //<--
  RescuePoint operator+(const RescuePoint& in) const {return RescuePoint(x+in.x,y+in.y,z+in.z);}
  RescuePoint operator-(const RescuePoint& in) const {return RescuePoint(x-in.x,y-in.y,z-in.z);}
  RescuePoint operator*(RESCUEFLOAT in) const {return RescuePoint(x*in, y*in, z*in);}
  RescuePoint operator/(RESCUEFLOAT in) const {return RescuePoint(x/in, y/in, z/in);}
  RESCUEFLOAT operator[](const RESCUEINT64 i) const {return (&x)[i];}
  //-->
protected:
  void Archive(RescueContext *context, FILE *archiveFile);
  RescuePoint(RescueContext *context, FILE *archiveFile);

  friend class cSetRescuePoint;
};

#endif

