// including header files
#include <stdio.h>
#include <string.h>

// Define the structure of books
struct books
{
    int serialNo;
    char book_name[20];
    char author[20];
    int edition;
    int ISBN;
    float price;
    char isReserved;
} b[5];

// Function prototypes
void add_book();
void remove_newline(char *str);
int last();
void delete_book();
void search_book();
void update_record();
void display_books();
void issue_book();
void exit_program();

// Main function
void main()
{

    FILE *lib;
    int start = 0;

    // Open the file in read mode to check if it exists and is empty
    lib = fopen("library.txt", "r");
    if (lib == NULL)
    {
        // If the file doesn't exist, create it and add '0'
        printf("File not found, creating new file.\n");
        lib = fopen("library.txt", "w");
        if (lib != NULL)
        {
            fprintf(lib, "%d", start);
            fclose(lib);
            printf("File created and initialized with value: %d\n", start);
        }
        else
        {
            printf("Failed to create file.\n");
        }
    }
    else
    {
        // File exists, check if it's empty
        fseek(lib, 0, SEEK_END);     // Move file pointer to the end
        long file_size = ftell(lib); // Get current position, which is file size
        if (file_size == 0)
        {
            // If file is empty, add '0' to it
            printf("File is empty, adding value: %d\n", start);
            fprintf(lib, "%d", start);
        }
        else
        {
            printf("File already exists and is not empty, skipping.\n");
        }
        fclose(lib); // Close the file
    }

    int chosen;
    int n = 0;

    // Menu
    do
    {
        printf("\n<!---Welcome to Library---!>\n");
        printf("1. Add Book\n2. Delete Book\n3. Search Book\n4. Update a Book Record\n5. Display all the books in Library\n6. Issue book to anyone\n7. Exit\n");
        printf("\nEnter your choice here (1 - 7): ");

        scanf("%d", &chosen);
        switch (chosen)
        {
        case 1:
            add_book();
            break;
        case 2:
            delete_book();
            break;
        case 3:
            search_book();
            break;
        case 4:
            update_record();
            break;
        case 5:
            display_books();
            break;
        case 6:
            issue_book();
            break;
        case 7:
            exit_program();
            break;
        default:
            printf("INVALID Entry\n");
            break;
        }
    } while (chosen != 7);
}

// Function definitions

// Add book function
void add_book()
{
    FILE *lib;
    lib = fopen("library.txt", "w");

    if (lib == NULL)
    {
        printf("File not found\n");
    }

    int n = 0;
    char choice = 'y';
    while (choice == 'y' && n < 5)
    {

        printf("Fill out the following details: \n");
        getchar();

        printf("Serial No: ");
        scanf("%d", &b[n].serialNo);
        fprintf(lib, "%-10d", b[n].serialNo);

        getchar();
        printf("Book name: ");
        fgets(b[n].book_name, sizeof(b[n].book_name), stdin);
        remove_newline(b[n].book_name);
        fprintf(lib, "%-20s", b[n].book_name);

        printf("Author: ");
        fgets(b[n].author, sizeof(b[n].author), stdin);
        remove_newline(b[n].author);
        fprintf(lib, "%-20s", b[n].author);

        printf("Edition: ");
        scanf("%d", &b[n].edition);
        fprintf(lib, "%-10d", b[n].edition);

        printf("ISBN: ");
        scanf("%d", &b[n].ISBN);
        fprintf(lib, "%-10d", b[n].ISBN);

        printf("Price: ");
        scanf("%f", &b[n].price);
        fprintf(lib, "%-10.2f", b[n].price);

        printf("Is Reserved(y / n): ");
        scanf(" %c", &b[n].isReserved);
        fprintf(lib, "%c\n", b[n].isReserved);

        n++;

        printf("Do you want to add another book (y / n): ");
        scanf(" %c", &choice);
    }
    fprintf(lib, "%d", n);
    fclose(lib);
    printf("Books added successfully\n");
}

// Remove new line function
void remove_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

