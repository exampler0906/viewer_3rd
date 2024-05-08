/********************************************************************

  RescueRadialGrid.h

  A geometry handler for RESCUE radial grids.
  See description of each array in the private section of
  the header.

  Rod Hanks,  June 2003

*********************************************************************/
#ifndef RescueRadialGrid_H
#define RescueRadialGrid_H

class RescueRadialGrid
{
public:
  ~RescueRadialGrid();
  RESCUEINT64 MaxI64() {return radialCells + 1;}
                            // Size of vertex arrays in i dimension.
  RESCUEINT64 MaxJ64() {return ((closed == TRUE) ? angularCells : (angularCells + 1));}
                            // Size of vertex arrays in the j dimension.
  RESCUEINT64 MaxK64() {return kLayers + 1;}
                            // Size of vertex arrays in k dimension.
  RESCUEINT64 Nodes64() {return MaxI() * MaxJ() * MaxK();}
                            // Length of vertex arrays.
  RESCUEINT32 MaxI() {return (RESCUEINT32) MaxI64();}
                            // Size of vertex arrays in i dimension.
  RESCUEINT32 MaxJ() {return (RESCUEINT32) MaxJ64();}
                            // Size of vertex arrays in the j dimension.
  RESCUEINT32 MaxK() {return (RESCUEINT32) MaxK64();}
                            // Size of vertex arrays in k dimension.
  RESCUEINT32 Nodes() {return (RESCUEINT32) Nodes64();}
                            // Length of vertex arrays.
  RESCUEINT64 VertexXLength64() {return ((vertexX == 0) ? 0 : Nodes64());}
  RESCUEINT64 VertexYLength64() {return ((vertexY == 0) ? 0 : Nodes64());}
  RESCUEINT64 VertexZLength64() {return ((vertexZ == 0) ? 0 : Nodes64());}
  RESCUEINT32 VertexXLength() {return ((vertexX == 0) ? 0 : Nodes());}
  RESCUEINT32 VertexYLength() {return ((vertexY == 0) ? 0 : Nodes());}
  RESCUEINT32 VertexZLength() {return ((vertexZ == 0) ? 0 : Nodes());}
  RESCUEFLOAT *VertexX() {return vertexX;}  // DO NOT delete the returned
  RESCUEFLOAT *VertexY() {return vertexY;}  // arrays.  Size is Nodes().
  RESCUEFLOAT *VertexZ() {return vertexZ;}
  RESCUEINT64 CopyArrays(RESCUEINT64 lowSrc, RESCUEINT64 count, RESCUEFLOAT *xs, RESCUEFLOAT *ys, 
                  RESCUEFLOAT *zs, RESCUEINT64 offset);
                            // Copy vertices into pre-allocated 
                            // arrays.  lowSrc is starting index,
                            // count is number to copy.  Offset is
                            // offset into xs, ys, zs.  May pass 0
                            // (null for java) for arrays you don't want.
                            // Returns number of rows returned.
  RESCUEFLOAT *CenterX() {return centerX;}  // DO NOT delete the returned
  RESCUEFLOAT *CenterY() {return centerY;}  // arrays.  Size is MaxK().
  RESCUEFLOAT *CenterZ() {return centerZ;}
  RESCUEFLOAT *CenterMD() {return centerMD;}
  RESCUEINT64 CenterXLength64() {return ((centerX == 0) ? 0 : MaxK64());}
  RESCUEINT64 CenterYLength64() {return ((centerY == 0) ? 0 : MaxK64());}
  RESCUEINT64 CenterZLength64() {return ((centerZ == 0) ? 0 : MaxK64());}
  RESCUEINT64 CenterMDLength64() {return ((centerMD == 0) ? 0 : MaxK64());}
  RESCUEINT32 CenterXLength() {return ((centerX == 0) ? 0 : MaxK());}
  RESCUEINT32 CenterYLength() {return ((centerY == 0) ? 0 : MaxK());}
  RESCUEINT32 CenterZLength() {return ((centerZ == 0) ? 0 : MaxK());}
  RESCUEINT32 CenterMDLength() {return ((centerMD == 0) ? 0 : MaxK());}
  RESCUEINT64 CopyCenter(RESCUEINT64 lowSrc, RESCUEINT64 count, RESCUEFLOAT *xs, RESCUEFLOAT *ys, 
                  RESCUEFLOAT *zs, RESCUEFLOAT *md, RESCUEINT64 offset);
                            // Copy center into pre-allocated 
                            // arrays.  lowSrc is starting index,
                            // count is number to copy.  Offset is
                            // offset into xs, ys, zs. May pass 0
                            // (null for java) for arrays you don't want.
                            // Returns number of rows returned (zero
                            // if no center line was written).
  static RESCUEINT64 MaxI(RESCUEINT64 radialCells) {return radialCells + 1;}
  static RESCUEINT64 MaxJ(RESCUEINT64 angularCells, RESCUEBOOL closed) 
                    {return ((closed == TRUE) ? angularCells : (angularCells + 1));}
  static RESCUEINT64 MaxK(RESCUEINT64 kLayers) {return kLayers + 1;}
  static RESCUEINT64 Nodes(RESCUEINT64 radialCells, RESCUEINT64 angularCells, RESCUEBOOL closed, RESCUEINT64 kLayers)
              {return MaxI(radialCells) * MaxJ(angularCells, closed) * MaxK(kLayers);}
                            // The methods above can be used to plan
                            // a set of arrays for Accept() or Set().
  void Accept(RESCUEINT64 radialCellsIn, RESCUEINT64 angularCellsIn, RESCUEINT64 kLayersIn, RESCUEBOOL closedIn, 
              RESCUEFLOAT *vertexXin, RESCUEFLOAT *vertexYin, RESCUEFLOAT *vertexZin, 
              RESCUEFLOAT *centerXin, RESCUEFLOAT *centerYin, RESCUEFLOAT *centerZin, RESCUEFLOAT *centerMDin);
                            // Set array context.  Note the formulas above
                            // for array sizes based on the above inputs.
                            // "vertex" arrays have Nodes() elements.
                            // "center" arrays have MaxK() elements.
                            // Arrays must be allocated with new RESCUEFLOAT[].
                            // Arrays become property of rescue.
                            // centerX, Y, Z, MD may be passed as null
                            // but if one is passed all must be.
  void Set(RESCUEINT64 radialCellsIn, RESCUEINT64 angularCellsIn, RESCUEINT64 kLayersIn, RESCUEBOOL closedIn, 
           RESCUEFLOAT *vertexXin, RESCUEFLOAT *vertexYin, RESCUEFLOAT *vertexZin,
           RESCUEFLOAT *centerXin, RESCUEFLOAT *centerYin, RESCUEFLOAT *centerZin, RESCUEFLOAT *centerMDin);
                            // centerX, Y, Z, MD may be passed as null.
                            // See above.  Arrays are copied.
private:
  RescueRadialGrid(RescueContext *context, FILE *archiveFile);
  RescueRadialGrid(RescueGeometry *lgrGeometry);         // Instantiated via RescueGeometry
  virtual void Relink(RescueObject *object);
  void Archive(RescueContext *context, FILE *archiveFile);
  void SetupGrid();
  void CalculateMinMax(RESCUEFLOAT &minX, RESCUEFLOAT &maxX, 
                       RESCUEFLOAT &minY, RESCUEFLOAT &maxY, 
                       RESCUEFLOAT &minZ, RESCUEFLOAT &maxZ);

  RescueGeometry *parentGeometry;
  RESCUEINT64 wellboreID;           // Wellbore ID of wellbore. May be zero.
  RESCUEINT64 kLayers;              // Number of cells along the center
                            // polyline.
  RESCUEINT64 angularCells;         // Number of cells around the center.
  RESCUEINT64 radialCells;          // Number of cells along axis
  RESCUEBOOL closed;        // True if first and last angular cells
                            // touch.
  RESCUEFLOAT *vertexX;
  RESCUEFLOAT *vertexY;
  RESCUEFLOAT *vertexZ;
  RESCUEFLOAT *centerX;
  RESCUEFLOAT *centerY;
  RESCUEFLOAT *centerZ;
  RESCUEFLOAT *centerMD;

  friend class RescueGeometry;
};

#endif

