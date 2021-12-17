#ifndef BOARD_H
#define BOARD_H
#include <string>
using namespace std;

class Board
{
public:
    Board();
	Board(string output_file_name);
    ~Board();

    string* take_deck(string deck_file_name);
    void print_deck(string* deck);
    void starting();
    void board_maker();
	void open_from_stock();
	void move_to_foundation(string command);
	void move_to_foundation();
	void move(string first, string second, string third);
	void move(string first);
	void open(string pile);
	void exit();
	
	string* split(string str);	
	bool invalid_move(string str1, string str2);
	bool invalid_move_piles(string str1, string str2);
	char find_type(string str);
	int length(string* arr);
	bool win();

	

private:
    string deck[52];
    string stock[25];
    string waste[25];
    string foundation_one[14];
    string foundation_two[14];
    string foundation_three[14];
    string foundation_four[14];
    string piles[20][7];
	string temp_arr[5];
	int opening[7];
	string output_file_name;

#endif // BOARD_HPP
};