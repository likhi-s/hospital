#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "patient.h"
#define USER_ID "patient_user"
#define USER_PASSWORD "patient@123"

patient *patientHead = NULL;
patient *patientTemp, *patientNode;

void loginAsPatientManagementUser()
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
            printf("\n--- Patient Management System ---\n");
            printf("1. Register patient\n2. Update patient details\n3. Display Available Patients\n4. Search Patient by ID\n5. Search Patient by Name\n6. Exit from Patient management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case REGISTER_PATIENT:
                registerPatient();
                break;
            case UPDATE_PATIENT_DETAILS:
                updatePatientDetails();
                break;
            case DISPLAY_AVAILABLE_PATIENTS:
                displayPatientDetails();
                break;
            case SEARCH_PATIENT_BY_ID:
                searchByPatientId();
                break;
            case SEARCH_PATIENT_BY_NAME:
                searchByPatientName();
                break;
            case EXIT_PATIENT_MANAGEMENT:
                printf("Exiting from Patient Management menu.\n");
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

void registerPatient()
{
    patient *patientNode = (patient *)malloc(sizeof(patient));
    if (!patientNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    patientNode->next = NULL;

    printf("Enter Patient ID: ");
    scanf("%d", &patientNode->patientId);

    patientTemp = patientHead;
    int idExists = 0;
    while (patientTemp != NULL)
    {
        if (patientTemp->patientId == patientNode->patientId)
        {
            idExists = 1;
            break;
        }
        patientTemp = patientTemp->next;
    }

    if (idExists)
    {
        printf("Patient with ID %d already exists....try again\n", patientNode->patientId);
        free(patientNode);
        registerPatient();
    }
    else
    {
        printf("Enter Patient Name: ");
        scanf(" %[^\n]", patientNode->patientName);
        printf("Enter Gender: ");
        scanf("%s", patientNode->patientGender);
        printf("Enter Age: ");
        scanf("%d", &patientNode->patientAge);
        printf("Enter Address: ");
        scanf(" %[^\n]", patientNode->patientAddress);
        printf("Enter Contact Number: ");
        scanf("%s", patientNode->patientContactNumber);
        printf("Enter Emergency Contact Number: ");
        scanf("%s", patientNode->patientEmergencyContactNumber);

        if (patientHead == NULL || strcasecmp(patientHead->patientName, patientNode->patientName) > 0)
        {
            patientNode->next = patientHead;
            patientHead = patientNode;
        }
        else
        {
            patientTemp = patientHead;
            while (patientTemp->next != NULL && strcasecmp(patientTemp->next->patientName, patientNode->patientName) < 0)
            {
                patientTemp = patientTemp->next;
            }
            patientNode->next = patientTemp->next;
            patientTemp->next = patientNode;
        }
        printf("Patient registered successfully!\n");
    }
}

void updatePatientDetails()
{
    int id, choice;
    printf("Enter Patient ID to update: ");
    scanf("%d", &id);

    patientTemp = patientHead;
    int patientFound = 0;

    while (patientTemp != NULL)
    {
        if (patientTemp->patientId == id)
        {
            patientFound = 1;

            printf("Updating details for %s...\n", patientTemp->patientName);
            printf("Which details do you want to update?\n");
            printf("1. Update Patient Name\n2. Update Gender\n3. Update Age\n4. Update Address\n5. Update Contact Number\n6. Update Emergency Contact Number\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Enter New Patient Name: ");
                scanf(" %[^\n]", patientTemp->patientName);
                break;
            case 2:
                printf("Enter New Gender: ");
                scanf("%s", patientTemp->patientGender);
                break;
            case 3:
                printf("Enter New Age: ");
                scanf("%d", &patientTemp->patientAge);
                break;
            case 4:
                printf("Enter New Address: ");
                scanf(" %[^\n]", patientTemp->patientAddress);
                break;
            case 5:
                printf("Enter New Contact Number: ");
                scanf("%s", patientTemp->patientContactNumber);
                break;
            case 6:
                printf("Enter New Emergency Contact Number: ");
                scanf("%s", patientTemp->patientEmergencyContactNumber);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Required patient details updated successfully.\n");
            break;
        }
        patientTemp = patientTemp->next;
    }

    if (!patientFound)
    {
        printf("Patient with ID %d not found.\n", id);
    }
}

void displayPatientDetails()
{
    if (patientHead == NULL)
    {
        printf("No patients found.\n");
        return;
    }

    patientTemp = patientHead;
    printf("\n--- Patient Details ---\n");
    while (patientTemp != NULL)
    {
        printf("Patient ID: %d\n", patientTemp->patientId);
        printf("Name: %s\n", patientTemp->patientName);
        printf("Gender: %s\n", patientTemp->patientGender);
        printf("Age: %d\n", patientTemp->patientAge);
        printf("Address: %s\n", patientTemp->patientAddress);
        printf("Contact Number: %s\n", patientTemp->patientContactNumber);
        printf("Emergency Contact Number: %s\n", patientTemp->patientEmergencyContactNumber);
        patientTemp = patientTemp->next;
    }
}

void searchByPatientId()
{
    int id;
    printf("Enter Patient ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    patientTemp = patientHead;
    while (patientTemp != NULL)
    {
        if (patientTemp->patientId == id)
        {
            printf("\n--- Patient Found ---\n");
            printf("Name: %s\n", patientTemp->patientName);
            printf("Gender: %s\n", patientTemp->patientGender);
            printf("Age: %d\n", patientTemp->patientAge);
            printf("Address: %s\n", patientTemp->patientAddress);
            printf("Contact Number: %s\n", patientTemp->patientContactNumber);
            printf("Emergency Contact Number: %s\n", patientTemp->patientEmergencyContactNumber);
            searchIdFound = 1;
            break;
        }
        patientTemp = patientTemp->next;
    }
    if (!searchIdFound)
    {
        printf("Patient with ID %d not found.\n", id);
    }
}

void searchByPatientName()
{
    char searchName[50];
    printf("Enter Patient Name to search: ");
    scanf(" %[^\n]", searchName);

    patientTemp = patientHead;
    int searchNameFound = 0;

    while (patientTemp != NULL)
    {
        if (strcasecmp(searchName, patientTemp->patientName) == 0)
        {
            printf("\n--- Patient Found ---\n");
            printf("Patient ID: %d\n", patientTemp->patientId);
            printf("Name: %s\n", patientTemp->patientName);
            printf("Gender: %s\n", patientTemp->patientGender);
            printf("Age: %d\n", patientTemp->patientAge);
            printf("Address: %s\n", patientTemp->patientAddress);
            printf("Contact Number: %s\n", patientTemp->patientContactNumber);
            printf("Emergency Contact Number: %s\n", patientTemp->patientEmergencyContactNumber);
            searchNameFound = 1;
            break;
        }
        patientTemp = patientTemp->next;
    }

    if (!searchNameFound)
    {
        printf("Patient with Name '%s' not found.\n", searchName);
    }
}
