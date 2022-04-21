#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count
#include <cmath>

using namespace std;


const int BUCKET_num = 15; // No. of buckets for numbers & spicitial cards in UNO
const int MAX_NUM_OF_PLAYERS = 10;//maximum number of players in UNO game
const int BUCKET_color = 4; // No. of buckets for  'R' 'G' 'B' 'Y'  Colors
int top_old;//top of ground before playing it is '1' at first card and piont to empty card in ground
int top_new;//top of ground after playing

const int Size = 108;//No. of UNO cards
struct card //our card in UNO has Value & color
{
    int value;
    char Color;
};
struct Ground {
    card Ground_Cards[Size];//array that include the all cards played on the ground

    int top = 0;  
};


//this Queue is representing the pulling cards
class Queue//Queue using Array with two indices   to O(1) of enqueue & dequeue
{

public:
    card arr[Size] = {};//array that will include the unsorted cards after randomly rearrange
    int Front = -1;
    int Tail = -1;

    void enqueue(class Queue*, card);//to put cards in the queue
    card dequeue(class Queue*);//to get cards from queue

};
Queue Insert_to_Pulling_Cards(card[]);


//nodes of linked list
struct node {
    card item;
    node* next;
};

class linked_list {
public:
    int legnth = 0;
    node* Head = NULL;
    //insert new node in the first of the linked list O(1)
    void push(node** Head_REF/*ADDRESS OF THE HEAD*/, card element)
    {
        node* newnode = new node;
        newnode->item = element;
        //the above 2 lines are creating the new node in the list
        newnode->next = *Head_REF;
        *Head_REF = newnode;
        legnth++;
    }
    card search(node* head, card x)
    {
        node* current = head;
        while (current != NULL)
        {
            if (current->item.value == x.value)
                return x;
            current = current->next;
        }
        x.value = -1;
        return x;
    }


    // as we define the list from the hash table to have consistant type of data -cards-
    //so we will delete first node only -if exist- every time

    void delete_node(node** head_ref /*ADDRESS OF THE HEAD*/, card key)
    {
        node* temp6 = *head_ref;
        node* prev = NULL;
        if (temp6->item.value == key.value&& temp6->item.Color== key.Color&& temp6!=NULL)
        {
            (*head_ref) = (*head_ref)->next;
            delete temp6;
            legnth--;
            return;
        }

        while (temp6 != NULL && (temp6->item.value != key.value || temp6->item.Color != key.Color))
        {
            prev = temp6;
            temp6 = temp6->next;
        }
        if (temp6 == NULL)
        {
            cout << "\n card is not found \n" << endl;
            return;
        }else{
            prev->next = temp6->next;
            delete temp6;
            legnth--;
              }
    }

    // display all nodes of the list
    void display(node* curr/*Head*/)
    {
        bool flag = true;
        while (curr)
        {
            cout << curr->item.Color << "\t" << curr->item.value << "\t\t";
            curr = curr->next;
            flag = false;
        }
        if (flag)
        {

            cout << "\nThis list is empty\n";
        }
    }
};

//Hash table of 4 colors in UNO
class Hash_color
{

public:
    // Array of linked lists to form the hash table with chaining resolving collision
    linked_list table[BUCKET_color];



    // inserts a key into hash table
    void insertItem(card my_card);

    void deletecard(card);

    // return card by this color
    card Get_card_by_color(card key);

    // hash function to map colors to key
    int hashFunction(card my_card)
    {
        int i=-1;
        switch (my_card.Color)
        {
        case 'R':
        {i = 0;
        break; }
        case 'G':
        { i= 1;
            break;
        }
        case 'B':
        { i= 2;
             break;
          }
        case 'Y':
        {  i= 3;
            break;
         }
        
        }
        return i;

    }

