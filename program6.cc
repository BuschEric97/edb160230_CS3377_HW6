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
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{
  // open the binary file for later reading
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);
  BinaryFileHeader myHeader;
  string magicNumber = "Magic: ";
  string versionNumber = "Version: ";
  string numRecords = "NumRecords: ";
  BinaryFileRecord myRecord[4];
  
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
  
  // read in the header of the binary file
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  magicNumber.append((string) myHeader.magicNumber);
  versionNumber.append((string) myHeader.versionNumber);
  numRecords.append((string) myHeader.numRecords);
  
  // fill in cells (1,1), (1,2), and (1,3) with the info from file header
  setCDKMatrixCell(myMatrix, 1, 1, magicNumber.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, versionNumber.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());
  
  // draw the matrix
  drawCDKMatrix(myMatrix, true);
  
  // wait for input
  char dummy;
  cin >> dummy;
  
  // cleanup the screen
  endCDK();
}
