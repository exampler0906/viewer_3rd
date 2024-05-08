/********************************************************************

  RescueTruncation.h

  A Truncation on a Pillar grid.  We don't need the overhead
  so this is not a RescueObject.

  Either truncation of base or top is stored here:

             #     *        #
           A |   ./         |
             |  ./ B        |
             | ./           *
             |./          A | \. C
             *              |  \.
             |              |   \.
             |              |    \.
             #              #      *

  Pillar A: Is the truncating pillar: Does not know anything.
  Pillar B: Is the BASE truncated pillar and has a pointer to
            the Truncation. i,j gives the node of the pillar A.
  Pillar C: Is the TOP truncated pillar and has a pointer to the
            Truncation.  i,j gives the node of pillar A.

  The self_fault_id and self_limit are used for self truncating
  pillars only.  Then the same pillar is truncating and truncated,
  and is found where the truncated pillar branches from the truncating
  pillar.

  self_fault_id: The id of the fault which is truncating
  self_limit:    The z value where the truncation begins.

  Rod Hanks,  Oct, 2003

*********************************************************************/
#ifndef RescueTruncation_H
#define RescueTruncation_H

#include "myHeaders.h"

class RescueTruncation
{
  RESCUEINT64 i;            // The ij node of the truncating fault.
  RESCUEINT64 j;
  RESCUEINT64 self_fault_id;  // Id if the pillar is truncated or zero.
  RESCUEFLOAT self_limit;              // Base/Top limit if the pillar is self-truncated.
public:
  RescueTruncation();
  void SetI(RESCUEINT64 iIn) {i = iIn;}
  void SetJ(RESCUEINT64 jIn) {j = jIn;}
  void SetSelfFaultId(RESCUEINT64 self_fault_idIn) {self_fault_id = self_fault_idIn;}
  void SetSelfLimit(RESCUEFLOAT self_limitIn) {self_limit = self_limitIn;}
  RESCUEINT64 I() {return i;}
  RESCUEINT64 J() {return j;}
  RESCUEINT64 SelfFaultId() {return self_fault_id;}
  RESCUEFLOAT SelfLimit() {return self_limit;}
  RESCUEBOOL isOk(RCHString &message) const;
  RESCUEBOOL isSelfTruncating() const;
protected:
  void Archive(RescueContext *context, FILE *archiveFile);
  RescueTruncation(RescueContext *context, FILE *archiveFile);
  void SwapIJAxis(bool swapI, RESCUEINT64 iLowBound, RESCUEINT64 iCount, 
                  bool swapJ, RESCUEINT64 jLowBound, RESCUEINT64 jCount);

  friend class RescuePillar;
};

#endif

