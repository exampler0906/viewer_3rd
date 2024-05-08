/*************************************************************************

        cBagRescueGeobodyPart.h

	Keeps a list of pointers to RescueGeobodyPart.

        Rod Hanks               December 15th, 1995	 / August 1996

****************************************************************************/

#ifndef cBagRescueGeobodyPart_H
#define cBagRescueGeobodyPart_H

#include "boolSupport.h"
#include "RescueTree.h"
class RescueGeobodyPart;

class cBagRescueGeobodyPart
{
protected:
  RescueTree *tree;
public:
  cBagRescueGeobodyPart();
  ~cBagRescueGeobodyPart();
  void operator+=(RescueGeobodyPart *newObject);
  RESCUEBOOL operator-=(RescueGeobodyPart *existingObject);
  RescueGeobodyPart *NthObject(RESCUEINT64 ordinal);
  RESCUEINT64 Count64(void) {return tree->Count();}
  RESCUEINT32 Count(void) {return (RESCUEINT32) tree->Count();}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RescueGeobodyPart *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
};

#endif


