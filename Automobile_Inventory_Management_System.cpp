//Nicholas Tan Peng Gen TP061291
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#pragma warning(disable:4996)

//Function Prototype
struct model* partCreator( int stock, char* partID, char* partName);
void CleanUp(struct model* list);
void fileAdder(struct model* list, char* modelName);
void inventoryUpdater();
char* rtrim(char* str, const char* seps);
struct model* searchModel(struct model* list, char* item);
void fileAdderSupplier(struct model* list1,struct model* list2, struct model* list3);
void inventoryTracker();
void inventorySearcher();
void inventoryCreator();

//structure used
struct model {
	char id[50];
	int stock;
	char date[200];
	char partName[50];
	char supplierName[50];
	char supplierCode[50];
	struct model* nextInLine;
};

//Calls appropriate functions based on the input of the user
void main() {

	int choice = 0;
	do {
		system("cls");
		choice = 0;
		printf("\n\n\t\tInventory Management System\n");
		printf("\n\t1. Inventory Parts Creation");
		printf("\n\t2. Inventory Parts Update");
		printf("\n\t3. Inventory Parts Tracking");
		printf("\n\t4. Inventory Search");
		printf("\n\t5. Exit");
		printf("\n\nWhat would you like to do? ");
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
			printf("\n\nEnter the number that corrosponds with your choice [e.g. 1 for Creating the Inventory Parts]: ");
			scanf_s("%d", &choice); while (getchar() != '\n');
		}
		switch (choice) {
		case 1:
			system("cls");
			inventoryCreator();
			break;
		case 2:
			system("cls");
			inventoryUpdater();
			break;
		case 3: 
			system("cls");
			inventoryTracker();
			break;
		case 4:
			system("cls");
			inventorySearcher();
			break;
		case 5:
			printf("Thank you for using Inventory Management System, have a nice day\n");
			printf("Exiting...\n");
			printf("Exited");
			break;
		}
		_getch();
	} while (choice != 5);
}

//Creates new structure and assigns the value of the members of the structure based on the value of the arguments received
struct model* partCreator(int stock, char *partID, char *partName) {
	struct model* newPart = NULL;
	time_t tm;
	time(&tm);
	char timeNow[100];
	strcpy(timeNow, ctime(&tm));
	newPart = (struct model*)malloc(sizeof(struct model));
	if (newPart != NULL) {
		newPart->nextInLine = NULL;
		newPart->stock = stock;
		strcpy(newPart->partName, partName);
		strcpy(newPart->id, partID);
		rtrim(timeNow, NULL);
		strcpy(newPart->date, timeNow);
	}
	return newPart;
}

//Cleans up the memory that has been dynamically allocated
void CleanUp(struct model *list)
{
	struct model* next;
	while (list)
	{
		next = list;
		list = list->nextInLine;
		free(next);
	}
	return;
}

//Initializes inventory of each part based on the user's input
//Has built in validation to prevent user from entering strings or characters or numbers other than the numbers shown
void inventoryCreator() {
	char modelName[10], item[30], header[100], codeName[5];
	int stock = -1;
	int flag = 0;
	int proceed = 0;
	FILE* fptrBlaze;
	FILE* fptrSilk;
	FILE* fptrArmer;
	struct model* blaze = NULL;
	struct model* silk = NULL;
	struct model* armer = NULL;
	struct model* added = NULL;
	printf("Initializing inventory");
	for (int i = 0; i < 3; i++) {
		added = NULL;
		switch (i) {
		case 0:
			strcpy(modelName, "Blaze");
			strcpy(codeName, "BLZ");
			break;
		case 1:
			strcpy(modelName, "Silk");
			strcpy(codeName, "SLK");
			break;
		case 2:
			strcpy(modelName, "Armer");
			strcpy(codeName, "ARM");
			break;
		}
		printf("\n\n=======================================================================\n");
		printf("\n\nCreating part inventory of %s\n\n", modelName);
		do {
			printf("\nDo you wish to continue? If you choose no, all other parts will be initialized to 0\n");
			printf("1. continue\n");
			printf("2. exit\n");
			printf("Enter your choice: ");
			scanf_s("%d", &proceed); while (getchar() != '\n');
			if (proceed != 1 && proceed != 2) {
				printf("\nPlease do not enter strings or numbers other than 1 or 2\n");
			}
		} while (proceed != 1 && proceed != 2);
		if (proceed == 2) {
			flag = 1;
		}
		for (int j = 1; j < 16; j++) {
			char leadingZeroes[10] = "";
			char partID[20];
			char modelPartName[20] = "";
			itoa(j, partID, 10);
			if (j < 10) {
				strcpy(leadingZeroes, "00");
			}
			else if (j < 100) {
				strcpy(leadingZeroes, "0");
			}
			strcat(modelPartName, codeName);
			strcat(modelPartName, "-");
			strcat(modelPartName, leadingZeroes);
			strcat(modelPartName, partID);
			switch (j) {
			case 1:
				strcpy(item, "engine block");
				break;
			case 2:
				strcpy(item, "piston");
				break;
			case 3:
				strcpy(item, "crankshaft");
				break;
			case 4:
				strcpy(item, "camshaft");
				break;
			case 5:
				strcpy(item, "cylinder head");
				break;
			case 6:
				strcpy(item, "bonet");
				break;
			case 7:
				strcpy(item, "bumper");
				break;
			case 8:
				strcpy(item, "door");
				break;
			case 9:
				strcpy(item, "windshield");
				break;
			case 10:
				strcpy(item, "wiper");
				break;
			case 11:
				strcpy(item, "mirror");
				break;
			case 12:
				strcpy(item, "headlights");
				break;
			case 13:
				strcpy(item, "compressor");
				break;
			case 14:
				strcpy(item, "condenser");
				break;
			case 15:
				strcpy(item, "evaporator");
				break;
			}
			if (flag == 0) {
				do {
					printf("\nEnter the number of %s: ", item);
					scanf_s("%d", &stock); while (getchar() != '\n');
					if (stock < 0) {
						printf("\nThe number you enter is invalid for initializing inventory stock. You cannot have negative stock of an inventory. Please enter whole numbers\n");
					}
				} while (stock < 0);
			}
			else {
				stock = 0;
			}
			if (i == 0) {
				if (blaze == NULL) {
					blaze = partCreator(stock, modelPartName, item );
					if (blaze != NULL) {
						added = blaze;
					}
				}
				else {
					added->nextInLine = partCreator(stock, modelPartName, item);
					if (added->nextInLine != NULL) {
						added = added->nextInLine;
					}
				}
			}
			else if (i == 1) {
				if (silk == NULL) {
					silk = partCreator(stock, modelPartName, item);
					if (silk != NULL) {
						added = silk;
					}
				}
				else {
					added->nextInLine = partCreator(stock, modelPartName, item);
					if (added->nextInLine != NULL) {
						added = added->nextInLine;
					}
				}
			}
			else if (i == 2) {
				if (armer == NULL) {
					armer = partCreator(stock, modelPartName, item);
					if (armer != NULL) {
						added = armer;
					}
				}
				else {
					added->nextInLine = partCreator(stock, modelPartName, item);
					if (added->nextInLine != NULL) {
						added = added->nextInLine;
					}
				}
			}
		}
		if (i == 0) {
			fileAdder(blaze, modelName);
		}
		else if (i == 1) {
			fileAdder(silk, modelName);
		}
		else if (i == 2) {
			fileAdder(armer, modelName);
		}
		CleanUp(blaze);
		CleanUp(silk);
		CleanUp(armer);
		added = NULL;
		blaze = NULL;
		silk = NULL;
		armer = NULL;
	}
	return;
}

