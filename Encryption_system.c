/*
This project was created by: 109024 & 85778
Everything will be explained by very detailed comments below.
We wrote this project with love and care to make it as easy as possible for you to use.
We were so excited to make this project and we hope you enjoy it.
*/

#include <stdio.h> //for the basic input and output functions
#include <stdlib.h> //for the general functions
#include <string.h> //for the string functions

void main_menu();
int add_new_sentences();
void display_all_sentences(int last_adding_sentence_index);
int select_a_sentence(int last_adding_sentence_index, int selected_sentence);
void selecting_menu ();
void display_a_sentence (int selected_sentence);
void modify_a_sentence (int selected_sentence);
void encrypt_a_sentence (int selected_sentence, int shift_value);
void decrypt_a_sentence (int selected_sentence, int shift_value);
void save_sentences_file (int last_adding_sentence_index);
void load_sentence_file (int *last_adding_sentence_index);
void quit_the_program ();
void cls();

char sentences[20][100]; //two dimentions array for the sentences
FILE *saving; //the file for saving the sentences

int main () {
    int main_menu_choice; //the choice of the user in the main menu
    int last_adding_sentence_index = 0; //the index of the last sentence added to the sentences array
    int selected_sentence; //the index of the selected sentence
    int selected_sentence_menu_choice; //the choice of the user in the selected sentence menu
    int encrypt_or_decrypt_choice; //the choice of the user in the encrypt or decrypt menu
    int shift_value; //the shift value of the encryption or decryption
    do {
        main_menu(); //display the main menu
        scanf("%d", &main_menu_choice);
        switch(main_menu_choice) { //switch the choice of the user in the main menu
            case 1:
                cls(); //clear the screen
                printf("\t\t\tAdd a new sentences\n");
                printf("\t\tStart adding new sentences now!\n");
                printf("\t\tWhen you want to stop adding sentences, just enter a 'None'\n");
                printf("\n");
                last_adding_sentence_index = add_new_sentences(); //get the index of the last sentence added to the sentences array
                break;
            case 2:
                cls(); //clear the screen
                printf("\t\t\tDisplay all sentences\n");
                printf("\t\tAll sentences are:\n");
                display_all_sentences(last_adding_sentence_index); //display all the sentences
                break;
            case 3:
                cls(); //clear the screen
                printf("\t\t\tSelect a sentence\n");
                do {
                    printf("\t\tEnter the number of the sentence you want to select: ");
                    scanf("%d", &selected_sentence);
                } while (selected_sentence > last_adding_sentence_index); //make sure the user entered a valid sentence index
                selected_sentence = select_a_sentence(last_adding_sentence_index, selected_sentence);
                if (selected_sentence == -1) {
                    printf("\t\tThe sentence you selected does not exist!\n");
                    getchar();
                } else {
                    do {
                        selecting_menu(); //display the selecting menu
                        scanf("%d", &selected_sentence_menu_choice);
                        switch (selected_sentence_menu_choice) { //switch the choice of the user in the selecting menu
                            case 1:
                                cls(); //clear the screen
                                printf("\t\t\tDisplay a sentence\n");
                                display_a_sentence (selected_sentence);
                                break;
                            case 2:
                                cls(); //clear the screen
                                printf("\t\t\tModify a sentence\n");
                                modify_a_sentence (selected_sentence);
                                break;
                            case 3:
                                cls(); //clear the screen
                                printf("\t\t\tEncrypting a sentence\n");
                                do { //make sure the user entered a valid shift value
                                    printf("\t\tEnter how much characters you want to shift by: ");
                                    scanf("%d", &shift_value);
                                } while (shift_value < 0 || shift_value > 26);
                                encrypt_a_sentence (selected_sentence, shift_value);
                                printf("\t\tThe sentence has been encrypted!\n");
                                getchar(); //wait for the user to press a key to continue
                                getchar();
                                break;
                            case 4:
                                cls(); //clear the screen
                                printf("\t\t\tDecrypting a sentence\n");
                                do { //make sure the user entered a valid shift value 
                                    printf("\t\tEnter the shifing key: ");
                                    scanf("%d", &shift_value);
                                } while (shift_value < 0 || shift_value > 26);
                                decrypt_a_sentence (selected_sentence, shift_value);
                                printf("\t\tThe sentence has been decrypted!\n");
                                getchar();
                                getchar(); //wait for the user to press a key to continue
                                break;
                            case 5:
                                cls(); //clear the screen
                                printf("\t\t\tBack to main menu\n");
                                getchar();
                                main_menu(); //display the main menu
                                break;
                            default:
                                cls(); //clear the screen
                                printf("\t\t\tInvalid choice!\n");
                                getchar(); //wait for the user to press a key to continue
                        }
                    } while (selected_sentence_menu_choice != 5);
                }
                break;
            case 4:
                cls(); //clear the screen
                printf("\t\t\tEncrypt or decrypt all sentences\n");
                printf("\t\tChoose:\n\t\t\t1::Encrypt\t2::Decrypt\n");
                scanf("%d", &encrypt_or_decrypt_choice);
                switch (encrypt_or_decrypt_choice){ //switch the choice of the user in the encrypt or decrypt menu
                    case 1:
                        cls(); //clear the screen
                        printf("\t\t\tEncrypting all sentences\n");
                        do { //make sure the user entered a valid shift value
                            printf("\t\tEnter how much characters you want to shift by: ");
                            scanf("%d", &shift_value);
                        } while (shift_value < 0 || shift_value > 26);
                        for (int i = 0; i <= last_adding_sentence_index; i++) { //encrypt all the sentences
                            encrypt_a_sentence (i, shift_value);
                        }
                        printf("\t\tAll sentences have been encrypted!\n");
                        getchar();
                        getchar(); //wait for the user to press a key to continue
                        break;
                    case 2:
                        cls(); //clear the screen
                        printf("\t\t\tDecrypting all sentences\n");
                        do { //make sure the user entered a valid shift value
                            printf("\t\tEnter the shifing key: ");
                            scanf("%d", &shift_value);
                        } while (shift_value < 0 || shift_value > 26);
                        for (int i = 0; i <= last_adding_sentence_index; i++) { //decrypt all the sentences
                            decrypt_a_sentence (i, shift_value);
                        }
                        printf("\t\tAll sentences have been decrypted!\n");
                        getchar(); //wait for the user to press a key to continue
                        getchar();
                        break;
                    default: //if the user entered an invalid choice
                        printf("\t\t\tInvalid choice!\n");
                        getchar(); //wait for the user to press a key to continue
                        break;
                }
                break;
            case 5:
                cls(); //clear the screen
                printf("\t\t\tSave sentences to a file\n");
                save_sentences_file(last_adding_sentence_index);
                break;
            case 6:
                cls(); //clear the screen
                printf("\t\t\tLoad sentences from a file\n");
                load_sentence_file(&last_adding_sentence_index);
                break;
            case 7:
                cls(); //clear the screen
                quit_the_program();
                break;
            default: //if the user entered an invalid choice
                cls(); //clear the screen
                printf("\n\t\tInvalid choice.\n");
        }
    } while (main_menu_choice != 7);
}

