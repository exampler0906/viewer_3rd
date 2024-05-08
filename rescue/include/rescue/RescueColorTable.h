/********************************************************************

  RescueColorTable.h

  A table which specifies how color relates to property values.

  Rod Hanks,  May, 1999

*********************************************************************/
#ifndef RESCUECOLORTABLE_H
#define RESCUECOLORTABLE_H

#include "myHeaders.h"
#include "RescueObject.h"
class RCHString;
class RescueColor;
class RescueModel;

class RescueColorTable:public RescueObject
{
public:
  typedef enum {ALL, RED, GREEN, BLUE} Role;
  RescueColorTable(RescueModel *parentModel, RESCUEINT64 probableRows, Role role = ALL);
                                    // Create RescueColorTables here, then either add them
                                    // to ParentModel's RescueColorTableList or assign them
                                    // to some RescueProperty (but DON'T do both).
  RescueColorTable(RescueColorTable &other);
                                    // Copy constructor in case you WANT to do both.
  ~RescueColorTable();
  void ResetColorTable();           // Sets number of color rows to 0.  Use just before re-describing
                                    // the color table.
  RESCUEINT64 ColorRowCount64() {return rowCount;}
  RESCUEINT32 ColorRowCount() {return (RESCUEINT32) rowCount;}
  RESCUEINT32 ColorRowCount(RESCUEBOOL throwIfTooBig);
                                    // Returns the number of color rows available.
  void GetColorRow(RESCUEINT64 zeroBasedOrdinal, RescueColor **lowColor, RescueColor **highColor,
                                         RESCUEBOOL &haveLowHint, RESCUEFLOAT &lowHint,
                                         RESCUEBOOL &haveHighHint, RESCUEFLOAT &highHint);
                                    // Returns information for a single row where 
                                    //  0 <= zeroBasedOrdinal < ColorRowCount().
                                    // lowColor will not be 0.  If only lowColor is present, then it
                                    // is used for the indicated value range.  If both lowColor
                                    // and highColor are present, a continuous color between those
                                    // two colors should be used for that value range.  DO NOT
                                    // delete the RescueColor objects returned, they remain the
                                    // property of RescueColorTable.
                                    // If haveLowHint == FALSE, the color is valid down to an infinitely
                                    // low value, otherwise it is valid down to lowHint.
                                    // If haveHighHint == FALSE, the color is valid up to an infinitely
                                    // high value, otherwise it is valid up to highHint.
  // **************************************************************************************************
  //
  // Color rows should be defined from low to high values.  If the role is not ALL, only the RED,
  // GREEN, or BLUE component of the RescueColor is used.
  //
  // **************************************************************************************************
  void AddColorRow(RESCUEFLOAT lowValue, RESCUEFLOAT highValue, RescueColor *color);
                                    // Define a color for a definite range of values.  Both low and
                                    // high values must be given.  The color is copied, so it should
                                    // be freed by the application after use. 
  void AddColorRow(RESCUEFLOAT lowValue, RESCUEFLOAT highValue, RescueColor *lowColor, RescueColor *highColor);
                                    // Define a color range for a definite range of values.  Both
                                    // low and high values must be given.  The color is copied, so
                                    // it should be freed by the application after use. Applications
                                    // should use a continuous color value with straight-line extrapolation
                                    // between those points.
  void AddColorRow(RESCUEBOOL lowToInfinite, RESCUEFLOAT lowValue, RESCUEBOOL highToInfinite, RESCUEFLOAT highValue, RescueColor *color);
                                    // Define a color for a range of values. lowToInfinite is TRUE if
                                    // the low value extends downwards toward infinity, FALSE if it
                                    // extends down to lowValue.  highToInfinite is TRUE if the high
                                    // value extends upwards toward infinity.
                                    // The color is copied, so it should
                                    // be freed by the application after use. 
  void AddColorRow(RESCUEBOOL lowToInfinite, RESCUEFLOAT lowValue, RESCUEBOOL highToInfinite, RESCUEFLOAT highValue, RescueColor *lowColor, RescueColor *highColor);
                                    // Define a color range for a definite range of values.  The color is 
                                    // copied, so it should be freed by the application after use. 

  virtual RESCUEBOOL IsLoaded() {return isLoaded;}
                                    // Returns true if data has been read from the file or
                                    // for new tables that have never been archived.
  RESCUEBOOL FileTruncated();
  RESCUEBOOL Load();
  RESCUEBOOL Unload();
  RESCUEBOOL HasChanged() {return hasChanged;}
                                    // Returns true if the data on the disk is known (not due
                                    // to version but due to actions of the current process)
                                    // to be different from data in memory, including new
                                    // tables never archived.
  void MarkChanged() {hasChanged = TRUE;}
  RESCUEINT32 Version(RESCUEBOOL reload = FALSE); // These methods return a version number for the file which
                                    // starts at zero and increments each time the file is
                                    // written.  Applications can use this as a quick check to
                                    // see if the file has been updated (by saving the version
                                    // number AFTER a write operation). If reload is TRUE the library
                                    // always goes back to the disk to read the version number,
                                    // in case it has been recently changed.  Therefore, the
                                    // version number returned is the version which would be
                                    // available if the data were loaded now, not the version which
                                    // IS loaded now (if any). If false, the version number returned
                                    // is the version of the last data loaded (if any).
private:
  RescueColorTable(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentModel);

  virtual void ArchiveData(FILE *archiveFile);
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  virtual void DropMemory();
  RESCUEBOOL ReadData(RESCUECHAR *basePathName, RESCUEBOOL versionOnly = FALSE);
  RESCUEBOOL WriteData();
  void RescueDeleteFile();
  void InsureCapacity();

  RESCUEINT32 colorVersion;

  Role role;
  RESCUEINT64 rowCount;
  RESCUEINT64 allocated;
  RescueColor **lowColor;
  RescueColor **highColor;
  RESCUEBOOL *haveLowHint;
  RESCUEFLOAT *lowHint;
  RESCUEBOOL *haveHighHint;
  RESCUEFLOAT *highHint;
  RESCUEBOOL hasChanged;
  RESCUEBOOL isLoaded;
  RescueModel *parentModel;

  friend class RescueColorTableList;
  friend class RescueProperty;
};

#endif



