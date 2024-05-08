/*************************************************************************

        cNameValuePair.h

	      Keeps a list of named values.

        Rod Hanks               June 1998

****************************************************************************/

#ifndef cNameValuePair_H
#define cNameValuePair_H

#include "myHeaders.h"
class RCHString;

class cNameValuePair
{
protected:
  RCHString **names;
  RCHString **values;
  RESCUEINT64 allocated;
  RESCUEINT64 count;

  cNameValuePair();
  ~cNameValuePair();
  RESCUEINT64 NdxOf(const RESCUECHAR *name);
  void Archive(RescueContext *context, FILE *archiveFile);
  cNameValuePair(RescueContext *context, FILE *archiveFile);
public:
  RESCUECHAR *NthName(RESCUEINT64 ordinal);  // DO NOT delete the object returned.
  RESCUECHAR *NthValue(RESCUEINT64 ordinal); // DO NOT delete the object returned.
  RESCUEINT64 Count64(void) {return count;}
  RESCUEINT32 Count(void) {return (RESCUEINT32) count;}
  RESCUECHAR *NthName(RESCUEINT32 ordinal) {return NthName((RESCUEINT64) ordinal);}
  RESCUECHAR *NthValue(RESCUEINT32 ordinal) {return NthValue((RESCUEINT64) ordinal);}
  RESCUEINT32 Count(RESCUEBOOL throwIfTooBig);  
  RESCUEBOOL Contains(RESCUECHAR *name);
  void SetNameValuePair(const RESCUECHAR *name, const RESCUECHAR *value);
                                     // cNameValuePair makes copies of character buffers you
                                     // pass, so they can be on the stack or the heap.  They
                                     // remain your responsibility.
  RESCUECHAR *GetNameValuePair(const RESCUECHAR *name);  // DO NOT delete the object returned.

  friend class RescueModel;
  friend class RescueDataContainer;
};

#endif




