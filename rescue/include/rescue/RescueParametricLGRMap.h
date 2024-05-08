/********************************************************************

  RescueParametricLGRMap.h

  For explicit (unconstrained) LGRs, a map between parent and
  child.  Knowing the fondness of Rescue members for arrays as
  opposed to classes I have constructed this map as a set of
  RESCUEINTeger arrays.

  cellToMapCount, lgrIndx, lgrJndx, lgrKndx, parentNdx, parentCount
  contain data about LGR (refining) cells.

  parentMapCount, parentIndx, parentJndx, parentKndx, lgrNdx
  contain data about the parent geometry (the one that is one
  step up the ancestor tree, not necessarily the founding BUG).

  Each has an index RESCUEINTo the other so that the map can be traversed
  in both directions.

  Rod Hanks,  June 2003

*********************************************************************/
#ifndef RescueParametricLGRMap_H
#define RescueParametricLGRMap_H

#define DEFAULT_REFINED_REALLOC 100
#define DEFAULT_PARENT_REALLOC 100

class RescueGeometry;
class cSetRescueDataContainer;

class RescueParametricLGRMap
{
public:
  RescueParametricLGRMap(RescueGeometry *lgrGeometry,
                         RESCUEINT64 expectedRefined, 
                         RESCUEINT64 expectedParent,
                         RESCUEINT64 refinedRealloc = DEFAULT_REFINED_REALLOC,
                         RESCUEINT64 parentRealloc = DEFAULT_PARENT_REALLOC);
                            // The map belongs to the child.
  ~RescueParametricLGRMap();
                            // Don't delete the object.  It is deleted
                            // automatically when you drop the RescueGeometry
                            // that owns it.  To get rid of an existing
                            // map use ClearMap().
  void ClearMap();          // Resets the counts.
/*********************** Cell at a time *****************************/
  void SetCellToCell(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEINT64 parentCount,
                     RESCUEINT64 *pIndx, RESCUEINT64 *pJndx, RESCUEINT64 *pKndx);
  void SetCellToCell(RESCUEINT32 iNdx, RESCUEINT32 jNdx, RESCUEINT32 kNdx, RESCUEINT32 parentCount,
                     RESCUEINT32 *pIndx, RESCUEINT32 *pJndx, RESCUEINT32 *pKndx);
                            // Sets the description of one lgr cell
                            // and one or more parent cells that it
                            // refines.  It is assumed that the lgr
                            // cell is not already in the map.  The
                            // arrays are copied.  Pass jNdx and kNdx
                            // as -1 if not used.  pJndx and pKndx may
                            // be passed as 0.
  RESCUEINT64 ReadLGRCellToCell(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEINT64 allocated,
                                RESCUEINT64 *pIndx, RESCUEINT64 *pJndx, RESCUEINT64 *pKndx);
  RESCUEINT32 ReadLGRCellToCell(RESCUEINT32 iNdx, RESCUEINT32 jNdx, RESCUEINT32 kNdx, RESCUEINT32 allocated,
                                RESCUEINT32 *pIndx, RESCUEINT32 *pJndx, RESCUEINT32 *pKndx);
                            // iNdx, jNdx, kNdx are the index of the LGR
                            // cell being RESCUEINTerrogated.  The return is
                            // -1 if the cell is not in the map or the
                            // number of parent cells that it refines
                            // if it is in the map.  If nonzero,
                            // pIndx, pJndx, pKndx are pre-allocated arrays
                            // RESCUEINTo which the parent cell indexes will
                            // be written.  allocated is the number of
                            // parent cell indexes that could be written
                            // before writing off the end of the arrays.
                            // Pass jNdx and kNdx as -1 if not used.
  RESCUEINT64 ReadParentCellToCell(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEINT64 allocated,
                                   RESCUEINT64 *cIndx, RESCUEINT64 *cJndx, RESCUEINT64 *cKndx);
  RESCUEINT32 ReadParentCellToCell(RESCUEINT32 iNdx, RESCUEINT32 jNdx, RESCUEINT32 kNdx, RESCUEINT32 allocated,
                                   RESCUEINT32 *cIndx, RESCUEINT32 *cJndx, RESCUEINT32 *cKndx);
                            // iNdx, jNdx, kNdx are the index of the parent
                            // cell being RESCUEINTerrogated.  The return is
                            // -1 if the cell is not in the map or the
                            // number of child cells that refine it
                            // if it is in the map.  If nonzero,
                            // cIndx, cJndx, cKndx are pre-allocated arrays
                            // RESCUEINTo which the parent cell indexes will
                            // be written.  allocated is the number of
                            // child cell indexes that could be written
                            // before writing off the end of the arrays.
                            // Pass jNdx and kNdx as -1 if not used.
/************************** Reading ************************************/
  RESCUEINT64 CellToCellMapCount64() {return cellToCellMapCount;}
  RESCUEINT64 *LGRIndx64() {return lgrIndx;}
  RESCUEINT64 *LGRJndx64() {return lgrJndx;}
  RESCUEINT64 *LGRKndx64() {return lgrKndx;}
  RESCUEINT64 *ParentNdx64() {return parentNdx;}
  RESCUEINT64 *ParentCount64() {return parentCount;}
  RESCUEINT64 ParentMapCount64() {return parentMapCount;}
  RESCUEINT64 *ParentINdx64() {return parentIndx;}
  RESCUEINT64 *ParentJNdx64() {return parentJndx;}
  RESCUEINT64 *ParentKNdx64() {return parentKndx;}
  RESCUEINT64 *LGRNdx64() {return lgrNdx;}
                            // Access to the entire data structure.  You
                            // should not write to the arrays via this
                            // method, though I can't prevent it.
  RESCUEINT32 CellToCellMapCount() {return CellToCellMapCount(false);}
  RESCUEINT32 *LGRIndx() {return LGRIndx(false);}
  RESCUEINT32 *LGRJndx() {return LGRJndx(false);}
  RESCUEINT32 *LGRKndx() {return LGRKndx(false);}
  RESCUEINT32 *ParentNdx() {return ParentNdx(false);}
  RESCUEINT32 *ParentCount() {return ParentCount(false);}
  RESCUEINT32 ParentMapCount() {return ParentMapCount(false);}
  RESCUEINT32 *ParentINdx() {return ParentINdx(false);}
  RESCUEINT32 *ParentJNdx() {return ParentJNdx(false);}
  RESCUEINT32 *ParentKNdx() {return ParentKNdx(false);}
  RESCUEINT32 *LGRNdx() {return LGRNdx(false);}

