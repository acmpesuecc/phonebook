//PHONEBOOK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX 256
#define EMAIL_REGEX "^[a-zA-Z0-9]\\+@[a-zA-Z0-9]\\+\\.[a-z]\\{2,\\}"
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
                break;
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
    // Function to validate email

    // declare valid regex variable
    regex_t regex;
    // declare regex result value
    int valid;

    // compile the regex
    valid = regcomp(&regex, EMAIL_REGEX, 0);

    // check compilation
    if (valid == 0)
    {
        // printf("Email Regex compiled succesfully");
    }
    else
    {
        printf("Email Regex Compilation failed.");
        return 0;
    }

    // validate the email
    int match_result = regexec(&regex, email, 0, NULL, 0);

    if (match_result == 0)
    {
        // match found, and thus, email is valid
        return 1;
    }
    else if (match_result == REG_NOMATCH)
    {
        // match not found, invalid email
        return 0;
    }
    else
    {
        // error occurred during pattern matching
        printf("An Unexpected error occurred.\n");
        return 0;
    }
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

int init_line()
{
    FILE *fp;
    fp = fopen("contact.csv", "r");
    char line[500];

    FILE *ftemp;
    ftemp = fopen("temp.csv", "w+");

    char *val1, *val2, *val3, *val4, *val5;
    char *n, *p, *a, *add, *e;
    char name[30];
    int ctr = 0;
    if (fp == NULL)
    {
        printf("error in opening the file\n");
    }
    if (!ftemp)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp);
        return 0;
    }
    else
    {
        printf("Enter the name to be searched:");
        scanf("%s", name);

        while (fgets(line, 500, fp) != NULL)
        {
            ctr++;
            val1 = strtok(line, ",");

            val2 = strtok(NULL, ",");

            val3 = strtok(NULL, ",");

            val4 = strtok(NULL, ",");

            val5 = strtok(NULL, ",");
            if (strcmp(val1, name) == 0)
            {
                n = val1;
                p = val2;
                a = val3;
                add = val4;
                e = val5;
                printf("--------------------------------------------------\n\n");
                printf("\tName    : %s\n ", n);
                printf("\tPhone   : %s\n ", p);
                printf("\tAge     : %s\n ", a);
                printf("\tAddress : %s\n ", add);
                printf("\tE-mail  : %s\n", e);
                break;
            }
        }
        printf("--------------------------------------------------\n");
    }
    char ch;
    int choice, count;
    do
    {
        count = 0;
        printf("Choose the field to modify!\n-------------------------------\n");
        printf("1.Modify Name\n2.Modify Phone\n3.Modify Age\n4.Modify Address\n5.Modify E-mail\n");
        printf("\nEnter your choice:");
        scanf("%d", &choice);
        switch (choice)
        {

        case 1:
            printf("Name : ");
            scanf("%s", n);
            break;
        case 2:
            count = 0;
            do
            {
                if (count != 0)
                {
                    printf("\tInvalid Phone number. Please try again.\n");
                }
                printf("Phone : ");
                scanf("%s", p);
                ++count;
            } while (!checkPhonenumber(p));
            break;
        case 3:
            count = 0;
            do
            {
                if (count != 0)
                {
                    printf("\tInvalid value for Age. Please try again.\n");
                }
                printf("Age : ");
                scanf("%s", a);
                ++count;
            } while (!checkAge(a));
            break;
        case 4:
            printf("Address : ");
            scanf("%s", add);
            break;
        case 5:
            do
            {
                printf("Email : ");
                scanf("%s", e);
                if (!validEmail(e))
                {
                    printf("\tInvalid Email.\n");
                }

            } while (!validEmail(e));
            break;
        default:
            break;
        }
        printf("Do you want to edit any other fields as well(y/n): ");
        fflush(stdin);
        scanf("%s", &ch);
        fflush(stdin);
    } while (ch == 'y');

    fprintf(ftemp, "%s,", n);

    fprintf(ftemp, "%s,", p);

    fprintf(ftemp, "%s,", a);

    fprintf(ftemp, "%s,", add);

    fprintf(ftemp, "%s\n", e);

    fclose(ftemp);
    fclose(fp);

    return ctr;
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
    printf("\nContact Added Successfully\n");
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

        char search[50];
        printf("Enter the name / email / phone-no to be searched: ");
        scanf("%s", search);

        while (fgets(line, 500, fp) != NULL)
        {

            val1 = strtok(line, ",");

            val2 = strtok(NULL, ",");

            val3 = strtok(NULL, ",");

            val4 = strtok(NULL, ",");

            val5 = strtok(NULL, ",");  //email ending with /n

            if (strcmp(val1, search) == 0  || strcmp(val2, search) == 0 || strcmp(val5, search) == 0)
            {

                printf("\n--------------------------------------------------\n\n");
                printf("\tName    : %s\n ", val1);
                printf("\tPhone   : %s\n ", val2);
                printf("\tAge     : %s\n ", val3);
                printf("\tAddress : %s\n ", val4);
                printf("\tE-mail  : %s\n",  val5);
                printf("--------------------------------------------------\n");
            }
            

        }
        
    }
    fclose(fp);

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
            printf("--------------------------------------------------\n\n");
            printf("\tName    : %s\n ", val1);
            printf("\tPhone   : %s\n ", val2);
            printf("\tAge     : %s\n ", val3);
            printf("\tAddress : %s\n ", val4);
            printf("\tE-mail  : %s\n", val5);
        }
        printf("--------------------------------------------------\n");
    }
    return 0;
    fclose(fp);
}

int modify_contact()
{
    {
        FILE *fptr1, *fptr2, *fptr3;
        int lno, linectr = 0;
        char str[MAX], fname[MAX] = "contact.csv";
        char newln[MAX], temp[] = "newcontact.csv";

        lno = init_line();

        fptr1 = fopen(fname, "r");
        if (fptr1 == NULL)
        {
            printf("Unable to open the input file!!\n");
            return 0;
        }
        fptr2 = fopen(temp, "w");
        if (!fptr2)
        {
            printf("Unable to open a temporary1 file to write!!\n");
            fclose(fptr1);
            return 0;
        }
        fptr3 = fopen("temp.csv", "a+");
        if (!fptr2)
        {
            printf("Unable to open a temporary2 file to write!!\n");
            fclose(fptr1);
            return 0;
        }

        fgets(newln, MAX, fptr3);

        while (!feof(fptr1))
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr1);
            if (!feof(fptr1))
            {
                linectr++;
                if (linectr != lno)
                {
                    fprintf(fptr2, "%s", str);
                }
                else
                {
                    fprintf(fptr2, "%s", newln);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        fclose(fptr3);
        remove("contact.csv");
        remove("temp.csv");
        rename(temp, fname);
        printf("Modification successfull!! \n");
        return 0;
    }
}

void main()
{

    int choice;
    do
    {
        printf("\t\t\t\t\t PHONEBOOK \t\t\t\t\t");

        printf("\nEnter 1 to Add Contact\nEnter 2 to Search Contact\nEnter 3 to Display Contacts\nEnter 4 to Modify Contact\nEnter 5 to Delete Contact\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
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
            //delete();
            //add_contact();
            modify_contact();
            break;
        case 5:
            delete ();
            printf("Deleted Contact\n");
            break;
        default:
            printf("Exiting the program now!");
            exit(0);
        }
    } while (choice != 0);

}


