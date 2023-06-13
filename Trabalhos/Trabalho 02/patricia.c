#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista.c"
#include "locale.h"


#define true 1 // verdadeiro
#define false 0 // falso

// ************************* VARIAVEIS GLOBAIS ************************* //
int linha = 1; // linha vai ser incrementada assim que estivermos no final da linha lida

// ************************* ESTRUTURA PATRÍCIA  ************************* //

typedef struct no_patricia PNO;
struct no_patricia{

    int pos_caracter;  // posicao do caracter a ser comparado
    TLista *linhas;    // uma lista que guarda em que linhas encontra-se as palavras
    char palavra[20];  // palavra que o nó/raiz irá armazenar  
    PNO *filho_esq;    
    PNO *filho_dir;

};

// ************************* CRIAR ESTRUTURA PATRÍCIA  ************************* //
/*
a função criarRaiz irá alocar um espaço na memória para uma nova  estrutura struct no_patricia
*/

PNO *criarRaiz(int pos_char, char palavra[20], int tamanho){
    
    PNO *nova_raiz = malloc(sizeof(PNO));
    nova_raiz->pos_caracter = pos_char;
    nova_raiz->linhas = criarLista();
    strncpy(nova_raiz->palavra, palavra,tamanho);
    

    nova_raiz->filho_esq = NULL;
    nova_raiz->filho_dir = NULL;

    return nova_raiz;
}
// ************************* FUNÇÕES AUXILIARES PARA ARVORES PATRICIAS  ************************* //

// a função irá retornar tamanho da menor string dadas duas strings (palavras);
int tamanhoMenorString(char palavra1[20], char palavra2[20]){
    int menor = strlen(palavra1);

    if(strlen(palavra1) > strlen(palavra2)){
        menor = strlen(palavra2);
    }
    return menor;
}

/* 
a função irá retornar o índice do último caracter em comum de duas strings

retorna -1 caso uma string for uma sub-palavra da outra string
retorna i = 0 caso não tenha elementos comum
se for difente disso é porque existe elementos comuns

*/
int ultimoCharComum(char palavra1[20], char palavra2[20]){

    int menor = tamanhoMenorString(palavra1,palavra2); // saber até onde i (contador) ser icrementado 
    int i = 0; // contador de cacteres iguais
    while(palavra1[i] == palavra2[i] && (i < menor)){
        i++;
    }
    if( i == menor){ // uma das palavras é sub-palavra da outra
        return -1;
    }
    i-= 1;
    if(i < 0){ // não tem nenhum char em comum
        i = 0;
    }
    return i;
}
// a função irá retornar o índice do primeiro caracter diferente entre duas strings dadas
int primeiroCharDistinto(char palavra1[20], char palavra2[20]){

    int menor = tamanhoMenorString(palavra1,palavra2); // menor foi criado para saber qual vai ser o limite do icremento do contador;
    int contador = 0; // contadador de caracteres iguais

    // o contador irá ser icrementado enquanto os caracteres das strings forem iguais e ele ser menor que o tamanho da menor string
    while(palavra1[contador] == palavra2[contador] && contador < menor){ 
        contador ++;
    }
    return contador;
}
// a função irá retornar a menor string entre duas strings  dado a posicao da diferenca de caracteres 
char *menorStringChar(char palavra1[20], char palavra2[20]){
    int aux = primeiroCharDistinto(palavra1,palavra2);
    return (palavra1[aux] < palavra2[aux])? palavra1 : palavra2;
       
}
// a função irá retornar a maior string entre duas strings dado a posicao da diferenca de caracteres 
char *maiorStringChar(char palavra1[20], char palavra2[20]){
    int aux = primeiroCharDistinto(palavra1,palavra2);
    return (palavra1[aux]>palavra2[aux])? palavra1 : palavra2;
}

// a função retornará o nó com a menor string
PNO *filhoMenor(PNO *filho_esq, PNO *filho_dir){
    char* aux = menorStringChar(filho_esq->palavra,filho_dir->palavra);
    if(strcmp(filho_esq->palavra,aux)==0){
        return filho_esq;
    }else{
        return filho_dir;
    }
}
// a função retornará o nó com maior string
PNO *filhoMaior(PNO *filho_esq, PNO *filho_dir){
    char* aux = maiorStringChar(filho_dir->palavra,filho_esq->palavra);
    return strcmp(filho_esq->palavra,aux) == 0 ? filho_esq : filho_dir;
}

// a função verifica se o nó/raiz passado é uma folha
int folha(PNO *raiz){
    if( (raiz->filho_dir==NULL) &&( raiz->filho_esq==NULL)){ // caso  o nó não tenha filhos, então ele é uma folha
        return true;
    }else{
        return false;
    }
}


// função que irá imprimir a árvore criada
void imprimirArvore(PNO *raiz){
    setlocale(LC_ALL, "Portuguese_Brazil");
    if(raiz != NULL){
        imprimirArvore(raiz->filho_esq);
        if(strlen(raiz->palavra)>=3 && listaVazia(raiz->linhas) == false){
            printf("%s ",raiz->palavra);
            imprimirLista(raiz->linhas);
            printf("\n");
        }
       imprimirArvore(raiz->filho_dir);  
    }
     
}

