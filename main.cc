#include <iostream>
#include <string>
#include <fstream>
#include "cell.h"
#include "textdisplay.h"
#include "grid.h"
#include "window.h"

using namespace std;

// A global variable to check whether the graph is displaying
bool is_graph = false;

int main(int argc, char *argv[]){
	// check the argument number
	if(argc == 2) {																 // is the program flood has one argument?
		string t = argv[1];
		if(t == "-graphics"){												 // is the argument is "-graphics"
			is_graph = true;
		}
	}
	Xwindow xw;																		 // set a Xwindow
	string command;																 // record command
	Grid board(&xw);															 // set up a grid, initialize with Xwindow xw
	string file;																	 // record file name
	bool is_game_start = false;										 // trace game start state
	int state;																		 // record cell state
	int count = 0;																 // number of moves left
	int n = 0;																		 // record size of grid
	int r = 0;																		 // record row coordinate
	int c = 0;																		 // record column coordinate

	// A loop to read in command
	while(cin >> command){
		if(command == "?"){													 // is command "?"
			// display the encoding between the text version and graphics version.
			cout << "White: 0" << endl;
			cout << "Black: 1" << endl;
			cout << "Red:   2" << endl;
			cout << "Green: 3" << endl; 
			cout << "Blue:  4" << endl;
		} else if(command == "new"){								 // is command "new"?
			cin >> n;
			board.init(n);														 // build a grid of size n x n
		} else if(command == "init"){								 // is command "init"(read from stdin)?

			// A loop used to skip invalid r, c and state
			while(cin >> r){
				cin >> c;
				if((r == -1) && (c == -1)){							 // initialization is done?
					break;
				} // if
				cin >> state;
				if((state > 4)||(state < 0)){						 // invalid state
					continue;
				} // if
				board.init(r, c, state); 								 // initialize state of cell at coordinates	r,c 
			} // while
			cout << board;														 // output grid
		} else if(command == "include"){						 // is command "include"(read from a file) ?
			cin >> file;
			ifstream f(file.c_str());

			// A loop to read from a file until eof
			while (f >> r){
				f >> c;
				if((r == -1) && (c == -1)){							 // is initialization done?
					break;
				} else {
					f >> state;
					if((state > 4)||(state < 0)){					 // is state invalid?
						continue;
					} // if
					board.init(r, c, state);							 // initialize state of cell at coordinates r,c	
				} // if
			} // while
			cout << board;														 // output grid
		} else if(command == "game"){								 // is command "game" ?
			cin >> count;															 // record total number of moves
			if(is_game_start == true) {								 // is game already start?
				continue;
			} // if
			is_game_start = true;
			if(count == 1) {													 // output number of moves left
				cout << "1 move left" << endl;
			} else {
				cout << count << " moves left" << endl;
			} // if
		} else if(command == "switch"){							 // is command "switch"?
			cin >> state;
			if(cin.eof()){break;}
			if((state > 4)||(state < 0)){							 // is state valid?
				continue;
			} // if
			if(is_game_start == false) {							 // is game already start?
				continue;
			} // if
			board.change(state);											 // update the 0 0 cell
			count--;																	 // update moves left
			cout << board;														 // output grid
			if(count == 1) {													 // output number of moves left
				cout << "1 move left" << endl;
			} else {
				cout << count << " moves left" << endl;
			} // if
		} // if
		if(is_game_start == true) {									 // is game already start?
			if(board.isWon()) {												 // is the player won?
				cout << "Won" << endl;
				break;
			} else if(count == 0) {
				cout << "Lost" << endl;
				break;
			}
		}
	}
}
