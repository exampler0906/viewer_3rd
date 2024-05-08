/********************************************************************

  RescueWellboreCell.h

  The record of an intersect between a wellbore and a grid cell.

  Rod Hanks,  January 1997

*********************************************************************/
#ifndef RESCUEWellboreCell_H
#define RESCUEWellboreCell_H

#include "myHeaders.h"
class RescueWellbore;
class RescueGeometry;

class RescueWellboreCell:public RescueObject
{
public:
  RescueWellbore *Wellbore() {return wellbore;}
  RescueGeometry *Geometry() {return geometry;}
  void CellIndex(RescueGeometry *geometry, RESCUEINT64 &i, RESCUEINT64 &j, RESCUEINT64 &k);
  void CellIndex(RescueGeometry *geometry, RESCUEINT64 *returnArray, RESCUEINT64 returnArraySize);
  void CellIndex(RescueGeometry *geometry, RESCUEINT32 &i, RESCUEINT32 &j, RESCUEINT32 &k, bool throwIfTooBig);
  void CellIndex(RescueGeometry *geometry, RESCUEINT32 *returnArray, RESCUEINT32 returnArraySize, bool throwIfTooBig);
          // Pass an array with at least 3 members.  array[0] = i,
          // array[1] = j, array[2] = k.

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
  ~RescueWellboreCell();
private:
  virtual void Archive(FILE *archiveFile);
  RescueWellboreCell(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void SetWellbore(RescueWellbore *wellboreIn) {wellbore = wellboreIn;}
  RescueWellboreCell(RescueGeometry *geometryIn,
                     RescueWellbore *wellboreIn,
                     RESCUEINT64 cellNumberIn);
  RescueWellbore *wellbore;
  RescueGeometry *geometry;
  RESCUEINT64 cellNumber;

  RESCUEINT64 wellboreID;   // used only during relinking.

  friend class RescueWellbore;
  friend class cSetRescueWellboreCell;
  friend class RescueGeometry;
};

#endif




