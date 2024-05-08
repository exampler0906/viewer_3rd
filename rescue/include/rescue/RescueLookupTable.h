/********************************************************************

  RescueLookupTable.h

  An item in a table of lookups for properties which translates to
  a two column table of floats. 

  Rod Hanks,  May 1997

*********************************************************************/
#ifndef RescueLookupTable_H
#define RescueLookupTable_H

#include <stdlib.h>
#include "myHeaders.h"
#include "RescueLookupItem.h"
#include "RCHString.h"

class RescueLookupTable:public RescueLookupItem
{
public:
  RescueLookupTable(RescueContext *context, RESCUEINT64 rowsIn, RESCUEFLOAT *tableIn)
                            :RescueLookupItem(context)
                            ,table(tableIn)
                            ,rows(rowsIn)
  {isA = R_RescueLookupTable;}
          // The array must be allocated on the heap and must be
          // rowsIn * 2 floats long.  It becomes the property of
          // the object.  Do not free it.
  ~RescueLookupTable() {delete table;}
  RESCUEFLOAT *Translation() {return table;}
  RESCUEINT64 TranslationLength64() {return rows * 2;}
  RESCUEINT32 TranslationLength() {return (RESCUEINT32) TranslationLength64();}
          // Do not free or change the array returned.
  RESCUEINT64 Rows() {return rows;}
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  RescueLookupTable(RescueContext *context, FILE *archiveFile);
  RESCUEFLOAT *table;
  RESCUEINT64 rows;

  friend class RescueLookup;
};

#endif




