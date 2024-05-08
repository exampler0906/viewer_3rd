/*****************************************************************************
 
        myHeaders.h
 
   Unlike some previous versions, beginning with v37.4 you should
   only have to change this if your compiler uses a different name
   for these data types.

        Rod Hanks       February 2007
 
*****************************************************************************/
#ifndef RESCUE_H
#define RESCUE_H

#ifdef _WIN32
#pragma warning(disable : 4996)
#endif

#ifdef _WIN32
#define RESCUEUINT64 unsigned __int64
#else
#define RESCUEUINT64 unsigned long long
#endif
/*
  Always a 64 bit unsigned integer.
*/
#ifdef _WIN32
#define RESCUEINT64 __int64
#else
#define RESCUEINT64 long long
#endif
/*
  Always a 64 bit signed integer. Must be equivalent to jlong.
*/
#define RESCUEINT32 int
/*
  Always a 32 bit signed integer.  Must be equivalent to jint.
*/
#define RESCUEUINT32 unsigned int
/*
  Always a 32 bit unsigned integer.
*/
#define RESCUEFLOAT float
/*
  Always a 32 bit IEEE floating point.
*/
#define RESCUEDOUBLE double
/*
  Always a 64 bit iEEE floating point.  Must be equivalent to jdouble.
*/
#define RESCUESHORT short
/*
  Always a 16-bit signed integer.
*/
#define RESCUECHAR char
/*
  Always an 8-bit signed integer.
*/
#define RESCUEUCHAR unsigned char
/*
  Always an 8-bit unsigned integer.
*/
#define RESCUEUSHORT unsigned short
/*
  Always a 16-bit unsigned integer.
*/
#include "boolSupport.h"

#include "RescueObject.h"

void myfprintf(RescueContext *context, FILE *archiveFile, const RESCUECHAR *value);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEINT64 value);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEINT32 value);
void myfprintf(RescueContext *context, FILE *archiveFile, unsigned RESCUEINT32 value);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEDOUBLE value);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEDOUBLE *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEFLOAT value);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEFLOAT *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEINT32 *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEINT64 *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfprintf(RescueContext *context, FILE *archiveFile, unsigned RESCUEINT32 *value, RESCUEINT64 count);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEINT32 *value, RESCUEINT64 count);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEINT64 *value, RESCUEINT64 count);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEBOOL value);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEUCHAR);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEUCHAR *, RESCUEINT64 count);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEUSHORT);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEUSHORT *, RESCUEINT64 count);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEUINT64);
void myfprintf(RescueContext *context, FILE *archiveFile, RESCUEUINT64 *, RESCUEINT64 count);
RESCUECHAR *myfgets(RescueContext *context, RESCUECHAR *buffer, RESCUEINT64 maxBytes, FILE *archiveFile);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEINT64 *value);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEINT32 *value);
void myfscanf(RescueContext *context, FILE *archiveFile, unsigned RESCUEINT32 *value);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEDOUBLE *value);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEDOUBLE *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEFLOAT *value);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEFLOAT *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEINT32 *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEINT64 *value, RESCUEINT64 count, RESCUEBOOL compress);
void myfscanf(RescueContext *context, FILE *archiveFile, unsigned RESCUEINT32 *value, RESCUEINT64 count);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEINT32 *value, RESCUEINT64 count);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEINT64 *value, RESCUEINT64 count);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEBOOL *value);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEUCHAR *);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEUCHAR *, RESCUEINT64 count);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEUSHORT *);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEUSHORT *, RESCUEINT64 count);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEUINT64 *);
void myfscanf(RescueContext *context, FILE *archiveFile, RESCUEUINT64 *, RESCUEINT64 count);

#endif



