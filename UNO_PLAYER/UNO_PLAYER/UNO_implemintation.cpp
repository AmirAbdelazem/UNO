#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count
#include <string.h>//to get an integer value with my function  "Take_only_and_only_integer"
#include <cmath>
#include"Data_Structure.h"
#include "my_functions.h"
using namespace std;


int top_old;//top of ground before playing it is '1' at first card and point to empty card in ground
int top_new;//top of ground after playing





//-------------------------------------------------start of UNO_Driver  -----------------------------------------------------------

//default constructor
UNO::UNO()
{
    flag_rev = false;//start clock wise
    counter = -1;//initial value
    Number_of_computer_players = MAX_NUM_OF_PLAYERS - 1;
}

void UNO::Construct_card_input_of_player(Queue* pulling, Ground* UNO_Ground)
{
    int flag;
    cout << "\nPulling==>press '1' play a card ==>press '2'\n";
    Take_only_and_only_integer(&flag);
    switch (flag)
    {
    case 1://card is pulled to both hashes
    {
        card pulled;
        pulled = pulling->dequeue(pulling);
        cout << "\x1B[31m\nThis card was pulled \t \033[0m ";
        display_card(pulled);
        UNO_players[counter].get_Card(pulled);
        cout << "\n";
        if (pulled.value == UNO_Ground->Ground_Cards[UNO_Ground->top - 1].value || pulled.Color == UNO_Ground->Ground_Cards[UNO_Ground->top - 1].Color || pulled.value == 10 || pulled.value == 11)
        {
            int play;
            cout << "\n Do you want to play this pulled card ? if yes==>press '1' no==>Other wise\n";
            Take_only_and_only_integer(&play);
            if (play == 1)
            {
                UNO_Ground->Ground_Cards[UNO_Ground->top] = pulled;
                UNO_Ground->top++;
                UNO_players[counter].delete_Card(pulled);
                return;
            }
        }
        break;
    }
    case 2://play to ground
    {
        card player_card, check;
        cout << "\n Enter your correspond Value for your card\n ";
        Take_only_and_only_integer(&player_card.value);
        cout << "\n Enter your correspond Color for your card\n ";
        cin >> player_card.Color;
        cin.ignore();
        int index = UNO_players[counter].UNO_Color.hashFunction(player_card);
        if (index == -1)
        {
            cout << "\x1B[31m\n\aPlease enter a correct color or pull a card\n\033[0m";
            Construct_card_input_of_player(pulling, UNO_Ground);
        }
        else
        {
            //return the card after searching ==> -1 not found ||| !(-1) found
            check = UNO_players[counter].UNO_Color.table[index].search(UNO_players[counter].UNO_Color.table[index].Head, player_card);

            if (check.value == -1)//if the card is not in his deck
            {
                cout << "\x1B[31m\a\n Enter a correct card or pull a card\n\033[0m";
                Construct_card_input_of_player(pulling, UNO_Ground);
            }
            else//he has the enterd card
            {
                if (check.value == UNO_Ground->Ground_Cards[UNO_Ground->top - 1].value || check.Color == UNO_Ground->Ground_Cards[UNO_Ground->top - 1].Color || check.value == 10 || check.value == 11)
                {
                    UNO_Ground->Ground_Cards[UNO_Ground->top] = check;
                    UNO_Ground->top++;
                    UNO_players[counter].delete_Card(check);

                }
                else
                {
                    cout << "\a Enter correct card if exist in your deck if you have not matched card please pull a card ";
                    Construct_card_input_of_player(pulling, UNO_Ground);
                }
            }

        }
        break;
    }
    default:
    {
        cout << "\x1B[31m\n\a Enter correct number\n\033[0m ";
        Construct_card_input_of_player(pulling, UNO_Ground);
        break;
    }
    }
}
void UNO::human_player_after_wild(Queue* pulling, Ground* UNO_Ground, card card_color)
{
    int flag;
    cout << "\nPulling==>press '1' play a card ==>press '2'\n";
    Take_only_and_only_integer(&flag);
    switch (flag)
    {
    case 1://card is pulled to both hashes
    {
        card pulled;
        pulled = pulling->dequeue(pulling);
        cout << "\x1B[31m\nThis card was pulled \t \033[0m ";
        display_card(pulled);
        UNO_players[counter].get_Card(pulled);
        cout << "\n";
        if (pulled.value == UNO_Ground->Ground_Cards[UNO_Ground->top - 1].value || pulled.Color == UNO_Ground->Ground_Cards[UNO_Ground->top - 1].Color || pulled.value == 10 || pulled.value == 11)
        {
            int play;
            cout << "\n Do you want to play this pulled card ? if yes==>press '1' no==>Other wise\n";
            Take_only_and_only_integer(&play);
            if (play == 1)
            {
                UNO_Ground->Ground_Cards[UNO_Ground->top] = pulled;
                UNO_Ground->top++;
                UNO_players[counter].delete_Card(pulled);
                return;
            }
        }
        return;
    }
    case 2://play to ground
    {
        card player_card, check;
        cout << "\n Enter your correspond Value for your card\n ";
        Take_only_and_only_integer(&player_card.value);
        cout << "\n Enter your correspond Color for your card\n ";
        cin >> player_card.Color;
        cin.ignore();
        int index = UNO_players[counter].UNO_Color.hashFunction(player_card);
        if (index == -1)
        {
            cout << "\x1B[31m\n\aPlease enter a correct color or pull a card\n\033[0m";
            human_player_after_wild(pulling, UNO_Ground, card_color);
        }
        else
        {
            //return the card after searching ==> -1 not found ||| !(-1) found
            check = UNO_players[counter].UNO_Color.table[index].search(UNO_players[counter].UNO_Color.table[index].Head, player_card);

            if (check.value == -1)//if the card is not in his deck
            {
                cout << "\x1B[31m\a\n Enter a correct card or pull a card\n\033[0m";
                human_player_after_wild(pulling, UNO_Ground, card_color);
            }
            else//he has the entered card
            {
                if (check.Color == card_color.Color || check.value == 10 || check.value == 11)
                {
                    UNO_Ground->Ground_Cards[UNO_Ground->top] = check;
                    UNO_Ground->top++;
                    UNO_players[counter].delete_Card(check);

                }
                else
                {
                    cout << "\a Enter correct card if exist in your deck if you have not matched card please pull a card ";
                    human_player_after_wild(pulling, UNO_Ground, card_color);
                }
            }

        }
        return;
    }
    default:
    {
        cout << "\x1B[31m\n\a Enter correct number\n\033[0m ";
        human_player_after_wild(pulling, UNO_Ground, card_color);
        return;
    }
    }
}


