#include <iostream>
#include "cell.h"

using namespace std;

extern bool is_graph;

/*********** Cell() ***********
  Purpose: Constructor of Class Cell
           using member initialization list to initialize some
           fields to zero.
  Return: this
************************************/
Cell::Cell():state(0), prevState(0), numNeighbours(0) {}


/*********** notifyDisplay() ***********
  Purpose: A method of Class Cell
  				 notify the TextDisplay of the change
  Return: void
************************************/
void Cell::notifyDisplay(){
	td->notify(r, c, state + '0');
} // notifyDisplay


/*********** getState() ***********
  Purpose: A method of Class Cell
  				 getter for private state.
  Return: char, current state
************************************/
char Cell::getState() {
	return state + '0';
} // getState


/*********** setState(const int &) ***********
  Purpose: A method of Class Cell
  				 setter for private state.
  Return: void
************************************/
void Cell::setState(const int& change){
	state = change;
	if(is_graph == true){													 // graph display?
		draw();
	} // if
} // setState


/*********** setCoords() ***********
  Purpose: A method of Class Cell
  				 setter for private co-ordinates of cell.
  Return: void
************************************/
void Cell::setCoords(const int r, const int c, const int width, const int height, Xwindow *xw) {
	this->r = r;
	this->c = c;
	this->width = width;
	this->height = height;
	this->xw = xw;
} // setCoords


/*********** draw() ***********
  Purpose: A method of Class Cell
  				 draw the cell on graph
  Return: void
************************************/
void Cell::draw(){
	xw->fillRectangle(c * width, r * height, width, height, state);
} // draw


/*********** setDisplay(TextDisplay *) ***********
  Purpose: A method of Class Cell
  				 setter for TextDisplay
  Return: void
************************************/
void Cell::setDisplay(TextDisplay * t){
	td = t;
} // setDisplay


/*********** addNeighbour(Cell *) ***********
  Purpose: A method of Class Cell
  				 add a neighbouring cell
  Return: void
************************************/
void Cell::addNeighbour(Cell *neighbour){
	neighbours[numNeighbours] = neighbour;
	numNeighbours++;
} // addNeighbour


/*********** notify(const int &) ***********
  Purpose: A method of Class Cell
  				 Intended to be called only by the grid class 
  				 for changing the state of the 0 0 cell
  Return: void
************************************/
void Cell::notify( const int & change){
	prevState = state;														 // record previous state
	setState(change);															 // change current state
	notify(state, prevState);											 // notify its neighbors
	notifyDisplay();															 // notify the TextDisplay of the change 
} // notify


/*********** notify(const int&, const int&) ***********
  Purpose: A method of Class Cell
  				 Intended to be called by Cells to notify their neighbors
  				 current: this cells current(new) state 
  				 previous: this cells past state
  Return: void
************************************/
void Cell::notify(const int & current, const int & previous){

	// A loop to check through all neighbours of a Cell
	// and changes the state if they previously under the same state of 0 0
	for(int i = 0; i < numNeighbours; i++){

		// is it previously under the same state of 0 0?
		if(neighbours[i]->getState() == previous + '0'){
			neighbours[i]->notify(current);
		} // if
	} // for
} // notify