#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int population;
    char Town[50];
    char District[50];
    struct node *next;
    struct node *pre;
};

struct node1
{
    char District[50];
    struct node *Town;
    struct node1 *next;
    struct node1 *pre;
};

struct node* MakeEmpty(struct node* L);
struct node1* MakeEmptyDistrict(struct node1* L);
int IsEmpty(struct node* L);
int IsEmptyDistrict(struct node1* L);
struct node* Find(int X, struct node* L);
struct node* FindPrevious(char town[], struct node* L);
struct node1* FindPreviousDistrict(char district[], struct node1* L);
void Delete(char town[], struct node* L);
void DeleteDistrict(char district[], struct node1* L);
void Insert(int X, char town[], char district[], struct node* L);
void InsertDistrict(char district[], struct node1* L);
void PrintList(struct node* L);
void PrintListDistricts(struct node1* L);
void DeleteList(struct node* L);
void DeleteListDistrict(struct node1* L);
int size(struct node* L);
int IsLast(struct node* P, struct node* L);
int IsLastDistrict(struct node1* P, struct node1* L);
void ReadFileAndStore(char *filename, struct node *head);
void printLikeFile(struct node1 * L);
void BuildDistrictsLinkedList(struct node1 * D, struct node * L);
void AddNewDistrict(struct node1 * L);
void AddNewTownToCertainDistrict(struct node * town, struct node1 * district);
void DeleteTownFromAspecificDistrict(struct node *town, struct node1 *district);
void DeleteCompleteDistrict(struct node *town, struct node1 *district);
void FindThePopulation(struct node * L);
void PrintDistrictsAndTheirPopulation(struct node1 * D);
void ChangeThePopulationofTown(struct node * L, struct node1 * D);
void SaveToOutputFile(struct node1 * D);
void SortingTownsInDistricts(struct node1 * D);
void PrintStoredInformation(struct node1* D);
int getMaxStringLength(struct node1* L);
void countingSort(struct node1** L, int pos);
void radixSort(struct node1** L);
int sizeDistrict(struct node1* L);


