/**
 * @file Funcoes.c
 * @author João Apresentação (a21152@alunos.ipca.pt)
 * @author Gonçalo Cunha (a21145@alunos.ipca.pt)
 * @author Carlos Barbosa (a21157@alunos.ipca.pt)
 *
 * @brief Neste ficheiro .c será introduzido todas as funções do programa exceto a main
 * @version 0.1
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcoes.h"

/**
 * @brief Espaço reservado as funções de pedidos do utilizador
 *
 */
#pragma region PEDIDOS

/**
 * @brief Verifica se um pedido existe através do seu numero de ordem
 *
 * @param ps pedidos
 * @param num numero de ordem
 * @return int
 */
int existePedido(Pedidos *ps, int num)
{
    for (int i = 0; i < ps->qt_pedidos; i++)
    {
        if (ps->pedido[i].num == num)
        {
            return 1; // existe
        }
    }
    return 0; // nao existe
}

/**
 * @brief  Inserção de um novo pedido de utilização
 *
 * @param ps pedidos
 * @param id identificador do pedido
 * @param nif nif do utilizador
 * @param cod codigo
 * @param tempo
 * @param distancia
 * @return int
 */
int insertPedido(Pedidos *ps, int id, Pedido p)
{
    if (id < TAM_A)
    {
        ps->pedido[id].num = id;
        ps->pedido[id].nif = p.nif;
        strcpy(ps->pedido[id].cod, p.cod);
        ps->pedido[id].tempo = p.tempo;
        ps->pedido[id].distancia = p.distancia;
        return 1;
    }
    else if (id >= TAM_A)
        printf("Erro: Array lotado\n");
    return 0;
}

/**
 * @brief Atribuição dos valores a serem inseridos em um novo pedido de utilização
 *
 * @param ps pedidos
 */
void criarPedido(Pedidos *ps)
{
    Pedido p;

    printf("NIF: ");
    scanf("%d", &p.nif);

    printf("CODIGO: ");
    scanf("%s", p.cod);

    printf("TEMPO (MIN): ");
    scanf("%d", &p.tempo);

    printf("DISTANCIA (KM): ");
    scanf("%d", &p.distancia);

    if (insertPedido(ps, ps->qt_pedidos, p) == 1)
    {
        ps->qt_pedidos++;
        printf("Inserido com sucesso\n");
    }
    else
        printf("Erro na insercao\n");
}

/**
 * @brief Listagem de todo os pedidos de utilização
 *
 * @param ps pedidos
 */
void mostraPedidos(Pedidos *ps)
{
    for (int i = 0; i < ps->qt_pedidos; i++)
    {
        mostraPedido(ps->pedido[i]);
    }
}

/**
 * @brief Listagem de um pedido de utilização
 *
 * @param p pedido
 */
void mostraPedido(Pedido p)
{
    printf("\n------------------------------------------");
    printf("\nNUMERO ORDEM  : %d", p.num);
    printf("\nNIF           : %d", p.nif);
    printf("\nCODIGO        : %s", p.cod);
    printf("\nTEMPO (MIN)   : %d", p.tempo);
    printf("\nDISTANCIA (KM): %.d", p.distancia);
    printf("\n------------------------------------------\n");
}

/**
 * @brief Remoção de um pedido de utilização a partir do seu código
 *
 * @param cod codigo
 * @param ps pedidos
 * @return int
 */
