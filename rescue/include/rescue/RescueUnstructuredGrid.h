/********************************************************************

  RescueUnstructuredGrid.h

  A geometry handler for RESCUE unstructured grids.
  See description of each array in the private section of
  the header.

  Rod Hanks,  June 2003

*********************************************************************/
#ifndef RescueUnstructuredGrid_H
#define RescueUnstructuredGrid_H

class RescueGeometry;

class RescueUnstructuredGrid
{
public:
  ~RescueUnstructuredGrid();
                            // Don't delete the object.  It is deleted
                            // automatically when you drop the RescueGeometry
                            // that owns it. 
/***********************************  Structure at a time *******************************/
  void AddVertices(RESCUEINT64 count, RESCUEFLOAT *vertexXIn, RESCUEFLOAT *vertexYIn, RESCUEFLOAT *vertexZin);
                            // Vertices are added to existing.  No checking
                            // for collisions.
  void AddFace(RESCUEINT64 count, RESCUEINT64 *vertexIndices);
  void AddFace(RESCUEINT32 count, RESCUEINT32 *vertexIndices);
                            // Add a single face by giving a list of vertices that
                            // belong to it, as indexes into vertexX,Y,Z.
  void AddCell(RESCUEINT64 cellCenterNdxIn, RESCUEINT64 kLayerIn,
               RESCUEINT64 count, RESCUEINT64 *faceIndices);
  void AddCell(RESCUEINT32 cellCenterNdxIn, RESCUEINT32 kLayerIn,
               RESCUEINT32 count, RESCUEINT32 *faceIndices);
                            // Add a single cell by giving a list of faces that
                            // belong to it, as indexes into faceVertexNdx,faceVertexCount.
/*********************************** Reading Vertices ***********************************/
  RESCUEINT64 VertexCount64() {return vertexCount;}
  RESCUEINT32 VertexCount() {return (RESCUEINT32) vertexCount;}
  RESCUEFLOAT NthVertexX(RESCUEINT64 zeroBasedOrdinal);
  RESCUEFLOAT NthVertexY(RESCUEINT64 zeroBasedOrdinal);
  RESCUEFLOAT NthVertexZ(RESCUEINT64 zeroBasedOrdinal);
  RESCUEFLOAT *VerticesX() {return vertexX;}      // DO NOT delete the array.
  RESCUEFLOAT *VerticesY() {return vertexY;}      // DO NOT delete the array.
  RESCUEFLOAT *VerticesZ() {return vertexZ;}      // DO NOT delete the array.
  RESCUEINT64 VerticesXLength64() {return ((vertexX == 0) ? 0 : VertexCount64());}
  RESCUEINT64 VerticesYLength64() {return ((vertexY == 0) ? 0 : VertexCount64());}
  RESCUEINT64 VerticesZLength64() {return ((vertexZ == 0) ? 0 : VertexCount64());}
  RESCUEINT32 VerticesXLength() {return ((vertexX == 0) ? 0 : VertexCount());}
  RESCUEINT32 VerticesYLength() {return ((vertexY == 0) ? 0 : VertexCount());}
  RESCUEINT32 VerticesZLength() {return ((vertexZ == 0) ? 0 : VertexCount());}
  void CopyVertices(RESCUEINT64 lowNdx, RESCUEINT64 count, 
                    RESCUEFLOAT *preAllocatedX, RESCUEFLOAT *preAllocatedY, RESCUEFLOAT *preAllocatedZ, 
                    RESCUEINT64 offset);            // Copy X,Y,Z vertices to pre-allocated arrays,
                                            // which must contain at least "count+offset" items.
                                            // Begin copying at index "lowNdx"
/*********************************** Writing Vertices ***********************************/
                                            // These replace entire contents.
  void AcceptVertices(RESCUEINT64 count, RESCUEFLOAT *xs, RESCUEFLOAT *ys, RESCUEFLOAT *zs);
                                            // Arrays must have been allocated with
                                            // "new RESCUEFLOAT[]".  They become the property
                                            // of this class.
  void SetVertices(RESCUEINT64 count, RESCUEFLOAT *xs, RESCUEFLOAT *ys, RESCUEFLOAT *zs);
                                            // Arrays are copied.
/*********************************** Reading Faces ***********************************/
  RESCUEINT64 FaceCount64() {return faceCount;}
  RESCUEINT32 FaceCount() {return (RESCUEINT32) faceCount;}
  RESCUEINT32 FaceCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT64 NthFace(RESCUEINT64 zeroBasedOrdinal, RESCUEINT64 count, RESCUEINT64 *preAllocated);
  RESCUEINT32 NthFace(RESCUEINT32 zeroBasedOrdinal, RESCUEINT32 count, RESCUEINT32 *preAllocated);
                                            // Return, for the indicated face, the list
                                            // of vertices that make up that face.  The
                                            // RESCUEINT64 return is the count of vertices in the
                                            // face.  If count and preAllocated are nonzero
                                            // up to count vertex indices are returned in
                                            // preAllocated.
  RESCUEINT64 *FaceVertexNdx() {return faceVertexNdx;}        // DO NOT delete the array.
  RESCUEINT64 *FaceVertexCount() {return faceVertexCount;}    // DO NOT delete the array.
  RESCUEINT32 *FaceVertexNdx(RESCUEBOOL throwIfTooBig);             // DO delete the array.
  RESCUEINT32 *FaceVertexCount(RESCUEBOOL throwIfTooBig);           // DO delete the array.
  RESCUEINT64 FaceVertexNdxLength() {return ((faceVertexNdx == 0) ? 0: FaceCount());}
  RESCUEINT64 FaceVertexNdxLength64() {return ((faceVertexNdx == 0) ? 0: FaceCount64());}
  RESCUEINT64 FaceVertexCountLength64() {return ((faceVertexCount == 0) ? 0: FaceCount64());}
  RESCUEINT32 FaceVertexCountLength() {return ((faceVertexCount == 0) ? 0: FaceCount());}
  void CopyFaces(RESCUEINT64 lowNdx, RESCUEINT64 count, RESCUEINT64 *preAllocatedNdx, RESCUEINT64 *preAllocatedCount, RESCUEINT64 offset);
  void CopyFaces(RESCUEINT32 lowNdx, RESCUEINT32 count, RESCUEINT32 *preAllocatedNdx, RESCUEINT32 *preAllocatedCount, RESCUEINT32 offset);
                                            // Copy faceVertexNdx and faceVertexCount arrays
                                            // into pre-allocated arrays, which must be large
                                            // enough to recieve them.  lowNdx is offset into
                                            // source arrays, offset is offset into destination
                                            // arrays.  count is number of items to copy.
  RESCUEINT64 FaceVertexTupleCount64() {return faceVertexTupleCount;}
  RESCUEINT32 FaceVertexTupleCount() {return (RESCUEINT32) faceVertexTupleCount;}
  RESCUEINT32 FaceVertexTupleCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT64 *FaceArray() {return faceArray;}                // DO NOT delete the array.
  RESCUEINT32 *FaceArray(RESCUEBOOL throwIfTooBig);                 // DO delete the array.
  RESCUEINT64 FaceArrayLength64() {return ((faceArray == 0) ? 0 : FaceVertexTupleCount64());}
  RESCUEINT32 FaceArrayLength() {return ((faceArray == 0) ? 0 : FaceVertexTupleCount());}
  void CopyFaceVertexTuples(RESCUEINT64 lowNdx, RESCUEINT64 count, RESCUEINT64 *preAllocatedNdx, RESCUEINT64 offset);
  void CopyFaceVertexTuples(RESCUEINT32 lowNdx, RESCUEINT32 count, RESCUEINT32 *preAllocatedNdx, RESCUEINT32 offset);
                                             // Copy faceArray RESCUEINT64 pre-allocated array, which must
                                             // contain at least "count+offset" items.  lowNdx is
                                             // offset into source array, offset is offset into
                                             // destination array.  count is number of items to copy.
/*********************************** Writing Faces ***********************************/
                                            // These replace entire contents.
  void AcceptFaces(RESCUEINT64 faceCountIn, RESCUEINT64 *faceVertexNdxIn, RESCUEINT64 *faceVertexCountIn,
                   RESCUEINT64 faceVertexTupleCountIn, RESCUEINT64 *faceArrayIn);
  void AcceptFaces(RESCUEINT32 faceCountIn, RESCUEINT32 *faceVertexNdxIn, RESCUEINT32 *faceVertexCountIn,
                   RESCUEINT32 faceVertexTupleCountIn, RESCUEINT32 *faceArrayIn);
                                            // Arrays must have been allocated with new RESCUEINT64[].
                                            // They become the property of this class.
  void SetFaces(RESCUEINT64 faceCountIn, RESCUEINT64 *faceVertexNdxIn, RESCUEINT64 *faceVertexCountIn,
                   RESCUEINT64 faceVertexTupleCountIn, RESCUEINT64 *faceArrayIn);
  void SetFaces(RESCUEINT32 faceCountIn, RESCUEINT32 *faceVertexNdxIn, RESCUEINT32 *faceVertexCountIn,
                   RESCUEINT32 faceVertexTupleCountIn, RESCUEINT32 *faceArrayIn);
                                            // Arrays are copied.
/*********************************** Reading Cells ***********************************/
  RESCUEINT64 CellCount64() {return cellCount;}
  RESCUEINT32 CellCount() {return (RESCUEINT32) cellCount;}
  RESCUEINT32 CellCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT64 NthCell(RESCUEINT64 zeroBasedOrdinal, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z, RESCUEINT64 &kLayer,
                      RESCUEINT64 count, RESCUEINT64 *faceIndices);   
  RESCUEINT32 NthCell(RESCUEINT32 zeroBasedOrdinal, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z, RESCUEINT32 &kLayer,
                      RESCUEINT32 count, RESCUEINT32 *faceIndices);   
                                              // For a given cell, return the number of faces as
                                              // the method return.  The cell center and k layer
                                              // index are set by reference (apologies to Java folk,
                                              // who can't read cell-at-a-time).  If count and 
                                              // faceIndices are non-zero returns up to count
                                              // face indices into the faceVertexNdx,faceVertexCount
                                              // arrays.
  RESCUEINT64 *FaceCellNdx() {return faceCellNdx;}    // Do NOT delete the array.
  RESCUEINT64 *FaceCellCount() {return faceCellCount;}// Do NOT delete the array.
  RESCUEINT64 *CellCenterNdx() {return cellCenterNdx;}// Do NOT delete the array.
  RESCUEINT64 *KLayer() {return kLayer;}              // Do NOT delete the array.
  RESCUEINT64 FaceCellNdxLength64() {return ((faceCellNdx == 0) ? 0 : CellCount64());}
  RESCUEINT64 FaceCellCountLength64() {return ((faceCellCount == 0) ? 0 : CellCount64());}
  RESCUEINT64 CellCenterNdxLength64() {return ((cellCenterNdx == 0) ? 0 : CellCount64());}
  RESCUEINT64 KLayerLength64() {return ((kLayer == 0) ? 0 : CellCount64());}
  RESCUEINT32 FaceCellNdxLength() {return ((faceCellNdx == 0) ? 0 : CellCount());}
  RESCUEINT32 FaceCellCountLength() {return ((faceCellCount == 0) ? 0 : CellCount());}
  RESCUEINT32 CellCenterNdxLength() {return ((cellCenterNdx == 0) ? 0 : CellCount());}
  RESCUEINT32 KLayerLength() {return ((kLayer == 0) ? 0 : CellCount());}

