
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include "ticket.h"

void initialize( TicketSystem *ticketsystem)
{
    ticketsystem->ticketcount=0;
    loadticketsfromfile(ticketsystem);
}


void booktickets(TicketSystem *ticketsystem)
{
    if(ticketsystem->ticketcount >= MAX_TICKET)
    {
        printf("Sorry No seats Available 🙏");
        return;
    }
    char name_tic[30];
    char phone_tic[15];
    char tktno[10];
    // char source_tic[30];
    // char destination_tic[30];
    //float fare;

    printf("\n==============================");
    printf("\n        Ticket Booking       ");
    printf("\n==============================\n");
    printf("Please Fill the Below Details For Booking..\n");
    is_namecheck(name_tic,ticketsystem);
    is_phonecheck(phone_tic,ticketsystem);
    int diff = select_source_destination(ticketsystem);
    get_fare(diff,ticketsystem);
    ticket_no(tktno , ticketsystem);
   ticket_no(tktno , ticketsystem);

// ✅ Save AFTER all fields are ready
ticketsystem->ticketcount++;
saveticketstofile(ticketsystem);

}
//name validation
void is_namecheck(char name_tic[],TicketSystem *ticketsystem)
{
    int valid;
    
    do
    {
        valid=1;// 1 true
        printf("Enter Your Name : ");
        scanf(" %[^\n]",name_tic);
        for(int i=0; name_tic[i]!='\0';i++)
        {
            if(!isalpha(name_tic[i]) && name_tic[i] != ' ')
            {
                valid=0;
                printf("Invalid name. Only letters and spaces are allowed.\n");
                break;
            }
        }
    } while (!valid);
    strcpy(ticketsystem->tickets[ticketsystem->ticketcount].name,name_tic);

}
//phone validation

void is_phonecheck(char *phone_tic, TicketSystem *ticketsystem)
{
    int valid;

    do {
        valid = 1; // Assume valid at the start
        printf("Enter Your Phone (10 digits): ");
        scanf(" %s", phone_tic);

        // Check if length is exactly 10
        if (strlen(phone_tic) != 10) {
            valid = 0;
            printf("Invalid phone number. It must be exactly 10 digits.\n");
            continue; // Ask for input again
        }

        // Check if all characters are digits
        for (int i = 0; i < 10; i++) {
            if (!isdigit(phone_tic[i])) {
                valid = 0;
                printf("Invalid phone number. Only digits are allowed.\n");
                break;
            }
        }
    } while (!valid);

    // If valid, copy to the ticket
    strcpy(ticketsystem->tickets[ticketsystem->ticketcount].phone, phone_tic);
}

int select_source_destination(TicketSystem * ticketsystem)
{
   FILE * srcdes =  fopen("stations.csv","r");
   if (srcdes == NULL)
   {
    printf("No stations available (missing stations.csv file)❎\n");
        return 1;
   }
   printf("\n📜Enter the Source and destination from the List \n");
   Station stations[50];//we can store 50 station of 30 char size..in the struct Station
   int count=0;
   while (fgets(stations[count].station, sizeof(stations[count].station), srcdes))
{
    // remove trailing newline from each station
    stations[count].station[strcspn(stations[count].station, "\r\n")] = '\0';
    count++;
}

   //int buffer[50];

   for(int i=0 ; i<count;i++)
   {
        printf("%d.  %s\n",i+1,stations[i].station);
        //buffer[i]=i+1;
   }
int src, des;
int y=1;
char choice;
while(y)
{
do
{
    printf("\nSelect your SOURCE station number: ");
    scanf("%d", &src);
} while (src<1 || src>count);
printf(" 📍You selected %s \n",(stations[src-1].station));

do
{
    printf("\nSelect your DESTINATION station number: ");
    scanf("%d", &des);
} while (des<1 || des>count || des == src);

printf(" 📍You selected %s\n",stations[des-1].station);
printf("\nCan i confirm your Stations (y/n): ");
scanf(" %c",&choice);
if(choice == 'n' || choice == 'N')
{
    y=1;//reask
}
else{
    y=0;
}


}
printf("\nStations confirmed..✅\n");
// strncpy(ticketsystem->tickets[ticketsystem->ticketcount].source,stations[src-1].station);
// strncpy(ticketsystem->tickets[ticketsystem->ticketcount].destination,stations[des-1].station);

strncpy(ticketsystem->tickets[ticketsystem->ticketcount].source, stations[src-1].station, 49);
ticketsystem->tickets[ticketsystem->ticketcount].source[49] = '\0';

strncpy(ticketsystem->tickets[ticketsystem->ticketcount].destination, stations[des-1].station, 49);
ticketsystem->tickets[ticketsystem->ticketcount].destination[49] = '\0';

return abs(src-des);

}
        
void get_fare(int diff, TicketSystem *ticketsystem)
{
    float base_fare=10;//base fare, for 1st 3 station = 10
    int extra_unit=(diff-1)/3;//exrta unit
    base_fare=base_fare+(extra_unit*10);//updated_fare;

    printf("Your fare for the trip is: ₹%.2f\n\n",base_fare);

     // Payment confirmation
    char choice;
    while(1)
    {
        printf("Do you want to pay and confirm your ticket? (y/n): ");
        scanf(" %c", &choice);
        if(choice == 'y' || choice == 'Y')
        {
            printf("Payment successful! ✅\n");
            ticketsystem->tickets[ticketsystem->ticketcount].fare = base_fare;
            break;
        }
        else if(choice == 'n' || choice == 'N')
        {
            printf("Ticket booking cancelled.\n");
            exit(0); // or return to main menu
        }
        else
        {
            printf("Invalid input! Please enter y or n.\n");
        }
    }

    
}

