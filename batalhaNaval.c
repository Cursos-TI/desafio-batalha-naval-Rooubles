#include <stdio.h>

// Tabuleiro inicial (10x10)
int Tabuleiro[10][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

int ataque_cone [3][5] = {
    {0,0,1,0,0},
    {0,1,1,1,0},
    {1,1,1,1,1}
};

int ataque_cruz [3][5] = {
    {0,0,1,0,0},
    {1,1,1,1,1},
    {0,0,1,0,0}
};

int ataque_octaedro [3][5] = {
    {0,0,1,0,0},
    {0,1,1,1,0},
    {0,0,1,0,0}
};

// Função para posicionar o navio no tabuleiro
int posicao(int linha, int coluna, int tamanho, char orientacao, char direcao) {  // posiciona o navio conforme a as definiçoes inputadas pelo usuario

    if (orientacao == 'H' || orientacao == 'h') {  // navio horizontal

        if (coluna + tamanho > 10) return 0;  // verifica o navio está dento do limite do tabuleiro, caso não, retorna 0 (falso)
        for (int i = 0; i < tamanho; i++) {  
            if (Tabuleiro[linha][coluna + i] != 0) return 0;  // verifica sobreposição do navio, retorna 0 (falso) caso exista outro navio já posicionado no local
        }
        for (int i = 0; i < tamanho; i++) { 
            Tabuleiro[linha][coluna + i] = 3;  // posiciona o navio no local solicitado desde que cumpra as condições de sobreposição e limite do tabuleiro
        }
        return 1;

    } else if (orientacao == 'V' || orientacao == 'v') {  // navio vertical

        if (linha + tamanho > 10) return 0;  // verifica o navio está dento do limite do tabuleiro, caso não, retorna 0 (falso)
        for (int i = 0; i < tamanho; i++) {
            if (Tabuleiro[linha + i][coluna] != 0) return 0;  // verifica sobreposição do navio, retorna 0 (falso) caso exista outro navio já posicionado no local
        }
        for (int i = 0; i < tamanho; i++) {
            Tabuleiro[linha + i][coluna] = 3;  // posiciona o navio no local solicitado desde que cumpra as condições de sobreposição e limite do tabuleiro
        }
        return 1;

    } else if (orientacao == 'D' || orientacao == 'd') {  // navio vertical

        if (direcao == 'C' || direcao == 'c') { // Diagonal para cima

            if (coluna + tamanho > 10 || linha - (tamanho - 1) < 0) return 0;  // verifica o navio está dento do limite do tabuleiro, caso não, retorna 0 (falso)
            for (int i = 0; i < tamanho; i++) {
                if (Tabuleiro[linha - i][coluna + i] != 0) return 0;  // verifica sobreposição do navio, retorna 0 (falso) caso exista outro navio já posicionado no local
            }
            for (int i = 0; i < tamanho; i++) {
                Tabuleiro[linha - i][coluna + i] = 3;  // posiciona o navio no local solicitado desde que cumpra as condições de sobreposição e limite do tabuleiro
            }
            return 1;

        } else if (direcao == 'B' || direcao == 'b') {  // Diagonal para cima
            
            if (coluna + tamanho > 10 || linha + tamanho > 10) return 0;  // verifica o navio está dento do limite do tabuleiro, caso não, retorna 0 (falso)
            for (int i = 0; i < tamanho; i++) {
                if (Tabuleiro[linha + i][coluna + i] != 0) return 0;  // verifica sobreposição do navio, retorna 0 (falso) caso exista outro navio já posicionado no local
            }
            for (int i = 0; i < tamanho; i++) {
                Tabuleiro[linha + i][coluna + i] = 3;  // posiciona o navio no local solicitado desde que cumpra as condições de sobreposição e limite do tabuleiro
            }
            return 1;  // retorna 1 (verdadeiro) quando o navio for posicionado com sucesso
        }
    }
    return 0; // retorna 0 (falso) quando o posicionamento do navio falhar
}

// Função para exibir o tabuleiro
void exibir_tabuleiro() {  // sempre que essa funcao for chamada, exibe o tabuleiro com os valores atuais
    printf ("\n");
    char letra[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };  // vetor char com o cabeçalho do tabuleiro
    
    printf("\t");
    for (int i = 0; i < 10; i++) {
        printf("%c\t", letra[i]);  // imprime o cabeçalho (A-J)
    }
    printf("\n\n");

    for (int l = 0; l < 10; l++) {  // executa a impressao do tabuleiro - loop externo para as linhas
        printf("%d\t", l + 1);  // imprime a identificaçlão das linhas do tabuleiro (1-10)
        for (int c = 0; c < 10; c++) {  // executa a impressao do tabuleiro - loop interno para as colunas
            printf("%d\t", Tabuleiro[l][c]);  // imprime o valor de cada indice do tabuleiro de acordo os loops aninhados
        }
        printf("\n\n\n");  // quebra de linha para separar as linhas do tabuleiro
    }
}

// Função para posicionar múltiplos navios
void posicionar_navio(int navios) { //sempre que a funçao for chamada ira solicitar ao usuario as coordenadas para posicionar o navio
    if (navios > 0) {  // condição para posicionar o navio de acordo com a quantidade de navios a serem posicionados (definido pelo usuario)

        int linha, coluna, tamanho;
        char colunaChar, orientacao, direcao;

    inicio: // ponto de retorno, caso exista algum impecilho para posicionar o navio na coordenada informada
        printf("Digite a posição que deseja colocar o seu navio:\n");
        printf("Coluna (A-J): ");
        scanf(" %c", &colunaChar);  // solicita ao usuario a coluna que o navio será posicionado
        printf("Linha (1-10): ");
        scanf("%d", &linha);  // solicita ao usuario a linha que o navio será posicionado
        printf("Tamanho do navio: ");
        scanf("%d", &tamanho);  // solicita ao usuario o tamanho do navio (quantas cadas serão ocupadas no tabuleiro)
        printf("Orientação [H/V/D]: ");  
        scanf(" %c", &orientacao);  // solicita ao usuario a orientação (horizontal, vertical ou diagonal) que o navio será posicionado
        if (orientacao == 'D' || orientacao == 'd') {  // caso o navio seja posicionado na diagonal o usuario devera informar a posiçao (para cima ou para baixo)
            printf("Diagonal para cima / Diagonal para baixo [C/B]: ");
            scanf(" %c", &direcao);  // solicita a direção ao usuario
        }

        coluna = colunaChar - 'A';  // converte a coluna indicada pelo usuario em um indice numerico (A-F) para (0-9)
        linha -= 1;  // corrige a linha informada pelo usuario para o indice da matriz (1-10) para (0-9)

        int ok = posicao(linha, coluna, tamanho, orientacao, direcao); // variavel ok verifica o retorno do posicionamento do navio se 0 (falso) ou se 1 (verdadeiro)

        if (ok) {  // se retorno do posicionamento for verdadeiro
            printf("\nNavio posicionado com sucesso!\n\n");  // imprime sucesso no posicionamento
            exibir_tabuleiro(); // chama a funçao exibir tabuleiro
        } else {
            printf("\nErro ao posicionar navio. Verifique a posição e tente novamente.\n\n");  // imprime sucesso no posicionamento
            goto inicio;  // retorna para a solicitação das coordenadas
        }

        posicionar_navio(navios - 1);  // chama a propria funçao pela quantidade navios que o usuario deseja posicionar
    }
}

// Função para resetar o tabuleiro
void reset_tabuleiro() {  // sempre que essa funçao for chamada todos os navios posicionados serao apagados 
    for (int l = 0; l < 10; l++) {
        for (int c = 0; c < 10; c++) {
            Tabuleiro[l][c] = 0;  // define todas as casas to tabuleiro para 0 (agua)
        }
    }
}

// Função principal
int main() {  // funçao principal do programa

    int opcao;
    int navios;
    menu:
    printf( "### BATALHA NAVAL ###\n\n" );
    printf( "1 - Jogar\n" );
    printf( "2 - Posicionar navios\n" );
    printf( "3 - Visualizar tabulairo;\n" );
    printf( "4 - Resetar tabuleiro Jogar\n" );
    printf( "5 - Sair\n" );
    printf( "\nEscolha uma opção: " );
        scanf("%d" , &opcao );  // usuario escolho uma das opções do menu

    switch (opcao)
    {
    case 1:
        exibir_tabuleiro();
        ataque:
        printf( "1 - Ataque simples\n" );
        printf( "2 - Ataque cone\n" );
        printf( "3 - Ataque cruz;\n" );
        printf( "4 - Ataque octardro\n" );
        printf( "\nEscolha uma opção: " );
            scanf("%d" , &opcao ); // usuario escolhe o tipo de ataque de deseja realizar

            int ataque_linha , ataque_coluna ;
            char ataque_coluna_char ;
        
        if (opcao == 1) {  // ataque simples
            printf( "Informe a posição do ataque (coluna e linha - ex: B2): " );
                scanf( " %c %d" , &ataque_coluna_char , &ataque_linha ); // usuario insere a posição do ataque
            ataque_linha -= 1;
            ataque_coluna = ataque_coluna_char - 'A';
                if (Tabuleiro[ataque_linha][ataque_coluna] == 3 ) {  // para o ataque simples é verificado se a posição do ataque possui um navio, se sim sera impresso 5 se não permanece 0.
                    Tabuleiro[ataque_linha][ataque_coluna] = 5;
                }
            exibir_tabuleiro(); // exibe o tabuleiro apos o ataque

            printf( "1 - Acatar novamente\n" );
            printf( "2 - sair\n" );
            printf( "\nEscolha uma opção: " );
                scanf("%d" , &opcao );
            if ( opcao == 1 ) { goto ataque; } else { goto menu; }
        
            
        } else if ( opcao == 2 ) { // ataque especial CONE
            printf( "Informe a posição do ataque (coluna e linha - ex: B2): " );
                scanf( " %c %d" , &ataque_coluna_char , &ataque_linha ); // usuario insere a posição do ataque
            ataque_linha -= 1;
            ataque_coluna = ataque_coluna_char - 'A';

            for (int l = 0; l < 3; l++) {
                for (int c = 0; c < 5; c++) {
                    int linha_tabuleiro = ataque_linha + (l - 1);  // ajusta a indice linha do tabuleiro em relação a matriz de ataque considerando centro da matriz de ataque
                    int coluna_tabuleiro = ataque_coluna + (c - 2);  // ajusta a indice coluna do tabuleiro em relação a matriz de ataque considerando centro da matriz de ataque
                    if ( ataque_cone[l][c] == 1 && Tabuleiro[linha_tabuleiro][coluna_tabuleiro] == 3) {  // veridica a area afetada na matriz de ataque e se possui algum navio posicionado no babuleiro considerando o ponto em que feito o ataque.
                        Tabuleiro[linha_tabuleiro][coluna_tabuleiro] = 5;  // caso algum navio seja atingido sera impresso 5 no local do ataque.
                    }
                }
            }
            exibir_tabuleiro(); // exibe o tabuleiro apos o ataque

            printf( "1 - Acatar novamente\n" );
            printf( "2 - sair\n" );
            printf( "\nEscolha uma opção: " );
            scanf("%d" , &opcao );
            if ( opcao == 1 ) { goto ataque; } else { goto menu; }


        } else if ( opcao == 3 ) { // ataque especial CRUZ
            printf( "Informe a posição do ataque (coluna e linha - ex: B2): " );
            scanf( " %c %d" , &ataque_coluna_char , &ataque_linha ); // usuario insere a posição do ataque
            ataque_linha -= 1;
            ataque_coluna = ataque_coluna_char - 'A';

            for (int l = 0; l < 3; l++) {
                for (int c = 0; c < 5; c++) {
                    int linha_tabuleiro = ataque_linha + (l - 1);
                    int coluna_tabuleiro = ataque_coluna + (c - 2);
                    if ( ataque_cruz[l][c] == 1 && Tabuleiro[linha_tabuleiro][coluna_tabuleiro] == 3) {
                        Tabuleiro[linha_tabuleiro][coluna_tabuleiro] = 5;
                    }
                }
            }
            exibir_tabuleiro(); // exibe o tabuleiro apos o ataque

            printf( "1 - Acatar novamente\n" );
            printf( "2 - sair\n" );
            printf( "\nEscolha uma opção: " );
                scanf("%d" , &opcao );
            if ( opcao == 1 ) { goto ataque; } else { goto menu; }

        } else if ( opcao == 4) {  // ataque especial OCTAEDRO
            printf( "Informe a posição do ataque (coluna e linha - ex: B2): " );
            scanf( " %c %d" , &ataque_coluna_char , &ataque_linha ); // usuario insere a posição do ataque
            ataque_linha -= 1;
            ataque_coluna = ataque_coluna_char - 'A';

            for (int l = 0; l < 3; l++) {
                for (int c = 0; c < 5; c++) {
                    int linha_tabuleiro = ataque_linha + (l - 1);
                    int coluna_tabuleiro = ataque_coluna + (c - 2);
                    if ( ataque_octaedro[l][c] == 1 && Tabuleiro[linha_tabuleiro][coluna_tabuleiro] == 3) {
                        Tabuleiro[linha_tabuleiro][coluna_tabuleiro] = 5;
                    }
                }
            }
            exibir_tabuleiro(); // exibe o tabuleiro apos o ataque

            printf( "1 - Acatar novamente\n" );
            printf( "2 - sair\n" );
            printf( "\nEscolha uma opção: " );
                scanf("%d" , &opcao );
            if ( opcao == 1 ) { goto ataque; } else { goto menu; }
        }

        break;

    case 2: 
        printf("Quantos navios deseja posicionar? ");
        scanf("%d", &navios);  // solicita ao usuario a quantidade de navios que deseja posicionar

        posicionar_navio(navios);  // chama a funçao posicionar navio que sera repedida recursivamente pela quantidade de navios a serem posicionados
        goto menu;
        break;

    case 3:  // exibe o tabuleiro e retorno ao menu inicial
        exibir_tabuleiro();
        goto menu;
        break;
        
    case 4:  // reseta o tabuleiro e retorno a menu inicial
        reset_tabuleiro();
        printf( "\nTabuleiro resetado com sucesso!\n" );
        goto menu;
        break;

    case 5:  // enecerra programa
    printf( "\n# # # GAME OVER # # #\n" );  
        break;
    
    default:  // retorna ao  menu inicial caso o usuario escolha uma opção invalida
    printf( "\nOpçao invalida. Tente novamente: " );
        goto menu;  
        break;
    }

    return 0;
}