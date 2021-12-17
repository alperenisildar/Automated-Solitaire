#include <stdio.h>
#include <iostream>
#include <string>
#include "Board.h"
#include <fstream>
using namespace std;



int main(int argc, char **argv){
	
	Board board(argv[3]);
	
	string deck_file_name = argv[1];
	string output_file_name = argv[3];
	
	board.take_deck(deck_file_name);
	board.starting();
	board.board_maker();
	
	
	string text;
	string commands_file = argv[2];
	ifstream my_commands_file(commands_file);
	ofstream fout;
	fout.open(output_file_name, ios::app);
	int loop = 0;
	while(getline(my_commands_file, text)){
		fout << text << endl;
		fout << "****************************************" << endl;
		if(board.split(text)[0] == "move"){
			if(board.split(text)[1] == "to")
				if(board.split(text)[3] == "waste")
					board.move_to_foundation();
				else
					board.move_to_foundation(board.split(text)[4]);
			else if(board.split(text)[1] == "pile")
				board.move(board.split(text)[2], board.split(text)[3], board.split(text)[4]);
			else if(board.split(text)[1] == "waste")
				board.move(board.split(text)[2]);
		}
		else if(board.split(text)[0] == "open"){
			if(board.split(text)[1] == "from")
				board.open_from_stock();
			else
				board.open(board.split(text)[1]);
		}
		else if(board.split(text)[0] == "exit"){
			fout << "Game Over" << endl;
			break;
		}
	}
	fout << "****************************************" << endl;
	fout << "Game Over!\n" << endl;
	if(board.win())
		fout << "You Win!" << endl;
	fout.close();
	
	
	
	return 0;
}