void UNO::GET_Number_of_PCs()//create 'n' players n--> number of players
{
    int num;
    cout << "\nEnter number of PCs players between 1 and 9\n";
    Take_only_and_only_integer(&num);
    if (num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9 || num == 1)
        Number_of_computer_players = num;
    else {
        cout << "\x1B[31m\n \a\a please enter availd number between 1 and 9\n\033[0m";

        GET_Number_of_PCs();
    }
}
//create number of players and give EACH ONE OF them 7 cards
void  UNO::Create_PCs_players(Queue* pulling) {

    for (int i = 0; i < Number_of_computer_players + 1; i++)
    {
        UNO_players[i].Give_player_7cards(pulling);
    }
}

void  UNO::REVERS_CARD_set_flag(card revers)
{
    if (revers.value == 13)
    {
        flag_rev = !flag_rev;
        if (flag_rev)
        {
            counter++;
        }
        else
        {
            counter--;
        }
    }

}

//temp is not the top of ground it is a vertual card to help in playing
void  UNO::Set_color_of_ground(card* temp)
{
    if (counter < Number_of_computer_players)//for pc players
    {
        srand(time(0));
        int COLOR_PC = rand() % 4;
        switch (COLOR_PC)
        {
        case 0: {
            temp->Color = 'R';
            break;
        }
        case 1: {
            temp->Color = 'G';
            break;
        }
        case 2: {
            temp->Color = 'B';
            break;
        }
        case 3: {
            temp->Color = 'Y';
            break;
        }
        }
    }
    else//for the human player
    {
        card flag;
        cout << "\n Please Set the ground color by enter first char\n ";
        cout << "\x1B[31mR\033[0m\t\x1B[32mG\033[0m\t\x1B[34mB\033[0m\t\x1B[33mY\033[0m\n ";
        cin >> flag.Color;
        cin.ignore();
        if (flag.Color == 'R' || flag.Color == 'G' || flag.Color == 'B' || flag.Color == 'Y')
        {
            temp->Color = flag.Color;
        }
        else
        {
            cout << "\x1B[31m\a\a Enter a valid Color \n\033[0m ";
            Set_color_of_ground(temp);
        }
    }
    cout << "\n The color of ground is set to be " << get_card_COLOR(temp->Color) << "\n";
}


