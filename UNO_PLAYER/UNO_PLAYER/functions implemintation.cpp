#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count
#include <string.h>//to get an integer value with my function  "Take_only_and_only_integer"
#include <cmath>
#include"Data_Structure.h"
#include "my_functions.h"
using namespace std;







//----------------------------------------------------------Start of global function -----------------------------------------------------------


void Get_Cards_of_UNO(card Card[])//generate cards of UNO

{
    Card[Size];
    int index = 0;//to count all 108 different Cards

    for (int i = 0; i < 15; i++)//as all card has values from 0-->14
    {
        int j;
        for (j = 0; j < 4; j++)//for cards of repeated 4 times
        {
            Card[index].value = i;//to get the value of the card

            switch (j)//to Generate the color of card
            {
            case 0:
                Card[index].Color = 'R'; index++;//R-->Red
                break;

            case 1:
                Card[index].Color = 'G'; index++;//G-->Green
                break;

            case 2:
                Card[index].Color = 'B'; index++;//B-->Blue
                break;

            case 3:
                Card[index].Color = 'Y'; index++;//Y-->Yellow
                break;
            }

        }
        if (!(i == 0 || i == 10 || i == 11))//to avoid 4 cards as it make 8 cards
        {
            for (; j < 8; j++)
            {
                Card[index].value = i;//to get the value of the card

                switch (j)//to Generate the color of card
                {
                case 4:
                    Card[index].Color = 'R'; index++;//R-->Red
                    break;

                case 5:
                    Card[index].Color = 'G'; index++;//G-->Green
                    break;

                case 6:
                    Card[index].Color = 'B'; index++;//B-->Blue
                    break;

                case 7:
                    Card[index].Color = 'Y'; index++;//Y-->Yellow
                    break;
                }

            }
        }

    }
}


int Random_Values(int Start, int End)//get random value in specific range Start to End
{
    int N = End - Start + 1;//number of values in the range
    return  Start + rand() % N;// this is our random value

}


bool emptycards(card cheack[])//to check if cards of UNO are all used means that it is empty
{
    for (int i = 0; i < Size; i++)
    {
        if (cheack[i].value != -1)// this condition means that there is unused cards so it is not empty
            return false;
    }
    return true;

}




Queue Insert_to_Pulling_Cards(card my_cards_array[])//take array of cards then randomly rearrange it into queue
{
    Queue PULLING_CARDS;
    while (!emptycards(my_cards_array))//outer loop is to check the unused cards
    {
        for (int i = 0; i < Size; i++)//inner loop is for (1)&(2)
        {

            int random = Random_Values(0, Size - 1);//get random value to rearrange it randomly
            //(1) swapping the cards in array - which is the sorted original UNO -
            //with the pulling cards to be ready for playing
            if (my_cards_array[random].value == -1)
            {
                continue;
            }
            PULLING_CARDS.enqueue(&PULLING_CARDS, my_cards_array[random]);//(1)
            //(2) Free the card that has gone from array to queue by replacing it with -1
            my_cards_array[random].value = -1;//(2) -1 refer to empty card in array
        }

    }
    return PULLING_CARDS;
}






void Take_only_and_only_integer(int* my_int_value/*pointer to my integer address*/)
{
    char integer_trial[100];
    int true_integer = 0;
    cout << "\nEnter the integer number \n\n";
    cin.getline(integer_trial, 100);
    int len = strlen(integer_trial);
    for (int i = 0; i < len; i++)
    {
        int ASCII = integer_trial[i];
        if (ASCII == 45)
        {
            cout << "\x1B[31m\a number must be positive \n\n\033[0m ";
            Take_only_and_only_integer(my_int_value);
            return;//to avoid recursive return values
        }
        if (ASCII >= 48 && ASCII <= 57)
        {
            continue;
        }
        else
        {
            cout << "\x1B[31m\aThe number  must be only integer\n\n\033[0m";
            Take_only_and_only_integer(my_int_value);
            return;//to avoid recursive return values
        }
    }
    for (int i = 0; i < len; i++)
    {
        int ASCII = integer_trial[i];
        //as pow return double so make type correction
        true_integer += (ASCII - 48) * int(pow(10, len - 1 - i));
    }


    *my_int_value = true_integer;

}



string  get_card_COLOR(char value) {
    switch (value)
    {
    case 'R':
    {
        return "\x1B[31m'R'\033[0m\t\t";//R
    }
    case 'G':
    {
        return "\x1B[32m'G'\033[0m\t\t";//G
    }case 'B':
    {
        return"\x1B[34m'B'\033[0m\t\t";//B
    }case 'Y':
    {
        return  "\x1B[33m'Y'\033[0m\t\t";//Y
    default:
        return "";
    }

    }
}



// to get the card name of special cards by its number
string  get_card_name(int value)
{//######   convert int to char then string :)   ###
    /*
    char character = value + 48;
    string back = "z " ;
    back[0] = character;*/
    switch (value)
    {
    case 10:
    {
        return "  Wild card  PLAYED ON ANY COLOR AND VALUE  ";
    }
    case 11:
    {
        return "  Wild Draw Four card PLAYED ON ANY COLOR AND VALUE  ";
    }case 12:
    {
        return "  Skip card  ";
    }case 13:
    {
        return "  Reverse card  ";
    }case 14:
    {
        return "  Draw Two card  ";
    }
    default:
        return  "";
    }

}



//sub function in the desplay of linked list

void   display_card(card temp)
{

    string card_name = get_card_name(temp.value);

    switch (temp.Color)
    {
    case 'R':
    {
        cout << "--";
        printf("\033[3;41;30m[%d'R'%s]\033[0m", temp.value, &card_name[0]);
        cout << "--";
        break;
    }
    case 'G':
    {
        cout << "--";
        printf("\033[3;42;30m[%d'G'%s]\033[0m", temp.value, &card_name[0]);
        cout << "--";
        break;

    }case 'B':
    {        cout << "--";
    printf("\033[3;44;30m[%d'B'%s]\033[0m", temp.value, &card_name[0]);
    cout << "--";
    break;

    }case 'Y':
    {        cout << "--";
    printf("\033[3;43;30m[%d'Y'%s]\033[0m", temp.value, &card_name[0]);
    cout << "--";
    break;
    }
    default:
        break;

    }

}

//----------------------------------------------------------end of global function -----------------------------------------------------------





