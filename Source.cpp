
#include <iostream>
#include <cstdlib>//for random values
#include <ctime>//for time count


using namespace std;


const int Size = 108;//number of cards in UNO

struct card //our card in UNO has Value & color
{
    int value;
    char Color;
};

bool emptycards(card[]);//to check if cards of UNO are all used means that it is empty

void Get_Cards_of_UNO(card[]);//generate cards of UNO

int Random_Values(int Start, int End);//get random value in specific range Start to End






//this Queue is representing the pulling cards
class Queue//Queue using Array with two indices   to O(1) of enqueue & dequeue
{

public:
    card arr[Size];//array that will include the unsorted cards after randomly rearrange
    int Front = -1;
    int Tail = -1;

    void enqueue(class Queue* , card);//to put cards in the queue
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

    PULLING_CARDS=Insert_to_Pulling_Cards(My_Cards);


    //to show conntent of pulling cards & array & another data
    for (int i = 0; i < Size; i++)
    {

        cout << PULLING_CARDS.dequeue(&PULLING_CARDS).value << "\t";
        cout << My_Cards[i].value << "             " << PULLING_CARDS.arr[PULLING_CARDS.Front].value
            << "\t" << PULLING_CARDS.arr[PULLING_CARDS.Front].Color <<
            "\t\tPULLING_CARDS.Front= " << PULLING_CARDS.Front << "\t\tPULLING_CARDS.Tail =" << PULLING_CARDS.Tail << endl;

    }
    
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


void Queue::enqueue(class Queue *UNO_cards, card input)
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
    if (((UNO_cards->Tail == UNO_cards->Front) ) || UNO_cards->Tail == -1)
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