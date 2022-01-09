# c--
Um reduzido analisador léxico de um subconjunto da linguagem C.

## Integrantes:
    - Victor Emanuel Almeida;
    - Marco Aurélio Guerra Pedroso.

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

Onde cmm.lex é o arquivo de especificações da linguagem c--, main.c é o arquivo gerado pelo flex e main.out o resultado final da compilação.

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