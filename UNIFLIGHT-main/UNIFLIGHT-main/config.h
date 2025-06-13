#ifndef CONFIG_H
#define CONFIG_H

#include "structs.h" // For ConfiguracaoJogo
#include "raylib.h"  // For key codes used in ObterNomeTecla, if any are raylib specific beyond simple ints

// Function declarations
void InicializarConfiguracaoPadrao(ConfiguracaoJogo *config);
const char *ObterNomeTecla(int tecla); // Declaration for ObterNomeTecla
void SalvarConfiguracoes(ConfiguracaoJogo *config);
void CarregarConfiguracoes(ConfiguracaoJogo *config);

#endif // CONFIG_H
