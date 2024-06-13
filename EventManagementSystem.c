#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for an event
typedef struct Event {
    char name[50];
    char date[20];
    char location[50];
    struct Event* next;
} Event;

// Function to create a new event
Event* createEvent(char* name, char* date, char* location) {
    Event* newEvent = (Event*)malloc(sizeof(Event));
    strcpy(newEvent->name, name);
    strcpy(newEvent->date, date);
    strcpy(newEvent->location, location);
    newEvent->next = NULL;
    return newEvent;
}

// Function to compare two dates in YYYY-MM-DD format
int compareDates(char* date1, char* date2) {
    return strcmp(date1, date2);
}

// Function to add an event in chronological order
void addEvent(Event** head, char* name, char* date, char* location) {
    Event* newEvent = createEvent(name, date, location);
    
    // If the list is empty or the new event date is earlier than the head event date
    if (*head == NULL || compareDates(newEvent->date, (*head)->date) < 0) {
        newEvent->next = *head;
        *head = newEvent;
    } else {
        Event* temp = *head;
        while (temp->next != NULL && compareDates(newEvent->date, temp->next->date) >= 0) {
            temp = temp->next;
        }
        newEvent->next = temp->next;
        temp->next = newEvent;
    }
}

// Function to display all events
void displayEvents(Event* head) {
    Event* temp = head;
    while (temp != NULL) {
        printf("Event Name: %s\n", temp->name);
        printf("Date: %s\n", temp->date);
        printf("Location: %s\n", temp->location);
        printf("----------------------\n");
        temp = temp->next;
    }
}

// Function to delete an event by name
void deleteEvent(Event** head, char* name) {
    Event* temp = *head;
    Event* prev = NULL;

    // If head node itself holds the event to be deleted
    if (temp != NULL && strcmp(temp->name, name) == 0) {
        *head = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    // Search for the event to be deleted, keep track of the previous node
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If event was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}

// Function to update an event by date
void updateEvent(Event* head, char* date) {
    Event* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->date, date) == 0) {
            printf("Enter new event name: ");
            fgets(temp->name, sizeof(temp->name), stdin);
            temp->name[strcspn(temp->name, "\n")] = 0; // Remove trailing newline
            printf("Enter new event date (YYYY-MM-DD): ");
            fgets(temp->date, sizeof(temp->date), stdin);
            temp->date[strcspn(temp->date, "\n")] = 0; // Remove trailing newline
            printf("Enter new event location: ");
            fgets(temp->location, sizeof(temp->location), stdin);
            temp->location[strcspn(temp->location, "\n")] = 0; // Remove trailing newline
            printf("Event updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Event not found.\n");
}

int main() {
    Event* eventList = NULL;
    int choice;
    char name[50], date[20], location[50];

    while (1) {
        printf("Event Planner Menu:\n");
        printf("1. Add Event\n");
        printf("2. Display Events\n");
        printf("3. Delete Event\n");
        printf("4. Update Event\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:
                printf("Enter event name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;  // Remove trailing newline
                printf("Enter event date (YYYY-MM-DD): ");
                fgets(date, sizeof(date), stdin);
                date[strcspn(date, "\n")] = 0;  // Remove trailing newline
                printf("Enter event location: ");
                fgets(location, sizeof(location), stdin);
                location[strcspn(location, "\n")] = 0;  // Remove trailing newline
                addEvent(&eventList, name, date, location);
                break;

            case 2:
                printf("All Events:\n");
                printf("----------------------\n");
                displayEvents(eventList);
                break;

            case 3:
                printf("Enter the name of the event to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;  // Remove trailing newline
                deleteEvent(&eventList, name);
                break;

            case 4:
                printf("Enter the date of the event to update (YYYY-MM-DD): ");
                fgets(date, sizeof(date), stdin);
                date[strcspn(date, "\n")] = 0;  // Remove trailing newline
                updateEvent(eventList, date);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}