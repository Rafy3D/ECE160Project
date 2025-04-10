#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <sys/types.h>
#include <processthreadsapi.h>
typedef struct recipe {
	int id;
	char name[32];
	char desc[512];
};
struct recipe list[128];
int len = (sizeof(list) / sizeof(list[0]));
char dir[1028];
void newRecipe();
void removeRecipe(int n);
void openRecipe(int n);
int main(void) {
	TCHAR username[256];
	DWORD size = sizeof(username);
	GetUserNameA(username, &size);
	snprintf(dir, 1028, "C:\\Users\\%s\\AppData\\Local\\ECE160_Project\\Recipes", username);
	_chdir(dir);
	printf("This program stores and recalls user inputted recipes. Input the number to the left of an entry to view its content. \nInput n to create a new recipe. Input d to delete a recipe. Input e to edit an existing recipe.\n");
	newRecipe();
}
void openRecipe(int n) {}
void newRecipe() {
	FILE* dat;
	char filename[35];
	char filepath[1028];
	struct recipe newRec;
	printf("Enter name of new recipe: ");
	fgets(newRec.name, sizeof(newRec.name), stdin);
	newRec.name[strcspn(newRec.name, "\n")] = 0;
	snprintf(filename, 35, "%s.txt", newRec.name);
	printf("Enter description of %s in the opened text file:\n", newRec.name);
	snprintf(filepath, 1028, "%s\\\"%s\"", dir, filename);
	fopen_s(&dat, filename, "w");
	fclose(dat);
	system(filepath);
}
void removeRecipe(int n) {
	int i;
	printf("Enter recipe to remove: ");
	scanf_s("%d", &i);
	for (n = 0; n <= len; n++) {
		struct recipe tempList[128];
		if (n != i) {
			tempList[n] = list[n];
		}
		else{
		
		}
	}
}

//thangs to do
//gotta add error detection
//check if new recipe already exists
//find out how to index the files