void ticket_no(char tktno[],TicketSystem * ticketsystem)
{
    FILE *tn = fopen("ticket_counter.txt","r");
    int ticket_count=1;// default if file doesn't exist
       if (tn != NULL) {
        fscanf(tn, "%d", &ticket_count);
        fclose(tn);
    }

    int next_ticket = ticket_count + 1;

    // Save the updated ticket number back to the file
    tn= fopen("ticket_counter.txt", "w");
    if (tn == NULL) {
        printf("Error opening counter file!\n");
        exit(1);
    }

    fprintf(tn, "%d", next_ticket);
      fclose(tn);

    sprintf(tktno,"TKT%03d",ticket_count);
    strcpy(ticketsystem->tickets[ticketsystem->ticketcount].ticketno,tktno);// storing to struct
    printf("\n      Your Ticket Number 👉: %s",tktno);
    printf("\n------------------------------------------------------\n");
    printf("\n....TICKET BOOKED SUCCESSFULLY ,ENJOY THE JOURNEY🙏....\n");
    printf("------------------------------------------------------\n");


}

void viewtickets(TicketSystem *ticketsystem)
{
        char str[20];
        printf("Enter your ticket number for View : ");
        scanf("%s",str); 

        FILE * fptr = fopen("tickets.csv","r");
        char ticnum[20],name[20],phone[20],source[30],destination[30];
        float fare;
        int found = 0;
        while(fscanf(fptr,"%19[^,],%19[^,],%19[^,],%29[^,],%29[^,],%f\n",ticnum,name,phone,source,destination,&fare)==6)
        {
             if(strcmp(ticnum,str)==0)
            {
                printf("\n============Ⓜ METRO TICKET Ⓜ==============\n");
                printf("      Tiket No      : %s\n",ticnum);
                printf("      Name          : %s\n",name);
                printf("      Phone         : %s\n",phone);
                printf("      Source        : %s\n",source);
                printf("      Destination   : %s\n",destination);
                printf("      Fare          : ₹%0.2f\n",fare);
                printf("........................................\n");
                printf("      ENJOY YOUR SAFE JOURNEY 🙏\n");
                printf("========================================\n");
                found=1;
                break;
            }
        }
        if(!found)
        {
            printf("❌ Ticket not found for number: %s\n", str);
        }
       
        fclose(fptr);
}


void cancelticket(TicketSystem *ticketsystem)
{
    
    char ch[20];
    printf("Ticket Number for cancellation : ");
    scanf("%s",ch);
    FILE *src = fopen("tickets.csv","r");
    FILE *tmp = fopen("temp.csv","w");

     if(src == NULL || tmp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char ticnum[20],name[20],phone[20],source[30],destination[30];
    float fare;
    int found=0;
    char choice;
    while(fscanf(src,"%19[^,],%19[^,],%19[^,],%29[^,],%29[^,],%f\n",ticnum,name,phone,source,destination,&fare)==6)
    {
        if(strcmp(ticnum,ch)==0)
        {
             printf("do you want to delete %s (y/n) : ",ch);
             scanf(" %c",&choice);
             if(choice == 'y' || choice == 'Y')
            {
              printf("\n✅ Ticket %s cancelled successfully.\n", ticnum);
              found=1;
              continue;
            }
            else{
                printf("Cancelation Failed.❌");
                found=1; 
            }
        
        }

        fprintf(tmp,"%s,%s,%s,%s,%s,%f\n",ticnum,name,phone,source,destination,fare);
    }


    fclose(src);
    fclose(tmp);
     // Replace original file with updated one
    remove("tickets.csv");
    rename("temp.csv", "tickets.csv");
    if(!found)
    {
        printf("❌ Ticket not found: %s\n", ch);
    }


}
void listalltickets(TicketSystem *ticketsystem)
{
    FILE *fptr = fopen("tickets.csv", "r");
    if (fptr == NULL)
    {
        printf("\n⚠️ No tickets found! File not available.\n");
        return;
    }

    char line[512];
    char ticketno[20], name[30], phone[15], source[100], destination[100];
    float fare;
    int count = 0;

    printf("\n================================================== ALL BOOKED TICKETS ==================================================\n");
    printf("%-10s %-20s %-15s %-25s %-25s %-10s\n",
           "Ticket No", "Name", "Phone", "Source", "Destination", "Fare (₹)");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fptr))
    {
        // Remove newline and carriage return (for Windows CSVs)
        line[strcspn(line, "\r\n")] = 0;

        // Parse the line safely
        if (sscanf(line, "%19[^,],%29[^,],%14[^,],%99[^,],%99[^,],%f",
                   ticketno, name, phone, source, destination, &fare) == 6)
        {
            printf("%-10s %-20s %-15s %-25s %-25s %-10.2f\n",
                   ticketno, name, phone, source, destination, fare);
            count++;
        }
    }

    if (count == 0)
        printf("No valid ticket records found.\n");

    printf("------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fptr);
}
