/********************************************************************

  RescueWellboreSurface.h

  The record of an intersect between a wellbore and a surface.

  Rod Hanks,  January 1997

*********************************************************************/
#ifndef RESCUEWellboreSurface_H
#define RESCUEWellboreSurface_H

#include "myHeaders.h"
#include <stdlib.h>
class RescueWellbore;
class RescueIJSurface;
class RescueGridAxis;

class RescueWellboreSurface:public RescueObject
{
public:
  RescueWellboreSurface(RescueWellbore *wellboreIn, 
                        RescueIJSurface *surfaceIn,
                        RESCUEFLOAT uIn, RESCUEFLOAT vIn, RESCUEFLOAT mdIn);
  RescueWellbore *Wellbore() {return wellbore;}
  RescueIJSurface *Surface() {return surface;}
  RESCUEFLOAT U() {return u;}
  RESCUEFLOAT V() {return v;}
  RESCUEFLOAT MD() {return md;}

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  ~RescueWellboreSurface();
private:
  virtual void Archive(FILE *archiveFile);
  RescueWellboreSurface(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void SetWellbore(RescueWellbore *wellboreIn) {wellbore = wellboreIn;}
  void Swap(bool swapI, RescueGridAxis *iAxis, bool swapJ, RescueGridAxis *jAxis);

  RescueWellbore *wellbore;
  RescueIJSurface *surface;
  RESCUEFLOAT u;
  RESCUEFLOAT v;
  RESCUEFLOAT md;
  RESCUEINT64 surfaceID;   // used only during relinking.

  friend class RescueWellbore;
  friend class cSetRescueWellboreSurface;
  friend class RescueIJSurface;
};

#endif




