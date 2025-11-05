
#include<stdio.h>
#include "ticket.h"

int main()
{
    int choice;
     
    TicketSystem ticketsystem;
    initialize(&ticketsystem);
    do
    {
        /* code */
        printf("\n----------------------------------------\n");
        printf("==== Metro Ticket Booking System ====\n");
        printf("    ...🌴..Entey Metro..🌴...\n");
        printf("----------------------------------------\n");
        printf("1. Book Ticket\n2. View Tickets\n3. Cancel Ticket\n4. List All Tickets\n5. Exit\n");
        printf("----------------------------------\n");
        printf("Enter Your Choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            booktickets(&ticketsystem);
            break; 

            case 2:
            viewtickets(&ticketsystem);
            break;

            case 3:
            cancelticket(&ticketsystem);
            break;

            case 4:
            listalltickets(&ticketsystem);
            break;

            case 5:
            printf("Exiting Successfully...✅\n");
            break; 

            default:
            printf("Invalid Choice, Try Again ❌");
        }
    } while (choice !=5);
    
}