int main() {
    struct node* Towns = MakeEmpty(NULL);
    struct node1* Districts = MakeEmptyDistrict(NULL);
    int selection;
    char fileName[50];

    do {
        printf("\nMenu:\n");
        printf("1. Load the input file\n");
        printf("2. Print the loaded information before sorting\n");
        printf("3. Sort the districts alphabetically using Radix sort\n");
        printf("4. Sort the towns for each district based on population in ascending order\n");
        printf("5. Print the sorted information\n");
        printf("6. Add a new district to the list of sorted districts\n");
        printf("7. Add a new town to a certain district\n");
        printf("8. Delete a town from a specific district\n");
        printf("9. Delete a complete district\n");
        printf("10. Calculate the population of Palestine, the max and min town population\n");
        printf("11. Print the districts and their total population\n");
        printf("12. Change the population of a town, after prompting the user to enter the district name\n");
        printf("13. Save to output file\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1:{
                printf("Enter the name of the file.\n");
                scanf("%s", fileName);
                ReadFileAndStore(fileName, Towns);
                BuildDistrictsLinkedList(Districts, Towns);
            }

                break;
            case 2:
                {
                    printLikeFile(Districts);
                }
                break;
            case 3:
                {
                    radixSort(&Districts);
                }
                break;
            case 4:
                {
                    SortingTownsInDistricts(Districts);
                }
                break;
            case 5:
                {
                    PrintStoredInformation(Districts);
                }
                break;
            case 6:
                {
                    AddNewDistrict(Districts);
                }
                break;
            case 7:
                {
                    AddNewTownToCertainDistrict(Towns, Districts);
                }
                break;
            case 8:
                {
                    DeleteTownFromAspecificDistrict(Towns, Districts);
                }
                break;
            case 9:
                {
                    DeleteCompleteDistrict(Towns, Districts);
                }
                break;
            case 10:
                {
                    FindThePopulation(Towns);
                }
                break;
            case 11:
                {
                    PrintDistrictsAndTheirPopulation(Districts);
                }
                break;
            case 12:
                {
                    ChangeThePopulationofTown(Towns, Districts);
                }
                break;
            case 13:
                {
                    SaveToOutputFile(Districts);
                }
                break;
            case 14 :
                printf("\n\nExiting program...\n\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (selection != 14);

    return 0;
}

struct node* MakeEmpty(struct node* L)
{
    if(L != NULL)
        DeleteList(L);

    L = (struct node*)malloc(sizeof(struct node));

    if(L == NULL)
        printf("Out of memory!\n");

    L->next = NULL;
    L->pre = NULL;
    return L;
}

struct node1* MakeEmptyDistrict(struct node1* L)
{
    if(L != NULL)
        DeleteListDistrict(L);

    L = (struct node1*)malloc(sizeof(struct node1));

    if(L == NULL)
        printf("Out of memory!\n");

    L->next = NULL;
    L->pre = NULL;
    L->Town = MakeEmpty(NULL);
    return L;
}

int IsEmpty(struct node* L)
{
    return L->next == NULL;
}

int IsEmptyDistrict(struct node1* L)
{
    return L->next == NULL;
}

struct node* Find(int X, struct node* L)
{
    struct node* P;
    P = L->next;

    while(P != NULL && P->population != X)
        P = P->next;

    return P;
}

struct node* FindPrevious(char town[], struct node* L)
{
    struct node* P;
    P = L;

    while (P->next != NULL && strcmp(P->next->Town, town) != 0)
        P = P->next;

    return P;
}

struct node1* FindPreviousDistrict(char district[], struct node1* L)
{
    struct node1* P;
    P = L;

    while (P->next != NULL && strcmp(P->next->District, district) != 0)
        P = P->next;

    return P;
}

void Delete(char town[], struct node* L)
{
    struct node* P, *temp;
    P = FindPrevious(town, L);

    if(!IsLast(P, L))
    {
        temp = P->next;
        P->next = temp->next; //bypass delete cell
        if (temp->next != NULL)
            temp->next->pre = P;
        free(temp);
    }
}

void DeleteDistrict(char district[], struct node1* L)
{
    struct node1* P, *temp;
    P = FindPreviousDistrict(district, L);

    if(!IsLastDistrict(P, L))
    {
        temp = P->next;
        P->next = temp->next; //bypass delete cell
        if (temp->next != NULL)
            temp->next->pre = P;
        free(temp);
    }
}

void InsertDistrict(char district[], struct node1* L)
{
    // Create a new node
    struct node1* temp = (struct node1*)malloc(sizeof(struct node1));
    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Assign values to the new node
    temp->Town = MakeEmpty(NULL); // Assuming the Town field of a district node should be NULL
    strcpy(temp->District, district);

    // Make the new node the new head of the list
    temp->next = L->next;
    temp->pre = L;
    L->pre = NULL;
    L->next = temp;
}

void Insert(int X, char town[], char district[], struct node* L)
{
    // Create a new node
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Assign values to the new node
    temp->population = X;
    strcpy(temp->Town, town);
    strcpy(temp->District, district);

    // Make the new node the new head of the list
    temp->next = L->next;
    L->next = temp;
    temp->pre = L;
    L->pre = NULL;
}

void PrintList(struct node* L)
{
    struct node* P = L;
    if(IsEmpty(L))
        printf("Empty list\n");
    else
    {
        do
        {
            P = P->next;

        } while(!IsLast(P, L));
    }
}

void DeleteList(struct node* L)
{
    struct node* P, *temp;
    P = L->next;
    L->next = NULL;

    while(P != NULL)
    {
        temp = P->next;
        free(P);
        P = temp;
    }
}

void DeleteListDistrict(struct node1* L)
{
    struct node1* P, *temp;
    P = L->next;
    L->next = NULL;

    while(P != NULL)
    {
        temp = P->next;
        free(P);
        P = temp;
    }
}

int size(struct node* L)
{
    struct node* p = L->next;
    int count = 0;
    while(p != NULL)
    {
        count += 1;
        p = p->next;
    }
    return count;
}

int IsLast(struct node* P, struct node* L)
{
    return P->next == NULL;
}

int IsLastDistrict(struct node1* P, struct node1* L)
{
    return P->next == NULL;
}

void ReadFileAndStore(char *filename, struct node *head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file %s.\n", filename);
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, "|");
        if (token == NULL)
            continue; // Skip empty lines

        // Trim leading and trailing spaces from the district token
        char district[50];
        int i = 0;
        while (*token != '\0' && *token == ' ')
            token++;
        while (*token != '\0' && *token != '|')
            district[i++] = *token++;
        while (i > 0 && district[i - 1] == ' ')
            i--;
        district[i] = '\0';

        token = strtok(NULL, "|");
        if (token == NULL)
            continue; // Skip invalid lines

        // Trim leading and trailing spaces from the town token
        char town[50];
        i = 0;
        while (*token != '\0' && *token == ' ')
            token++;
        while (*token != '\0' && *token != '|')
            town[i++] = *token++;
        while (i > 0 && town[i - 1] == ' ')
            i--;
        town[i] = '\0';

        token = strtok(NULL, "|");
        if (token == NULL)
            continue; // Skip invalid lines

        // Convert population to integer and skip any leading spaces
        int population = atoi(token);

        // Insert data into the linked list
        Insert(population, town, district, head);
    }

    fclose(file);
}

