#include <stdio.h>
#include <stdlib.h> // Para a função abs()

// Definições de tamanho e valores
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5 // Tamanho fixo 5x5 para as matrizes de habilidade

// Códigos de exibição no tabuleiro
#define AGUA ' ' // 0 (originalmente)
#define NAVIO 'N' // 3 (originalmente)
#define AREA_AFETADA 'X' // 5 (originalmente)

// Códigos nas matrizes de habilidade
#define NAO_AFETADO 0
#define AFETADO 1

// --- Função para Inicializar o Tabuleiro ---
void inicializar_tabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
    // Adicionar alguns navios para visualização (valor 'N'/'3')
    tabuleiro[2][2] = NAVIO;
    tabuleiro[2][3] = NAVIO;
    tabuleiro[5][5] = NAVIO;
    tabuleiro[6][5] = NAVIO;
    tabuleiro[7][5] = NAVIO;
}

// --- Funções para Construir as Matrizes de Habilidade ---

// Habilidade Cone: Expansão em forma de triângulo/cone (apontando para baixo)
void construir_cone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // Índice central (ex: 2 para 5x5)

    printf("\nConstruindo Matriz de Habilidade: CONE\n");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            /*
             * Lógica do Cone:
             * Na linha 'i', o cone afeta posições que estão dentro do range [centro - i, centro + i].
             * O abs(j - centro) calcula a distância horizontal até o centro da linha.
             * A habilidade afeta se essa distância for menor ou igual à linha atual 'i'.
             */
            if (abs(j - centro) <= i) {
                habilidade[i][j] = AFETADO;
            } else {
                habilidade[i][j] = NAO_AFETADO;
            }
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

// Habilidade Cruz: Linha horizontal e vertical no centro
void construir_cruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // Índice central

    printf("\nConstruindo Matriz de Habilidade: CRUZ\n");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            /*
             * Lógica da Cruz:
             * Afeta se a posição estiver na linha central (i == centro) OU na coluna central (j == centro).
             */
            if (i == centro || j == centro) {
                habilidade[i][j] = AFETADO;
            } else {
                habilidade[i][j] = NAO_AFETADO;
            }
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

// Habilidade Octaedro/Losango: Distância de Manhattan
void construir_octaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2; // Índice central

    printf("\nConstruindo Matriz de Habilidade: OCTAEDRO (Losango)\n");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            /*
             * Lógica do Losango (Distância de Manhattan):
             * A distância de Manhattan do ponto (i, j) ao centro (centro, centro) é |i - centro| + |j - centro|.
             * Para formar um losango centrado, a área afetada é onde essa distância é menor ou igual ao centro (raio).
             */
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = AFETADO;
            } else {
                habilidade[i][j] = NAO_AFETADO;
            }
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

// --- Função para Sobrepor a Habilidade no Tabuleiro ---
void sobrepor_habilidade(
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
    int origem_linha,
    int origem_coluna
) {
    int centro_habilidade = TAMANHO_HABILIDADE / 2;

    // A iteração vai de 0 a TAMANHO_HABILIDADE - 1 (índices da matriz de habilidade)
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {

            // Se a posição (i, j) na matriz de habilidade é AFETADA
            if (habilidade[i][j] == AFETADO) {

                // Calcular as coordenadas correspondentes no tabuleiro
                // Linha_tabuleiro = Origem_tabuleiro + (Índice_habilidade - Centro_habilidade)
                int tab_i = origem_linha + (i - centro_habilidade);
                int tab_j = origem_coluna + (j - centro_habilidade);

                /*
                 * Condicional de Validação de Limites:
                 * Verifica se a coordenada calculada (tab_i, tab_j) está dentro dos limites [0, TAMANHO_TABULEIRO - 1].
                 */
                if (tab_i >= 0 && tab_i < TAMANHO_TABULEIRO &&
                    tab_j >= 0 && tab_j < TAMANHO_TABULEIRO)
                {
                    // Marca a posição no tabuleiro com o código de área afetada
                    // Verifica se já não é um navio para evitar sobrescrever a 'N'
                    if (tabuleiro[tab_i][tab_j] != NAVIO) {
                        tabuleiro[tab_i][tab_j] = AREA_AFETADA;
                    }
                }
            }
        }
    }
}

// --- Função para Exibir o Tabuleiro ---
void exibir_tabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n--- Tabuleiro de Batalha Naval ---\n");
    
    // Cabeçalho de colunas (0-9)
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Separador
    printf("  +-");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("\n");

    // Conteúdo
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d | ", i); // Índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("|\n");
    }

    // Separador
    printf("  +-");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("\n");
}


// --- Função Principal ---
int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // 1. Inicializa o tabuleiro com água e navios
    inicializar_tabuleiro(tabuleiro);

    // 2. Define os pontos de origem para as habilidades
    int origem_cone_r = 0; // Linha 0
    int origem_cone_c = 4; // Coluna 4

    int origem_cruz_r = 5; // Linha 5
    int origem_cruz_c = 2; // Coluna 2

    int origem_octaedro_r = 7; // Linha 7
    int origem_octaedro_c = 7; // Coluna 7

    // --- CONE (Area 1) ---
    // Cria a matriz de habilidade Cone
    construir_cone(habilidade);
    // Sobrepõe o Cone no tabuleiro, centrado na origem definida
    sobrepor_habilidade(tabuleiro, habilidade, origem_cone_r, origem_cone_c);
    
    // --- CRUZ (Area 2) ---
    // Cria a matriz de habilidade Cruz
    construir_cruz(habilidade);
    // Sobrepõe a Cruz no tabuleiro, centrado na origem definida
    sobrepor_habilidade(tabuleiro, habilidade, origem_cruz_r, origem_cruz_c);

    // --- OCTAEDRO/LOSANGO (Area 3) ---
    // Cria a matriz de habilidade Octaedro
    construir_octaedro(habilidade);
    // Sobrepõe o Octaedro no tabuleiro, centrado na origem definida
    sobrepor_habilidade(tabuleiro, habilidade, origem_octaedro_r, origem_octaedro_c);

    // 3. Exibe o resultado final
    printf("\n--- Legenda: ' ' = Agua | 'N' = Navio | 'X' = Area Afetada ---\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}