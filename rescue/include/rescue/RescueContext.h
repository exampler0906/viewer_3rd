/********************************************************************

  RescueContext.h

  Contains all the context information required for RescueModel
  manipulation.

  Rod Hanks,  February, 2002

*********************************************************************/
#ifndef RescueContext_H
#define RescueContext_H

class RescueProgressReporter;
class RCHString;
#include "cSetString.h"
class RescueIdTree;
class RescueModel;

class RescueContext
{
public:
  RescueContext();
  ~RescueContext();
  RescueProgressReporter *RegisterProgressReporter(RescueProgressReporter *newProgressObject);
  void SetAutoBackup(RESCUEBOOL newState = FALSE) {backupEnabled = newState;}
                                       // Turns off automatic creation of .bak files, which
                                       // by default are always created.
  void SetFileNameManipulation(RESCUEBOOL newState = FALSE) {vetFileNames = newState;}
                                      // Turns off intelligent manipulation of file names,
                                      // which by default are on.
  void CleanFromUnarchive();          // Deletes a model which was half-created
                                      // due to an interrupted UnarchiveModel
                                      // command.  Do not call this function at
                                      // any other time.
  void SetLoadOnDemand(RESCUEBOOL newState = TRUE) {delayedPropertyLoad = newState;}
  RESCUEBOOL DelayedPropertyLoad() {return  delayedPropertyLoad;}
                                      // These methods control the loading of RescueArray
                                      // objects, used in RescueProperty and RescueWellborePropery.
                                      // Default DelayedPropertyLoad() is TRUE.
  void SetLoadOnDemand2(RESCUEBOOL newState = TRUE) {delayedGeometryLoad = newState;}
  RESCUEBOOL DelayedGeometryLoad() {return  delayedGeometryLoad;}
                                      // These methods control the loading of geometry information
                                      // for surfaces and BUGs, as well as wireframe information.
                                      // Default DelayedGeometryLoad is TRUE.
  void RescueProgress(const RESCUECHAR *progressDescription);
  RESCUECHAR *GetLock(RESCUECHAR *rescueFileName, RESCUEBOOL needWrite = FALSE, RESCUEBOOL forceLock = FALSE);
                                    // Returns null if lock is acquired successfully. Otherwise
                                    // returns a character string (which should be freed by the
                                    // application) containing owner pid \t date acquired \n of
                                    // all blocking locks.
                                    // If forceLock == TRUE, will attempt to override existing
                                    // lock and return null.  All blocking locks will be lost.
  void ReleaseLock(RESCUECHAR *rescueFileName);
                                    // Release lock.  Fails silently if another process has
                                    // overridden the lock.
  RESCUEBOOL CheckLock(RESCUECHAR *rescueFileName);
                                    // Returns TRUE if the current process is the owner of the lock.
  void VetFileName(RCHString *fileName, RESCUEBOOL creating, RESCUEBOOL desireBinary);
  RESCUEINT32 FileVersion(RESCUECHAR *pathName);
                                      // Returns the Rescue file version of the
                                      // path.  -1 indicates the pathName is not
                                      // a Rescue model file.  Values of 12 or above
                                      // are almost certianly Rescue model files.
                                      // Values of 5-11 probably are, but could be
                                      // other types of files, because signatures
                                      // were not added to files until version 12.
  RESCUEINT32 SoftwareVersion(RESCUECHAR *pathName);
                                      // Returns the software version that wrote the main file.
                                      // -1 if unknown.
  void SoftwareVersion(RESCUECHAR *pathName, int &fileVersion, int &subVersion);
                                      // Returns the software version and the subversion.
  static RESCUEINT32 LibraryVersion();
                                      // Returns the version of the currently loaded library.
  static RESCUEINT32 LibrarySubVersion();     // Returns the sub-version of the currently loaded library.
                                      // Handy for RJNI users who can't include the header.
  RESCUEBOOL TypeMarker(RESCUECHAR *pathName, RESCUEUCHAR *buffer, RESCUEINT64 bufLen);
                                      // If the file version is at least 37, returns true and
                                      // fills in buffer contents, which should be 20 but may
                                      // be less.  If more than 20 only 20 bytes are returned.
                                      // The buffer contents tells you the size and endianness
                                      // of numbers in the model.
                                      // If file version is less than 37, returns false and
                                      // nothing is written to the buffer.
  RESCUEBOOL FileTruncated(RESCUECHAR *pathName);
                                      // Returns true if the main file appears to be truncated.
  RESCUEBOOL BinaryFlag() {return binaryFlag;}
  size_t UIntSize() {return uintSize;}
  RESCUEBOOL UIntSwap() {return uintSwap;}
  size_t IntSize() {return intSize;}
  RESCUEBOOL IntSwap() {return intSwap;}
  int ReadFileVersion() {return readFileVersion;}
  int FileVersion() {return fileVersion;}
  RESCUEINT64 NextId() {return (uniqueIDCounter++);}

  const char *LastError(); // May be zero.  Do not delete.
  void ClearError();
  RESCUEBOOL LittleEndian() {return littleEndian;} // Returns true if little endian.
  RESCUEBOOL Write32() {return write32;}  // Returns true if user has elected to write out 32 bit model.

