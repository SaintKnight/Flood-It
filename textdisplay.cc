#include <iostream>
#include <string>
#include "textdisplay.h"

using namespace std;

/*********** TextDisplay() ***********
  Purpose: Constructor of Class TextDisplay
           one arg constructor where the parameter is the gridSize.
  Return: this
************************************/
TextDisplay::TextDisplay(int n):gridSize(n){
	theDisplay = new char *[n];

	// A loop to construct n x n TextDisplay
	for(int i = 0; i < n; i++){
		theDisplay[i] = new char [n];
	} // for

	// A loop to initialize all displayed cell states to '0'
	for(int j = 0; j < n; j++){
		for(int k = 0; k < n; k++){
			theDisplay[j][k] = '0';
		} // for
	} // for
	colourCount[0] = n * n;

	// record initial number of cells of different colours respectively
	for(int t = 1; t <= 4; t++){
		colourCount[t] = 0;
	} // for
} // TextDisplay


/*********** TextDisplay() ***********
  Purpose: A method of Class TextDisplay
           update the (r,c) location to be ch
  Return: this
************************************/
void TextDisplay::notify(int r, int c, char ch){
	int color = theDisplay[r][c] - '0';
	colourCount[color]--;
	colourCount[ch-'0']++;
	theDisplay[r][c] = ch;
} // notify


/*********** isFilled() ***********
  Purpose: A method of Class TextDisplay
           To check the win condition, the Grid calls the isFilled
           method which returns true if all cells are the same color
  Return: this
************************************/
bool TextDisplay::isFilled(){

	// A loop to go through every color and check its number
	for(int i = 0; i < 5; i++){
		if(colourCount[i] == gridSize * gridSize){
			return true;
		} // if
	} // for
	return false;
}


/*********** ~TextDisplay() ***********
  Purpose: Destructor of Class TextDisplay
           free all memory allocated
************************************/
TextDisplay::~TextDisplay(){
	// A loop to free every cell of two dimension TextDisplay
	for(int i = 0; i < gridSize; i++){
		delete [] theDisplay[i];
	} // for
	delete [] theDisplay;
	theDisplay = NULL;
} // ~TextDisplay


/*********** output operator ***********
  Purpose: A friend of Class TextDisplay
           overload output operator to out put a TextDisplay
  Return: out
************************************/
std::ostream &operator<<(std::ostream &out, const TextDisplay &td){

	// loops to go through every cell of TextDisplay
	for(int j = 0; j < td.gridSize; j++){
		for(int k = 0; k < td.gridSize; k++){
			out << td.theDisplay[j][k];
		} // for
		out << endl;
	} // for
	return out;
}