//recursion function to play correctly after wild card
void UNO::wild_play_after(Queue* pulling, Ground* UNO_Ground, card card_color)
{

    card check;
    if (top_new == top_old)//if true therefore he doesn't play
    {
        if (counter == Number_of_computer_players)//human player
        {
            cout << "\n The card you must play is setted by wild card on " << get_card_COLOR(card_color.Color) << "\n";
            cout << "you should play a matched color  or special card \n";
            desplay_cards();
            human_player_after_wild(pulling, UNO_Ground, card_color);
            top_new = UNO_Ground->top;//to know if previous player played or not
            SET_COUNTER();

        }
        else {//computer player
            check = UNO_players[counter].UNO_Color.Get_card_by_color(card_color);
            desplay_cards();
            UNO_players[counter].Play_by_color_due_to_wild(check, pulling, UNO_Ground, card_color);
            top_new = UNO_Ground->top;//to know if previous player played or not
            SET_COUNTER();
            //to make player [next]
        }
        wild_play_after(pulling, UNO_Ground, card_color);
    }


}

void UNO::play_after(Queue* pulling, Ground* UNO_Ground)
{
    if (top_new == top_old)
    {
        if (counter == Number_of_computer_players)
        {
            desplay_cards();
            Construct_card_input_of_player(pulling, UNO_Ground);
            top_new = UNO_Ground->top;
            SET_COUNTER();
        }
        else
        {

            desplay_cards();
            UNO_players[counter].Search_to_play(UNO_Ground, pulling);
            top_new = UNO_Ground->top;
            SET_COUNTER();
        }
        play_after(pulling, UNO_Ground);
    }
}

// play first_card_into_Ground
void UNO::SET_Ground_first_card(Queue* pulling, Ground* UNO_Ground)
{
    card pulled;
    pulled = pulling->dequeue(pulling);
    if (pulled.value == 11)//wild +4
    {
        pulling->enqueue(pulling, pulled);
        SET_Ground_first_card(pulling, UNO_Ground);
        return;
    }
    UNO_Ground->Ground_Cards[UNO_Ground->top] = pulled;
    UNO_Ground->top++;
    SET_COUNTER();//to make player [0]
}
// after this function one card only is is played to ground at the end of recursion and counter is point to the player in turn
void UNO::Check_Ground_Top_and_Play(Queue* pulling, Ground* UNO_Ground)
{

    card Top_card_of_ground;//to make the check on special cards
    Top_card_of_ground = UNO_Ground->Ground_Cards[UNO_Ground->top - 1];
    switch (Top_card_of_ground.value)
    {
        // 10-->WILD CARD
    case 10: {
        if (!(UNO_Ground->top == 1 && counter == 0))//if it was not first time
        {
            previous_counter();
        }
        card card_color;//virtual card contain color of wild

        top_new = top_old = UNO_Ground->top;//top of ground before playing it is '1' at first card and piont to empty card in ground

        Set_color_of_ground(&card_color);//player current set color
        if (UNO_Ground->top == 1 && counter == 0)//if it was the first card only he will play
        {
            wild_play_after(pulling, UNO_Ground, card_color);
        }
        else
        {
            SET_COUNTER();
            wild_play_after(pulling, UNO_Ground, card_color);
        }
        //  solve_pulled_in_wiled(UNO_Ground, &card_color, pulling);

        break;
    }//11-->Draw Four Wild (+4 and wild)
    case 11: {
        if (!(UNO_Ground->top == 1 && counter == 0))//if it was not first time
        {
            previous_counter();
        }
        card card_color;
        Set_color_of_ground(&card_color);//player current set color
        SET_COUNTER();//to move to player how will
        int diffrence;
        diffrence = pulling->Front - pulling->Tail;
        if (diffrence < 0)
        {
            diffrence = -1 * diffrence;
        }
        if (diffrence < 6)
        {
            *pulling = Insert_to_Pulling_Cards(UNO_Ground->Ground_Cards);
            UNO_Ground->top = 0;
            UNO_Ground->Ground_Cards[UNO_Ground->top] = Top_card_of_ground;
            UNO_Ground->top++;
        }
        if (counter == Number_of_computer_players)//human player
        {
            cout << "\n you will pull 4 cards as pc player entered +4 wild card\n\a";
        }
        UNO_players[counter].get_Card(pulling->dequeue(pulling));
        UNO_players[counter].get_Card(pulling->dequeue(pulling));
        UNO_players[counter].get_Card(pulling->dequeue(pulling));
        UNO_players[counter].get_Card(pulling->dequeue(pulling));
        SET_COUNTER();//to make who pulled +4 card skip his turn
        //now we need to play same color card as setted from player
        top_new = top_old = UNO_Ground->top;//top of ground before playing it is '1' at first card and piont to empty card in ground
        wild_play_after(pulling, UNO_Ground, card_color);

        break;
    }//12-->Skip depend on color
    case 12: {

        SET_COUNTER();//to skip first one after the card only
        top_new = top_old = UNO_Ground->top;//top of ground before playing it is '1' at first card and piont to empty card in ground
        // function to play after skip card without skipping
        play_after(pulling, UNO_Ground);
        break;
    }//13-->Reverse  depend on color
    case 13: {
        if (!(UNO_Ground->top == 1 && counter == 0))//if it was not first time
        {
            previous_counter();
        }
        REVERS_CARD_set_flag(Top_card_of_ground);
        SET_COUNTER();
        top_new = top_old = UNO_Ground->top;//top of ground before playing it is '1' at first card and piont to empty card in ground
        //after this two lines now counter is at the current player
        play_after(pulling, UNO_Ground);

        break;
    }//14--> Draw Two(+2)  depend on color
    case 14: {
        top_new = top_old = UNO_Ground->top;//top of ground before playing it is '1' at first card and point to empty card in ground
        int diffrence;
        diffrence = pulling->Front - pulling->Tail;
        if (diffrence < 0)
        {
            diffrence = -1 * diffrence;
        }
        if (diffrence < 3)
        {
            *pulling = Insert_to_Pulling_Cards(UNO_Ground->Ground_Cards);
            UNO_Ground->top = 0;
            UNO_Ground->Ground_Cards[UNO_Ground->top] = Top_card_of_ground;
            UNO_Ground->top++;
        }
        if (counter == Number_of_computer_players)//human player
        {
            cout << "\n you will pull 2 cards as pc player entered +2 card\n\a";
        }
        UNO_players[counter].get_Card(pulling->dequeue(pulling));
        UNO_players[counter].get_Card(pulling->dequeue(pulling));
        SET_COUNTER();
        play_after(pulling, UNO_Ground);

        break;
    }
    default:
    {
        top_new = top_old = UNO_Ground->top;//top of ground before playing it is '1' at first card and point to empty card in ground
        play_after(pulling, UNO_Ground);
        break;
    }

    }
}

