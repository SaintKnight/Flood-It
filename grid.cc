#include <iostream>
#include "grid.h"

using namespace std;

extern bool is_graph;


/*********** Grid() ***********
  Purpose: Constructor of Class Grid
           using member initialization list to initialize some
           fields to zero(pointers to NULL).
  Return: this
************************************/
Grid::Grid(Xwindow * theWindow):theGrid(NULL), gridSize(0), td(NULL), theWindow(theWindow) {}


/*********** ~Grid() ***********
  Purpose: Destructor of Class Grid
           free all memory allocated
************************************/
Grid::~Grid(){
	clearGrid();
	delete td;
} // ~Grid


/*********** clearGrid() ***********
  Purpose: A method of Class Grid
           Frees the theGrid field.
  Return: void
************************************/
void Grid::clearGrid(){

	// A loop to free two dimentional array
	for(int i = 0; i < gridSize; i++){
		delete [] theGrid[i];
	} // for
	delete [] theGrid;
	theGrid = NULL;
	gridSize = 0;																	 // set gridSize to 0
} // clearGrid


/*********** isWon() ***********
  Purpose: A method of Class Grid
           check whether the player is won the game
  Return: true if won, otherwise false
************************************/
bool Grid::isWon(){
	// TextDisplay's board filled with the same state implies player won the game
	return td->isFilled();
} // isWon


/*********** init(int) ***********
  Purpose: A method of Class Grid
           Sets up an n x n grid.  Clears old grid, if necessary.
  Return: void
************************************/
void Grid::init(int n){
	// td is either allcated or NULL, free possibly allocated memory first
	delete td;
	// Sets up an n x n TextDisplay
	td = new TextDisplay(n);
	clearGrid();
	gridSize = n;																 // set the new size of Grid n
	theGrid = new Cell *[n];

	// A loop to set up an n x n grid
	for(int i = 0; i < n; i++){
		theGrid[i] = new Cell [n];
	} // for
	// initialize every element of the grid array
	for(int j = 0; j < n; j++){
		for(int k = 0; k < n; k++){
			if(is_graph == true){											 // is graph displaying?
				// set for private co-ordinates of the cell
				theGrid[j][k].setCoords(j,k,500/n,500/n,theWindow);
			} else {
				// set for private co-ordinates of the cell
				theGrid[j][k].setCoords(j,k,0,0,NULL);
			} // if
			theGrid[j][k].setDisplay(td);							 // set for TextDisplay
			if(j < n - 1){														 // have a nether neighbour?
				theGrid[j][k].addNeighbour(&theGrid[j + 1][k]);
			} // if
			if(j > 0){																 // have a upper neighbour?
				theGrid[j][k].addNeighbour(&theGrid[j - 1][k]);
			} // if
			if(k < n - 1){														 // have a right neighbour?
				theGrid[j][k].addNeighbour(&theGrid[j][k + 1]);
			} // if
			if(k > 0){																 // have a left neighbour?
				theGrid[j][k].addNeighbour(&theGrid[j][k - 1]);
			} // if
		} // for
	} // for
} // init


/*********** change(const int) ***********
  Purpose: A method of Class Grid
           Notify Cell (0,0) of the change to new state: state 
  Return: void
************************************/
void Grid::change(const int & state){
	if(theGrid[0][0].getState() - '0' != state){	 // is state changed?
		theGrid[0][0].notify(state);								 // change the state of 0 0 cell
		if(is_graph == true){												 // is graph displaying?
			theGrid[0][0].draw();											 // draw the cell 0 0 
		} // if
	} // if
} // change


/*********** init(int) ***********
  Purpose: A method of Class Grid
           Sets up an n x n grid.  Clears old grid, if necessary.
  Return: void
************************************/
void Grid::init(int r, int c, int state){
	// is the coordinates valid?
	if((r >= 0)&&(r < gridSize)&&(c >= 0)&&(c < gridSize)){
		// is the states changed?
		if(theGrid[r][c].getState() - '0' != state){
			theGrid[r][c].setState(state);						 // change state
			if(is_graph == true){											 // is graph displaying?
				theGrid[r][c].draw();										 // draw the cell
			} // if
			td->notify(r,c,state + '0');							 // update the (r,c) location to be state
		} // if
	} // if
} // init


/*********** output operator ***********
  Purpose: A friend of Class Grid
           overload output operator to out put a grid
  Return: out
************************************/
std::ostream &operator<<(std::ostream &out, const Grid &g){
	out << *(g.td);
	return out;
}


