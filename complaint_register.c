
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Complaint
{
  int id;
  char name[50];
  char complaint[150];
  char date[15];
  char subject[80];
  char issue[500];
  char place[50];
  char contact[15];
  char status[20];
};
int
getLastComplaintId ()
{
  FILE *fp;
  char line[800];
  int lastId = 0;
  fp = fopen ("complaints.txt", "r");
  if (fp != NULL)
    {
      while (fgets (line, sizeof (line), fp))
	{
	  char *complaint = strtok (line, "|");
	  if (complaint)
	    lastId = atoi (complaint);
	}
      fclose (fp);
    }
  return lastId + 1;
}

void
registerComplaint ()
{
  FILE *fp;
  struct Complaint c;
  fp = fopen ("complaints.txt", "a");
  if (fp == NULL)
    {
      perror ("Error opening file");
      return;
    }

  c.id = getLastComplaintId ();
  printf ("\nComplaint Number: %d\n", c.id);
  getchar ();

  printf ("Enter First Name: ");
  fgets (c.name, sizeof (c.name), stdin);
  strtok (c.name, "\n");

  printf ("Enter Complaint Name: ");
  fgets (c.complaint, sizeof (c.complaint), stdin);
  strtok (c.complaint, "\n");

  printf ("Enter Date (DD-MM-YYYY): ");
  fgets (c.date, sizeof (c.date), stdin);
  strtok (c.date, "\n");

  printf ("Enter Subject: ");
  fgets (c.subject, sizeof (c.subject), stdin);
  strtok (c.subject, "\n");

  printf ("Enter Description: ");
  fgets (c.issue, sizeof (c.issue), stdin);
  strtok (c.issue, "\n");

  printf ("Enter Place of Incident: ");
  fgets (c.place, sizeof (c.place), stdin);
  strtok (c.place, "\n");

  printf ("Enter Contact Number: ");
  fgets (c.contact, sizeof (c.contact), stdin);
  strtok (c.contact, "\n");

  strcpy (c.status, "Pending");
  fprintf (fp, "%d|%s|%s|%s|%s|%s|%s|%s|%s\n", c.id, c.name, c.complaint,
	   c.date, c.subject, c.issue, c.place, c.contact, c.status);
  fclose (fp);

  printf ("\nComplaint Registered Successfully.\n");
  printf ("Status: %s\n", c.status);
}

void
viewComplaints ()
{
  FILE *fp;
  struct Complaint complaints[100];
  int count = 0;
  char line[800];
  int i;
  fp = fopen ("complaints.txt", "r");
  if (fp == NULL)
    {
      printf ("\nNo complaints found.\n");
      return;
    }
  while (fgets (line, sizeof (line), fp))
    {
      struct Complaint c;
      char *token;
      token = strtok (line, "|");
      if (token)
	c.id = atoi (token);
      token = strtok (NULL, "|");
      if (token)
	strcpy (c.name, token);
      token = strtok (NULL, "|");
      if (token)
	strcpy (c.complaint, token);
      token = strtok (NULL, "|");
      if (token)
	strcpy (c.date, token);
      token = strtok (NULL, "|");
      if (token)
	strcpy (c.subject, token);
      token = strtok (NULL, "|");
      if (token)
	strcpy (c.issue, token);
      token = strtok (NULL, "|");
      if (token)
	strcpy (c.place, token);
      token = strtok (NULL, "|");
      if (token)
	strcpy (c.contact, token);
      token = strtok (NULL, "\n");
      if (token)
	strcpy (c.status, token);
      complaints[count++] = c;
    }
  fclose (fp);
  for (i = 0; i < count; i++)
    {
      struct Complaint c = complaints[i];
      char choice;
      int updateChoice;
      printf ("\n---\n");
      printf
	("Complaint No: %d\nName: %s\nComplaint: %s\nDate: %s\nSubject: %s\nDescription: %s\nPlace: %s\nContact: %s\nStatus: %s\n",
	 c.id, c.name, c.complaint, c.date, c.subject, c.issue, c.place,
	 c.contact, c.status);

      printf ("Do you want to update the status? (y/n): ");
      scanf (" %c", &choice);
      getchar ();
      if (choice == 'y' || choice == 'Y')
	{
	  printf
	    ("Select new status:\n1. Case Closed\n2. Case Withdrawn\n3. No Change\n4. Sucess\n Enter choice: ");
	  scanf ("%d", &updateChoice);
	  getchar ();
	  if (updateChoice == 1)
	    strcpy (complaints[i].status, "Case Closed");
	  else if (updateChoice == 2)
	    strcpy (complaints[i].status, "Case Withdrawn");
	  else if (updateChoice == 3)
	    strcpy (complaints[i].status, "No Change");  
	  else if (updateChoice == 4)
	    strcpy (complaints[i].status, "Case Was Success");
	  else
	    printf ("No changes made.\n");
	}
    }
  fp = fopen ("complaints.txt", "w");
  if (fp == NULL)
    {
      perror ("Error saving updates");
      return;
    }
  for (i = 0; i < count; i++)
    {
      struct Complaint c = complaints[i];
      fprintf (fp, "%d|%s|%s|%s|%s|%s|%s|%s|%s\n", c.id, c.name, c.complaint,
	       c.date, c.subject, c.issue, c.place, c.contact, c.status);
    }
  fclose (fp);
  printf ("\nAll updates saved successfully.\n");
  printf ("Press Enter to return to the menu.");
  getchar ();
}

int
main ()
{
  int choice;
  do
    {
      printf ("\n- Complaint Register System -\n");
      printf ("1. Register Complaint\n");
      printf ("2. View Complaints\n");
      printf ("3. Exit\n");
      printf ("Enter your choice: ");
      scanf ("%d", &choice);
      getchar ();
      switch (choice)
	{
	case 1:
	  registerComplaint ();
	  break;
	case 2:
	  viewComplaints ();
	  break;
	case 3:
	  printf ("\nExiting...\n");
	  break;
	default:
	  printf ("\nInvalid choice.\n");
	}
    }
  while (choice != 3);
  return 0;
}


