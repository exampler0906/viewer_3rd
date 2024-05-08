/********************************************************************

  RescueColor.h

  A (possibly) named rgb.

  Rod Hanks,  February, 1999

*********************************************************************/
#ifndef RESCUECOLOR_H
#define RESCUECOLOR_H

#include "myHeaders.h"
#include "RescueObject.h"
class RCHString;

class RescueColor:public RescueObject
{
public:
  RescueColor(RescueColor &otherColor);
  RescueColor(RescueContext *context, int red, int green, int blue, RESCUECHAR *name=0);
  RescueColor(RescueContext *context, RESCUEFLOAT red, RESCUEFLOAT green, RESCUEFLOAT blue, RESCUECHAR *name=0);
  ~RescueColor();
  void SetColor(int red, int green, int blue, RESCUECHAR *name=0);
  void SetColor(RESCUEFLOAT red, RESCUEFLOAT green, RESCUEFLOAT blue, RESCUECHAR *name=0);
  void GetColor(int &red, int &green, int &blue);
  void GetColor(RESCUEFLOAT &red, RESCUEFLOAT &green, RESCUEFLOAT &blue);
  RESCUECHAR *ColorName() {return colorName->String();}

  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
private:
  void CommonInitialization();
  RescueColor(RescueContext *context, FILE *archiveFile);
  virtual void Archive(RescueContext *context, FILE *archiveFile);

  RCHString *colorName;
  RESCUEFLOAT red;
  RESCUEFLOAT green;
  RESCUEFLOAT blue;
  RescueContext *context;
/*
  We have to keep the context in the color so we can have a copy constructor.
  We keep the context arguments on archiving and unarchiving to lessen the
  impact of somebody moving a color from one model to another with the copy
  constructor (which is not a supported technique, use SetColor instead).
*/

  friend class RescueGeometry;
  friend class RescueSurface;
  friend class RescueColorTable;
  friend class RescueBlockUnit;
  friend class RescueGeobodyPart;
};

#endif

