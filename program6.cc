// CS3377.501 - Program 6
//
// Main file for project
//
// Program by: Eric Busch
// edb160230@utdallas.edu

#include <iostream>
#include <stdlib.h>
#include <cdk.h>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

int main()
{
  // initialize variables
  WINDOW *window;
  CDKSCREEN *cdkScreen;
  CDKMATRIX *myMatrix;
  
  // set arrays for the displayed matrix
  const char *rowTitles[MATRIX_HEIGHT + 1] = {"R0", "R1", "R2", "R3"};
  const char *colTitles[MATRIX_WIDTH + 1] = {"C0", "C1", "C2", "C3"};
  int boxWidths[MATRIX_WIDTH + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};
  
  // initialize the CDK screen
  window = initscr();
  cdkScreen = initCDKScreen(window);
  
  // start CDK colors
  initCDKColor();
  
  // create the matrix
  myMatrix = newCDKMatrix(cdkScreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_NAME_STRING, (char **) colTitles, (char **) rowTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);
  
  // check if the matrix was created properly
  if (myMatrix == NULL)
    {
      cerr << "error: could not create matrix." << endl;
      exit(EXIT_FAILURE);
    }
  
  // draw the matrix
  drawCDKMatrix(myMatrix, true);
  
  // fill in cell (2,2)
  setCDKMatrixCell(myMatrix, 2, 2, "Oriponi");
  drawCDKMatrix(myMatrix, true);
  
  sleep(5);
  
  // cleanup the screen
  endCDK();
}
