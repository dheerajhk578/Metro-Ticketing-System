
//Contains definitions and declarations used by multiple source files.
#ifndef TICKET_H
#define TICKET_H



#define MAX_TICKET  100

typedef struct 
{
    char station[100];
}Station;

typedef struct 
{
    /* data */
    char ticketno[20];      // new field for ticket number
    char name[30];
    char phone[15];
    char source[100];
    char destination[100];
    float fare;
}Ticket;

typedef struct 
{
    /* data */
    Ticket tickets[MAX_TICKET];
    int ticketcount;
}TicketSystem;

void initialize(TicketSystem * ticketsystem);
void loadticketsfromfile(TicketSystem * ticketsystem);
void saveticketstofile(TicketSystem *ticketsystem);
//operation
void booktickets(TicketSystem *ticketsystem);
void viewtickets(TicketSystem *ticketsystem);
void cancelticket(TicketSystem *ticketsystem);
void listalltickets(TicketSystem *ticketsystem);

//sub functions for book ticket
void is_namecheck(char * name_tic,TicketSystem * ticketsystem);
void is_phonecheck(char * phone_tic,TicketSystem * ticketsystem);
int select_source_destination(TicketSystem * ticketsystem);
void get_fare(int diff, TicketSystem *ticketsystem);
void ticket_no(char tktno[],TicketSystem * ticketsystem);


#endif
