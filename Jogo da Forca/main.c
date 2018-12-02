/*
   *    jjjjj██╗j██████╗jj██████╗jj██████╗jjjjj██████╗jj█████╗jjjjj███████╗j██████╗j██████╗jj██████╗j█████╗j
   *    jjjjj██║██╔═══██╗██╔════╝j██╔═══██╗jjjj██╔══██╗██╔══██╗jjjj██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔══██╗
   *    jjjjj██║██║jjj██║██║jj███╗██║jjj██║jjjj██║jj██║███████║jjjj█████╗jj██║jjj██║██████╔╝██║jjjjj███████║
   *    ██jjj██║██║jjj██║██║jjj██║██║jjj██║jjjj██║jj██║██╔══██║jjjj██╔══╝jj██║jjj██║██╔══██╗██║jjjjj██╔══██║
   *    ╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝jjjj██████╔╝██║jj██║jjjj██║jjjjj╚██████╔╝██║jj██║╚██████╗██║jj██║
   *    j╚════╝jj╚═════╝jj╚═════╝jj╚═════╝jjjjj╚═════╝j╚═╝jj╚═╝jjjj╚═╝jjjjjj╚═════╝j╚═╝jj╚═╝j╚═════╝╚═╝jj╚═╝
   *    jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include <conio.h>  // Necessário para utilização da função 'getch'

#include <string.h>  // Necessário para separar os caracteres em índices.

#include <time.h>  // Necessário para utilizar a função time().

#define size 20  // Número de quantas palavras serão buscadas.

#define s_char 20 // Número de caracteres da palavra.

#define s_char2 55 // Número de caracteres da dica.

char word[s_char], void_word[s_char]; //Variável que irá conter a palavra a ser descoberta no jogo

int fails = 0; //Variável que irá conter o número de falhas ocorridas durante o jogo

int n_char = 0; //Variável que irá conter o numero de caracteres da string

char tip[s_char2]; //Variável que irá conter a dica

int tip_cont = 0; //Variavel que será incrementada se houver uma chamada para dica

//Função que irá buscar a dica em um banco de dados de acordo com a palavra escolhida

int helper(int k)
{

    int i,j;

    FILE *file;
    file = fopen("bd_help.txt","r");

    j = (k / 5);

    for(i=0; i<=j; i++)
    {
        fgets(tip,s_char2,file);
    }

    fclose(file);
    return 0;
}

//Função que irá construir a forca

int engineer()
{

    //Para substituir comandos "if-else" na forma geral, podemos utilizar o operador "?". Ou seja, ele que realiza o teste lógico.

    printf("  __________       \n");
    printf(" |/         |      \n");
    printf(" |          %c     \n", (fails>=1?'O':' '));
    printf(" |         %c%c%c  \n", (fails>=3?'\\':' '), (fails>=2?'|':' '), (fails>=4?'/': ' '));
    printf(" |          %c     \n", (fails>=2?'|':' '));
    printf(" |         %c %c   \n", (fails>=5?'/':' '), (fails>=6?'\\':' '));
    printf(" |              \n");
    printf(" |              \n");
    printf(" |              \n");
    printf("_|____          \n");
    printf("\n\n");

    if(tip_cont == 0)
    {
       printf("Aperte ESPACO para ver a dica da palavra");

    }else if(tip_cont == 1){
        printf("%s",tip);
    }

    printf("\n\n");

    return 0;
}

//Função que irá montar a linha tracejada com o número de caracteres existentes

int char_len()
{
    int i;

    for(i = 0; i < n_char; i++)
    {
        if(void_word[i])
        {
            printf("%c ",void_word[i]); //Se houver alguma letra irá exibir na tela
        }
        else
        {
            printf("_ "); //Se não houver letra irá exibir "_ " na tela
        }
    }
    printf("\n\n");

    return 0;
}

//Função que verifica se o jogo já foi concluido

int finish()
{
    if(strcmp(void_word,word) == 0)
    {
        return 1;
    }

    return 0;
}

//Função que verifica se há a letra digitada

int checker(char letter)
{
    int i, falso = 0;

    for(i = 0; i < strlen(word); i++)
    {
        if(letter == word[i])
        {
            void_word[i] = word[i]; //Se houver a letra digitada, a string vazia receberá a letra na posição referente à variável com o resultado

            falso = 1;
        }
    }
    if(falso == 0)
    {
        fails++; //Se não houver a letra digitada na variável com o resultado, entao irá aumentar +1 no número de falhas
    }
    return 0;
}

//Função que irá buscar a palavra no banco de dados

int get_word()
{
    struct palavra
    {
        char words[s_char];
    };

    struct palavra array[size];

    int i=0,j;

    FILE *file;
    file = fopen("bd_words.txt","r");

    if(file == NULL)
    {
        printf("Não foi possível achar o arquivo.");
        return 0;
    }
    else
    {
        srand(time(NULL)); // Pega o horário do sistema para que não haja repetições toda vez que inicializar o game.

        while(((fgets(array[i].words,s_char,file)) != NULL) && (i != size))
        {
            i++;
        }
        j = rand() % i;

        strcpy(word, array[j].words); //Copia para a variável global

        helper(j); //Chama a função da dica, passando por parametro o número de indice da palavra escolhida

        n_char = (strlen(word)) - 1; //Atribuindo o número de caracteres da string selecionada

        word[n_char] = "\0"; //Adicionado o '\0' para indicar o fim da string

        void_word[n_char] = "\0"; //Adicionado o '\0' para indicar o fim da string

        fclose(file);

        return 0;
    }
}

//Função criada apenas para retornar o valor do resultado do jogo

int wonornot()
{
    if(fails > 6)
    {
        return 0; //Se perdeu, retorna 0
    }
    else
    {
        return 1; //Se ganhou retorna 1
    }
}

//Função onde será executado o jogo

int in_game()
{
    char get_char;

    do
    {
        system("cls");

        engineer();
        char_len();

        printf("\n\n");
        printf("Qual letra ? \n\n");

        get_char = getch();

        if( ( (tip_cont == 0) && (get_char == 32) ) || (tip_cont == 1))
        {
            tip_cont++;
        }
        else
        {
            checker(get_char);
        }
    }
    while( (fails <= 6) && ((finish()) != 1) ); //Irá permanecer no jogo se o n° de falhas for menor do que o delimitado e se não tiver acertado a palavra

    return wonornot();
}

//Função que irá exibir o menu principal

int main_menu()
{
    char get_key;

    int order = 0;

    get_word(); //Chama a função que escolhe a palavra do banco de dados

    do
    {
        system("cls"); // Função limpa tela

        printf("                              |-----------------|\n");
        printf("                              |  Jogo de Forca  |\n");
        printf("                              |-----------------|\n\n");
        printf("\n\n\n\n\n\n\n");
        printf("                                  ___________\n");
        printf("                                 |           |\n");
        printf("                                 |  Iniciar  |    %c\n",order == 0?'<':' '); //Irá verificar onde está o ponteiro, para a escolha da opção
        printf("                                 |___________|\n");
        printf("                                  ___________\n");
        printf("                                 |           |\n");
        printf("                                 |   Sair    |    %c\n",order == 1?'<':' '); //Irá verificar onde está o ponteiro, para a escolha da opção
        printf("                                 |___________|\n");
        printf("\n\n");
        printf("                          Aperte Enter para selecionar.\n");

        get_key = getch();

        /*
            72 = ↑ (seta pra cima)

            80 = ↓ (seta para baixo)
        */

        if(get_key == 72)
        {
            order = 0; //Se for apertado a ↑ (seta pra cima), a variável recebe '0'
        }
        else if(get_key == 80)
        {
            order = 1; //Se for apertado a ↓ (seta para baixo), a variável recebe '0'
        }
    }
    while( get_key != 13); //Ficará no menu principal até que a tecla 'ENTER' seja pressionada

    return order;
}