void main_menu () { //display the main menu
    cls();
    printf("\t\t\t\tMain Menu:\n");
    printf("\t\t1. Add a new sentences\n");
    printf("\t\t2. Display all sentences\n");
    printf("\t\t3. Select a sentence\n");
    printf("\t\t4. Encrypt or decrypt all sentences\n");
    printf("\t\t5. Save sentences to a file\n");
    printf("\t\t6. Load sentences from a file\n");
    printf("\t\t7. Quit the program\n");
    printf("\n\t\tChoice: "); //ask the user to enter a choice
}

int add_new_sentences () { //add a new sentence to the sentences array
    int i, flag = 0;
    for (i = 0; i < 20; i++) { //give the user a chance to enter as sentences as he wants until he reaches the limit of 20 or he enters None
        printf("\n\t\tEnter sentence %d: ", i + 1);
        if (flag == 0) {
            getchar();
            flag = 1;
        }
        scanf("%[^\n]%*c", sentences[i]);
        if (strcmp(sentences[i], "None") == 0 || strcmp(sentences[i], "none") == 0 || strcmp(sentences[i], "NONE") == 0) { //if the user entered None break the loop
            return i-1;
        }
    }
    getchar();
    return i;
}

void display_all_sentences(int last_adding_sentence_index) { //display all the sentences
    int i;
    getchar();
    for (i = 0; i <= last_adding_sentence_index; i++) {
        printf("\t\t%s\n", sentences[i]);
    }
    getchar();
}

int select_a_sentence(int last_adding_sentence_index, int selected_sentence) { //select a sentence from the sentences array
    int i;
    for (i = 0; i <= last_adding_sentence_index; i++) {
        if (i == (selected_sentence - 1)) {
            return i;
        }
    }
    return -1;
}

