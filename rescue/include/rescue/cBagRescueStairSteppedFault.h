/*************************************************************************

        cBagRescueStairSteppedFault.h

	Keeps a list of pointers to RescueStairSteppedFault.

        Rod Hanks               December 15th, 1995	 / August 1996

****************************************************************************/

#ifndef cBagRescueStairSteppedFault_H
#define cBagRescueStairSteppedFault_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescueStairSteppedFault;

class cBagRescueStairSteppedFault
{
protected:
  RescueTree *tree;
public:
  cBagRescueStairSteppedFault();
  ~cBagRescueStairSteppedFault();
  void operator+=(RescueStairSteppedFault *newObject);
  RESCUEBOOL operator-=(RescueStairSteppedFault *existingObject);
  RescueStairSteppedFault *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescueStairSteppedFault *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
private:
  void EmptySelf();

  friend class RescueIJSurface;
};

#endif




