# Organização De Arquivo Sequencial Indexado

Neste projeto foram criadas duas tabelas para a pesquisa binária. Seus dados foram retirados do arquivo jewelry.csv e separados entre dados relacionados as joias e a ordem dos pedidos. 

Para os dados das joias foi criado o arquivo chamado jewelry.dat contendo as colunas:

```bash
jewelry(id, price, mainMetal, mainColor, productGender, category, mainGem, elo, excluido)
```

Para os dados dos pedidos foi criado um arquivo chamado order.dat contendo as colunas:

```bash
order(id, items, date, time, countItems, elo, excluido)
```

Visando um auxilio na pesquisa foi ainda criado struct de header:

```bash
header(numeroRegistros, numeroInsercoes,numeroExclusoes)
```

E uma struct de indice:
```bash
Indice(ultimoDoBloco, deslocamento,numeroRegistrosNoBloco)
```

Para a criação desse software foram implementadas as seguintes funções que serão explicadas categoricamente cada uma delas:

### *CriacaoDataFile*:  

 ```gerarParticoesJewelry(file)'''``` : Através de uma organização com seleção por substituição realizamos uma pré-organização dos dados dados a serem inseridos, apenas necessitamos que seja informado o nome do arquivo que é 'jewelry.dat'

 ```intercalarParticoesJewelryFile(num_particoes, contJoias)```: Realizamos a inserção das informações referentes as joias, basta informarmos a quantidade de partições a a quantidade de joias a serem inseridas

 ```criarDataFiles()```: criamos os arquivos jewelry.dat e order.dat  e chamamos as demais funções para a organização dos dados do arquivo jewelry.csv


### *CriacaoArquivoIndice*:

```criarArquivoindicePedidos(num_indice_max, file)```: Criamos o arquivos de indices através de partições ja criadas. Esses indices são referentes a ordem do arquivo order.dat. Precisamos informar que é o File order.dat como referencia e a quantidade de numero de registros preente no arquivo a ser lido.

```criarArquivoindiceJoias(num_indice_max, file)```: Criamos o arquivos de indices através de partições ja criadas. Esses indices são referentes a ordem do arquivo jewelry.dat. Precisamos informar que é o File jewelry.dat como referencia e a quantidade de numero de registros preente no arquivo a ser lido.

### *Consultas*:


```mostrarPedidos(file)```: Realizamos a consulta de todos os pedidos do arquivo order.dat

```mostrarPedidos(file)```: Realizamos a consulta de todos os pedidos do arquivo order.dat que estão excluidos

```mostrarJoias(file)```: Realizamos a consulta de todos as joias do arquivo jewelry.dat

```mostrarJoiasComExcluidos(file)```: Realizamos a consulta de todos as joias do arquivo jewelry.dat que estão excluidas

```pesquisaBinariaOrder(file, cod)```:  Deslocam-se até a posição informada através do cod e verifica caso ela exista ou não. Precisamos da informação de nosso arquivo Order.dat(file) e do item que procuramos(cod)

```pesquisaBinariaJewelry(file, cod)```:Desloca-se até a posição informada através do cod e verifica-se caso ela exista ou não. Precisamos da informação de nosso arquivo Jewelry.dat(file) e do item que procuramos(cod)

```calculaTotalPedido(file_order, file_jewelry, cod)```: Realizamos o calculo do total de um único pedido 

```calculaTotalDosPedidos(file_order, file_jewelry)```: Realizamos o calculo do totoal de todos os pedidos


### *Operações*:

```insercaoOrder(file, pedido_inserido)```: Faz a inserção do novo pedido no arquivo Order.dat, adiciona na área de extensão e encontra seus valores vizinhos aplicando uma lógica de ELO. 

```remocaoOrder(file, cod)```: Remove um valor de nosso arquivo Order.dat. Esse valor é excluido de forma lógica, ou seja, o registro ainda existe no arquivo até a reorganização do arquivo.

```insercaoJewelry(file, pedido_inserido)```: Faz a inserção do novo pedido no arquivo Jewelry.dat, adiciona na área de extensão e encontra seus valores vizinhos aplicando uma lógica de ELO. 

```remocaoJewelry(file, cod)```: Remove um valor de nosso arquivo Jewelry.dat. Esse valor é excluido de forma lógica, ou seja, o registro ainda existe no arquivo até a reorganização do arquivo.


```reorganizacaoArquivoOrder(file)```:  determinamos um valor limite, seja esse valor equivalente a 5% do maximo de dados armazenados em nosso arquivo sem nenhuma inserção ou exclusão. Ao atingirmos esse valor através de inserções e exclusões realizamos a reorganização do arquivo Order.dat ou Jewelry.dat criando novos arquivos de indice

```reorganizacaoArquivoJewelry(file)```:  determinamos um valor limite, seja esse valor equivalente a 5% do maximo de dados armazenados em nosso arquivo sem nenhuma inserção ou exclusão. Ao atingirmos esse valor através de inserções e exclusões realizamos a reorganização do arquivo Order.dat ou Jewelry.dat criando novos arquivos de indice


### *Main*:

Utilizamos as operações apontadas acima, inserindo dados, removendo eles, criando as partições e mostrando os dados.
