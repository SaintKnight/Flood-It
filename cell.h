#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "textdisplay.h"
#include "window.h"

const int maxNeighbours = 4;

class Cell {
  int state;        //current state of the cell
  int prevState;    //previous state of the cell
  int numNeighbours;   //number of neighbors
  Cell *neighbours[maxNeighbours];   //pointers to neighbors
  int r, c;                   //co-ordinates of the cell
  int width, height;          //co-ordinates of the cell, width and height of the cell in graph
  Xwindow *xw;                //co-ordinates of the cell, pointer to Xwindow
  TextDisplay * td;        //pointer to the text display

  // Add private members, if necessary (access to Xwindow, location in the window etc)
  //int x, y, width, height;
  //Xwindow * window;

  void notifyDisplay();					    //notify the TextDisplay of the change

public:
  Cell();                                   // Default constructor

  char getState();                          //getter for private state
  void setState(const int& change);         //setter for private state
  void setCoords(const int r, const int c, const int width, const int height, Xwindow *xw);				//setter for private co-ordinates of cell

  //possible setter for partb when we have XWindow
  //void setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w);

  void setDisplay(TextDisplay * t);         //setter for TextDisplay

  void addNeighbour(Cell *neighbour);       //add a neighbouring cell
  
  /*
   * The following methods are provided as a hint towards implementing the notification 
   * You should try to use the methods with the given signatures.
   *
   * If you feel the need to change the *signature* of the method (not the name) you may
   * do so but MUST provide a comprehensive explanation in your code why you felt the change
   * was necessary
   */
	
  // draw the cell in the graph
   void draw();
  /*
   * Intended to be called only by the grid class for changing the state of the 0 0 cell
   */
   void notify( const int & change);	

	/*
	 * Intended to be called by Cells to notify their neighbors
	 * current: this cells current(new) state 
	 * previous: this cells past state
	 */
   void notify(const int & current, const int & previous); 
};
#endif
