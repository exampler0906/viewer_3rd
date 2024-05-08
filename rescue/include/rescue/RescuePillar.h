/********************************************************************

  RescuePillar.h

  The geometry is described by the control points, which are stored
  in a cSetRescuePoint.  The base point is NthObject(0) and the top
  point is NthObject(Count() - 1).

  p_1.z < p_2.z ... < p_i.z < ... p_n.z

  The values are stored in real values.  No transformation need be
  applied.  Z-values below the datum (normally mean sea level) are
  negative, above the datum are positive.  The logical geometries are:

    VERTICAL: 2 control points and is_vertical = true.  The x and y
              of the second control point is not stored.  When reading
              the x and y value of the second control point is set equal
              to the first control point.
    LINEAR:   2 control points and is_vertical = false.
    LISTRIC:  3 control points, follows spline curve.
    CURVED:   5 control points, follows a spline curve.
    OTHER:    Any number of points can be stored but automatic
              calculation of the geometry is not available.

  Truncation:
    top_truncation:  Is != 0 if the pillar is truncated to top by a
                     truncating pillar.  The LAST control point is
                     attached to the truncating pillar.
    base_truncation: Is != 0 if the pillar is truncated to base by 
                     a truncating pillar.  The FIRST control point is
                     attached to the truncating pillar.

  In addition, the class has a separate list of z depth values to
  supply the depth of each k layer boundary in the parent BUG geometry,
  much like RescueZStack.  The control ints determine the x, y
  values for each node (possibly via a spline fit) and the z values
  determine the 3rd coordinate.

  Rod Hanks,  October 2003

*********************************************************************/
#ifndef RescuePillar_H
#define RescuePillar_H

#include "myHeaders.h"
#include "RescueGeometryObject.h"
#include "RescuePoint.h"
#include "cSetRescuePoint.h"

class RescueGeometry;
class RescueTruncation;
class RescueSplineCoef;

class RescuePillar:public RescueGeometryObject
{
  cSetRescuePoint *ctrlPoints;
  RescueTruncation *top_truncation;
  RescueTruncation *base_truncation;
  RescueSplineCoef *splineCoefs;
  RESCUEINT64 splineCoefsCount;
  RESCUEBOOL isVertical;
  RESCUEINT64 zCount;
  RESCUEINT64 dirCount;
  RESCUEFLOAT **zValues;
public:
  RescuePillar();
  ~RescuePillar();

  RescueGeometry::RescueVertexType VertexIs() {return RescueGeometry::R_SPLINE_LINE;}			
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEINT64 corner, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RescueGeometry *geometry, RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, 
							RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
	void Values(RESCUEINT64 k, RESCUEFLOAT &z);
	void Values(RESCUEINT64 k, RESCUEINT64 corner, RESCUEFLOAT &z);
                                    // Read values, C++.
  RESCUEFLOAT *NodeValues(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k);
  RESCUEINT32 NodeValuesLength() {return 3;}
                                    // Corresponds to 
                                    // RESCUEBOOL Values(RESCUEINT64 i, RESCUEINT64 j, RESCUEINT64 k, RESCUEFLOAT &x, RESCUEFLOAT &y, RESCUEFLOAT &z);
                                    // Returns 0 if the value would have been FALSE.
                                    // DO delete the returned array.
  RESCUEFLOAT KValue(RESCUEINT64 k);              // Corresponds to Values(RESCUEINT64 k, RESCUEFLOAT &z);
  RESCUEFLOAT KValue(RESCUEINT64 k, RESCUEINT64 dir);     // Corresponds to Values(RESCUEINT64 k, RESCUEINT64 dir, RESCUEFLOAT &z);
                                    // Read values, especially Java.
  void ZValue(RESCUEINT64 k, RESCUEFLOAT newZValues);
  void ZStack(RescueGeometry *geometry, RESCUEFLOAT *newZValues);
  void ZStack(RescueGeometry *geometry, RESCUEINT64 direction, RESCUEFLOAT *newZValues);
                                // Set z values.
  RESCUEBOOL IsSplit() const;

  RESCUEBOOL IsVertical() const {return isVertical;}
  void SetIsVertical(RESCUEBOOL verticalIn) {isVertical = verticalIn;}
  RESCUEBOOL IsTruncated() const;
  RescueTruncation *TopTruncation() {return top_truncation;}
  RescueTruncation *BaseTruncation() {return base_truncation;}
                                // Don't delete the returned object.
  void SetTopTruncation(RescueTruncation *newTop);
  void SetBaseTruncation(RescueTruncation *newBase);
                                // Don't pass a RescueTruncation that you have
                                // used anyplace else.  Becomes the property of
                                // Rescue.  You may pass 0.
  void AddControlPoint(RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z);
  void rebuildSplineCoeffs();
                                // After you add no more than 5 control points,
                                // use rebuildSplineCoeffs() to make the spline
                                // coefficients.
  void AddControlPoint(RESCUEFLOAT x, RESCUEFLOAT y, RESCUEFLOAT z, 
                       RESCUEFLOAT xb, RESCUEFLOAT xc, RESCUEFLOAT xd,
                       RESCUEFLOAT yb, RESCUEFLOAT yc, RESCUEFLOAT yd);
                                // Using this method you may add as many
                                // control points as you wish.  You pass
                                // both the point and the spline.  DO NOT
                                // use rebuildSplineCoeffs() with more than
                                // 5 control points.
                                //
                                // The spline coefficients associated with
                                // the last point probably aren't used, but
                                // you have to specify something anyway.
  RescuePoint *getByZ(RESCUEFLOAT z) const;
                                // Delete the return point when you are done.
  RescuePoint *getMinTangent(); //Get tangent at the base of the pillar, 
                                //normalized, pointing upwards.
                                //I realize this is a lot more annoying 
                                // than returning RescuePoint
                                // because you have to dispose of
                                // the RescuePoint but it is necessary for Java.
  RescuePoint *getMaxTangent(); // Delete when you get back.
  RESCUEINT32 getNumCtrlPoints() {return ctrlPoints->Count();}
  RescuePoint *getMinCtrlPoint() const;
  RescuePoint *getMaxCtrlPoint() const;
  RescuePoint *getCtrlPointAt(RESCUEINT64 ndx) const;
                                // DO NOT delete the points you get back,
                                // and don't change it unless you want to
                                // move the line.
  RescueSplineCoef *getXSplineCoefAt(RESCUEINT64 ndx) const;
  RescueSplineCoef *getYSplineCoefAt(RESCUEINT64 ndx) const;
  //<--   More convienient for C++ use -->
  const RescuePoint getMinCtrlPointRef() const;
  const RescuePoint getMaxCtrlPointRef() const;
  const RescuePoint getMinTangentRef() const;
  const RescuePoint getMaxTangentRef() const;
  const RescuePoint getRefByZ(RESCUEFLOAT z) const;
  //-->
protected:
  RescuePillar(RescueContext *context, FILE *archiveFile, RESCUEBOOL compress);
  virtual void Archive(RescueContext *context, RESCUEINT64 kLayers, FILE *archiveFile, RESCUEBOOL compress);
  void SwapKAxis(RESCUEINT64 kNodes);
  void SwapIJAxis(bool swapI, RESCUEINT64 iLowBound, RESCUEINT64 iCount, 
                  bool swapJ, RESCUEINT64 jLowBound, RESCUEINT64 jCount);
  friend class RescueGeometry;
};

#endif