//move to next player depending on Flag_rev
void UNO::SET_COUNTER()
{
    if (flag_rev)//move to next player
    {

        if (counter < 0)
        {
            counter = counter + Number_of_computer_players + 1;//counter clk wise direction
        }
        else {
            counter--;
            if (counter < 0)
            {
                counter = counter + Number_of_computer_players + 1;//counter clk wise direction
            }
        }
    }
    else {
        counter++;
        counter = counter % (Number_of_computer_players + 1);//clk wise direction
    }

}
void UNO::previous_counter()
{
    if (flag_rev)//move to next player
    {
        counter++;
        counter = counter % (Number_of_computer_players + 1);
    }
    else
    {
        if (counter < 0)
        {
            counter = counter + Number_of_computer_players + 1;//counter clk wise direction
        }
        else {
            counter--;
            if (counter < 0)
            {
                counter = counter + Number_of_computer_players + 1;//counter clk wise direction
            }
        }
    }
}


void UNO::desplay_cards()
{
    if (counter == Number_of_computer_players)
    {

        cout << "\x1B[36mYour cards are \n\033[0m";

        UNO_players[counter].UNO_Color.displayHash();
        cout << endl;
    }
    else
    {

        cout << "\x1B[36mPC Player number[\033[0m" << counter + 1 << "\x1B[36m] cards are\n\033[0m";
        UNO_players[counter].UNO_Color.displayHash();
        cout << endl;

    }
}


bool UNO::Game_finished()
{
    for (int i = 0; i <= Number_of_computer_players; i++)
    {
        if (UNO_players[i].UNO_Color.Hash_color_is_empty())
        {
            if (i == Number_of_computer_players)
            {
                cout << "\x1B[35m\nYou are the winner of the game\n\033[0m\n";
            }
            else
            {
                cout << "\x1B[35m\n PC player number [\033[0m" << i + 1 << "\x1B[35m] is winner\n\033[0m\n";
            }
            return true;
        }
    }
    cout << "\n game not Finished \n";

    return false;
}


//-------------------------------------------------end of UNO_Driver  -----------------------------------------------------------
