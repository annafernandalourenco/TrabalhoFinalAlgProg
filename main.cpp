#include <stdio.h>
#include <string.h>

//1) CADASTRO DE EQUIPE

    // Essa é uma ficha que guarda cada informação de cada equipe

    struct Equipe{

    char nome_equipe [31];
    char sigla [4];
    char estado [3];

    int jogos;  //Quantidade de partidas disputadas
    int vitorias;  //Quantidade de vitórias
    int empates;  //Quantidade de empates
    int derrotas;  //Quantidade de derrotas
    int gols_pro;  //Quantidade de gols marcados
    int gols_contra;  //Quantidade de gols sofridos
    int pontos;  //Pontos na tabela

    };


//2) Função para validar UF

int estadoValido(char uf[])
{
    char estados[27][3] = {  // É uma matriz que indica que possui 27 estados e cada um deles com 2 letras
        "AC","AL","AP","AM","BA","CE",
        "DF","ES","GO","MA","MT","MS",
        "MG","PA","PB","PR","PE","PI",
        "RJ","RN","RS","RO","RR","SC",
        "SP","SE","TO"
    };

    for(int i = 0; i < 27; i++)  // O laço percorre toda matriz comparando a UF digitada com a UF da posição i
    {
        if(strcmp(uf, estados[i]) == 0)  // strcmp compara se uf  =  estado
        {
            return 1;  //VÁLIDO
        }
    }

    return 0;  //INVÁLIDO
}


// 3) Função que procura equipes de um determinado estado

    //Os parâmetros são:
    //      equipes[] - equipes cadastradas
    //      qtd - quantidade cadastrada


void buscarPorEstado(struct Equipe equipes[], int qtd)
{
    char uf[3]; //variável para guardar a UF que o usuário deseja pesquisar

    printf("Digite a UF: ");
    scanf("%2s", uf);

    // Vetor para guardar as posições das equipes encontradas do estado
    int encontrados[40];
    int qtdEncontrados = 0;  //Contador das equipes encontradas

    // Percorre todas as equipes da UF
    for(int i = 0; i < qtd; i++)
    {
        if(strcmp(uf, equipes[i].estado) == 0) //Compara
                                            //equipes[i] é o vetor e .estado é para acessar o campo estado da struct
                                         // == 0 se as strings forem iguais, !=0 se as strings forem diferentes
        {
            encontrados[qtdEncontrados] = i;  //Guarda a posição encontrada
            qtdEncontrados++;  //Incrementa o contador
        }
    }
        if(qtdEncontrados == 0) // Verifica se encontrou alguma equipe
            {
                printf("Nenhuma equipe encontrada para essa UF.\n");
                return;
            }

    // Ordenação por nome (Bubble Sort)
    for(int i = 0; i < qtdEncontrados - 1; i++)  //Primeiro laço da ordenação que controla quantas passadas serão feitas
    {
        for(int j = i + 1; j < qtdEncontrados; j++)  // Segundo laço que compara uma equipe com todas as seguintes.
        {
            if(strcmp(     //Compara os nomes
                equipes[encontrados[i]].nome_equipe,
                equipes[encontrados[j]].nome_equipe
                )  > 0)       //O primeiro nome vem depois do segundo em ordem alfabética
                                // Se o primeiro nome vier depois do segundo em ordem alfabética,
                                // strcmp retorna um valor positivo e as posições são trocadas.
            {
                int aux = encontrados[i];  //Troca das posições. Guarda temporariamente um valor
                encontrados[i] = encontrados[j];
                encontrados[j] = aux;
            }
        }
    }

    printf("\nEquipes encontradas:\n");  //Imprime o resultador

    for(int i = 0; i < qtdEncontrados; i++)  //Percorre todas as equipes encontradas.
    {
        printf("%s - %s\n",
               equipes[encontrados[i]].nome_equipe,
               equipes[encontrados[i]].sigla);
    }
}


