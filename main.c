#include <time.h>
#include "operacoes.c"
#include "IndiceBplustree.c"
#include "tabelaHash.c"
#include "structs.h"

int main()
{
    clock_t t;

    // criarDataFiles();    

    FILE *fOrder = fopen("order.dat","rb+");
    FILE *fJewelry = fopen("jewelry.dat","rb+");
    
    if(!fOrder || !fJewelry)
    {
        criarDataFiles();    
        fOrder = fopen("order.dat","rb+");
        fJewelry = fopen("jewelry.dat","rb+");
    }

    // 1 - Mostrar pedidos e joias;
    // printf("Pedidos:\n");
    // mostrarPedidos(fOrder);
    // printf("\n\nJoias:\n");
    // mostrarJoias(fJewelry);
    
    //2 - Consultar um pedido e uma joia;
    // ORDER order = pesquisaBinariaOrder(fOrder,2718537529266536800,&t);
    // printf("%lu\n",order.id);
    // JOIA joia = pesquisaBinariaJewelry(fJewelry,1956663836694020322,&t);
    // printf("%lu\n",joia.id);
    
    // 3 - Consultas extras - calculaTotalDosPedidos so funciona no terminal do vscode(ou alguma ide) não sei pq
    // double totalPedido = calculaTotalPedido(fOrder,fJewelry,2718537529266536812);
    // printf("R$%.2lf\n",totalPedido);
    // double totalPedidos = calculaTotalDosPedidos(fOrder,fJewelry);
    // printf("R$%.2lf\n",totalPedidos);
    
    // 4 - Insercao
    // ORDER pedido;
    // pedido.countItems = 0;
    // strcpy(pedido.date,"teste");
    // strcpy(pedido.time, "teste");
    // insercaoOrder(fOrder,pedido);
    // insercaoOrder(fOrder,pedido);
    // insercaoOrder(fOrder,pedido);
    // insercaoOrder(fOrder,pedido);
    // insercaoOrder(fOrder,pedido);
    // insercaoOrder(fOrder,pedido);
    // insercaoOrder(fOrder,pedido);
    // insercaoOrder(fOrder,pedido);
    
    // JOIA joia;
    // strcpy(joia.category ,"teste");
    // strcpy(joia.mainColor, "teste");
    // strcpy(joia.mainMetal ,"teste");
    // strcpy(joia.mainGem, "teste");
    // insercaoJewelry(fJewelry,joia);
    // insercaoJewelry(fJewelry,joia);
    // insercaoJewelry(fJewelry,joia);
    // insercaoJewelry(fJewelry,joia);
    // insercaoJewelry(fJewelry,joia);
    // insercaoJewelry(fJewelry,joia);
    // insercaoJewelry(fJewelry,joia);
    // insercaoJewelry(fJewelry,joia);
    
    //5 - Remocao
    // remocaoOrder(fOrder,1924719191579951782,&t);
    // remocaoOrder(fOrder,1924899396621697920,&t);
    // remocaoOrder(fOrder,1925511016616034733,&t);
    // remocaoOrder(fOrder,1925626951238681511,&t);
    // remocaoOrder(fOrder,1925740842841014667,&t);
    
    // remocaoJewelry(fJewelry,2501331816804253948,&t);
    // remocaoJewelry(fJewelry,2537782512956997930,&t);
    // remocaoJewelry(fJewelry,2539957035806490883,&t);
    // remocaoJewelry(fJewelry,2540059984184476519,&t);
    // remocaoJewelry(fJewelry,2541962442884252323,&t);
    
    // 6 - Reorganização, definir limite de insercoes e exclusoes para implementar
    // reorganizacaoArquivoOrder(fOrder);
    // reorganizacaoArquivoJewelry(fJewelry);
    // fOrder = fopen("order.dat","rb+");
    // fJewelry = fopen("jewelry.dat","rb+");
    
    // mostrarPedidosComExcluidos(fOrder);
    // mostrarJoiasComExcluidos(fJewelry);
    
    //PARTE 2 INDICE EM MEMORIA E TABELA HASH

    // BPLUSNODO *raiz = criarIndiceEmMemoriaArquivoJoias(fJewelry, &t);
    // printf("Tempo de criação do indice em Árvore B+: %fs\n\n\n", ((double)t)/CLOCKS_PER_SEC);

    //Consultas com tempo de execucao em memoria
    //Consulta1
    // JOIA joia;
    // joia = pesquisaComIndiceEmMemoria(raiz,fJewelry,2501331816804253948,&t);
    // joia.id != 0 ? printf("%lu\n",joia.id) : printf("Joia nao encontrada\n");
    // printf("Tempo de execucao consulta1 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    // raiz = voltarParaRaiz(raiz);
    //Consulta2
    // joia = pesquisaComIndiceEmMemoria(raiz,fJewelry,2537782512956997930,&t);
    // joia.id != 0 ? printf("%lu\n",joia.id) : printf("Joia nao encontrada\n");
    // printf("Tempo de execucao consulta2 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    // raiz = voltarParaRaiz(raiz);
    //Consulta3
    // joia = pesquisaComIndiceEmMemoria(raiz,fJewelry,2539957035806490883,&t);
    // joia.id != 0 ? printf("%lu\n",joia.id) : printf("Joia nao encontrada\n");
    // printf("Tempo de execucao consulta3 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    // raiz = voltarParaRaiz(raiz);
    //Consulta4
    // joia = pesquisaComIndiceEmMemoria(raiz,fJewelry,2540059984184476519,&t);
    // joia.id != 0 ? printf("%lu\n",joia.id) : printf("Joia nao encontrada\n");
    // printf("Tempo de execucao consulta4 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    // raiz = voltarParaRaiz(raiz);
    //Consulta5
    // joia = pesquisaComIndiceEmMemoria(raiz,fJewelry,2541962442884252323,&t);
    // joia.id != 0 ? printf("%lu\n",joia.id) : printf("Joia nao encontrada\n");
    // printf("Tempo de execucao consulta5 (memoria): %fs\n\n\n", ((double)t)/CLOCKS_PER_SEC);
    // raiz = voltarParaRaiz(raiz);

    //Consultas com tempo de execucao com indices em arquivo
    //Consulta 1
    // joia = pesquisaBinariaJewelry(fJewelry,2501331816804253948,&t);
    // printf("%lu\n",joia.id);
    // printf("Tempo de execucao consulta1 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 2
    // joia = pesquisaBinariaJewelry(fJewelry,2537782512956997930,&t);
    // printf("%lu\n",joia.id);
    // printf("Tempo de execucao consulta2 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 3
    // joia = pesquisaBinariaJewelry(fJewelry,2539957035806490883,&t);
    // printf("%lu\n",joia.id);
    // printf("Tempo de execucao consulta3 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 4
    // joia = pesquisaBinariaJewelry(fJewelry,2540059984184476519,&t);
    // printf("%lu\n",joia.id);
    // printf("Tempo de execucao consulta4 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 5
    // joia = pesquisaBinariaJewelry(fJewelry,2541962442884252323,&t);
    // printf("%lu\n",joia.id);
    // printf("Tempo de execucao consulta5 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);


    //Remocoes com tempo de execucao em memoria
    //Remocao1
    // remocaoComIndiceEmMemoria(raiz,fJewelry,2501331816804253948,&t) ? printf("Joia removida com sucesso!\n") : printf("Joia nao encontrada!\n");
    // printf("Tempo de execucao remocao1 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao2
    // remocaoComIndiceEmMemoria(raiz,fJewelry,2537782512956997930,&t) ? printf("Joia removida com sucesso!\n") : printf("Joia nao encontrada!\n");
    // printf("Tempo de execucao remocao2 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao3
    // remocaoComIndiceEmMemoria(raiz,fJewelry,2539957035806490883,&t) ? printf("Joia removida com sucesso!\n") : printf("Joia nao encontrada!\n");
    // printf("Tempo de execucao remocao3 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao4
    // remocaoComIndiceEmMemoria(raiz,fJewelry,2540059984184476519,&t) ? printf("Joia removida com sucesso!\n") : printf("Joia nao encontrada!\n");
    // printf("Tempo de execucao remocao4 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao5
    // remocaoComIndiceEmMemoria(raiz,fJewelry,2541962442884252323,&t) ? printf("Joia removida com sucesso!\n") : printf("Joia nao encontrada!\n");
    // printf("Tempo de execucao remocao5 (memoria): %fs\n\n\n", ((double)t)/CLOCKS_PER_SEC);

    //Remocoes com tempo de execucao em arquivos
    //Remocao1
    // remocaoJewelry(fJewelry,2501331816804253948,&t);
    // printf("Tempo de execucao remocao1 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao2
    // remocaoJewelry(fJewelry,2537782512956997930,&t);
    // printf("Tempo de execucao remocao2 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao3
    // remocaoJewelry(fJewelry,2539957035806490883,&t);
    // printf("Tempo de execucao remocao3 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao4
    // remocaoJewelry(fJewelry,2540059984184476519,&t);
    // printf("Tempo de execucao remocao4 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao5
    // remocaoJewelry(fJewelry,2541962442884252323,&t);
    // printf("Tempo de execucao remocao5 (arquivo): %fs\n\n\n", ((double)t)/CLOCKS_PER_SEC);

    TABELAHASH tabelaHashPedidos = criarTabelaHashArquivoCompras(fOrder, &t);
    printf("Tempo de criação do indice em tabela hash: %f\n\n\n", ((double)t)/CLOCKS_PER_SEC);
    //Consultas com tempo de execucao em memoria
    // Consulta1
    // ORDER order;
    // order = pesquisaTabelaHash(fOrder,"2021-12-01","09:47:37",tabelaHashPedidos,&t);
    // if(order.id != 0)
    // {
    //     printf("%lu\n",order.id); 
    // }
    // printf("Tempo de execucao consulta1 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta2
    // order = pesquisaTabelaHash(fOrder,"2021-12-01","09:50:37",tabelaHashPedidos,&t);
    // if(order.id != 0)
    // {
    //     printf("%lu\n",order.id); 
    // }
    // printf("Tempo de execucao consulta2 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta3
    // order = pesquisaTabelaHash(fOrder,"2021-12-01","09:52:06",tabelaHashPedidos,&t);
    // if(order.id != 0)
    // {
    //     printf("%lu\n",order.id); 
    // }
    // printf("Tempo de execucao consulta3 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta4
    // order = pesquisaTabelaHash(fOrder,"2021-12-01","09:55:35",tabelaHashPedidos,&t);
    // if(order.id != 0)
    // {
    //     printf("%lu\n",order.id); 
    // }
    // printf("Tempo de execucao consulta4 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta5
    // order = pesquisaTabelaHash(fOrder,"2021-12-01","09:59:07",tabelaHashPedidos,&t);
    // if(order.id != 0)
    // {
    //     printf("%lu\n",order.id); 
    // }
    // printf("Tempo de execucao consulta5 (memoria): %fs\n\n\n", ((double)t)/CLOCKS_PER_SEC);

    //Consultas com tempo de execucao com indices em arquivo
    //Consulta 1
    // order = pesquisaBinariaOrder(fOrder,2719016587653808559,&t);
    // printf("%lu\n",order.id);
    // printf("Tempo de execucao consulta1 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 2
    // order = pesquisaBinariaOrder(fOrder,2719018098886705639,&t);
    // printf("%lu\n",order.id);
    // printf("Tempo de execucao consulta2 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 3
    // order = pesquisaBinariaOrder(fOrder,2719018846999544322,&t);
    // printf("%lu\n",order.id);
    // printf("Tempo de execucao consulta3 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 4
    // order = pesquisaBinariaOrder(fOrder,2719020596963836492,&t);
    // printf("%lu\n",order.id);
    // printf("Tempo de execucao consulta4 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Consulta 5
    // order = pesquisaBinariaOrder(fOrder,2719022379232658075,&t);
    // printf("%lu\n",order.id);
    // printf("Tempo de execucao consulta5 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);

    //Remocoes com tempo de execucao em memoria
    //Remocao1
    // remocaoTabelaHash(fOrder,"2021-12-01","09:47:37",tabelaHashPedidos,&t);
    // printf("Tempo de execucao remocao1 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao2
    // remocaoTabelaHash(fOrder,"2021-12-01","09:50:37",tabelaHashPedidos,&t);
    // printf("Tempo de execucao remocao2 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao3
    // remocaoTabelaHash(fOrder,"2021-12-01","09:52:06",tabelaHashPedidos,&t);
    // printf("Tempo de execucao remocao3 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao4
    // remocaoTabelaHash(fOrder,"2021-12-01","09:55:35",tabelaHashPedidos,&t);
    // printf("Tempo de execucao remocao4 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao5
    // remocaoTabelaHash(fOrder,"2021-12-01","09:59:07",tabelaHashPedidos,&t);
    // printf("Tempo de execucao remocao5 (memoria): %fs\n", ((double)t)/CLOCKS_PER_SEC);

    //Remocoes com tempo de execucao em arquivos
    //Remocao1
    // remocaoOrder(fOrder,2719016587653808559,&t);
    // printf("Tempo de execucao remocao1 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao2
    // remocaoOrder(fOrder,2719018098886705639,&t);
    // printf("Tempo de execucao remocao2 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao3
    // remocaoOrder(fOrder,2719018846999544322,&t);
    // printf("Tempo de execucao remocao3 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao4
    // remocaoOrder(fOrder,2719020596963836492,&t);
    // printf("Tempo de execucao remocao4 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);
    //Remocao5
    // remocaoOrder(fOrder,2719022379232658075,&t);
    // printf("Tempo de execucao remocao5 (arquivo): %fs\n", ((double)t)/CLOCKS_PER_SEC);


    fclose(fOrder);
    fclose(fJewelry);
    

    return 0;    
}