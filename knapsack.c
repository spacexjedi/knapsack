#include <stdio.h>
#include <stdlib.h>

/*------------------------------*/
/* Problema da Mochila Limitado
* ------------------------------
* Capacidade da Mochila de um viajante é de 400kg e ele precisa escolher os items melhores para serem levados em um acampamento.
*
* */

/* Matriz de Pokemon 
*
*   Ash é um treinador Pokemon e esta ajudando o professor Carvalho, para isso ele precisa enviar o máximo de Pokemons possível para o laboratório do professor.
    A mochila de Ash suporta 400kg.
* */


typedef struct {

    int pokecode; // tipo código de barra  
    char *pokename; // nome do pokemon
    int pokeweight; // o quanto pesa
    int pokevalue; // o nível de poder
    int count; // quantidade do mesmo pokemon levados

} pokemon_t;


/* Matriz de Pokemon -  Peso - Stats - Quantidade */

pokemon_t pokedex[] = {

    {1, "bulbassaur",               6,   45,   3},
    {2, "snubbull",                 8,   60,   2},
    {3, "squirtle",                 9,   44,   2},
    {4, "metapod",                  10,  50,   2},
    {5, "vulpix",                   10,  38,   2},
    {6, "pikachu",                  6,   35,   3},
    {7, "zubat",                    8,   40,   3},
    {8, "meltan",                   8,   46,   3},
    {9, "aggron",                   360, 70,   1},
    {10, "gyarados",                335, 95,   1},
    {11, "turtonator",              212, 60,   1},
    {12, "tyranitar",               203, 100,  1},
    {13, "arcanine",                155, 90,   1},
    {14, "evee",                    7,   55,   2},
    {15, "magikarp",                10,  20,   1},
    {16, "tapu koko",               21,  70,   1},
    {17, "raichu",                  21,  60,   1},
    {18, "dragonair",               17,  61,   1},
    {19, "komala",                  20,  65,   1},
    {20, "ditto",                   4,   48,   2},
    {21, "rockruff",                11,  45,   1},

};


 
int n = sizeof (pokedex) / sizeof (pokemon_t); // apenas escolhendo um n para percorrer toda a estrutura
 
int *knapsack (int w) { // função da mochila recebe o peso da mochila

    int i, j, k, v, *mm, **m, *s; // auxilires para interar no laço
    mm = calloc((n + 1) * (w + 1), sizeof (int));  // malloc e calloc são funções para criar espaço de memória na linguagem C
    m = malloc((n + 1) * sizeof (int *));
    m[0] = mm;
    for (i = 1; i <= n; i++) { // laço para comparar peso e valor de todos com todos
        m[i] = &mm[i * (w + 1)];
        for (j = 0; j <= w; j++) {
            m[i][j] = m[i - 1][j];
            for (k = 1; k <= pokedex[i - 1].count; k++) {
                if (k * pokedex[i - 1].pokeweight > j) {
                    break;
                }
                v = m[i - 1][j - k * pokedex[i - 1].pokeweight] + k * pokedex[i - 1].pokevalue;
                if (v > m[i][j]) {
                    m[i][j] = v;
                }
            }
        }
    }
    s = calloc(n, sizeof (int)); // laço para colocar os items escolhidos no vetor de printar
    for (i = n, j = w; i > 0; i--) {
        int v = m[i][j];
        for (k = 0; v != m[i - 1][j] + k * pokedex[i - 1].pokevalue; k++) {
            s[i - 1]++;
            j -= pokedex[i - 1].pokeweight;
        }
    }
    free(mm); // liberando os ponteiros
    free(m);

    return s;
}
 
int main () {

    int kg; // variável para pegar o peso da mochila 
    printf("knapsack capacity?\n");
    scanf("%d", &kg);

    // auxiliar pra me ajudar a printar
    int i, tc = 0, tw = 0, tv = 0, *s;
    s = knapsack(kg); // chamada da função da mochila


    // Laço da Mochila do Ash

        for (i = 0; i < n; i++) {
        if (s[i]) {
            printf("%d %-22s %5d %5d %5d\n", pokedex[i].pokecode, pokedex[i].pokename, s[i], s[i] * pokedex[i].pokeweight, s[i] * pokedex[i].pokevalue);
            tc += s[i];
            tw += s[i] * pokedex[i].pokeweight;
            tv += s[i] * pokedex[i].pokevalue;
        }
    }
    printf("%-22s %5d %5d %5d\n", "count, weight, value_stats:", tc, tw, tv); // retorna quantidade | peso | nível de stats




    return 0;
}
