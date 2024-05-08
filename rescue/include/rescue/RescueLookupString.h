/********************************************************************

  RescueLookupString.h

  An item in a table of lookups for properties which translates to
  a string. 

  Rod Hanks,  May 1997

*********************************************************************/
#ifndef RescueLookupString_H
#define RescueLookupString_H

#include "myHeaders.h"
#include "RescueLookupItem.h"
#include "RCHString.h"

class RescueLookupString:public RescueLookupItem
{
public:
  ~RescueLookupString();
  RescueLookupString(RescueContext *context, RESCUECHAR *translationString);
  RCHString *Translation() {return translation;}
                              // Do NOT delete the returned object.

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescueLookupString(RescueContext *context, FILE *archiveFile);
  RCHString *translation;

  friend class RescueLookup;
};

#endif




