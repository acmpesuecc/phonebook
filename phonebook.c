//PHONEBOOK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 256
#define MAX_FILE_NAME 100

int line()
{
    FILE *fp;
    int count = 0, line = 0; // Line counter (result)
    char filename[MAX_FILE_NAME] = "contact.csv";
    char c[100], name[100];
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

    else
    {
        printf("Enter the name to be modified:");
        scanf("%s", name);

        while (fgets(c, 500, fp) != NULL)
        {
            count = count + 1;
            char *val1 = strtok(c, ",");
            if (strcmp(val1, name) == 0)
            {
                line = count;
            }
        }

        fclose(fp);
    }
    return line;
}

int delete ()
{
    int lno, ctr = 0;
    char ch;
    FILE *fptr1, *fptr2;
    char fname[MAX] = "contact.csv";
    char str[MAX], temp[] = "newcontact.csv";
    fptr1 = fopen(fname, "r");
    if (!fptr1)
    {
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    fptr2 = fopen(temp, "w"); // open the temporary file in write mode
    if (!fptr2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        return 0;
    }
    lno = line();
    //lno++;
    // copy all contents to the temporary file except the specific line
    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            ctr++;
            /* skip the line at given line number */
            if (ctr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fname);       // remove the original file
    rename(temp, fname); // rename the temporary file to original name

    return 0;
}

struct contact
{
    char name[100], phone[100], age[10], address[100], email[100];
} c;


int checkPhonenumber(char *phone)
{

    int count1 = 0;
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (isdigit(phone[i]) != 0)
            ++count1;
        else
            return 0;
    }
    if (count1 == 10)
    {
        return 1;
    }
    else
        return 0;
}

int checkAge(char *age)
{
    for (int i = 0; age[i] != '\0'; i++)
    {
        if (isdigit(age[i]) == 0)
            return 0;
    }
    if (atoi(age) > 0 && atoi(age) < 105)
        return 1;
    else
        return 0;
}

int add_contact()
{
    int count;

    char line[500], *val1;
    FILE *fptr;
    fptr = fopen("contact.csv", "a+");

    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    else
    {
        printf("Name : ");
        scanf("%s", c.name);

        count = 0;

        int count = 0;
        do
        {
            if (count != 0)
            {
                printf("\tInvalid Phone number. Please try again.\n");
            }
            printf("Phone : ");
            scanf("%s", c.phone);
            ++count;
        } while (!checkPhonenumber(c.phone));

        printf("Age : ");

        count = 0;
        do
        {
            if (count != 0)
            {
                printf("\tInvalid value for Age. Please try again.\n");
            }
            printf("Age : ");
            scanf("%s", c.age);
            ++count;
        } while (!checkAge(c.age));

        printf("Address : ");
        scanf("%s", c.address);
        printf("Email : ");
        scanf("%s", c.email);

        fprintf(fptr, "%s,", c.name);

        fprintf(fptr, "%s,", c.phone);

        fprintf(fptr, "%s,", c.age);

        fprintf(fptr, "%s,", c.address);

        fprintf(fptr, "%s\n", c.email);

        fclose(fptr);
    }
    printf("Added");
    return 0;
}

int search_contact()
{
    FILE *fp = fopen("contact.csv", "r");
    char line[500];
    if (fp == NULL)
    {
        printf("error in opening the file\n");
    }
    else
    {
        char *val1, *val2, *val3, *val4, *val5;
        char name[30];
        printf("Enter the name to be searched:");
        scanf("%s", name);

        while (fgets(line, 500, fp) != NULL)
        {

            val1 = strtok(line, ",");

            val2 = strtok(NULL, ",");

            val3 = strtok(NULL, ",");

            val4 = strtok(NULL, ",");

            val5 = strtok(NULL, ",");

            if (strcmp(val1, name) == 0)
            {
                printf("Name:%s\n ", val1);
                printf("Phone:%s\n ", val2);
                printf("Age:%s\n ", val3);
                printf("Address:%s\n ", val4);
                printf("E-mail:%s\n ", val5);
            }
        }
    }
    return 0;
}
int display_contacts()
{
    FILE *fp = fopen("contact.csv", "r");
    char line[500];
    if (fp == NULL)
    {
        printf("error in opening the file\n");
    }
    else
    {
        char *val1, *val2, *val3, *val4, *val5;

        while (fgets(line, 500, fp) != NULL)
        {

            val1 = strtok(line, ",");

            val2 = strtok(NULL, ",");


            val3 = strtok(NULL, ",");

            val4 = strtok(NULL, ",");

            val5 = strtok(NULL, ",");
            printf("----------");
            printf("Name:%s\n ", val1);
            printf("Phone:%s\n ", val2);
            printf("Age:%s\n ", val3);
            printf("Address:%s\n ", val4);
            printf("E-mail:%s\n \n", val5);
        }
    }
    return 0;
}

int validEmail(char * email) {
        int atFlag = 0, atLoc = 0, dotFlag = 0, dotLoc=0, space = 0;
        if (strcmp(email, "") == 0) return 1;
        else {
                for(int i = 0; i < strlen(email); i++) {
			char current = email[i];
			switch(current) {
				case '@': atFlag = 1;
					  atLoc = i;
					  break;
				case '.': dotFlag = 1;
					  dotLoc = i;
					  break;
				case ' ': space = 1;
					  return 0;
				default : break;
			}
                }
        }
        if(dotFlag && atFlag && (atLoc > 0) && (strlen(email)-atLoc > 4) && (atLoc < dotLoc)) return 1;
        else return 0;
}

void main()
{

    int choice;
    do
    {
        printf("\t\t\t\t\t PHONEBOOK \t\t\t\t\t");
        printf("\n1.Add Contact\n2.Search Contact\n3.Dispay Contacts\n4.Modify Contact\n5.Delete Contact\n");

        scanf("\n%d", &choice);
        switch (choice)
        {

        case 1:
            add_contact();
            break;
        case 2:
            search_contact();
            break;
        case 3:
            display_contacts();
            break;
        case 4:
            delete ();
            add_contact();
            break;
        case 5:
            delete ();
            printf("Deleted Contact\n");
            break;
        default:
            exit(0);
        }
    } while (choice != 0);
}
