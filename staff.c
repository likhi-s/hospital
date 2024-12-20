#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "staff.h"

#define USER_ID "staff_user"
#define USER_PASSWORD "staff@123"

staff *staffHead =NULL ;
staff *staffTemp, *staffNode;
void loginAsStaffManagementUser()
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
            printf("\n--- Staff Management System ---\n");
            printf("1. Add Staff\n2. Update Staff details\n3. Display Available Staff\n4. Search Staff by ID\n5. Search Staff by Role\n6. Exit from Staff Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_STAFF:
                addStaff();
                //saveData();
                break;
            case UPDATE_STAFF_DETAILS:
                updateStaffDetails();
                //saveData();
                break;
            case DISPLAY_AVAILABLE_STAFF:
                displayStaffDetails();
                break;
            case SEARCH_STAFF_BY_ID:
                searchByStaffId();
                break;
            case SEARCH_STAFF_BY_ROLE:
                searchByStaffRole();
                break;
            case EXIT_STAFF_MANAGEMENT:
                printf("Exiting from Staff Management menu.\n");
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

void addStaff()
{
    staff *staffNode = (staff *)malloc(sizeof(staff));
    if (!staffNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    staffNode->next  = NULL;


    printf("Enter Staff ID: ");
    scanf("%d", &staffNode->staffId);

    staffTemp = staffHead;
    int idExists = 0;
    while (staffTemp != NULL)
    {
        if (staffTemp->staffId == staffNode->staffId)
        {
            idExists = 1;
            break;
        }
        staffTemp = staffTemp->next;
    }

    if (idExists)
    {
        printf("Staff with ID %d already exists....try again\n", staffNode->staffId);
        free(staffNode);
        addStaff();
    }
    else
    {
        printf("Enter Staff Name: ");
        scanf(" %[^\n]", staffNode->staffName);
        printf("Enter Staff Role (e.g., Nurse, Technician, Receptionist): ");
        scanf(" %[^\n]", staffNode->staffRole);
        printf("Enter Staff Shift (Day/Night): ");
        scanf("%s", staffNode->staffShift);
        printf("Enter Staff Salary: ");
        scanf("%f", &staffNode->staffSalary);
        printf("Enter Staff Contact Number: ");
        scanf("%s", staffNode->staffContactNumber);

        if (staffHead == NULL|| strcasecmp(staffHead->staffName, staffNode->staffName) > 0)
        {
            staffNode->next = staffHead;
            staffHead = staffNode;
        }
        else
        {
            staffTemp = staffHead;

            while(staffTemp->next != NULL&& strcasecmp(staffTemp->next->staffName, staffNode->staffName) < 0)
            {
                staffTemp = staffTemp->next;
            }
            staffNode->next = staffTemp->next;
            staffTemp->next = staffNode;
        }
        printf("staff registered successfully!\n");

    }
}

void updateStaffDetails()
{
    int id, choice;
    printf("Enter Staff ID to update: ");
    scanf("%d", &id);

    staffTemp = staffHead;
    int staffFound = 0;

    while (staffTemp != NULL)
    {
        if (staffTemp->staffId == id)
        {
            staffFound = 1;

            printf("Updating details for %s...\n", staffTemp->staffName);
            printf("Which details do you want to update?\n");
            printf("1. Update Staff Name\n2. Update Role\n3. Update Shift\n4. Update Salary\n5. Update Contact Number\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_STAFF_NAME:
                printf("Enter New Staff Name: ");
                scanf(" %[^\n]", staffTemp->staffName);
                break;
            case UPDATE_STAFF_ROLE:
                printf("Enter New Role: ");
                scanf(" %[^\n]", staffTemp->staffRole);
                break;
            case UPDATE_STAFF_SHIFT:
                printf("Enter New Shift (Day/Night): ");
                scanf("%s", staffTemp->staffShift);
                break;
            case UPDATE_STAFF_SALARY:
                printf("Enter New Salary: ");
                scanf("%f", &staffTemp->staffSalary);
                break;
            case UPDATE_STAFF_CONTACT_NUMBER:
                printf("Enter New Contact Number: ");
                scanf("%s", staffTemp->staffContactNumber);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Required staff details updated successfully.\n");
            break;
        }
        staffTemp = staffTemp->next;
    }

    if (!staffFound)
    {
        printf("Staff with ID %d not found.\n", id);
    }
}

void displayStaffDetails()
{
    if (staffHead == NULL)
    {
        printf("No staff found.\n");
        return;
    }

    staffTemp = staffHead;
    printf("\n--- Staff Details ---\n");
    while (staffTemp != NULL)
    {
        printf("Staff ID: %d\n", staffTemp->staffId);
        printf("Name: %s\n", staffTemp->staffName);
        printf("Role: %s\n", staffTemp->staffRole);
        printf("Shift: %s\n", staffTemp->staffShift);
        printf("Salary: %f\n", staffTemp->staffSalary);
        printf("Contact Number: %s\n", staffTemp->staffContactNumber);
        staffTemp = staffTemp->next;
    }
}

void searchByStaffId()
{
    int id;
    printf("Enter Staff ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    staffTemp = staffHead;
    while (staffTemp != NULL)
    {
        if (staffTemp->staffId == id)
        {
            printf("\n--- Staff Found ---\n");
            printf("Name: %s\n", staffTemp->staffName);
            printf("Role: %s\n", staffTemp->staffRole);
            printf("Shift: %s\n", staffTemp->staffShift);
            printf("Salary: %f\n", staffTemp->staffSalary);
            printf("Contact Number: %s\n", staffTemp->staffContactNumber);
            searchIdFound = 1;
            break;
        }
        staffTemp = staffTemp->next;
    }
    if (!searchIdFound)
    {
        printf("Staff with ID %d not found.\n", id);
    }
}

void searchByStaffRole()
{
    char searchRole[50];
    printf("Enter Staff Role to search: ");
    scanf(" %[^\n]", searchRole);

    staffTemp = staffHead;
    int searchRoleFound = 0;

    while (staffTemp != NULL)
    {
        if (strcasecmp(searchRole, staffTemp->staffRole) == 0)
        {
            printf("\n--- Staff Found ---\n");
            printf("Staff ID: %d\n", staffTemp->staffId);
            printf("Name: %s\n", staffTemp->staffName);
            printf("Role: %s\n", staffTemp->staffRole);
            printf("Shift: %s\n", staffTemp->staffShift);
            printf("Salary: %f\n", staffTemp->staffSalary);
            printf("Contact Number: %s\n", staffTemp->staffContactNumber);
            searchRoleFound = 1;
            break;
        }
        staffTemp = staffTemp->next;
    }

    if (!searchRoleFound)
    {
        printf("Staff with Role '%s' not found.\n", searchRole);
    }
}
