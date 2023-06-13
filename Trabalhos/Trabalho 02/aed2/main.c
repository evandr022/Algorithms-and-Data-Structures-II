/*Evandro Salvador Marinho da Silva - 22052988
Video: https://youtu.be/-KwQFhq1hbQ
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "locale.h"
#include "assert.h"
#include "list.h"

#define WORD_NOT_FOUND 0
#define true 1 
#define false 0

typedef struct patricia_node Node;
struct patricia_node{
    int character_pos;
    char word[20];   
    ChargeList *line_numbers;   
    Node *left ;    
    Node *right;
};

Node *createNode(int char_pos, char word[20], int length){   
    Node *new_node = malloc(sizeof(Node));
    new_node->character_pos = char_pos;
    new_node->line_numbers = createList();
    strncpy(new_node->word, word,length);
    
    new_node->left  = NULL;
    new_node->right = NULL;

    return new_node;
}

int smallestStringSize(char word1[20], char word2[20]){
    int smallest = strlen(word1);

    if(smallest > strlen(word2)){
        smallest = strlen(word2);
    }
    return smallest;
}

int lastCommonChar(char word1[20], char word2[20]){

    int smallest = smallestStringSize(word1,word2);  
    int index = 0;
    while(word1[index] == word2[index] && (index < smallest)){
        index++;
    }
    if( index == smallest){ 
        return -1;
    }
    index-= 1;
    if(index < 0){ 
        index = 0;
    }
    return index;
}

int firstDifferentChar(char word1[20], char word2[20]){

    int smallest = smallestStringSize(word1,word2); 
    int counter  = 0; 

    while(word1[counter] == word2[counter] && counter  < smallest){ 
        counter  ++;
    }
    assert(counter <= smallest);
    return counter ;
}

const char *smallerString(const char word1[20], const char word2[20]){
    if (word1 == NULL || word2 == NULL) {
        return NULL;
    }
    size_t diffIndex = firstDifferentChar(word1,word2);
    return (word1[diffIndex] < word2[diffIndex])? word1 : word2;
       
}

const char *largerString(const char word1[20], const char word2[20]){
    if (word1 == NULL || word2 == NULL) {
        return NULL;
    }
    size_t diffIndex = firstDifferentChar(word1,word2);
    return (word1[diffIndex] > word2[diffIndex])? word1 : word2;
}

Node *smallerChild(Node *left, Node *right){
    if (left->word == NULL || right->word == NULL) {
        return NULL;
    }
    int result = strncmp(left->word, right->word, 20);
    if (result < 0) {
        return left;
    } else {
        return right;
    }
}

Node *largerChild(Node *left, Node *right){
    if (left->word == NULL || right->word == NULL) {
        return NULL;
    }
    int result = strncmp(left->word, right->word, 20);
    if (result > 0) {
        return left;
    } else {
        return right;
    }
}

int isLeaf(Node *root){
    if (root == NULL) {
        return false;
    }
    if (root->left == NULL && root->right == NULL) {
        return true;
    }
    return false;
}

void printTree(Node *root) {
    static int is_locale_set = 0;
    if (!is_locale_set) {
        setlocale(LC_ALL, "Portuguese_Brazil");
        is_locale_set = 1;
    }
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        printTree(root->left);
    }
    if (root->word != NULL && strlen(root->word) >= 3 && !isEmptyList(root->line_numbers)) {
        printf("%s ", root->word);
        printList(root->line_numbers);
        printf("\n");
    }
    if (root->right != NULL) {
        printTree(root->right);
    }
}

int determineInsertionSide(Node *root, char new_word[20]){

    int first_diff = firstDifferentChar(root->word,new_word);
    int smallest_size = smallestStringSize(root->word,new_word);

    if(first_diff > smallest_size -1){ 
        int smallest_word_1 = firstDifferentChar(new_word,root->left ->word);
        int smallest_word_2 = firstDifferentChar(new_word,root->right->word);
        if(smallest_word_2>smallest_word_1 ){ 
            return 2;
        }else if (smallest_word_2 == smallest_word_1 ){ 
            if(root->right->word[smallest_word_2] > new_word[smallest_word_2]){ 
                return 1;
            }else{
                return 2;
            }
        }else{ 
            return 1;
        }
    }
    if(new_word[first_diff] > root->word[first_diff]){
        return 2;
    }else{
        return 1;
    }
}

int searchWord(Node *root, char word[20]) {
    while (root != NULL) {
        int comparison = strcmp(word, root->word);
        if (comparison == 0) {
            return 1;
        } else if (comparison < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return WORD_NOT_FOUND;
}

int currentLine = 1; 

Node *updateLine(Node *root, char word[20]){
    if(strcmp(word,root->word) == 0){ 
        ChargeNode *new_load = createElement(currentLine);
        insertList(root->line_numbers,new_load);
        return root;
    }else{
        if(isLeaf(root) == false){
           root->left  = updateLine(root->left ,word);
           root->right = updateLine(root->right,word);
        }else{ 
            return root;
        }
    }
    return root;
}

Node *insertTree(Node *node, Node *root, char new_word[20]){
    if(new_word[0]=='*'){ 
        currentLine++;      
        return root;
    }

    if(root == NULL){
        root = createNode(0,new_word,strlen(new_word));
        ChargeNode *new_load = createElement(currentLine);
        insertList(root->line_numbers, new_load);
    }else{
        int flag = searchWord(root,new_word);
        if(flag == 1){ 
            root = updateLine(root, new_word);
            return root;
        }else{
                if(isLeaf(root) == true){ 
                
                int char_pos;
                char_pos = lastCommonChar(root->word,new_word);
                
                char caracterString[20]={""};
                strncpy(caracterString, new_word, char_pos + 1);      
                
                if(node != NULL){
                    if(strcmp(caracterString,node->word) == 0){
                        char_pos = firstDifferentChar(root->word,new_word);
                        strncpy(caracterString,largerString(root->word,new_word), char_pos + 1);
                    }

                }
                Node *oldRoot = root;
                int newCharPos = 0;

                if(node != NULL){     
                    newCharPos = firstDifferentChar(node->word,new_word);
                }

                Node *newRoot = createNode(newCharPos,caracterString,1);
                Node *newChild = createNode(firstDifferentChar(newRoot->word,new_word),new_word,strlen(new_word));
                ChargeNode *new_load = createElement(currentLine);

                insertList(newChild->line_numbers,new_load);

                oldRoot->character_pos = firstDifferentChar(newRoot->word, oldRoot->word);
                newRoot->left  = smallerChild(oldRoot,newChild);
                newRoot->right = largerChild(newChild,oldRoot);
                
                return newRoot;
            }else{ 
                    if(determineInsertionSide(root,new_word) == 1){
                    root->left  = insertTree(root,root->left , new_word);
                }else if(determineInsertionSide(root, new_word) == 2){
                    root->right = insertTree(root, root->right, new_word);
                }

            }
        
        }  

    }
    return root;
}

int countPunctuation(char word[20]){
    int wordLength = strlen(word);
    int counter  = 0;
    for(int index = 0; index<wordLength; index++){
        if (word[index] == '.' || word[index] == ',' || word[index] == '!' || word[index] == '?' || word[index] == '"'){
            counter ++;
        }
    }
    return counter ;
}

int isPunctuation(char caracter){
    if(caracter == '.' || caracter == ',' || caracter == '!' || caracter =='?' || caracter == '"'){
        return true;
    }
    return false;
}

char *removePunctuation(char word[20]){
    int word_length = strlen(word);
    int index = 0;
    int num_punctuation  = countPunctuation(word);

    if(isPunctuation(word[0]) == true){  
        for(int j = 0;  j < word_length-1;j++){
            word[j] = word[j+1];
        }
        word[word_length-1] = '\0';
        index++;
        while (index < num_punctuation ) {
            if(isPunctuation(word[strlen(word)-index])==true){
                word[strlen(word)-index] = '\0';
            }
            index++;
        }  
    }else{ 
        while(index < num_punctuation ){
            if(isPunctuation(word[strlen(word)-index-1]) == true){
                word[strlen(word)-index-1] = '\0';
            }
            index++;
        }
    }
    return word;
}

int add_asterisk(const char *file_path) {
    FILE *fp;
    fp = fopen(file_path, "r+");
    if (fp == NULL) {
        return 1;
    }

    int c, prev_c = 0;
    while ((c = fgetc(fp)) != EOF) {
        prev_c = c;
    }

    if (prev_c != '\n') {
        fputc('\n', fp);
    }

    fseek(fp, -1, SEEK_END);
    fputc('*', fp);

    fclose(fp);
    return 0;
}


int main(int argc, char *argv[]){
    setlocale(LC_ALL, "portuguese_Brazil");
    
    if (argc < 2){
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *fileName = argv[1];
    printf("Lendo arquivo de texto: %s\n", fileName);

    FILE *file;
    file = fopen(fileName,"r");

    char word[20];
    Node *root=NULL; 
    
    if(file == NULL){
        printf("Error opening file\n");
        return 1;
    }else{ 
        while(!feof(file)){

            fscanf(file,"%s",word); 
            strlwr(word);  
            strcpy(word, removePunctuation(word)); 
            
            if(strlen(word)>=3 || strcmp(word,"*") == 0){ 
                root=insertTree(NULL,root,word);   
            }
        }
    }
    printTree(root);
    
    fclose(file);
}  