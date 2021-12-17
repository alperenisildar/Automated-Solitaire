#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
Board::Board()
{
}

Board::Board(string output_file_name){
	this -> output_file_name = output_file_name;
}

Board::~Board()
{
}
	string* Board::take_deck(string deck_file_name){
		
		string my_text;
		ifstream my_file(deck_file_name);
		int loop = 0;
		while(getline(my_file, my_text)){
			deck[loop] = my_text;
			loop++;
	}
		return deck;
}		

	void Board::starting(){
		
		stock[24] = "null";
		waste[24] = "null";
		for(int i = 0; i < 14; i++){
			foundation_one[i] = "null";
			foundation_two[i] = "null";
			foundation_three[i] = "null";
			foundation_four[i] = "null";
		}
		for(int i = 0; i < 24; i++){
			waste[i] = "null";
		}
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 7; j++){
				piles[i][j] = "null";
			}
		}
		int counter = 51;
		for(int i = 0; i < 14; i++){
			for(int j = i; j < 7; j++){
				piles[i][j] = deck[counter];
				counter--;
			}
		}
		for(int i = 23; i > -1; i--){
			stock[i] = deck[i];
		}		
		for(int i = 0; i < 7; i++){
			opening[i] = i;
		}
	
	}

	void Board::board_maker(){
		
		ofstream fout;
		fout.open(output_file_name, ios::app);
	
		if(stock[0] == "null"){
			fout << "___ ";
		}
		else{
			fout << "@@@ ";
		}
		
		int curser = 0;
		while(waste[curser] != "null"){
			curser++;
		}
		
		if(curser == 0)
			fout << "___ ___ ___         ";
		else{
			if(curser % 3 == 0){
				if(waste[curser-3] == "empty")
					fout << "___ " << "___ " << "___         ";
				else if(waste[curser-2] == "empty")
					fout << waste[curser-3] << " " << "___ " << "___         ";
				else if(waste[curser-1] == "empty")
					fout << waste[curser-3] << " " << waste[curser-2] << " " << "___         ";
				else 
					fout << waste[curser-3] << " " << waste[curser-2] << " " << waste[curser-1] << "         ";
			}
			else if(curser % 3 == 1){
				if(waste[curser-1] == "empty")
					fout << "___ " << "___ " << "___         ";
				else 
					fout << waste[curser-1] << " " << "___ " << "___         ";
			}
			else if(curser % 3 == 2){
				if(waste[curser-2] == "empty")
					fout << "___ " << "___ " << "___         ";
				else if(waste[curser-1] == "empty")
					fout << waste[curser-2] << " " << "___ " << "___         ";
				else
					fout << waste[curser-2] << " " << waste[curser-1] << " " << "___         ";
			}
		}
		
		if(foundation_one[0] == "null")
			fout << "___ ";
		else
			fout << foundation_one[length(foundation_one)-1] << " ";
		
		if(foundation_two[0] == "null")
			fout << "___ ";
		else
			fout << foundation_two[length(foundation_two)-1] << " ";
		
		if(foundation_three[0] == "null")
			fout << "___ ";
		else
			fout << foundation_three[length(foundation_three)-1] << " ";
		
		if(foundation_four[0] == "null")
			fout << "___ ";
		else
			fout << foundation_four[length(foundation_four)-1] << endl;
		fout << endl << endl;
		int i = 0;
		int j = 0;
		
		for(i = 0; i<20; i++){
			j = 0;
			while(j < 7){
				int start = opening[j];
				if(i >= start){
					if(piles[i][j] == "null"){
						fout << "      ";
					}
					else{
						fout << piles[i][j] << "   ";
					}
				}
				else{
					fout << "@@@   ";
				}
				j++;
			}
			fout << endl;
		}
		fout.close();
		
	}
	
	void Board::open_from_stock(){
		ofstream fout;
		fout.open(output_file_name, ios::app);
		if(length(stock) == 0){
			int j = 0;
			for(int i = 23; i > -1; i--){
				if(waste[i] != "empty" && waste[i] != "null"){
					stock[j] = waste[i];
					j++;
				}
			}
			for(int i = 0; i < 25; i++)
				waste[i] = "null";
		}		
		else if(length(stock) == 1){
			int c = 1;
			int curser = 0;
			while(c != 0){
				int i = (length(stock))-1;
				while(true){
					if(waste[curser] == "null"){
					break;
					}
				curser++;
				}
				waste[curser] = stock[i];
				stock[i] = "null";
				c--;
				i--;
			}
		}
		else if(length(stock) == 2){
			int c = 2;
			int curser = 0;
			while(c != 0){
				int i = (length(stock))-1;
				while(true){
					if(waste[curser] == "null"){
					break;
					}
				curser++;
				}
				waste[curser] = stock[i];
				stock[i] = "null";
				c--;
				i--;
			}	
		}
		else{
			int c = 3;
			int curser = 0;
			while(c != 0){
				int i = (length(stock))-1;
				while(true){
					if(waste[curser] == "null"){
					break;
					}
				curser++;
				}
				waste[curser] = stock[i];
				stock[i] = "null";
				c--;
				i--;
				fout << waste[curser] << endl;
			}
		}
		fout.close();
		board_maker();
	}
	
	void Board::move_to_foundation(string command){
		ofstream fout;
		fout.open(output_file_name, ios::app);
		if(command == "0"){
			for(int i = 0; i < 20; i++){
				if(piles[i][0] == "null"){
					if(find_type(piles[i-1][0]) == 'H'){
						if(invalid_move(foundation_one[length(foundation_one)],piles[i-1][0])){
							fout << "Invalid Move" << endl;
							return;
						}
							else{
								foundation_one[length(foundation_one)] = piles[i-1][0];
								piles[i-1][0] = "null";
							}
								
					}
					else if(find_type(piles[i-1][0]) == 'D'){
						if(invalid_move(foundation_two[length(foundation_two)],piles[i-1][0])){
							fout << "Invalid Move" << endl;
							return;
						}
							else{
								foundation_two[length(foundation_two)] = piles[i-1][0];
								piles[i-1][0] = "null";
							}
								
					}
					else if(find_type(piles[i-1][0]) == 'S'){
						if(invalid_move(foundation_three[length(foundation_three)],piles[i-1][0])){
							fout << "Invalid Move" << endl;
							return;
						}
							else{
								foundation_three[length(foundation_three)] = piles[i-1][0];
								piles[i-1][0] = "null";
							}
								
					}
					else if(find_type(piles[i-1][0]) == 'C'){
						if(invalid_move(foundation_four[length(foundation_four)],piles[i-1][0])){
							fout << "Invalid Move" << endl;
							return;
						}
							else{
								foundation_four[length(foundation_four)] = piles[i-1][0];
								piles[i-1][0] = "null";
							}	
					}
				}
			}
		}
		else if(command == "1"){
			for(int i = 0; i < 20; i++){
				if(piles[i][1] == "null"){
					if(find_type(piles[i-1][1]) == 'H'){
						if(invalid_move(foundation_one[length(foundation_one)], piles[i-1][1])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_one[length(foundation_one)] = piles[i-1][1];
							piles[i-1][1] = "null";
						}
					}
					else if(find_type(piles[i-1][1]) == 'D'){
						if(invalid_move(foundation_two[length(foundation_two)], piles[i-1][1])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_two[length(foundation_two)] = piles[i-1][1];
							piles[i-1][1] = "null";
						}
					}
					else if(find_type(piles[i-1][1]) == 'S'){
						if(invalid_move(foundation_three[length(foundation_three)], piles[i-1][1])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_three[length(foundation_three)] = piles[i-1][1];
							piles[i-1][1] = "null";
						}
					}		
					
					else if(find_type(piles[i-1][1]) == 'C'){
						if(invalid_move(foundation_four[length(foundation_four)], piles[i-1][1])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_four[length(foundation_four)] = piles[i-1][1];
							piles[i-1][1] = "null";
						}
					}
				}
			}
		}
		else if(command == "2"){
			for(int i = 0; i < 20; i++){
				if(piles[i][2] == "null"){
					if(find_type(piles[i-1][2]) == 'H'){
						if(invalid_move(foundation_one[length(foundation_one)], piles[i-1][2])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_one[length(foundation_one)] = piles[i-1][2];
							piles[i-1][2] = "null";
						}
					}
					else if(find_type(piles[i-1][2]) == 'D'){
						if(invalid_move(foundation_two[length(foundation_two)], piles[i-1][2])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_two[length(foundation_two)] = piles[i-1][2];
							piles[i-1][2] = "null";
						}
					}
					else if(find_type(piles[i-1][2]) == 'S'){
						if(invalid_move(foundation_three[length(foundation_three)], piles[i-1][2])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_three[length(foundation_three)] = piles[i-1][2];
							piles[i-1][2] = "null";
						}
					}
					else if(find_type(piles[i-1][2]) == 'C'){
						if(invalid_move(foundation_four[length(foundation_four)], piles[i-1][2])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_four[length(foundation_four)] = piles[i-1][2];
							piles[i-1][2] = "null";
						}
					}
				}
			}
		}
		else if(command == "3"){
			for(int i = 0; i < 20; i++){
				if(piles[i][3] == "null"){
					if(find_type(piles[i-1][3]) == 'H'){
						if(invalid_move(foundation_one[length(foundation_one)], piles[i-1][3])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_one[length(foundation_one)] = piles[i-1][3];
							piles[i-1][3] = "null";
						}
					}
					else if(find_type(piles[i-1][3]) == 'D'){
						if(invalid_move(foundation_two[length(foundation_two)], piles[i-1][3])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_two[length(foundation_two)] = piles[i-1][3];
							piles[i-1][3] = "null";
						}
					}
					else if(find_type(piles[i-1][3]) == 'S'){
						if(invalid_move(foundation_three[length(foundation_three)], piles[i-1][3])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_three[length(foundation_three)] = piles[i-1][3];
							piles[i-1][3] = "null";
						}
					}
					else if(find_type(piles[i-1][3]) == 'C'){
						if(invalid_move(foundation_four[length(foundation_four)], piles[i-1][3])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_four[length(foundation_four)] = piles[i-1][3];
							piles[i-1][3] = "null";
						}
					}
				}
			}
		}
		else if(command == "4"){
			for(int i = 0; i < 20; i++){
				if(piles[i][4] == "null"){
					if(find_type(piles[i-1][4]) == 'H'){
						if(invalid_move(foundation_one[length(foundation_one)], piles[i-1][4])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_one[length(foundation_one)] = piles[i-1][4];
							piles[i-1][4] = "null";
						}
					}
					else if(find_type(piles[i-1][4]) == 'D'){
						if(invalid_move(foundation_two[length(foundation_two)], piles[i-1][4])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_two[length(foundation_two)] = piles[i-1][4];
							piles[i-1][4] = "null";
						}
					}
					else if(find_type(piles[i-1][4]) == 'S'){
						if(invalid_move(foundation_three[length(foundation_three)], piles[i-1][4])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_three[length(foundation_three)] = piles[i-1][4];
							piles[i-1][4] = "null";
						}
					}
					else if(find_type(piles[i-1][4]) == 'C'){
						if(invalid_move(foundation_four[length(foundation_four)], piles[i-1][4])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_four[length(foundation_four)] = piles[i-1][4];
							piles[i-1][4] = "null";
						}
					}
				}
			}
		}
		else if(command == "5"){
			for(int i = 0; i < 20; i++){
				if(piles[i][5] == "null"){
					if(find_type(piles[i-1][5]) == 'H'){
						if(invalid_move(foundation_one[length(foundation_one)], piles[i-1][5])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_one[length(foundation_one)] = piles[i-1][5];
							piles[i-1][5] = "null";
						}
					}
					else if(find_type(piles[i-1][5]) == 'D'){
						if(invalid_move(foundation_two[length(foundation_two)], piles[i-1][5])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_two[length(foundation_two)] = piles[i-1][5];
							piles[i-1][5] = "null";
						}
					}
					else if(find_type(piles[i-1][5]) == 'S'){
						if(invalid_move(foundation_three[length(foundation_three)], piles[i-1][5])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_three[length(foundation_three)] = piles[i-1][5];
							piles[i-1][5] = "null";
						}
					}
					else if(find_type(piles[i-1][5]) == 'C'){
						if(invalid_move(foundation_four[length(foundation_four)], piles[i-1][5])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_four[length(foundation_four)] = piles[i-1][5];
							piles[i-1][5] = "null";
						}
					}
				}
			}
		}
		else if(command == "6"){
			for(int i = 0; i < 20; i++){
				if(piles[i][6] == "null"){
					if(find_type(piles[i-1][6]) == 'H'){
						if(invalid_move(foundation_one[length(foundation_one)], piles[i-1][6])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_one[length(foundation_one)] = piles[i-1][6];
							piles[i-1][6] = "null";
						}
					}
					else if(find_type(piles[i-1][6]) == 'D'){
						
						if(invalid_move(foundation_two[length(foundation_two)], piles[i-1][6])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_two[length(foundation_two)] = piles[i-1][6];
							piles[i-1][6] = "null";
						}
					}
					else if(find_type(piles[i-1][6]) == 'S'){
						if(invalid_move(foundation_three[length(foundation_three)], piles[i-1][6])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_three[length(foundation_three)] = piles[i-1][6];
							piles[i-1][6] = "null";
						}
					}
					else if(find_type(piles[i-1][6]) == 'C'){
						if(invalid_move(foundation_four[length(foundation_four)], piles[i-1][6])){
							fout << "Invalid Move" << endl;
						}
						else{
							foundation_four[length(foundation_four)] = piles[i-1][6];
							piles[i-1][6] = "null";
						}
					}
				}
			}
		}
		fout.close();
		board_maker();
	}
	
	void Board::move_to_foundation(){
		ofstream fout;
		fout.open(output_file_name, ios::app);
		int curser = 0;
		while(waste[curser] != "null"){
			curser++;
		}
		while(waste[curser-1] == "empty")
			curser--;
			
			if(find_type(waste[curser - 1]) == 'H'){
				if(invalid_move(foundation_one[length(foundation_one)], waste[curser-1])){
					fout << "Invalid Move" << endl;
				}
				else{
					foundation_one[length(foundation_one)] = waste[curser-1];
					waste[curser-1] = "empty";
				}
			}
			else if(find_type(waste[curser - 1]) == 'D'){
				if(invalid_move(foundation_two[length(foundation_two)], waste[curser-1])){
					fout << "Invalid Move" << endl;
				}
				else{
					foundation_two[length(foundation_two)] = waste[curser-1];
					waste[curser-1] = "empty";
				}
			}
			else if(find_type(waste[curser - 1]) == 'S'){
				if(invalid_move(foundation_three[length(foundation_three)], waste[curser-1])){
					fout << "Invalid Move" << endl;
				}
				else{
					foundation_three[length(foundation_three)] = waste[curser-1];
					waste[curser-1] = "empty";
				}
			}
			else if(find_type(waste[curser - 1]) == 'C'){
				if(invalid_move(foundation_four[length(foundation_four)], waste[curser-1])){
					fout << "Invalid Move" << endl;
				}
				else{
					foundation_four[length(foundation_four)] = waste[curser-1];
					waste[curser-1] = "empty";
				}
			}
			fout.close();
		board_maker();
	}
	
	void Board::move(string first, string second, string third){
		ofstream fout;
		fout.open(output_file_name, ios::app);
		int int_first = stoi(first);
		int int_second = stoi(second);
		int int_third = stoi(third);
		int j = 0;
		int i = int_second + 1;
		while(true){
			if(piles[j][int_third] == "null")
				break;
			j++;
		}
		
		int curser = 0;
		while(piles[curser][int_first] != "null"){
			curser++;
		}
		if(invalid_move_piles(piles[curser-i][int_first], piles[j-1][int_third])){
			fout << "Invalid Move" << endl;
			return;
		}
		while(i>0){
			piles[j][int_third] = piles[curser-i][int_first];
			piles[curser-i][int_first] = "null";
			i--;
			j++;
		}
		fout.close();
		board_maker();
	}
	
	void Board:: move(string first){
		ofstream fout;
		fout.open(output_file_name, ios::app);
		int curser = 0;
		int j = 0;
		int int_first = stoi(first);
		
		while(waste[curser] != "null"){
			curser++;
		}
		
		while(waste[curser-1] == "empty")
			curser--;
		
		while(true){
			if(piles[j][int_first] == "null")
				break;
			j++;
		}
		if(invalid_move_piles(waste[curser-1], piles[j-1][int_first])){
			fout << "Invalid Move" << endl;
		}
		else{
			piles[j][int_first] = waste[curser - 1];
			waste[curser - 1] = "empty";
		}
		fout.close();
		board_maker();
	}
	
	void Board::open(string pile){
		ofstream fout;
		fout.open(output_file_name, ios::app);
		int pile_num = stoi(pile);
		
		if(piles[0][pile_num] == "null"){
			fout << "Invalid Move" << endl;
			return;
		}
		if(piles[opening[pile_num]][pile_num] == "null"){
			opening[pile_num]--;
		}
		fout.close();
		board_maker();
	}
	
	void Board::exit(){
		ofstream fout;
		fout.open(output_file_name, ios::app);
		fout << "Game Over" << endl;
		fout.close();
	}
	
	void Board::print_deck(string* deck){
		int loop = 0;
		while(loop != 52){
			cout << *(deck+loop) << endl;
			loop++;
		}
	}
	
	string* Board::split(string str){
		
		int i = 0;
		int j = 0;
		int first = 0;
		while(true){
			if(str[i] == ' ' || str[i] == '\0'){
				temp_arr[j] = str.substr(first, i-first);
				first = i+1;
				j++;
			}
			if(str[i] == '\0')
				break;
			i++;
		}
		return temp_arr;
	}
	
	bool Board::invalid_move(string str1, string str2){
		

		string str3 = "xx";
		string str4 = "xx";
		str3[0] = str1[1];
		str3[1] = str1[2];
		str4[0] = str2[1];
		str4[1] = str2[2];
		if(str1 == "null"){
			str3 = "0";
			return false;
		}
		int int1 = stoi(str3);
		int int2 = stoi(str4);
		
		if(str1[0] == str1[0]){
			if((int2-int1) == 1)
				return false;
			else 
				return true;
		}
		else
			return true;	
	}
	
	bool Board::invalid_move_piles(string str1, string str2){
		string str3 = "xx";
		string str4 = "xx";
		str3[0] = str1[1];
		str3[1] = str1[2];
		str4[0] = str2[1];
		str4[1] = str2[2];

		if(str2 == "null"){
			str3 = "0";
			return false;
		}

		int int1 = stoi(str3);
		int int2 = stoi(str4);	
		if(str1[0] == 'D'){
			if(str2[0] == 'S' || str2[0] == 'C'){
				if((int2-int1) == 1)
					return false;
				else
					return true;
			}
			else
				return true;
		}
		else if(str1[0] == 'H'){
			if(str2[0] == 'S' || str2[0] == 'C'){
				if((int2-int1) == 1)
					return false;
				else 
					return true;
			}
			else
				return true;
		}
		else if(str1[0] == 'S'){
			if(str2[0] == 'D' || str2[0] == 'H'){
				if((int2-int1) == 1)
					return false;
				else 
					return true;
			}
			else
				return true;
		}
		else if(str1[0] == 'C'){
			if(str2[0] == 'D' || str2[0] == 'H'){
				if((int2-int1) == 1)
					return false;
				else 
					return true;
			}
			else
				return true;
		}
	}
	
	char Board::find_type(string str){
		
		if(str[0] == 'D'){
			return 'D';
		}
		else if(str[0] == 'H'){
			return 'H';
		}
		else if(str[0] == 'S'){
			return 'S';
		}
		else if(str[0] == 'C'){
			return 'C';
		}
		
	}
	
	int Board::length(string* arr){
		
		
		int k = 0;
		int index = 0;
		while(arr[index] != "null"){
			if(arr[index] == "empty"){
				index++;
				continue;
			}
			k++;
			index++;
		}
		return k;
	}
	
	bool Board::win(){
		if(foundation_one[12] == "H13" && foundation_two[12] == "D13" && 
		foundation_three[12] == "S13" && foundation_four[12] == "C13")
			return true;
		else
			return false;
	}
