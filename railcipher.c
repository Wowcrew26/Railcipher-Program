#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

#define error(code, message)              \
    do                                    \
    {                                     \
        fprintf(stderr, "%s\n", message); \
        return code;                      \
    } while (0)

#define NOT_ENOUGH_CLAS 1

void removingNonLetters(char *str)
{
    // we need to get rid of punctuation and white space
    char *PrevString = str;
    char *newString = str;

    while (*PrevString)
    {
        if (isalpha(*PrevString))
        {
            
            *newString = tolower(*PrevString);
            newString++;
        }
        PrevString++;
    }
    *newString = '\0';
}/*
void printArray(int n, int m, char array2d[][m])
{
    printf("\n");
    //printf(" Plaintext: ");
    printf("\n");
    for (int i = 0; i < n; i++)
    { // for demonstration purposes
        for (int j = 0; j < m; j++)
            printf("%c ", array2d[i][j]);
        printf("\n");
    }
}
*/
void LettersInArray(char *tester, int m, int n, char str[][m])
{
    // we need to place all letters in a rectangle 2D array of size n x m
    // fill row-by-row, left to right, top to bottom
    // if last row is not full we need to make it adjacent to z - 1
    // m is num of columns (length of encryption key)
    // n is rows, calculated by rounding the value up to closest int (l/m where l is num of char left in og message after removing non alphabetical chars)
    int k = 0;
    int dif = m * n - strlen(tester) - 1;
    // printf("%d\n", strlen(tester));
    // printf(" Letters:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            //

            if (k < strlen(tester))
                str[i][j] = tester[k++];

            else
            {
                str[i][j] = (char)('z' - dif--);
            }

            // printf("%c\n", str[i][j]);
        }
}
void ciphertext(int n, int m, char array2d[][m], int *key)
{
    //printf(" Ciphertext:\n");
    int currCol = 1;
    while (1)
    {
        for (int i = 0; i < m; i++)
        {
            // printf("%d", key[i]);
            if (key[i] == currCol)
            {
                currCol++;
                for (int row = 0; row < n; row++)
                {

                    printf("%c", toupper(array2d[row][i]));
                }
                //  printf("%d", key[i]);
            }
        }

        if (currCol > m)
            break;
    }
    printf("\n");
}

// end of encryption
// next up is decryption

void letterDecrypt(char *ciphertext, int *key, int m)
{
    // Step 1: Find the length of ciphertext
    int length = strlen(ciphertext);
    //printf("Step 1 - Length of text: %d\n", length);

    // Step 2: Divide the length of ciphertext by the length of given key to obtain the number of rows
    int n = length / m;
    //printf("Step 2 - Number of rows (n): %d\n", n);
    //printf("Number of columns (m): %d\n", m);

    // Step 3: Break the ciphertext into equal-length words of length n
    //printf("Step 3 - Decrypted segments:\n");
    /*
    for (int i = 0; i < length; i += n)
    {
        // Print out each segment of length n
        for (int j = 0; j < n; j++)
        {
            if (i + j < length)
            {
                printf("%c", ciphertext[i + j]);
            }
        }
        // Print a space after each segment for readability
        //printf(" ");
    }
    printf("\n");
    */
    // Proceeding with decryption as previously explained
    char decrypt2d[n][m]; // 2D array to store the decrypted segments
    //printf("\n");
    // Fill the 2D array according to the key
    for (int pos = 0; pos < m; pos++)
    {
        int segmentIndex = key[pos] - 1; // Find the correct segment for this column
        for (int row = 0; row < n; row++)
        {
            int charIndex = segmentIndex * n + row; // Index in the ciphertext for this character
            decrypt2d[row][pos] = ciphertext[charIndex];
        }
    }

    // Print the key above the 2D array
    //printf("Key:        ");
    for (int i = 0; i < m; i++)
    {
       // printf("%d ", key[i]); // Print key with a single space
    }
    //printf("\n");

    // Print the decrypted 2D array with a single space between columns
    //printf("Plaintext:  ");
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
        {
         //   printf("            "); // This aligns with the start of the array on the next lines
        }
        for (int j = 0; j < m; j++)
        {
          //  printf("%c ", decrypt2d[i][j]); // Print each character with a single space
        }
        //printf("\n");
    }

    // Print the decrypted message in row-major order
    //printf("\nCiphertext: ");
    for (int row = 0; row < n; row++)
    {

        for (int col = 0; col < m; col++)
        {
            printf("%c", decrypt2d[row][col]);
        }
    }
    //printf("\n");
}

