/**
 * @file Funcoes.h
 * @author João Apresentação (a21152@alunos.ipca.pt)
 * @author Gonçalo Cunha (a21145@alunos.ipca.pt)
 * @author Carlos Barbosa (a21157@alunos.ipca.pt)
 * 
 * @brief Nesta biblioteca será introduzido código referente a todas as assinaturas de funções
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef FUNCOES
#define FUNCOES
#include <stdio.h>
#include "Estruturas.h"

#pragma region ASSINATURAS PEDIDO
int existePedido(Pedidos *ps, int num);
void mostraPedidos(Pedidos *ps);
void mostraPedido(Pedido p);
int guardarPedidos(Pedidos *ps);
int lerPedidos(Pedidos *ps);
int insertPedido(Pedidos *ps, int id, Pedido p);
void criarPedido(Pedidos *ps);
int removerPedido(char cod[], Pedidos *ps);
float custoPedido(int num, Esquema *e, Pedidos *ps);
#pragma endregion

#pragma region ASSINATURAS MEIO
int existeMeio(Esquema *e, char cod[]);
void mostraMeios(Esquema *e);
void mostraMeio(Meio m);
int insertMeio(Esquema *e, int count, Meio m);
int lerMeios(Esquema *e);
int guardarMeios(Esquema *e);
void criarMeio(Esquema *e);
int removerMeio(Esquema *e, char cod[]);
void listarPlanoMeio(Esquema *e, Pedidos *ps, char cod[]);
#pragma endregion

#pragma region ASSISNATURAS AUTONOMIA
Pedido verificaAutonomia(Esquema *e, Pedido p);
char *procuraVeiculoSuficiente(Esquema *e, int distancia, char tipo[]);
void distribuirMeios(Esquema *e, Pedidos *ps);
#pragma endregion

#pragma region ASSINATURAS MENU
void interfacePrincipal();
void menuPrincipal(Esquema *e, Pedidos *ps);
void interfaceMeio();
void menuMeio(Esquema *e, Pedidos *ps);
void interfacePedido();
void menuPedido(Esquema *e, Pedidos *ps);
#pragma endregion

#endif