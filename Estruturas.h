/**
 * @file Estruturas.h
 * @author João Apresentação (a21152@alunos.ipca.pt)
 * @author Gonçalo Cunha (a21145@alunos.ipca.pt)
 * @author Carlos Barbosa (a21157@alunos.ipca.pt)
 * 
 * @brief Nesta biblioteca terá todas as structs do programa
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESTRUTURAS
#define ESTRUTURAS
#define TAM_T 10 //tamanho para texto
#define TAM_A 100 //tamanho para structs
/**
 * @brief Struct que representa um pedido realizado por um utilizador
 * 
 */
typedef struct
{
    int num, nif, tempo, distancia;
    char cod[TAM_T];

} Pedido;

/**
 * @brief Struct para um conjunto de pedidos e sua respetiva quantidade
 * 
 */
typedef struct
{
    int qt_pedidos;
    Pedido pedido[TAM_A];

} Pedidos;

/**
 * @brief Estrutura do meio de mobilidade elétrica
 * 
 */
typedef struct 
{
    char cod[TAM_T], tipo[TAM_T];
    float custo;
    int autonomia, id;

} Meio;

/**
 * @brief Estrutura do conjunto de meios de mobilidade elétrica e sua respetiva quantidade
 * 
 */
typedef struct 
{
    int qt_meios;
    Meio meio[TAM_A];

} Esquema;

#endif