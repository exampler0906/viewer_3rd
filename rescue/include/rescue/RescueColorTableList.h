/********************************************************************

  RescueColorTableList.h

  An association between a color table and a property type.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RESCUECOLORTABLELIST_H
#define RESCUECOLORTABLELIST_H

#include "myHeaders.h"
#include "RescueObject.h"
class RCHString;
class RescueColorTable;

class RescueColorTableList:public RescueObject
{
public:
  RescueColorTableList(RescueContext *context, RESCUEINT64 probableCount = 10);
  ~RescueColorTableList();
  RescueColorTable *TableFor(RESCUECHAR *typeName);
                                            // Returns 0 if no color table currently
                                            // defined for that name.
  RESCUEBOOL AddTableFor(RESCUECHAR *typeName, RescueColorTable *table);
                                            // The table becomes the property of
                                            // RescueColorTableList.  DO NOT delete it.
                                            // DO NOT pass a RescueColorTable that is already
                                            // owned by another typeName or is already being
                                            // used by some specific property.  If you want
                                            // to do this use RescueColorTable's copy
                                            // constructor and pass a copy.
                                            // If a different color table was already
                                            // defined for this type name, it is deleted
                                            // and any application pointers to it become
                                            // invalid.  Returns TRUE if the typeName did
                                            // already exist, false otherwise.
                                            // typeName DOES NOT become the property of
                                            // RescueColorTableList.
  RESCUEBOOL DeleteTableFor(RESCUECHAR *typeName);      // Returns TRUE if a table for that type was
                                            // already defined.  If so, it is deleted and
                                            // any application pointers to it become invalid.
                            // When you delete an existing color table, the file associated
                            // with the color table is deleted.  If your actual
                            // intention was to transfer the color table to a new property
                            // that is okay.  When the
                            // table is next unloaded it will be written out again.  You
                            // may want to use RescueColorTable->MarkChanged().
  RESCUEINT64 TypeCount64() {return count;}
  RESCUEINT32 TypeCount() {return (RESCUEINT32) count;}
  RESCUECHAR **TypeNames() {return typeNames;}    // DO NOT delete the array returned.
private:
  RescueColorTableList(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parentModel);
  RESCUEINT64 allocated;
  RESCUEINT64 count;
  RESCUECHAR **typeNames;
  RescueColorTable **tables;

  friend class RescueModel;
};

#endif