    void displayHash();
    bool Hash_color_is_empty()
    {
        if (table[0].Head|| table[1].Head || table[2].Head || table[3].Head  )
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

//Hash table of numbers & spicitial cards in UNO
class Hash
{


    // Array of linked lists to form the hash table with chaining resolving collision
    linked_list table[BUCKET_num];

public:

    // inserts a key into hash table
    void insertItem(card my_card);
    void deletecard(card);
    // deletes a key from hash table
    card Get_card_by_num(card key);

    // hash function to map values to key
    int hashFunction(card my_card) {
        return (my_card.value % BUCKET_num);
    }

    void displayHash();
};

bool emptycards(card[]);//to check if cards of UNO are all used means that it is empty

void Get_Cards_of_UNO(card[]);//generate cards of UNO

int Random_Values(int Start, int End);//get random value in specific range Start to End

class Player
{
public:
    Hash UNO_Numbers;
    Hash_color UNO_Color;

    void get_Card(card);//put the card into UNO_Numbers & UNO_Color both

    void Give_player_7cards(Queue*);// give 7 cards for #one player

    bool check_on_Ground_Top_and_play(card , Ground*);//CHECK IF CARD WAS FOUND PALY IT AND 
    //DELETE FROM TWO HASHES IF NOT PLAY UNTILL GET CASE FROM FUNCTION  Search_to_play

    void Search_to_play(Ground*,Queue*);//countinue untill go to next player 

    void delete_Card(card);//delete the card from UNO_Numbers & UNO_Color both
    void Play_by_color_due_to_wild(card, Queue*, Ground*, card);


};
//put the card into UNO_Numbers & UNO_Color both
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
void Player::Search_to_play(Ground* array,Queue* pulling)
{
    card Card_top_ground = array->Ground_Cards[array->top-1];//TOP CARD IN GROUND
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

    flag=check_on_Ground_Top_and_play(check, array);//check by value of card
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
                for(int i = 0; i < 4; i++)
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
                //if all cases return false then 1)pull -----2) thry to play pulled in '1'
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
                //if all cases return false then 1)pull -----2) thry to play pulled in '1'
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
 
 class UNO
 {
 public:
     bool flag_rev;// true ==> counter clock wise ------false==>clock wise  change if revers card played
     int  counter;// to get the player who will play
     int Number_of_computer_players;//must deal with it in all functions depend on  number of players
     int Number_of_players = Number_of_computer_players + 1;
     //default constructor
     UNO()
     {
         flag_rev = false;//start clock wise
         counter = -1;//initial value
         Number_of_computer_players = MAX_NUM_OF_PLAYERS-1;
     }
     
     Player UNO_players[MAX_NUM_OF_PLAYERS];// array of max players 
     void Create_PCs_players(Queue*);//create players and give them 7 cards
     void GET_Number_of_PCs();//creat 'n' playersn--> number of players
     void first_card_into_Ground(Queue*,Ground*);
     void REVERS_CARD_set_flag(card);
     //void player_card_into_Ground(Queue* , Ground*);
     void Set_color_of_ground(card*);

     void SET_COUNTER();
     void SET_Ground_first_card(Queue*, Ground*);
     void solve_pulled_in_wiled(Ground*, card* , Queue* );
     void solve_pulled_in_wiled_and_plus_4(Ground*, card*, Queue*);

     void wild_play_after( Queue*, Ground*, card);
     card Construct_card_inout_of_player(Queue*, Ground* UNO_Ground);

     bool Game_finished();
 };
 //creat 'n' playersn--> number of players 
 void UNO::GET_Number_of_PCs()//creat 'n' players n--> number of players
 {
     int num;
     cout << "\nEnter number of PCs players between 1 and 9\n";
     cin >> num;
     cin.ignore();
     if (num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9 || num == 1)
         Number_of_computer_players = num;
     else {
         cout << " \a\a please enter availd number between 1 and 9 ";
         GET_Number_of_PCs();
     }
 }
 //create number of players and give EACH ONE OF them 7 cards
 void  UNO::Create_PCs_players( Queue *pulling) {
    
     for (int i = 0; i < Number_of_computer_players; i++)
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
             return;
         }
         case 1: {
             temp->Color = 'G';
             return;
         }
         case 2: {
             temp->Color = 'B';
             return;
         }
         case 3: {
             temp->Color = 'Y';
             return;
         }
         }
     }
     else//for the human player
     {
         card flag;
         cout << "\n Please Set the ground color by enter first char\n ";
         cout << "'R'=>Red\t'G'=>Green\t'B'=>Blue\t'Y'=>Yellow  \n ";
         cin >> flag.Color;
         cin.ignore();
         if (flag.Color == 'R' || flag.Color == 'G' || flag.Color == 'B' || flag.Color == 'Y')
         {
             temp->Color = flag.Color;
         }
         else
         {
             cout << "\a\a Enter a vaild Color \n ";
             Set_color_of_ground(temp);
         }
     }
 }

 void UNO::solve_pulled_in_wiled(Ground* UNO_Ground, card* temp2,Queue* pulling)
 {
     if (UNO_Ground->Ground_Cards[UNO_Ground->top-1].value == 10 && UNO_Ground->Ground_Cards[UNO_Ground->top - 2].value != 10)//if pulled we need to keep the color
     {//first condition will be
         //(UNO_Ground->Ground_Cards[0].value ==10&& UNO_Ground->top ==1)
         SET_COUNTER();
         card check;
         check = UNO_players[counter].UNO_Color.Get_card_by_color(*temp2);
         UNO_players[counter].Play_by_color_due_to_wild(check, pulling, UNO_Ground, *temp2); //if pulled make colliosn
         solve_pulled_in_wiled(UNO_Ground, temp2, pulling);
     }
     else
     {
         return;
     }
 }
 void UNO::solve_pulled_in_wiled_and_plus_4(Ground* UNO_Ground, card* temp2, Queue* pulling)
 {
     if (UNO_Ground->Ground_Cards[UNO_Ground->top - 1].value == 11 && UNO_Ground->Ground_Cards[UNO_Ground->top - 2].value != 11)//if pulled we need to keep the color
     {
         SET_COUNTER();
         card check;
         check = UNO_players[counter].UNO_Color.Get_card_by_color(*temp2);
         UNO_players[counter].Play_by_color_due_to_wild(check, pulling, UNO_Ground, *temp2); //if pulled make colliosn
         solve_pulled_in_wiled(UNO_Ground, temp2, pulling);
     }
     else
     {
         return;
     }
 }

 //recursion function to play correctly after wild card
 void UNO::wild_play_after( Queue* pulling, Ground* UNO_Ground, card card_color)
 {
     


     card check;
     if (top_new == top_old)//if true therefore he doesn't play 
     {
         if (counter == Number_of_computer_players)
         {

         }
         check = UNO_players[counter].UNO_Color.Get_card_by_color(card_color);
         UNO_players[counter].Play_by_color_due_to_wild(check, pulling, UNO_Ground, card_color);
         top_new = UNO_Ground->top;//to know if previous player played or not
         SET_COUNTER();
         //to make player [next]

         wild_play_after( pulling, UNO_Ground, card_color);
     }
     

 }
 // play first_card_into_Ground 
 void UNO::SET_Ground_first_card(Queue* pulling, Ground* UNO_Ground)
 {
     card pulled;
     pulled = pulling->dequeue(pulling);
     if (pulled.value==11)//wild +4 
     {
         pulling->enqueue(pulling, pulled);
         SET_Ground_first_card(pulling, UNO_Ground);
     }
     card first_card_into_ground;//to make the check on special cards
     UNO_Ground->Ground_Cards[UNO_Ground->top] = first_card_into_ground;
     UNO_Ground->top++;
     SET_COUNTER();
 }
 void UNO::first_card_into_Ground(Queue* pulling, Ground* UNO_Ground)
 {
     
     card Top_card_of_ground;//to make the check on special cards
     switch (Top_card_of_ground.value)
     {
         // 10-->WILD CARD
     case 10: {

         card card_color;//virtual card contain color of wild

         top_new= top_old = UNO_Ground->top;//top of ground before playing it is '1' at first card and piont to empty card in ground

         Set_color_of_ground(&card_color);//player 0 set color

         wild_play_after( pulling, UNO_Ground, card_color);
       //  solve_pulled_in_wiled(UNO_Ground, &card_color, pulling);
        
         break;
     }//11-->Draw Four Wild (+4 and wild)
     case 11: {
         pulling->enqueue(pulling, first_card_into_ground);
         first_card_into_Ground(pulling, UNO_Ground);
         break;
     }//12-->Skip depened on color
     case 12: {

         SET_COUNTER();//player[0] not play
         UNO_Ground->Ground_Cards[UNO_Ground->top] = first_card_into_ground;
         UNO_Ground->top++;
         SET_COUNTER();//player[1] 
         //function that make next play without skipping
         UNO_players[counter].Search_to_play(UNO_Ground,pulling);
         break;
     }//13-->Reverse  depened on color
     case 13: {

         REVERS_CARD_set_flag(first_card_into_ground);
         UNO_Ground->Ground_Cards[0] = first_card_into_ground;
         UNO_Ground->top++;
         counter++;//to make first player to play

         break;
     }//14--> Draw Two(+2)  depened on color
     case 14: {

         UNO_Ground->Ground_Cards[0] = first_card_into_ground;
         UNO_Ground->top++;

         counter++;//counter=0
         //if all cases return false then 1)pull -----2) thry to play pulled in '1'
         UNO_players[counter].get_Card(pulling->dequeue(pulling));
         UNO_players[counter].get_Card(pulling->dequeue(pulling));

         counter++;//to skip first player his play
         UNO_players[counter].Search_to_play(UNO_Ground, pulling);//play card to ground ##if exist
         break;
     }
     default:
     {
         UNO_Ground->Ground_Cards[UNO_Ground->top] = first_card_into_ground;
         UNO_Ground->top++;

         break;
     }


     }
 }
 //after this first card

 //move to next player depending on Flag_rev
 void UNO::SET_COUNTER()
 {
     if (flag_rev)//move to next player
     {

         if (counter < 0)
         {
             counter = counter + Number_of_players;//counter clk wise direction
         }
         else {
             counter--;
             if (counter < 0)
             {
                 counter = counter + Number_of_players;//counter clk wise direction
             }
         }
     }
     else {
         counter++;
         counter = counter % Number_of_players;//clk wise direction
     }
     
 }

 // take card from the two hashes from player 
 //void UNO::player_card_into_Ground(Queue* pulling, Ground* UNO_Ground)
 //{
 //    card top_ground_card;//to make the check on special cards
 //    
 //        int last_card = UNO_Ground->top - 1;
 //    top_ground_card = UNO_Ground->Ground_Cards[last_card];//get the card of top of ground
 //    switch (top_ground_card.value)
 //    {
 //        // 10-->WILD CARD
 //    case 10: {
 //        card temp2;//virtual card contain color of wild WE KNOW THAT IT IS NOT INITIALIZED AS IT WILL BE INITIALIZED IN next line

 //        UNO_players[counter].Set_color_of_ground(&temp2);//player[counter] set color in temp2

 //        SET_COUNTER();//to move to the next player
 //        card check;
 //        check = UNO_players[counter].UNO_Color.Get_card_by_color(temp2);
 //        UNO_players[counter].Play_by_color_due_to_wild(check, pulling, UNO_Ground, temp2);
 //        solve_pulled_in_wiled(UNO_Ground, &temp2, pulling);
 //        break;
 //    }//11-->Draw Four Wild (+4 and wild)
 //    case 11: {

 //        card temp2;//virtual card contain color of wild WE KNOW THAT IT IS NOT INITIALIZED AS IT WILL BE INITIALIZED IN next line
 //        UNO_players[counter].Set_color_of_ground(&temp2);//player[counter] set color in temp2
 //   
 //        SET_COUNTER();
 //        card pulled;
 //        int diffrence;
 //        diffrence=pulling->Front - pulling->Tail;
 //        diffrence = int(fabsf(diffrence));
 //        if (diffrence<6)
 //        {            
 //              *pulling = Insert_to_Pulling_Cards(UNO_Ground ->Ground_Cards);
 //                UNO_Ground->top = 0;
 //                UNO_Ground ->Ground_Cards[UNO_Ground->top] = top_ground_card;
 //                UNO_Ground->top++;
 //                pulled = pulling->dequeue(pulling);
 //                UNO_players[counter].get_Card(pulled);
 //                UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //                UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //                UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //        }
 //        else {
 //            UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //            UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //            UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //            UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //        }
 //        SET_COUNTER();
 //        card check;
 //        check = UNO_players[counter].UNO_Color.Get_card_by_color(temp2);
 //        UNO_players[counter].Play_by_color_due_to_wild(check, pulling, UNO_Ground, temp2);
 //        solve_pulled_in_wiled_and_plus_4(UNO_Ground, &temp2, pulling);
 //        break;
 //    }//12-->Skip depened on color
 //    case 12: {
 //        SET_COUNTER();
 //        UNO_players[counter].Search_to_play(UNO_Ground, pulling);//play card to ground ##if exist

 //        break;
 //    }//13-->Reverse  depened on color
 //    case 13: {

 //        REVERS_CARD_set_flag(top_ground_card);
 //        SET_COUNTER();
 //        UNO_players[counter].Search_to_play(UNO_Ground, pulling);//play card to ground ##if exist

 //        break;
 //    }//14--> Draw Two(+2)  depened on color
 //    case 14: {

 //        SET_COUNTER();
 //        UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //        UNO_players[counter].get_Card(pulling->dequeue(pulling));
 //        SET_COUNTER();
 //        UNO_players[counter].Search_to_play(UNO_Ground, pulling);//play card to ground ##if exist

 //        break;
 //    }
 //    default:
 //    {
 //        SET_COUNTER();
 //        UNO_players[counter].Search_to_play(UNO_Ground, pulling);//play card to ground ##if exist
 //        break;
 //    }

 //    }
 //}

 bool UNO::Game_finished()
 {
     for (int i = 0; i < Number_of_players; i++)
     {
         if (UNO_players[i].UNO_Color.Hash_color_is_empty())
         {
             cout << "\n player number " << i + 1 << " is winner\n";
             return true;
         }
     }
     cout << "\n game not F\n";

     return false;
 }





