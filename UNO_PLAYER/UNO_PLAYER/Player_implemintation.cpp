#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count
#include <string.h>//to get an integer value with my function  "Take_only_and_only_integer"
#include <cmath>
#include"Data_Structure.h"
#include "my_functions.h"
using namespace std;






//-------------------------------------------------start of Player  -----------------------------------------------------------


void Player::get_Card(card input)
{
    UNO_Numbers.insertItem(input);
    UNO_Color.insertItem(input);
}

// give 7 cards for #one player
void Player::Give_player_7cards(Queue* pulling)
{
    for (int i = 0; i < 7; i++)
    {
        get_Card(pulling->dequeue(pulling));
    }
}

//CHECK IF CARD WAS FOUND PALY IT AND
    //DELETE FROM TWO HASHES IF NOT PLAY UNTILL GET CASE FROM FUNCTION  Search_to_play sub Function
bool Player::check_on_Ground_Top_and_play(card check, Ground* array)
{

    if (check.value != -1)//NOT FOUND IN PLAYER CARDS
    {
        array->Ground_Cards[array->top] = check;
        array->top++;
        delete_Card(check);
        return true;
    }
    else {
        return false;
    }

}
//countinue untill go to next player this Function is to Play
void Player::Search_to_play(Ground* array, Queue* pulling)
{
    card Card_top_ground = array->Ground_Cards[array->top - 1];//TOP CARD IN GROUND
    card check;//-1 MEANS NOT FOUND

    card check1[4], check2[4];//special cards
    for (int i = 0; i < 4; i++)
    {
        check1[i].value = 10;// wild
        check2[i].value = 11;// wild +4
        switch (i)
        {
        case 0: {
            check1[i].Color = 'R';
            check2[i].Color = 'R';
            break;
        }
        case 1: {
            check1[i].Color = 'G';
            check2[i].Color = 'G';
            break;
        }
        case 2: {
            check1[i].Color = 'B';
            check2[i].Color = 'B';
            break;
        }
        case 3: {
            check1[i].Color = 'Y';
            check2[i].Color = 'Y';
            break;
        }
        }
    }


    bool flag;/*true thus i played and delete the card so i finished
    false thus we need to try another thing*/

    check = UNO_Numbers.Get_card_by_num(Card_top_ground);//return -1 if not found

    flag = check_on_Ground_Top_and_play(check, array);//check by value of card
    if (flag)
    {
        return;
    }
    else
    {
        check = UNO_Color.Get_card_by_color(Card_top_ground);//return -1 if not found
        flag = check_on_Ground_Top_and_play(check, array);//check by color of card
        if (flag)
        {
            return;
        }
        else {
            for (int i = 0; i < 4; i++)
            {
                check = UNO_Numbers.Get_card_by_num(check1[i]);//return -1 if not found
                flag = check_on_Ground_Top_and_play(check, array);//check special
                if (flag)
                    break;
            }if (flag)
            {
                return;
            }
            else
                for (int i = 0; i < 4; i++)
                {
                    check = UNO_Numbers.Get_card_by_num(check2[i]);//return -1 if not found
                    flag = check_on_Ground_Top_and_play(check, array);//check special
                    if (flag)
                        break;
                }if (flag)
                {
                    return;
                }
                else {
                    //if all cases return false then 1)pull -----2) they to play pulled in '1'
                    card pulled;
                    pulled = pulling->dequeue(pulling);
                    //  card temp = array.Ground_Cards[array.top];
                    if (pulled.value == -1)
                    {
                        *pulling = Insert_to_Pulling_Cards(array->Ground_Cards);
                        array->top = 0;
                        array->Ground_Cards[array->top] = Card_top_ground;
                        array->top++;
                        pulled = pulling->dequeue(pulling);

                    }
                    cout << "\x1B[31m\nThis card was pulled \t \033[0m ";
                    display_card(pulled);
                    cout << "\n";
                    if (pulled.value == Card_top_ground.value || pulled.Color == Card_top_ground.Color || pulled.value == 10 || pulled.value == 11)
                    {
                        array->Ground_Cards[array->top] = pulled;
                        array->top++;
                    }
                    else
                    {
                        get_Card(pulled);
                    }

                }

        }
    }

}

void Player::Play_by_color_due_to_wild(card temp, Queue* pulling, Ground* array, card by_color)
{
    card Card_top_ground = array->Ground_Cards[array->top - 1];//TOP CARD IN GROUND

    card check1[4], check2[4];//special cards 10 & 11
    for (int i = 0; i < 4; i++)
    {
        check1[i].value = 10;// wild
        check2[i].value = 11;// wild +4
        switch (i)
        {
        case 0: {
            check1[i].Color = 'R';
            check2[i].Color = 'R';
            break;
        }
        case 1: {
            check1[i].Color = 'G';
            check2[i].Color = 'G';
            break;
        }
        case 2: {
            check1[i].Color = 'B';
            check2[i].Color = 'B';
            break;
        }
        case 3: {
            check1[i].Color = 'Y';
            check2[i].Color = 'Y';
            break;
        }
        }
    }


    bool flag;
    flag = check_on_Ground_Top_and_play(temp, array);
    if (flag)
    {
        return;
    }
    else {
        for (int i = 0; i < 4; i++)
        {
            temp = UNO_Numbers.Get_card_by_num(check1[i]);//return -1 if not found
            flag = check_on_Ground_Top_and_play(temp, array);//check special
            if (flag)
                break;
        }if (flag)
        {
            return;
        }
        else
            for (int i = 0; i < 4; i++)
            {
                temp = UNO_Numbers.Get_card_by_num(check2[i]);//return -1 if not found
                flag = check_on_Ground_Top_and_play(temp, array);//check special
                if (flag)
                    break;
            }if (flag)
            {
                return;
            }
            else {
                //if all cases return false then 1)pull -----2) they to play pulled in '1'
                card pulled;
                pulled = pulling->dequeue(pulling);
                //  card temp = array.Ground_Cards[array.top];
                if (pulled.value == -1)
                {
                    *pulling = Insert_to_Pulling_Cards(array->Ground_Cards);
                    array->top = 0;
                    array->Ground_Cards[array->top] = Card_top_ground;
                    array->top++;
                    pulled = pulling->dequeue(pulling);

                }
                cout << "\x1B[31m\nThis card was pulled \t \033[0m ";
                display_card(pulled);
                cout << "\n";
                if (pulled.Color == by_color.Color || pulled.value == 10 || pulled.value == 11)
                {
                    array->Ground_Cards[array->top] = pulled;
                    array->top++;
                }
                else
                {
                    get_Card(pulled);
                }


            }
    }
}

//delete the card from UNO_Numbers & UNO_Color both
void Player::delete_Card(card input)
{
    UNO_Numbers.deletecard(input);
    UNO_Color.deletecard(input);
}



//-------------------------------------------------end of Player  -----------------------------------------------------------





