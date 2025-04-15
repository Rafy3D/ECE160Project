#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
/*Variables & Declarations*/
char dir[MAX_PATH];
char opDir[MAX_PATH];
char *recList[64];
void newRecipe();
void removeRecipe(int n);
void openRecipe(int n);
void listRecipes();
void setDir();
void scanInput();
int recCount;

int main(void) {
	setDir();			//sets the working directory to Recipes folder
	listRecipes();		//show list of recipes and their indexes
	while (1) {
		scanInput();	//continually scan for user's input
		system("cls");
	}
}

void listRecipes() {
	//scans and lists all the .txt files in the Recipes folder and saves them to an array for later indexing
	HANDLE hFind = INVALID_HANDLE_VALUE;	//Handle is a data type used to interract with files in windows. it is initiallized to Invalid_Handle_Value
	WIN32_FIND_DATA ffd;					//stores the data collected from each file scanned. Most important to our use case is the file name
	hFind = FindFirstFileA(opDir, &ffd);	//Initialize the handle to the first file found in the Recipes directory, here the directory path passed to the function is opDir, which is the working directiory + /*.txt appended to tell the find file function to only scan for all .txt files. file data is saved to ffd
	recCount = 0;							//counter that will serve as the index for each file
	memset(recList, 0, sizeof(recList));	//recList is an array that contains the names of all the files that will be scanned. this funciton clears that array to initialize it
	printf("This program stores and recalls user inputted recipes. Input the number to the left of an entry to view its content. \nInput 's' to view a recipe, 'n' to create a new recipe, 'd' to delete a recipe,'e' to edit an existing recipe.\n");
	printf("\tRECIPES:\n");
	do {
		if (hFind != INVALID_HANDLE_VALUE) { //this if should only excecute if the directory is not empty, this doesnt work for now and if you run it with the Recipes folder empty it prints a bunch of crazy shit
			char* name = ffd.cFileName;		// sets the variable name to the name of the current file scanned including the .txt extension
			printf("%d\t%s \n", recCount, name);	//prints the recipe name along with its index number
			recList[recCount] = malloc(strlen(name) + 1); //allocates memory to the current pointer in recList to scanned recipe name
			strcpy_s(recList[recCount], sizeof(recList[recCount]), name);	//adds the current scanned file name to recList at the position denoted by its index numbers for future indexing
			recCount++;														//increses index number by 1
			free(recList[recCount]);										//frees memory allocated to the pointer earlier
		}
	} while (FindNextFileA(hFind,&ffd)!=0);						//executes until function fails, usually that is when no more files can be found
	FindClose(hFind);														//close the find function
}
void openRecipe(int n) {
	//reads the recipe from the file users input
	FILE* dat;
	char buffer[1028];
	char* filename = recList[n];
	char throwaway;
	fopen_s(&dat, filename, "r");
	//printf("\n%s: \n", );
	while (fgets(buffer, sizeof(buffer), dat) != NULL) {
		printf("%s", buffer);
	}
	fclose(dat);
	printf("\n\n\n");
	scanf_s(" %c", &throwaway);
}
void newRecipe() {
	FILE* dat;
	char newRecName[32];
	char filename[36];
	char filepath[MAX_PATH];
	printf("Enter name of new recipe: ");
	fgets(newRecName, sizeof(newRecName), stdin);	//scans user input for recipe name
	newRecName[strcspn(newRecName, "\n")] = 0;	//fgets appends (or reads?) the newline character from hitting enter to submit your input and thats a problem so this function just strips away that \n character
	snprintf(filename, sizeof(filename), "%s.txt", newRecName);	//takes the name the user inputted and adds .txt to the end so that the resulting file that is created lower down in this function will be a .txt file
	printf("Enter description of %s in the opened text file and save when done:\n", newRecName);
	snprintf(filepath, sizeof(filepath), "%s\\\"%s\"", dir, filename);	//this gets what will be the filepath of the created file and saves it to filepath
	fopen_s(&dat, filename, "w");										//created new file with the user inputted name of .txt type
	fclose(dat);														//closes newly created file
	setvbuf(dat, NULL, _IONBF, sizeof(dat));
	system(filepath);													//executes the .txt file to open it and allow users to easily type in recipe
	system("cls");														//clears the terminal
	listRecipes();														//updates recList with the new file created and lists the recipes again with the newly created recipe shown
}
void editRecipe(int n) {
	char filepath[MAX_PATH];
	snprintf(filepath, sizeof(filepath), "%s\\%s",dir,recList[n]);
	system(filepath);
}
void removeRecipe(int n) {}
void setDir() {
	//sets the working directory to the Recipes folder so that everything is nice and organized
	_getcwd(dir, sizeof(dir));								//gets current directory, should always be project folder
	snprintf(dir, sizeof(dir), "%s\\Recipes", dir);			//appends "Recipes" to the current working directory path and saves the resulting path to the dir variable defined at the beginning
	snprintf(opDir, sizeof(opDir), "%s\\*.txt", dir);		//this one appends "*.txt" to the end of the path from the previous step. this is necessary later for the function that scans the Recipes directory for all the recipe files
	if (_chdir(dir) == -1) { _mkdir(dir); }					//checks if Recipes folder exists. If not, it is created.
	_chdir(dir);											//finally sets the current working directory to the Recipes folder
}
void scanInput() {
	char select;
	printf("Input your selection: ");
	scanf_s(" %c", &select, sizeof(select));
	switch(select){
	int sel;
	case 's':
		//select recipe
		//need to add detection so that user can only pass int or program crashes
		printf("Enter recipe number: ");
		scanf_s("%d", &sel);
		openRecipe(sel);
		break;
	case 'n':
		//create new recipe
		newRecipe();
		break;
	case 'e':
		//edit existing recipe
		printf("Enter recipe number: ");
		scanf_s("%d", &sel);
		editRecipe(sel);
		break;
	case 'r':
		//remove recipe
		printf("remove recipe");
		break;
	default:
		printf("Invalid input. Try again.\n");
		break;
	}

}