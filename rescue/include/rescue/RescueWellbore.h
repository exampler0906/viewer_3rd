/********************************************************************

  RescueWellbore.h

  The wellbore for RESCUE's data model.

  Rod Hanks,  May 1996

*********************************************************************/
#ifndef RESCUEWELLBORE_H
#define RESCUEWELLBORE_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
#include "RCHString.h"
#include "RescueWellboreSampling.h"
#include "RescueGrid.h"
#include "RescueTripletArray.h"
#include "cSetRescueWellboreSampling.h"
#include "cSetRescueWellboreSurface.h"
#include "cBagRescueWellboreCell.h"
#include "RescueQuadrupletArray.h"
class RescueModel;
class RescueOrientationLedger;

class RescueWellbore:public RescueHistoryObject
{
public:
  virtual ~RescueWellbore();
  RescueWellbore(RescueCoordinateSystem::Orientation orientation,
                 RescueModel *parentModel,
                 const RESCUECHAR *wellboreName,
                 RESCUEFLOAT missingValue,
                 RESCUEINT64 i_lowbound, RESCUEINT64 i_count);
  RescueWellbore(RescueCoordinateSystem::Orientation orientation,
                 RescueModel *parentModel,
                 const RESCUECHAR *wellboreName,
                 RESCUEFLOAT missingValue,
                 RESCUEFLOAT *quadrupletArray,
                 RESCUEINT64 i_lowbound, RESCUEINT64 i_count);
  // Create a new wellbore.
  // Delete with this->ParentModel()->DropRescueWellbore(this);
  RCHString *WellboreName() {return wellboreName;}
                                    // Do NOT drop the object returned.
  void SetWellboreName(RESCUECHAR *newName);

  RescueModel *ParentModel() {return parentModel;}
  RescueGrid *WellboreGrid() {return wellboreGrid;}
  RescueQuadrupletArray *WellboreGeometry() {return wellboreGeometry;}

  RESCUEINT64 WellboreSamplingCount64() {return sampling->Count64();}
  RESCUEINT32 WellboreSamplingCount() {return sampling->Count();}
  RescueWellboreSampling *NthRescueWellboreSampling(RESCUEINT64 zeroBasedOrdinal) 
                  {return sampling->NthObject(zeroBasedOrdinal);}
  RescueWellboreSampling *WellboreSamplingIdentifiedBy(RESCUEINT64 identifier)
                  {return sampling->ObjectIdentifiedBy(identifier);}
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescueWellboreSampling(RescueWellboreSampling *unitToDrop) 
                          {return ((*sampling) -= unitToDrop);}

  RESCUEINT64 WellboreSurfaceCount64() {return surfaceIntersections->Count64();}
  RESCUEINT32 WellboreSurfaceCount() {return surfaceIntersections->Count();}
  RescueWellboreSurface *NthRescueWellboreSurface(RESCUEINT64 zeroBasedOrdinal) 
                  {return surfaceIntersections->NthObject(zeroBasedOrdinal);}
                                    // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescueWellboreSurface(RescueWellboreSurface *surfaceToDrop) 
                          {return ((*surfaceIntersections) -= surfaceToDrop);}
  cBagRescueWellboreCell *CellIntersections() {return cellIntersections;}
  RESCUEBOOL AnyFileTruncated();            // Checks all subfiles in the instantiated model.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  RescueWellbore(RescueContext *context, FILE *archiveFile);
  void Archive(FILE *archiveFile);
  void Relink(RescueObject *parentObject);
  void Dispose(); 
  void SwapAxis();
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RCHString *wellboreName;
  RescueModel *parentModel;
  cSetRescueWellboreSampling *sampling;
  cSetRescueWellboreSurface *surfaceIntersections;
  cBagRescueWellboreCell *cellIntersections;
  RescueGrid *wellboreGrid;                   // 1d open grid.
  RescueQuadrupletArray *wellboreGeometry;

  friend class RescueWellboreSampling;
  friend class cSetRescueWellbore;
  friend class RescueWellboreSurface;
  friend class RescueWellboreCell;
  friend class RescueWellboreProperty;
  friend class RescueModel;
  friend class cSetRescueWellboreCell;
};

#endif




