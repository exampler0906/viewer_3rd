/*************************************************************************

        cBagRescueSurfaceToGrid.h

	Keeps a list of pointers to RescueSurfaceToGrid.

        Rod Hanks               December 15th, 1995	 / August 1996

****************************************************************************/

#ifndef cBagRescueSurfaceToGrid_H
#define cBagRescueSurfaceToGrid_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescueSurfaceToGrid;

class cBagRescueSurfaceToGrid
{
protected:
  RescueTree *tree;
public:
  cBagRescueSurfaceToGrid();
  ~cBagRescueSurfaceToGrid();
  void operator+=(RescueSurfaceToGrid *newObject);
  RESCUEBOOL operator-=(RescueSurfaceToGrid *existingObject);
  RescueSurfaceToGrid *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescueSurfaceToGrid *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
};

#endif




