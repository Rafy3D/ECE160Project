#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct recipe {
	int id;
	char name[32];
	char desc[1028];
};
char dir[MAX_PATH];
char opDir[MAX_PATH];
void newRecipe();
void removeRecipe(int n);
void openRecipe(int n);
void listRecipes();

int main(void) {
	_getcwd(dir, sizeof(dir));
	snprintf(dir, sizeof(dir), "%s\\Recipes", dir);
	snprintf(opDir, sizeof(opDir), "%s\\*", dir);
	_chdir(dir);
	printf("This program stores and recalls user inputted recipes. Input the number to the left of an entry to view its content. \nInput 'n' to create a new recipe. Input 'd' to delete a recipe. Input 'e' to edit an existing recipe.\n");
	listRecipes();
}

void listRecipes() {
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	hFind = FindFirstFileA(opDir, &ffd);
	printf("\tRECIPES:\n");
	do {
		if (hFind != "INVALID_HANDLE_VALUE") {
			char* name = ffd.cFileName;
			
			printf(" %s \n", name);
		}
	} while (FindNextFileA(hFind,&ffd)!=0);
	FindClose(hFind);
}
void openRecipe(int n) {}
void newRecipe() {
	FILE* dat;
	char filename[36];
	char filepath[MAX_PATH];
	struct recipe newRec;
	printf("Enter name of new recipe: ");
	fgets(newRec.name, sizeof(newRec.name), stdin);
	newRec.name[strcspn(newRec.name, "\n")] = 0;
	snprintf(filename, sizeof(filename), "%s.txt", newRec.name);
	printf("Enter description of %s in the opened text file and save when done:\n", newRec.name);
	snprintf(filepath, sizeof(filepath), "%s\\\"%s\"", dir, filename);
	fopen_s(&dat, filename, "w");
	fclose(dat);
	system(filepath);
}
void removeRecipe(int n) {}

//thangs to do
//gotta add error detection
//check if new recipe already exists
//find out how to index the files
