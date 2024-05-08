/**************************************************************************

	RCHXMLTokenizer.h

	Simple XML tokenizer.

	Rod Hanks,	July, 2007

**************************************************************************/

#ifndef RCHXMLTokenizer_H
#define RCHXMLTokenizer_H
#include <malloc.h>
#include <stdio.h>

#include "myHeaders.h"
#include "boolSupport.h"
#include "RCHString.h"

class RCHXMLTokenizer
{
  RCHString nextToken;
  FILE *inputFile;
  RESCUEBOOL needSpecialTerminator;
  RESCUEBOOL returnSpecialTerminator;
  RESCUEBOOL hitEOF;
  RESCUEBOOL inTag;
  
  RESCUECHAR buffer[512];
  int readPos;
  int writePos;

  void FillBuffer();
  RESCUECHAR NextByte();
  void PushByte(int toPush);
public:
  RCHXMLTokenizer(FILE *inputFileIn);
  RESCUECHAR *NextToken();
  RESCUECHAR *UnquotedToken();
  RESCUEBOOL InTag() {return inTag;}
  void ConsumeTag();
  RESCUEBOOL TokenIsTag(const RESCUECHAR *tag);
};

#endif


