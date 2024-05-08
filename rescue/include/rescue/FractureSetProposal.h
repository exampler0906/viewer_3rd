/*************************************************************************

        Fracture representation straw man proposal.

	Based on the work of Miguel Gomez of Golder Associates and
  Jean François Rainaud of IFP, as presented to Rescue in 2006
  and 2007.

        Rod Hanks               January, 2008

****************************************************************************/

class RescueFractureSetStatistics;
class RescueTesselatedFractureSet;
class RescueTesselatedFracture;
class RescuePolygonalFractureSet;
class RescuePolygonalFracture;
class RescueSimpleFractureSet;
class RescueFractureSet;
class cSetRescueFractureSet;
class RescueFractureSetRelation;
class cSetRescueFractureSetRelation;
class RescueFractureNetwork:public RescueHistoryObject
{
public:
  ~RescueFractureNetwork();
  RescueFractureNetwork(RescueModel *model);
private:
  cSetRescueFractureSet *sets;
  cSetRescueFractureSetRelation *relationships;
};

class cSetRescueFractureSet:public RescueObject
{
public:
  ~cSetRescueFractureSet();
  cSetRescueFractureSet(RescueContext *context);
  RESCUEUINT64 Count() {return count;}
  RescueFractureSet *NthFractureSet(RESCUEUINT64 zbn);
  void Add(RescueFractureSet *toAdd);
private:
  RESCUEUINT64 count;
  RESCUEUINT64 allocated;
  RescueFractureSet *sets;
};

class RescueFractureSet:public RescueObject
{
/* Abstract class that represents all three possible fracture set types,
   RescueSimpleFractureSet, RescuePolygonalFractureSet, RescueTesselatedFractureSet.

  As RescueObject's, you can use IsA() to find out which type you actually have.
*/
public:
  ~RescueFractureSet();
  RescueFractureSet(RescueContext *context):RescueObject(context) {};
  virtual RESCUEUINT64 FaceCount()=0;
  RescueDataContainer *DemandDataContainer();
/*
  RescueDataContainer is used to put properties on a RescueFractureSet.  All of
  the sets are perfect for a 1D grid of Count() nodes, each node giving a property
  of a particular fracture.
*/
  RescueFractureSetStatistics *Statistics();
private:
  RescueFractureSetStatistics *stats;
  RescueDataContainer *container;
};

class RescueSimpleFractureSet:public RescueFractureSet
{
public:
  ~RescueSimpleFractureSet();
  RescueSimpleFractureSet(RescueContext *context);

  typedef enum {ELLIPSE,RECTANGLE} FractureType;

  void EnsureCapacity(RESCUEUINT64 allocateAtLeastThisMany);
  RESCUEUINT64 Allocated() {return allocated;}
  RESCUEUINT64 FaceCount() {return count;}
  RESCUEUINT64 SetCount(RESCUEUINT64 newCount);
  RESCUEFLOAT **CenterVertex() {return centerVertex;}
  RESCUEFLOAT **GreatAxisVertex() {return centerVertex;}
  RESCUEFLOAT **SmallAxisVertex() {return centerVertex;}
  FractureType *Types() {return types;}
private:
  RESCUEUINT64 allocated;
  RESCUEUINT64 count;
  RESCUEFLOAT *centerVertex[3];
  RESCUEFLOAT *greatAxisVertex[3];
  RESCUEFLOAT *smallAxisVertex[3];
  FractureType *types;
};

class RescuePolygonalFracture
{
public:
  ~RescuePolygonalFracture();
  RescuePolygonalFracture();
  RESCUEFLOAT **Vertices() {return m_vertices;}
  RESCUEUINT64 Count() {return m_vertexCount;}
  void SetVertices(RESCUEUINT64 arraySize, RESCUEFLOAT *vertices[3]);
private:
  RESCUEFLOAT *m_vertices[3];
  RESCUEUINT64 m_vertexCount;
};

class RescuePolygonalFractureSet: public RescueFractureSet
{
public:
  ~RescuePolygonalFractureSet();
  RescuePolygonalFractureSet(RescueContext *context);
  RESCUEUINT64 FaceCount() {return count;}
  RescuePolygonalFracture *NthFracture(RESCUEUINT64 zbn);
  void Add(RescuePolygonalFracture *toAdd);
private:
  RESCUEUINT64 allocated;
  RESCUEUINT64 count;
  RescuePolygonalFracture *fractures;
};

class RescueTesselatedFracture
{
public:
  ~RescueTesselatedFracture();
  RescueTesselatedFracture();
  typedef enum {GL_TRIANGLES, 
                GL_QUADS, 
                GL_TRIANGLE_STRIP, 
                GL_QUAD_STRIP, 
                GL_TRIANGLE_FAN} GLMode;
  GLMode Mode();
  void SetMode(GLMode modeIn);
  RESCUEUINT64 VertexCount() {return m_vertexCount;}
  RESCUEUINT64 FaceCount(); // Calculated based on vertex count and mode.
  RESCUEFLOAT **Vertices() {return m_vertices;}
  void SetVertices(RESCUEUINT64 arraySize, RESCUEFLOAT *vertices[3]);
private:
  GLMode mode;
  RESCUEFLOAT *m_vertices[3];
  RESCUEUINT64 m_vertexCount;
};

class RescueTesselatedFractureSet: public RescueFractureSet
{
public:
  ~RescueTesselatedFractureSet();
  RescueTesselatedFractureSet(RescueContext *context);
  RESCUEUINT64 FaceCount();  // Sum of all RescueTesselatedFracture::FaceCount().
  RESCUEUINT64 FeatureCount() {return count;}
  RescueTesselatedFracture *NthFeature(RESCUEUINT64 zbn);
  void Add(RescueTesselatedFracture *toAdd);
private:
  RESCUEUINT64 allocated;
  RESCUEUINT64 count;
  RescueTesselatedFracture *features;

};

class cSetRescueFractureSetRelation:public RescueObject
{
public:
  ~cSetRescueFractureSetRelation();
  cSetRescueFractureSetRelation(RescueContext *context);
  RESCUEUINT64 Count() {return count;}
  RescueFractureSetRelation *NthRelation(RESCUEUINT64 zbn);
  void Add(RescueFractureSetRelation *toAdd);
private:
  RESCUEUINT64 count;
  RESCUEUINT64 allocated;
  RescueFractureSetRelation *relations;
};

class RescueFractureSetRelation:public RescueObject
{
/*
  Describes a relationship between sets (primary, secondary,
  early, late, etc.
*/
public:
  ~RescueFractureSetRelation();
  RescueFractureSetRelation(RescueContext *context);
  RescueFractureSet *PrimeSet();
  void SetPrimeSet(RescueFractureSet *newPrime);
  RescueFractureSet *SecondarySet();
  void SetSecondarySet(RescueFractureSet *newSecondary);
  RCHString *PrimaryRelation();
  void SetPrimaryRelation(RESCUECHAR *relationVerb);
  RCHString *SecondaryRelation();
  void SetSecondaryRelation(RESCUECHAR *secondaryVerb);
};

class RescueFractureSetStatistics: public RescueObject
{
public:
  ~RescueFractureSetStatistics();
  RescueFractureSetStatistics(RescueContext *context);
  cNameValuePair *Orientation() {return orientation;}
  cNameValuePair *Size() {return size;}
  cNameValuePair *Aperture() {return aperture;}
  cNameValuePair *Conductivity() {return conductivity;}
public:
  cNameValuePair *orientation;
  cNameValuePair *size;
  cNameValuePair *aperture;
  cNameValuePair *conductivity;
};
