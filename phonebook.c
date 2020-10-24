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
int validEmail(char *email)
{
    int atFlag = 0, atLoc = 0, dotFlag = 0, dotLoc = 0, space = 0;
    if (strcmp(email, "-") == 0)
        return 1;
    else
    {
        for (int i = 0; i < strlen(email); i++)
        {
            char current = email[i];
            switch (current)
            {
            case '@':
                atFlag = 1;
                atLoc = i;
                break;
            case '.':
                dotFlag = 1;
                dotLoc = i;
                break;
            case ' ':
                space = 1;
                return 0;
            default:
                break;
            }
        }
    }
    if (dotFlag && atFlag && (atLoc > 0) && (strlen(email) - atLoc > 4) && (atLoc < dotLoc))
        return 1;
    else
        return 0;
}
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

        do
        {
            printf("Email : ");
            scanf("%s", c.email);
            if (!validEmail(c.email))
            {
                printf("\tInvalid Email.\n");
            }

        } while (!validEmail(c.email));

        fprintf(fptr, "%s,", c.name);

        fprintf(fptr, "%s,", c.phone);

        fprintf(fptr, "%s,", c.age);

        fprintf(fptr, "%s,", c.address);

        fprintf(fptr, "%s,\n", c.email);

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
        char phone[15];
        char email[30];
        int choice = 0;
        int found=0;
        int val = 0;
 label: printf("Search by?:\n");
        printf("1. Search by Phone Number\n2. Search by EmailID\n3. Search by Name\n");
        scanf("%d", &choice);
        // printf("Enter the name to be searched:");
        // scanf("%s", name);
        if(choice == 1)
        {
            printf("Enter Phone Number:");
            scanf("%s", phone);
        }
        else if(choice == 2)
        {
            printf("Enter EmailID:");
            scanf("%s", email);
        }
        else if(choice == 3)
        {
            printf("Enter Name:");
            scanf("%s", name);
        }
        
        else
        {
            printf("Pick an appropriate option !!\n");
            goto label;
        }
        while (fgets(line, 500, fp) != NULL)
        {

            val1 = strtok(line, ",");

            val2 = strtok(NULL, ",");

            val3 = strtok(NULL, ",");

            val4 = strtok(NULL, ",");

            val5 = strtok(NULL, ",");

            switch (choice)
            {
                case 1:
                    if (strcmp(val2, phone) == 0)
                    {
                        found = 1;
                        printf("------------------------------------------------------------------------------------------------------------------------------\n\n");
                        printf("\tName    : %s\n ", val1);
                        printf("\tAge     : %s\n ", val3);
            
                        printf("\t\t\t\t\t Contact Details \t\t\t\t\t");
                        printf("\n\tAddress : %s\n ", val4);
                        printf("\tPhone   : %s ", val2);
                        printf("\tE-mail  : %s\n",  val5);
                    }
                    else{
                        found=0;
                    }
                    break;
                
                case 2:
                    // printf("%s", val5);
                    // printf("%s", email);
                    // val = strcmp(val5, email);
                    // printf("%d", val);
                    if (strcmp(val5, email) == 0)
                    {
                        found =1 ;
                        printf("------------------------------------------------------------------------------------------------------------------------------\n\n");
                        printf("\tName    : %s\n ", val1);
                        printf("\tAge     : %s\n ", val3);
            
                        printf("\t\t\t\t\t Contact Details \t\t\t\t\t");
                        printf("\n\tAddress : %s\n ", val4);
                        printf("\tPhone   : %s ", val2);
                        printf("\tE-mail  : %s\n",  val5);
                        
                    }               
                    else{
                        found=0;
                    }
                    break;
                case 3:
                    if (strcmp(val1, name) == 0)
                    {
                        found=1;
                        printf("------------------------------------------------------------------------------------------------------------------------------\n\n");
                        printf("\tName    : %s\n ", val1);
                        printf("\tAge     : %s\n ", val3);
            
                        printf("\t\t\t\t\t Contact Details \t\t\t\t\t");
                        printf("\tAddress : %s\n ", val4);
                        printf("\tPhone   : %s ", val2);
                        printf("\tE-mail  : %s\n",  val5);
                    }
                    else{
                    found=0;
                    }
                default:
                    printf("Pick an appropriate option");
                    break;
            }
            //break;
        
        }
        if(found == 0)
            {
             printf("------------------------------------------------------------------------------------------------------------------------------\n\n");
             printf("Contact Not Found!\n\n");
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
            printf("------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf("\tName    : %s\n ", val1);
            printf("\tAge     : %s\n ", val3);
            
            printf("\t\t\t\t\t Contact Details \t\t\t\t\t");
            printf("\n\tAddress : %s\n ", val4);
            printf("\tPhone   : %s ", val2);
            printf("\tE-mail  : %s\n",  val5);
        }
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
    }
    return 0;
}

void main()
{

    int choice;
    do
    {
        printf("********************************************************************************************************************************\n");
        printf("\t\t\t\t\t PHONEBOOK \t\t\t\t\t");
        printf("\nEnter 1 to Add Contact\nEnter 2 to Search Contact\nEnter 3 to Display Contacts\nEnter 4 to Modify Contact\nEnter 5 to Delete Contact\nEnter 6 to Quit Phonebook\n");
        printf("\n********************************************************************************************************************************\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        printf("\n********************************************************************************************************************************\n");
        
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
    } while (choice != 6);
}

