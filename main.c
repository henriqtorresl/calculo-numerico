#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const int TAM_MAX = 100;            // tamanho máximo dos vetores x e y
const int GRAU_POLINOMIO = 2;       

typedef struct Dados {
    double *x;          // vetor para os valores de x
    double *y;          // vetor para os valores de y
} Dados;

void lerDados(FILE *arquivo, Dados *dados) {
    printf("Valores: \n\n");
    printf("\tX\tY\n");

    int i = 0;
    while (!feof(arquivo)) {
        fscanf(arquivo, "%lf %lf", &dados->x[i], &dados->y[i]);

        printf("\t%.2lf\t%.2lf\n", dados->x[i], dados->y[i]);
        i++;
    }

    fclose(arquivo);

    printf("\n");
}

void plotarGrafico(char *filename, Dados dados, double *coeficientes, char *title, char *outputFilename) {
    FILE *scriptFile = fopen(filename, "w");

    fprintf(scriptFile, "set title \"%s\"\n", title);
    fprintf(scriptFile, "set xlabel \"X\"\n");
    fprintf(scriptFile, "set ylabel \"Y\"\n");
    fprintf(scriptFile, "plot '-' with points title 'Dados', ");

    for (int i = 0; i < TAM_MAX; ++i) {
        if (dados.x[i] != 0 || dados.y[i] != 0) {
            fprintf(scriptFile, "%f * x + %f title '', ", coeficientes[1], coeficientes[0]);
        }
    }

    fprintf(scriptFile, "\n");

    for (int i = 0; i < TAM_MAX; ++i) {
        if (dados.x[i] != 0 || dados.y[i] != 0) {
            fprintf(scriptFile, "%.5f %.5f\n", dados.x[i], dados.y[i]);
        }
    }

    fclose(scriptFile);

    char gnuplotCmd[256];
    snprintf(gnuplotCmd, sizeof(gnuplotCmd), "gnuplot -p -e \"load '%s'\"", filename);
    system(gnuplotCmd);
}

// Calcular os coeficientes da reta (y = ax + b)
void linear(Dados dados) {
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXSquare = 0.0;
    int n = 0;

    for (int i = 0; i < TAM_MAX; ++i) {
        if (dados.x[i] != 0 || dados.y[i] != 0) {
            sumX += dados.x[i];
            sumY += dados.y[i];
            sumXY += dados.x[i] * dados.y[i];
            sumXSquare += dados.x[i] * dados.x[i];
            n++;
        }
    }

    double a = (n * sumXY - sumX * sumY) / (n * sumXSquare - sumX * sumX);
    double b = (sumY - a * sumX) / n;

    printf("Ajuste linear:\n");
    printf("Coeficientes: a = %.5f, b = %.5f\n", a, b);

    double coeficientes[2] = {a, b};

    plotarGrafico("ajuste_linear_script.gp", dados, coeficientes, "Ajuste Linear", "linear_fit.png");

    printf("\n");
    printf("Função:\n\t y = %.2fx + %.2f", a, b);
    printf("\n");
}

// Calcular os coeficientes do ajuste quadrático (y = ax^2 + bx + c)
void quadratico(Dados dados) {
    double sumX = 0.0, sumY = 0.0, sumXSquare = 0.0, sumXCube = 0.0, sumXQuad = 0.0, sumXY = 0.0;
    int n = 0;

    for (int i = 0; i < TAM_MAX; ++i) {
        if (dados.x[i] != 0 || dados.y[i] != 0) { 
            double x = dados.x[i];
            double xSquare = x * x;

            sumX += x;
            sumY += dados.y[i];
            sumXSquare += xSquare;
            sumXCube += x * xSquare;
            sumXQuad += xSquare * xSquare;
            sumXY += dados.y[i] * x;

            n++;
        }
    }

    double a = (n * sumXQuad - sumXSquare * sumX) / (n * sumXCube - sumXSquare * sumX);
    double b = (sumXY * n - sumX * sumY) / (sumXSquare * n - sumX * sumX);
    double c = (sumY - b * sumX - a * sumXSquare) / n;

    printf("Ajuste quadrático:\n");
    printf("Coeficientes: a = %.5f, b = %.5f, c = %.5f\n", a, b, c);
    
    double coeficientes[3] = {a, b, c};
    
    plotarGrafico("ajuste_quadratico_script.gp", dados, coeficientes, "Ajuste Quadratico", "quadratic_fit.png");

    printf("\n");
    printf("Função:\n\t y = %.2fx^2 + %.2fx + %.2f", a, b, c);
    printf("\n");
}

