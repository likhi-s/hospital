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
            printf("1. Register patient\n2. Update patient details\n3. Display Available Patients\n4. Search Patient by ID\n5. Search Patient by Name\n6. Sort By ID\n7. Exit from Patient management\n");
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
            case SORT_BY_PATIENT_ID:
                sortPatientsById();
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
            case UPDATE_PATIENT_NAME:
                printf("Enter New Patient Name: ");
                scanf(" %[^\n]", patientTemp->patientName);
                break;
            case UPDATE_PATIENT_GENDER:
                printf("Enter New Gender: ");
                scanf("%s", patientTemp->patientGender);
                break;
            case UPDATE_PATIENT_AGE:
                printf("Enter New Age: ");
                scanf("%d", &patientTemp->patientAge);
                break;
            case UPDATE_PATIENT_ADDRESS:
                printf("Enter New Address: ");
                scanf(" %[^\n]", patientTemp->patientAddress);
                break;
            case UPDATE_PATIENT_CONTACT_NUMBER:
                printf("Enter New Contact Number: ");
                scanf("%s", patientTemp->patientContactNumber);
                break;
            case UPDATE_PATIENT_EMERGENCY_CONTACT_NUMBER:
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
    printf("--- Patient Sorted by Name ---\n");
    while (patientTemp != NULL)
    {
        printf("Patient ID: %d\n", patientTemp->patientId);
        printf("Name: %s\n", patientTemp->patientName);
        printf("Gender: %s\n", patientTemp->patientGender);
        printf("Age: %d\n", patientTemp->patientAge);
        printf("Address: %s\n", patientTemp->patientAddress);
        printf("Contact Number: %s\n", patientTemp->patientContactNumber);
        printf("Emergency Contact Number: %s\n", patientTemp->patientEmergencyContactNumber);
        printf("\n");
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
            printf("--- Patient Found ---\n");
            printf("Name: %s\n", patientTemp->patientName);
            printf("Gender: %s\n", patientTemp->patientGender);
            printf("Age: %d\n", patientTemp->patientAge);
            printf("Address: %s\n", patientTemp->patientAddress);
            printf("Contact Number: %s\n", patientTemp->patientContactNumber);
            printf("Emergency Contact Number: %s\n", patientTemp->patientEmergencyContactNumber);
            printf("\n");
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
            printf("--- Patient Found ---\n");
            printf("Patient ID: %d\n", patientTemp->patientId);
            printf("Name: %s\n", patientTemp->patientName);
            printf("Gender: %s\n", patientTemp->patientGender);
            printf("Age: %d\n", patientTemp->patientAge);
            printf("Address: %s\n", patientTemp->patientAddress);
            printf("Contact Number: %s\n", patientTemp->patientContactNumber);
            printf("Emergency Contact Number: %s\n", patientTemp->patientEmergencyContactNumber);
            printf("\n");
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

void sortPatientsById()

{
    if (patientHead == NULL)
    {
        printf("No patients found.\n");
        return;
    }


    patient *tempHead = NULL, *tempTail = NULL, *current = patientHead;

    while (current != NULL)
    {

        patient *newNode = (patient *)malloc(sizeof(patient));
        if (!newNode)
        {
            printf("Memory allocation failed\n");
            return;
        }

        *newNode = *current;
        newNode->next = NULL;

        if (tempHead == NULL)
        {
            tempHead = newNode;
            tempTail = newNode;
        }
        else
        {
            tempTail->next = newNode;
            tempTail = newNode;
        }

        current = current->next;
    }

    patient *sortedList = NULL;

    patient *splitList(patient *head)
    {
        patient *slow = head, *fast = head->next;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        patient *middle = slow->next;
        slow->next = NULL;
        return middle;
    }

    patient *mergeLists(patient *left, patient *right)
    {
        patient dummy;
        patient *tail = &dummy;
        dummy.next = NULL;

        while (left != NULL && right != NULL)
        {
            if (left->patientId < right->patientId)
            {
                tail->next = left;
                left = left->next;
            }
            else
            {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }
        tail->next = (left != NULL) ? left : right;
        return dummy.next;
    }

    patient *mergeSort(patient *head)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }

        patient *middle = splitList(head);
        patient *left = mergeSort(head);
        patient *right = mergeSort(middle);
        return mergeLists(left, right);
    }

    sortedList = mergeSort(tempHead);


    printf("--- Patients Sorted by ID ---\n");
    patient *temp = sortedList;
    while (temp != NULL)
    {
        printf("Patient ID: %d\n", temp->patientId);
        printf("Name: %s\n", temp->patientName);
        printf("Gender: %s\n", temp->patientGender);
        printf("Age: %d\n", temp->patientAge);
        printf("Address: %s\n", temp->patientAddress);
        printf("Contact Number: %s\n", temp->patientContactNumber);
        printf("Emergency Contact Number: %s\n", temp->patientEmergencyContactNumber);
        printf("\n");
        temp = temp->next;
    }

    while (sortedList != NULL)
    {
        patient *temp = sortedList;
        sortedList = sortedList->next;
        free(temp);
    }
}
