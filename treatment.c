#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "treatment.h"
#define USER_ID "treatment_user"
#define USER_PASSWORD "treatment@123"

treatment *treatmentHead = NULL ;
treatment *treatmentNode,*treatmentTemp;
void loginAsTreatmentAndPriceManagementUser()
{
    char userId[15];
    char userPass[15];
    int option;

    printf("User Id:\n");
    scanf(" %[^\n]", userId);
    printf("User Password:\n");
    scanf(" %[^\n]", userPass);

    if (strcmp(userId, USER_ID) == 0 && strcmp(userPass, USER_PASSWORD) == 0)
    {
        while (true)
        {
            printf("\n--- Treatment Management System ---\n");
            printf("1. Add Treatment\n2. Update Treatment Details\n3. Display All Treatments\n4. Search Treatment by ID\n5. Search Treatment by Name\n6. Exit Treatment Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_TREATMENT:
                addTreatment();
                //saveData();
                break;
            case UPDATE_TREATMENT_DETAILS:
                updateTreatmentDetails();
                //saveData();
                break;
            case DISPLAY_ALL_TREATMENTS:
                displayTreatment();
                break;
            case SEARCH_TREATMENT_BY_ID:
                searchByTreatmentId();
                break;
            case SEARCH_TREATMENT_BY_NAME:
                searchByTreatmentName();
                break;
            case EXIT_TREATMENT_MANAGEMENT:
                printf("Exiting from Treatment Management menu.\n");
                return;
            default:
                printf("Invalid choice, try again\n");
                break;
            }
        }
    }
    else
    {
        printf("Invalid User ID or Password!\n");
    }
}

void addTreatment()
{
    treatment *treatmentNode = (treatment *)malloc(sizeof(treatment));
    if (!treatmentNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    treatmentNode->next  = NULL;


    printf("Enter Treatment ID: ");
    scanf("%d", &treatmentNode->treatmentId);

    treatmentTemp = treatmentHead;
    int idExists = 0;
    while (treatmentTemp != NULL)
    {
        if (treatmentTemp->treatmentId == treatmentNode->treatmentId)
        {
            idExists = 1;
            break;
        }
        treatmentTemp = treatmentTemp->next;
    }

    if (idExists)
    {
        printf("Treatment with ID %d already exists....try again\n", treatmentNode->treatmentId);
        free(treatmentNode);
        addTreatment();
    }
    else
    {
        printf("Enter Treatment Name: ");
        scanf(" %[^\n]", treatmentNode->treatmentName);
        printf("Enter Treatment Cost: ");
        scanf("%d", &treatmentNode->treatmentCost);
        printf("Enter Treatment Duration (in days): ");
        scanf("%d", &treatmentNode->treatmentDuration);

        if (treatmentHead == NULL|| strcasecmp(treatmentHead->treatmentName, treatmentNode->treatmentName) > 0)
        {
            treatmentNode->next = treatmentHead;
            treatmentHead = treatmentNode;
        }
        else
        {
            treatmentTemp = treatmentHead;

            while(treatmentTemp->next != NULL&& strcasecmp(treatmentTemp->next->treatmentName, treatmentNode->treatmentName) < 0)
            {
                treatmentTemp = treatmentTemp->next;
            }
            treatmentNode->next = treatmentTemp->next;
            treatmentTemp->next = treatmentNode;
        }
        printf("treatment registered successfully!\n");

    }
}

void updateTreatmentDetails()
{
    int id, choice;
    printf("Enter Treatment ID to update: ");
    scanf("%d", &id);

    treatmentTemp = treatmentHead;
    int treatmentFound = 0;

    while (treatmentTemp != NULL)
    {
        if (treatmentTemp->treatmentId == id)
        {
            treatmentFound = 1;

            printf("Updating details for %s...\n", treatmentTemp->treatmentName);
            printf("Which details do you want to update?\n");
            printf("1. Update Treatment Name\n2. Update Treatment Cost\n3. Update Treatment Duration\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_TREATMENT_NAME:
                printf("Enter New Treatment Name: ");
                scanf(" %[^\n]", treatmentTemp->treatmentName);
                break;
            case UPDATE_TREATMENT_COST:
                printf("Enter New Treatment Cost: ");
                scanf("%d", &treatmentTemp->treatmentCost);
                break;
            case UPDATE_TREATMENT_DURATION:
                printf("Enter New Treatment Duration (in days): ");
                scanf("%d", &treatmentTemp->treatmentDuration);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Required treatment details updated successfully.\n");
            break;
        }
        treatmentTemp = treatmentTemp->next;
    }

    if (!treatmentFound)
    {
        printf("Treatment with ID %d not found.\n", id);
    }
}

void displayTreatment()
{
    if (treatmentHead == NULL)
    {
        printf("No treatments found.\n");
        return;
    }

    treatmentTemp = treatmentHead;
    printf("\n--- Treatment Details ---\n");
    while (treatmentTemp != NULL)
    {
        printf("Treatment ID: %d\n", treatmentTemp->treatmentId);
        printf("Name: %s\n", treatmentTemp->treatmentName);
        printf("Cost: %d\n", treatmentTemp->treatmentCost);
        printf("Duration: %d days\n", treatmentTemp->treatmentDuration);
        treatmentTemp = treatmentTemp->next;
    }
}

void searchByTreatmentId()
{
    int id;
    printf("Enter Treatment ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    treatmentTemp = treatmentHead;
    while (treatmentTemp != NULL)
    {
        if (treatmentTemp->treatmentId == id)
        {
            printf("\n--- Treatment Found ---\n");
            printf("Name: %s\n", treatmentTemp->treatmentName);
            printf("Cost: %d\n", treatmentTemp->treatmentCost);
            printf("Duration: %d days\n", treatmentTemp->treatmentDuration);
            searchIdFound = 1;
            break;
        }
        treatmentTemp = treatmentTemp->next;
    }
    if (!searchIdFound)
    {
        printf("Treatment with ID %d not found.\n", id);
    }
}

void searchByTreatmentName()
{
    char searchName[100];
    printf("Enter Treatment Name to search: ");
    scanf(" %[^\n]", searchName);

    treatmentTemp = treatmentHead;
    int searchNameFound = 0;

    while (treatmentTemp != NULL)
    {
        if (strcasecmp(searchName, treatmentTemp->treatmentName) == 0)
        {
            printf("\n--- Treatment Found ---\n");
            printf("Treatment ID: %d\n", treatmentTemp->treatmentId);
            printf("Cost: %d\n", treatmentTemp->treatmentCost);
            printf("Duration: %d days\n", treatmentTemp->treatmentDuration);
            searchNameFound = 1;
            break;
        }
        treatmentTemp = treatmentTemp->next;
    }

    if (!searchNameFound)
    {
        printf("Treatment with Name '%s' not found.\n", searchName);
    }
}

