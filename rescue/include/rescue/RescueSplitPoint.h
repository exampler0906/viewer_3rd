/********************************************************************

  RescueSplitPoint.h

  An object used by RescueTripletArray for split ij vertices
  in surface geometries.

  Rod Hanks,  October 2002

*********************************************************************/
#ifndef RescueSplitPoint_H
#define RescueSplitPoint_H

#include "myHeaders.h"

class RescueSplitPoint
{
private:
  RescueSplitPoint(RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
  void SetCornerNode(RESCUEINT64 corner, RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
	void Values(RESCUEINT64 corner, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
public:
  ~RescueSplitPoint() {delete addresses;}
private:
  void Archive(RescueContext *context, FILE *archiveFile, RESCUEBOOL compress);
  RescueSplitPoint(RescueContext *context, FILE *archiveFile, RESCUEBOOL compress);

  RESCUEFLOAT *addresses;  // 4 * 3.

  friend class RescueTripletArray;
};

#endif




