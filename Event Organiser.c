#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#define max_events 15

 struct event{
  char a;
  char ename[30];
  char date[20];
  int time[2];
  int venue;
  int eventtype;
  int mic;
  int lamp;
  int PODIUM;
  char contactno[20];
  
  
  
 };
struct event all[max_events];
int i;

int eventexist(char d[],int t[],int v){
  for(i=0;i<max_events;i++){
    if((strcmp(all[i].date, d) == 0)&&all[i].venue==v&&all[i].a=='1'){
     if(t[0]<= all[i].time[1] && t[1] >= all[i].time[0]){
      printf("\nVenue Already Booked..Choose other venue\n");
      return 0;}
      }
    }
  return 1;
  }
  
int eventdetailsmic(char d[],int t[]){
 for(i=0;i<max_events;i++){
    if((strcmp(all[i].date, d) == 0)&&all[i].mic==1&&all[i].a=='1'){
     if(t[0]<= all[i].time[1] && t[1] >= all[i].time[0]){
     printf("\nMic Unavailable");
        return 0;}
      
      }}
      printf("\nMic Available");
      return 1;
      
  
}
int eventdetailslamp(char d[],int t[]){
 for(i=0;i<max_events;i++){
    if((strcmp(all[i].date, d) == 0)&&all[i].lamp==1&&all[i].a=='1'){
     if(t[0]<= all[i].time[1]  && t[1] >= all[i].time[0]){
     printf("\nLamp Unavailable");
        return 0;}
      
      }}
      printf("\nLamp Available");
      return 1;
      
  
}
int eventdetailspodium(char d[],int t[]){
 for(i=0;i<max_events;i++){
    if((strcmp(all[i].date, d) == 0)&&all[i].PODIUM==1&&all[i].a=='1'){
     if(t[0]<= all[i].time[1] &&t[1] >= all[i].time[0]){
     printf("\nPODIUM Unavailable");
        return 0;}
      
      }}
      printf("\nPODIUM Available");
      return 1;
      
  
}

void bookeventfinal(int eventtype, int t[], int v, char d[], int M, int L, int P) {
    FILE* outfile;
    char name[30], contactnum[20];
    int f = 0;
    

    printf("\nPLEASE ENTER EVENT NAME:\n");
    scanf("%s", name);
    
    printf("PLEASE ENTER CONTACT NUMBER:\n");
    scanf("%s", contactnum);

    for (i = 0; i < max_events; i++) {
        if (all[i].a == '0') {
            all[i].a = '1';
            all[i].eventtype = eventtype;
            all[i].time[0] = t[0];
            all[i].time[1] = t[1];
            all[i].venue = v;
            strcpy(all[i].date, d);
            all[i].mic = M;
            all[i].lamp = L;
            all[i].PODIUM = P;
            strcpy(all[i].contactno, contactnum);
            strcpy(all[i].ename, name);

            outfile = fopen("eo.txt", "a");

            if (outfile == NULL) {
                fprintf(stderr, "\nError opened file\n");
                return;
            }

            
            fwrite(&all[i], sizeof(struct event), 1, outfile);

            fclose(outfile);

            f = 1;
            
            break;
        }
    }

    if (f == 1) {
        printf("\nEVENT BOOKED SUCCESSFULLY!!\n");
    }
}



void Deleteevent(char name[],int v){
	 int f = 0;
    FILE *infile, *outfile;
    struct event temp_event;

    infile = fopen("eo.txt", "r");
    if (infile == NULL) {
        fprintf(stderr, "\nError opening file for reading\n");
        return;
    }

    outfile = fopen("temp.txt", "w");
    if (outfile == NULL) {
        fprintf(stderr, "\nError opening file for writing\n");
        fclose(infile);
        return;
    }

    while (fread(&temp_event, sizeof(struct event), 1, infile)) {
        if (!(strcmp(temp_event.ename, name) == 0 && temp_event.venue == v && temp_event.a == '1')) {
            fwrite(&temp_event, sizeof(struct event), 1, outfile);
        } else {
            f = 1;
        }
    }

    fclose(infile);
    fclose(outfile);

    if (f == 1) {
        printf("\nEVENT DELETED SUCCESSFULLY\n");
        remove("eo.txt");
        rename("temp.txt", "eo.txt");
    } else {
        printf("Event not found");
        remove("temp.txt");
    }
}



