
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "room.h"
#define USER_ID "room_user"
#define USER_PASSWORD "room@123"

room *roomHead =NULL;
room *roomNode, *roomTemp;
void loginAsRoomManagementUser()
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
            printf("\n--- Room Management System ---\n");
            printf("1. Add Room\n2. Update Room Details\n3. Display Available Rooms\n4. Search Room by ID\n5. Search Room by Type\n6. Check Room Availability\n7. Exit Room Management\n");
            printf("Enter your option: ");
            scanf("%d", &option);

            switch (option)
            {
            case ADD_ROOM:
                addRoom();
                //saveData();
                break;
            case UPDATE_ROOM_DETAILS:
                updateRoomDetails();
                //saveData();
                break;
            case DISPLAY_AVAILABLE_ROOMS:
                displayRoomDetails();
                break;
            case SEARCH_ROOM_BY_ID:
                searchByRoomId();
                break;
            case SEARCH_ROOM_BY_TYPE:
                searchByRoomType();
                break;
            case CHECK_ROOM_AVAILABILITY:
                checkAvailability();
                break;
            case EXIT_ROOM_MANAGEMENT:
                printf("Exiting from Room Management menu.\n");
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

void addRoom()
{
    room *roomNode = (room *)malloc(sizeof(room));
    if (!roomNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    roomNode->next  = NULL;

    printf("Enter Room ID: ");
    scanf("%d", &roomNode->roomId);

    roomTemp = roomHead;
    int idExists = 0;
    while (roomTemp != NULL)
    {
        if (roomTemp->roomId == roomNode->roomId)
        {
            idExists = 1;
            break;
        }
        roomTemp = roomTemp->next;
    }

    if (idExists)
    {
        printf("Room with ID %d already exists....try again\n", roomNode->roomId);
        free(roomNode);
        addRoom();
    }
    else
    {
        printf("Enter Room Type (icu/general/private): ");
        scanf(" %[^\n]", roomNode->roomType);
        printf("Enter Number of Beds: ");
        scanf("%d", &roomNode->bedCount);
        printf("Enter Available Beds: ");
        scanf("%d", &roomNode->availableBeds);
        printf("Enter Bed Status (occupied/vacant): ");
        scanf(" %[^\n]", roomNode->bedStatus);
        printf("Enter Room Fee: ");
        scanf("%f", &roomNode->roomFee);

        if (roomHead == NULL|| strcasecmp(roomHead->roomType, roomNode->roomType) > 0)
        {
            roomNode->next = roomHead;
            roomHead = roomNode;
        }
        else
        {
            roomTemp = roomHead;

            while(roomTemp->next != NULL&& strcasecmp(roomTemp->next->roomType, roomNode->roomType) < 0)
            {
                roomTemp = roomTemp->next;
            }
            roomNode->next = roomTemp->next;
            roomTemp->next = roomNode;
        }
        printf("Medicine registered successfully!\n");
        free(roomTemp);
    }
}

void updateRoomDetails()
{
    int id, choice;
    printf("Enter Room ID to update: ");
    scanf("%d", &id);

    roomTemp = roomHead;
    int roomFound = 0;

    while (roomTemp != NULL)
    {
        if (roomTemp->roomId == id)
        {
            roomFound = 1;

            printf("Updating details for Room ID %d...\n", roomTemp->roomId);
            printf("Which details do you want to update?\n");
            printf("1. Update Room Type\n2. Update Bed Count\n3. Update Available Beds\n4. Update Bed Status\n5. Update Room Fee\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case UPDATE_ROOM_TYPE:
                printf("Enter New Room Type: ");
                scanf(" %[^\n]", roomTemp->roomType);
                break;
            case UPDATE_BED_COUNT:
                printf("Enter New Bed Count: ");
                scanf("%d", &roomTemp->bedCount);
                break;
            case UPDATE_AVAILABLE_BEDS:
                printf("Enter New Available Beds: ");
                scanf("%d", &roomTemp->availableBeds);
                break;
            case UPDATE_BED_STATUS:
                printf("Enter New Bed Status (occupied/vacant): ");
                scanf(" %[^\n]", roomTemp->bedStatus);
                break;
            case UPDATE_ROOM_FEE:
                printf("Enter New Room Fee: ");
                scanf("%f", &roomTemp->roomFee);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Room details updated successfully.\n");
            break;
        }
        roomTemp = roomTemp->next;
    }

    if (!roomFound)
    {
        printf("Room with ID %d not found.\n", id);
    }
}

void displayRoomDetails()
{
    if (roomHead == NULL)
    {
        printf("No rooms available.\n");
        return;
    }

    roomTemp = roomHead;
    printf("\n--- Room Details ---\n");
    while (roomTemp != NULL)
    {
        printf("Room ID: %d\n", roomTemp->roomId);
        printf("Room Type: %s\n", roomTemp->roomType);
        printf("Total Beds: %d\n", roomTemp->bedCount);
        printf("Available Beds: %d\n", roomTemp->availableBeds);
        printf("Bed Status: %s\n", roomTemp->bedStatus);
        printf("Room Fee: %f\n", roomTemp->roomFee);
        roomTemp = roomTemp->next;
    }
}

void searchByRoomId()
{
    int id;
    printf("Enter Room ID to search: ");
    scanf("%d", &id);
    int searchIdFound = 0;
    roomTemp = roomHead;
    while (roomTemp != NULL)
    {
        if (roomTemp->roomId == id)
        {
            printf("\n--- Room Found ---\n");
            printf("Room Type: %s\n", roomTemp->roomType);
            printf("Total Beds: %d\n", roomTemp->bedCount);
            printf("Available Beds: %d\n", roomTemp->availableBeds);
            printf("Bed Status: %s\n", roomTemp->bedStatus);
            printf("Room Fee: %f\n", roomTemp->roomFee);
            searchIdFound = 1;
            break;
        }
        roomTemp = roomTemp->next;
    }

    if (!searchIdFound)
    {
        printf("Room with ID %d not found.\n", id);
    }
}

void searchByRoomType()
{
    char type[10];
    printf("Enter Room Type (icu/general/private) to search: ");
    scanf(" %[^\n]", type);

    roomTemp = roomHead;
    int searchTypeFound = 0;

    while (roomTemp != NULL)
    {
        if (strcasecmp(type, roomTemp->roomType) == 0)
        {
            printf("\n--- Room Found ---\n");
            printf("Room ID: %d\n", roomTemp->roomId);
            printf("Total Beds: %d\n", roomTemp->bedCount);
            printf("Available Beds: %d\n", roomTemp->availableBeds);
            printf("Bed Status: %s\n", roomTemp->bedStatus);
            printf("Room Fee: %f\n", roomTemp->roomFee);
            searchTypeFound = 1;
            break;
        }
        roomTemp = roomTemp->next;
    }

    if (!searchTypeFound)
    {
        printf("Room of Type '%s' not found.\n", type);
    }
}

void checkAvailability()
{
    int id;
    printf("Enter Room ID to check availability: ");
    scanf("%d", &id);
    int availabilityFound = 0;
    roomTemp = roomHead;
    while (roomTemp != NULL)
    {
        if (roomTemp->roomId == id)
        {
            printf("\n--- Room Availability ---\n");
            printf("Room ID: %d\n", roomTemp->roomId);
            printf("Available Beds: %d\n", roomTemp->availableBeds);
            availabilityFound = 1;
            break;
        }
        roomTemp = roomTemp->next;
    }

    if (!availabilityFound)
    {
        printf("Room with ID %d not found.\n", id);
    }
}