  static RESCUEBOOL SamePoint(RESCUEFLOAT x1, RESCUEFLOAT y1, RESCUEFLOAT z1,
                              RESCUEFLOAT x2, RESCUEFLOAT y2, RESCUEFLOAT z2);
                                      // Returns true if (x1, y1, z1) is the same as (x2, y2, z2).
  static void CurrentISOTime(RCHString &buffer);

  static void SwapArray(RESCUEFLOAT *array, RESCUEINT64 arrayLength);
  static void SwapArray(RESCUEDOUBLE *array, RESCUEINT64 arrayLength);
  static void SwapArray(RESCUECHAR *array, RESCUEINT64 arrayLength);
  static void SwapArray(RESCUEUCHAR *array, RESCUEINT64 arrayLength);
  static void SwapArray(RESCUEINT32 *array, RESCUEINT64 arrayLength);
  static void SwapArray(RESCUESHORT *array, RESCUEINT64 arrayLength);
  static void SwapArray(RESCUEUSHORT *array, RESCUEINT64 arrayLength);

  static void SwapAxes(RESCUEFLOAT *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes);
  static void SwapAxes(RESCUEINT32 *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes);
  static void SwapAxes(RESCUEUSHORT *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes);
  static void SwapAxes(RESCUEDOUBLE *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes);
  static void SwapAxes(RESCUEUCHAR *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes);

  static void SwapAxes(RESCUEFLOAT *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes, bool swapK, RESCUEINT64 kNodes);
  static void SwapAxes(RESCUEINT32 *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes, bool swapK, RESCUEINT64 kNodes);
  static void SwapAxes(RESCUEUSHORT *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes, bool swapK, RESCUEINT64 kNodes);
  static void SwapAxes(RESCUEDOUBLE *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes, bool swapK, RESCUEINT64 kNodes);
  static void SwapAxes(RESCUEUCHAR *array, bool swapI, RESCUEINT64 iNodes, bool swapJ, RESCUEINT64 jNodes, bool swapK, RESCUEINT64 kNodes);

  static RESCUEINT64* Allocate64For32(RESCUEINT32 *inputArray, RESCUEINT32 cellToCellCount, RESCUEBOOL freeInput);
  static RESCUEINT32* Allocate32For64(RESCUEINT64 *inputArray, RESCUEINT32 cellToCellCount, RESCUEBOOL freeInput, RESCUEBOOL throwIfTooBig);
  static RESCUEINT32 Return32For64(RESCUEINT64 output, RESCUEBOOL throwIfTooBig);
private:
  RCHString *LockFileForRescueFile(RESCUECHAR *rescueFileName);
  RESCUEBOOL FileTruncatedPrimitive(RESCUECHAR *fileName);
  RESCUEUINT64 FileSizePrimitive(RESCUECHAR *fileName);
  void SetError(const char *errorMessage);

  RESCUEINT64 uniqueIDCounter;
  RESCUEINT32 fileVersion;                    // This is the version number of the file we are
                                              // writing now.
  RESCUEINT32 readFileVersion;                // This is the version number of the file we are
                                              // reading now.
  RESCUEINT32 readFileMainSoftwareVersion;    // These are the versions that wrote the software.
  RESCUEINT32 readFileSubSoftwareVersion;     // Valid only during unarchive operations.

  RescueProgressReporter *progressReportObject;
  cSetString locksAcquired;
  RescueIdTree *wellboreProperties;      // These objects are used only during
  RescueIdTree *timeStepGroups;          // relinking.
  RescueIdTree *properties;
  RescueIdTree *modelPropertyGroups;
  RescueIdTree *macroVolumes;
  RescueIdTree *grids;
  RescueIdTree *geometries;
  RescueIdTree *geobodyVolumes;
  RescueIdTree *geobodyParts;
  RescueIdTree *blockUnitSides;
  RescueIdTree *propertyGroups;
  RESCUEBOOL delayedPropertyLoad;
  RESCUEBOOL delayedGeometryLoad;
  RESCUEBOOL vetFileNames;
  RESCUEBOOL backupEnabled;
  RescueModel *unarchivingModel;
  RCHString *lastError;
public:
  RESCUEBOOL binaryFlag;
protected:
  size_t uintSize;
  RESCUEBOOL uintSwap;
  size_t intSize;
  RESCUEBOOL intSwap;
private:
  FILE *archiveFile;
  RESCUEBOOL littleEndian;
  RESCUEBOOL write32;

  friend class RescueObject;
  friend class RescueModel;
  friend class RescueArray;
  friend class RescueGeobodyPart;
  friend class RescueGeobodyVolume;
  friend class RescueGeometry;
  friend class RescueWireframe;
  friend class RescueBlockUnitSide;
  friend class RescueTriangulatedSurface;
  friend class RescueSurface;
  friend class RescueColorTable;
  friend class RescueGrid;
  friend class RescueHistory;
  friend class RescueTripletArray;
  friend class RescueMacroVolume;
  friend class RescueModelPropertyGroup;
  friend class RescueProperty;
  friend class RescuePropertyGroup;
  friend class RescueTimeStepGroup;
  friend class RescueWellboreProperty;
  friend class RescueStairSteppedFault;
  friend class cSetRescueDataContainer;
  friend class RescueDocumentList;
  friend class RescuePolyLine;
};
#endif



