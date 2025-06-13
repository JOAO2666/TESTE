#ifndef EFEITOS_H
#define EFEITOS_H

#include "structs.h"
#include "raylib.h" // For Vector2, Color, etc.

// Function declarations for particle effects
void CriarEfeitoImpacto(SistemaParticulas *sistema, Vector2 posicao, Color cor, int numParticulas);
void AtualizarParticulas(SistemaParticulas *sistema, float deltaTime);
void DesenharParticulas(SistemaParticulas *sistema);

#endif // EFEITOS_H
