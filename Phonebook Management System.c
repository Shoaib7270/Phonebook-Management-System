#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

struct Contact {
    char name[50];
    char phone[15];
    struct Contact* next;
};

struct Contact* phonebook = NULL;

void addContact() {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    if (newContact == NULL) {
        printf("\n\t\t\t Failed to allocate memory for new contact.\n");
        return;
    }

    printf("\n\t\t\t Enter name: ");
    fgets(newContact->name, sizeof(newContact->name), stdin);
    newContact->name[strcspn(newContact->name, "\n")] = '\0';

    printf("\n\t\t\t Enter phone number: ");
    fgets(newContact->phone, sizeof(newContact->phone), stdin);
    newContact->phone[strcspn(newContact->phone, "\n")] = '\0';

    newContact->next = phonebook;
    phonebook = newContact;

    printf("\n\t\t\t Contact added successfully.\n");
}

void searchContact() {
    char searchName[50];

    printf("\n\t\t\t Enter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    struct Contact* current = phonebook;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->name, searchName) == 0) {
            printf("\n\t\t\t Name: %s\n\t\t\t Phone: %s\n", current->name, current->phone);
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("\n\t\t\t Contact not found.\n");
    }
}

void deleteContact() {
    char deleteName[50];

    printf("\n\t\t\t Enter name to delete: ");
    fgets(deleteName, sizeof(deleteName), stdin);
    deleteName[strcspn(deleteName, "\n")] = '\0';

    struct Contact* current = phonebook;
    struct Contact* prev = NULL;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->name, deleteName) == 0) {
            if (prev == NULL) {
                // Deleting the first contact
                phonebook = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            found = 1;
            printf("\n\t\t\t Contact deleted successfully.\n");
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        printf("\n\t\t\t Contact not found.\n");
    }
}

void displayPhonebook() {
    if (phonebook == NULL) {
        printf("\n\t\t\t Phonebook is empty.\n");
        return;
    }

    printf("\n\t\t\t Contact list:\n");
    struct Contact* current = phonebook;

    while (current != NULL) {
        printf("\n\t\t\t Name: %s\n\t\t\t Phone: %s\n", current->name, current->phone);
        current = current->next;
    }
}

void freePhonebook() {
    struct Contact* current = phonebook;
    struct Contact* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {

    system("color 3F");
    time_t now;
    time(&now);
    printf("\n");
    printf("\t\t\t\t\t    %s",ctime(&now));
    printf("\n\t\t\t\t  ======== Welcome to Phonebook Management System ========\n");

    int choice;

    do {
        printf("\n\n\t\t\t\t  ============ Phonebook Management System ============");
        printf("\n\t\t 1. Add Contact\n");
        printf("\n\t\t 2. Search Contact\n");
        printf("\n\t\t 3. Delete Contact\n");
        printf("\n\t\t 4. Display Phonebook\n");
        printf("\n\t\t 5. Exit\n");
        printf("\n\t\t Enter your choice: ");

        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                displayPhonebook();
                break;
            case 5:
                printf("\n\t\t\t Thanks for using my phonebook.");
                break;
            default:
                printf("\n\t\t\t Invalid choice. Please try again.\n");
        }

        printf("\n");
    } while (choice != 5);

    // Free memory before exiting
    freePhonebook();

    return 0;
}
