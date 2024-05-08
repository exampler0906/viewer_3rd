/********************************************************************

  RescueEventDescr.h

  This object describes an unconformity or a diapir.

  Rod Hanks,  June 2002

*********************************************************************/
#ifndef RESCUEEventDescr_H
#define RESCUEEventDescr_H

#include "myHeaders.h"
#include "RescueLogicalOrderEntry.h"
#include "RescueSection.h"
#include "cBagRescueSection.h"

class RescueEventDescr:public RescueLogicalOrderEntry
{
public:
  typedef enum {UNCONFORMITY, DIAPIR} EventType;
                              // These objects are instantiated via
                              // RescueModel::MakeUnconformity and
                              // RescueModel::MakeDiapir methods.
  EventType Type() {return eventType;}
  RCHString *EventDescrName() {return eventDescrName;}
                              // Do NOT delete the returned object.
                              // It will not be null, but the string may have zero
                              // length, or the String() method of the object may
                              // return null.
  void SetEventDescrName(RESCUECHAR *newEventDescrName) {(*eventDescrName) = newEventDescrName;}
  virtual ~RescueEventDescr();
          // Do not delete these objects.  Use RescueModel::DropRescueEventDescr.

  void AddSection(RescueSection *existingSection)
                        {(*sections) += existingSection;}
  void DropSection(RescueSection *existingSection)
                        {(*sections) -= existingSection;}
  RESCUEINT64 SectionCount64() {return sections->Count64();}
  RESCUEINT32 SectionCount() {return sections->Count();}
  RescueSection *NthSection(RESCUEINT64 zeroBasedOrdinal) 
                        {return sections->NthObject(zeroBasedOrdinal);}
                  // RescueEventDescr does not "own" RescueSections,
                  // so it does not create or delete them, merely
                  // catalogs relationships to them. 
  RESCUEBOOL FullEvents(RescueModel *model);
                  // Provided for ease of writing v25 models.
  virtual RESCUEBOOL IsOfType(_RescueObjectType thisType);
					// Returns TRUE if the object is a
					// member of the specified class.
protected:
  virtual void Archive(RescueModel *model, RescueContext *context, FILE *archiveFile);
  RescueEventDescr(RescueContext *context, FILE *archiveFile);
  virtual void Relink(RescueObject *object); // Pass RescueModel.

private:
  RescueEventDescr(RescueContext *context,
                   RESCUECHAR *nameIn,
                   EventType flagIn);

  EventType eventType;
  RCHString *eventDescrName;
  cBagRescueSection *sections; 

  cBagInt *sectionIds;
  RESCUEINT64 horizonAboveID;           // These are used only when loading older
  RESCUEINT64 horizonBelowID;           // models.
  RESCUEINT64 eventDescrAboveID;
  RESCUEINT64 eventDescrBelowID;

  friend class cSetRescueEventDescr;
  friend class RescueModel;
  friend class RescueEvent;
  friend class RescueLogicalOrder;
};

#endif




