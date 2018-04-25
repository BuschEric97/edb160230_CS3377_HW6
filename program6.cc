// CS3377.501 - Program 6
//
// Main file for project
//
// Program by: Eric Busch
// edb160230@utdallas.edu

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cdk.h>
#include <string>
#include "program6.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{
  // open the binary file for later reading
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  char buffer[30];
  string cellText;
  
  if (!binInfile) // check if the binary file opened properly
    {
      cerr << "error: could not open binary file" << endl;
      exit(EXIT_FAILURE);
    }
  
  // initialize CDK variables
  WINDOW *window;
  CDKSCREEN *cdkScreen;
  CDKMATRIX *myMatrix;
  
  // set arrays for the displayed matrix
  const char *rowTitles[MATRIX_HEIGHT + 1] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char *colTitles[MATRIX_WIDTH + 1] = {"C0", "C1", "C2", "C3"};
  int boxWidths[MATRIX_WIDTH + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};
  
  // initialize the CDK screen
  window = initscr();
  cdkScreen = initCDKScreen(window);
  
  // start CDK colors
  initCDKColor();
  
  // create the matrix
  myMatrix = newCDKMatrix(cdkScreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_NAME_STRING, (char **) rowTitles, (char **) colTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);
  
  // check if the matrix was created properly
  if (myMatrix == NULL)
    {
      cerr << "error: could not create matrix." << endl;
      exit(EXIT_FAILURE);
    }
  
  // draw an empty matrix
  //drawCDKMatrix(myMatrix, true);
  
  // read in the header of the binary file
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  
  // build the text for cell (1,1) and insert it into cell (1,1)
  sprintf(buffer, "Magic: 0x%.8X", myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buffer);
  
  // build the text for cell (1,2) and insert it into cell (1,2)
  cellText = "Version: ";
  cellText.append(to_string(myHeader->versionNumber));
  setCDKMatrixCell(myMatrix, 1, 2, cellText.c_str());
  
  // build the text for cell (1,3) and insert it into cell (1,3)
  cellText = "NumRecords: ";
  cellText.append(to_string(myHeader->numRecords));
  setCDKMatrixCell(myMatrix, 1, 3, cellText.c_str());
  
  // read in the each record and put them in the matrix
  for (unsigned int i = 1; i <= myHeader->numRecords; i++)
    {
      // read the next record
      binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
      
      // build the strlen string and add it to the matrix
      cellText = "strlen: ";
      cellText.append(to_string(myRecord->strLength));
      setCDKMatrixCell(myMatrix, i+1, 1, cellText.c_str());

      // build the stringBuffer string and add it to the matrix
      cellText = myRecord->stringBuffer;
      setCDKMatrixCell(myMatrix, i+1, 2, cellText.c_str());
    }
  
  // draw the matrix
  drawCDKMatrix(myMatrix, true);
  
  // wait for input
  char dummy;
  cin >> dummy;
  
  // cleanup the screen
  endCDK();
}
