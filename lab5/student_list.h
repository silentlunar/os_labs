#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H

#include <stdio.h>

#define MAX_NAME_LENGTH 30

struct Student {
  struct Student *next;
  char surname[MAX_NAME_LENGTH];
  double mark;
};

void addStudent(const char surname[], double mark);
void printList();
void serialize();
void deserialize();
void searchInList(const char surname[]);
void deleteFromList(const char surname[]);
void sortByMark();

#endif  // STUDENT_LIST_H