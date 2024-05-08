/********************************************************************

  RescueBuffer.h

  A buffer area where we read and write named file sections.

  Rod Hanks,  June, 2005

*********************************************************************/
#ifndef RescueBuffer_H
#define RescueBuffer_H

#include "myHeaders.h"
class RescueContext;

class RescueBuffer
{
private:
  RESCUEINT64 allocated;
  RESCUEINT64 count;
  RESCUEINT64 lineCount;
  RESCUEUCHAR *buffer;
  RESCUEUCHAR *cursor;
  RescueContext *context;
  
  void EnsureCapacity(RESCUEINT64 needed);
public:
  RescueBuffer(RescueContext *context, FILE *archiveFile);
  RescueBuffer(RescueContext *context, RESCUEINT64 allocationHint);
  ~RescueBuffer();

  void Archive(FILE *archiveFile);

  RescueBuffer &operator<<(RCHString &more);
  RescueBuffer &operator<<(const RESCUECHAR *more);
  RescueBuffer &operator<<(RESCUEUINT64 more);
  RescueBuffer &operator<<(RESCUEINT64 more);
#ifndef RESCUEINT_INT32_SAME
  RescueBuffer &operator<<(RESCUEINT32 more);
  RescueBuffer &operator<<(unsigned RESCUEINT32 more);
#endif
  RescueBuffer &operator<<(RESCUEUCHAR more);
  RescueBuffer &operator<<(RESCUEUSHORT more);
  RescueBuffer &operator<<(RESCUESHORT more);
  RescueBuffer &operator<<(RESCUEFLOAT more);
  RescueBuffer &operator<<(RESCUEDOUBLE more);

  void operator>>(RCHString &more);
  void operator>>(RESCUEUINT64 &more);
  void operator>>(RESCUEINT64 &more);
#ifndef RESCUEINT_INT32_SAME
  void operator>>(RESCUEINT32 &more);
  void operator>>(unsigned RESCUEINT32 &more);
#endif
  void operator>>(RESCUEUCHAR &more);
  void operator>>(RESCUEUSHORT &more);
  void operator>>(RESCUESHORT &more);
  void operator>>(RESCUEFLOAT &more);
  void operator>>(RESCUEDOUBLE &more);
};

#endif