  RESCUEINT32 CellToCellMapCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *LGRIndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *LGRJndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *LGRKndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *ParentNdx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *ParentCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 ParentMapCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *ParentINdx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *ParentJNdx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *ParentKNdx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *LGRNdx(RESCUEBOOL throwIfTooBig);
                            // Here I can't really provide equivalent RESCUEINT32
                            // functionality.  I am returning a copy of the array
                            // and the consumer must delete it when done.
  typedef enum
  {
    LGR_I_NDX,              // Identifies arrays for CopyArray.
    LGR_J_NDX,
    LGR_K_NDX,
    PARENT_NDX,
    PARENT_COUNT,
    PARENT_I_NDX,
    PARENT_J_NDX,
    PARENT_K_NDX,
    LGR_NDX
  } RescuePMLGRArrayName;
  void CopyArray(RescuePMLGRArrayName whichArray, RESCUEINT64 srcLowBound, RESCUEINT64 srcCount,
                 RESCUEINT64 *preAllocated, RESCUEINT64 destOffset);
  void CopyArray(RescuePMLGRArrayName whichArray, RESCUEINT32 srcLowBound, RESCUEINT32 srcCount,
                 RESCUEINT32 *preAllocated, RESCUEINT32 destOffset);
                            // Copies the named array RESCUEINTo the RESCUEINTeger
                            // array buffer passed in preAllocated, 
                            // especially handy for Java developers.
                            // srcLowBound is the first index to copy
                            // srcCount is the number to copy
                            // destOffset is the index of the first copied RESCUEINTeger
                            // There must be enough spaces in the preAllocated
                            // array to copy srcCount RESCUEINTegers.
/****************************** Writing **********************************/
                                    // In both methods, arrays which are not
                                    // needed (such as j and k indexes for
                                    // unstructured grids) or that are not
                                    // available (lgrNdx in some cases?)
                                    // may be passed as zero
  void Accept(RESCUEINT64 cellToCellCount,  // Sets the entire map at one go.
              RESCUEINT64 *lgrIndxIn,       // The arrays must have been allocated
              RESCUEINT64 *lgrJndxIn,       // with new RESCUEINT64[].  The array pointers
              RESCUEINT64 *lgrKndxIn,       // are copied.  Do not delete the arrays
              RESCUEINT64 *parentNdxIn,     // after passing them in.  Not a good
              RESCUEINT64 *parentCountIn,   // choice for Java developers.
              RESCUEINT64 parentMapCount,
              RESCUEINT64 *parentIndxIn,
              RESCUEINT64 *parentJndxIn,
              RESCUEINT64 *parentKndxIn,
              RESCUEINT64 *lgrNdx);
  void Accept(RESCUEINT32 cellToCellCount,  // Sets the entire map at one go.
              RESCUEINT32 *lgrIndxIn,       // The arrays must have been allocated
              RESCUEINT32 *lgrJndxIn,       // with new RESCUEINT32[].  Internally
              RESCUEINT32 *lgrKndxIn,       // arrays are RESCUEINT32 so Rescue can't
              RESCUEINT32 *parentNdxIn,     // copy the pointers.  However, for historical
              RESCUEINT32 *parentCountIn,   // reasons the arrays are deleted after
              RESCUEINT32 parentMapCount,   // they are used.  Do not delete or access
              RESCUEINT32 *parentIndxIn,    // the arrays after passing them in.
              RESCUEINT32 *parentJndxIn,
              RESCUEINT32 *parentKndxIn,
              RESCUEINT32 *lgrNdx);
  void Set(RESCUEINT64 cellToCellCount,     // Sets the entire map at one go.
              RESCUEINT64 *lgrIndxIn,       // The arrays are copied.  A better choice
              RESCUEINT64 *lgrJndxIn,       // for Java developers.
              RESCUEINT64 *lgrKndxIn,
              RESCUEINT64 *parentNdxIn,
              RESCUEINT64 *parentCountIn,
              RESCUEINT64 parentMapCount,
              RESCUEINT64 *parentIndxIn,
              RESCUEINT64 *parentJndxIn,
              RESCUEINT64 *parentKndxIn,
              RESCUEINT64 *lgrNdxIn);
  void Set(RESCUEINT32 cellToCellCount,     // Sets the entire map at one go.
              RESCUEINT32 *lgrIndxIn,       // The arrays are copied.  A better choice
              RESCUEINT32 *lgrJndxIn,       // for Java developers.
              RESCUEINT32 *lgrKndxIn,
              RESCUEINT32 *parentNdxIn,
              RESCUEINT32 *parentCountIn,
              RESCUEINT32 parentMapCount,
              RESCUEINT32 *parentIndxIn,
              RESCUEINT32 *parentJndxIn,
              RESCUEINT32 *parentKndxIn,
              RESCUEINT32 *lgrNdxIn);
  cSetRescueDataContainer *DataContainers();
                             // Will return 0 if properties have not
                             // been defined.
                             // DO NOT delete the class returned.
  cSetRescueDataContainer *DemandDataContainers();
                             // May return an empty container, but
                             // will never return 0.
                             // DO NOT delete the class returned.
  RESCUEBOOL AnyFileTruncated();
  void FindUniquePropertyNames(cSetString *container);
private:
  void Relink(RescueGeometry *lgrGeometryIn);
  RescueParametricLGRMap(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  void AddRefinedCell();
  void EnsureParentMapSize(RESCUEINT64 parentCountIn);

  RESCUEINT64 refinedReallocFactor; // Number to add to refined side if we run
                            // out while doing cell by cell writing.
  RESCUEINT64 refinedAllocated;     // Number of items allocated in the lgrIndx, 
                            // lgrJndx, lgrKndx, parentNdx, parentCount arrays.
  RESCUEINT64 cellToCellMapCount;   // The number of LGR cells that refine at
                            // least one parent cell.  Also the number
                            // of valid items in lgrIndx, lgrJndx, 
                            // lgrKndx, parentNdx, and parentCount.
  RESCUEINT64 *lgrIndx;             // I index of refining cell.
  RESCUEINT64 *lgrJndx;             // J index of refining cell.  Not used for 
                            // unstructured grids.
  RESCUEINT64 *lgrKndx;             // K index of refining cell.  Not used for
                            // unstructured grids.
  RESCUEINT64 *parentNdx;           // Index RESCUEINTo the parentIndx, parentJndx,
                            // parentKndx arrays for this cell.
  RESCUEINT64 *parentCount;         // Number of rows in parentIndx, parentJndx,
                            // parentKndx which pertain to this refining
                            // cell.
  /*******************************************************************/
  RESCUEINT64 parentReallocFactor;  // Number to add to the parent side if we
                            // run out while doing cell by cell writing.
  RESCUEINT64 parentAllocated;      // The number of items allocated in the
                            // parentIndx, parentJndx, parentKndx arrays.
  RESCUEINT64 parentMapCount;       // The number of valid cells in parentIndx,
                            // parentJndx, parentKndx.  Also the sum
                            // of all parentCount entries.
  RESCUEINT64 *parentIndx;          // I index of refined cell.
  RESCUEINT64 *parentJndx;          // J index of refined cell.  Not used for
                            // unstructured grids.
  RESCUEINT64 *parentKndx;          // K index of refined cell.  Not used for
                            // unstructured grids.
  RESCUEINT64 *lgrNdx;              // Index RESCUEINTo lgrIndx, lgrJndx, lgrKndx,
                            // parentNdx, parentCount for this parent
                            // cell.
  /*******************************************************************/
  RescueGeometry *lgrGeometry;
  cSetRescueDataContainer *properties;
  RESCUEINT64 propertyContainerId;

  friend class RescueGeometry;
};

#endif

