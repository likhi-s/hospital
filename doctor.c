
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "doctor.h"


#define USER_ID "doctor_user"
#define USER_PASSWORD "doctor@123"
doctor *doctorHead =NULL;
doctor *doctorNode, *doctorTemp;

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
            printf("1. Add doctor\n2. Update doctor details\n3. Display Available Doctors\n4. Search Doctor by ID\n5. Search Doctor by Specialization\n6. Exit from Doctor management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_DOCTOR:
                addDoctor();
                //saveData();
                break;
            case UPDATE_DOCTOR_DETAILS:
                updateDoctorDetails();
                //saveData();
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

void addDoctor()
{
    doctor *doctorNode = (doctor *)malloc(sizeof(doctor));
    if (!doctorNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    doctorNode->next  = NULL;

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
        addDoctor();
    }
    else
    {
        printf("Enter Doctor Name: ");
        scanf(" %[^\n]", doctorNode->doctorName);
        printf("Enter Doctor Specialization: ");
        scanf(" %[^\n]", doctorNode->doctorSpecialization);
        printf("Enter Doctor Consultation Fee: ");
        scanf("%f", &doctorNode->doctorConsultationFee);
        printf("Enter Doctor Contact Number: ");
        scanf("%s", doctorNode->doctorContactNumber);
        printf("Enter Doctor Experience (in years): ");
        scanf("%d", &doctorNode->doctorExperience);
        printf("Enter Doctor Qualification: ");
        scanf(" %[^\n]", doctorNode->doctorQualification);

        if (doctorHead == NULL|| strcasecmp(doctorHead->doctorName, doctorNode->doctorName) > 0)
        {
            doctorNode->next = doctorHead;
            doctorHead = doctorNode;
        }
        else
        {
            doctorTemp = doctorHead;

            while(doctorTemp->next != NULL&& strcasecmp(doctorTemp->next->doctorName, doctorNode->doctorName) < 0)
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

            printf("Updating details for Dr. %s...\n", doctorTemp->doctorName);
            printf("Which details do you want to update?\n");
            printf("1. Update Doctor Name\n2. Update Specialization\n3. Update Consultation Fee\n4. Update Contact Number\n5. Update Experience\n6. Update Qualification\n");
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
    printf("\n--- Doctor Details ---\n");
    while (doctorTemp != NULL)
    {
        printf("Doctor ID: %d\n", doctorTemp->doctorId);
        printf("Name: %s\n", doctorTemp->doctorName);
        printf("Specialization: %s\n", doctorTemp->doctorSpecialization);
        printf("Consultation Fee: %.2f\n", doctorTemp->doctorConsultationFee);
        printf("Contact Number: %s\n", doctorTemp->doctorContactNumber);
        printf("Experience: %d years\n", doctorTemp->doctorExperience);
        printf("Qualification: %s\n", doctorTemp->doctorQualification);
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
            printf("\n--- Doctor Found ---\n");
            printf("Name: %s\n", doctorTemp->doctorName);
            printf("Specialization: %s\n", doctorTemp->doctorSpecialization);
            printf("Consultation Fee: %.2f\n", doctorTemp->doctorConsultationFee);
            printf("Contact Number: %s\n", doctorTemp->doctorContactNumber);
            printf("Experience: %d years\n", doctorTemp->doctorExperience);
            printf("Qualification: %s\n", doctorTemp->doctorQualification);
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
            printf("\n--- Doctor Found ---\n");
            printf("Doctor ID: %d\n", doctorTemp->doctorId);
            printf("Name: %s\n", doctorTemp->doctorName);
            printf("Specialization: %s\n", doctorTemp->doctorSpecialization);
            printf("Consultation Fee: %.2f\n", doctorTemp->doctorConsultationFee);
            printf("Contact Number: %s\n", doctorTemp->doctorContactNumber);
            printf("Experience: %d years\n", doctorTemp->doctorExperience);
            printf("Qualification: %s\n", doctorTemp->doctorQualification);
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
