# c--
Um reduzido analisador léxico de um subconjunto da linguagem C.

## Integrantes:
    - Victor Emanuel Almeida;
    - Marco Aurélio Guerra Pedroso.

## A linguagem c--:

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
