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
/*Variables & Declarations*/
char dir[MAX_PATH];
char opDir[MAX_PATH];
void newRecipe();
void removeRecipe(int n);
void openRecipe(int n);
void listRecipes();
void setDir();
void scanInput();
int recCount;


int main(void) {
	setDir();
	while (1) {
		listRecipes();
		scanInput();
	}
}

void listRecipes() {
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	hFind = FindFirstFileA(opDir, &ffd);
	system("cls");
	printf("This program stores and recalls user inputted recipes. Input the number to the left of an entry to view its content. \nInput 'n' to create a new recipe. Input 'd' to delete a recipe. Input 'e' to edit an existing recipe.\n");
	printf("\tRECIPES:\n");
	recCount = 0;
	do {
		if (hFind != "INVALID_HANDLE_VALUE") {
			char* name = ffd.cFileName;
			printf("%d\t%s \n", recCount, name);
			recCount++;
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
void setDir() {
	_getcwd(dir, sizeof(dir));
	snprintf(dir, sizeof(dir), "%s\\Recipes", dir);
	snprintf(opDir, sizeof(opDir), "%s\\*.txt", dir);
	printf("\n\n\n%d\n\n\n", _chdir(dir));
	if (_chdir(dir) == -1) { _mkdir(dir); }
	_chdir(dir);
}
void scanInput() {
	char select;
	printf("Input your selection: ");
	scanf_s(" %c", &select);
	switch(select){
	case 's':
		//select recipe
		break;
	case 'n':
		//new recipe
		newRecipe();
		break;
	case 'e':
		//edit recipe
		break;
	case 'r':
		//remove recipe
		break;
	default:
		printf("Invalid input");
		break;
	}

}







//thangs to do
//gotta add error detection
//check if new recipe already exists
//find out how to index the files