int removerPedido(char cod[], Pedidos *ps)
{
    int remocoes = 0;
    for (int i = 0; i < ps->qt_pedidos; i++)
    {
        if (strcmp(cod, ps->pedido[i].cod) == 0)
        {
            int qt_recuar = ps->qt_pedidos - 1;
            for (int j = i; j < qt_recuar; j++)
            {
                ps->pedido[j] = ps->pedido[j + 1];
            }
            ps->qt_pedidos--;
            remocoes++;
        }
    }
    if (remocoes > 0)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Cálculo do custo associado a um pedido de utilização a partir da indicação do seu número de ordem
 *
 * @param num numero de ordem
 * @param e esquema
 * @param ps pedidos
 * @return float
 */
float custoPedido(int num, Esquema *e, Pedidos *ps)
{
    char cod[TAM_T];
    float custo;
    int tempo;

    for (int i = 0; i < ps->qt_pedidos; i++)
    {
        if (num == ps->pedido[i].num)
        {
            strcpy(cod, ps->pedido[i].cod);
            tempo = ps->pedido[i].tempo;
        }
    }

    for (int i = 0; i < e->qt_meios; i++)
    {
        if (strcmp(cod, e->meio[i].cod) == 0)
        {
            custo = e->meio[i].custo;
        }
    }
    return custo * tempo;
}

#pragma endregion

/**
 * @brief Espaço reservado as funções dos meios de mobilidade
 *
 */
#pragma region MEIO_MOBILIDADE

/**
 * @brief Procura e retorna um meio de mobilidade
 *
 * @param e esquema
 * @param cod codigo
 * @return Meio
 */
Meio buscaMeio(Esquema *e, char cod[])
{
    Meio m;
    for (int i = 0; i < e->qt_meios; i++)
    {
        if (strcmp(e->meio[i].cod, cod) == 0)
        {
            m = e->meio[i];
        }
    }
    return m;
}

/**
 * @brief verifica se um meio existe
 *
 * @param e esquema
 * @param cod codigo
 * @return int
 */
int existeMeio(Esquema *e, char cod[])
{
    for (int i = 0; i < e->qt_meios; i++)
    {
        if (strcmp(cod, e->meio[i].cod) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Inserção de um novo meio de mobilidade elétrica
 *
 * @param e esquema
 * @param id identificador do esquema
 * @param cod codigo
 * @param tipo
 * @param custo
 * @param autonomia
 * @return int
 */
int insertMeio(Esquema *e, int id, Meio m)
{
    if (id < TAM_A && existeMeio(e, m.cod) == 0)
    {
        strcpy(e->meio[id].cod, m.cod);
        strcpy(e->meio[id].tipo, m.tipo);
        e->meio[id].custo = m.custo;
        e->meio[id].autonomia = m.autonomia;
        e->meio[id].id = id;
        return 1;
    }
    else if (id >= TAM_A)
        printf("Erro: Array lotado\n");
    else if (existeMeio(e, m.cod) != 0)
        printf("Erro: Meio ja existente\n");

    return 0;
}

/**
 * @brief Atribuição dos valores a serem inseridos em um novo meio de mobilidade elétrica
 *
 * @param e esquema
 */
void criarMeio(Esquema *e)
{
    Meio m;

    printf("CODIGO: ");
    scanf("%s", m.cod);

    printf("TIPO: ");
    scanf("%s", m.tipo);

    printf("CUSTO ($): ");
    scanf("%f", &m.custo);

    printf("AUTONOMIA: ");
    scanf("%d", &m.autonomia);

    if (insertMeio(e, e->qt_meios, m) == 1)
        e->qt_meios++;
}

/**
 * @brief Listagem dos dados de todos os meios de mobilidade elétrica
 *
 * @param e esquema
 */
void mostraMeios(Esquema *e)
{
    for (int i = 0; i < e->qt_meios; i++)
    {
        mostraMeio(e->meio[i]);
    }
}

/**
 * @brief Listagem dos dados de um meio de mobilidade elétrica
 *
 * @param m meio de mobilidade
 */
void mostraMeio(Meio m)
{
    printf("\n------------------------------------------");
    printf("\nCODIGO   : %s", m.cod);
    printf("\nTIPO     : %s", m.tipo);
    printf("\nCUSTO ($): %.2f", m.custo);
    printf("\nAUTONOMIA: %d", m.autonomia);
    printf("\n------------------------------------------\n");
}

/**
 * @brief Remoção de um meio de mobilidade elétrica a partir do seu código
 *
 * @param e esquema
 * @param cod codigo
 */
int removerMeio(Esquema *e, char cod[])
{
    if (existeMeio(e, cod) == 1)
    {
        for (int i = 0; i < e->qt_meios; i++)
        {
            if (strcmp(cod, e->meio[i].cod) == 0)
            {
                for (int j = i; j < e->qt_meios - 1; j++)
                {
                    e->meio[j] = e->meio[j + 1];
                }
                e->qt_meios--;
                return 1;
            }
        }
    }
    else
        printf("Meio inexistente\n");
    return 0;
}

/**
 * @brief Listagem do plano de utilização de um determinado meio de
 * mobilidade elétrica, a partir do seu código, por
 * ordem crescente de número de ordem do pedido
 *
 * @param e esquema
 * @param ps pedidos
 * @param cod codigo
 */
void listarPlanoMeio(Esquema *e, Pedidos *ps, char cod[])
{
    if (existeMeio(e, cod) == 1)
    {
        Meio m = buscaMeio(e, cod);

        int auto_ini = m.autonomia, tempo_ini = 0;
        printf("-----------------------------");
        for (int i = 0; i < ps->qt_pedidos; i++)
        {
            if (strcmp(ps->pedido[i].cod, m.cod) == 0)
            {
                printf("\nNUMERO ORDEM     : %d", ps->pedido[i].num);
                printf("\nNIF              : %d", ps->pedido[i].nif);
                printf("\nTEMPO INICIO     : %d", tempo_ini);
                printf("\nTEMPO TERMINO    : %d", tempo_ini + ps->pedido[i].tempo);
                printf("\nAUTONOMIA INICIAL: %d", auto_ini);
                printf("\nCODIGO           : %s", m.cod);
                printf("\n-----------------------------");

                tempo_ini += ps->pedido[i].tempo;
                auto_ini -= ps->pedido[i].distancia;
            }
        }
        printf("\n");
    }
    else
        printf("Meio inexistente\n");
}

#pragma endregion

/**
 * @brief Espaço reservado as funções de distribuição dos meios pelos utilizadores
 *
 */
#pragma region DISTRIBUIR_VEICULO

/**
 * @brief procura um veiculo com autonomia suficiente para uma determinada distancia a percorrer
 * retorna o novo codigo
 * @param e esquema
 * @param distancia
 * @param tipo
 * @return char*
 */
char *procuraVeiculoSuficiente(Esquema *e, int distancia, char tipo[])
{
    for (int i = 0; i < e->qt_meios; i++)
    {
        if (e->meio[i].autonomia > distancia)
        {
            if (strcmp(e->meio[i].tipo, tipo) == 0)
            {
                return e->meio[i].cod;
            }
        }
    }
    return "Vazio";
}

/**
 * @brief verifica se a autonomia de um meio é ultrapassada pela distancia de um pedido
 * retorn pedido com codigo alterado ou nao
 * @param e esquema
 * @param p pedido
 * @return Pedido
 */
Pedido verificaAutonomia(Esquema *e, Pedido p)
{
    for (int i = 0; i < e->qt_meios; i++)
    {
        if (strcmp(e->meio[i].cod, p.cod) == 0)
        {
            if (p.distancia > e->meio[i].autonomia)
            {
                strcpy(p.cod, procuraVeiculoSuficiente(e, p.distancia, e->meio[i].tipo));
            }
        }
    }
    return p;
}

/**
 * @brief realiza uma distribuição dos meios de mobilidade pelos utilizadores
 *
 * @param e esquema
 * @param ps pedidos
 */
void distribuirMeios(Esquema *e, Pedidos *ps)
{
    Pedido p;
    for (int i = 0; i < ps->qt_pedidos; i++)
    {
        p = verificaAutonomia(e, ps->pedido[i]);
        if (existeMeio(e, p.cod) == 1)
            mostraPedido(p);
        printf("\nAviso: pedidos para meios nao disponiveis nao serao exibidos\n");
    }
}

#pragma endregion

/**
 * @brief Espaço reservado as funções de menus
 *
 */
#pragma region MENUS

/**
 * @brief parte visual do menu principal
 *
 */
void interfacePrincipal()
{
    printf("-------------------------\n");
    printf("Menu Principal\n");
    printf("-------------------------\n");
    printf("[1]-Menu meio\n[2]-Menu pedido\n[3]-Distribuir meios\n[0]-Sair\n");
    printf("-------------------------\n");
    printf("Insira a opcao: ");
}

/**
 * @brief menu com opcoes que correspondem a interface principal
 *
 * @param e esquema
 * @param ps pedidos
 */
void menuPrincipal(Esquema *e, Pedidos *ps)
{
    int op;
    interfacePrincipal();
    scanf("%d", &op);
    while (op != 0)
    {
        switch (op)
        {
        case 1:
            system("cls");
            menuMeio(e, ps);
            system("cls");
            break;

        case 2:
            system("cls");
            menuPedido(e, ps);
            system("cls");
            break;

        case 3:
            system("cls");
            if (e->qt_meios > 0 && ps->qt_pedidos > 0)
            {
                distribuirMeios(e, ps);
                system("pause");
                system("cls");
            }
            else
                printf("Dados insuficientes");
            break;

        case 0:
            break;

        default:
            printf("Opcao invalida");
            getchar();
            system("cls");
            break;
        }
        interfacePrincipal();
        scanf("%d", &op);
    }
}

/**
 * @brief parte visual do menu dos meios de mobilidade
 *
 */
void interfaceMeio()
{
    printf("-------------------------\n");
    printf("Menu Meio\n");
    printf("-------------------------\n");
    printf("[1]-Inserir meio\n[2]-Listar meios\n[3]-Remover meio\n[4]-Listar plano de utilizacao\n[0]-Sair\n");
    printf("-------------------------\n");
    printf("Insira a opcao: ");
}

/**
 * @brief menu com opcoes que correspondem a interface dos meios de mobilidade
 *
 * @param e
 * @param ps
 */
void menuMeio(Esquema *e, Pedidos *ps)
{
    int op;
    char cod[TAM_T];
    interfaceMeio();
    scanf("%d", &op);
    while (op != 0)
    {
        switch (op)
        {
        case 1:
            system("cls");
            criarMeio(e);
            break;

        case 2:
            system("cls");
            if (e->qt_meios > 0)
            {
                mostraMeios(e);
            }
            else
                printf("Nao existem meios inseridos\n");
            break;

        case 3:
            system("cls");
            if (e->qt_meios > 0)
            {
                printf("Insira codigo: ");
                scanf("%s", cod);
                if (removerMeio(e, cod) == 1)
                    printf("Removido com sucesso\n");
            }
            else
                printf("Nao existem meios inseridos\n");
            break;

        case 4:
            system("cls");
            if (e->qt_meios > 0)
            {
                printf("Insira codigo: ");
                scanf("%s", cod);
                listarPlanoMeio(e, ps, cod);
            }
            else
                printf("Nao existem meios inseridos\n");
            break;

        case 0:
            printf("A sair ...");
            break;

        default:
            printf("Opcao invalida\nInsira novamente\n");
            break;
        }
        system("pause");
        system("cls");
        interfaceMeio();
        scanf("%d", &op);
    }
}

/**
 * @brief parte visual do menu de pedidos do utilizador
 *
 */
void interfacePedido()
{
    printf("-------------------------\n");
    printf("Menu Pedido\n");
    printf("-------------------------\n");
    printf("[1]-Inserir pedido\n[2]-Listar pedidos\n[3]-Remover pedido\n[4]-Custo associado\n[0]-Sair\n");
    printf("-------------------------\n");
    printf("Insira a opcao: ");
}

/**
 * @brief menu com opcoes que correspondem a interface dos pedidos do utilizador
 *
 * @param e
 * @param ps
 */
void menuPedido(Esquema *e, Pedidos *ps)
{
    int op, num;
    char cod[TAM_T];
    interfacePedido();
    scanf("%d", &op);
    while (op != 0)
    {
        switch (op)
        {
        case 1:
            system("cls");
            criarPedido(ps);
            break;

        case 2:
            system("cls");
            if (ps->qt_pedidos > 0)
            {
                mostraPedidos(ps);
            }
            else
                printf("Nao existem pedidos inseridos");
            break;

        case 3:
            system("cls");
            if (ps->qt_pedidos > 0)
            {
                printf("Insira codigo: ");
                scanf("%s", cod);
                if (removerPedido(cod, ps) == 1)
                    printf("Removido com sucesso\n");
                else
                {
                    printf("Pedido inexistente");
                }
            }
            else
                printf("Nao existem pedidos inseridos");
            break;

        case 4:
            system("cls");
            if (ps->qt_pedidos > 0)
            {
                printf("Insira numero de ordem: ");
                scanf("%d", &num);
                if (existePedido(ps, num) == 1)
                {
                    printf("Custo total: %.2f $\n", custoPedido(num, e, ps));
                }
                else
                    printf("Pedido inexistente");
            }
            else
                printf("Nao existem pedidos inseridos");
            break;

        case 0:
            printf("A sair ...");
            break;

        default:
            printf("Opcao invalida");
            getchar();
            system("cls");
            break;
        }
        system("pause");
        system("cls");
        interfacePedido();
        scanf("%d", &op);
    }
}

#pragma endregion

/**
 * @brief Espaço reservado as funções que manipulam ficheiros
 *
 */
#pragma region FILES

/**
 * @brief manipula o ficheiro esquema.txt para leitura
 *
 * @param e esquema
 * @return int
 */
int lerMeios(Esquema *e)
{
    FILE *file;
    Meio m;
    e->qt_meios = 0;

    file = fopen("esquema.txt", "rt");

    if (file == NULL)
    {
        printf("Ficheiro não pode ser aberto!\n");
        getchar();
        return 0;
    }

    while (!feof(file))
    {
        fscanf(file, "%[^;];%[^;];%f;%d\n", m.cod, m.tipo, &m.custo, &m.autonomia);
        if (insertMeio(e, e->qt_meios, m) == 1)
            e->qt_meios++;
        else
            break;
    }
    fclose(file);
    return 0;
}

/**
 * @brief manipula o ficheiro esquema.txt para escrita
 *
 * @param e esquema
 */
int guardarMeios(Esquema *e)
{
    FILE *file;
    file = fopen("esquema.txt", "wt");

    if (file == NULL)
    {
        printf("Ficheiro não pode ser aberto!\n");
        getchar();
        return 0;
    }

    for (int i = 0; i < e->qt_meios; i++)
    {
        fprintf(file, "%s;", e->meio[i].cod);
        fprintf(file, "%s;", e->meio[i].tipo);
        fprintf(file, "%.2f;", e->meio[i].custo);
        fprintf(file, "%d\n", e->meio[i].autonomia);
    }
    fclose(file);
    return 1;
}

/**
 * @brief manipula o ficheiro historico.txt para leitura
 *
 * @param ps pedidos
 * @return int
 */
int lerPedidos(Pedidos *ps)
{
    FILE *file;
    Pedido p;
    ps->qt_pedidos = 0;

    file = fopen("historico.txt", "rt");

    if (file == NULL)
    {
        printf("Ficheiro não pode ser aberto!\n");
        getchar();
        return 0;
    }

    while (!feof(file))
    {
        fscanf(file, "%d;%d;%[^;];%d;%d\n", &p.num, &p.nif, p.cod, &p.tempo, &p.distancia);
        if (insertPedido(ps, ps->qt_pedidos, p) == 1)
            ps->qt_pedidos++;
        else
            break;
    }
    fclose(file);
    return 0;
}

/**
 * @brief manipula o ficheiro historico.txt para escrita
 *
 * @param ps pedidos
 */
int guardarPedidos(Pedidos *ps)
{
    FILE *file;
    file = fopen("historico.txt", "wt");

    if (file == NULL)
    {
        printf("Ficheiro não pode ser aberto!\n");
        getchar();
        return 0;
    }

    for (int i = 0; i < ps->qt_pedidos; i++)
    {
        fprintf(file, "%d;", ps->pedido[i].num);
        fprintf(file, "%d;", ps->pedido[i].nif);
        fprintf(file, "%s;", ps->pedido[i].cod);
        fprintf(file, "%d;", ps->pedido[i].tempo);
        fprintf(file, "%d\n", ps->pedido[i].distancia);
    }
    fclose(file);
    return 1;
}

#pragma endregion
