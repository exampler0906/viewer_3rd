/********************************************************************

  RescueGeometry.h

  A geometry handler for RESCUE style corner point grids.

  Rod Hanks,  January, 1997

*********************************************************************/
#ifndef RESCUEGEOMETRY_H
#define RESCUEGEOMETRY_H

#include "myHeaders.h"
#include "RescueHistoryObject.h"
class RescueGrid;
class RescueGeometryObject;
class RescueSurface;
class RescueIJSurface;
#include "RescueSurfaceCell.h"
#include "RescueGeometryUnit.h"
#include "cSetRescueGeometryUnit.h"
#include "cSetRescueSurfaceCell.h"
#include "cSetRescueWellboreCell.h"
#include "RescuePolyLine.h"
#include "cSetRescuePolyLine.h"
#include "cSetRescueTrimVertex.h"
#include "cSetRescueProperty.h"
#include "cSetRescueSurfaceToGrid.h"
#include "cSetRescueStairSteppedFault.h"
#include "RescueCoordinateSystem.h"
class RescueModel;
class RescueWellbore;
class RescueReferenceSurface;
class RescueBitArray;
class RescueSurfaceToGrid;
class cSetRescueSurfaceToGrid;
class RescueColor;
class cSetRescueTrimVertex;
class RescueWireframe;
class RescueUnit;
class RescueGeobodyPart;
class RescueBlockUnit;
struct RescueIJKCellPair;
class RescueStairSteppedFault;
class cSetRescueGeometry;
class RescueParametricLGRMap;
class RescueInterfaceSurfaceDesc;
class cSetRescueInterfaceSurfaceDesc;
class RescueUnstructuredGrid;
class RescueRadialGrid;
class RescuePillar;
class RescueOrientationLedger;
class cSetRescueDataContainer;
#include "RescueGridAxis.h"

class RescueGeometry:public RescueHistoryObject
{
public:
/******************************** Applies to CPG Only ********************************************/
  typedef enum {R_EQUAL_AXIS, 						 // x, y, z derived from grid origin and step or from reference surfaces.
					      R_UNEQUAL_AXIS,						 // x and y from origin and step, z is given.
                R_COORDINATE_LINE,				 // straight coordinate line.
					      R_COORDINATE_POLYLINE,		 // piece wise coordinate line.
                R_SPLIT_LINE,						   // split nodes (corner point or multiple coordinate line).
                R_SPLINE_LINE}             // splined line via RescuePillar.
									   RescueVertexType;     // It makes the most sense to put R_SPLINE_LINE before
                                           // R_SPLIT_LINE, but that would invalidate older models.

  typedef enum {R_ONLAP,                   // Reference surface is ABOVE the grid.
                R_OFFLAP}                  // Reference surface is BELOW the grid.
                      RescueLapType;

  typedef enum {R_XY_ORTHOGONAL,           // If VertexIs() == R_UNEQUAL_AXIS  or VertexIs() == R_EQUAL_AXIS
                R_SQUASHED_ORTHOGONAL,     // If all interior vertexes are R_EQUAL_AXIS or R_UNEQUAL_AXIS but
                                           // at least some exterior vertexes are R_COORDINATE_LINE or
                                           // R_COORDINATE_POLYLINE.
                R_CONFORMABLE}             // If neither of the above is TRUE.
                      RescueGridType;

  typedef enum {R_ACTIVE,                  // Cell is completely inside the BUG
                R_INACTIVE,                // Cell is completely outside the BUG
                R_TRUNCATED,               // Cell is partially inside and partially outside the BUG
                R_INACTIVATED_BY_PILLAR}   // Cell is inactivated by a Y Fault.
                      RescueCellStatus;
/********************************** Applies to LGR only ******************************************/
  typedef enum {R_NOT_LGR,
                R_RULE_BASED,              // Describes the parent/child relationship
                R_WEIGHT_BASED,            // for an LGR.
                R_UNCONSTRAINED,
                R_RULE_BASED_NOSPAN,
                R_WEIGHT_BASED_NOSPAN}
                      RescueLGRType;

