/********************************************************************

  RescueInterfaceSurfaceDesc.h

  A map between faces of refining cells and neighboring cells of
  other grids.  The other grids are either the BUG or some LGR
  which refines that BUG.

  For efficiency, the map is made of two sets of arrays.  One set
  of arrays gives faces of the lgrGeometry and points into the
  other set of arrays, which gives cells of other RescueGeometry
  objects.

  The description of faces for the lgrGeometry . . .
  RESCUEINT64 FaceCount();    // The number of items in each of the following arrays.
  RESCUEINT64 *FaceIndx();    // The I index of the cell containing the face.
  RESCUEINT64 *FaceJndx();    // The J index of the cell containing the face.
  RESCUEINT64 *FaceKndx();    // The K index of the cell containing the face.
  RESCUEINT64 *FaceNdx();     // The face index number (see Cell Face Numbering)
  RESCUEINT64 *CellNdx();     // The index into the cell description arrays for the
                      // first cell that is associated with this face.
  RESCUEINT64 *CellCount()    // The number of cells in the cell description arrays
                      // associated with this face.

  The description of the cells . . .

  RESCUEINT64 CellMapCount(); // The number of items in the following arrays.
  RESCUEINT64 *CellRef();     // Reference ID of the grid containing the cell.  
                      // The id of the BUG is 0.
  RESCUEINT64 *CellIndx();    // The I index of the cell.
  RESCUEINT64 *CellJndx();    // The J index of the cell.
  RESCUEINT64 *CellKndx();    // The K index of the cell.
  RESCUEINT64 *FaceRowNdx();  // The index of row in the face description of
                      // the face associated with this cell.

  Rod Hanks,  June 2003

*********************************************************************/
#ifndef RescueInterfaceSurfaceDesc_H
#define RescueInterfaceSurfaceDesc_H

#define DEFAULT_FACE_REALLOC 100
#define DEFAULT_CELL_REALLOC 100

class RescueGeometry;
class cSetRescueDataContainer;