void printLikeFile(struct node1 * L)
{
    struct node1 *currentDistrict = L->next;
    while (currentDistrict != NULL) {
        struct node *currentTown = currentDistrict->Town->next;
        while(currentTown != NULL)
        {
            printf("%s | %s | %d\n", currentTown->District, currentTown->Town, currentTown->population);
            currentTown = currentTown->next;
        }
        currentDistrict = currentDistrict->next;
    }
}

void BuildDistrictsLinkedList(struct node1 *D, struct node *L) {
    struct node *current = L->next;

    // Traverse the main linked list
    while (current != NULL) {
        // Check if the district already exists in the district linked list
        struct node1 *tempDistrict = D->next; // Start from the first district node
        int districtExists = 0; // Flag to check if district exists

        while (tempDistrict != NULL) {
            if (strcmp(current->District, tempDistrict->District) == 0) {
                districtExists = 1; // District found
                break;
            }
            tempDistrict = tempDistrict->next;
        }

        // If the district doesn't exist, insert it into the district linked list
        if (!districtExists) {
            (current->District, D);
        }
        tempDistrict = D->next;
        current = current->next;
    }

    // Traverse the main linked list again to add towns to districts
    current = L->next;
    while (current != NULL) {
        struct node1 *tempDistrict = D->next; // Start from the first district node
        // Find the district node corresponding to the current town
        while (tempDistrict != NULL) {
            if (strcmp(current->District, tempDistrict->District) == 0) {
                // Insert a new town node into the district's town linked list
                Insert(current->population, current->Town, current->District, tempDistrict->Town);
                break;
            }
            tempDistrict = tempDistrict->next;
        }
        current = current->next;
    }
}

void AddNewDistrict(struct node1 * L)
{
    char district[50];
    int flag = 0;
    printf("\nEnter the name of the District.\n");
    scanf("%s", district);
    struct node1 *tempDistrict = L->next;
    while (tempDistrict != NULL) {
        if (strcmp(district, tempDistrict->District) == 0) {
            flag = 1;
            break;
        }
       tempDistrict = tempDistrict->next;
    }
    if(flag == 0)
    {
        InsertDistrict(district, L);
        printf("The District has been added.\n");
    }
    else
    {
        printf("The District is already exist.\n");
    }

}

void AddNewTownToCertainDistrict(struct node *town, struct node1 *district) {
    char districtName[50];
    char townName[50];
    int population, flag = 0;

    printf("Enter The District which new town belongs to:\n");
    scanf("%s", districtName);

    printf("Enter the name of the new town:\n");
    scanf("%s", townName);

    printf("Enter the population of the town:\n");
    scanf("%d", &population);

    // Traverse the district linked list to find the specified district
    struct node1 *tempDistrict = district->next;
    while (tempDistrict != NULL) {
        if (strcmp(districtName, tempDistrict->District) == 0) {
            flag = 1;
            break;
        }
       tempDistrict = tempDistrict->next;
    }

    if(flag == 1)
    {
        struct node * tempTown = tempDistrict->Town->next;
        while(tempTown != NULL)
        {
            if (strcmp(townName, tempTown->Town) == 0) {
            flag = 2;
            printf("The Town is already exist.\n");
            break;
            }
            tempTown = tempTown->next;
        }
    }
    if (flag == 1)
    {
        Insert(population, townName, districtName, tempDistrict->Town);
        Insert(population, townName, districtName, town);
        printf("\nThe Town has been added.\n");
    }
    // If the district doesn't exist, print a message
    if (flag == 0)
    {
        printf("\nThe District does not exist.\n");
    }
}

void DeleteTownFromAspecificDistrict(struct node *town, struct node1 *district)
{
    char districtName[50];
    char townName[50];
    int flag = 0;

    printf("Enter The District which town belongs to:\n");
    scanf("%s", districtName);

    printf("Enter the name of the town:\n");
    scanf("%s", townName);

    struct node1 *tempDistrict = district->next;
    while (tempDistrict != NULL) {
            struct node *tempTown = tempDistrict->Town->next;
        if (strcmp(districtName, tempDistrict->District) == 0) {
            flag = 1;
            while(tempTown != NULL)
            {
                if (strcmp(townName, tempTown->Town) == 0)
                {
                    flag = 2;
                    break;
                }
                tempTown = tempTown->next;
            }
            break;
        }
       tempDistrict = tempDistrict->next;
    }

    // If the district doesn't exist, print a message
    if (flag == 2)
    {
        printf("\nThe Town has been deleted.\n");
        Delete(townName, tempDistrict->Town);
        Delete(townName, town);
    }
    else if (flag == 1)
    {
        printf("\nThe Town does not exist.\n");
    }
    else
    {
        printf("\nThe District does not exist.\n");
    }

}

