
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
            printf("1. Add Room\n2. Update Room Details\n3. Display Available Rooms\n4. Search Room by ID\n5. Search Room by Type\n6. Check Room Availability\n7. Sort Room By Id\n8. Exit Room Management\n");
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
            case SORT_BY_ROOM_ID:
                sortByRoomId();
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
        printf("Room registered successfully!\n");

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
    printf("\n--- Rooms sorted by Type(icu/general/private) ---\n");
    while (roomTemp != NULL)
    {
        printf("Room ID: %d\n", roomTemp->roomId);
        printf("Room Type: %s\n", roomTemp->roomType);
        printf("Total Beds: %d\n", roomTemp->bedCount);
        printf("Available Beds: %d\n", roomTemp->availableBeds);
        printf("Bed Status: %s\n", roomTemp->bedStatus);
        printf("Room Fee: %f\n", roomTemp->roomFee);
        printf("\n");
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
            printf("\n");
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
            printf("\n");
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

void sortByRoomId()
{
    if (roomHead == NULL)
    {
        printf("No rooms found.\n");
        return;
    }

    room *tempHead = NULL, *tempTail = NULL, *current = roomHead;


    while (current != NULL)
    {
        room *newNode = (room *)malloc(sizeof(room));
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

    room *sortedList = NULL;


    room *splitList(room *head)
    {
        room *slow = head, *fast = head->next;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        room *middle = slow->next;
        slow->next = NULL;
        return middle;
    }


    room *mergeLists(room *left, room *right)
    {
        room dummy;
        room *tail = &dummy;
        dummy.next = NULL;

        while (left != NULL && right != NULL)
        {
            if (left->roomId < right->roomId)
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


    room *mergeSort(room *head)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }

        room *middle = splitList(head);
        room *left = mergeSort(head);
        room *right = mergeSort(middle);
        return mergeLists(left, right);
    }

    sortedList = mergeSort(tempHead);


    printf("--- Rooms Sorted by ID ---\n");
    room *temp = sortedList;
    while (temp != NULL)
    {
        printf("Room ID: %d\n",temp->roomId);
        printf("Room Type: %s\n", temp->roomType);
        printf("Total Beds: %d\n", temp->bedCount);
        printf("Available Beds: %d\n", temp->availableBeds);
        printf("Bed Status: %s\n", temp->bedStatus);
        printf("Room Fee: %f\n", temp->roomFee);
        printf("\n");
        temp = temp->next;
    }


    while (sortedList != NULL)
    {
        room *temp = sortedList;
        sortedList = sortedList->next;
        free(temp);
    }
}
