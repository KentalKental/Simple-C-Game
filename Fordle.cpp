#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
struct Data{
	char word[11];
	int letters;
	struct Data*next;
}*head[2] = {NULL},*tail[2] = {NULL};

int letterChecker(char word[],char guess[]){
	int len = strlen(word),correct=0;
	for(int i =0;i<len;i++){
		if(word[i] == guess[i]) correct++;
	}
	return correct;
}

void pushQ(int curr_Player,char word[],char guess[]){
	struct Data*node = (struct Data*)malloc(sizeof(struct Data));
	strcpy(node->word,guess);
	node->letters= letterChecker(word,guess);
	node->next = NULL;
	if(!head[curr_Player]){
		head[curr_Player] = tail[curr_Player] = node;
	}
	else{
		tail[curr_Player]->next = node;
		tail[curr_Player] = tail[curr_Player]->next;
	}
}

void printGuesses(int curr_Player){
	if(head[curr_Player]){
		int n =1;
		struct Data*temp=head[curr_Player];
		while(temp){
			printf("%d. %s - %d letter(s) in the correct spot\n",n++,temp->word,temp->letters);
			temp = temp->next;
		}
	}
	else{
		printf("No Guesses yet !\n");
	}
}


void game(int n){
	int mode =0;
	while(mode !=4 && mode !=5){
		printf("Choose your game mode !\n1. 4 Letter words\n2. 5 Letter words\n>> ");
		scanf("%d",&n);
		switch(n){
			case 1:
				mode=4;
				system("cls");
				break;
			case 2:
				mode = 5;
				system("cls");
				break;
			default:
				printf("Input may be incorrect !\n");
				system("cls");
		}
	}
	
	// choose the word to predict
	int players = 2,curr_Player = 0;
	char words[players][mode*2+1];
	char word[12];
	
	while(true){
		printf("Choose your %d letter word !\n",mode);
		printf("Player %d's word : ",curr_Player+1);
		scanf("%s",word);
		system("cls");
		int len = strlen(word);
		if(len != mode){
			printf("Your word needs to be %d letters ! [Press ENTER to continue]\n",mode);
			getch();
			system("cls");
			continue;
		}
		else{
			strcpy(words[curr_Player++],word);
		}
		
		if(curr_Player == 2){
			system("cls");
			curr_Player =0;
			break;
		}
	}
	
	int winner=-1;
	// gameplay 
	while(true){
		printf("Player 1's Guesses :\n");
		printGuesses(0);
		puts("");
		printf("Player 2's Guesses :\n");
		printGuesses(1);
		puts("");
		printf("Player %d's turn to guess : ",curr_Player+1);
		scanf("%s",word);
		
		int len = strlen(word);
		if(len != mode){
			printf("Your word needs to be %d letters ! [Press ENTER to continue]\n",mode);
			getch();
			system("cls");
			continue;
		}
		else{
			pushQ(curr_Player,words[curr_Player],word);
			winner = (tail[curr_Player]->letters == mode ) ? curr_Player : -1 ;
		}
		if(winner != -1){
			printf("\nThe Winner is Player %d ! Congratulations !\n[Press ENTER to continue]",winner+1);
			getch();
			system("cls");
			return;
		}
		curr_Player++;
		if(curr_Player == 2) curr_Player = 0;
		system("cls");
	}
	
}

void howToPlay(){
	printf("2 Players, 1 Winner\n\nHow to play :\nThere are 2 players in this game and each of them has to guess a word that has been thought of by the opposing player.\n\nThere are unlimited tries, but the first one to guess is the winner !\n\nThis game currently has 2 modes : 4 letter words and 5 letter words.\n\n[Press ENTER to continue]");
	getch();
	system("cls");
}

int main(){
	int n;
	while(true){
		printf("Welcome to Fordle !\n1. Play Game !\n2. How to play ??\n3. Exit ...\n>> ");
		scanf("%d",&n);
		switch(n){
			case 1:
				system("cls");
				game(n);
				break;
			case 2:
				system("cls");
				howToPlay();
				break;
			case 3:
				printf("\nThank you for playing !!");
				return 0;
			default:
				printf("Input may be incorrect !\n");
				system("cls");
		}	
	}
}
