#include <stdio.h>
#include <string.h>

//1) CADASTRO DE EQUIPE

    struct Equipe{

    char nome_equipe [31];
    char sigla [4];
    char estado [3];

    };

int main()
{
    struct Equipe equipes [40]; //"Equipe" é o tipo e "equipes" é o nome da variável.
    int qtd_equipe = 0;

    char continuar = 'S';

    while(continuar == 'S' || continuar == 's')
    {
    char nome [31]; //é uma variável temporária para verificar antes se já existe esse nome.

    printf("Digite o nome da equipe: ");
    fgets(nome, 31, stdin);

    nome[strcspn(nome, "\n" )] = '\0';

    int pos = -1;

    for(int i = 0; i < qtd_equipe; i++) {
        if(strcmp(nome, equipes[i].nome_equipe) == 0){
             pos = i;
             break;
        }
    }
    if(pos != -1)
    {
        printf("Equipe ja cadastrada.\n");
    }
    else
    {
        strcpy(equipes[qtd_equipe].nome_equipe, nome);

        printf("Digite a sigla: ");
        scanf("%3s", equipes[qtd_equipe].sigla);

        printf("Digite o estado: ");
        scanf("%2s", equipes[qtd_equipe].estado);

        qtd_equipe++;
    }
     printf("Deseja cadastrar outra equipe? (S/N): ");
     scanf(" %c", &continuar);

     getchar(); // remove o Enter que ficou no teclado
    }

    return 0;

}