class RescueInterfaceSurfaceDesc
{
public:
  RescueInterfaceSurfaceDesc(RescueGeometry *lgrGeometryIn,
                             RESCUEBOOL isExteriorIn,
                             RESCUEINT64 expectedFaces,
                             RESCUEINT64 expectedCells,
                             RESCUEINT64 facesRealloc = DEFAULT_FACE_REALLOC,
                             RESCUEINT64 cellsRealloc = DEFAULT_CELL_REALLOC);
                            // The surface description belongs to
                            // the refining LGR (the child).
  ~RescueInterfaceSurfaceDesc();
                            // Don't delete the object.  It is deleted
                            // automatically when you drop the RescueGeometry
                            // that owns it.  You can also delete it with
                            // RescueGeometry::DropInterfaceSurface().
/************************** Face at a time ******************************/
  void SetIsExterior(RESCUEBOOL newState) {isExterior = newState;}
  void SetFaceToCell(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEINT64 faceNdx,
                     RESCUEINT64 cellCount, RESCUEINT64 *cellRef, 
                     RESCUEINT64 *cIndx, RESCUEINT64 *cJndx, RESCUEINT64 *cKndx);
  void SetFaceToCell(RESCUEINT32 iNdx, RESCUEINT32 jNdx, RESCUEINT32 kNdx, RESCUEINT32 faceNdx,
                     RESCUEINT32 cellCount, RESCUEINT32 *cellRef, 
                     RESCUEINT32 *cIndx, RESCUEINT32 *cJndx, RESCUEINT32 *cKndx);
                            // Sets the description of one face and
                            // one or more cells that are in contact.
                            // pass -1 for jNdx and kNdx of they are
                            // not used, 0 for cJndx, cKndx if not used.
  RESCUEINT64 ReadFaceToCell(RESCUEINT64 iNdx, RESCUEINT64 jNdx, RESCUEINT64 kNdx, RESCUEINT64 faceNdx,
                             RESCUEINT64 allocated, RESCUEINT64 *cellRef, 
                             RESCUEINT64 *cIndx, RESCUEINT64 *cJndx, RESCUEINT64 *cKndx);
  RESCUEINT32 ReadFaceToCell(RESCUEINT32 iNdx, RESCUEINT32 jNdx, RESCUEINT32 kNdx, RESCUEINT32 faceNdx,
                             RESCUEINT32 allocated, RESCUEINT32 *cellRef, 
                             RESCUEINT32 *cIndx, RESCUEINT32 *cJndx, RESCUEINT32 *cKndx);
                            // The first four arguments specify the
                            // face row.  The return is -1 if not found,
                            // or the number of neighbor cells for that
                            // map in the description.  If nonzero,
                            // cellRef, cIndx, cJndx, cKndx are
                            // pre-allocated arrays into which the
                            // cell information can be written, allocated
                            // is the maximum number of cell rows that
                            // could be written.
                            // pass -1 for jNdx and kNdx of they are
                            // not used, 0 for cJndx, cKndx if not used.
  RESCUEINT64 ReadCellToFace(RESCUEINT64 cRef, RESCUEINT64 cIndx, RESCUEINT64 cJndx, RESCUEINT64 cKndx, 
                             RESCUEINT64 allocated,
                             RESCUEINT64 *iNdx, RESCUEINT64 *jNdx, RESCUEINT64 *kNdx, RESCUEINT64 *faceNdx);
  RESCUEINT32 ReadCellToFace(RESCUEINT32 cRef, RESCUEINT32 cIndx, RESCUEINT32 cJndx, RESCUEINT32 cKndx, 
                             RESCUEINT32 allocated,
                             RESCUEINT32 *iNdx, RESCUEINT32 *jNdx, RESCUEINT32 *kNdx, RESCUEINT32 *faceNdx);
                            // cRef, cIndx, cJndx, cKndx describe a cell.
                            // Pass -1 for cJndx and cKndx if not used.
                            // Returns the number of faces in the desc
                            // that touch that cell.  Pass jNdx = 0 and
                            // kNdx = 0 if not used.  allocated is the
                            // number of faces that can be returned in
                            // the pre-allocated arrays.
/************************** Reading ************************************/
  RESCUEBOOL IsExterior() {return isExterior;}
  RESCUEINT64 FaceCount64()    {return faceCount;}
  RESCUEINT64 *FaceIndx64()    {return faceIndx;}
  RESCUEINT64 *FaceJndx64()    {return faceJndx;}
  RESCUEINT64 *FaceKndx64()    {return faceKndx;}
  RESCUEINT64 *FaceNdx64()     {return faceNdx;}
  RESCUEINT64 *CellNdx64()     {return cellNdx;}
  RESCUEINT64 *CellCount64()   {return cellCount;}
  RESCUEINT64 CellMapCount64() {return cellMapCount;}
  RESCUEINT64 *CellRef64()     {return cellRef;}
  RESCUEINT64 *CellIndx64()    {return cellIndx;}
  RESCUEINT64 *CellJndx64()    {return cellJndx;}
  RESCUEINT64 *CellKndx64()    {return cellKndx;}
  RESCUEINT64 *FaceRowNdx64()  {return faceRowNdx;}
                            // Access to the entire data structure.  You
                            // should not write to the arrays via this
                            // method, though I can't prevent it.
  RESCUEINT32 FaceCount() {return FaceCount(false);}
  RESCUEINT32 *FaceIndx() {return FaceIndx(false);}
  RESCUEINT32 *FaceJndx() {return FaceJndx(false);}
  RESCUEINT32 *FaceKndx() {return FaceKndx(false);}
  RESCUEINT32 *FaceNdx() {return FaceNdx(false);}
  RESCUEINT32 *CellNdx() {return CellNdx(false);}
  RESCUEINT32 *CellCount() {return CellCount(false);}
  RESCUEINT32 CellMapCount() {return CellMapCount(false);}
  RESCUEINT32 *CellRef() {return CellRef(false);}
  RESCUEINT32 *CellIndx() {return CellIndx(false);}
  RESCUEINT32 *CellJndx() {return CellJndx(false);}
  RESCUEINT32 *CellKndx() {return CellKndx(false);}
  RESCUEINT32 *FaceRowNdx() {return FaceRowNdx(false);}
 
