
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
        printf("Enter the name for which data has to be modified:");
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

int modify()
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
            //printf("%s",str);
            ctr++;
            /* skip the line at given line number */
            if (ctr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
             else if(ctr == lno)
             {
                 int choice;
                                char attr[100];
                                printf("\n which attribute to modify:");
                                printf("\n1.name     2.number    3.age    4address   5. Email");
                                printf("\n ENTER YOUR CHOICE: ");
                                //scanf("%s",attr);
                                scanf("%d",&choice);
                                if(choice == 1)
                                {
                                char *val1, *val2, *val3, *val4, *val5;
                                val1 = strtok(str, ",");
                                val2 = strtok(NULL, "\n");
                                char new_name[30];
                                char old_stuff[60];
                                printf("\nenter new name : ");
                                scanf("%s",&new_name);
                                strcat(new_name,",");
                                strcpy(old_stuff,val2);
                                strcat(new_name,old_stuff);
                                fprintf(fptr2, "%s\n", new_name);
                                }
                                else if(choice == 2)
                                {
                                char *val1, *val2, *val3, *val4, *val5;
                                val1 = strtok(str, ",");
                                val2 = strtok(NULL, ",");
                                val3 = strtok(NULL,"\n");
                                char newphone[30];
                                char old_stuff_1[60];
                                strcpy(old_stuff_1,val1);
                                strcat(old_stuff_1,",");
                                char old_stuff[60];
                                int check = 0;
                                do
                                {
                                    if (check != 0)
                                    {
                                        printf("\tInvalid Phone number. Please try again.\n");
                                    }
                                    printf("\nenter new number : ");
                                    scanf("%s",&newphone);  
                                    ++check;
                                } while (!checkPhonenumber(newphone));
                                strcat(newphone,",");
                                strcat(old_stuff_1,newphone);
                                strcpy(old_stuff,val3);
                                strcat(old_stuff_1,old_stuff);
                                strcat(newphone,old_stuff);
                                fprintf(fptr2, "%s\n", old_stuff_1);
                                printf("\nrecord modified ...\n");
                                }
                                else if(choice == 3)
                                {
                                char *val1, *val2, *val3, *val4, *val5;
                                val1 = strtok(str, ",");
                                val2 = strtok(NULL, ",");
                                val3 = strtok(NULL,",");
                                val4 = strtok(NULL,"\n");
                                char newage[30];
                                char old_stuff_1[60];
                                strcpy(old_stuff_1,val1);
                                strcat(old_stuff_1,",");
                                strcat(old_stuff_1,val2);
                                strcat(old_stuff_1,","); 
                                char old_stuff[60];
                                int check = 0;
                                do
                                {
                                    if (check != 0)
                                    {
                                        printf("\tInvalid Phone number. Please try again.\n");
                                    }
                                    printf("\nenter new age : ");
                                    scanf("%s",&newage);  
                                    ++check;
                                } while (!checkAge(newage));
                                strcat(newage,",");
                                strcat(old_stuff_1,newage);
                                strcpy(old_stuff,val4);
                                strcat(old_stuff_1,old_stuff);
                                fprintf(fptr2, "%s\n", old_stuff_1);
                                printf("\nrecord modified ...\n");
                                }
                                else if(choice == 4)
                                {
                                char *val1, *val2, *val3, *val4, *val5;
                                val1 = strtok(str, ",");
                                val2 = strtok(NULL, ",");
                                val3 = strtok(NULL,",");
                                val4 = strtok(NULL,",");
                                val5 = strtok(NULL,"\n");
                                char newaddr[30];
                                char old_stuff_1[60];
                                strcpy(old_stuff_1,val1);
                                strcat(old_stuff_1,",");
                                strcat(old_stuff_1,val2);
                                strcat(old_stuff_1,",");
                                strcat(old_stuff_1,val3);
                                strcat(old_stuff_1,",");  
                                char old_stuff[60];
                                printf("\nenter new addres : ");
                                scanf("%s",&newaddr); 
                                strcat(newaddr,",");
                                strcat(old_stuff_1,newaddr);
                                strcpy(old_stuff,val5);
                                strcat(old_stuff_1,old_stuff);
                                fprintf(fptr2, "%s\n", old_stuff_1);
                                printf("\nrecord modified ...\n");
                                }
                                else if(choice == 5)
                                {
                                char *val1, *val2, *val3, *val4, *val5;
                                val1 = strtok(str, ",");
                                val2 = strtok(NULL, ",");
                                val3 = strtok(NULL,",");
                                val4 = strtok(NULL,",");
                                val5 = strtok(NULL,"\n");
                                char newemail[30];
                                char old_stuff_1[60];
                                strcpy(old_stuff_1,val1);
                                strcat(old_stuff_1,",");
                                strcat(old_stuff_1,val2);
                                strcat(old_stuff_1,",");
                                strcat(old_stuff_1,val3);
                                strcat(old_stuff_1,",");
                                strcat(old_stuff_1,val4);
                                strcat(old_stuff_1,",");  
                                char old_stuff[60];
                                int check =0;
                                 do
                                {
                                    if (check != 0)
                                    {
                                        printf("\tInvalid email id. Please try again.\n");
                                    }
                                    printf("\nenter new email : ");
                                    scanf("%s",&newemail);  
                                    ++check;
                                } while (!validEmail(newemail)); 
                                //strcat(newemail,",");
                                strcat(old_stuff_1,newemail);
                                //strcpy(old_stuff,val5);
                                //strcat(old_stuff_1,old_stuff);
                                fprintf(fptr2, "%s\n", old_stuff_1);
                                printf("\nrecord modified ...\n");
                                }

            }
            
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove("contact.csv");       // remove the original file
    rename("newcontact.csv","contact.csv"); // rename the temporary file to original name

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
            printf("\tE-mail  : %s\n",  val5);
        }
        printf("--------------------------------------------------\n");
    }
    return 0;
    fclose(fp);
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
            modify ();
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

