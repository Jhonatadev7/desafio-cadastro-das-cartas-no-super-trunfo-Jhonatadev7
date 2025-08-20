#include <stdio.h>
#include <string.h>

// Estrutura da Carta
struct Carta {
    char estado[30];
    char codigo[4];
    char cidade[30];
    unsigned long int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
};

// Função que retorna o valor de um atributo específico
float obterAtributo(struct Carta carta, int opcao) {
    switch (opcao) {
        case 1: return (float)carta.populacao;
        case 2: return carta.area;
        case 3: return carta.pib;
        case 4: return (float)carta.pontos_turisticos;
        case 5: return carta.densidade_populacional; 
        default: return 0.0f;
    }
}

// Função que retorna o nome de um atributo (string)
char* nomeAtributo(int opcao) {
    switch (opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

int main() {
    struct Carta carta1, carta2;

    // ================= CADASTRO CARTA 1 =================
    printf("=== Cadastro da Carta 1 ===\n");
    printf("Estado: ");
    scanf(" %[^\n]", carta1.estado);
    printf("Código da carta (ex: A01): ");
    scanf(" %3s", carta1.codigo);
    printf("Cidade: ");
    scanf(" %[^\n]", carta1.cidade);
    printf("População: ");
    scanf("%lu", &carta1.populacao);
    printf("Área em km²: ");
    scanf("%f", &carta1.area);
    printf("PIB (em bilhões): ");
    scanf("%f", &carta1.pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &carta1.pontos_turisticos);

    // Cálculos derivados da Carta 1
    carta1.densidade_populacional = (carta1.area != 0.0f) ? (float)carta1.populacao / carta1.area : 0.0f;
    carta1.pib_per_capita = (carta1.populacao != 0UL) ? (carta1.pib * 1e9f) / (float)carta1.populacao : 0.0f;

    // ================= CADASTRO CARTA 2 =================
    printf("\n=== Cadastro da Carta 2 ===\n");
    printf("Estado: ");
    scanf(" %[^\n]", carta2.estado);
    printf("Código da carta (ex: B02): ");
    scanf(" %3s", carta2.codigo);
    printf("Cidade: ");
    scanf(" %[^\n]", carta2.cidade);
    printf("População: ");
    scanf("%lu", &carta2.populacao);
    printf("Área em km²: ");
    scanf("%f", &carta2.area);
    printf("PIB (em bilhões): ");
    scanf("%f", &carta2.pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &carta2.pontos_turisticos);

    // Cálculos derivados da Carta 2
    carta2.densidade_populacional = (carta2.area != 0.0f) ? (float)carta2.populacao / carta2.area : 0.0f;
    carta2.pib_per_capita = (carta2.populacao != 0UL) ? (carta2.pib * 1e9f) / (float)carta2.populacao : 0.0f;

    // ================= MENU DE ATRIBUTOS =================
    int opcao1, opcao2;
    printf("\n=== MENU DE COMPARAÇÃO ===\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Demográfica\n");
    printf("Escolha o PRIMEIRO atributo: ");
    scanf("%d", &opcao1);

    // Segundo menu dinâmico (não mostra o já escolhido)
    printf("\nEscolha o SEGUNDO atributo (diferente do primeiro):\n");
    for (int i = 1; i <= 5; i++) {
        if (i != opcao1) {
            printf("%d - %s\n", i, nomeAtributo(i));
        }
    }
    scanf("%d", &opcao2);

    if (opcao1 == opcao2) {
        printf("Erro: não é permitido escolher o mesmo atributo duas vezes!\n");
        return 0;
    }

    // ================= COMPARAÇÕES =================
    float valor1_c1 = obterAtributo(carta1, opcao1);
    float valor1_c2 = obterAtributo(carta2, opcao1);
    float valor2_c1 = obterAtributo(carta1, opcao2);
    float valor2_c2 = obterAtributo(carta2, opcao2);

    printf("\n=== RESULTADO DA COMPARAÇÃO ===\n");
    printf("Carta 1: %s | Carta 2: %s\n", carta1.cidade, carta2.cidade);

    // --- Comparação atributo 1 ---
    printf("\nAtributo 1: %s\n", nomeAtributo(opcao1));
    printf("%s: %.2f | %s: %.2f\n", carta1.cidade, valor1_c1, carta2.cidade, valor1_c2);

    // Regra especial: Densidade Demográfica (menor vence)
    int resultado1 = (opcao1 == 5) ?
                     (valor1_c1 < valor1_c2 ? 1 : (valor1_c2 < valor1_c1 ? 2 : 0)) :
                     (valor1_c1 > valor1_c2 ? 1 : (valor1_c2 > valor1_c1 ? 2 : 0));

    // --- Comparação atributo 2 ---
    printf("\nAtributo 2: %s\n", nomeAtributo(opcao2));
    printf("%s: %.2f | %s: %.2f\n", carta1.cidade, valor2_c1, carta2.cidade, valor2_c2);

    int resultado2 = (opcao2 == 5) ?
                     (valor2_c1 < valor2_c2 ? 1 : (valor2_c2 < valor2_c1 ? 2 : 0)) :
                     (valor2_c1 > valor2_c2 ? 1 : (valor2_c2 > valor2_c1 ? 2 : 0));

    // --- Soma dos atributos ---
    float soma1 = valor1_c1 + valor2_c1;
    float soma2 = valor1_c2 + valor2_c2;

    printf("\nSoma dos atributos:\n");
    printf("%s: %.2f | %s: %.2f\n", carta1.cidade, soma1, carta2.cidade, soma2);

    // --- Resultado Final ---
    if (soma1 > soma2) {
        printf("\nVENCEDOR FINAL: %s\n", carta1.cidade);
    } else if (soma2 > soma1) {
        printf("\nVENCEDOR FINAL: %s\n", carta2.cidade);
    } else {
        printf("\nEMPATE!\n");
    }

    return 0;
}
