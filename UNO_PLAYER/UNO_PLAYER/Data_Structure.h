#pragma once
//constant variable definition
const int BUCKET_num = 15; // No. of buckets for numbers & special cards in UNO
const int MAX_NUM_OF_PLAYERS = 10;//maximum number of players in UNO game
const int BUCKET_color = 4; // No. of buckets for  'R' 'G' 'B' 'Y'  Colors
const int Size = 108;//No. of UNO cards


//our card in UNO has Value & color
struct card
{
    int value;
    char Color;
};

//class that include the all cards played on the ground and pointer to empty card

struct Ground {
    card Ground_Cards[Size];//array that include the all cards played on the ground

    int top = 0;//pointer to empty ground card
};


//-------------------------------------------------start of linked list-----------------------------------------------------------


//nodes of linked list
struct node {
    card item;
    node* next;
};
// linked list of cards
class linked_list {
public:
    int legnth ;
    node* Head ;
    //default constractor
    linked_list();
    //insert new node in the first of the linked list O(1)

    void push(node** Head_REF/*ADDRESS OF THE HEAD*/, card element);



    card search(node* head, card x);



    // as we define the list from the hash table to have matched type of data -cards-
    //so we will delete first node only -if exist- every time
    void delete_node(node** head_ref /*ADDRESS OF THE HEAD*/, card key);

    // display all nodes of the list

    void display(node* curr/*Head*/);


};


//-------------------------------------------------end of linked list-----------------------------------------------------------



//-------------------------------------------------start of Queue -----------------------------------------------------------

//this Queue is representing the pulling cards
class Queue//Queue using Array with two indices   to O(1) of enqueue & dequeue
{

public:
    card arr[Size];//array that will include the unsorted cards after randomly rearrange
    int Front;
    int Tail;
    Queue();
    void enqueue(class Queue*, card);//to put cards in the queue
    card dequeue(class Queue*);//to get cards from queue

};
//-------------------------------------------------end of Queue -----------------------------------------------------------



//-------------------------------------------------start of Hash_color -----------------------------------------------------------

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
    int hashFunction(card my_card);


    void displayHash();
    bool Hash_color_is_empty();

};

//-------------------------------------------------end of Hash_color -----------------------------------------------------------




//-------------------------------------------------start of Hash -------------------------------------------------------------

//Hash table of numbers & special cards in UNO
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
    int hashFunction(card my_card);


    void displayHash();
};

//-------------------------------------------------end of Hash -----------------------------------------------------------


//-------------------------------------------------start of Player  -----------------------------------------------------------


class Player
{
public:
    Hash UNO_Numbers;
    Hash_color UNO_Color;

    void get_Card(card);//put the card into UNO_Numbers & UNO_Color both

    void Give_player_7cards(Queue*);// give 7 cards for #one player

    bool check_on_Ground_Top_and_play(card, Ground*);//CHECK IF CARD WAS FOUND PALY IT AND
    //DELETE FROM TWO HASHES IF NOT PLAY UNTILL GET CASE FROM FUNCTION  Search_to_play

    void Search_to_play(Ground*, Queue*);//continue until go to next player

    void delete_Card(card);//delete the card from UNO_Numbers & UNO_Color both
    void Play_by_color_due_to_wild(card, Queue*, Ground*, card);


};
//-------------------------------------------------end of Player  -----------------------------------------------------------



//-------------------------------------------------start of UNO_Driver  -----------------------------------------------------------

class UNO
{
public:
    bool flag_rev;// true ==> counter clock wise ------false==>clock wise  change if revers card played
    int  counter;// to get the player who will play
    int Number_of_computer_players;//must deal with it in all functions depend on  number of players
    //default constructor
    UNO();


    Player UNO_players[MAX_NUM_OF_PLAYERS];// array of max players
    void Create_PCs_players(Queue*);//create players and give them 7 cards
    void GET_Number_of_PCs();//create 'n' playersn--> number of players
    void Check_Ground_Top_and_Play(Queue*, Ground*);
    void REVERS_CARD_set_flag(card);
    //void player_card_into_Ground(Queue* , Ground*);
    void Set_color_of_ground(card*);

    void SET_COUNTER();
    void SET_Ground_first_card(Queue*, Ground*);

    void play_after(Queue*, Ground*);

    void wild_play_after(Queue*, Ground*, card);
    void Construct_card_input_of_player(Queue*, Ground* UNO_Ground);
    void human_player_after_wild(Queue*, Ground*, card);


    bool Game_finished();
    void desplay_cards();
    void previous_counter();
};

//-------------------------------------------------end of UNO_Driver  -----------------------------------------------------------