  RESCUEINT32 FaceCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *FaceIndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *FaceJndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *FaceKndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *FaceNdx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *CellNdx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *CellCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 CellMapCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *CellRef(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *CellIndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *CellJndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *CellKndx(RESCUEBOOL throwIfTooBig);
  RESCUEINT32 *FaceRowNdx(RESCUEBOOL throwIfTooBig);
                            // Here I can't really provide equivalent RESCUEINT32
                            // functionality.  I am returning a copy of the array
                            // and the consumer must delete it when done.
  typedef enum
  {
    FACE_I_NDX,               // Identifies arrays for CopyArray.
    FACE_J_NDX,
    FACE_K_NDX,
    FACE_NDX,
    CELL_NDX,
    CELL_COUNT,
    CELL_REF,
    CELL_I_NDX,
    CELL_J_NDX,
    CELL_K_NDX,
    FACE_ROW_NDX
  } RescueISDArrayName;
  void CopyArray(RescueISDArrayName whichArray, RESCUEINT64 srcLowBound, RESCUEINT64 srcCount,
                 RESCUEINT64 *preAllocated, RESCUEINT64 destOffset);
  void CopyArray(RescueISDArrayName whichArray, RESCUEINT32 srcLowBound, RESCUEINT32 srcCount,
                 RESCUEINT32 *preAllocated, RESCUEINT32 destOffset);
                            // Copies the named array into the integer
                            // array buffer passed in preAllocated, 
                            // especially handy for Java developers.
                            // srcLowBound is the first index to copy
                            // srcCount is the number to copy
                            // destOffset is the index of the first copied integer
                            // There must be enough spaces in the preAllocated
                            // array to copy srcCount integers.
/****************************** Writing **********************************/
                                    // In both methods, arrays which are not
                                    // needed (such as j and k indexes for
                                    // unstructured grids) may be passed as zero.
  void Accept(RESCUEINT64 faceCountIn,      // Sets the entire map at one go.
              RESCUEINT64 *faceIndxIn,      // The arrays must have been allocated
              RESCUEINT64 *faceJndxIn,      // with new RESCUEINT64[].  The array pointers
              RESCUEINT64 *faceKndxIn,      // are copied.  Do not delete the arrays
              RESCUEINT64 *faceNdxIn,       // after passing them in.  Not a good
              RESCUEINT64 *cellNdxIn,       // choice for Java developers.
              RESCUEINT64 *cellCountIn,
              RESCUEINT64 cellMapCountIn,
              RESCUEINT64 *cellRefIn,
              RESCUEINT64 *cellINdxIn,
              RESCUEINT64 *cellJNdxIn,
              RESCUEINT64 *cellKNdxIn,
              RESCUEINT64 *faceRowNdxIn);
  void Accept(RESCUEINT32 faceCountIn,      // Sets the entire map at one go.
              RESCUEINT32 *faceIndxIn,      // The arrays must have been allocated
              RESCUEINT32 *faceJndxIn,      // with new RESCUEINT32[].  The are not
              RESCUEINT32 *faceKndxIn,      // copied, but they are deleted after use.  
              RESCUEINT32 *faceNdxIn,       // Do not delete or access the arrays
              RESCUEINT32 *cellNdxIn,       // after passing them in.  Not a good
              RESCUEINT32 *cellCountIn,     // choice for Java developers
              RESCUEINT32 cellMapCountIn,
              RESCUEINT32 *cellRefIn,
              RESCUEINT32 *cellINdxIn,
              RESCUEINT32 *cellJNdxIn,
              RESCUEINT32 *cellKNdxIn,
              RESCUEINT32 *faceRowNdxIn);
  void Set(RESCUEINT64 faceCountIn,         // Sets the entire map at one go.
              RESCUEINT64 *faceIndxIn,      // The arrays are copied.  A better
              RESCUEINT64 *faceJndxIn,      // choice for Java developers.
              RESCUEINT64 *faceKndxIn,      
              RESCUEINT64 *faceNdxIn,      
              RESCUEINT64 *cellNdxIn,      
              RESCUEINT64 *cellCountIn,
              RESCUEINT64 cellMapCountIn,
              RESCUEINT64 *cellRefIn,
              RESCUEINT64 *cellINdxIn,
              RESCUEINT64 *cellJNdxIn,
              RESCUEINT64 *cellKNdxIn,
              RESCUEINT64 *faceRowNdxIn);
  void Set(RESCUEINT32 faceCountIn,         // Sets the entire map at one go.
              RESCUEINT32 *faceIndxIn,      // The arrays are copied.  A better
              RESCUEINT32 *faceJndxIn,      // choice for Java developers.
              RESCUEINT32 *faceKndxIn,      
              RESCUEINT32 *faceNdxIn,      
              RESCUEINT32 *cellNdxIn,      
              RESCUEINT32 *cellCountIn,
              RESCUEINT32 cellMapCountIn,
              RESCUEINT32 *cellRefIn,
              RESCUEINT32 *cellINdxIn,
              RESCUEINT32 *cellJNdxIn,
              RESCUEINT32 *cellKNdxIn,
              RESCUEINT32 *faceRowNdxIn);

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
  RescueInterfaceSurfaceDesc(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);
  void Relink(RescueGeometry *lgrGeometryIn);

  RescueGeometry *lgrGeometry;
  RESCUEINT64 facesAllocated;
  RESCUEINT64 cellsAllocated;
  RESCUEINT64 facesReallocFactor;
  RESCUEINT64 cellsReallocFactor;

  RESCUEBOOL isExterior;    // Is either a description of the
                            // exterior surface of the grid or
                            // of some interior space.
  RESCUEINT64 faceCount;            // Number of faces of this grid in
                            // the description.  Applies to
                            // faceIndx, faceJndx, faceKndx,
                            // faceNdx, cellNdx, cellCount.
  RESCUEINT64 *faceIndx;            // I index of cell of each face.
  RESCUEINT64 *faceJndx;            // J index of cell of each face.
  RESCUEINT64 *faceKndx;            // K index of cell of each face.
  RESCUEINT64 *faceNdx;             // values are 1 - positive I face,
                            //            2 - positive J face,
                            //            3 - positive K face,
                            //           -1 - negative I face,
                            //           -2 - negative J face,
                            //           -3 - negative K face.
  RESCUEINT64 *cellNdx;             // First index on cell side of
                            // neighbor cells for this face.
  RESCUEINT64 *cellCount;           // Number of neighbor cells for
                            // this face.
  RESCUEINT64 cellMapCount;         // Number of face/cell interactions
                            // in the list.  Applies to cellRef,
                            // cellIndx, cellJndx, cellKndx, faceRowNdx.
  RESCUEINT64 *cellRef;             // Reference ID of the grid containing
                            // the cell.  The id of the BUG is 0.
  RESCUEINT64 *cellIndx;            // I index of the cell.
  RESCUEINT64 *cellJndx;            // J index of the cell.
  RESCUEINT64 *cellKndx;            // K index of the cell.
  RESCUEINT64 *faceRowNdx;          // Cross index of this row into the
                            // face rows.
  cSetRescueDataContainer *properties;
  RESCUEINT64 propertyContainerId;

  friend class cSetRescueInterfaceSurfaceDesc;
};

#endif


