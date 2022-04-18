#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count


using namespace std;

const int BUCKET_num = 15; // No. of buckets for numbers & spicitial cards in UNO

const int BUCKET_color = 4; // No. of buckets for  'R' 'G' 'B' 'Y'  Colors

const int Size = 108;//No. of UNO cards

struct card //our card in UNO has Value & color
{
    int value;
    char Color;
};
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



    // as we define the list from the hash table to have consistant type of data -cards-
    //so we will delete first node only -if exist- every time
    void delete_node(node** head_ref /*ADDRESS OF THE HEAD*/, card key)
    {
        node* temp = *head_ref;//temp for the pointer Head

        if ((*head_ref) != NULL)
        {
            (*head_ref) = (*head_ref)->next;
            delete temp;
            legnth--;
        }
        else {
            cout << "\n this card is not exist\n";
        }

    }
    // display all nodes of the list
    void display(node* curr/*Head*/)
    {
        bool flag = true;
        while (curr)
        {
            cout << curr->item.Color << "\t" << curr->item.value << "\n";
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


    // Array of linked lists to form the hash table with chaining resolving collision
    linked_list table[BUCKET_color];

public:

    // inserts a key into hash table
    void insertItem(card my_card);

    // deletes a key from hash table
    void deleteItem(card key);

    // hash function to map colors to key
    int hashFunction(card my_card)
    {
        switch (my_card.Color)
        {
        case 'R':
            return 0;
        case 'G':
            return 1;
        case 'B':
            return 2;
        case 'Y':
            return 3;
        default:
            break;
        }

    }

    void displayHash();
};

//Hash table of numbers & spicitial cards in UNO
class Hash
{


    // Array of linked lists to form the hash table with chaining resolving collision
    linked_list table[BUCKET_num];

public:

    // inserts a key into hash table
    void insertItem(card my_card);

    // deletes a key from hash table
    void deleteItem(card key);

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
    Hash UNO_Numbers;
    Hash_color UNO_Color;

public:
    //put the card into UNO_Numbers & UNO_Color both
    void get_Card(card);




};
void Player::get_Card(card input)
{
    UNO_Numbers.insertItem(input);
    UNO_Color.insertItem(input);
}
class special_cards
{
public:
    card Draw_Two;
    card Wild_Draw_Four;
   
};

//this Queue is representing the pulling cards
class Queue//Queue using Array with two indices   to O(1) of enqueue & dequeue
{

public:
    card arr[Size];//array that will include the unsorted cards after randomly rearrange
    int Front = -1;
    int Tail = -1;

    void enqueue(class Queue*, card);//to put cards in the queue
    card dequeue(class Queue*);//to get cards from queue

};
Queue Insert_to_Pulling_Cards(card[]);

int main()
{

    card My_Cards[Size];//array that include the all cards before rearrange it randomly

    card Ground_Cards[Size];//array that include the all cards played on the ground

    Get_Cards_of_UNO(My_Cards);// to load the UNO CARDS

    srand(time(0));//to make the game different in each run time

    Queue PULLING_CARDS;//define the cards that will be distributed on players

    PULLING_CARDS = Insert_to_Pulling_Cards(My_Cards);

    Hash amir;
    for (int i = 0; i < Size; i++)
    {
        amir.insertItem(PULLING_CARDS.dequeue(&PULLING_CARDS));

    }
    amir.displayHash();





    //to show conntent of pulling cards & array & another data
   /* for (int i = 0; i < Size; i++)
    {

        cout << PULLING_CARDS.dequeue(&PULLING_CARDS).value << "\t";
        cout << My_Cards[i].value << "             " << PULLING_CARDS.arr[PULLING_CARDS.Front].value
            << "\t" << PULLING_CARDS.arr[PULLING_CARDS.Front].Color <<
            "\t\tPULLING_CARDS.Front= " << PULLING_CARDS.Front << "\t\tPULLING_CARDS.Tail =" << PULLING_CARDS.Tail << endl;

    }*/
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

void Hash::deleteItem(card key)
{
    // get the hash index of key
    int index = hashFunction(key);

    table[index].delete_node(&table[index].Head, key);
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

void Hash_color::deleteItem(card key)
{
    // get the hash index of key
    int index = hashFunction(key);

    table[index].delete_node(&table[index].Head, key);
}

// function to display hash table of my cards of UNO by colors not number
void Hash_color::displayHash() {

    for (int i = 0; i < BUCKET_color; i++) {

        table[i].display(table[i].Head);
    }

}
