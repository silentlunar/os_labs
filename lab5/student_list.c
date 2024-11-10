#include "student_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student *head = NULL;
struct Student *tail = NULL;

void addStudent(const char surname[], double mark) {
  struct Student *newNode = (struct Student *)malloc(sizeof(struct Student));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }
  strncpy(newNode->surname, surname, MAX_NAME_LENGTH);
  newNode->mark = mark;
  newNode->next = NULL;

  if (head == NULL) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
}

void printList() {
  struct Student *current = head;

  if (current == NULL) {
    printf("The list is empty.\n");
    return;
  }

  while (current != NULL) {
    printf("Surname: %s, Mark: %.2lf\n", current->surname, current->mark);
    current = current->next;
  }
}

void serialize() {
  FILE *file = fopen("students.dat", "wb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for writing\n");
    return;
  }

  struct Student *current = head;
  while (current != NULL) {
    fwrite(current->surname, sizeof(current->surname), 1, file);
    fwrite(&(current->mark), sizeof(current->mark), 1, file);
    current = current->next;
  }
  fclose(file);
}

void deserialize() {
  FILE *file = fopen("students.dat", "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for reading\n");
    return;
  }

  char surname[MAX_NAME_LENGTH];
  double mark;

  while (fread(surname, sizeof(surname), 1, file) &&
         fread(&mark, sizeof(mark), 1, file)) {
    addStudent(surname, mark);
  }

  fclose(file);
}

void searchInList(const char surname[]) {
  struct Student *current = head;

  while (current != NULL) {
    if (strcmp(current->surname, surname) == 0) {
      printf("Found: Surname: %s, Mark: %.2lf\n", current->surname,
             current->mark);
      return;
    }
    current = current->next;
  }

  printf("The surname %s was not found.\n", surname);
}

void deleteFromList(const char surname[]) {
  struct Student *current = head;
  struct Student *prev = NULL;

  while (current != NULL) {
    if (strcmp(current->surname, surname) == 0) {
      if (prev == NULL) {
        head = current->next;
        if (head == NULL) {
          tail = NULL;
        }
      } else {
        prev->next = current->next;
        if (current == tail) {
          tail = prev;
        }
      }
      free(current);
      printf("Deleted: %s\n", surname);
      return;
    }
    prev = current;
    current = current->next;
  }

  printf("The surname %s was not found for deletion.\n", surname);
}

void sortByMark() {
  int swapped;

  do {
    swapped = 0;
    struct Student *ptr1 = head;

    while (ptr1 != NULL && ptr1->next != NULL) {
      if (ptr1->mark > ptr1->next->mark) {
        double tempMark = ptr1->mark;
        ptr1->mark = ptr1->next->mark;
        ptr1->next->mark = tempMark;

        char tempSurname[MAX_NAME_LENGTH];
        strcpy(tempSurname, ptr1->surname);
        strcpy(ptr1->surname, ptr1->next->surname);
        strcpy(ptr1->next->surname, tempSurname);

        swapped = 1;
      }
      ptr1 = ptr1->next;
    }

  } while (swapped);
}