int main()
{
    
    card My_Cards[Size];//array that include the all cards before rearrange it randomly
    
    Get_Cards_of_UNO(My_Cards);// to load the UNO CARDS

    srand(time(0));//to make the game different in each run time


    Queue PULLING_CARDS;//define the cards that will be distributed on players

    PULLING_CARDS = Insert_to_Pulling_Cards(My_Cards);
    Ground UNO_GND;
    for (int i = 0; i < Size; i++)
    {
        UNO_GND.Ground_Cards[i].value = -1; //empty ground;

    }

    UNO amir;
    amir.GET_Number_of_PCs();

    amir.Create_PCs_players(&PULLING_CARDS);
    amir.first_card_into_Ground(&PULLING_CARDS, &UNO_GND);
    while (!amir.Game_finished())
    {
        cout << "card on top of ground= " << UNO_GND.Ground_Cards[UNO_GND.top-1].value << "COLOR= " << UNO_GND.Ground_Cards[UNO_GND.top-1].Color;
            amir.SET_COUNTER();
            cout << "\ncards by Numbers before play\n";
            amir.UNO_players[amir.counter].UNO_Numbers.displayHash();
            amir.player_card_into_Ground(&PULLING_CARDS, &UNO_GND);
            cout << "card on top of ground= " << UNO_GND.Ground_Cards[UNO_GND.top - 1].value << "COLOR= " << UNO_GND.Ground_Cards[UNO_GND.top - 1].Color;

            cout << "cards by Numbers after \n";
            amir.UNO_players[amir.counter].UNO_Numbers.displayHash();
       
        
    }

    
    return 0;
}


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