//Gets data from linked list and puts it to the text files
void fileAdder(struct model* list, char *modelName){
	FILE* fptrBlaze;
	FILE* fptrArmer;
	FILE* fptrSilk;
	struct model* t;
	t = list;
	char header[] = "Part Name		       Part ID		Stock		Date Modified\n";
	if (strcmp(modelName, "Blaze")==0) {
		fopen_s(&fptrBlaze, "blaze.txt", "w");
		fprintf(fptrBlaze, header);
		while (t) {
			fprintf(fptrBlaze, "%-30s%-20s%-10d%-20s\n", t->partName, t->id, t->stock, t->date);
			t = t->nextInLine;
		}
		fclose(fptrBlaze);
	}
	else if (strcmp(modelName, "Silk")==0) {
		fopen_s(&fptrSilk, "silk.txt", "w");
		fprintf(fptrSilk, header);
		while (t) {
			fprintf(fptrSilk, "%-30s%-20s%-10d%-20s\n", t->partName, t->id, t->stock, t->date);
			t = t->nextInLine;
		}
		fclose(fptrSilk);
	}
	else if (strcmp(modelName, "Armer")==0) {
		fopen_s(&fptrArmer, "armer.txt", "w");
		fprintf(fptrArmer, header);
		while (t) {
			fprintf(fptrArmer, "%-30s%-20s%-10d%-20s\n", t->partName, t->id, t->stock, t->date);
			t = t->nextInLine;
		}
		fclose(fptrArmer);
	}
	CleanUp(t);
}

//Gets supplier details from the linked list and writes it to the text file
void fileAdderSupplier(struct model* list1, struct model* list2, struct model* list3) {
	FILE* fptrSupply;
	struct model* t, *g, *h;
	t = list1;
	g = list2;
	h = list3;
	char header[100] = "Part Name			Part ID		Stock		Date Modified				Supplier Name			Supplier Code\n";
	fopen_s(&fptrSupply, "supplier.txt", "w");
	fprintf(fptrSupply, header);
	while (t) {
		fprintf_s(fptrSupply, "%-30s%-20s%-10d%-40s%-40s%-20s\n", t->partName, t->id, t->stock, t->date, t->supplierName, t->supplierCode);
		t = t->nextInLine;
	}
	while (g) {
		fprintf_s(fptrSupply, "%-30s%-20s%-10d%-40s%-40s%-20s\n", g->partName, g->id, g->stock, g->date, g->supplierName, g->supplierCode);
		g = g->nextInLine;
	}
	while (h) {
		fprintf_s(fptrSupply, "%-30s%-20s%-10d%-40s%-40s%-20s\n", h->partName, h->id, h->stock, h->date, h->supplierName, h->supplierCode);
		h = h->nextInLine;
	}
	fclose(fptrSupply);
	CleanUp(t);
	CleanUp(g);
	CleanUp(h);
}

//Searches for the particular structure in the linked list that has the same part name as the argument received
struct model* searchModel(struct model* list, char *item) {
	struct model* temp = list;
	while (strcmp(temp->partName, item) != 0) {
		temp = temp->nextInLine;
	}
	if (strcmp(temp->partName, item) == 0) {
		return temp;
	}
	CleanUp(temp);
}

