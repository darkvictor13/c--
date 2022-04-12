# c--
Um reduzido analisador léxico e sintático de um subconjunto da linguagem procedural C.

## Integrantes:
    - Victor Emanuel Almeida;
    - Marco Aurélio Guerra Pedroso.

## Softwares utilizados
- bison 3.8.2 encontrado na pasta build
- flex 2.6.4 encontrado na pasta build
- make 4.3 encontrado na pasta build

## A linguagem c--:

### Descrição da linguagem
O objetivo da linguagem C-- é implementar um subconjunto da linguagem procedural C, para isso recriando algumas das expressões regulares dos tokens utilizados por Dennis Ritchie. Tudo isso com o objetivo de aprimorar os nossos conhecimentos a respeito da criação de compiladores.

### Expressões regulares dos tokens reconhecidos
- comando para o preprocessador: "#"(.*)
- palavra reservada if: "if"
- palavra reservada else: "else"
- palavra reservada for: "for"
- palavra reservada while: "while"
- palavra reservada return: "return"
- palavra reservada struct: "struct"
- palavra reservada const: "const"
- tipo de dados inteiro: "u"?"int"(("8"|"16"|"32"|"64")"_t")?
- tipo de dados ponto flutuante: "float"|"double"
- tipo de dados caractere: "char"
- tipo de dados void: "void"
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

A descrição das expressões regulares supracitadas encontra-se no arquivo fonte "lexico.lex" das linhas 63-110

### Descrição da gramática
\<programa\> ::= λ
    | TOKEN_PREPROCESSOR_COMMAND \<programa\> 
    | \<definicao\> \<programa\> 

\<data_type\> ::= TOKEN_DATA_TYPE_INT
    | TOKEN_DATA_TYPE_FLOAT
    | TOKEN_DATA_TYPE_CHAR
    | TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_INT
    | TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_FLOAT
    | TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_CHAR
    | TOKEN_DATA_TYPE_VOID

\<keyword\> ::= TOKEN_KEYWORD_IF
	| TOKEN_KEYWORD_ELSE
	| TOKEN_KEYWORD_CONST
	| TOKEN_KEYWORD_FOR
	| TOKEN_KEYWORD_WHILE
	| TOKEN_KEYWORD_RETURN
	| TOKEN_KEYWORD_STRUCT

\<segure_token\> ::= \<keyword\>
    | \<data_type\>
    | TOKEN_END_EXP

\<literal\> ::= TOKEN_INTEGER_LITERAL
    | TOKEN_FLOAT_LITERAL
    | TOKEN_CHAR_LITERAL
    | TOKEN_STRING_LITERAL

\<definition\> ::= \<data_type\> TOKEN_ID \<definition_variable_function\>

\<definition_variable_function\> ::= \<variable\> | \<function\>

\<complete_variable\> ::= \<data_type\> TOKEN_ID \<variable\>

\<variable\> ::= TOKEN_ASSIGNMENT \<literal\> TOKEN_END_EXP
    | TOKEN_ARITHMETIC_OPERATOR TOKEN_END_EXP
    | TOKEN_END_EXP

\<function\> ::=
    TOKEN_PARENTESEIS_BEGIN TOKEN_PARENTESEIS_END TOKEN_END_EXP
    | TOKEN_PARENTESEIS_BEGIN TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN \<exp\> TOKEN_BLOCK_END
    | \<error\> segure_token

\<exp\> ::= λ
    | \<complete_variable\> \<exp\>
    | \<atribuition\> \<exp\>
    | \<ifel\> \<exp\>
    | \<for\> \<exp\>
    | \<while\> \<exp\>

\<for\> ::=
    TOKEN_KEYWORD_FOR TOKEN_PARENTESEIS_BEGIN \<atribuition\> TOKEN_END_EXP \<conditional\> TOKEN_END_EXP \<math_expression\> TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN \<exp\> TOKEN_BLOCK_END
    | TOKEN_KEYWORD_FOR TOKEN_PARENTESEIS_BEGIN complete_variable TOKEN_END_EXP \<conditional\> TOKEN_END_EXP \<math_expression\> TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN \<exp\> TOKEN_BLOCK_END
    | \<error\> segure_token

\<while\> ::=
    TOKEN_KEYWORD_WHILE TOKEN_PARENTESEIS_BEGIN \<conditional\> TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN \<exp\> TOKEN_BLOCK_END
    | \<error\> segure_token

\<atribuition\> ::= TOKEN_ID TOKEN_ASSIGNMENT \<math_expression\> TOKEN_END_EXP

