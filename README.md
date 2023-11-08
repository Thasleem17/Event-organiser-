# Event-organiser-
#Event organiser helps in managing multiple events at same date and time at different venues at a college or an institution without any time or venue,sound system clash ..

#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#define max_events 15

struct event
{
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




int
eventexist (char d[], int t[], int v)
{
  for (int i = 0; i < max_events; i++)
    {
      if ((strcmp (all[i].date, d) == 0) && all[i].venue == v
	  && all[i].a == '1')
	{
	  if (t[0] <= all[i].time[1] && t[1] >= all[i].time[0])
	    {
	      printf ("\nVenue Already Booked..Choose other venue\n");
	      return 0;
	    }
	}
    }
  return 1;
}

int
eventdetailsmic (char d[], int t[])
{

  for (int i = 0; i < max_events; i++)
    {
      if ((strcmp (all[i].date, d) == 0) && all[i].mic == 1
	  && all[i].a == '1')
	{
	  if (t[0] <= all[i].time[1] && t[1] >= all[i].time[0])
	    {
	      printf ("\nMic Unavailable");
	      return 0;
	    }

	}
    }
  printf ("\nMic Available");
  return 1;


}

int
eventdetailslamp (char d[], int t[])
{
  for (int i = 0; i < max_events; i++)
    {
      if ((strcmp (all[i].date, d) == 0) && all[i].lamp == 1
	  && all[i].a == '1')
	{
	  if (t[0] <= all[i].time[1] && t[1] >= all[i].time[0])
	    {
	      printf ("\nLamp Unavailable");
	      return 0;
	    }

	}
    }
  printf ("\nLamp Available");
  return 1;


}

int
eventdetailspodium (char d[], int t[])
{
  for (int i = 0; i < max_events; i++)
    {
      if ((strcmp (all[i].date, d) == 0) && all[i].PODIUM == 1
	  && all[i].a == '1')
	{
	  if (t[0] <= all[i].time[1] && t[1] >= all[i].time[0])
	    {
	      printf ("\nPODIUM Unavailable");
	      return 0;
	    }

	}
    }
  printf ("\nPODIUM Available");
  return 1;


}

void
bookeventfinal (int eventtype, int t[], int v, char d[], int M, int L, int P)
{
  char name[30], contactnum[20];
  int flag = 0;
  printf ("\nPLEASE ENTER EVENT NAME:\n");
  scanf ("%s", name);
  printf ("PLEASE ENTER CONTACT NUMBER:\n");
  scanf ("%s", contactnum);
  for (int i = 0; i < max_events; i++)
    {
      if (all[i].a == '0')
	{
	  all[i].a = '1';
	  all[i].eventtype = eventtype;
	  all[i].time[0] = t[0];
	  all[i].time[1] = t[1];
	  all[i].venue = v;
	  strcpy (all[i].date, d);
	  all[i].mic = M;
	  all[i].lamp = L;
	  all[i].PODIUM = P;
	  strcpy (all[i].contactno, contactnum);
	  strcpy (all[i].ename, name);
	  flag = 1;
	  break;
	}
    }
  if (flag == 1)
    printf ("\nEVENT BOOKED SUCCESSFULLY!!\n");
  return;



}

void
Deleteevent (char name[], int v)
{
  for (int i = 0; i < max_events; i++)
    {
      if (strcmp (all[i].ename, name) == 0 && all[i].venue == v)
	{
	  all[i].a = '0';
	  printf ("\nEVENT DELETED SUCCESSFULLY\n");
	  break;
	}
    }
}

void
Displayevent (char d[])
{
  int b = 1, flag = 0;
  //enum ven{ 1 ="Amphi theatre" ,2 ="Conference hall 1",3 ="Conference hall 2",4 ="Conference hall 3", 5 ="Lab" ,6 ="Library"};
  for (int i = 0; i < max_events; i++)
    {
      if (all[i].a == '1' && strcmp (all[i].date, d) == 0)
	{
	  printf ("S.No : %d", b++);
	  printf ("\nNAME  : %s", all[i].ename);
	  printf ("\nDate  : %s", all[i].date);
	  printf ("\nTime  : %d - %d", all[i].time[0], all[i].time[1]);
	  printf ("\nVenue : %d", all[i].venue);
	  printf ((all[i].eventtype ==
		   1) ? "\nEventtype : TEST" : "\nEventtype : CEREMONY");
	  printf ((all[i].mic ==
		   1) ? "\nSoundSystem : Available" :
		  "\nSoundSystem : Unavailable");
	  printf ((all[i].lamp ==
		   1) ? "\nLAMP  : Available" : "\nLAMP  : Unavailable");
	  printf ((all[i].PODIUM ==
		   1) ? "\nPODIUM  : Available" : "\nPODIUM  : Unavailable");
	  printf ("\nContactno : %s", all[i].contactno);
	  printf ("\n\n");
	  flag = 1;
	}

    }
  if (flag == 0)
    printf ("No EVENTS BOOKED");
}

bool
isLeapYear (int year)
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool
isValidDate (char date[])
{
  int day, month, year;
  sscanf (date, "%d-%d-%d", &day, &month, &year);

  if (month < 1 || month > 12 || day < 1)
    {
      return false;
    }

  int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  if (isLeapYear (year))
    {
      daysInMonth[2] = 29;
    }

  return (day <= daysInMonth[month]);
}



void
Bookevent ()
{
  int eventtype, M, L, P, final;
  printf ("CHOOSE Number of EVENT TYPE\n1.TEST/DRIVE\n2.CEREMONY/FUNCTION\n");
  scanf ("%d", &eventtype);
  printf ("ENTER DATE in dd-mm-yy format:\n");
  char d[20];
  int v, t[2], flag = 0;
  scanf ("%s", d);
s:
  if (isValidDate (d))
    {
      flag = 1;
    }
  else
    {
      printf ("The entered date is invalid.\n");
      printf ("ENTER DATE in dd-mm-yy format:\n");
      scanf ("%s", d);
      goto s;
    }
  if (flag == 1)
    {
      printf
	("ENTER STARTING & ENDING TIME (24 hr format) in HHMM-HHMM format:\n");
      scanf ("%d-%d", &t[0], &t[1]);
    b:
      printf
	("Enter venue Number\n1.Amphi theatre-venue capacity-200\n2.Conference hall 1-venue capacity-100\n3.Conference hall 2-venue capacity-200\n4.Conference hall 3-venue capacity-100\n5.Lab-venue capacity-80\n6.Library-venue capacity-200\n");
      scanf ("%d", &v);
      if (eventexist (d, t, v) == 0 || (eventtype == 1 && v == 1)
	  || (eventtype == 2 && v == 6) || (eventtype == 2 && v == 5))
	{
	  printf ("\nPLEASE CHANGE VENUE\n");
	  goto b;
	}
      printf ("\nDO YOU REQUIRE SOUND SYSTEM?\npress '1' if yes, else '0'\n");
      scanf ("%d", &M);
      if (M == 1)
	M = eventdetailsmic (d, t);
      printf ("\nDO YOU REQUIRE LAMP?\npress '1' if yes, else '0'\n");
      scanf ("%d", &L);
      if (L == 1)
	L = eventdetailslamp (d, t);
      printf ("\nDO YOU REQUIRE PODIUM?\npress '1' if yes, else '0'\n");
      scanf ("%d", &P);
      if (P == 1)
	P = eventdetailspodium (d, t);
      printf
	("\nSHALL WE BOOK THE EVENT(Enter no) ?\n1.BOOK IT\n2.NO!CANCEL\n");
      scanf ("%d", &final);
      if (final == 1)
	bookeventfinal (eventtype, t, v, d, M, L, P);
      else
	printf ("EVENT CANCELLED ...\n");
      return;
    }

}


int
main ()
{
  for (int i = 0; i < max_events; i++)
    {
      all[i].a = '0';
    }
  int choice;
  while (1)
    {
      printf ("\n*  WELCOME TO EVENT ORGANIZER  *\n");
      printf
	("KINDLY CHOOSE YOUR PURPOSE(ONLY ENTER THE NUMBER OF CHOICE)\n");
      printf ("1.BOOK EVENT\n2.DELETE EVENT\n3.DISPLAY EVENTS\n4.EXIT\n");
      scanf ("%d", &choice);
      if (choice == 1)
	Bookevent ();
      else if (choice == 2)
	{
	  char name[30];
	  int v;
	  printf ("ENTER EVENT NAME:\n");
	  scanf ("%s", name);
	  printf ("ENTER VENUE:\n");
	  scanf ("%d", &v);
	  Deleteevent (name, v);
	}
      else if (choice == 3)
	{
	  char d[20];
	  printf ("PLEASE ENTER EVENT DATE in dd-mm-yy format\n");
	  scanf ("%s", d);
	  Displayevent (d);
	}
      else if (choice == 4)
	return 0;
      else
	printf ("\nEnter valid option");
    }
}
