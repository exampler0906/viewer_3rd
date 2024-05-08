/********************************************************************

  RescueLookupItem.h

  An item in a table of lookups for properties. 

  Rod Hanks,  May 1997

*********************************************************************/
#ifndef RescueLookupItem_H
#define RescueLookupItem_H

#include "myHeaders.h"

class RescueLookupItem:public RescueObject
{
public:
  RescueLookupItem(RescueContext *context):RescueObject(context) {}
  virtual ~RescueLookupItem() {}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(RescueContext *context, FILE *archiveFile)=0;
  friend class RescueLookup;
};

#endif