// ************************* FUNÇÃO DE INSERÇÃO DE ARVORES PATRICIAS  ************************* //
/* 
a função ladoInsercao vai identificar em qual filho deve ser feito a inserção
return 1 - filho esquerdo
return 2 - filho direito 
*/
int ladoInsercao(PNO *raiz, char palavra_nova[20]){

    int aux = primeiroCharDistinto(raiz->palavra,palavra_nova);
    int menor = tamanhoMenorString(raiz->palavra,palavra_nova);

    if(aux>menor-1){  // caso de uma string ser sub-string da outra 
        int menorPalavra1 = primeiroCharDistinto(palavra_nova,raiz->filho_esq->palavra);
        int menorPalavra2 = primeiroCharDistinto(palavra_nova,raiz->filho_dir->palavra);
        if(menorPalavra2>menorPalavra1){ // a palavra guardada no filho direto tem mais caracteres em comum com a nova palavra a ser inserida
            return 2;
        }else if (menorPalavra2 == menorPalavra1){ // caso tenha a mesma quantidade de caracteres em comum com as palavras do os dois filhos do nó
            // irá verificar onde deve ser inserido a partir da posição onde ocorre a diferença de de caracter
            if(raiz->filho_dir->palavra[menorPalavra2] > palavra_nova[menorPalavra2]){ 
                return 1;
            }else{
                return 2;
            }
        }else{ // a palavra guardada no filho esq tem mais caracteres em comum com a nova palavra a ser inserida
            return 1;
        }
    } // caso não seja uma sub-string
    if(palavra_nova[aux] > raiz->palavra[aux]){
        return 2;
    }else{
        return 1;
    }
}
// a função irá retornar 1 caso a palavra já esteja na árvore e retornará zero caso não pertença a árvore
int buscaPalavra(PNO *raiz, char palavra[20], int flag){

    if(strcmp(palavra,raiz->palavra) == 0){ // casso a palavra seja igual a palavra armazenada no nó/raiz
        flag = true;
    }else{
        if( folha(raiz) == false){ // caso não seja folha, ele irá ficar percorrendo pelo filhos que estão a esquerda
            flag = buscaPalavra(raiz->filho_esq,palavra,flag);
            if(flag == 0){ // não foi nada encontrado nos filhos da esquerda, agora irá percorrer pelos filhos a direita
                flag = buscaPalavra(raiz->filho_dir,palavra,flag);
            }
        }else{ // caso não seja encontrado nada 
            flag = 0;
        }
    }
    return flag;
}
// a função irá atualizar a lista de linhas que contêm a string 
PNO *atualizarLinha(PNO *raiz, char palavra[20]){
    if(strcmp(palavra,raiz->palavra) == 0){ // se raiz/nó tenha tenha a string, irá ser atualizado a lista de linhas
        TELE *carga_nova = criarElemento(linha);
        inserirLista(raiz->linhas,carga_nova);
        return raiz;
    }else{
        if(folha(raiz) == false){ // irá percorre os filhos caso a raiz/nó não forem folhas;
           raiz->filho_esq = atualizarLinha(raiz->filho_esq,palavra);
           raiz->filho_dir = atualizarLinha(raiz->filho_dir,palavra);
        }else{ // caso a raiz/nó não for folha, não há o que se atualizar, uma vez que eles não armazenam palavras 
            return raiz;
        }
    }
    return raiz;
}

