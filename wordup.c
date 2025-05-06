//Author: Jalen Atkins
//Date: 4/22/2025
//Purpose: Wordle

#include<stdio.h>
#include<stdbool.h>
#define GUESS 7
#define NUMBER 12
#define FILE1 "mystery.txt"

//Here are my prototypes
void read(char word[GUESS]);
int guess(int num, char guess1[GUESS]);
void gcheck(int length, char guess1[GUESS]);
void display(char trans[GUESS][GUESS], int num);
void search(char word[GUESS], char guess1[GUESS], int* stop);
void point(char word[GUESS], char guess1[GUESS], char point1[GUESS]);
void transcribe(char point1[GUESS], char word[GUESS], char guess1[GUESS], char trans[GUESS][GUESS], int num);
void logic(int num, int stop);

//My main function
int main(){
	int num = 0, i, length, stop;
	char word[GUESS], guess1[GUESS], point1[GUESS], trans[GUESS][GUESS];

//This gets the word to guess from the mystery.txt file	
	read(word);

//This runs through the guess and check until either the use is right or until they run out of guesses	
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

//Once they are through their guesses, this function decides what to display	
	logic(num, stop);
	
	return 0;
}

void read(char word[GUESS]){
	FILE *txt;

//Opening the file	
	txt = fopen(FILE1, "r");
	
	if(txt == NULL){
		printf("Could not open file\n");
	}

//Get the word from the file	
	fscanf(txt, "%s", word);

//Close the file	
	fclose(txt);
}

int guess(int num, char guess2[GUESS]){
	int length, i;

//This is for when the user is below 6 guesses	
	if(num < 5){
		printf("GUESS %d! Enter your guess: ", num+1);
		scanf("%s", guess2);	

//It gets the length of their word		
		for(length = 0; guess2[length] != '\0'; length++){}
		}
		
//This is for when the user is on their 6th guess
	else{
		printf("FINAL GUESS: ", num);
		scanf("%s", guess2);	
	
		for(length = 0; guess2[length] != '\0'; length++){}
	}

//I use pass by value to return the length of the word	
	return length;
}
	
void gcheck(int length, char guess2[GUESS]){
	int i;

//This checks the length of the word, and if it's not 5, asks for another word until it's a length of 5
	while(length != 5){
		printf("Guess must be 5 letters long\n");
		printf("Please try again: ");
		scanf("%s", guess2);
		for(length = 0; guess2[length] != '\0'; length++){}
	}
}

void search(char word[GUESS], char guess2[GUESS], int* stop){ 
	int i;

//I use pass by address to see how many letters the user correctly guessed
	*stop = 0;
	for(i = 0; guess2[i] != '\0'; i++){
		if(guess2[i] == word[i]){
			*stop = *stop+1;
//I capitalize every letter that is in the same place
			guess2[i] = guess2[i]-32;
		}
	}
}

void point(char word[GUESS], char guess2[GUESS], char point1[GUESS]){
	int i, j;

//I put the arrows into a different array, and filled the array with spaces beforehand
	for(i = 0; i <= 6; i++){
		point1[i] = ' ';
	}
	
//I put a null at the end of the point array to make it into a string
	point1[5] = '\0';

	for(i = 0; word[i] != '\0'; i++){
		for(j = 0; guess2[j] != '\0'; j++){
//This puts an arrow underneath every correct letter (but not in right place)
			if(guess2[j] == word[i]){
				point1[j] = '^';
			}
		}
	}
}

//This function stores both the point and guess arrays into a 2D array
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

//This just displays the 2D array
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

