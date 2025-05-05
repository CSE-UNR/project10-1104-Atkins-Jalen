//Author: Jalen Atkins
//Date: 4/22/2025
//Purpose: Wordle

#include<stdio.h>
#include<stdbool.h>
#define GUESS 7
#define NUMBER 12
#define FILE1 "mystery.txt"

void read(char word[GUESS]);
int guess(int num, char guess1[GUESS]);
void gcheck(int length, char guess1[GUESS]);
void display(char trans[GUESS][GUESS], int num);
void search(char word[GUESS], char guess1[GUESS], int* stop);
void point(char word[GUESS], char guess1[GUESS], char point1[GUESS]);
void transcribe(char point1[GUESS], char word[GUESS], char guess1[GUESS], char trans[GUESS][GUESS], int num);
void logic(int num, int stop);

void read(char word[GUESS]){
	FILE *txt;
	
	txt = fopen(FILE1, "r");
	
	if(txt == NULL){
		printf("Could not open file\n");
	}
	
	fscanf(txt, "%s", word);

	
	fclose(txt);
}

int guess(int num, char guess2[GUESS]){
	int length, i;
	
	if(num < 5){
		printf("GUESS %d! Enter your guess: ", num+1);
		scanf("%s", guess2);	
		
		for(length = 0; guess2[length] != '\0'; length++){}
		}
	else{
		printf("FINAL GUESS: ", num);
		scanf("%s", guess2);	
	
		for(length = 0; guess2[length] != '\0'; length++){}
	}
	
	return length;
}
	
void gcheck(int length, char guess2[GUESS]){
	int i;
	
	while(length != 5){
		printf("Guess must be 5 letters long\n");
		printf("Please try again: ");
		scanf("%s", guess2);
		for(length = 0; guess2[length] != '\0'; length++){}
	}
}

void search(char word[GUESS], char guess2[GUESS], int* stop){ 
	int i;

	*stop = 0;
	for(i = 0; guess2[i] != '\0'; i++){
		if(guess2[i] == word[i]){
			*stop = *stop+1;
			guess2[i] = guess2[i]-32;
		}
	}
}

void point(char word[GUESS], char guess2[GUESS], char point1[GUESS]){
	int i, j;

	for(i = 0; i <= 6; i++){
		point1[i] = ' ';
	}
	point1[5] = '\0';

	for(i = 0; word[i] != '\0'; i++){
		for(j = 0; guess2[j] != '\0'; j++){
			if(guess2[j] == word[i]){
				point1[j] = '^';
			}
		}
	}
}

void transcribe(char point1[GUESS], char word[GUESS], char guess2[GUESS], char trans[NUMBER][GUESS], int num){
	int y, j, i, t;
		
	for(i = 0; guess2[i] != '\0'; i++){
		if(num < 1){
			trans[num][i] = guess2[i];
			trans[num + 1][i] = point1[i];
		}
		else if(num >= 1){
			trans[num*2][i] = guess2[i];
			trans[num*2 + 1][i] = point1[i];
		}
	}
	
		trans[num*2-1][6] = '\0';
		trans[num*2][6] = '\0';
}

void display(char trans[GUESS][GUESS], int num){
	int i, j;
	
	printf("=================================\n");
	
	for(j = 0; j <= num*2 + 1; j++){
		printf("%s\n", trans[j]);
	}	
}

void logic(int num, int stop){
	if(num < 6){
		if(num < 1){
			printf("       You won in %d guess!\n", num);
			printf("            GOATED\n");
		}
		else if(num >= 1){
			printf("      You won in %d guesses!\n", num);
			printf("            Amazing!\n");
		}
	}
	else if(num >= 6){
		if(num == 6 && stop == 5){
			printf("       You won in %d guesses!\n", num);
			printf("            Amazing!\n");
		}
		else{
			printf("You lost, better luck next time!\n");
		}
	}
}
	
int main(){
	int num = 0, i, length, stop;
	char word[GUESS], guess1[GUESS], point1[GUESS], trans[GUESS][GUESS];
	
	read(word);
	
	do{
		length = guess(num, guess1);
		gcheck(length, guess1);
		
		search(word, guess1, &stop);
		
		if(stop < 5){
			point(word, guess1, point1);
			transcribe(point1, word, guess1, trans, num);
			display(trans, num);
		}
		num++;
	}while(num <= 5 && stop < 5);
	
	logic(num, stop);
	
	return 0;
}