int main()
{
    struct Equipe equipes [40]; //"Equipe" é o tipo, e "equipes" é o nome da variável. ARMAZENA AS EQUIPES CADASTRADAS
    int qtd_equipe = 0;

    char continuar = 'S';

    while(continuar == 'S' || continuar == 's')
    {

        //LEITURA DO NOME DA EQUIPE
        char nome [31]; //é uma variável temporária para verificar antes se já existe esse nome.

        printf("Digite o nome da equipe: ");
        fgets(nome, 31, stdin);

        nome[strcspn(nome, "\n" )] = '\0';


        int pos = -1;  // BUSCA PELO NOME PARA VERIFICAR SE A EQUIPE JÁ ESTÁ CADASTRADA


        for(int i = 0; i < qtd_equipe; i++) {
            if(strcmp(nome, equipes[i].nome_equipe) == 0){
                pos = i;
                break;
            }
        }

        if(pos != -1)  // ATUALIZAÇÃO DOS DADOS DE UMA EQUIPE JÁ CADASTRADA
        {
            char resposta;

            printf("Equipe ja cadastrada.\n");
            printf("Deseja atualizar os dados? (S/N): ");
            scanf(" %c", &resposta);

                if(resposta == 'S' || resposta == 's')
                {
                    int siglaRepetida;  // VALIDAÇÃO DA NOVA SIGLA

                        do
                        {
                        siglaRepetida = 0;

                        printf("Digite a nova sigla: ");
                        scanf("%3s", equipes[pos].sigla);

                            for(int i = 0; i < qtd_equipe; i++)
                        {
                            if(i != pos && strcmp(equipes[pos].sigla, equipes[i].sigla) == 0)
                        {
                            printf("Sigla ja cadastrada!\n");
                            siglaRepetida = 1;
                            break;
                        }
                    }

                    }
                    while(siglaRepetida);


        do  // VALIDAÇÃO DA NOVA UF
        {
            printf("Digite o novo estado: ");
            scanf("%2s", equipes[pos].estado);

            if(!estadoValido(equipes[pos].estado))
            {
                printf("UF invalida!\n");
            }

        }while(!estadoValido(equipes[pos].estado));

        printf("Equipe atualizada com sucesso!\n");
    }

    getchar();
}
    else  // CADASTRO DE UMA NOVA EQUIPE
    {
        strcpy(equipes[qtd_equipe].nome_equipe, nome);

        int siglaRepetida;  // VALIDAÇÃO DA SIGLA DA NOVA EQUIPE

    do
    {
        siglaRepetida = 0;

        printf("Digite a sigla: ");
        scanf("%3s", equipes[qtd_equipe].sigla);

            for(int i = 0; i < qtd_equipe; i++)
            {
                if(strcmp(equipes[qtd_equipe].sigla,
                  equipes[i].sigla) == 0)
                {
                    printf("Sigla ja cadastrada!\n");
                    siglaRepetida = 1;
                    break;
                }
            }

    }
    while(siglaRepetida);

    do   // VALIDAÇÃO DA UF DA NOVA EQUIPE
    {
        printf("Digite o estado: ");
        scanf("%2s", equipes[qtd_equipe].estado);

            if(!estadoValido(equipes[qtd_equipe].estado))
            {
                printf("UF invalida!\n");
            }

    }
    while(!estadoValido(equipes[qtd_equipe].estado));

        // INICIALIZAÇÃO DAS ESTATÍSTICAS DA EQUIPE
        equipes[qtd_equipe].jogos = 0;
        equipes[qtd_equipe].vitorias = 0;
        equipes[qtd_equipe].empates = 0;
        equipes[qtd_equipe].derrotas = 0;
        equipes[qtd_equipe].gols_pro = 0;
        equipes[qtd_equipe].gols_contra = 0;
        equipes[qtd_equipe].pontos = 0;

        qtd_equipe++;  // REGISTRA A NOVA EQUIPE NO VETOR
    }


     printf("Deseja cadastrar outra equipe? (S/N): ");  // VERIFICA SE O USUÁRIO DESEJA CONTINUAR CADASTRANDO
     scanf(" %c", &continuar);

     getchar(); // remove o Enter que ficou no teclado
    }

    //  BUSCA POR ESTADO
    printf("\n--- BUSCA POR ESTADO ---\n");
    buscarPorEstado(equipes, qtd_equipe);  // Chamada da função


    return 0;

}
