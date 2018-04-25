// CS3377.501 - Program 6
//
// Project's Header File
//
// Program by: Eric Busch
// edb160230@utdallas.edu

#ifndef _PROGRAM6_H_
#define _PROGRAM6_H_

#include <stdint.h>

const int maxRecordStringLength = 25;

class BinaryFileHeader
{
 public:
  uint32_t magicNumber; // should be 0xFEEDFACE
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

#endif /*_PROGRAM6_H_*/