  typedef enum {R_STRUCTURED_CPG,             // The type of LGR grid.
                R_STRUCTURED_RADIAL,
                R_UNSTRUCTURED_TETRAHEDRAL,
                R_UNSTRUCTURED_2D_POLYHEDRAL,
                R_UNSTRUCTURED_3D_POLYHEDRAL}
                      RescueLGRGridType;
/***************************************************************************************************/
  RescueGeometry(RescueModel *parentModelIn, 
                 RescueGrid *existingGrid, 
                 RESCUEFLOAT missingValueIn);
                                            // Normal constructor for most block unit grids.
                                            // x,y,z of vertexes of type R_EQUAL_AXIS are 
                                            // determined by the grid.
  RescueGeometry(RescueModel *parentModelIn, 
                 RescueGrid *existingGrid, 
                 RESCUEFLOAT missingValueIn,
                 RescueReferenceSurface *topSurfaceIn, 
                 RESCUEFLOAT topOffsetIn,
                 RescueReferenceSurface *bottomSurfaceIn, 
                 RESCUEFLOAT  bottomOffsetIn);
                                            // Constructor for a grid whose z values are 
                                            // determined by the reference surfaces and offsets.
                                            // Each k-layer is proportional to the distance between
                                            // the top and bottom reference surfaces, after the
                                            // offsets are applied. This applies only to vertexes
                                            // of type R_EQUAL_AXIS.
  RescueGeometry(RescueModel *parentModelIn, 
                 RescueGrid *existingGrid, 
                 RESCUEFLOAT missingValueIn,
                 RescueReferenceSurface *referenceSurfaceIn, 
                 RESCUEFLOAT referenceOffsetIn, 
                 RESCUEFLOAT thicknessIn, 
                 RescueLapType onOffLapIn);
                                            // Constructor for a grid whose z values are 
                                            // determined by the reference surface and offset.
                                            // Each k-layer is of the same thickness, determined
                                            // by the thickness argument. This applies only to vertexes
                                            // of type R_EQUAL_AXIS.
/****************************************************************************************************

    Constructors for CPG LGRs.

******************************************************************************************************/
  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a rule based (implicitly mapped) LGR.
                 RESCUEINT64 referenceID,            // For each axis LowBound and Count define the
                 RESCUEINT64 parentILowBound,        // section of the axis that is being refined,
                 RESCUEINT64 parentICount,           // and the refined count specifies how many
                 RESCUEINT64 refinedILowBound,       // nodes lie in that space along the axis of
                 RESCUEINT64 refinedICount,          // the refined grid.  The first node and last node
                 RESCUEINT64 parentJLowBound,        // of the refined axis are in exactly the same
                 RESCUEINT64 parentJCount,           // location as the first and last node of the
                 RESCUEINT64 refinedJLowBound,       // refined area, and the other nodes are equally
                 RESCUEINT64 refinedJCount,          // distributed along the axis.
                 RESCUEINT64 parentKLowBound,        // (R_RULE_BASED).
                 RESCUEINT64 parentKCount,           
                 RESCUEINT64 refinedKLowBound,
                 RESCUEINT64 refinedKCount);         
  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a rule based (implicitly mapped) LGR.
                 RESCUEINT32 referenceID,            // For each axis LowBound and Count define the
                 RESCUEINT32 parentILowBound,        // section of the axis that is being refined,
                 RESCUEINT32 parentICount,           // and the refined count specifies how many
                 RESCUEINT32 refinedILowBound,       // nodes lie in that space along the axis of
                 RESCUEINT32 refinedICount,          // the refined grid.  The first node and last node
                 RESCUEINT32 parentJLowBound,        // of the refined axis are in exactly the same
                 RESCUEINT32 parentJCount,           // location as the first and last node of the
                 RESCUEINT32 refinedJLowBound,       // refined area, and the other nodes are equally
                 RESCUEINT32 refinedJCount,          // distributed along the axis.
                 RESCUEINT32 parentKLowBound,        // (R_RULE_BASED).
                 RESCUEINT32 parentKCount,           
                 RESCUEINT32 refinedKLowBound,
                 RESCUEINT32 refinedKCount);  
  
  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a rule based (implicitly mapped) LGR.
                 RESCUEINT64 referenceID,            // For each axis, LowBound and Count define the
                 RESCUEINT64 parentILowBound,        // section of the axis that is being refined,
                 RESCUEINT64 parentICount,           // and the refined count array specifies how many
                 RESCUEINT64 *refinedICountArray,    // divisions in each coarsen cell.  The dimensions of
                 RESCUEINT64 parentJLowBound,        // the array is the same as the parent count.
                 RESCUEINT64 parentJCount,           // The arrays are copied by the constructor.
                 RESCUEINT64 *refinedJCountArray,    // (R_RULE_BASED_NOSPAN).
                 RESCUEINT64 parentKLowBound,        
                 RESCUEINT64 parentKCount,           
                 RESCUEINT64 *refinedKCountArray);         
  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a rule based (implicitly mapped) LGR.
                 RESCUEINT32 referenceID,            // For each axis, LowBound and Count define the
                 RESCUEINT32 parentILowBound,        // section of the axis that is being refined,
                 RESCUEINT32 parentICount,           // and the refined count array specifies how many
                 RESCUEINT32 *refinedICountArray,    // divisions in each coarsen cell.  The dimensions of
                 RESCUEINT32 parentJLowBound,        // the array is the same as the parent count.
                 RESCUEINT32 parentJCount,           // The arrays are copied by the constructor.
                 RESCUEINT32 *refinedJCountArray,    // (R_RULE_BASED_NOSPAN).
                 RESCUEINT32 parentKLowBound,        
                 RESCUEINT32 parentKCount,           
                 RESCUEINT32 *refinedKCountArray);         

  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a weight based (implicitly mapped) LGR.
                 RESCUEINT64 referenceID,            // For each axis the array of weights gives floating point    
                 RESCUEINT64 xLowBoundin,            // values that lie along the i, j, and k axes.
                 RESCUEDOUBLE *xWeights,            // Low bounds are used to construct the LGR's grid and
                 RESCUEINT64 xWeightLength,          // would often be zero no matter what part of the parent
                 RESCUEINT64 yLowBoundin,            // axis is being covered.
                 RESCUEDOUBLE *yWeights,            // Arrays are copied by the constructor.
                 RESCUEINT64 yWeightLength,          // (R_WEIGHT_BASED).
                 RESCUEINT64 zLowBoundin,
                 RESCUEDOUBLE *zWeights,  
                 RESCUEINT64 zWeightLength);
  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a weight based (implicitly mapped) LGR.
                 RESCUEINT32 referenceID,            // For each axis the array of weights gives floating point    
                 RESCUEINT32 xLowBoundin,            // values that lie along the i, j, and k axes.
                 RESCUEDOUBLE *xWeights,            // Low bounds are used to construct the LGR's grid and
                 RESCUEINT32 xWeightLength,          // would often be zero no matter what part of the parent
                 RESCUEINT32 yLowBoundin,            // axis is being covered.
                 RESCUEDOUBLE *yWeights,            // Arrays are copied by the constructor.
                 RESCUEINT32 yWeightLength,          // (R_WEIGHT_BASED).
                 RESCUEINT32 zLowBoundin,
                 RESCUEDOUBLE *zWeights,  
                 RESCUEINT32 zWeightLength);

  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a weight based (implicitly mapped) LGR.
                 RESCUEINT64 referenceID,            // For each axis LowBound and Count define the section of   
                 RESCUEINT64 parentILowBound,        // the axis that is being refined.  The array of weights
                 RESCUEINT64 parentICount,           // gives the floating point values to devide each parent
                 RESCUEINT64 *xWeightLength,           // cell.  For each cell, consider the distance from 
                 RESCUEDOUBLE **xWeights,         // node n to node n + 1 to be measured from 0 to 1.
                 RESCUEINT64 parentJLowBound,        // The weights give the position of the extra nodes in the
                 RESCUEINT64 parentJCount,           // refining grid, expressed as a series of floating point
                 RESCUEINT64 *yWeightLength,           // that should sum to 1.0
                 RESCUEDOUBLE **yWeights,         // (R_WEIGHT_BASED_NOSPAN).
                 RESCUEINT64 parentKLowBound,
                 RESCUEINT64 parentKCount,           
                 RESCUEINT64 *zWeightLength,  
                 RESCUEDOUBLE **zWeights);
  RescueGeometry(RescueGeometry *parentGrid, // Constructor for a weight based (implicitly mapped) LGR.
                 RESCUEINT32 referenceID,            // For each axis LowBound and Count define the section of   
                 RESCUEINT32 parentILowBound,        // the axis that is being refined.  The array of weights
                 RESCUEINT32 parentICount,           // gives the floating point values to devide each parent
                 RESCUEINT32 *xWeightLength,           // cell.  For each cell, consider the distance from 
                 RESCUEDOUBLE **xWeights,         // node n to node n + 1 to be measured from 0 to 1.
                 RESCUEINT32 parentJLowBound,        // The weights give the position of the extra nodes in the
                 RESCUEINT32 parentJCount,           // refining grid, expressed as a series of floating point
                 RESCUEINT32 *yWeightLength,           // that should sum to 1.0
                 RESCUEDOUBLE **yWeights,         // (R_WEIGHT_BASED_NOSPAN).
                 RESCUEINT32 parentKLowBound,
                 RESCUEINT32 parentKCount,           
                 RESCUEINT32 *zWeightLength,  
                 RESCUEDOUBLE **zWeights);

  RescueGeometry(RescueGeometry *parentGrid, // Constructor for an unconstrained (explicitly mapped) LGR.
                 RESCUEINT64 referenceID,            // The mapping with the parent must be supplied separately.   
                 RescueGrid *existingGrid, 
                 RESCUEFLOAT missingValueIn);      
  RescueGeometry(RescueGeometry *parentGrid, // Constructor for an unconstrained (explicitly mapped) LGR.
                 RESCUEINT32 referenceID,            // The mapping with the parent must be supplied separately.   
                 RescueGrid *existingGrid, 
                 RESCUEFLOAT missingValueIn);      
                                              // Remove any of these with RescueGeometry::DropGeometry
