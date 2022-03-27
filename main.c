/**
 * @file main.c
 * @author João Apresentação (a21152@alunos.ipca.pt)
 * @author Gonçalo Cunha (a21145@alunos.ipca.pt)
 * @author Carlos Barbosa (a21157@alunos.ipca.pt)
 * 
 * @brief Neste ficheiro .c apenas terá a função main para execução do programa
 * @version 0.1
 * @date 2022-01-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "Funcoes.h"

/**
 * @brief função main
 * 
 * @return int 
 */
int main()
{
    Pedidos ps;
    Esquema e;

    lerPedidos(&ps);
    lerMeios(&e);
    
    menuPrincipal(&e, &ps);

    if(guardarPedidos(&ps) == 1) printf("Guardado com sucesso");
    if(guardarMeios(&e)== 1) printf("Guardado com sucesso");;

    return 0;
}