// Display books function
void display_books()
{
    int n = last();
    FILE *lib;
    lib = fopen("library.txt", "r");

    if (lib == NULL)
    {
        printf("File not found\n");
    }
    if (n == 0)
    {
        printf("No books in the library\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {

            fscanf(lib, "%d", &b[i].serialNo);
            printf("Serial No: %d\n", b[i].serialNo);

            fscanf(lib, "%s", b[i].book_name);
            printf("Book Name: %s\n", b[i].book_name);

            fscanf(lib, "%s", b[i].author);
            printf("Author: %s\n", b[i].author);

            fscanf(lib, "%d", &b[i].edition);
            printf("Edition: %d\n", b[i].edition);

            fscanf(lib, "%d", &b[i].ISBN);
            printf("ISBN: %d\n", b[i].ISBN);

            fscanf(lib, "%f", &b[i].price);
            printf("Price: %.2f\n", b[i].price);

            fscanf(lib, " %c", &b[i].isReserved);
            printf("Reserved: %c\n", b[i].isReserved);
        }

        printf("Books displayed successfully\n");
    }

    fclose(lib);
}

// Delete book function
void delete_book()
{
    int n = last();
    FILE *lib;
    lib = fopen("library.txt", "r");

    if (lib == NULL)
    {
        printf("File not found\n");
    }

    if (n == 0)
    {
        printf("No books in the library\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            fscanf(lib, "%d", &b[i].serialNo);
            fscanf(lib, "%s", b[i].book_name);
            fscanf(lib, "%s", b[i].author);
            fscanf(lib, "%d", &b[i].edition);
            fscanf(lib, "%d", &b[i].ISBN);
            fscanf(lib, "%f", &b[i].price);
            fscanf(lib, " %c", &b[i].isReserved);
        }
        fclose(lib);

        lib = fopen("library.txt", "w");

        if (lib == NULL)
        {
            printf("File not found\n");
        }

        char name[20];
        printf("Enter book name: ");
        getchar();
        fgets(name, sizeof(name), stdin);
        remove_newline(name);

        int deleted = 0;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(b[i].book_name, name) != 0)
            {
                fprintf(lib, "%-10d", b[i].serialNo);
                fprintf(lib, "%-20s", b[i].book_name);
                fprintf(lib, "%-20s", b[i].author);
                fprintf(lib, "%-10d", b[i].edition);
                fprintf(lib, "%-10d", b[i].ISBN);
                fprintf(lib, "%-10.2f", b[i].price);
                fprintf(lib, "%-10c\n", b[i].isReserved);
                printf("Book not found\n");
            }
            else
            {
                deleted++;
                printf("Book deleted successfully\n");
            }
        }
        n -= deleted;
        fprintf(lib, "%d", n);
        fclose(lib);
    }
}