  RESCUEINT32 *FaceCellNdx(RESCUEBOOL throwIfTooBig);     // DO delete the array.
  RESCUEINT32 *FaceCellCount(RESCUEBOOL throwIfTooBig);   // DO delete the array.
  RESCUEINT32 *CellCenterNdx(RESCUEBOOL throwIfTooBig);   // DO delete the array.
  RESCUEINT32 *KLayer(RESCUEBOOL throwIfTooBig);          // DO delete the array.
  void CopyCells(RESCUEINT64 lowNdx, RESCUEINT64 count, 
                 RESCUEINT64 *faceCellNdxArray, RESCUEINT64 *faceCellCountArray, RESCUEINT64 *cellCenterNdxArray, RESCUEINT64 *kLayerArray,
                 RESCUEINT64 offset);                 
  void CopyCells(RESCUEINT32 lowNdx, RESCUEINT32 count, 
                 RESCUEINT32 *faceCellNdxArray, RESCUEINT32 *faceCellCountArray, RESCUEINT32 *cellCenterNdxArray, RESCUEINT32 *kLayerArray,
                 RESCUEINT32 offset);                 
                                              // Copy arrays into pre-allocated buffers.  lowNdx is
                                              // offset into source, count is number to copy.  The
                                              // arrays must contain at least "count+offset" items.  Any
                                              // array you don't want can be passed as null.
  RESCUEINT64 FaceListCount64() {return faceListCount;}
  RESCUEINT32 FaceListCount() {return (RESCUEINT32) faceListCount;}
  RESCUEINT32 FaceListCount(RESCUEBOOL throwIfTooBig);
  RESCUEINT64 *FaceList() {return faceList;}          // Do NOT delete the array.
  RESCUEINT32 *FaceList(RESCUEBOOL throwIfTooBig);          // DO delete the array.
  RESCUEINT64 FaceListLength64() {return ((faceList == 0) ? 0 : FaceListCount64());}
  RESCUEINT32 FaceListLength() {return ((faceList == 0) ? 0 : FaceListCount());}
  void CopyCellFaceTuples(RESCUEINT64 lowNdx, RESCUEINT64 count, RESCUEINT64 *faceListArray, RESCUEINT64 offset);
  void CopyCellFaceTuples(RESCUEINT32 lowNdx, RESCUEINT32 count, RESCUEINT32 *faceListArray, RESCUEINT32 offset);
                                              // Copy faceList array into pre-allocated buffers.  As above.
/*********************************** Writing Cells ***********************************/
                                            // These replace entire contents.
  void AcceptCells(RESCUEINT64 cellCountIn, RESCUEINT64 *faceCellNdxIn, RESCUEINT64 *faceCellCountIn, RESCUEINT64 *cellCenterNdxIn,
                   RESCUEINT64 *kLayerIn, RESCUEINT64 faceListCountIn, RESCUEINT64 *faceListIn);
  void AcceptCells(RESCUEINT32 cellCountIn, RESCUEINT32 *faceCellNdxIn, RESCUEINT32 *faceCellCountIn, RESCUEINT32 *cellCenterNdxIn,
                   RESCUEINT32 *kLayerIn, RESCUEINT32 faceListCountIn, RESCUEINT32 *faceListIn);
                                            // Arrays must have been allocated with new RESCUEINT64[] or RESCUEINT32[].
                                            // They become the property of this class.
  void SetCells(RESCUEINT64 cellCountIn, RESCUEINT64 *faceCellNdxIn, RESCUEINT64 *faceCellCountIn, RESCUEINT64 *cellCenterNdxIn,
                   RESCUEINT64 *kLayerIn, RESCUEINT64 faceListCountIn, RESCUEINT64 *faceListIn);
  void SetCells(RESCUEINT32 cellCountIn, RESCUEINT32 *faceCellNdxIn, RESCUEINT32 *faceCellCountIn, RESCUEINT32 *cellCenterNdxIn,
                   RESCUEINT32 *kLayerIn, RESCUEINT32 faceListCountIn, RESCUEINT32 *faceListIn);
                                            // Arrays are copied.
/**************************************************************************************/
private:
  RescueUnstructuredGrid(RescueContext *context, FILE *archiveFile);
  RescueUnstructuredGrid(RescueGeometry *lgrGeometry,         // Instantiated via RescueGeometry
                         RESCUEINT64 expectedVertexCount,             // constructor.
                         RESCUEINT64 expectedFaceCount,
                         RESCUEINT64 expectedFaceVertexTuples,
                         RESCUEINT64 expectedCellCount,
                         RESCUEINT64 expectedCellFaceTuples,
                         RESCUEINT64 expectedVertexRealloc = 100,
                         RESCUEINT64 expectedFaceRealloc = 100,
                         RESCUEINT64 expectedFaceVertexRealloc = 100,
                         RESCUEINT64 expectedCellRealloc = 100,
                         RESCUEINT64 expectedCellFaceRealloc = 100);
  void Archive(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object);
  void SetupGrid();
  void CalculateMinMax(RESCUEFLOAT &minX, RESCUEFLOAT &maxX, 
                       RESCUEFLOAT &minY, RESCUEFLOAT &maxY, 
                       RESCUEFLOAT &minZ, RESCUEFLOAT &maxZ);
/*
  "An array of vertices each defined by an xyz triplet"
*/
  RescueGeometry *parentGeometry;
  RESCUEINT64 vertexCount;         // Number of vertices.
  RESCUEINT64 vertexAlloc;         // Size of vertexX,Y,Z arrays.
  RESCUEINT64 vertexRealloc;       // Factor for expansion.
                           // For each. . .
  RESCUEFLOAT *vertexX;          // X coordinate of vertices.
  RESCUEFLOAT *vertexY;          // Y coordinate of vertices.
  RESCUEFLOAT *vertexZ;          // Z coordinate of vertices.
/*
  "An array of faces, each defined by a list of vertices."
*/
  RESCUEINT64 faceCount;           // Number of faces.
  RESCUEINT64 faceAlloc;           // Size of faceNdx and faceVertexCount
  RESCUEINT64 faceRealloc;         // Factor for expansion.
                           // For each. . .
  RESCUEINT64 *faceVertexNdx;      // Index into faceArray of first vertex.
  RESCUEINT64 *faceVertexCount;    // Number of vertices in faceArray.

