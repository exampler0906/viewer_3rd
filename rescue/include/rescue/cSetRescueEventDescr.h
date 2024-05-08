/*************************************************************************

        cSetRescueEventDescr.h

	Keeps a list of pointers to some RescueEventDescr.

        Rod Hanks               January 18th, 1995	 /  August 1996

****************************************************************************/

#ifndef cSetRescueEventDescr_H
#define cSetRescueEventDescr_H

#include "boolSupport.h"
#include <stdlib.h>


class RescueEventDescr;
class RescueContext;

class cSetRescueEventDescr
{
protected:
  RescueEventDescr **objects;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

public:
  cSetRescueEventDescr();
  ~cSetRescueEventDescr();
  void operator+=(RescueEventDescr *newObject);
  RESCUEBOOL operator-=(RescueEventDescr *existingObject);
  RESCUEBOOL operator-=(RESCUEINT64 ndx);
  RescueEventDescr *NthObject(RESCUEINT64 ordinal);
  RescueEventDescr *ObjectNamed(RESCUECHAR *nameIn);
  RescueEventDescr *ObjectIdentifiedBy(RESCUEINT64 identifier);
  RESCUEINT64 Count64(void);
  RESCUEINT32 Count(void);
  RESCUEBOOL operator-=(RESCUEINT32 ndx) {return (*this) -=((RESCUEINT64) ndx);}
  RescueEventDescr *NthObject(RESCUEINT32 ordinal) {return NthObject((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  void EmptySelf(void);
  void Archive(RescueModel *model, RescueContext *context, FILE *archiveFile);
  void UnArchive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueObject *parent);
};

#endif