//Removes space from a string as well as newline and tab 
char* rtrim(char* str, const char* seps) {
	int i;
	if (seps == NULL) {
		seps = "\t\n\v\f\r ";
	}
	i = strlen(str) - 1;
	while (i >= 0 && strchr(seps, str[i]) != NULL) {
		str[i] = '\0';
		i--;
	}
	return str;
}

//Updates the stock that is contained in the textfile
void inventoryUpdater() {
	int choice = -1, choiceModel, partToUpdate = -1, addOrRemove = -1, num = 1, sizeBlaze =0, sizeSilk =0, sizeArmer =0; 
	char item[30];
	char modelName[30];
	char stockAmount[30];
	char partInfo[15][100];
	struct model* blaze = NULL;
	struct model* silk = NULL;
	struct model* armer = NULL;
	struct model* added = NULL;
	struct model* temp = NULL;
	FILE* fptrBlaze;
	FILE* fptrSilk;
	FILE* fptrArmer;
	fptrBlaze = fopen("blaze.txt", "r");
	fptrSilk = fopen("silk.txt", "r");
	fptrArmer = fopen("armer.txt", "r");
	if (fptrBlaze) { 
		fseek(fptrBlaze, 0, SEEK_END);
		sizeBlaze = ftell(fptrBlaze);
		fclose(fptrBlaze);
	}
	if (fptrSilk) { 
		fseek(fptrSilk, 0, SEEK_END);
		sizeSilk = ftell(fptrSilk);
		fclose(fptrSilk);
	}
	if (fptrArmer) { 
		fseek(fptrArmer, 0, SEEK_END);
		sizeArmer = ftell(fptrArmer);
		fclose(fptrArmer);
	}
	if (sizeBlaze == 0 || sizeSilk == 0 || sizeArmer == 0 || fptrBlaze == NULL || fptrSilk == NULL || fptrArmer == NULL) {
		printf("Error, inventory not initialized\n");
		printf("Please return to main menu and initiate the inventory by selecting the first option. ");
		printf("Press any key to continue... ");
		_getch();
		return; 
	}
	printf("Inventory Updater\n");
	printf("\n\n=======================================================================\n\n");
	printf("You can update the contents of each part in the inventory\n");
	do {
		printf("1. Blaze\n");
		printf("2. Silk\n");
		printf("3. Armer\n");
		printf("4. Exit\n");
		printf("Choose the inventory of the model that you would like to update. [e.g. enter 1 to update the inventory of blaze's warehouse]\n");
		printf("Enter choice: ");
		scanf_s("%d", &choice); while (getchar() != '\n');
		if (choice <0) {
			printf("\nPlease enter numbers according to the given choice. Do not enter strings or other irrelevent numbers.\n\n");
		}
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
	if (choice == 4) {
		return;
	}
	do {
		printf("\nChoose the part that you would like to update\n");
		printf("1. Engine Block\n");
		printf("2. Piston\n");
		printf("3. Crankshaft\n");
		printf("4. Camshaft\n");
		printf("5. Cylinder head\n");
		printf("6. Bonet\n");
		printf("7. Bumper\n");
		printf("8. Door\n");
		printf("9. Windshield\n");
		printf("10. Wiper\n");
		printf("11. Mirror\n");
		printf("12. Headlights\n");
		printf("13. Compressor\n");
		printf("14. Condenser\n");
		printf("15. Evaporator\n");
		printf("Enter choice: ");
		scanf_s("%d", &partToUpdate); while (getchar() != '\n');
		if (partToUpdate <= 0 || partToUpdate > 15) {
			printf("\nPlease enter numbers according to the given choice. Do not enter strings or other irrelevent numbers.\n\n");
		}
	} while (partToUpdate<= 0 || partToUpdate>15);
	switch (partToUpdate) {
		case 1:
			strcpy(item, "engine block");
			break;
		case 2:
			strcpy(item, "piston");
			break;
		case 3:
			strcpy(item, "crankshaft");
			break;
		case 4:
			strcpy(item, "camshaft");
			break;
		case 5:
			strcpy(item, "cylinder head");
			break;
		case 6:
			strcpy(item, "bonet");
			break;
		case 7:
			strcpy(item, "bumper");
			break;
		case 8:
			strcpy(item, "door");
			break;
		case 9:
			strcpy(item, "windshield");
			break;
		case 10:
			strcpy(item, "wiper");
			break;
		case 11:
			strcpy(item, "mirror");
			break;
		case 12:
			strcpy(item, "headlights");
			break;
		case 13:
			strcpy(item, "compressor");
			break;
		case 14:
			strcpy(item, "condenser");
			break;
		case 15:
			strcpy(item, "evaporator");
			break;
		}
	do {
		printf("\nDo you want to add or remove the part?\n");
		printf("1. Add\n");
		printf("2. Remove\n");
		printf("Enter choice: ");
		scanf_s("%d", &addOrRemove); while (getchar() != '\n');
		if (addOrRemove < 1 || addOrRemove >2) {
			printf("\nPlease enter numbers according to the given choice. Do not enter strings or other irrelevent numbers.\n\n");
		}
	} while (addOrRemove != 1 && addOrRemove != 2);
	fptrBlaze = fopen("blaze.txt", "r");
	fgetc(fptrBlaze);
	fgetc(fptrBlaze);
	fseek(fptrBlaze,49, SEEK_CUR );
	while (!feof(fptrBlaze)) {
		fseek(fptrBlaze, -2, SEEK_CUR);
		if (blaze == NULL)
		{
			added = blaze = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrBlaze);
		fgets(added->id, 21, fptrBlaze);
		fgets(stockAmount, 11, fptrBlaze);
		fgets(added->date, 35, fptrBlaze);
		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");

		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		fgetc(fptrBlaze);
		fgetc(fptrBlaze);
	}
	fclose(fptrBlaze);
	fptrSilk = fopen("silk.txt", "r");
	fseek(fptrSilk, 49, SEEK_CUR);
	fgetc(fptrSilk);
	fgetc(fptrSilk);
	while (!feof(fptrSilk)) {
		fseek(fptrSilk, -2, SEEK_CUR);
		if (silk == NULL)
		{
			added = silk = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrSilk);
		fgets(added->id, 21, fptrSilk);
		fgets(stockAmount, 11, fptrSilk);
		fgets(added->date, 35, fptrSilk);

		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");
		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		fgetc(fptrSilk);
		fgetc(fptrSilk);
	}
	fclose(fptrSilk);
	fptrArmer = fopen("armer.txt", "r");
	fgetc(fptrArmer);
	fgetc(fptrArmer);
	fseek(fptrArmer, 49, SEEK_CUR);
	while (!feof(fptrArmer)) {
		fseek(fptrArmer, -2, SEEK_CUR);
		if (armer == NULL)
		{
			added = armer = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrArmer);
		fgets(added->id, 21, fptrArmer);
		fgets(stockAmount, 11, fptrArmer);
		fgets(added->date, 31, fptrArmer);

		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");
		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		fgetc(fptrArmer);
		fgetc(fptrArmer);
	}
	fclose(fptrArmer);
	if (addOrRemove == 1) {
		do {
			if (num < 0) {
				printf("The number you enter is negative, please enter a whole number\n");
			}
			printf("\nEnter the number that you would like to increase %s for:", item);
			scanf_s("%d", &num); while (getchar() != '\n');
			if (choice == 1) {
				time_t tm;
				time(&tm);
				char timeNow[100];
				strcpy(timeNow, ctime(&tm));
				temp = searchModel(blaze, item);
				temp->stock = temp->stock + num;
				strcpy(temp->date, rtrim(timeNow, NULL));
				strcpy(modelName, "Blaze");
				fileAdder(blaze, modelName);
				fileAdderSupplier(armer, blaze, silk);
			}
			if (choice == 2) {
				time_t tm;
				time(&tm);
				char timeNow[100];
				strcpy(timeNow, ctime(&tm));
				temp = searchModel(silk, item);
				temp->stock = temp->stock + num;
				strcpy(temp->date, rtrim(timeNow, NULL));
				strcpy(modelName, "Silk");
				fileAdder(silk, modelName);
				fileAdderSupplier(armer, blaze, silk);

			}
			if (choice == 3) {
				time_t tm;
				time(&tm);
				char timeNow[100];
				strcpy(timeNow, ctime(&tm));
				temp = searchModel(armer, item);
				temp->stock = temp->stock + num;
				strcpy(temp->date, rtrim(timeNow, NULL));
				strcpy(modelName, "Armer");
				fileAdder(armer, modelName);
				fileAdderSupplier(armer, blaze, silk);

			}
		} while (num < 0);
	}
	else if(addOrRemove == 2) {
		do {
			printf("\nEnter the number that you would like to decrease %s for:", item);
			scanf_s("%d", &num); while (getchar() != '\n');
			while (num < 0) {
				printf("The number you enter is negative, please enter a whole number\n");
				printf("\nEnter the number that you would like to decrease %s for:", item);
				scanf_s("%d", &num); while (getchar() != '\n');
			}
			if (choice == 1) {
				temp = searchModel(blaze, item);
				if (temp->stock < num) {
					printf("Error, the amount of stock of %s in blaze's warehouse is lesser then the amount you are requesting.\n", item);
					printf("Please reduce the amount or consider ordering more stock\n");
					num = -1;
					continue;
				}
				else {
					time_t tm;
					time(&tm);
					char timeNow[100];
					strcpy(timeNow, ctime(&tm));
					strcpy(temp->date, rtrim(timeNow, NULL));
					temp->stock = temp->stock - num;
					strcpy(modelName, "Blaze");
					fileAdder(blaze, modelName);
					fileAdderSupplier(armer, blaze, silk);
				}
			}
			if (choice == 2) {
				temp = searchModel(silk, item);
				if (temp->stock < num) {
					printf("Error, the amount of stock of %s in blaze's warehouse is lesser then the amount you are requesting.\n", item);
					printf("Please reduce the amount or consider ordering more stock\n");
					num = -1;
					continue;
				}
				else {
					time_t tm;
					time(&tm);
					char timeNow[100];
					strcpy(timeNow, ctime(&tm));
					strcpy(temp->date, rtrim(timeNow, NULL));
					temp->stock = temp->stock - num;
					strcpy(modelName, "Silk");
					fileAdder(silk, modelName);
					fileAdderSupplier(armer, blaze, silk);
				}
			}
			if (choice == 3) { 
				temp = searchModel(armer, item);
				if (temp->stock < num) {
					printf("Error, the amount of stock of %s in blaze's warehouse is lesser then the amount you are requesting.\n", item);
					printf("Please reduce the amount or consider ordering more stock\n");
					num = -1;
					continue;
				}
				else {
					time_t tm;
					time(&tm);
					char timeNow[100];
					strcpy(timeNow, ctime(&tm));
					strcpy(temp->date, rtrim(timeNow, NULL));
					temp->stock = temp->stock - num;
					strcpy(modelName, "Armer");
					fileAdder(armer, modelName);
					fileAdderSupplier(armer, blaze, silk);
				}
			}
		} while (num < 0); 
	}
	CleanUp(blaze);
	CleanUp(silk);
	CleanUp(armer);
	return;
}

//inventoryTracker function displays the record of all the part in the text file of the warehouse that has been selected by the user
void inventoryTracker() {
	int choice=-1, option = -1, flag = 0, sizeBlaze = 0, sizeSilk = 0, sizeArmer = 0;
	struct model* blaze = NULL;
	struct model* silk = NULL;
	struct model* armer = NULL;
	struct model* added = NULL;
	char stockAmount[30];
	FILE* fptrBlaze;
	FILE* fptrSilk;
	FILE* fptrArmer;
	fptrBlaze = fopen("blaze.txt", "r");
	fptrSilk = fopen("silk.txt", "r");
	fptrArmer = fopen("armer.txt", "r");
	if (fptrBlaze) {
		fseek(fptrBlaze, 0, SEEK_END);
		sizeBlaze = ftell(fptrBlaze);
		fclose(fptrBlaze);
	}
	if (fptrSilk) {
		fseek(fptrSilk, 0, SEEK_END);
		sizeSilk = ftell(fptrSilk);
		fclose(fptrSilk);
	}
	if (fptrArmer) {
		fseek(fptrArmer, 0, SEEK_END);
		sizeArmer = ftell(fptrArmer);
		fclose(fptrArmer);
	}
	if (sizeBlaze == 0 || sizeSilk == 0 || sizeArmer == 0 || fptrBlaze == NULL || fptrSilk == NULL || fptrArmer == NULL) {
		printf("Error, inventory not initialized\n");
		printf("Please return to main menu and initiate the inventory by selecting the first option. ");
		printf("Press any key to continue... ");
		_getch();
		return;
	}
	do {
		printf("Warehouse selection\n");
		printf("\n\n=======================================================================\n\n");
		printf("1. Blaze\n");
		printf("2. Silk\n");
		printf("3. Armer\n");
		printf("4. All warehouses\n");
		printf("5. Exit\n");
		printf("Enter your warehouse of choice: "); 
		scanf_s("%d", &choice); while (getchar() != '\n');
		if (choice < 1 || choice > 4) {
			printf("\nPlease enter numbers according to the given choice. Do not enter strings or other irrelevent numbers.\n\n");
		}
		if (choice == 5) {
			printf("Exiting...");
			return;
		}
	} while (choice!= 1 && choice != 2 && choice != 3 && choice != 4);
	do {
		printf("\nInventory tracking options\n\n");
		printf("1. Total available quantity of all parts\n");
		printf("2. Record of parts with less than 10 units\n");
		printf("Enter your choice: ");
		scanf_s("%d", &option); while (getchar() != '\n');
		if (option != 1 && option != 2) {
			printf("\nPlease enter numbers according to the given choice. Do not enter strings or other irrelevent numbers.\n\n");
		}
	} while (option != 1 && option != 2);
	if (choice == 1) {
		fptrBlaze = fopen("blaze.txt", "r");
		fgetc(fptrBlaze);
		fgetc(fptrBlaze);
		fseek(fptrBlaze, 49, SEEK_CUR);
		while (!feof(fptrBlaze)) {
			fseek(fptrBlaze, -2, SEEK_CUR);
			if (blaze == NULL)
			{
				added = blaze = (struct model*)malloc(sizeof(struct model));
			}
			else
			{
				added->nextInLine = (struct model*)malloc(sizeof(struct model));
				added = added->nextInLine;
			}
			fgets(added->partName, 31, fptrBlaze);
			fgets(added->id, 21, fptrBlaze);
			fgets(stockAmount, 11, fptrBlaze);
			fgets(added->date, 35, fptrBlaze);
			rtrim(added->partName, NULL);
			rtrim(added->id, NULL);
			rtrim(added->date, NULL);
			rtrim(stockAmount, NULL);
			if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
				strcpy(added->supplierName, "Dives La Victoria");
				strcpy(added->supplierCode, "DLV");

			}
			else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
				strcpy(added->supplierName, "Future Motors");
				strcpy(added->supplierCode, "FM");
			}
			else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
				strcpy(added->supplierName, "Tiger Motors");
				strcpy(added->supplierCode, "TM");
			}
			added->stock = atoi(stockAmount);
			added->nextInLine = NULL;
			fgetc(fptrBlaze);
			fgetc(fptrBlaze);
		}
		fclose(fptrBlaze);
		if (option == 1) {
			added = blaze;
			printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
			while (added) {
				printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
				added = added->nextInLine;
				
			}
		}
		else if (option == 2) {
			added = blaze;
			while (added) {
				if (added->stock < 10) {
					if (flag == 0) {
						printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
						flag = 1;
					}
					printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
					
					
				}
				added = added->nextInLine;
			}
			if (flag == 0) {
				printf("\nAll items in Blaze inventory have at least 10 stock.\n"); 
			}
		}
	}
	else if (choice == 2) {
		fptrSilk = fopen("silk.txt", "r");
		fseek(fptrSilk, 49, SEEK_CUR);
		fgetc(fptrSilk);
		fgetc(fptrSilk);
		while (!feof(fptrSilk)) {
			fseek(fptrSilk, -2, SEEK_CUR);
			if (silk == NULL)
			{
				added = silk = (struct model*)malloc(sizeof(struct model));
			}
			else
			{
				added->nextInLine = (struct model*)malloc(sizeof(struct model));
				added = added->nextInLine;
			}
			fgets(added->partName, 31, fptrSilk);
			fgets(added->id, 21, fptrSilk);
			fgets(stockAmount, 11, fptrSilk);
			fgets(added->date, 35, fptrSilk);

			rtrim(added->partName, NULL);
			rtrim(added->id, NULL);
			rtrim(added->date, NULL);
			rtrim(stockAmount, NULL);
			if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
				strcpy(added->supplierName, "Dives La Victoria");
				strcpy(added->supplierCode, "DLV");
			}
			else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
				strcpy(added->supplierName, "Future Motors");
				strcpy(added->supplierCode, "FM");
			}
			else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
				strcpy(added->supplierName, "Tiger Motors");
				strcpy(added->supplierCode, "TM");
			}
			added->stock = atoi(stockAmount);
			added->nextInLine = NULL;
			added->nextInLine = NULL;
			fgetc(fptrSilk);
			fgetc(fptrSilk);
		}
		fclose(fptrSilk);
		if (option == 1) {
			added = silk;
			printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
			while (added) {
				printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
				added = added->nextInLine;
				
			}
			while (getchar() != '\n');
		}
		else if (option == 2) {
			added = silk;
			while (added) {
				if (added->stock < 10) {
					if (flag == 0) {
						printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");;
						flag = 1;
					}
					printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
					
					
				}
				added = added->nextInLine;
			}
			if (flag == 0) {
				printf("\nAll items in Silk inventory have at least 10 stock.\n");
			}
		}
	}
	else if (choice == 3) {
		fptrArmer = fopen("armer.txt", "r");
		fgetc(fptrArmer);
		fgetc(fptrArmer);
		fseek(fptrArmer, 49, SEEK_CUR);
		while (!feof(fptrArmer)) {
			fseek(fptrArmer, -2, SEEK_CUR);
			if (armer == NULL)
			{
				added = armer = (struct model*)malloc(sizeof(struct model));
			}
			else
			{
				added->nextInLine = (struct model*)malloc(sizeof(struct model));
				added = added->nextInLine;
			}
			fgets(added->partName, 31, fptrArmer);
			fgets(added->id, 21, fptrArmer);
			fgets(stockAmount, 11, fptrArmer);
			fgets(added->date, 31, fptrArmer);

			rtrim(added->partName, NULL);
			rtrim(added->id, NULL);
			rtrim(added->date, NULL);
			rtrim(stockAmount, NULL);
			if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
				strcpy(added->supplierName, "Dives La Victoria");
				strcpy(added->supplierCode, "DLV");
			}
			else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
				strcpy(added->supplierName, "Future Motors");
				strcpy(added->supplierCode, "FM");
			}
			else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
				strcpy(added->supplierName, "Tiger Motors");
				strcpy(added->supplierCode, "TM");
			}
			added->stock = atoi(stockAmount);
			added->nextInLine = NULL;
			fgetc(fptrArmer);
			fgetc(fptrArmer);
		}
		fclose(fptrArmer);
		if (option == 1) {
			added = armer;
			printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
			while (added) {
				printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
				added = added->nextInLine;
				
			}
		}
		else if (option == 2) {
			added = armer;
			while (added) {
				if (added->stock < 10) {
					if (flag == 0) {
						printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
						flag = 1;
					}
					printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
					
					
				}
				added = added->nextInLine;
			}
			if (flag == 0) {
				printf("\nAll items in Armer inventory have at least 10 stock.\n"); 
			}
		}
	}
	else if (choice == 4) {
	fptrBlaze = fopen("blaze.txt", "r");
	fgetc(fptrBlaze);
	fgetc(fptrBlaze);
	fseek(fptrBlaze, 49, SEEK_CUR);
	while (!feof(fptrBlaze)) {
		fseek(fptrBlaze, -2, SEEK_CUR);
		if (blaze == NULL)
		{
			added = blaze = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrBlaze);
		fgets(added->id, 21, fptrBlaze);
		fgets(stockAmount, 11, fptrBlaze);
		fgets(added->date, 35, fptrBlaze);
		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");

		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		fgetc(fptrBlaze);
		fgetc(fptrBlaze);
	}
	fclose(fptrBlaze);
	fptrSilk = fopen("silk.txt", "r");
	fseek(fptrSilk, 49, SEEK_CUR);
	fgetc(fptrSilk);
	fgetc(fptrSilk);
	while (!feof(fptrSilk)) {
		fseek(fptrSilk, -2, SEEK_CUR);
		if (silk == NULL)
		{
			added = silk = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrSilk);
		fgets(added->id, 21, fptrSilk);
		fgets(stockAmount, 11, fptrSilk);
		fgets(added->date, 35, fptrSilk);

		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");
		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		added->nextInLine = NULL;
		fgetc(fptrSilk);
		fgetc(fptrSilk);
	}
	fclose(fptrSilk);
	fptrArmer = fopen("armer.txt", "r");
	fgetc(fptrArmer);
	fgetc(fptrArmer);
	fseek(fptrArmer, 49, SEEK_CUR);
	while (!feof(fptrArmer)) {
		fseek(fptrArmer, -2, SEEK_CUR);
		if (armer == NULL)
		{
			added = armer = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrArmer);
		fgets(added->id, 21, fptrArmer);
		fgets(stockAmount, 11, fptrArmer);
		fgets(added->date, 31, fptrArmer);

		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");
		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		fgetc(fptrArmer);
		fgetc(fptrArmer);
	}
	fclose(fptrArmer);
	if (option == 1) {
		added = armer;
		printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
		while (added) {
			printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
			added = added->nextInLine;

		}
		added = blaze;
		while (added) {
			printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
			added = added->nextInLine;

		}
		added = silk;
		while (added) {
			printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
			added = added->nextInLine;

		}
		_getch();
	}
	else if (option == 2) {
		added = armer;
		while (added) {
			if (added->stock < 10) {
				if (flag == 0) {
					printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");;
					flag = 1;
				}
				printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
			}
			added = added->nextInLine;
		}
		added = blaze;
		while (added) {
			if (added->stock < 10) {
				if (flag == 0) {
					printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");;
					flag = 1;
				}
				printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
			}
			added = added->nextInLine;
		}
		added = silk;
		while (added) {
			if (added->stock < 10) {
				if (flag == 0) {
					printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");;
					flag = 1;
				}
				printf("%-30s%-20s%-10d%-40s%-40s%-40s\n", added->partName, added->id, added->stock, added->date, added->supplierName, added->supplierCode);
			}
			added = added->nextInLine;
		}
		if (flag == 0) {
			printf("\nAll items in all warehouses have at least 10 stocks.\n");
		}
	}
	}

	CleanUp(blaze);
	CleanUp(silk);
	CleanUp(armer);
	return;
}

