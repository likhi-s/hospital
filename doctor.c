#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "doctor.h"

#define USER_ID "doctor_user"
#define USER_PASSWORD "doctor@123"

doctor *doctorHead = NULL;
doctor *doctorTemp, *doctorNode;

void loginAsDoctorManagementUser()
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
            printf("\n--- Doctor Management System ---\n");
            printf("1. Register Doctor\n2. Update Doctor Details\n3. Display Available Doctors\n4. Search Doctor by ID\n5. Search Doctor by Specialization\n6. Sort Doctors by ID\n7. Exit from Doctor Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_DOCTOR:
                registerDoctor();
                break;
            case UPDATE_DOCTOR_DETAILS:
                updateDoctorDetails();
                break;
            case DISPLAY_AVAILABLE_DOCTORS:
                displayDoctorDetails();
                break;
            case SEARCH_DOCTOR_BY_ID:
                searchByDoctorId();
                break;
            case SEARCH_DOCTOR_BY_SPECIALIZATION:
                searchByDoctorSpecialization();
                break;
            case SORT_DOCTORS_BY_ID:
                sortDoctorsById();
                break;
            case EXIT_DOCTOR_MANAGEMENT:
                printf("Exiting from Doctor Management menu.\n");
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

void registerDoctor()
{
    doctor *doctorNode = (doctor *)malloc(sizeof(doctor));
    if (!doctorNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    doctorNode->next = NULL;

    printf("Enter Doctor ID: ");
    scanf("%d", &doctorNode->doctorId);

    doctorTemp = doctorHead;
    int idExists = 0;
    while (doctorTemp != NULL)
    {
        if (doctorTemp->doctorId == doctorNode->doctorId)
        {
            idExists = 1;
            break;
        }
        doctorTemp = doctorTemp->next;
    }

    if (idExists)
    {
        printf("Doctor with ID %d already exists....try again\n", doctorNode->doctorId);
        free(doctorNode);
        registerDoctor();
    }
    else
    {
        printf("Enter Doctor Name: ");
        scanf(" %[^\n]", doctorNode->doctorName);
        printf("Enter Specialization: ");
        scanf(" %[^\n]", doctorNode->doctorSpecialization);
        printf("Enter Consultation Fee: ");
        scanf("%f", &doctorNode->doctorConsultationFee);
        printf("Enter Contact Number: ");
        scanf("%s", doctorNode->doctorContactNumber);
        printf("Enter Experience (years): ");
        scanf("%d", &doctorNode->doctorExperience);
        printf("Enter Qualification: ");
        scanf(" %[^\n]", doctorNode->doctorQualification);

        if (doctorHead == NULL || strcasecmp(doctorHead->doctorName, doctorNode->doctorName) > 0)
        {
            doctorNode->next = doctorHead;
            doctorHead = doctorNode;
        }
        else
        {
            doctorTemp = doctorHead;
            while (doctorTemp->next != NULL && strcasecmp(doctorTemp->next->doctorName, doctorNode->doctorName) < 0)
            {
                doctorTemp = doctorTemp->next;
            }
            doctorNode->next = doctorTemp->next;
            doctorTemp->next = doctorNode;
        }
        printf("Doctor registered successfully!\n");
    }
}

void updateDoctorDetails()
{
    int id, choice;
    printf("Enter Doctor ID to update: ");
    scanf("%d", &id);

    doctorTemp = doctorHead;
    int doctorFound = 0;

    while (doctorTemp != NULL)
    {
        if (doctorTemp->doctorId == id)
        {
            doctorFound = 1;

            printf("Updating details for %s...\n", doctorTemp->doctorName);
            printf("Which details do you want to update?\n");
            printf("1. Update Name\n2. Update Specialization\n3. Update Consultation Fee\n4. Update Contact Number\n5. Update Experience\n6. Update Qualification\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_DOCTOR_NAME:
                printf("Enter New Doctor Name: ");
                scanf(" %[^\n]", doctorTemp->doctorName);
                break;
            case UPDATE_DOCTOR_SPECIALIZATION:
                printf("Enter New Specialization: ");
                scanf(" %[^\n]", doctorTemp->doctorSpecialization);
                break;
            case UPDATE_DOCTOR_CONSULTATION_FEE:
                printf("Enter New Consultation Fee: ");
                scanf("%f", &doctorTemp->doctorConsultationFee);
                break;
            case UPDATE_DOCTOR_CONTACT_NUMBER:
                printf("Enter New Contact Number: ");
                scanf("%s", doctorTemp->doctorContactNumber);
                break;
            case UPDATE_DOCTOR_EXPERIENCE:
                printf("Enter New Experience (years): ");
                scanf("%d", &doctorTemp->doctorExperience);
                break;
            case UPDATE_DOCTOR_QUALIFICATION:
                printf("Enter New Qualification: ");
                scanf(" %[^\n]", doctorTemp->doctorQualification);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Doctor details updated successfully.\n");
            break;
        }
        doctorTemp = doctorTemp->next;
    }

    if (!doctorFound)
    {
        printf("Doctor with ID %d not found.\n", id);
    }
}

void displayDoctorDetails()
{
    if (doctorHead == NULL)
    {
        printf("No doctors found.\n");
        return;
    }

    doctorTemp = doctorHead;
    printf("--- Doctor Sorted by Name ---\n");
    while (doctorTemp != NULL)
    {
        printf("Doctor ID: %d\n", doctorTemp->doctorId);
        printf("Name: %s\n", doctorTemp->doctorName);
        printf("Specialization: %s\n", doctorTemp->doctorSpecialization);
        printf("Consultation Fee: %.2f\n", doctorTemp->doctorConsultationFee);
        printf("Contact Number: %s\n", doctorTemp->doctorContactNumber);
        printf("Experience: %d years\n", doctorTemp->doctorExperience);
        printf("Qualification: %s\n", doctorTemp->doctorQualification);
        printf("\n");
        doctorTemp = doctorTemp->next;
    }
}

void searchByDoctorId()
{
    int id;
    printf("Enter Doctor ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    doctorTemp = doctorHead;
    while (doctorTemp != NULL)
    {
        if (doctorTemp->doctorId == id)
        {
            printf("--- Doctor Found ---\n");
            printf("Name: %s\n", doctorTemp->doctorName);
            printf("Specialization: %s\n", doctorTemp->doctorSpecialization);
            printf("Consultation Fee: %.2f\n", doctorTemp->doctorConsultationFee);
            printf("Contact Number: %s\n", doctorTemp->doctorContactNumber);
            printf("Experience: %d years\n", doctorTemp->doctorExperience);
            printf("Qualification: %s\n", doctorTemp->doctorQualification);
            printf("\n");
            searchIdFound = 1;
            break;
        }
        doctorTemp = doctorTemp->next;
    }
    if (!searchIdFound)
    {
        printf("Doctor with ID %d not found.\n", id);
    }
}

void searchByDoctorSpecialization()
{
    char specialization[50];
    printf("Enter Doctor Specialization to search: ");
    scanf(" %[^\n]", specialization);

    doctorTemp = doctorHead;
    int searchSpecializationFound = 0;

    while (doctorTemp != NULL)
    {
        if (strcasecmp(specialization, doctorTemp->doctorSpecialization) == 0)
        {
            printf("--- Doctor Found ---\n");
            printf("Doctor ID: %d\n", doctorTemp->doctorId);
            printf("Name: %s\n", doctorTemp->doctorName);
            printf("Specialization: %s\n", doctorTemp->doctorSpecialization);
            printf("Consultation Fee: %.2f\n", doctorTemp->doctorConsultationFee);
            printf("Contact Number: %s\n", doctorTemp->doctorContactNumber);
            printf("Experience: %d years\n", doctorTemp->doctorExperience);
            printf("Qualification: %s\n", doctorTemp->doctorQualification);
            printf("\n");
            searchSpecializationFound = 1;
            break;
        }
        doctorTemp = doctorTemp->next;
    }

    if (!searchSpecializationFound)
    {
        printf("Doctor with Specialization '%s' not found.\n", specialization);
    }
}

void sortDoctorsById()
{
    if (doctorHead == NULL)
    {
        printf("No doctors found.\n");
        return;
    }
    doctor *tempHead = NULL, *tempTail = NULL, *current= doctorHead;
    while(current != NULL)
    {
        doctor *newNode = (doctor *) malloc(sizeof(doctor));
        if(!newNode)
        {
            printf("Memory Alloctaion Failed\n");
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

    doctor *sortedList = NULL;

    doctor *splitList(doctor *head)
    {
        doctor *slow = head, *fast = head->next;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        doctor *middle = slow->next;
        slow->next = NULL;
        return middle;
    }

    doctor *mergeLists(doctor *left, doctor *right)
    {
        doctor dummy;
        doctor *tail = &dummy;
        dummy.next = NULL;

        while (left != NULL && right != NULL)
        {
            if (left->doctorId < right->doctorId)
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


    doctor *mergeSort(doctor *head)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }

        doctor *middle = splitList(head);
        doctor *left = mergeSort(head);
        doctor *right = mergeSort(middle);
        return mergeLists(left, right);
    }


    sortedList = mergeSort(tempHead);


    printf("--- Doctors Sorted by ID ---\n");
    doctor *doctorTemp = sortedList;
    while (doctorTemp != NULL)
    {
        printf("Doctor ID: %d\n", doctorTemp->doctorId);
        printf("Name: %s\n", doctorTemp->doctorName);
        printf("Specialization: %s\n", doctorTemp->doctorSpecialization);
        printf("Consultation Fee: %.2f\n", doctorTemp->doctorConsultationFee);
        printf("Contact Number: %s\n", doctorTemp->doctorContactNumber);
        printf("Experience: %d years\n", doctorTemp->doctorExperience);
        printf("Qualification: %s\n", doctorTemp->doctorQualification);
        printf("\n");
        doctorTemp = doctorTemp->next;
    }
}

