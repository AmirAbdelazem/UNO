#pragma once
#include <string>
using namespace std;

void   display_card(card temp);



Queue Insert_to_Pulling_Cards(card[]);



bool emptycards(card[]);//to check if cards of UNO are all used means that it is empty

void Get_Cards_of_UNO(card[]);//generate cards of UNO

int Random_Values(int Start, int End);//get random value in specific range Start to End


string  get_card_name (int value);
string  get_card_COLOR (char);//TO PAINT THE COLORS

void   display_card(card temp);

//get input only integer from the user to avoid any infinite loop
void Take_only_and_only_integer(int*);
