#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX 1000
#define SORTS 3

typedef struct log{
	char nameSort[30];
	int att;
	int cmp;
} log_t;

void printVet(int* vet);
void printLogs(int listVet[SORTS][MAX], log_t* logsSorts);
void orderLul(int* vet, log_t* logsSort, int nSort);
void selectionSort(int* vet, log_t* logsSort, int nSort);
void mergeSort(int* vet, int left, int right, log_t* logsSort, int nSort);
void merge(int* vet, int left, int middle, int right, log_t* logsSort, int nSort);

int main (void){
	log_t logsSort[SORTS];
	int vetsToOrder[SORTS+1][MAX];
	int contadorA, contadorB, rndNumber;
	
	srand(time(NULL));
	
	for (contadorA = 0; contadorA < MAX; contadorA++){
		rndNumber = rand() % MAX;
		
		for (contadorB = 0; contadorB < SORTS+1; contadorB++)
			vetsToOrder[contadorB][contadorA] = rndNumber;
	}
	
	for (contadorA = 0; contadorA < SORTS; contadorA++){
		logsSort[contadorA].att = 0;
		logsSort[contadorA].cmp = 0;
		switch(contadorA){
			case 0:
				strcpy(logsSort[contadorA].nameSort, "PROPRIO");
				orderLul(vetsToOrder[contadorA+1], logsSort, contadorA);
				break;
			case 1:
				strcpy(logsSort[contadorA].nameSort, "SELECTION");
				selectionSort(vetsToOrder[contadorA+1], logsSort, contadorA);
				break;
			case 2:
				strcpy(logsSort[contadorA].nameSort, "MERGE");
				mergeSort(vetsToOrder[contadorA+1], 0, MAX - 1, logsSort, contadorA);
				break;
			default:
				break;
		}
	}
	
	printLogs(vetsToOrder, logsSort);
}

void printVet(int* vet){
	int contadorA;
	
    for (contadorA = 0; contadorA < MAX; contadorA++)
    	printf("%d, ", vet[contadorA]);
}

void printLogs(int listVet[SORTS][MAX], log_t* logsSorts){
	int contadorA;
	
	printf("MATRIZ ORIGINAL\n\t");
	//printVet(listVet[0]);
	printf("\n\n\nSORTS\n");
	
	for (contadorA = 0; contadorA < SORTS; contadorA++){
		printf("\t%s\n\t\t", logsSorts[contadorA].nameSort);
		//printVet(listVet[contadorA+1]);
		printf("\n\t\tAtribuicoes: %d; Comparacoes: %d\n\n", logsSorts[contadorA].att, logsSorts[contadorA].cmp);
	}
}

void orderLul(int* vet, log_t* logsSort, int nSort){
	int contadorA, contadorB;
	
	for (contadorA = 0; contadorA < MAX - 1; contadorA++)
		for (contadorB = contadorA + 1; contadorB < MAX; contadorB++){
  	    	logsSort[nSort].cmp++;
			if (vet[contadorB] < vet[contadorA]){
				vet[contadorA] += vet[contadorB];
				vet[contadorB] = vet[contadorA] - vet[contadorB];
				vet[contadorA] -= vet[contadorB];
  	    		logsSort[nSort].att += 3;
			}
		}
}

void selectionSort(int* vet, log_t* logsSort, int nSort){
	int contadorA, contadorB, min;
	
	for (contadorA = 0; contadorA < MAX - 1; contadorA++){
		min = contadorA;
		for (contadorB = contadorA + 1; contadorB < MAX; contadorB++){
  	    	logsSort[nSort].cmp++;
			if (vet[min] > vet[contadorB])
				min = contadorB;
		}
		
  	    logsSort[nSort].cmp++;
	    if (min != contadorA){
			vet[contadorA] += vet[min];
			vet[min] = vet[contadorA] - vet[min];
			vet[contadorA] -= vet[min];
  	    	logsSort[nSort].att += 3;
		}
	}
}

void merge(int* vet, int left, int middle, int right, log_t* logsSort, int nSort){
	int contadorA, contadorB, contadorC;
    int lengthVetL = middle - left + 1;
    int lengthVetR = right - middle;
    
    int leftVet[lengthVetL], rightVet[lengthVetR];
 
    for (contadorA = 0; contadorA < lengthVetL; contadorA++)
        leftVet[contadorA] = vet[left + contadorA];

    for (contadorA = 0; contadorA < lengthVetR; contadorA++)
        rightVet[contadorA] = vet[middle + 1 + contadorA];

 
    contadorA = 0;
    contadorB = 0;
    contadorC = left;
    while ((contadorA < lengthVetL) && (contadorB < lengthVetR)){
		logsSort[nSort].cmp++;
	   	logsSort[nSort].att++;
        if (leftVet[contadorA] <= rightVet[contadorB]){
            vet[contadorC] = leftVet[contadorA];
            contadorA++;
        } else{
            vet[contadorC] = rightVet[contadorB];
            contadorB++;
        }
        contadorC++;
    }
    
    while (contadorA < lengthVetL){
    	logsSort[nSort].att++;
        vet[contadorC] = leftVet[contadorA];
        contadorA++;
        contadorC++;
    }
    
    while (contadorB < lengthVetR){
    	logsSort[nSort].att++;
        vet[contadorC] = rightVet[contadorB];
        contadorB++;
        contadorC++;
    }
}

void mergeSort(int* vet, int left, int right, log_t* logsSort, int nSort){
	int middle;
	
	logsSort[nSort].cmp++;
	if (left < right){
		//middle = (left + right) / 2 in case of large vector
		middle = left + ((right - left) / 2);
		
		mergeSort(vet, left, middle, logsSort, nSort);
		mergeSort(vet, middle+1, right, logsSort, nSort);
		
		merge(vet, left, middle, right, logsSort, nSort);
	}
}