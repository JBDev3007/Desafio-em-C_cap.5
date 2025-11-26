#include <stdio.h>
#include <stdbool.h>

// Definição das constantes para o tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Protótipos das funções
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool validarPosicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int tamanho, int direcao);
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int tamanho, int direcao);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Constantes para as direções dos navios
// 0: Horizontal (Coluna aumenta)
// 1: Vertical (Linha aumenta)
// 2: Diagonal Principal (Linha e Coluna aumentam)
// 3: Diagonal Secundária (Linha aumenta, Coluna diminui)
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL_PRINCIPAL 2
#define DIAGONAL_SECUNDARIA 3

// --- Função Principal ---
int main() {
    // 1. Criação do Tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa todas as posições com água (0)
    inicializarTabuleiro(tabuleiro);

    // --- Definição das Posições dos Navios ---
    // Os navios têm tamanho fixo de 3

    // Navio 1: Ortogonal (Vertical), Início (1, 3)
    int n1_lin = 1, n1_col = 3, n1_dir = VERTICAL;

    // Navio 2: Ortogonal (Horizontal), Início (6, 5)
    int n2_lin = 6, n2_col = 5, n2_dir = HORIZONTAL;

    // Navio 3: Diagonal Principal, Início (0, 0)
    int n3_lin = 0, n3_col = 0, n3_dir = DIAGONAL_PRINCIPAL;

    // Navio 4: Diagonal Secundária, Início (3, 6)
    int n4_lin = 3, n4_col = 6, n4_dir = DIAGONAL_SECUNDARIA;

    // --- Posicionamento e Validação dos Navios ---

    // Posicionar Navio 1 (Vertical)
    if (validarPosicao(tabuleiro, n1_lin, n1_col, TAMANHO_NAVIO, n1_dir)) {
        posicionarNavio(tabuleiro, n1_lin, n1_col, TAMANHO_NAVIO, n1_dir);
    } else {
        printf("Erro: Navio 1 invalido (limites ou sobreposicao).\n");
    }

    // Posicionar Navio 2 (Horizontal)
    if (validarPosicao(tabuleiro, n2_lin, n2_col, TAMANHO_NAVIO, n2_dir)) {
        posicionarNavio(tabuleiro, n2_lin, n2_col, TAMANHO_NAVIO, n2_dir);
    } else {
        printf("Erro: Navio 2 invalido (limites ou sobreposicao).\n");
    }

    // Posicionar Navio 3 (Diagonal Principal)
    if (validarPosicao(tabuleiro, n3_lin, n3_col, TAMANHO_NAVIO, n3_dir)) {
        posicionarNavio(tabuleiro, n3_lin, n3_col, TAMANHO_NAVIO, n3_dir);
    } else {
        printf("Erro: Navio 3 invalido (limites ou sobreposicao).\n");
    }

    // Posicionar Navio 4 (Diagonal Secundária)
    if (validarPosicao(tabuleiro, n4_lin, n4_col, TAMANHO_NAVIO, n4_dir)) {
        posicionarNavio(tabuleiro, n4_lin, n4_col, TAMANHO_NAVIO, n4_dir);
    } else {
        printf("Erro: Navio 4 invalido (limites ou sobreposicao).\n");
    }

    // --- Exibir o Tabuleiro Completo ---
    printf("\n--- Tabuleiro de Batalha Naval (10x10) ---\n");
    printf("0 = Agua, 3 = Navio\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

// --- Implementação das Funções ---

// Inicializa o tabuleiro com o valor AGUA (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Valida se as posições do navio estão dentro dos limites e não há sobreposição
bool validarPosicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int tamanho, int direcao) {
    int linha, coluna;

    for (int i = 0; i < tamanho; i++) {
        // Calcula as coordenadas para cada segmento do navio
        switch (direcao) {
            case HORIZONTAL: // Coluna aumenta
                linha = linhaInicial;
                coluna = colunaInicial + i;
                break;
            case VERTICAL: // Linha aumenta
                linha = linhaInicial + i;
                coluna = colunaInicial;
                break;
            case DIAGONAL_PRINCIPAL: // Linha e Coluna aumentam
                linha = linhaInicial + i;
                coluna = colunaInicial + i;
                break;
            case DIAGONAL_SECUNDARIA: // Linha aumenta, Coluna diminui
                linha = linhaInicial + i;
                coluna = colunaInicial - i;
                break;
            default:
                return false; // Direção inválida
        }

        // 1. Validação de Limites
        if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
            return false;
        }

        // 2. Validação de Sobreposição
        if (tabuleiro[linha][coluna] == NAVIO) {
            return false;
        }
    }

    // A posição é válida (dentro dos limites e sem sobreposição)
    return true;
}

// Posiciona o navio no tabuleiro, marcando as posições com NAVIO (3)
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, int tamanho, int direcao) {
    int linha, coluna;

    for (int i = 0; i < tamanho; i++) {
        // Calcula as coordenadas (lógica idêntica à de validação)
        switch (direcao) {
            case HORIZONTAL:
                linha = linhaInicial;
                coluna = colunaInicial + i;
                break;
            case VERTICAL:
                linha = linhaInicial + i;
                coluna = colunaInicial;
                break;
            case DIAGONAL_PRINCIPAL:
                linha = linhaInicial + i;
                coluna = colunaInicial + i;
                break;
            case DIAGONAL_SECUNDARIA:
                linha = linhaInicial + i;
                coluna = colunaInicial - i;
                break;
            default:
                return; // Não deve acontecer se a validação for correta
        }
        
        // Marca a posição com o valor do navio
        tabuleiro[linha][coluna] = NAVIO;
    }
}

// Exibe o tabuleiro 10x10 no console com alinhamento
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Exibe o cabeçalho das colunas (0 a 9)
    printf("   "); // Espaço para o cabeçalho das linhas
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");

    // Exibe uma linha separadora
    printf("  +---------------------\n");

    // Exibe as linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Exibe o índice da linha
        printf("%d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Utiliza printf com espaço para alinhar os números
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}