// função que insere as palavras na árvore
PNO *inserirArvore(PNO *raiz_pai, PNO *raiz, char palavra_nova[20]){
    if(palavra_nova[0]=='*'){ // caso seja um asterisco, é para pular a linha  
        linha++;      
        return raiz;
    }
    // caso a raiz seja nula;
    if(raiz == NULL){
       
        raiz = criarRaiz(0,palavra_nova,strlen(palavra_nova));
        TELE *carga = criarElemento(linha);
        inserirLista(raiz->linhas, carga);
    // raiz != NULL  
    }else{
        // primeiro será verificado se a palavra já não está na árvore
        int flag = buscaPalavra(raiz,palavra_nova,flag);
        if(flag == 1){ // se estiver na árvore, será atualizado lista de linhas com essa palavra associada
            raiz = atualizarLinha(raiz, palavra_nova);
            return raiz;
        // caso ela não esteja
        }else{
                if(folha(raiz) == true){ // caso se o nó/raiz for uma folha
                
                // sera obtido a posicao do ultimo caracter em comum com a palavra nova e com a palavra da raiz
                int pos_caracter;
                pos_caracter = ultimoCharComum(raiz->palavra,palavra_nova);
                
                char caracterString[20]={""};
                strncpy(caracterString, palavra_nova, pos_caracter + 1);      
                
                if(raiz_pai != NULL){
                    // Se sub-string criada for igual a sub-string do pai, vai ser obtida uma nova sub-string
                    if(strcmp(caracterString,raiz_pai->palavra) == 0){
                        pos_caracter = primeiroCharDistinto(raiz->palavra,palavra_nova);
                        strncpy(caracterString,maiorStringChar(raiz->palavra,palavra_nova), pos_caracter + 1);
                    }

                }
                PNO *raiz_antiga = raiz;
                int nova_pos_char = 0;

                if(raiz_pai != NULL){     
                    nova_pos_char = primeiroCharDistinto(raiz_pai->palavra,palavra_nova);
                }
                // criando uma nova raiz com uma sub-string em comum
                PNO *raiz_nova = criarRaiz(nova_pos_char,caracterString,1);

                // criando o novo nó/filho com a nova palavra que vai ser inserida
                PNO *novo_filho = criarRaiz(primeiroCharDistinto(raiz_nova->palavra,palavra_nova),palavra_nova,strlen(palavra_nova));
                TELE *carga_nova = criarElemento(linha);
                inserirLista(novo_filho->linhas,carga_nova);
                // atualizando pos_caracter da raiz antiga
                raiz_antiga->pos_caracter = primeiroCharDistinto(raiz_nova->palavra, raiz_antiga->palavra);
                // definindo os filhos
                raiz_nova->filho_esq = filhoMenor(raiz_antiga,novo_filho);
                raiz_nova->filho_dir = filhoMaior(novo_filho,raiz_antiga);
                
                return raiz_nova;
            }else{ // caso o nó/raiz não seja uma folha, será verificado onde deve ocorrer a inserção
                    if(ladoInsercao(raiz,palavra_nova) == 1){
                    raiz->filho_esq = inserirArvore(raiz,raiz->filho_esq, palavra_nova);
                }else if(ladoInsercao(raiz, palavra_nova) == 2){
                    raiz->filho_dir = inserirArvore(raiz, raiz->filho_dir, palavra_nova);
                }

            }
        
        }  

    }
    return raiz;
}

// ************************* FUNÇÕES AUXILIARES PARA TRATAMENTO DO TRABALHO  ************************* //

// a função irá retorna a quantidade de characteres que são pontuações
int numeroPontuacao(char palavra[20]){
    int tamanho_palavra = strlen(palavra);
    int contador = 0;
    for(int i = 0; i<tamanho_palavra; i++){
        if (palavra[i] == '.' || palavra[i] == ',' || palavra[i] == '!' || palavra[i] == '?' || palavra[i] == '"'){
            contador++;
        }
    }
    return contador;
}

// função irá retorna 1 caso o caracter for uma pontuação e zero caso não seja
int charPontuacao(char caracter){
    if(caracter == '.' || caracter == ',' || caracter == '!' || caracter =='?' || caracter == '"'){
        return true;
    }
    return false;
}

// a função irá retirar as pontuações da string
char *tirarPontuacao(char palavra[20]){
    int tamanho_palavra = strlen(palavra);
    int i = 0;
    //int num = 1;
    int numero_pontuacao = numeroPontuacao(palavra);
    if(charPontuacao(palavra[0]) == true){  // verifica se o inicio tem aspas
        for(int j = 0;  j < tamanho_palavra-1;j++){
            palavra[j] = palavra[j+1];
        }
        palavra[tamanho_palavra-1] = '\0';
        i++;
        while (i < numero_pontuacao) // irá fazer as remoções das pontuações que são armazenadas no final da string caso tenha
        {
            if(charPontuacao(palavra[strlen(palavra)-i])==true){
                palavra[strlen(palavra)-i] = '\0';
            }
            i++;
        }
        
    }else{ // caso não tenha pontuação no inicio, irá remover caso tenha no final 
        while(i < numero_pontuacao){
            if(charPontuacao(palavra[strlen(palavra)-i-1]) == true){
                palavra[strlen(palavra)-i-1] = '\0';
            }
            i++;
        }

    }
    return palavra;
}

int main(){
    setlocale(LC_ALL, "portuguese_Brazil");
    
    FILE *arquivo;
    arquivo = fopen("teste.txt","r");

    char palavra[20]; // variável criada para receber as strings do aquivo de texto;
    PNO *raiz=NULL; 
    
    if(arquivo == NULL){
        printf("Arquivo nao encontrado\n");
    }else{ 
        while(!feof(arquivo)){

            fscanf(arquivo,"%s",palavra); // a string palavra recebendo a string do texto
            strlwr(palavra); // deixa em letra minúscula 
            strcpy(palavra, tirarPontuacao(palavra)); // tirando as pontuações da palavra 
            // fará a inserção caso a palavra seja maior ou igual a 3  ou ela seja apenas * simbolizando a leitura da outra linha
            if(strlen(palavra)>=3 || strcmp(palavra,"*") == 0){ 
                raiz=inserirArvore(NULL,raiz,palavra);                          
            }
        }
    }

    imprimirArvore(raiz);
    
    fclose(arquivo);
    
}
   