void Queue::enqueue(class Queue* UNO_cards, card input)
{
    if (input.value == -1)//means that the card is empty as we difine -1 to be empty so take another value
        return;
    if (UNO_cards->Front == -1 && UNO_cards->Tail == -1)//empty queue
    {
        UNO_cards->Front = UNO_cards->Tail = 0;
        UNO_cards->arr[UNO_cards->Tail] = input;

    }
    else {
        UNO_cards->Tail = (++Tail) % Size;//to make it circular
        UNO_cards->arr[UNO_cards->Tail] = input;
    }

}


card Queue::dequeue(class Queue* UNO_cards)
{
    card Flag;
    Flag.value = -1;
    //condition for empty queue at first and while playing the remender in the queue is only one card
    if (((UNO_cards->Tail == UNO_cards->Front)) || UNO_cards->Tail == -1)
        return Flag;//means that we need to fill the queue with the cards in ground after random selecting
    else
    {

        Flag = UNO_cards->arr[UNO_cards->Front];//get the card that is on the top FIFO
        UNO_cards->Front = (++Front) % Size;//to make it circular and move the index front to the next card in queue
        return Flag;

    }

}


Queue Insert_to_Pulling_Cards(card my_cards_array[])//take array of cards then randomly rearrange it into queue
{
    Queue PULLING_CARDS;
    while (!emptycards(my_cards_array))//outer loop is to cheak the un used cards
    {
        for (int i = 0; i < Size; i++)//inner loop is for (1)&(2)
        {

            int random = Random_Values(0, Size - 1);//get random value to rearrange it randomly
            //(1) swapping the cards in array - which is the sortted original UNO -
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


void Hash::insertItem(card key)
{
    // get the hash index of key
    int index = hashFunction(key);
    // table[index] is an object of the linked list at the correct index
    //to insert from array of indicies
    table[index].push(&table[index].Head, key);
}

card Hash::Get_card_by_num(card key)
{
    card back;//the returned card
    back.value = -1;//initial unfound
    // get the hash index of key
    int index = hashFunction(key);
    if (table[index].Head)//if the required list is empty
    {
        back = key;
        return back;
    }
    return back;

}

// function to display hash table of my cards of UNO by numbers not colors
void Hash::displayHash() {

    for (int i = 0; i < BUCKET_num; i++) {

        table[i].display(table[i].Head);

    }
}


void Hash_color::insertItem(card key)
{
    // get the hash index of key
    int index = hashFunction(key);
    // table[index] is an object of the linked list at the correct index
    //to insert from array of indicies
    table[index].push(&table[index].Head, key);
}

card Hash_color::Get_card_by_color(card key)
{
    card back;//the returned card
    back.value = -1;//initial unfound
    // get the hash index of key
    int index = hashFunction(key);
    if (table[index].Head)//if the required list is empty
    {
        back = key;
        return back;
    }
    return back;
}

// function to display hash table of my cards of UNO by colors not number
void Hash_color::displayHash() {

    for (int i = 0; i < BUCKET_color; i++) {

        table[i].display(table[i].Head);
    }

}

void Hash::deletecard(card key)
{// get the hash index of key
    int index = hashFunction(key);
    if (table[index].Head)//if the required list is empty
    {
        table[index].delete_node(&table[index].Head, key);

    }
}
void Hash_color::deletecard(card key)
{
    int index = hashFunction(key);
    if (table[index].Head)//if the required list is empty
    {

        table[index].delete_node(&table[index].Head, key);

    }
}
card UNO::Construct_card_inout_of_player(Queue* pulling, Ground* UNO_Ground)
{
    int flag;
    cout << "\nPulling==>press '1' play a card ==>press '2'\n";
    cin >> flag;
    switch (flag)
    {
    case 1://card is pulled to both hashes
    {
        UNO_players[counter].get_Card(pulling->dequeue(pulling));
        break;
    }
    case 2:
    {
        card player_card,check;
        cout << "\n Enter your correspond Value for your card\n ";
        cin >> player_card.value;
        cin.ignore();
        cout << "\n Enter your correspond Color for your card\n ";
        cin >> player_card.Color;
        cin.ignore();
       int index= UNO_players[counter].UNO_Color.hashFunction(player_card);
       if (index==-1)
       {
           cout << "\aPlease enter a correct color or pull a card";
           Construct_card_inout_of_player( pulling, UNO_Ground);
       }
       else
       {
           //return the card after searching ==> -1 not found ||| !(-1) found
           check = UNO_players[counter].UNO_Color.table[index].search(UNO_players[counter].UNO_Color.table[index].Head, player_card);

           if (check.value == -1)//if the card is not in his deck 
           {
               cout << "\a\n Enter a correct card or pull a card\n";
               Construct_card_inout_of_player(pulling, UNO_Ground);
           }
           else
           {
               if (check.value==UNO_Ground->Ground_Cards[UNO_Ground->top-1].value|| check.Color == UNO_Ground->Ground_Cards[UNO_Ground->top-1].Color|| check.value==10|| check.value==11)
               {
                   UNO_Ground->Ground_Cards[UNO_Ground->top] = check;
                   UNO_Ground->top++;
                   UNO_players[counter].delete_Card(check);

               }
               else
               {
                   cout << "\a Enter correct card if exist in your deck if you have not matched card please pull a card ";
                   Construct_card_inout_of_player(pulling, UNO_Ground);
               }
           }

       }
        break;
    }
    default:
    {
        cout << "\a Enter correct number ";
        Construct_card_inout_of_player(pulling, UNO_Ground);
        break;
    }
    }
}