//Função que irá apagar o conteúdo da variável e zerar o n° de falhas

void restart(void)
{
    int i;
    char void_string[s_char] = "";

    for(i = 0 ; i < s_char ; i++){
        void_word[i] = void_string[i];
    }

    fails = 0;

    tip_cont = 0;
}

int main(void)
{
    setlocale(LC_ALL,"Portuguese");

    restart:

    if(main_menu() == 0)
    {
        if(in_game() == 1)
        {
            system("cls");

            printf("\nParabens, voce ganhou!\n\n");

            printf("       ___________      \n");
            printf("      '._==_==_=_.'     \n");
            printf("      .-\\:      /-.    \n");
            printf("     | (|:.     |) |    \n");
            printf("      '-|:.     |-'     \n");
            printf("        \\::.   /      \n");
            printf("         '::. .'        \n");
            printf("           ) (          \n");
            printf("         _.' '._        \n");
            printf("        '-------'       \n\n");
        }
        else
        {
            system("cls");

            printf("\nGame Over, voce foi enforcado!\n\n");

            printf("    _______________         \n");
            printf("   /               \\       \n");
            printf("  /                 \\      \n");
            printf(" /                   \\     \n");
            printf(" |   XXXX     XXXX   |      \n");
            printf(" |   XXXX     XXXX   |      \n");
            printf(" |   XXX       XXX   |      \n");
            printf(" |                   |      \n");
            printf(" \\__      XXX      __/     \n");
            printf("   |\\     XXX     /|       \n");
            printf("   | |           | |        \n");
            printf("   | I I I I I I I |        \n");
            printf("   |  I I I I I I  |        \n");
            printf("   \\_             _/       \n");
            printf("     \\_         _/         \n");
            printf("       \\_______/           \n");
        }
        system("pause");
        restart();
        goto restart;
    }
    return 0;
}
