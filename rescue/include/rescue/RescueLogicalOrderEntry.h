/********************************************************************

  RescueLogicalOrderEntry.h

  Base class for all objects that can be in a RescueLogicalOrder

  Rod Hanks,  June 2002

*********************************************************************/
#ifndef RescueLogicalOrderEntry_H
#define RescueLogicalOrderEntry_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"

class RescueLogicalOrderEntry:public RescueHistoryObject
{
public:
  RescueLogicalOrderEntry(RescueContext *context):RescueHistoryObject(context) {};
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  friend class RescueLogicalOrder;
};

#endif




