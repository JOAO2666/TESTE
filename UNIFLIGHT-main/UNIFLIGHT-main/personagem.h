#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "structs.h"
#include "defines.h"
#include "raylib.h" // For Texture2D, Rectangle, Vector2, bool

// Function declarations
void InicializarPosicaoPersonagem(Personagem *p, float x, float y, bool viradoDireita);
void AtualizarHitbox(Personagem *p);
void AtualizarAlcanceAtaque(Personagem *p);
bool VerificarProximidade(Personagem *atacante, Personagem *alvo);
void MoverPersonagem(Personagem *p, float deltaTime, float limiteEsquerdo, float limiteDireito);
void ProcessarMovimentoPlayer1(Personagem *p, ConfiguracaoJogo *config);
void ProcessarMovimentoPlayer2(Personagem *p, ConfiguracaoJogo *config);
void AtualizarAnimacaoSprite(Personagem *p, float deltaTime);
Texture2D ObterTexturaAtual(Personagem *p);
void IniciarAnimacao(Personagem *p, TipoPose pose, float duracao);
void AtualizarAnimacao(Personagem *p, float deltaTime);
Rectangle ObterSourceRectSprite(Personagem *p);
void VirarPersonagemParaOponente(Personagem *p1, Personagem *p2);
bool ExecutarAtaque(Personagem *atacante, Personagem *alvo, TipoPose tipoAtaque, int dano);
void InicializarPersonagem(Personagem *p, const char *nomePersonagem);

#endif // PERSONAGEM_H
