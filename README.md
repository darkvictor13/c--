# c--
Um reduzido analisador léxico de um subconjunto da linguagem C.

## Integrantes:
    - Victor Emanuel Almeida;
    - Marco A. Guerra Pedroso.

## A linguagem c--:

### Expressões regulares dos Tokens reconhecidos

## Estrutura do projeto
```
├── build
│   ├── main.out
│   ├── Makefile
│   ├── setup_arch.sh
│   └── setup_ubuntu.sh
├── input_files
│   ├── falha.txt
│   └── sucesso.txt
├── README.md
└── src
    ├── cmm.lex
    ├── headers
    │   └── token_definitions.h
    ├── log_info
    │   ├── logging.c
    │   └── logging.h
    └── main.c
```

Onde:
- input_files: Pasta contendo exemplos de arquivos que contém ou não erros léxicos;
- src: Pasta contendo todos os códigos fonte do projeto, sendo escritos diretamente em C, ou gerados automaticamente pelo flex.
- cmm.lex: Arquivo de especificações da linguagem c--, escrito em lex;
- main.c: Arquivo gerado pelo flex;
- main.out: Arquivo resultado final da compilação;

## Compilando e executando
### Compilando

Para realizar o processo de compilação do projeto primeiro é necessário obter os pacotes flex e make dos repositórios oficiais para isso basta rodar:

	./setup_arch.sh

ou caso esteja no ubuntu ou outro derivado do debian:

	./setup_ubuntu.sh

Uma vez com make e flex instalado basta iniciar o processo de compilação entrando na pasta build e rodando o comando:

	make

### Executando
Tendo gerado o executável "main.out" dentro da pasta build, basta executá-lo podendo passar um único argumento adicional sendo esse o caminho relativo para um arquivo texto o qual será tratado como o fonte a ser analisado, caso não tenha parâmetros o input deve vir da linha de comandos.

	./main.out [caminho_para_fonte]

# TODO
[ ] Apresentação;
[ ] Documentação;
[ ] Fonte 1 e 2;