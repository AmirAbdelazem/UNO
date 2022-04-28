#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count
#include <string.h>//to get an integer value with my function  "Take_only_and_only_integer"
#include <cmath>
#include"Data_Structure.h"
#include <chrono>
#include "my_functions.h"
using namespace std;








//put the card into UNO_Numbers & UNO_Color both

//create 'n' playersn--> number of players

void desplay_1() {
    printf("\x1B[34m\n\n_______________________________________________________________________________________________________________\n\n\033[0m\t\t");//B



    cout << "\n\n\t\t\t\t\x1B[31m***     ***\033[0m\t\x1B[32m******\033[0m\x1B[34m******\033[0m\t\x1B[33m*************\033[0m\n";
    cout << "\t\t\t\t\x1B[31m***     ***\033[0m\t\x1B[32m******\033[0m\x1B[34m******\033[0m\t\x1B[33m*************\033[0m\n";
    cout << "\t\t\t\t\x1B[31m***     ***\033[0m\t\x1B[32m***     \033[0m\x1B[34m ***\033[0m\t\x1B[33m*****   *****\033[0m\n";
    cout << "\t\t\t\t\x1B[31m***     ***\033[0m\t\x1B[32m***     \033[0m\x1B[34m ***\033[0m\t\x1B[33m*****   *****\033[0m\n";
    cout << "\t\t\t\t\x1B[31m***     ***\033[0m\t\x1B[32m***     \033[0m\x1B[34m ***\033[0m\t\x1B[33m*****   *****\033[0m\n";
    cout << "\t\t\t\t\x1B[31m***********\033[0m\t\x1B[32m***     \033[0m\x1B[34m ***\033[0m\t\x1B[33m*************\033[0m\n";
    cout << "\t\t\t\t\x1B[31m***********\033[0m\t\x1B[32m***     \033[0m\x1B[34m ***\033[0m\t\x1B[33m*************\033[0m\n";

    printf("\x1B[34m\n\n_______________________________________________________________________________________________________________\n\n\033[0m\t\t");//B


}


int main()
{


    auto start = chrono::steady_clock::now();





    desplay_1();
    card My_Cards[Size];//array that include the all cards before rearrange it randomly

    Get_Cards_of_UNO(My_Cards);// to load the UNO CARDS

    srand(time(0));//to make the game different in each run time

    Queue PULLING_CARDS;//define the cards that will be distributed on players

    PULLING_CARDS = Insert_to_Pulling_Cards(My_Cards);

    Ground UNO_GND;//make all the ground array empty
    for (int i = 0; i < Size; i++)
    {
        UNO_GND.Ground_Cards[i].value = -1; //empty ground;

    }

    UNO OBJ;
    OBJ.GET_Number_of_PCs();
    OBJ.Create_PCs_players(&PULLING_CARDS);

    OBJ.SET_Ground_first_card(&PULLING_CARDS, &UNO_GND);
    while (!OBJ.Game_finished())
    {

        cout << "\nCards before playing\n";
        cout << "\x1B[35mcard on top of ground=\033[0m ";
        display_card(UNO_GND.Ground_Cards[UNO_GND.top - 1]); //get_card_name(UNO_GND.Ground_Cards[UNO_GND.top - 1].value)<<UNO_GND.Ground_Cards[UNO_GND.top - 1].value << " COLOR= " <<get_card_COLOR( UNO_GND.Ground_Cards[UNO_GND.top - 1].Color);
        cout << "\n";

        OBJ.Check_Ground_Top_and_Play(&PULLING_CARDS, &UNO_GND);

        cout << " After playing card on top of ground= ";
        display_card(UNO_GND.Ground_Cards[UNO_GND.top - 1]);//<< get_card_name(UNO_GND.Ground_Cards[UNO_GND.top - 1].value)<< UNO_GND.Ground_Cards[UNO_GND.top - 1].value << "COLOR= " << get_card_COLOR(UNO_GND.Ground_Cards[UNO_GND.top - 1].Color);
        cout << "\n";

        cout << "\x1B[34m\n\n----------------------------------------------------------------------------------------------------\n\033[0m";
        auto end = chrono::steady_clock::now();

        cout << "Elapsed time in milliseconds: "
            << chrono::duration_cast<chrono::milliseconds>(end - start).count()
            << " ms" << endl;

    }


    return 0;
}

