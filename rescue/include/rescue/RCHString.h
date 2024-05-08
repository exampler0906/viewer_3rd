/**************************************************************************

	RCHString.h

	A simple string class.

	Rod Hanks,	April 1996

**************************************************************************/

#ifndef RCHSTRING_H
#define RCHSTRING_H
#include <malloc.h>
#include <stdio.h>

#include "myHeaders.h"
#include "boolSupport.h"
class RescueContext;

class RCHString
{
  RESCUECHAR *stringValue;
  unsigned RESCUEINT64 allocated;
  RESCUECHAR *delimiters;
  RESCUECHAR *pos;
  RESCUEBOOL each;
  RESCUEBOOL respectQuotes;

public:
  RCHString();
  RCHString(RESCUEINT64 length);
  RCHString(RESCUEINT32 length);
  RCHString(const RESCUECHAR *begin);
  RCHString(RescueContext *context, FILE *archiveFile);
  ~RCHString();
  void Archive(RescueContext *context, FILE *archiveFile);
  RESCUECHAR *String() {return stringValue;}
  RESCUECHAR *NonNullString();
  void Accept(RESCUECHAR *value);
  void AddTo(RCHString &more);
  void AddTo(const RESCUECHAR *more);
  void AddTo(RESCUECHAR more);
  void AddTo(RESCUEINT64 more);
  void AddTo(RESCUEINT32 more);
  void AddTo(RESCUEDOUBLE more);
  void Replace(RCHString &more);
  void Replace(const RESCUECHAR *replace);
  void Replace(RESCUEINT64 replace);
  void Replace(RESCUEINT32 replace);
  void Replace(RESCUEDOUBLE more);
  RCHString &operator+=(const RESCUECHAR *more);
  RCHString &operator=(const RESCUECHAR *replace);
  RCHString &operator+=(RCHString &more);
  RCHString &operator=(RCHString &more);
  RCHString &operator+=(RESCUEINT64 more);
  RCHString &operator=(RESCUEINT64 replace);
  RCHString &operator+=(RESCUEINT32 more);
  RCHString &operator=(RESCUEINT32 replace);
  RCHString &operator+=(RESCUEDOUBLE more);
  RCHString &operator=(RESCUEDOUBLE replace);
  RESCUEBOOL operator==(const RESCUECHAR *other);
  RESCUEBOOL operator!=(const RESCUECHAR *other);
  RESCUEBOOL operator==(RCHString &other);
  RESCUEBOOL operator!=(RCHString &other);
  RESCUEBOOL StartsWith(RCHString &other);
  RESCUEBOOL StartsWith(const RESCUECHAR *other);
  RESCUEBOOL EndsWith(RCHString &other);
  RESCUEBOOL EndsWith(const RESCUECHAR *other);
  RCHString &operator<<(RCHString &more);
  RCHString &operator<<(const RESCUECHAR *more);
  RCHString &operator<<(RESCUEINT64 more);
  RCHString &operator<<(RESCUEINT32 more);
  RCHString &operator<<(RESCUECHAR more);
  RCHString &operator<<(RESCUEDOUBLE more);
  void tokenize(const RESCUECHAR *delimiters=0, RESCUEBOOL eachIn=FALSE, 
                                    RESCUEBOOL respectQuotes=FALSE);
  RESCUEBOOL operator>>(RESCUECHAR *buffer);
  RESCUEBOOL operator>>(RCHString &buffer);
  RESCUEINT64 length64();
  RESCUEINT32 length() {return (RESCUEINT32) length64();}
  RESCUEINT32 length(RESCUEBOOL throwIfTooBig);
  void doubleApostrophe();
  void cgiEncode();
  void cgiDecode();
};

#endif


