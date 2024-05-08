/********************************************************************

  RescueTriangulatedSurface.h

  A representation of a triangulated surface for RescueSurface.

  Rod Hanks,  June, 1999

*********************************************************************/
#ifndef RescueTriangulatedSurface_H
#define RescueTriangulatedSurface_H

#include "myHeaders.h"
#include "cSetRescueTriangleVertex.h"
#include "cSetRescueTriangleFace.h"
#include "RescueProperty.h"
class RescueTrimVertex;
class RescueTriangleVertex;
#include "cSetRescueSOctTreeNode.h"
class RescueSOctTreeNode;
class RescueIdTree;
class RescueBitArray;

class RescueTriangulatedSurface:public RescueObject
{
public:

  virtual RESCUEINT64 VertexCount64() {return vertices->Count();}
  virtual RESCUEINT32 VertexCount() {return (RESCUEINT32) vertices->Count();}
  virtual RESCUEINT32 VertexCount(RESCUEBOOL throwIfTooBig);
  virtual RescueTriangleVertex *NthVertex(RESCUEINT64 zeroBasedOrdinal) {return vertices->NthObject(zeroBasedOrdinal);}
  virtual RESCUEINT64 FaceCount64() {return faces->Count64();}
  virtual RESCUEINT32 FaceCount() {return faces->Count();}
  virtual RESCUEINT32 FaceCount(RESCUEBOOL throwIfTooBig);
  virtual RescueTriangleFace *NthFace(RESCUEINT64 zeroBasedOrdinal) {return faces->NthObject(zeroBasedOrdinal);}

  RESCUEFLOAT *Vertices(RESCUEINT64 &vertexCount);    // Returns a RESCUEFLOAT[vertexCount * 3] array of vertices.
  RESCUEINT64 *Faces(RESCUEINT64 &faceCount);           // Returns an RESCUEINT64[faceCount * 3] array of face indexes
  RESCUEFLOAT *Vertices(RESCUEINT32 &vertexCount);    // Returns a RESCUEFLOAT[vertexCount * 3] array of vertices.
  RESCUEINT32 *Faces(RESCUEINT32 &faceCount);           // Returns an RESCUEINT32[faceCount * 3] array of face indexes
                                         // (goes with the vertices array).
  cSetRescueTriangleFace *FaceList() {return faces;}
  cSetRescueTriangleVertex *VertexList() {return vertices;}
/*********************************** Warning **********************************************
  
   Changing the number of faces in a triangulated surface invalidates any RescueProperty
   objects which are defined on the triangulated representation of that surface.
  
******************************************************************************************/
  virtual void AddVertex(RescueTriangleVertex *toAdd) {(*vertices) += toAdd;}
  virtual void AddFace(RescueTriangleFace *toAdd)    {(*faces) += toAdd;}
  virtual RESCUEBOOL DropVertex(RescueTriangleVertex *toDrop);   // Automatically drops all faces of which it is
                                                   // a member.
  virtual RESCUEBOOL DropFace(RescueTriangleFace *toDrop);       // Does not drop vertices that are part of the face,
                                                   // but does unhook them from the face.
  virtual RescueGrid *Grid(RescueProperty::AttachmentPoint howAttached);

  virtual ~RescueTriangulatedSurface();
  virtual RescueSurface *ParentSurface() {return parentSurface;}
  RESCUEBOOL Contains(RescueTriangleVertex *vertex);

  void SetFaceStatus(RESCUEINT64 i, RescueIJSurface::RescueFaceStatus newStatus = RescueIJSurface::R_FACE_ACTIVE);
  RescueIJSurface::RescueFaceStatus FaceStatus(RESCUEINT64 i);
/*************************************** OctTrees ***********************************

 OctTrees should be created after the surface is completely constructed.  If the surface
 needs to be changed, they should be dropped and re-created.

****************************************************************************************/
  virtual RESCUEINT64 OctTreeCount64() {return octTrees->Count64();}
  virtual RESCUEINT32 OctTreeCount() {return octTrees->Count();}
  virtual RESCUEINT32 OctTreeCount(RESCUEBOOL throwIfTooBig);
  virtual RescueSOctTreeNode *NthOctTree(RESCUEINT64 zeroBasedOrdinal) {return octTrees->NthObject(zeroBasedOrdinal);}
  virtual RESCUEBOOL DropOctTree(RescueSOctTreeNode *toDrop) {return (*octTrees) -= toDrop;}
/***********************************************************************************

  The next six methods have to do with loading and unloading triangulated surfaces
  separately.

***********************************************************************************/
  virtual RESCUEBOOL IsLoaded() {return loaded;}
  virtual RESCUEBOOL Load();
  virtual RESCUEBOOL FileTruncated();
  virtual RESCUEBOOL Unload();
  virtual RESCUEBOOL HasChanged() {return hasChanged;}
  virtual void MarkChanged() {hasChanged = TRUE;}
/***********************************************************************************/
  virtual RESCUEINT32 Version(RESCUEBOOL reload = FALSE); // These methods return a version number for the file which
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
protected:
  RescueTriangulatedSurface(RescueContext *context,
                            RescueSurface *parentIn, 
                            cSetRescueTriangleVertex *verticesIn,
                            cSetRescueTriangleFace *facesIn)
                            :RescueObject(context)
                            ,verticesLookups(0)
                            ,parentSurface(parentIn)
                            ,vertices(verticesIn)
                            ,faces(facesIn)
                            ,octTrees(new cSetRescueSOctTreeNode())
                            ,faceGrid(0)
                            ,nodeGrid(0)
                            ,arrayVersion(0)
                            ,hasChanged(TRUE)
                            ,loaded(TRUE)
                            ,faceStatus(0) {};
  RescueTriangulatedSurface(RescueContext *context, FILE *archiveFile);
  virtual void Archive(FILE *archiveFile);
  virtual void Relink(RescueObject *parentModel);
  virtual void RelinkPropertyGrids();
  RescueTriangleVertex *TriangleVertexIdentifiedBy(RESCUEINT64 id);

  virtual void ArchiveData(FILE *archiveFile);
  virtual void UnArchiveData(FILE *archiveFile, RESCUEINT64 fileVersion);
  virtual void DropMemory();
  virtual RESCUEBOOL ReadData(RESCUECHAR *basePathName, RESCUEBOOL versionOnly = FALSE);
  virtual RESCUEBOOL WriteData();
  virtual void RescueDeleteFile();
  void SwapAxes(bool swapI, RescueGridAxis *iAxis, bool swapJ, RescueGridAxis *jAxis);

  RescueIdTree *verticesLookups;
  RescueSurface *parentSurface;
  cSetRescueTriangleVertex *vertices;
  cSetRescueTriangleFace   *faces;
  cSetRescueSOctTreeNode   *octTrees;
  RescueGrid *faceGrid;
  RescueGrid *nodeGrid;
  RESCUEINT32 arrayVersion;
  RESCUEBOOL hasChanged;
  RESCUEBOOL loaded;
  RescueBitArray *faceStatus;

  friend class RescueTriangleFace;
  friend class RescueSurface;
  friend class RescueProperty;
  friend class RescueSOctTreeNode;
};

#endif