/****************************************************************************************************

    Constructor for Unstructured LGRs.

******************************************************************************************************/
  RescueGeometry(RescueGeometry *parentGrid,                    // Can be used for a parent of any type
                 RESCUEINT64 referenceID,                       // but should only be used when the parent
                 RescueLGRGridType gridType,                    // is not a CPG, because it does not define
                 RESCUEINT64 expectedVertexCount,               // the area of the refinement within the
                 RESCUEINT64 expectedFaceCount,                 // cpg of the parent.
                 RESCUEINT64 expectedFaceVertexTuples,
                 RESCUEINT64 expectedCellCount,
                 RESCUEINT64 expectedCellFaceTuples,
                 RESCUEINT64 expectedVertexRealloc = 100,        // I did not do RESCUEINT32 versions of these
                 RESCUEINT64 expectedFaceRealloc = 100,          // because they have default arguments and
                 RESCUEINT64 expectedFaceVertexRealloc = 100,    // no arrays.  In my tests they did not
                 RESCUEINT64 expectedCellRealloc = 100,          // cause problems for "int" arguments.
                 RESCUEINT64 expectedCellFaceRealloc = 100);
  RescueGeometry(RescueGeometry *parentGrid,
                 RESCUEINT64 parentILowBound,        // section of the axis that is being refined,
                 RESCUEINT64 parentICount,           // this constructor is preferred when the parent
                 RESCUEINT64 parentJLowBound,        // is a CPG.
                 RESCUEINT64 parentJCount,      
                 RESCUEINT64 parentKLowBound, 
                 RESCUEINT64 parentKCount,           
                 RESCUEINT64 referenceID,
                 RescueLGRGridType gridType,
                 RESCUEINT64 expectedVertexCount,
                 RESCUEINT64 expectedFaceCount,
                 RESCUEINT64 expectedFaceVertexTuples,
                 RESCUEINT64 expectedCellCount,
                 RESCUEINT64 expectedCellFaceTuples,
                 RESCUEINT64 expectedVertexRealloc = 100,
                 RESCUEINT64 expectedFaceRealloc = 100,
                 RESCUEINT64 expectedFaceVertexRealloc = 100,
                 RESCUEINT64 expectedCellRealloc = 100,
                 RESCUEINT64 expectedCellFaceRealloc = 100);
/****************************************************************************************************

    Constructor for Radial LGRs.

******************************************************************************************************/
  RescueGeometry(RescueGeometry *parentGrid,       // Use this constructor when the parent grid
                 RESCUEINT64 referenceID);           // is not CPG.
  RescueGeometry(RescueGeometry *parentGrid,
                 RESCUEINT64 parentILowBound,        // section of the axis that is being refined,
                 RESCUEINT64 parentICount,           // this constructor is preferred when the parent
                 RESCUEINT64 parentJLowBound,        // is a CPG.
                 RESCUEINT64 parentJCount,      
                 RESCUEINT64 parentKLowBound, 
                 RESCUEINT64 parentKCount,           
                 RESCUEINT64 referenceID);