void Displayevent(){
	 FILE *file = fopen("eo.txt", "r");
	 int c;
	 int flag=0;
    
    if (file == NULL) {
        printf("Unable to open file for reading\n");
        return;
    }
    
    struct event temp_event;
    printf("Enter choice :\n1.Display Events by Date\n2.Display Upcoming Events\n3.Display Events by Month\n");
    scanf("%d",&c);
    if(c==1){
	char d[20];
    printf("PLEASE ENTER EVENT DATE in dd-mm-yy format\n");
    scanf("%s",d);
  
    while (fread(&temp_event, sizeof(struct event), 1, file)) {
    	if (temp_event.a == '1' && strcmp(temp_event.date, d) == 0) {
    	flag=1;
        printf("Event Name: %s\n", temp_event.ename);
        printf("Event Date: %s\n", temp_event.date);
        printf("Start Time: %d\n", temp_event.time[0]);
        printf("End Time: %d\n", temp_event.time[1]);
        char k[20];
      if(temp_event.venue==1)strcpy(k,"Amphi theatre");
      else if(temp_event.venue==2)strcpy(k,"Conference hall 1");
      else if(temp_event.venue==3)strcpy(k,"Conference hall 2");
      else if(temp_event.venue==4)strcpy(k,"Conference hall 3");
      else if(temp_event.venue==5)strcpy(k,"Lab");
      else if(temp_event.venue==6)strcpy(k,"Library");
      printf("Venue : %s\n",k);
      printf((temp_event.eventtype==1)?"Eventtype: Test\n": "Eventtype: Ceremony\n");
      printf((temp_event.mic==1)?"Mic: Booked\n":"Mic :Hasn't been Booked\n");
      printf((temp_event.lamp==1)?"Lamp: Booked\n":"Lamp :Hasn't been Booked\n");
      printf((temp_event.PODIUM==1)?"Podium: Booked\n":"Podium :Hasn't been Booked\n");
      printf("Contact no: %s\n", temp_event.contactno); 
        
        printf("\n");
    }}
    rewind(file);
	}
    if(c==2){
    	int f=0;char d[20];
    g:printf("PLEASE ENTER Today's DATE in dd-mm-yy format\n");
    scanf("%s",d);
   // if(isValidDate(d)==0){
	//printf("ENTER VALID DATE\n");goto g;}
	int day, month, year;
    sscanf(d, "%d-%d-%d", &day, &month, &year);
	int checkupcoming(char s[],int day,int month,int year){
			int cday, cmonth, cyear;
    sscanf(s, "%d-%d-%d", &cday, &cmonth, &cyear);
    if(month<cmonth||year<cyear)return 1;
    if(month==cmonth&&cday>day)return 1;
    return 0;
	}
	
	
   	while (fread(&temp_event, sizeof(struct event), 1, file)) {
    	   if (temp_event.a == '1' && checkupcoming(temp_event.date,day,month,year)==1 ){
    	   	flag=1;
        printf("Event Name: %s\n", temp_event.ename);
        printf("Event Date: %s\n", temp_event.date);
        printf("Start Time: %d\n", temp_event.time[0]);
        printf("End Time: %d\n", temp_event.time[1]);
         char k[20];
      if(temp_event.venue==1)strcpy(k,"Amphi theatre");
      else if(temp_event.venue==2)strcpy(k,"Conference hall 1");
      else if(temp_event.venue==3)strcpy(k,"Conference hall 2");
      else if(temp_event.venue==4)strcpy(k,"Conference hall 3");
      else if(temp_event.venue==5)strcpy(k,"Lab");
      else if(temp_event.venue==6)strcpy(k,"Library");
      printf("Venue : %s\n",k);
      printf((temp_event.eventtype==1)?"Eventtype: Test\n": "Eventtype: Ceremony\n");
      printf((temp_event.mic==1)?"Mic: Booked\n":"Mic :Hasn't been Booked\n");
      printf((temp_event.lamp==1)?"Lamp: Booked\n":"Lamp :Hasn't been Booked\n");
      printf((temp_event.PODIUM==1)?"Podium: Booked\n":"Podium :Hasn't been Booked\n");
      printf("Contact no: %s\n", temp_event.contactno); 
      printf("\n");
    }}
	rewind(file);}
    if(c==3){int m;
    printf("Please Enter Month:\n");
    scanf("%d",&m);
    int monthsep(char s[],int m){
    	int mday,mmonth,myear;
    	sscanf(s,"%d-%d-%d",&mday,&mmonth,&myear);
    	if(mmonth==m)return 1;
		return 0;
	}
    while (fread(&temp_event, sizeof(struct event), 1, file)) {
    
    	   if (temp_event.a == '1' && monthsep(temp_event.date,m)==1 ){
    	   	flag=1;
    	   	
        printf("Event Name: %s\n", temp_event.ename);
        printf("Event Date: %s\n", temp_event.date);
        printf("Start Time: %d\n", temp_event.time[0]);
        printf("End Time: %d\n", temp_event.time[1]);
        char k[20];
      if(temp_event.venue==1)strcpy(k,"Amphi theatre");
      else if(temp_event.venue==2)strcpy(k,"Conference hall 1");
      else if(temp_event.venue==3)strcpy(k,"Conference hall 2");
      else if(temp_event.venue==4)strcpy(k,"Conference hall 3");
      else if(temp_event.venue==5)strcpy(k,"Lab");
      else if(temp_event.venue==6)strcpy(k,"Library");
    printf("Venue : %s\n",k);
       
        printf((temp_event.eventtype==1)?"Eventtype: Test\n": "Eventtype: Ceremony\n");
        printf((temp_event.mic==1)?"Mic: Booked\n":"Mic :Hasn't been Booked\n");
        printf((temp_event.lamp==1)?"Lamp: Booked\n":"Lamp :Hasn't been Booked\n");
        printf((temp_event.PODIUM==1)?"Podium: Booked\n":"Podium :Hasn't been Booked\n");
        printf("Contact no: %s\n", temp_event.contactno);

        printf("\n");
    }}
    rewind(file);
	}
	
    fclose(file);
    if(flag==0)printf("No EVENTS BOOKED");}
  
 
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(char date[]) {
    int day, month, year;
    sscanf(date, "%d-%d-%d", &day, &month, &year);

    if (month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year)) {
        daysInMonth[2] = 29;
    }

    return (day <= daysInMonth[month]);
}



