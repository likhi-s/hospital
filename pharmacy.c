#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pharmacy.h"
#define USER_ID "pharmacy_user"
#define USER_PASSWORD "pharmacy@123"

pharmacy *pharmacyHead = NULL;
pharmacy *pharmacyTemp, *pharmacyNode;

void loginAsPharmacyManagementUser()
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
        while (true) {
            printf("\n--- Pharmacy Management System ---\n");
            printf("1. Add Medicine\n2. Update Medicine Details\n3. Display Available Medicines\n4. Search Medicine by ID\n5. Search Medicine by Name\n6. Check Medicine Stock\n7. Exit from Pharmacy Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_NEW_MEDICINE:
                addMedicine();
                //saveData();
                break;
            case UPDATE_MEDICINE_DETAILS:
                updateMedicineDetails();
                //saveData();
                break;
            case DISPLAY_AVAILABLE_MEDICINES:
                displayMedicineDetails();
                break;
            case SEARCH_MEDICINE_BY_ID:
                searchByMedicineId();
                break;
            case SEARCH_MEDICINE_BY_NAME:
                searchByMedicineName();
                break;
            case CHECK_STOCK:
                checkMedicineStock();
                break;
            case EXIT_PHARMACY_MANAGEMENT:
                printf("Exiting from Pharmacy Management menu.\n");
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

void addMedicine()
{
    pharmacy *pharmacyNode = (pharmacy *)malloc(sizeof(pharmacy));
    if (!pharmacyNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    pharmacyNode->next  = NULL;

    printf("Enter Medicine ID: ");
    scanf("%d", &pharmacyNode->medicineId);

    pharmacyTemp = pharmacyHead;
    int idExists = 0;
    while (pharmacyTemp != NULL)
    {
        if (pharmacyTemp->medicineId == pharmacyNode->medicineId)
        {
            idExists = 1;
            break;
        }
        pharmacyTemp = pharmacyTemp->next;
    }

    if (idExists)
    {
        printf("Medicine with ID %d already exists....try again\n", pharmacyNode->medicineId);
        free(pharmacyNode);
        addMedicine();
    }
    else
    {
        printf("Enter Medicine Name: ");
        scanf(" %[^\n]", pharmacyNode->medicineName);
        printf("Enter Medicine Cost: ");
        scanf("%f", &pharmacyNode->medicineCost);
        printf("Enter Medicine Stock Quantity: ");
        scanf("%d", &pharmacyNode->medicineStockQuantity);
        printf("Enter Medicine Type (tablet/injection): ");
        scanf(" %[^\n]", pharmacyNode->medicineType);
        printf("Enter Medicine Dosage: ");
        scanf(" %[^\n]", pharmacyNode->medicineDosage);

        if (pharmacyHead == NULL|| strcasecmp(pharmacyHead->medicineName, pharmacyNode->medicineName) > 0)
        {
            pharmacyNode->next = pharmacyHead;
            pharmacyHead = pharmacyNode;
        }
        else
        {
            pharmacyTemp = pharmacyHead;

            while(pharmacyTemp->next != NULL&& strcasecmp(pharmacyTemp->next->medicineName, pharmacyNode->medicineName) < 0)
            {
                pharmacyTemp = pharmacyTemp->next;
            }
            pharmacyNode->next = pharmacyTemp->next;
            pharmacyTemp->next = pharmacyNode;
        }
        printf("Medicine registered successfully!\n");

    }
}

void updateMedicineDetails()
{
    int id, choice;
    printf("Enter Medicine ID to update: ");
    scanf("%d", &id);

    pharmacyTemp = pharmacyHead;
    int medicineFound = 0;

    while (pharmacyTemp != NULL)
    {
        if (pharmacyTemp->medicineId == id)
        {
            medicineFound = 1;

            printf("Updating details for %s...\n", pharmacyTemp->medicineName);
            printf("Which details do you want to update?\n");
            printf("1. Update Medicine Name\n2. Update Medicine Cost\n3. Update Medicine Stock\n4. Update Medicine Type\n5. Update Medicine Dosage\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_MEDICINE_NAME:
                printf("Enter New Medicine Name: ");
                scanf(" %[^\n]", pharmacyTemp->medicineName);
                break;
            case UPDATE_MEDICINE_COST:
                printf("Enter New Medicine Cost: ");
                scanf("%f", &pharmacyTemp->medicineCost);
                break;
            case UPDATE_MEDICINE_STOCK:
                printf("Enter New Stock Quantity: ");
                scanf("%d", &pharmacyTemp->medicineStockQuantity);
                break;
            case UPDATE_MEDICINE_TYPE:
                printf("Enter New Medicine Type: ");
                scanf(" %[^\n]", pharmacyTemp->medicineType);
                break;
            case UPDATE_MEDICINE_DOSAGE:
                printf("Enter New Medicine Dosage: ");
                scanf(" %[^\n]", pharmacyTemp->medicineDosage);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Medicine details updated successfully.\n");
            break;
        }
        pharmacyTemp = pharmacyTemp->next;
    }

    if (!medicineFound)
    {
        printf("Medicine with ID %d not found.\n", id);
    }
}

void displayMedicineDetails()
{
    if (pharmacyHead == NULL)
    {
        printf("No medicines found.\n");
        return;
    }

    pharmacyTemp = pharmacyHead;
    printf("\n--- Medicine Details ---\n");
    while (pharmacyTemp != NULL)
    {
        printf("Medicine ID: %d\n", pharmacyTemp->medicineId);
        printf("Name: %s\n", pharmacyTemp->medicineName);
        printf("Cost: %f\n", pharmacyTemp->medicineCost);
        printf("Stock Quantity: %d\n", pharmacyTemp->medicineStockQuantity);
        printf("Type: %s\n", pharmacyTemp->medicineType);
        printf("Dosage: %s\n", pharmacyTemp->medicineDosage);
        pharmacyTemp = pharmacyTemp->next;
    }
}

void searchByMedicineId()
{
    int id;
    printf("Enter Medicine ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    pharmacyTemp = pharmacyHead;
    while (pharmacyTemp != NULL)
    {
        if (pharmacyTemp->medicineId == id)
        {
            printf("\n--- Medicine Found ---\n");
            printf("Name: %s\n", pharmacyTemp->medicineName);
            printf("Cost: %f\n", pharmacyTemp->medicineCost);
            printf("Stock Quantity: %d\n", pharmacyTemp->medicineStockQuantity);
            printf("Type: %s\n", pharmacyTemp->medicineType);
            printf("Dosage: %s\n", pharmacyTemp->medicineDosage);
            searchIdFound = 1;
            break;
        }
        pharmacyTemp = pharmacyTemp->next;
    }

    if (!searchIdFound)
    {
        printf("Medicine with ID %d not found.\n", id);
    }
}

void searchByMedicineName()
{
    char name[100];
    printf("Enter Medicine Name to search: ");
    scanf(" %[^\n]", name);

    pharmacyTemp = pharmacyHead;
    int searchNameFound = 0;

    while (pharmacyTemp != NULL)
    {
        if (strcasecmp(name, pharmacyTemp->medicineName) == 0)
        {
            printf("\n--- Medicine Found ---\n");
            printf("Medicine ID: %d\n", pharmacyTemp->medicineId);
            printf("Cost: %f\n", pharmacyTemp->medicineCost);
            printf("Stock Quantity: %d\n", pharmacyTemp->medicineStockQuantity);
            printf("Type: %s\n", pharmacyTemp->medicineType);
            printf("Dosage: %s\n", pharmacyTemp->medicineDosage);
            searchNameFound = 1;
            break;
        }
        pharmacyTemp = pharmacyTemp->next;
    }

    if (!searchNameFound)
    {
        printf("Medicine with Name '%s' not found.\n", name);
    }
}

void checkMedicineStock()
{
    int id;
    printf("Enter Medicine ID to check stock: ");
    scanf("%d", &id);
    int stockFound = 0;
    pharmacyTemp = pharmacyHead;
    while (pharmacyTemp != NULL)
    {
        if (pharmacyTemp->medicineId == id)
        {
            printf("\n--- Stock Details ---\n");
            printf("Medicine ID: %d\n", pharmacyTemp->medicineId);
            printf("Stock Quantity: %d\n", pharmacyTemp->medicineStockQuantity);
            stockFound = 1;
            break;
        }
        pharmacyTemp = pharmacyTemp->next;
    }

    if (!stockFound)
    {
        printf("Medicine with ID %d not found.\n", id);
    }
}