// Calcular os coeficientes do ajuste exponencial (y = ae^(bx))
void exponencial(Dados dados) {
    double sumX = 0.0, sumY = 0.0, sumXSquare = 0.0, sumXY = 0.0;
    int n = 0;

    for (int i = 0; i < TAM_MAX; ++i) {
        if (dados.x[i] != 0 || dados.y[i] != 0) {
            double x = dados.x[i];
            double y = dados.y[i];

            sumX += x;
            sumY += log(y); 
            sumXSquare += x * x;
            sumXY += x * log(y);

            n++;
        }
    }

    double b = (n * sumXY - sumX * sumY) / (n * sumXSquare - sumX * sumX);
    double a = exp((sumY - b * sumX) / n);

    printf("Ajuste exponencial:\n");
    printf("Coeficientes: a = %.5f, b = %.5f\n", a, b);
    
    double coeficientes[2] = {a, b};
    
    plotarGrafico("exponencial_script.gp", dados, coeficientes, "Ajuste Exponencial", "exponential_fit.png");

    printf("\n");
    printf("Função:\n\t y = %.2fe^(%.2fx)", a, b);
    printf("\n");
}

void polinomial(Dados dados) {
    double somatorias[2 * GRAU_POLINOMIO + 1];
    for (int i = 0; i < 2 * GRAU_POLINOMIO + 1; ++i) {
        somatorias[i] = 0.0;
    }

    int n = 0;

    for (int i = 0; i < TAM_MAX; ++i) {
        if (dados.x[i] != 0 || dados.y[i] != 0) {
            double x = dados.x[i];
            double y = dados.y[i];

            for (int j = 0; j < 2 * GRAU_POLINOMIO + 1; ++j) {
                somatorias[j] += pow(x, j) * y;
            }

            n++;
        }
    }

    // Construir sistema de equações normais
    double sistemaEquacoes[GRAU_POLINOMIO + 1][GRAU_POLINOMIO + 2];

    for (int i = 0; i <= GRAU_POLINOMIO; ++i) {
        for (int j = 0; j <= GRAU_POLINOMIO; ++j) {
            sistemaEquacoes[i][j] = somatorias[i + j];
        }

        sistemaEquacoes[i][GRAU_POLINOMIO + 1] = somatorias[i + GRAU_POLINOMIO + 1];
    }

    // Resolver o sistema de equações
    for (int i = 0; i < GRAU_POLINOMIO + 1; ++i) {
        for (int j = i + 1; j < GRAU_POLINOMIO + 1; ++j) {
            double ratio = sistemaEquacoes[j][i] / sistemaEquacoes[i][i];

            for (int k = 0; k < GRAU_POLINOMIO + 2; ++k) {
                sistemaEquacoes[j][k] -= ratio * sistemaEquacoes[i][k];
            }
        }
    }

    // Calcular os coeficientes do ajuste polinomial
    double coeficientes[GRAU_POLINOMIO + 1];
    for (int i = GRAU_POLINOMIO; i >= 0; --i) {
        coeficientes[i] = sistemaEquacoes[i][GRAU_POLINOMIO + 1];

        for (int j = i + 1; j <= GRAU_POLINOMIO; ++j) {
            coeficientes[i] -= sistemaEquacoes[i][j] * coeficientes[j];
        }

        coeficientes[i] /= sistemaEquacoes[i][i];
    }

    // Imprimir os resultados
    printf("Ajuste polinomial de grau %d:\n", GRAU_POLINOMIO);
    printf("Coefficients: ");
    for (int i = 0; i <= GRAU_POLINOMIO; ++i) {
        printf("a%d = %.5f ", i, coeficientes[i]);
    }
    printf("\n");

    plotarGrafico("polinomial_script.gp", dados, coeficientes, "Ajuste Polinomial", "polynomial_fit.png");
}

int main() {
    FILE *arq;
    Dados dados;
    int tipoAjuste;

    arq = fopen("dados.txt", "r");

    if (arq == NULL) {
        printf("Houve um erro ao ler o arquivo!\n");
        return 0;
    }

    dados.x = (double *)malloc(TAM_MAX * sizeof(double));
    dados.y = (double *)malloc(TAM_MAX * sizeof(double));
    lerDados(arq, &dados);

    printf("Escolha um tipo de ajuste:\n\n \t1 - Linear\n \t2 - Quadrático\n \t3 - Exponencial\n \t4 - Polinomial\n\n");
    scanf("%d", &tipoAjuste);

    switch (tipoAjuste) {
    case 1:
        linear(dados);
        break;
    case 2:
        quadratico(dados);
        break;
    case 3:
        exponencial(dados);
        break;
    case 4:
        polinomial(dados);
        break;

    default:
        printf("Opção inválida!\n");
        break;
    }

    return 0;
}