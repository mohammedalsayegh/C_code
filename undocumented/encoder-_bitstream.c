// Name: Mohammed Al-Sayegh
// This program bitstream 2 bit parallel from a string as binary
// It store the result in struct for every byte

#include <stdio.h>
#include <stdlib.h>
//#include <wiringPi.h>

// The GPIO pins are 4 : enable - active high, 
// The GPIO pins are 17 : clock - latch on falling edge, 
// The GPIO pins are 18 : bit0 - least significant bit, 
// The GPIO pins are 22 : bit1 - most significant bit.

#define ENABLE 4
#define CLOCK 17
#define BIT0 18
#define BIT1 22

void bitstream_encoder(char num);

typedef struct node
{
    char data;
    struct node* next;
} node;

typedef void (*callback)(node* data);

/*
    create a new node
    initialize the data and next field

    return the newly created node
*/
node* create(char data,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;

    return new_node;
}

/*
    add a new node at the beginning of the list
*/
node* prepend(node* head,char data)
{
    node* new_node = create(data,head);
    head = new_node;
    return head;
}

/*
    traverse the linked list
*/
void traverse(node* head,callback f)
{
    node* cursor = head;

    while(cursor != NULL)
    {
        f(cursor);
        cursor = cursor->next;
    }
    //digitalWrite(ENABLE , LOW);
}

/*
    display a node
*/
void display(node* n)
{
    if(n != NULL) bitstream_encoder(n->data);
}

/*
    reverse the linked list
*/
node* reverse(node* head)
{
    node* prev    = NULL;
    node* current = head;
    node* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

void bitstream_encoder(char num)
{
    int i,g;
 
	/* perform bitwise AND for every bit of the character For BIT1 & BIT0 */
	for(i = 7; i >= 4; --i)
	{
		// setup the clock for bitstream
	    //delayMicroseconds(1);
		//digitalWrite(CLOCK, HIGH);

		if(num & 1 << i)
		{
		    //digitalWrite(BIT1 , HIGH);
		    printf("BIT1: 1 \n");
		}
		else
		{
		    //digitalWrite(BIT1 , LOW);
		    printf("BIT1: 0 \n");
		}
		
		g = i-4;
		
		if(num & 1 << g)
		{
		    //digitalWrite(BIT0 , HIGH);
		    printf("BIT0: 1 \n");
		}
		else
		{
		    //digitalWrite(BIT0 , LOW);
		    printf("BIT0: 0 \n");
		}

		//digitalWrite(CLOCK, LOW);
	}
}

int main(int argc, char *argv[])
{
    // if no input string exit
    if(argv[1] == NULL) return 0; 

    /* initialize the output pin's & Initalize Pi GPIO
    wiringPiSetupGpio();
	pinMode(ENABLE, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(BIT0, OUTPUT);
	pinMode(BIT1, OUTPUT);

	// setup the Enable high to bit stream
    digitalWrite(ENABLE , HIGH);

    */ 
    //setup the struct of the list of the bit-stream
    //int command = 0;
    //int data;
    node* head = NULL;
    //node* tmp = NULL;
    callback disp = display;
    
    // initialize a pointer for the 1st argument
    char *ptr = argv[1];

    // loop to the end of the 1st argument size
    for(; *ptr != 0; ++ptr) head = prepend(head,*ptr);

	// reverse the sequence of the bytes
    head = reverse(head);
	
	// loop through revese bytes sequence list and output to pin's 
    traverse(head,disp);

    return EXIT_SUCCESS;
}