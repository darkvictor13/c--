# c--
Um reduzido analisador léxico de um subconjunto da linguagem procedural C.

## Integrantes:
    - Victor Emanuel Almeida;
    - Marco Aurélio Guerra Pedroso.

## A linguagem c--:

### Descrição da linguagem
O objetivo da linguagem C-- é implementar um subconjunto da linguagem procedural C, para isso recriando algumas das expressões regulares dos tokens utilizados por Dennis Ritchie. Tudo isso com o objetivo de aprimorar os nossos conhecimentos a respeito da criação de analisadores léxicos.

### Expressões regulares dos tokens reconhecidos
- comando para o preprocessador: "#"(.*)
- palavras reservadas: "if"|"else"|"const"|"for"|"while"|"struct"
- tipos de dados: "int"|"float"|"double"|"char"
- atribuição: ("+"|"-"|"*"|"/"|"%"|"<<"|">>"|"&"|"|"|"^")?"="
- operador aritmético: "+""+"?|"-""-"?|"/"|"*"|"sizeof"|"["{INTEGER_LITERAL}"]"
- operador relacional: "&&"|"||"|"!"|("="|"!")"="|("<"|">")"="?
- fim de expressão: ;
- início de bloco: "{"
- fim de bloco: "}"
- abre parenteses: "("
- fecha parenteses: ")"
- inteiro literal: {DIGIT}+
- float literal: {INTEGER_LITERAL}"."{INTEGER_LITERAL}
- string literal: \\"[^\\\\n\\"]+
- char literal: \\'\\\\?.\\'
- identificador: ({LETTER})({ALPHA_NUM}|_)*

### Descrição da gramática
-

A descrição das expressões regulares supracitadas encontra-se no arquivo fonte "cmm.lex" das linhas 76-114

### Identificando erros
Uma vez definidos os tokens a serem identificados, foram definidas estratégias diferentes para reconhecer erros léxicos comuns, tais como:
- Qualquer caractere não reconhecido por nenhuma expressão regular é lido descartado e gerado o erro;
- Quando lidos os caracteres "(" ou "{" suas respectivas variáveis globais contadoras são incrementadas, e decrementadas quando encontrado ")" ou "}". Sendo assim caso no final do programa qualquer valor seja diferente de 0 houve erros.
- Quando lidos caracteres iniciais de char ou string literal, utiliza-se a estratégia de start conditions, ver seção 11 da referência "Start conditions", que possibilita tomar determinado caminho de leitura tendo em vista entradas diferentes.

## Estrutura do projeto
```
├── build
│   ├── main.out
│   ├── Makefile
│   ├── setup_arch.sh
│   └── setup_ubuntu.sh
├── input_files
│   ├── teste_falha.c
│   └── teste_sucesso.c
├── README.md
└── src
    ├── cmm.lex
    ├── headers
    │   ├── log_type.h
    │   ├── token_definitions.h
    │   └── user_config.h
    ├── log_info
    │   ├── logging.c
    │   └── logging.h
    ├── main.c
    └── utils
        ├── user_input.c
        ├── user_input.h
        ├── utils.c
        └── utils.h
```

Onde:
- input_files: Pasta contendo exemplos de arquivos que contém ou não erros léxicos;
- src: Pasta contendo todos os códigos fonte do projeto, sendo escritos diretamente em C, ou gerados automaticamente pelo flex.
- cmm.lex: Arquivo de especificações da linguagem c--, escrito em lex;
- main.c: Arquivo gerado pelo flex;
- main.out: Arquivo resultado final da compilação;

## Compilando e executando
### Compilando

Para realizar o processo de compilação do projeto primeiro é necessário obter os pacotes flex e make dos repositórios oficiais para isso basta entrar na pasta build:

    cd build/

E executar:

	./setup_arch.sh

ou caso esteja no ubuntu ou outro derivado do debian:

	./setup_ubuntu.sh

Uma vez com make e flex instalado basta iniciar o processo de compilação rodando o comando:

	make

### Executando
Tendo gerado o executável "main.out" dentro da pasta build, basta executá-lo podendo passar um único argumento adicional sendo esse o caminho relativo para um arquivo texto o qual será tratado como o fonte a ser analisado, caso não tenha parâmetros o input deve vir da linha de comandos.

	./main.out [caminho_para_fonte]

## Referências
- https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html