void DeleteCompleteDistrict(struct node *town, struct node1 *district)
{
    char districtName[50];
    int flag = 0;

    printf("Enter the name of the District:\n");
    scanf("%s", districtName);

    struct node1 *tempDistrict = district->next;
    while (tempDistrict != NULL) {
        if (strcmp(districtName, tempDistrict->District) == 0) {
            flag = 1;
            break;
        }
       tempDistrict = tempDistrict->next;
    }

    if(flag == 1)
    {
        struct node *current = town->next;
        while(current != NULL)
        {
            if(strcmp(current->District, tempDistrict->District) == 0)
            {
                Delete(current->Town, town);
                current = town->next;
                continue;
            }
            current = current->next;
        }
        DeleteList(tempDistrict->Town);
        DeleteDistrict(districtName, district);
        printf("\nThe District has been deleted\n");
    }
    else
    {
        printf("\nThe District does not exist.\n");
    }

}

void FindThePopulation(struct node * L)
{
    struct node *current = L->next;
    int TotalPopulation = 0;
    int max = current->population, min = current->population;
    char MinTown[50];
    char MaxTown[50];

    strcpy(MinTown, current->Town);
    strcpy(MaxTown, current->Town);

    while(current != NULL)
    {
        TotalPopulation += current->population;
        if(current->population > max)
        {
            max = current->population;
            strcpy(MaxTown, current->Town);
        }
        if(current->population < min)
        {
            min = current->population;
            strcpy(MinTown, current->Town);
        }

        current = current->next;
    }

    printf("\nThe population of Palestine is : %d\n", TotalPopulation);
    printf("Town %s has the maximum population in Palestine (%d).\n",MaxTown, max);
    printf("Town %s has the minimum population in Palestine (%d).\n",MinTown, min);
}

void PrintDistrictsAndTheirPopulation(struct node1 * D)
{
    int DistrictPopulation = 0;
    struct node1 * tempDistrict = D->next;
    printf("\n");
    while(tempDistrict != NULL)
    {
        struct node * tempTown = tempDistrict->Town->next;
        while(tempTown != NULL)
        {
            DistrictPopulation += tempTown->population;
            tempTown = tempTown->next;
        }
        printf("%s District, Population = %d\n", tempDistrict->District, DistrictPopulation);
        tempDistrict = tempDistrict->next;
        DistrictPopulation = 0;
    }
}

void ChangeThePopulationofTown(struct node * L, struct node1 * D)
{
    char districtName[50];
    char townName[50];
    int NewPopulation = 0;
    int flag = 0;

    printf("Enter the name of the District which the town belongs to.\n");
    scanf("%s", districtName);

    struct node1 * tempDistrict = D->next;

    while(tempDistrict != NULL)
    {
        if(strcmp(tempDistrict->District, districtName) == 0)
        {
            flag = 1;
            break;
        }
        tempDistrict = tempDistrict->next;
    }
    PrintList(tempDistrict->Town);

    if(flag == 1)
    {
        printf("Enter the name of the Town : ");
        scanf("%s", townName);
        struct node * tempTown = tempDistrict->Town->next;
        while(tempTown != NULL)
        {
            if(strcmp(tempTown->Town, townName) == 0)
            {
                flag = 2;
                break;
            }
            tempTown = tempTown->next;
        }
    }
    if(flag == 2)
    {
        printf("Enter the new population : ");
        scanf("%d", &NewPopulation);
        struct node * current = L->next;
        while(current != NULL)
        {
            if(strcmp(townName, current->Town) == 0)
            {
                Delete(townName, L);
                Delete(townName, tempDistrict->Town);
                break;
            }
            current = current->next;
        }
        Insert(NewPopulation, townName, current->District, L);
        Insert(NewPopulation, townName, current->District, tempDistrict->Town);
        printf("The Population has been changed.\n");
    }
    else if(flag == 1)
    {
        printf("The town %s does not exist.\n", townName);
    }
    else
        printf("The district %s does not exist.\n", districtName);
}