// Search book function
void search_book()
{
    int n = last();
    FILE *lib;
    lib = fopen("library.txt", "r");

    if (lib == NULL)
    {
        printf("File not found\n");
    }
    if (n == 0)
    {
        printf("No books in the library\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {

            fscanf(lib, "%d", &b[i].serialNo);
            fscanf(lib, "%s", b[i].book_name);
            fscanf(lib, "%s", b[i].author);
            fscanf(lib, "%d", &b[i].edition);
            fscanf(lib, "%d", &b[i].ISBN);
            fscanf(lib, "%f", &b[i].price);
            fscanf(lib, " %c", &b[i].isReserved);
        }

        int s_choice, ISBN;
        int flag = 0;
        char book_name[20];
        char author[20];
        printf("Search by...\n1. ISBN\n2. Book Name\n3. Author\n");
        printf("\nChoose Here (1 - 3): ");
        scanf("%d", &s_choice);

        switch (s_choice)
        {
        case 1:
            printf("Enter ISBN: ");
            scanf("%d", &ISBN);
            for (int i = 0; i < n; i++)
            {
                if (ISBN == b[i].ISBN)
                {
                    printf("Book Found\n");
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                printf("Book not found\n");
            }
            break;
        case 2:
            printf("Enter Book Name: ");
            getchar();
            fgets(book_name, sizeof(book_name), stdin);
            remove_newline(book_name);
            for (int i = 0; i < n; i++)
            {
                if (strcmp(book_name, b[i].book_name) == 0)
                {
                    printf("Book Found\n");
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                printf("Book not found\n");
            }
            break;
        case 3:
            printf("Enter Author Name: ");
            getchar();
            fgets(author, sizeof(author), stdin);
            remove_newline(author);
            for (int i = 0; i < n; i++)
            {
                if (strcmp(author, b[i].author) == 0)
                {
                    printf("Book Found\n");
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                printf("Book not found\n");
            }
            break;

        default:
            printf("Invalid Entry");
        }
        fclose(lib);
    }
}

// Update record function
void update_record()
{
    int n = last();
    FILE *lib;
    lib = fopen("library.txt", "r");

    if (lib == NULL)
    {
        printf("File not found\n");
    }

    if (n == 0)
    {
        printf("No books in the library\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {

            fscanf(lib, "%d", &b[i].serialNo);
            fscanf(lib, "%s", b[i].book_name);
            fscanf(lib, "%s", b[i].author);
            fscanf(lib, "%d", &b[i].edition);
            fscanf(lib, "%d", &b[i].ISBN);
            fscanf(lib, "%f", &b[i].price);
            fscanf(lib, " %c", &b[i].isReserved);
        }
        fclose(lib);

        char newName[20];
        char oldName[20];
        int flag = 0;
        printf("Enter old Book Name: ");
        getchar();
        fgets(oldName, sizeof(oldName), stdin);
        remove_newline(oldName);

        printf("Enter new Book Name: ");
        fgets(newName, sizeof(newName), stdin);
        remove_newline(newName);

        for (int i = 0; i < n; i++)
        {
            if (strcmp(oldName, b[i].book_name) == 0)
            {
                strcpy(b[i].book_name, newName);
                printf("Book Updated\n");
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            printf("Book not found");
        }
        lib = fopen("library.txt", "w");

        if (lib == NULL)
        {
            printf("File not found\n");
        }

        for (int i = 0; i < n; i++)
        {

            fprintf(lib, "%-10d", b[i].serialNo);
            fprintf(lib, "%-20s", b[i].book_name);
            fprintf(lib, "%-20s", b[i].author);
            fprintf(lib, "%-10d", b[i].edition);
            fprintf(lib, "%-10d", b[i].ISBN);
            fprintf(lib, "%-10.2f", b[i].price);
            fprintf(lib, "%-10c\n", b[i].isReserved);
        }
        fprintf(lib, "%d", n);
        fclose(lib);
    }
}
// Last function
int last()
{
    FILE *lib;
    int last;
    lib = fopen("library.txt", "r");
    fseek(lib, -1, SEEK_END);
    fscanf(lib, "%d", &last);
    fclose(lib);
    return last;
}

// Issue book function
void issue_book()
{
    int n = last();
    FILE *lib;
    lib = fopen("library.txt", "r");

    if (lib == NULL)
    {
        printf("File not found\n");
    }

    if (n == 0)
    {
        printf("No books in the library\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {

            fscanf(lib, "%d", &b[i].serialNo);
            fscanf(lib, "%s", b[i].book_name);
            fscanf(lib, "%s", b[i].author);
            fscanf(lib, "%d", &b[i].edition);
            fscanf(lib, "%d", &b[i].ISBN);
            fscanf(lib, "%f", &b[i].price);
            fscanf(lib, " %c", &b[i].isReserved);
        }
        fclose(lib);
        char book_name[20];
        int flag = 0;

        printf("Enter Book Name: ");
        getchar();
        fgets(book_name, sizeof(book_name), stdin);
        remove_newline(book_name);

        for (int i = 0; i < n; i++)
        {
            if (strcmp(book_name, b[i].book_name) == 0)
            {
                if (b[i].isReserved == 'y')
                {
                    printf("Book is already reserved\n");
                }
                else
                {
                    printf("Book issued successfully\n");
                    b[i].isReserved = 'y';
                }
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            printf("Book not found\n");
        }

        lib = fopen("library.txt", "w");

        if (lib == NULL)
        {
            printf("File not found\n");
        }

        for (int i = 0; i < n; i++)
        {

            fprintf(lib, "%-10d", b[i].serialNo);
            fprintf(lib, "%-20s", b[i].book_name);
            fprintf(lib, "%-20s", b[i].author);
            fprintf(lib, "%-10d", b[i].edition);
            fprintf(lib, "%-10d", b[i].ISBN);
            fprintf(lib, "%-10.2f", b[i].price);
            fprintf(lib, "%-10c\n", b[i].isReserved);
        }
        fprintf(lib, "%d", n);
        fclose(lib);
    }
}

// Exit function
void exit_program()
{
    printf("You're Exiting...\n");
}