void Bookevent(){
  int eventtype,M,L,P,final;
  printf("CHOOSE Number of EVENT TYPE\n1.TEST/DRIVE\n2.CEREMONY/FUNCTION\n");
  scanf("%d",&eventtype);
  printf("ENTER DATE in dd-mm-yy format:\n");
  char d[20];int v,t[2],flag=0;
  scanf("%s",d);
    s:
    if (isValidDate(d)) {
        flag=1;
    } else {
        printf("The entered date is invalid.\n");
        printf("ENTER DATE in dd-mm-yy format:\n");
        scanf("%s",d);
        goto s;
    }
    if(flag==1){
  printf("ENTER STARTING & ENDING TIME (24 hr format) in HHMM-HHMM format:\n");
  scanf("%d-%d",&t[0],&t[1]);
  b:
  printf("Enter Venue Number\n1.Amphi Theatre    \tCapacity: 200\n2.Conference hall 1\tCapacity: 100\n3.Conference hall 2\tCapacity: 200\n4.Conference hall 3\tCapacity: 100\n5.Lab                \tCapacity: 80\n6.Library\t  \tCapacity: 200\n");
  scanf("%d",&v);
  if(eventexist(d,t,v)==0||(eventtype==1&&v==1)||(eventtype==2&&v==6)||(eventtype==2&&v==5)){printf("\nPLEASE CHANGE VENUE\n");goto b;}
  printf("\nDO YOU REQUIRE SOUND SYSTEM?\npress '1' if yes, else '0'\n");
  scanf("%d",&M);
  if(M==1)M=eventdetailsmic(d,t);
  printf("\nDO YOU REQUIRE LAMP?\npress '1' if yes, else '0'\n");
  scanf("%d",&L);
  if(L==1)L=eventdetailslamp(d,t);
  printf("\nDO YOU REQUIRE PODIUM?\npress '1' if yes, else '0'\n");
  scanf("%d",&P);
  if(P==1)P=eventdetailspodium(d,t);
  printf("\nSHALL WE BOOK THE EVENT(Enter no) ?\n1.BOOK IT\n2.NO!CANCEL\n");
  scanf("%d",&final);
  if (final==1)bookeventfinal(eventtype,t,v,d,M,L,P);
  else printf("EVENT CANCELLED ...\n");
  return ;
}
  
}


int main(){
   for(i=0;i<max_events;i++){
    all[i].a='0';
}
  int choice;
  while(1){
    printf("\n********************************************* WELCOME TO EVENT ORGANIZER *********************************************\n");
    printf("KINDLY CHOOSE YOUR PURPOSE(ONLY ENTER THE NUMBER OF CHOICE)\n");
    printf("1.BOOK EVENT\n2.DELETE EVENT\n3.DISPLAY EVENTS\n4.EXIT\n");
    scanf("%d",&choice);
    if (choice==1)Bookevent();
    else if(choice==2){char name[30];int v;printf("ENTER EVENT NAME:\n");
      scanf("%s",name);
	  printf("Enter Venue Number\n1.Amphi Theatre    \tCapacity: 200\n2.Conference hall 1\tCapacity: 100\n3.Conference hall 2\tCapacity: 200\n4.Conference hall 3\tCapacity: 100\n5.Lab                \tCapacity: 80\n6.Library\t  \tCapacity: 200\n");
      scanf("%d",&v);
      Deleteevent(name,v);}
    else if(choice==3){
    Displayevent();}
    else if(choice==4)return 0;
    else printf("\nEnter valid option");
  }
}