void SaveToOutputFile(struct node1 * D)
{
    FILE *output = fopen("Output.txt", "w");
    if (output == NULL) {
        printf("Unable to open the output file.\n");
        exit(1);
    }

    int DistrictPopulation = 0;
    struct node1 * tempDistrict = D->next;
    while(tempDistrict != NULL)
    {
        struct node * tempTown = tempDistrict->Town->next;
        while(tempTown != NULL)
        {
            DistrictPopulation += tempTown->population;
            tempTown = tempTown->next;
        }
        fprintf(output, "%s District, Population = %d\n", tempDistrict->District, DistrictPopulation);
        tempTown = tempDistrict->Town->next;
        while(tempTown != NULL)
        {
            fprintf(output, "%s, %d\n", tempTown->Town, tempTown->population);
            tempTown = tempTown->next;
        }
        tempDistrict = tempDistrict->next;
        DistrictPopulation = 0;
    }
    fclose(output);

    printf("The Data has been saved.\n");

}

void SortingTownsInDistricts(struct node1 * D) {
    // Iterate through each district
    struct node1 *tempDistrict = D->next;
    while(tempDistrict != NULL) {
        int swapped;
        do {
            swapped = 0;
            struct node *current = tempDistrict->Town->next; // Start with the first town in the district

            while(current != NULL && current->next != NULL) {
                // Compare the population of the current town and the next town
                if (current->population > current->next->population) {
                    // Swap the towns if they are in the wrong order
                    int tempPopulation = current->population;
                    current->population = current->next->population;
                    current->next->population = tempPopulation;

                    char tempTown[50];
                    strcpy(tempTown, current->Town);
                    strcpy(current->Town, current->next->Town);
                    strcpy(current->next->Town, tempTown);

                    char tempDistrict[50];
                    strcpy(tempDistrict, current->District);
                    strcpy(current->District, current->next->District);
                    strcpy(current->next->District, tempDistrict);

                    swapped = 1; // Indicate that a swap has occurred
                }
                current = current->next; // Move to the next pair of towns
            }
        } while(swapped); // Keep sorting until no swaps occur

        tempDistrict = tempDistrict->next; // Move to the next district
    }
    printf("The Towns has been sorted.\n");
}

void PrintStoredInformation(struct node1* D)
{
    int DistrictPopulation = 0;
    struct node1 * tempDistrict = D->next;
    while(tempDistrict != NULL)
    {
        struct node * tempTown = tempDistrict->Town->next;
        while(tempTown != NULL)
        {
            DistrictPopulation += tempTown->population;
            tempTown = tempTown->next;
        }
        printf("%s District, Population = %d\n", tempDistrict->District, DistrictPopulation);
        tempTown = tempDistrict->Town->next;
        while(tempTown != NULL)
        {
            printf("%s, %d\n", tempTown->Town, tempTown->population);
            tempTown = tempTown->next;
        }
        tempDistrict = tempDistrict->next;
        DistrictPopulation = 0;
    }
}

int getMaxStringLength(struct node1* L) {
    int maxLength = 0;
    struct node1* current = L->next;
    while (current != NULL) {
        int length = strlen(current->District);
        if (length > maxLength) {
            maxLength = length;
        }
        current = current->next;
    }
    return maxLength;
}

void countingSort(struct node1** L, int pos) {
    int count[256] = {0}; // Assuming ASCII characters
    struct node1* output[sizeDistrict(*L)]; // Output array to store sorted elements
    memset(output, 0, sizeof(output));

    // Calculate count of characters
    struct node1* temp = (*L)->next;
    while (temp != NULL) {
        int index = strlen(temp->District) - pos - 1;
        char ch = (index >= 0) ? temp->District[index] : 0; // Pad with 0 if pos is outside the string
        count[(int)ch]++;
        temp = temp->next;
    }

    // Change count[i] to contain actual position of this character in output
    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    temp = (*L)->next;
    while (temp != NULL) {
        int index = strlen(temp->District) - pos - 1;
        char ch = (index >= 0) ? temp->District[index] : 0; // Pad with 0 if pos is outside the string
        output[count[(int)ch] - 1] = temp;
        count[(int)ch]--;
        temp = temp->next;
    }

    // Copy the output array to L, so that L contains sorted names according to the current character
    struct node1* current = *L;
    for (int i = 0; i < sizeDistrict(*L); i++) {
        current->next = output[i];
        output[i]->pre = current;
        current = current->next;
    }
    current->next = NULL; // End the list
}

void radixSort(struct node1** L) {
    int maxLength = getMaxStringLength(*L);

    for (int pos = 0; pos < maxLength; pos++) {
        countingSort(L, pos);
    }
}

int sizeDistrict(struct node1* L) {
    int count = 0;
    struct node1* temp = L->next; // Assuming L is a dummy header
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}