/******************************************************************************************************

    Methods for manipulating LGRs.  All of these methods can be called WITHOUT loading the geometry.

******************************************************************************************************/
  void SetReferenceID(RESCUEINT64 newId) {referenceID = newId;}
  RESCUEINT64 ReferenceID64() {return referenceID;}   // Application-defined id used for mapping   areas
                                                      // in the LGRID property.  Unassigned ones are zero.
  RESCUEINT32 ReferenceID() {return RescueContext::Return32For64(ReferenceID64(), false);}
  void SetReferenceName(RESCUECHAR *newName);         // Application-defined name.  Unassigned names return 0.
  RESCUECHAR *ReferenceName() {return referenceName;} // DO NOT delete the pointer returned.
  void SetLGRGroupName(RESCUECHAR *newName);          // Application-defined group name.  Unassigned returns 0.
  RESCUECHAR *LGRGroupName() {return lgrSetName;}     // DO NOT delete the pointer returned.
  void SetLGRStartTime(RESCUECHAR *startTime);        // Time formats are the same as those used for 
  RESCUECHAR *LGRStartTime() {return lgrStartTime;}   // RescueTimeStepGroup.  Unassigned returns 0.
  void SetLGREndTime(RESCUECHAR *endTime);            // Do not delete the pointer returned.
  RESCUECHAR *LGREndTime() {return lgrEndTime;}

  RescueGeometry *ProgenyHavingID(RESCUEINT64 referenceID);
                                             // Returns any offspring LGR with the given ID (including
                                             // the current generation).
  RESCUEBOOL DropGeometry(RescueGeometry *toDrop); 
                                             // Drop any offspring geometry, including grandchildren etc.
                                             // Returns true if the geometry was located and dropped.
  RescueGeometry *ParentGeometry() {return parentGeometry;}          
                                             // Returns the immediate parent.  Top level (BUG) will
                                             // return 0;
  RescueGeometry *ParentBUG();               // Returns the top level parent.  If at the top level
                                             // returns itself.
  RESCUEINT32 LGRCount();                    // Number of offspring in next generation.
  RESCUEINT64 LGRCount64();                  // Number of offspring in next generation.
  RescueGeometry *NthLGR(RESCUEINT64 zeroBasedOrdinal);
                                             // Returns offspring of the next generation.
  RescueLGRType LGRType() {return lgrType;}  // 
  RescueLGRGridType LGRGridType() {return lgrGridType;}
  RESCUEINT64 ParentLowBound64(RescueGridAxis::GridNdx ndx);
  RESCUEINT64 ParentCount64(RescueGridAxis::GridNdx ndx);
  RESCUEINT64 ParentILowBound64() {return parentILowBound;}
  RESCUEINT64 ParentICount64() {return parentICount;}
  RESCUEINT64 ParentJLowBound64() {return parentJLowBound;}
  RESCUEINT64 ParentJCount64() {return parentJCount;}
  RESCUEINT64 ParentKLowBound64() {return parentKLowBound;}
  RESCUEINT64 ParentKCount64() {return parentKCount;}   // For rule-based implicit LGR's returns
                                              // the section of the parent axis involved.  The count of
                                              // the axes is available from the grid, as usual. 
  RESCUEINT32 ParentLowBound(RescueGridAxis::GridNdx ndx) {return RescueContext::Return32For64(ParentLowBound64(ndx), false);}
  RESCUEINT32 ParentCount(RescueGridAxis::GridNdx ndx) {return RescueContext::Return32For64(ParentCount64(ndx), false);}
  RESCUEINT32 ParentILowBound() {return RescueContext::Return32For64(parentILowBound, false);}
  RESCUEINT32 ParentICount() {return RescueContext::Return32For64(parentICount, false);}
  RESCUEINT32 ParentJLowBound() {return RescueContext::Return32For64(parentJLowBound, false);}
  RESCUEINT32 ParentJCount() {return RescueContext::Return32For64(parentJCount, false);}
  RESCUEINT32 ParentKLowBound() {return RescueContext::Return32For64(parentKLowBound, false);}
  RESCUEINT32 ParentKCount() {return RescueContext::Return32For64(parentKCount, false);} 

  RESCUEINT32 ParentLowBound(RescueGridAxis::GridNdx ndx, RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(ParentLowBound64(ndx), throwIfTooBig);}
  RESCUEINT32 ParentCount(RescueGridAxis::GridNdx ndx, RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(ParentCount64(ndx), throwIfTooBig);}
  RESCUEINT32 ParentILowBound(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(parentILowBound, throwIfTooBig);}
  RESCUEINT32 ParentICount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(parentICount, throwIfTooBig);}
  RESCUEINT32 ParentJLowBound(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(parentJLowBound, throwIfTooBig);}
  RESCUEINT32 ParentJCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(parentJCount, throwIfTooBig);}
  RESCUEINT32 ParentKLowBound(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(parentKLowBound, throwIfTooBig);}
  RESCUEINT32 ParentKCount(RESCUEBOOL throwIfTooBig) {return RescueContext::Return32For64(parentKCount, throwIfTooBig);} 

  RESCUEINT64 WeightLength64(RescueGridAxis::GridNdx ndx);
  RESCUEINT32 WeightLength(RescueGridAxis::GridNdx ndx) {return RescueContext::Return32For64(WeightLength64(ndx), false);}
  RESCUEDOUBLE *Weight(RescueGridAxis::GridNdx ndx);
  void Weight(RescueGridAxis::GridNdx ndx, RESCUEDOUBLE *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);
  RESCUEINT64 XWeightLength64() {return xWeightLength;}
  RESCUEINT32 XWeightLength() {return RescueContext::Return32For64(XWeightLength64(), false);}
  void XWeight(RESCUEDOUBLE *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);
  RESCUEDOUBLE *XWeight() {return xWeight;}          // DO NOT delete the returned array.
  RESCUEINT64 YWeightLength64() {return yWeightLength;}
  RESCUEINT32 YWeightLength() {return RescueContext::Return32For64(YWeightLength64(), false);}
  void YWeight(RESCUEDOUBLE *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);
  RESCUEDOUBLE *YWeight() {return yWeight;}          // DO NOT delete the returned array.
  RESCUEINT64 ZWeightLength64() {return zWeightLength;}
  RESCUEINT32 ZWeightLength() {return RescueContext::Return32For64(ZWeightLength64(), false);}
  void ZWeight(RESCUEDOUBLE *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);
  RESCUEDOUBLE *ZWeight() {return zWeight;}          // DO NOT delete the returned array.
                                               // These weight routines work for R_WEIGHT_BASED, but also
                                               // for R_RULE_BASED_NOSPAN and R_WEIGHT_BASED_NOSPAN, since
                                               // they are essentially special cases of weight based LGRs.

  void RefinedCountArray(RescueGridAxis::GridNdx ndx, RESCUEINT64 *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLen);  
  void RefinedCountArray(RescueGridAxis::GridNdx ndx, RESCUEINT32 *buffer, RESCUEINT32 offset, RESCUEINT32 bufferLen);  
                                               // For R_RULE_BASED_NOSPAN.  The arrays are re-created
                                               // from the R_WEIGHT_BASED structures.  ParentICount(),
                                               // ParentJCount(), ParentKCount() give maximum sizes for
                                               // the output buffers.
  RESCUEINT64 WeightBasedNodesFor(RescueGridAxis::GridNdx ndx, RESCUEINT64 iNdx);          
                                               // For R_WEIGHT_BASED_NOSPAN.  It is difficult to return a
                                               // doubly-subscripted array, so here we are returning all the
                                               // values that are available for a particular node.
                                               // These can return useful information for R_RULE_BASED_NOSPAN
                                               // and R_WEIGHT_BASED, though you have to be careful how you
                                               // interpret it in those cases.
  void WeightFor(RescueGridAxis::GridNdx ndx, RESCUEINT64 iNdx, RESCUEDOUBLE *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLen);

  RescueParametricLGRMap *ParametricMap() {return parametricMap;}    
                                              // May return 0
  RescueInterfaceSurfaceDesc *InterfaceSurfaceDesc(RESCUEINT64 zeroBasedNdx);
  RESCUEINT64 InterfaceSurfaceDescCount64();
  RESCUEINT32 InterfaceSurfaceDescCount();
  RESCUEBOOL DropInterfaceSurfaceDesc(RescueInterfaceSurfaceDesc *toDrop);
  RescueUnstructuredGrid *UnstructuredGrid() {return unstructuredGrid;}
  RescueRadialGrid *RadialGrid() {return radialGrid;}
