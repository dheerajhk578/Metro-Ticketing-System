
#include<stdio.h>
#include "ticket.h"
void saveticketstofile(TicketSystem *ticketsystem)
{
    FILE *fp = fopen("tickets.csv", "a");
    if (fp == NULL)
    {
        printf("Error: Could not open tickets.csv for writing.\n");
        return;
    }

    int index = ticketsystem->ticketcount - 1;

    fprintf(fp, "%s,%s,%s,%s,%s,%.2f\n",
            ticketsystem->tickets[index].ticketno,
            ticketsystem->tickets[index].name,
            ticketsystem->tickets[index].phone,
            ticketsystem->tickets[index].source,
            ticketsystem->tickets[index].destination,
            ticketsystem->tickets[index].fare);

    fclose(fp);
}



void loadticketsfromfile(TicketSystem  *ticketsystem)
{
    FILE * fp = fopen("tickets.csv","r");
    if(fp == NULL)
    {
        return ;
    }
    while(fscanf(fp,"%19[^,],%29[^,],%14[^,],%29[^,],%29[^,],%f\n",
         ticketsystem->tickets[ticketsystem->ticketcount].ticketno,
         ticketsystem->tickets[ticketsystem->ticketcount].name,
         ticketsystem->tickets[ticketsystem->ticketcount].phone,
         ticketsystem->tickets[ticketsystem->ticketcount].source,
         ticketsystem->tickets[ticketsystem->ticketcount].destination,
         &ticketsystem->tickets[ticketsystem->ticketcount].fare)==5)
    {
         ticketsystem->ticketcount++;
    }

    fclose(fp);
}