\<value\> ::= TOKEN_ID
    | TOKEN_INTEGER_LITERAL
    | TOKEN_FLOAT_LITERAL

\<math_expression\> ::= λ | \<value\>
    | TOKEN_PARENTESEIS_BEGIN \<math_expression\> TOKEN_PARENTESEIS_END \<math_expression\>
    | \<math_expression\> TOKEN_ARITHMETIC_OPERATOR \<math_expression\>

\<ifel\> ::=
    TOKEN_KEYWORD_IF TOKEN_PARENTESEIS_BEGIN \<conditional\> TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN \<exp\> TOKEN_BLOCK_END
    | TOKEN_KEYWORD_IF TOKEN_PARENTESEIS_BEGIN \<conditional\> TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN \<exp\> TOKEN_BLOCK_END TOKEN_KEYWORD_ELSE TOKEN_BLOCK_BEGIN \<exp\> TOKEN_BLOCK_END
    | \<error\> segure_token

\<conditional\> ::= \<value\> | \<value\> TOKEN_RELATIONAL_OPERATOR \<value\>

### Identificando erros
Uma vez definidos os tokens a serem identificados, foram definidas estratégias diferentes para reconhecer erros léxicos comuns, tais como:
- Qualquer caractere não reconhecido por nenhuma expressão regular é lido descartado e gerado o erro;
- Quando lidos os caracteres "(" ou "{" suas respectivas variáveis globais contadoras são incrementadas, e decrementadas quando encontrado ")" ou "}". Sendo assim caso no final do programa qualquer valor seja diferente de 0 houve erros.
- Quando lidos caracteres iniciais de char ou string literal, utiliza-se a estratégia de start conditions, ver seção 11 da referência "Start conditions", que possibilita tomar determinado caminho de leitura tendo em vista entradas diferentes.

Para tratamento de erros sintáticos excluí-se todos os tokens até que se encontre uma palavra chave ou um tipo de dados ou um ";".

## Funcionamento do software
Fluxograma da execução do software:
![Fluxograma](presentation/images/fluxo.png)

## Árvore de derivação
```
programa
programa
definition
    data type
    variable
            assignment
            literal
programa
definition
    data type
    function
programa
definition
    data type
    function
        if
            data type
                assignment
                literal
        else
            data type
                assignment
                literal
        data type
            assignment
            literal
programa
definition
    data type
    function
        data type
        data type
            assignment
            literal
        data type
            assignment
            literal
        data type
            assignment
            literal
        data type
            assignment
            literal
        if
            assignment
            assignment
        else
            assignment
```

## Estrutura do projeto
```
.
├── build
│   ├── arvores_fonte1.txt
│   ├── fonte1.txt
│   ├── fonte2.txt
│   ├── fonte3.txt
│   ├── main.out
│   ├── Makefile
│   ├── setup_arch.sh
│   └── setup_ubuntu.sh
├── feito.txt
├── presentation
│   ├── fluxo.drawio
│   ├── images
│   │   ├── alerta.png
│   │   ├── burrito.png
│   │   ├── eletricidade.png
│   │   ├── fluxo.png
│   │   ├── perigo.png
│   │   ├── pizza.png
│   │   └── rolo.png
│   ├── p1
│   │   ├── main.nav
│   │   ├── main.pdf
│   │   ├── main.snm
│   │   ├── main.tex
│   │   └── main.vrb
│   └── p2
│       ├── main.nav
│       ├── main.pdf
│       ├── main.snm
│       ├── main.tex
│       └── main.vrb
├── README.md
└── src
    ├── headers
    │   ├── log_type.h
    │   ├── token_definitions.h
    │   └── user_config.h
    ├── lexico.c
    ├── lexico.lex
    ├── log_info
    │   ├── logging.c
    │   └── logging.h
    ├── sintatico.tab.c
    ├── sintatico.tab.h
    ├── sintatico.y
    ├── tree
    │   ├── tree.c
    │   └── tree.h
    └── utils
        ├── user_input.c
        ├── user_input.h
        ├── utils.c
        └── utils.h
```

Onde:
- input_files: Pasta contendo exemplos de arquivos que contém ou não erros léxicos;
- src: Pasta contendo todos os códigos fonte do projeto, sendo escritos diretamente em C, ou gerados automaticamente pelo flex.
- lexico.lex: Arquivo de especificações da linguagem c--, escrito em lex;
- sintatico.y: Arquivo de entrada para geração do parser escrito em bison
- sintatico.tab.h: Definições do parser
- sintatico.tab.c: Implementação do parser
- lexico.c: Arquivo gerado pelo flex;
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
- https://www.gnu.org/software/bison/manual/html_node/index.html
