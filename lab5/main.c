#include <stdio.h>
#include <stdlib.h>

#include "student_list.h"

int main() {
  addStudent("Ivanov", 4.5);
  addStudent("Petrov", 3.0);
  addStudent("Sidorov", 5.0);

  printf("Before sorting:\n");
  printList();

  serialize();

  sortByMark();

  printf("\nAfter sorting:\n");
  printList();

  char searchSurname[MAX_NAME_LENGTH];
  printf("\nEnter the surname to search: ");
  scanf("%s", searchSurname);

  searchInList(searchSurname);

  char deleteSurname[MAX_NAME_LENGTH];
  printf("\nEnter the surname to delete: ");
  scanf("%s", deleteSurname);

  deleteFromList(deleteSurname);

  printf("\nAfter deletion:\n");
  printList();

  // deserialize();

  return 0;
}