/******************************************************************************************************/
	virtual ~RescueGeometry();
  RESCUEBOOL AnyFileTruncated();
  RescueGrid *Grid() {return grid;}
  RescueModel *ParentModel() {return parentModel;}
  RESCUEFLOAT MissingValue() {return missingValue;}
  void SetZValue(RESCUEFLOAT *valueArray);
																		// Sets Z values for all nodes.
                                    // The array has three dimensions (i,j,k) each						 
																		// sized to the number of nodes	in the grid.  No
																		// nodes will be split in the z direction after this.
																		// Promotes to R_UNEQUAL_AXIS.
                                    // Copies the array.

	void SetZValue(RESCUEINT64 i, RESCUEINT64 j, RESCUEFLOAT *valueArray);
																		// Sets the z values for a particular ij vertex.
																		// The array is the length of the number of
																		// k layers. i and j are vertex indexes.
																		// Promotes to R_UNEQUAL_AXIS.
                                    // The array must have been created with new RESCUEFLOAT []
                                    // and becomes the property of the grid.
	void SetZValue(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT value);
																		// Sets the z value of a particular k layer.  i and j
																		// are vertex indexes.
																		// Promotes to R_UNEQUAL_AXIS.
	void SetCoordinateLine(RESCUEINT64 i, RESCUEINT64 j, RESCUEFLOAT xTop, RESCUEFLOAT yTop, RESCUEFLOAT zTop,
	                                     RESCUEFLOAT xBottom, RESCUEFLOAT yBottom, RESCUEFLOAT zBottom,
																			 RESCUEFLOAT *middleZvalues = 0);
																		// Sets a vertex to a coordinate line.  i and j are vertex
																		// indexes.  If middleZvalues	is given there are two less
																		// than the number of k layers (since top and bottom are
																		// defined by zTop and zBottom).
																		// Vertex will promote or collapse to R_COORDINATE_LINE.
                                    // If middleValues is given, it must have been created
                                    // with new RESCUEFLOAT[] and becomes the property of the grid.
	void SetCoordinatePolyLine(RESCUEINT64 i, RESCUEINT64 j, RESCUEFLOAT *values);
																		// The array contains 2 dimensions.  The first is the k layer,
																		// the second is x = 0, y = 1, z = 2.  i and j are vertex
																		// indexes.  Will promote or collapse to R_COORDINATE_POLYLINE.
                                    // The array must have been created with new RESCUEFLOAT[].  It becomes
                                    // the property of the grid.  Do NOT free it.
	void SetCornerNode(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
																		// i, j, k define a cell, corner is a corner of that cell (0-8).
																		// x, y, and z is the geometry of that corner. Promotes to
																		// R_SPLIT_LINE.
                                    // For corners of split nodes that have been truncated away,
                                    // x, y, and z should be set to FLT_MAX.
	void SetXValue(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT value);
	void SetYValue(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT value);
	void SetZValue(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT value);
																		// Sets a split x,y, or z value for a particular node corner.
																	  // i,j,k identify the cell, corner the node.
																		// Will promote vertex to R_SPLIT_LINE.
	RescueVertexType VertexIs() {return vertexIs;}			
																		// Returns the highest RescueVertexType present in the grid.
	RescueVertexType VertexIs(RESCUEINT64 i, RESCUEINT64 j);
																		// Returns the storage regime in use at the given vertex index.
  RescueGridType GeometryType();    // Characterizes the grid as a whole.
	void Values(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k, RESCUEINT32 corner, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
																		// Returns, in x, y, and z, the geometry of the given cell node
																	  // (identified by i, j, k) and corner.
	RESCUEBOOL Values(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	RESCUEBOOL Values(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
																		// For all unsplit nodes, returns, TRUE, and in x, y, and z, 
																		// the values of the unsplit node identified by i, j, and k.  
																	  // This is by node, not cell. If the node is split, returns
																		// FALSE, and x, y, and z are zero.
	RESCUEBOOL Values(RESCUEDOUBLE u, RESCUEDOUBLE v, RESCUEDOUBLE w, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
																		// For all unsplit nodes, returns, TRUE, and in x, y, and z, 
																		// the values of the unsplit node identified by u, v, and w.  
																	  // This is by node, not cell. If the node is split, returns
																		// FALSE, and x, y, and z are zero.
	RESCUEBOOL Values(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &z);
	RESCUEBOOL Values(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k, RESCUEFLOAT &z);
																		// For all unsplit nodes, returns TRUE and the z value of the
																		// unsplit node identified by i, j, and k.  If the node is split,
																		// returns FALSE and z is zero.
  void CellToNode(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEINT64 &iPrime, RESCUEINT64 &jPrime, RESCUEINT64 &kPrime);
  void CellToNode(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k, RESCUEINT32 corner, RESCUEINT32 &iPrime, RESCUEINT32 &jPrime, RESCUEINT32 &kPrime);
																	  // Returns node based ijk for cell ijk and corner.
  RescuePillar *DemandPillar(RESCUEINT64 i, RESCUEINT64 j);
  RescuePillar *DemandPillar(RESCUEINT32 i, RESCUEINT32 j) {return DemandPillar((RESCUEINT64) i, (RESCUEINT64) j);}
                                    // Promotes to R_SPLINE_LINE (if node is not already) and
                                    // returns a pointer to the new or existing pillar definition.
                                    // The pillar will initially be undefined, unless the node
                                    // was already R_SPLINE_LINE.
  void UVWValues(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEDOUBLE &uTerm, RESCUEDOUBLE &vTerm, RESCUEDOUBLE &wTerm);
  void UVWValues(RESCUEINT32 i, RESCUEINT32 j, RESCUEINT32 k, RESCUEDOUBLE &uTerm, RESCUEDOUBLE &vTerm, RESCUEDOUBLE &wTerm);
  void UVWValues(RESCUEDOUBLE i, RESCUEDOUBLE j, RESCUEDOUBLE k, RESCUEDOUBLE &uTerm, RESCUEDOUBLE &vTerm, RESCUEDOUBLE &wTerm);
                                    // Returns i,j,k of rule or weight based LGR (including nospan)
                                    // as u,v,w of the parent's axes.
  /****************************************************************************************************/
  RESCUEFLOAT *CornerValues(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner);
  RESCUEINT32 CornerValuesLength() {return 3;}
                                    // Returns x y and z for the geometry of the identified cell corner.
                                    // Corresponds to 
                                    // void Values(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                    // DO delete the returned array.
  RESCUEFLOAT *NodeValues(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
  RESCUEINT32 NodeValuesLength() {return 3;}
                                    // Corresponds to 
                                    // RESCUEBOOL Values(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                    // Returns 0 if the value would have been FALSE.
                                    // DO delete the returned array.
  RESCUEFLOAT *UVWNodeValues(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
  RESCUEINT32 UVWNodeValuesLength() {return 3;}
                                    // Corresponds to 
                                    // RESCUEBOOL UVWValues(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                    // Returns 0 if the value would have been FALSE.
                                    // DO delete the returned array.
  RESCUEFLOAT *UVWNodeValues2(RESCUEDOUBLE i, RESCUEDOUBLE j, RESCUEDOUBLE k);
  RESCUEINT32 UVWNodeValues2Length() {return 3;}
                                    // Corresponds to 
                                    // RESCUEBOOL UVWValues(RESCUEDOUBLE i, RESCUEDOUBLE j, RESCUEDOUBLE k, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                    // Returns 0 if the value would have been FALSE.
                                    // DO delete the returned array.
  RESCUEFLOAT ZValue(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);// Corresponds to 
                                    // RESCUEBOOL Values(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &z);
                                    // Returns FLT_MIN if the return would have been FALSE.
  void AllCornerValues(RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);         
                                    // Returns a floating point buffer with ALL corner values.
  RESCUEINT64 AllCornerValuesLength64();      // Length of buffer is (ni - 1)*(nj - 1)*(nk - 1)*8*3.
  RESCUEINT32 AllCornerValuesLength();
  RESCUEINT32 AllCornerValuesLength(RESCUEBOOL throwIfTooBig);  
  void LayerCornerValues(RESCUEINT64 k, RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);  
                                    // Returns a floating point buffer with all corner values for
                                    // a particular layer of cells (therefore 0 < k < nk - 1).
  RESCUEINT64 LayerCornerValuesLength64();    // Length of buffer is (ni - 1)*(nj - 1)*8*3
  RESCUEINT32 LayerCornerValuesLength();
  /****************************************************************************************************/
  void SetStairSteppedSurface(RescueIJSurface *surface,
                              RescueIJKCellPair *cellPairs, 
                              RESCUEINT64 arrayLength);
                                     // Records the intersection of a BUG with a stair-stepped fault
                                     // by recording pairs of cells.  The area of the faces shared by
                                     // these cells is the area of the fault.
                                     // The cellPairs becomes the property of the RescueStairSteppedFault
                                     // object.  Do not delete this pointer after using it in this
                                     // method.  RescueStairSteppedFault will use "delete" to free the
                                     // memory.
  RescueStairSteppedFault *StairStepsFor(RescueIJSurface *surface);
                                     // Return a RescueStairSteppedFault object for a given surface.
                                     // Returns 0 if there is no RescueStairSteppedFault declared for
                                     // that surface.  Do NOT delete the object returned.
  RESCUEINT64 StairStepCount64() {return stairSteps->Count64();}
  RESCUEINT32 StairStepCount() {return stairSteps->Count();}
  RescueStairSteppedFault *NthStairSteppedFault(RESCUEINT64 zeroBasedOrdinal)
                                  {return stairSteps->NthObject(zeroBasedOrdinal);}
                                     // Return a RescueStairSteppedFault object. Returns zero if ndx is
                                     // out of bounds. Do NOT delete the object returned
  void SetSurfaceIntersection(RescueIJSurface *surface,
                              RESCUEINT64 *iList, RESCUEINT64 *jList, RESCUEINT64 listLength);
  void SetSurfaceIntersection(RescueIJSurface *surface,
                              RESCUEINT32 *iList, RESCUEINT32 *jList, RESCUEINT32 listLength);
                                     // Declare a polyline in the ij space of the BUG which defines
                                     // the cutting plane of the surface thru the BUG.  The plane is
                                     // assumed to extend from the top of the BUG to the bottom, so
                                     // no k information is needed.  This information replaces any
                                     // previous information for this surface and BUG.  If the poly
                                     // line has multiple segments, segment breaks are denoted in the
                                     // list with -999, -999 coordinates.  The integer arrays passed
                                     // must have been allocated with new RESCUEINT64[] or RESCUEINT32[]
                                     // and become the property of the BUG.
                                     // To drop one, pass a listLength=0.
  RescueSurfaceToGrid *IntersectionFor(RescueIJSurface *surface);
                                     // Return a RescueSurfaceToGrid object which contains the data
                                     // given in the SetSurfaceIntersection method above.  Returns 0
                                     // if the SetSurfaceIntersection method above has not been called
                                     // for that surface (including if surface intersection data was
                                     // given by the alternate SetSurfaceIntersection method below).
  RescueSurfaceToGrid *NthSurfaceToGrid(RESCUEINT64 zeroBasedOrdinal)
                          {return surfaceToGrid->NthObject(zeroBasedOrdinal);}
                                      // Useful for validator checks.  Start at zero and keep raising
                                      // the ordinal until the pointer returned is zero.
  void SetSurfaceIntersection(RescueIJSurface *surface,
                              RescueSurfaceCell::SurfaceSide side,
                              RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k,
                              RESCUEINT64 cellFaceNumber,
                              RESCUEFLOAT *uvs=0);
                                      // Declare a new relationship between a cell
                                      // in this grid and a surface.
                                      // array is 2 x 4 in which the first index is u=0, v=1,
                                      // and the second index is the face corner number (see
                                      // document). The array must have been allocated with new RESCUEFLOAT[]
                                      // and becomes the property of the grid.
  RESCUEBOOL DropRescueSurfaceCell(RescueSurfaceCell *cellToDrop) 
                          {return ((*surfaceCell) -= cellToDrop);}
                                      // Destructor will drop it from the surface side.
  RescueSurfaceCell *NthSurfaceCell(RESCUEINT64 zeroBasedOrdinal) {return surfaceCell->NthObject(zeroBasedOrdinal);}

  RESCUEINT64 GeometryUnitCount64() {return geometryUnit->Count64();}
  RESCUEINT32 GeometryUnitCount() {return geometryUnit->Count();}
  RESCUEINT32 GeometryUnitCount(RESCUEBOOL throwIfTooBig);
  RescueGeometryUnit *NthGeometryUnit(RESCUEINT64 zeroBasedOrdinal) {return geometryUnit->NthObject(zeroBasedOrdinal);}
  RescueGeometryUnit *UnitIntersect(RescueUnit *unit);
  RESCUEBOOL DropUnitIntersect(RescueUnit *unit);
  RESCUEBOOL DropUnitIntersect(RescueGeometryUnit *unit);

  void SetWellboreIntersection(RescueWellbore *wellbore,
                              RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
                                      // Declare a new relationship between a cell
                                      // in this grid and a wellbore.
  RESCUEBOOL DropRescueWellboreCell(RescueWellboreCell *cellToDrop) 
                          {return ((*wellboreCell) -= cellToDrop);}
                                      // Destructor will drop it from the surface side.
  RescueWellboreCell *NthWellboreCell(RESCUEINT64 zeroBasedOrdinal) {return wellboreCell->NthObject(zeroBasedOrdinal);}

  void CalculateMinMax();
  RESCUEBOOL MinMaxDirty() {return dirtyMinMax;}
  RESCUEFLOAT MinX() {return minX;}
  RESCUEFLOAT MaxX() {return maxX;}
  RESCUEFLOAT MinY() {return minY;}
  RESCUEFLOAT MaxY() {return maxY;}
  RESCUEFLOAT MinZ() {return minZ;}
  RESCUEFLOAT MaxZ() {return maxZ;}
  RESCUEINT64 PropertyCount64() {return properties->Count64();}
  RESCUEINT32 PropertyCount() {return properties->Count();}
  RescueProperty *NthRescueProperty(RESCUEINT64 zeroBasedOrdinal) 
                  {return properties->NthObject(zeroBasedOrdinal);}
  RescueProperty *PropertyIdentifiedBy(RESCUEINT64 identifier);
  RescueProperty *PropertyNamed(RESCUECHAR *name) {return properties->ObjectNamed(name);}
                                  // Do NOT delete the object returned.
                                    // If you want to remove them from the
                                    // model use the corresponding Drop method.
  RESCUEBOOL DropRescueProperty(RescueProperty *unitToDrop); 
                                   // The property is automatically dropped from
                                   // any RescueTimeStepGroups of which it was a
                                   // member, and any application pointers to it
                                   // become invalid.
  RESCUEBOOL SetKLayerID(RESCUEINT64 zeroBasedNdx, RESCUEINT64 globalID);
  RESCUEINT64 KLayerID(RESCUEINT64 zeroBasedNdx);

  RescueBlockUnit *ParentBlockUnit();
  RescueGeobodyPart *ParentGeobodyPart();

  RESCUEBOOL IsProportional() {return (referenceSurface1 != 0 && referenceSurface2 != 0);}
                                      // Returns TRUE if the RescueGeometry grid is proportional
                                      // (determined by top and bottom surfaces).
  RescueReferenceSurface *TopReferenceSurface() {return referenceSurface1;}
  RescueReferenceSurface *BottomReferenceSurface() {return referenceSurface2;}
  RESCUEFLOAT TopOffset() {return offset1;}
  RESCUEFLOAT BottomOffset() {return offset2;}
                                      // Routines to return information about proportional
                                      // grid definitions.
  RESCUEBOOL IsReferenced() {return (referenceSurface1 != 0 && referenceSurface2 == 0);}
                                      // Returns TRUE if the RescueGeometry grid is of fixed
                                      // thickness, referenced from some surface.
  RescueReferenceSurface *ReferenceSurface() {return referenceSurface1;}
  RESCUEFLOAT SurfaceOffset() {return offset1;}
  RESCUEFLOAT KLayerThickness() {return thickness;}
  RescueLapType LapType() {return onOffLap;}
                                       // Routines to return information about constant
                                       // thickness grids.
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

  void SetCellStatus(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RescueCellStatus newStatus = R_ACTIVE);
  RescueCellStatus CellStatus(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
                                    //
/**********************************************************************************/
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
/***********************************************************************************
:
:  The next five methods have to do with loading and unloading geometry data
:  separately.
:
***********************************************************************************/
  RESCUEBOOL IsLoaded() {return loaded;}
  RESCUEBOOL FileTruncated();
  RESCUEBOOL Load();
  void EnsureLoaded();
  RESCUEBOOL Unload();
  RESCUEBOOL HasChanged() {return hasChanged;}
  void MarkChanged() {hasChanged = TRUE; dirtyMinMax = TRUE;}
  static void LoadRefSurface(RescueReferenceSurface *surface);
/****************************************************************************************

    Methods dealing with RescueDataContainers.

*******************************************************************************************/
  cSetRescueDataContainer *DataContainers();
                             // Will return 0 if properties have not
                             // been defined.
                             // DO NOT delete the class returned.
  cSetRescueDataContainer *DemandDataContainers();
                             // May return an empty container, but
                             // will never return 0.
                             // DO NOT delete the class returned.
/*******************************************************************************************/
  void FindUniquePropertyNames(cSetString *container);
/***********************************************************************************
  Calls added to assist Validator.
************************************************************************************/
  RESCUEINT64 *ObjectCounts();          // Returns an array of four ints where [0] - Count of RescueZStack,
  RESCUEINT32 *ObjectCounts(RESCUEBOOL titb); // [1] - Count of RescueCoordinateLine, 
                                        // [2] - Count of RescueCoordinatePolyLine,
                                        // [3] - Count of RescueSplitLine.  Used by Validator.
                                        // Otherwise useless.  delete[] the array.
  RESCUEINT32 ObjectCountsLength() {return 4;}
  RESCUEINT64 SurfaceToGridCount64() {return surfaceToGrid->Count64();}
  RESCUEINT32 SurfaceToGridCount() {return surfaceToGrid->Count();}
  RESCUEINT32 SurfaceToGridCount(RESCUEBOOL throwIfTooBig);
  RescueColor *GetColor() {return color;} // DO NOT delete the object returned.
private:
  void CommonInitialization();
  RescueGeometry(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parent);
  void SetGrid(RescueGrid *newGrid) {grid = newGrid;}

	RescueGeometryObject **VertexAddress(RESCUEINT64 i, RESCUEINT64 j);
																	// Returns address of array element for a particular vertex.
	RescueGeometryObject **VertexAddress(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 corner);
																	// Returns address for particular corner of a stack of cells.
	RescueGeometryObject **PromoteToSplitLine(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner);
  RESCUEBOOL ProportionalValueAt(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &z);    // These use the first RescueIJSurface
  RESCUEBOOL ReferencedValueAt(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &z);      // defined for the reference surfaces.
  void PrepareModelDelete() {if (surfaceCell != 0) surfaceCell->PrepareModelDelete();}
  virtual void ArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  virtual void UnArchiveData(RescueContext *context, FILE *archiveFile, RESCUEINT64 fileVersion);
  virtual void DropMemory();
  RESCUEBOOL WriteData();
  RESCUEBOOL ReadData(RESCUECHAR *basePathName, RESCUEBOOL versionOnly = FALSE);
  void RelinkGeometryData();
  void RescueDeleteFile();
  void SetColor(RescueColor &colorIn); 
  void SetColor(RescueColor *colorIn);
  RESCUEBOOL WriteWireframeData();          // Writes stubs for earlier versions.
  void CornerValuesPrimitive(RESCUEINT64 kLayer, RESCUEBOOL layerValid, RESCUEFLOAT *buffer, RESCUEINT64 offset, RESCUEINT64 bufferLength);
  void SetUnstructuredGrid(RescueUnstructuredGrid *toSet);
  void SetRadialGrid(RescueRadialGrid *toSet);
  void SetOrientation(RescueOrientationLedger *ledger, RescueCoordinateSystem::Orientation orientation);

  RescueGrid *grid;
	RESCUEINT64 jNodes;
	RESCUEINT64 kNodes;
  RESCUEFLOAT missingValue;
	RescueGeometryObject **vertices;	// One of these for each ij vertex on the grid.
  RescueBitArray *cellStatus;
	RescueVertexType vertexIs;
  RescueModel *parentModel;

  RESCUEINT64 *kLayerIDs;
  RescueReferenceSurface *referenceSurface1;
  RescueReferenceSurface *referenceSurface2;
  RESCUEFLOAT offset1;
  RESCUEFLOAT offset2;
  RESCUEFLOAT thickness;
  RescueLapType onOffLap;

  RESCUEINT64 referenceSurface1Id;
  RESCUEINT64 referenceSurface2Id;

  cSetRescueSurfaceCell *surfaceCell;
  cSetRescueWellboreCell *wellboreCell;
  cSetRescueSurfaceToGrid *surfaceToGrid;
  cSetRescueStairSteppedFault *stairSteps;
  cSetRescueGeometryUnit *geometryUnit;
  cSetRescueProperty *properties;
  RESCUEBOOL hasChanged;
  RESCUEBOOL dirtyMinMax;
  RESCUEBOOL loaded;
  RESCUEINT32 mainFileVersion;
  RESCUEINT32 wireframeVersion;
  RescueColor *color;
  RescueBlockUnit *parentBlockUnit;
  RescueGeobodyPart *parentGeobodyPart;

  RESCUEINT64 referenceID;
  RESCUECHAR *referenceName;
  RescueLGRType lgrType;
  RescueLGRGridType  lgrGridType;
  RESCUEINT64 parentILowBound;
  RESCUEINT64 parentICount;
  RESCUEINT64 parentJLowBound;
  RESCUEINT64 parentJCount;
  RESCUEINT64 parentKLowBound;
  RESCUEINT64 parentKCount;
  RescueGeometry *parentGeometry;
  cSetRescueGeometry *lgrs;
  RESCUEINT64 xWeightLength;
  RESCUEDOUBLE *xWeight;
  RESCUEINT64 yWeightLength;
  RESCUEDOUBLE *yWeight;
  RESCUEINT64 zWeightLength;
  RESCUEDOUBLE *zWeight;
/*
  I went from RESCUEFLOAT to RESCUEDOUBLE in v36 because I was worried about
  running out of signifigant digits in R_WIEGHT_BASED_NOSPAN.
*/
  RescueParametricLGRMap *parametricMap;
  cSetRescueInterfaceSurfaceDesc *isds;
  RescueUnstructuredGrid *unstructuredGrid;
  RescueRadialGrid *radialGrid;

  RESCUEFLOAT minX;
  RESCUEFLOAT maxX;
  RESCUEFLOAT minY;
  RESCUEFLOAT maxY;
  RESCUEFLOAT minZ;
  RESCUEFLOAT maxZ;

  cSetRescueDataContainer *propertyContainers;
  RESCUEINT64 propertyContainerId;

  RESCUECHAR *lgrSetName;
  RESCUECHAR *lgrStartTime;
  RESCUECHAR *lgrEndTime;

  friend class RescueBlockUnit;
  friend class RescueSurface;
  friend class RescueWellbore;
  friend class RescueProperty;
  friend class cSetRescueGeometry;
  friend class RescueGeobodyPart;
  friend class RescueTrimVertex;
  friend class RescuePolyLine;
  friend class RescueWireframe;
  friend class RescueGeometryUnit;
  friend class RescueModel;
  friend class RescuePropertyGroup;
  friend class RescueParametricLGRMap;
  friend class RescueInterfaceSurfaceDesc;
  friend class RescueUnstructuredGrid;
  friend class RescueRadialGrid;
  friend class RescueTimeStepManager;
};

#endif