int check_integer(char *str)
{
    if (strlen(str) == 0)
        return FALSE;
    if (str[0] == '-' || str[0] == '+') // explicit signal
        str++;                          // skip it
    while (*str)
        if (!isdigit(*(str++)))
            return FALSE;
    return TRUE;
}
/*
char *get_DaInput()
{ // Scanner.next equivalent by
    // char string[1000];//stack! not a good choice
    char *string = (char *)malloc(1000); // char* cast to malloc is the most generic way, so the most versatile; also, the quantity is in bytes
    for (int i = 0; i < 1000; i++)
    {
        string[i] = getchar();
        if (string[i] == '\t' || string[i] == '\n' || string[i] == EOF)
        {
            string[i] = '\0';
            break;
        }
    }
    return string; // logically correct, but incorrect bc a pointer is being returned to a stack data that will be erased after return--building a house on water.
}
*/
int main(int argc, char *argv[])
{

    // remember to run in terminal to avoid segment fault
    for (int i = 1; i < argc; i++)
    {
        if (!check_integer(argv[i]))
        {
            printf("railcipher: Fatal error! First CLA must be a valid integer.\n");
            error(NOT_ENOUGH_CLAS, "railcipher: Fatal error! First CLA must be a valid integer.\n");
        }
    }

    if (argc < 2)
    {
        printf("railcipher: Fatal error! The encryption key passed as CLAs is not valid.\n");
        error(NOT_ENOUGH_CLAS, "railcipher: Fatal error! The encryption key passed as CLAs is not valid.\n");
    }

    int m = atoi(argv[1]);

    if (m > 26)
    {
        printf("railcipher: Fatal error! The encryption key length cannot exceed 26.\n");
        error(NOT_ENOUGH_CLAS, "railcipher: Fatal error! The encryption key length cannot exceed 26.\n");
    }
    // hardcoded tester int m = 7;
    int key[m];
    for (int i = 2; i < argc; i++)
    {
        key[i - 2] = atoi(argv[i]);
    }
    // Check for a valid permutation of the key
    for (int i = 1; i <= m; ++i)
    {
        int found = 0;
        for (int j = 0; j < m; ++j)
        {
            if (key[j] == i)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("railcipher: Fatal error! The encryption key passed as CLAs is not valid.\n");
            error(NOT_ENOUGH_CLAS, "railcipher: Fatal error! The encryption key passed as CLAs is not valid.\n");
        }
    }
    // hardcoded tester
    // if temp starts with encrypt or decrpyt we decide what to do next or quit
    // this will go inside while loop eventually
    // text input
    // char *temp = get_DaInput();
    // printf("%s\n", temp);

    /*
    dummy testers
    char tester[] = "Attack postponed until two A.M.";
    removingNonLetters(tester);
    int l = strlen(tester);
    int n = (l + m - 1) / m;

    printf("amount of rows (n): %d\n", n);
    printf("length before xyz filler values: %d\n", l);
    printf("\n");
    char array2d[n][m];
    char cipher2d[n][m];
    LettersInArray(tester, m, n, array2d);
    printf("%s\n", tester);
    printArray(n, m, array2d);
    // int key[] = {4, 3, 1, 2, 5, 6, 7};

    printf("\n");
    ciphertext(n, m, array2d, key);
    printf("\n");

    printf("-----------------------\n");
    printf("\n");
    char ciphertext[] = "TTNAAPTMTSUOAODWCOIXKNLYPETZ";
    printf("ciphertext test: %s\n", ciphertext); // printing array text
    printf("\n");
    letterDecrypt(ciphertext, key, m); // length of text
    printf("\n");
    */

    char command[8];// Buffer for the command
    char inputText[1000]; // Buffer for the input text (PLAINTEXT or CIPHERTEXT)

    while (1)
    {
        if (scanf("%7s", command) != 1)
        { // Read the command
            return 1;
        }

        if (strcmp(command, "quit") == 0)
        {  // If the command is 'quit'
            return 0; // Exit the program
        }
        else if (strcmp(command, "encrypt") == 0)
        { // If the command is 'encrypt'
            scanf(" %[^\n]", inputText);   // Read the plaintext until a newline is encountered in console
            removingNonLetters(inputText); // Remove non-letters and convert to lowercase (above fn)
            int l = strlen(inputText);
            int n = (l + m - 1) / m; // Calculate number of rows
            char array2d[n][m]; // Defining  the 2D array
            LettersInArray(inputText, m, n, array2d); // Fill the 2D array
            // printf("Encrypted text: ");
            ciphertext(n, m, array2d, key); // Encrypt and print the ciphertext
        }
        else if (strcmp(command, "decrypt") == 0)
        { // If the command is 'decrypt'
            scanf(" %[^\n]", inputText); // Read the ciphertext until a newline is encountered
            // printf("Original text: ");
            letterDecrypt(inputText, key, m); // Decrypt and print the original text
        }
        else
        {
        // fprintf(stderr, "Invalid command.\n");
            return 1;
        }
    }
}
