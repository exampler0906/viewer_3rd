/**************************************************************************

	RescueProgressReporter.h

	An abstract class which may be subclassed to report progress during
  RESCUE operations.  Create an instance of the subclass and pass it to
  RescueModel::RegisterProgressReporter.

	Rod Hanks,	November 1997

**************************************************************************/

#ifndef RescueProgressReporter_H
#define RescueProgressReporter_H
#include "myHeaders.h"

class RescueProgressReporter

{
public:
  virtual void ReportProgress(const RESCUECHAR *phaseDescription)=0;
};

#endif