// Displays the informtion of the supplier of a part or all the data related with the part based on the part ID of that part
void inventorySearcher() {
	int choice = -1, flag=0, secondFlag=0, sizeBlaze = 0, sizeSilk = 0, sizeArmer = 0;
	char partID[60];
	struct model* blaze = NULL;
	struct model* silk = NULL;
	struct model* armer = NULL;
	struct model* added = NULL;
	struct model* temp = NULL;
	char stockAmount[30];
	FILE* fptrBlaze;
	FILE* fptrSilk;
	FILE* fptrArmer;
	fptrBlaze = fopen("blaze.txt", "r");
	fptrSilk = fopen("silk.txt", "r");
	fptrArmer = fopen("armer.txt", "r");
	if (fptrBlaze) {
		fseek(fptrBlaze, 0, SEEK_END);
		sizeBlaze = ftell(fptrBlaze);
		fclose(fptrBlaze);
	}
	if (fptrSilk) {
		fseek(fptrSilk, 0, SEEK_END);
		sizeSilk = ftell(fptrSilk);
		fclose(fptrSilk);
	}
	if (fptrArmer) {
		fseek(fptrArmer, 0, SEEK_END);
		sizeArmer = ftell(fptrArmer);
		fclose(fptrArmer);
	}
	if (sizeBlaze == 0 || sizeSilk == 0 || sizeArmer == 0 || fptrBlaze == NULL || fptrSilk == NULL || fptrArmer == NULL) {
		printf("Error, inventory not initialized\n");
		printf("Please return to main menu and initiate the inventory by selecting the first option. ");
		printf("Press any key to continue... ");
		_getch();
		return;
	}
	fptrBlaze = fopen("blaze.txt", "r");
	fgetc(fptrBlaze);
	fgetc(fptrBlaze);
	fseek(fptrBlaze, 49, SEEK_CUR);
	while (!feof(fptrBlaze)) {
		fseek(fptrBlaze, -2, SEEK_CUR);
		if (blaze == NULL)
		{
			added = blaze = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrBlaze);
		fgets(added->id, 21, fptrBlaze);
		fgets(stockAmount, 11, fptrBlaze);
		fgets(added->date, 35, fptrBlaze);
		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");

		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		fgetc(fptrBlaze);
		fgetc(fptrBlaze);
	}
	fclose(fptrBlaze);
	fptrSilk = fopen("silk.txt", "r");
	fseek(fptrSilk, 49, SEEK_CUR);
	fgetc(fptrSilk);
	fgetc(fptrSilk);
	while (!feof(fptrSilk)) {
		fseek(fptrSilk, -2, SEEK_CUR);
		if (silk == NULL)
		{
			added = silk = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrSilk);
		fgets(added->id, 21, fptrSilk);
		fgets(stockAmount, 11, fptrSilk);
		fgets(added->date, 35, fptrSilk);

		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");
		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		added->nextInLine = NULL;
		fgetc(fptrSilk);
		fgetc(fptrSilk);
	}
	fclose(fptrSilk);
	fptrArmer = fopen("armer.txt", "r");
	fgetc(fptrArmer);
	fgetc(fptrArmer);
	fseek(fptrArmer, 49, SEEK_CUR);
	while (!feof(fptrArmer)) {
		fseek(fptrArmer, -2, SEEK_CUR);
		if (armer == NULL)
		{
			added = armer = (struct model*)malloc(sizeof(struct model));
		}
		else
		{
			added->nextInLine = (struct model*)malloc(sizeof(struct model));
			added = added->nextInLine;
		}
		fgets(added->partName, 31, fptrArmer);
		fgets(added->id, 21, fptrArmer);
		fgets(stockAmount, 11, fptrArmer);
		fgets(added->date, 31, fptrArmer);

		rtrim(added->partName, NULL);
		rtrim(added->id, NULL);
		rtrim(added->date, NULL);
		rtrim(stockAmount, NULL);
		if (strcmp(added->partName, "engine block") == 0 || strcmp(added->partName, "piston") == 0 || strcmp(added->partName, "crankshaft") == 0 || strcmp(added->partName, "camshaft") == 0 || strcmp(added->partName, "cylinder head") == 0) {
			strcpy(added->supplierName, "Dives La Victoria");
			strcpy(added->supplierCode, "DLV");
		}
		else if (strcmp(added->partName, "bonet") == 0 || strcmp(added->partName, "bumper") == 0 || strcmp(added->partName, "door") == 0 || strcmp(added->partName, "windshield") == 0 || strcmp(added->partName, "wiper") == 0 || strcmp(added->partName, "mirror") == 0 || strcmp(added->partName, "headlights") == 0) {
			strcpy(added->supplierName, "Future Motors");
			strcpy(added->supplierCode, "FM");
		}
		else if (strcmp(added->partName, "compressor") == 0 || strcmp(added->partName, "condenser") == 0 || strcmp(added->partName, "evaporator") == 0) {
			strcpy(added->supplierName, "Tiger Motors");
			strcpy(added->supplierCode, "TM");
		}
		added->stock = atoi(stockAmount);
		added->nextInLine = NULL;
		fgetc(fptrArmer);
		fgetc(fptrArmer);
	}
	fclose(fptrArmer);
	do {
		printf("\nInventory searcher\n");
		printf("1. Part's record by ID\n");
		printf("2. Supplier's detail by part ID\n");
		printf("Enter your choice: ");
		scanf_s("%d", &choice); while (getchar() != '\n');
		if (choice != 1 && choice != 2) {
			printf("\nPlease enter numbers according to the given choice. Do not enter strings or other irrelevent numbers.\n\n");
		}
	} while (choice != 1 && choice != 2);
	if (choice == 1) {
		do {
			printf("\nPlease enter the part ID. e.g. BLZ-001\n");
			printf("Enter part ID: ");
			gets_s(partID); 
			for (int i = 0; partID[i] != '\0'; i++) 
			{
				/*
				 * If current character is lowercase alphabet then
				 * convert it to uppercase.
				 */
				if (partID[i] >= 'a' && partID[i] <= 'z')
				{
					partID[i] = partID[i] - 32;
				}
			}
			added = silk;
			while (added) {
				if (strstr(added->id, partID) != NULL) {
					flag = 1;
					temp = added;
					if (secondFlag == 0) {
						secondFlag = 1;
						printf("\n%-30s%-20s%-10s%-20s\n", "Part Name", "Part ID", "Stock", "Date Modified");
					}
					printf("%-30s%-20s%-10d%-20s\n", temp->partName, temp->id, temp->stock, temp->date);
				}
				added = added->nextInLine;
			}

			added = blaze;
			while (added) {
				if (strstr(added->id, partID) != NULL) {
					flag = 1;
					temp = added;
					if (secondFlag == 0) {
						secondFlag = 1;
						printf("\n%-30s%-20s%-10s%-20s\n", "Part Name", "Part ID", "Stock", "Date Modified");
					}
					printf("%-30s%-20s%-10d%-20s\n", temp->partName, temp->id, temp->stock, temp->date);
				}
				added = added->nextInLine;
			}
			added = armer;
			while (added) {
				if (strstr(added->id, partID) != NULL) {
					flag = 1;
					temp = added;
					if (secondFlag == 0) {
						secondFlag = 1;
						printf("\n%-30s%-20s%-10s%-20s\n", "Part Name", "Part ID", "Stock", "Date Modified");
					}
					printf("%-30s%-20s%-10d%-20s\n", temp->partName, temp->id, temp->stock, temp->date);
				}
				added = added->nextInLine;
			}
			if (flag == 0) {
				printf("\nError, Part ID entered is not in inventory\n");
				printf("Please enter a valid partID\n");
			}
		} while (flag != 1);
	}
	else if (choice == 2) {
		do {
			printf("Please enter the part ID. e.g. BLZ-001\n");
			printf("Enter part ID: ");
			gets_s(partID);
			for (int i = 0; partID[i] != '\0'; i++) 
			{
				if (partID[i] >= 'a' && partID[i] <= 'z')
				{
					partID[i] = partID[i] - 32;
				}
			}
			added = silk;
			while (added) {
				if (strstr(added->id, partID) != NULL) {
					flag = 1;
					temp = added;
					if (secondFlag == 0) {
						secondFlag = 1;
						printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
					}
					printf("%-30s%-20s%-10d%-40s%-40s%-20s\n", temp->partName, temp->id, temp->stock, temp->date, temp->supplierName, temp->supplierCode);

				}
				added = added->nextInLine;
			}

			added = blaze;
			while (added) {
				if (strstr(added->id, partID) != NULL) {
					flag = 1;
					temp = added;
					if (secondFlag == 0) {
						secondFlag = 1;
						printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
					}
					printf("%-30s%-20s%-10d%-40s%-40s%-20s\n", temp->partName, temp->id, temp->stock, temp->date, temp->supplierName, temp->supplierCode);

				}
				added = added->nextInLine;
			}
			added = armer;
			while (added) {
				if (strstr(added->id, partID) != NULL) {
					flag = 1;
					temp = added;
					if (secondFlag == 0) {
						secondFlag = 1;
						printf("\n%-30s%-20s%-10s%-40s%-40s%-40s\n", "Part Name", "Part ID", "Stock", "Date Modified", "Supplier Name", "Supplier Code");
					}
					printf("%-30s%-20s%-10d%-40s%-40s%-20s\n", temp->partName, temp->id, temp->stock, temp->date, temp->supplierName, temp->supplierCode);

				}
				added = added->nextInLine;
			}
			if (flag == 0) {
				printf("\nError, Part ID entered is not in inventory\n");
				printf("Please enter a valid partID\n");
			}
		} while (flag != 1);
	}
	CleanUp(blaze);
	CleanUp(silk);
	CleanUp(armer);
	return;
}