void selecting_menu () { //display the selecting menu
    int flag = 0;
    if (flag = 0) {
        getchar();
        flag = 1;
    }
    cls();
    printf("\t\t\tSelecting Menu:\n");
    printf("\t\t1. Display the sentence\n");
    printf("\t\t2. Modify the sentence\n");
    printf("\t\t3. Encrypt the sentence\n");
    printf("\t\t4. Decrypt the sentence\n");
    printf("\t\t5. Go back to the main menu\n");
    printf("\n\t\tChoice: ");
}

void display_a_sentence (int selected_sentence) { //display a sentence
    getchar();
    printf("\t\t%s\n", sentences[selected_sentence]);
    getchar();
}

void modify_a_sentence (int selected_sentence) { //modify a sentence
    getchar();
    printf("\t\tEnter another sentence to modify this sentence: ");
    scanf("%[^\n]%*c", sentences[selected_sentence]);
    printf("\t\tThe sentence has been modified!\n");
    getchar();
}

void encrypt_a_sentence (int selected_sentence, int shift_value) { //encrypt a sentence
    int temp;
    for (int i = 0; i < strlen(sentences[selected_sentence]); i++) { //encrypt each character in the sentence
        temp = (int)sentences[selected_sentence][i];
        if (temp >= 65 && temp <= 90) {
            temp = temp + shift_value;
            if (temp > 90) {
                temp = temp - 26;
            }
        } else if (temp >= 97 && temp <= 122) { //if the character is a lowercase letter
            temp = temp + shift_value;
            if (temp > 122) {
                temp = temp - 26;
            }
        }
        sentences[selected_sentence][i] = (char)temp;
    }
}

void decrypt_a_sentence (int selected_sentence, int shift_value) { //decrypt a sentence
    int temp;
    for (int i = 0; i < strlen(sentences[selected_sentence]); i++) { //decrypt each character in the sentence
        temp = (int)sentences[selected_sentence][i];
        if (temp >= 65 && temp <= 90) {
            temp = temp - shift_value;
            if (temp < 65) {
                temp = temp + 26;
            }
        } else if (temp >= 97 && temp <= 122) { //if the character is a lowercase letter
            temp = temp - shift_value;
            if (temp < 97) {
                temp = temp + 26;
            }
        }
        sentences[selected_sentence][i] = (char)temp;
    }
}

void save_sentences_file (int last_adding_sentence_index) { //save the sentences to a file
    char temp_ans;
    saving = fopen("sentences.txt", "r");
    if (saving != NULL) { //if the file exists
        do { //if the file already exists, ask the user if he wants to overwrite it
            printf("\t\tThe file is already full. Do you want to overwrite it? (y/n): ");
            scanf("%c", &temp_ans);
            getchar();
        } while (temp_ans == 'y' || temp_ans == 'Y'); //if the user wants to overwrite the file, delete the file and create a new one
    }
    fclose(saving); //close the file
    saving = fopen("sentences.txt", "w");
    for (int i = 0; i <= last_adding_sentence_index; i++) { //write the sentences to the file
        fprintf(saving, "%s\n", sentences[i]);
    }
    fclose(saving);
    printf("\n\t\tThe file has been saved!\n"); //display a message that the file has been saved
    getchar(); //wait for the user to press a key to continue
}

void load_sentence_file (int *last_adding_sentence_index) { //load the sentences from a file
    int i =0;
    saving = fopen("sentences.txt", "r");
    if (saving != NULL) { //if the file exists
        while (!feof(saving)) { //read the file line by line 
            fgets(sentences[i], 100, saving);
            strtok(sentences[i], "\n");
            i++;
        }
        *last_adding_sentence_index = i;
    } else { //if the file doesn't exist
        printf("\t\tThe file is not found!\n");
        getchar();
    }
    getchar();
    printf("\t\tThe file has been loaded!\n"); //display a message that the file has been loaded
    getchar(); //wait for the user to press a key to continue
}

void quit_the_program () { //quit the program
    printf("\t\tThe program has been quit!\n");
    printf("\t\tThank you for using this program!\n");
    printf("\t\tGoodbye!\n");
    getchar(); //wait for the user to press a key to continue
}

void cls () { //clear the screen
    for (int i = 0; i < 100; i++) { //clear the screen by printing void 100 lines
        printf("\n");
    }
}