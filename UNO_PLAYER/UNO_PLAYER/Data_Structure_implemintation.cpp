#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count
#include <string.h>//to get an integer value with my function  "Take_only_and_only_integer"
#include <cmath>
#include"Data_Structure.h"
#include "my_functions.h"
using namespace std;





//-------------------------------------------------start of linked list-----------------------------------------------------------

//default constractor
linked_list::linked_list()
{
    legnth = 0;
    Head = NULL;
}

void linked_list::delete_node(node** head_ref /*ADDRESS OF THE HEAD*/, card key)
{
    node* temp6 = *head_ref;
    node* prev = NULL;
    if (temp6 != NULL)
    {
        if (temp6->item.value == key.value)
        {
            if (temp6->item.Color == key.Color)
            {
                (*head_ref) = (*head_ref)->next;
                delete temp6;
                legnth--;
                return;
            }

        }
    }

    while (temp6 != NULL && !(temp6->item.value == key.value && temp6->item.Color == key.Color))
    {
        prev = temp6;
        temp6 = temp6->next;
    }
    if (temp6 == NULL)
    {
        cout << "\x1B[31m\n card is not found \n\033[0m" << endl;
        return;
    }
    else {
        prev->next = temp6->next;
        delete temp6;
        legnth--;
    }
}

// display all nodes of the list
void linked_list::display(node* curr/*Head*/)
{
    while (curr)
    {

        //cout << "[ " <<get_card_name(curr->item.value)<<curr->item.value << "" << get_card_COLOR(curr->item.Color) << " ]\t";
        display_card(curr->item);
        cout << "\n\n";
        curr = curr->next;
    }
}

card linked_list::search(node* head, card x)
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

//insert new node in the first of the linked list O(1)
void  linked_list::push(node** Head_REF/*ADDRESS OF THE HEAD*/, card element)
{
    node* newnode = new node;
    newnode->item = element;
    //the above 2 lines are creating the new node in the list
    newnode->next = *Head_REF;
    *Head_REF = newnode;
    legnth++;
}


//-------------------------------------------------end of linked list-----------------------------------------------------------




//-------------------------------------------------start of Queue -----------------------------------------------------------

//default constractor
Queue::Queue()
{
    Front = -1;
    Tail = -1;
}


void Queue::enqueue(class Queue* UNO_cards, card input)
{
    if (input.value == -1)//means that the card is empty as we define -1 to be empty so take another value
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
    //condition for empty queue at first and while playing the reminder in the queue is only one card
    if (((UNO_cards->Tail == UNO_cards->Front)) || UNO_cards->Tail == -1)
        return Flag;//means that we need to fill the queue with the cards in ground after random selecting
    else
    {

        Flag = UNO_cards->arr[UNO_cards->Front];//get the card that is on the top FIFO
        UNO_cards->Front = (++Front) % Size;//to make it circular and move the index front to the next card in queue
        return Flag;

    }

}

//-------------------------------------------------end of Queue -----------------------------------------------------------


//-------------------------------------------------start of Hash_color -----------------------------------------------------------

// hash function to map colors to key
int Hash_color::hashFunction(card my_card)
{
    int i = -1;
    switch (my_card.Color)
    {
    case 'R':
    {i = 0;
    break; }
    case 'G':
    { i = 1;
    break;
    }
    case 'B':
    { i = 2;
    break;
    }
    case 'Y':
    {  i = 3;
    break;
    }

    }
    return i;

}

bool Hash_color::Hash_color_is_empty()
{
    if (table[0].Head || table[1].Head || table[2].Head || table[3].Head)
    {
        return false;
    }
    else
    {
        return true;
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
    back.value = -1;//initial unfounded
    // get the hash index of key
    int index = hashFunction(key);
    if (table[index].Head)//if the required list is empty
    {
        back = table[index].Head->item;
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

//-------------------------------------------------end of Hash_color -----------------------------------------------------------


//-------------------------------------------------start of Hash -----------------------------------------------------------

// hash function to map values to key
int Hash::hashFunction(card my_card) {
    return (my_card.value % BUCKET_num);
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
    back.value = -1;//initial unfounded
    // get the hash index of key
    int index = hashFunction(key);
    if (table[index].Head)//if the required list is empty
    {
        back = table[index].Head->item;
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




void Hash::deletecard(card key)
{// get the hash index of key
    int index = hashFunction(key);
    if (table[index].Head)//if the required list is empty
    {
        table[index].delete_node(&table[index].Head, key);

    }
}

//-------------------------------------------------end of Hash -----------------------------------------------------------