  RESCUEINT64 faceVertexTupleCount;// Number of face/vertex tuples.
  RESCUEINT64 faceVertexAlloc;     // Size of faceArray.
  RESCUEINT64 faceVertexRealloc;   // Factor for expansion.
                           // For each. . .
  RESCUEINT64 *faceArray;          // Index into vertexX,Y,Z for one tuple.
/*
  "An array of cells, each defined by a list of faces, a cell center
  XYZ triplet, and a k-layer index for the ORIGINAL (IE top of the
  LGR tree) paren grid."
*/
  RESCUEINT64 cellCount;           // Number of cells.
  RESCUEINT64 cellAlloc;           // Size of faceCellNdx, cellCenterNdx, kLayer.
  RESCUEINT64 cellRealloc;         // Factor for expansion.
                           // For each. . .
  RESCUEINT64 *faceCellNdx;        // An index into faceList of first face.
  RESCUEINT64 *faceCellCount;      // Number of faces in faceList.
  RESCUEINT64 *cellCenterNdx;      // Index into vertexX,Y,Z.
  RESCUEINT64 *kLayer;             // k-layer number.

  RESCUEINT64 faceListCount;       // Number of cell/face tuples.
  RESCUEINT64 faceListAlloc;       // Size of faceList.
  RESCUEINT64 faceListRealloc;     // Factor for expansion.
                           // For each. . .
  RESCUEINT64 *faceList;           // Index into faceVertexNdx,faceVertexCount.

  friend class RescueGeometry;
};

#endif

