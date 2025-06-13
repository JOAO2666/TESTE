#ifndef UI_H
#define UI_H

#include "structs.h"
#include "defines.h"
#include "raylib.h" // For Font, Color, Texture2D, Rectangle, Vector2, bool etc.

// Function declarations
void DesenharSelecaoPersonagem(Personagem personagens[], int selecionado, int inicioX, int inicioY, int larguraArea, int alturaArea, Color corDestaque);
void DesenharInfoPersonagem(Personagem personagem, int x, int y, int largura, int altura, Font fonte);
void DesenharBarraVida(int x, int y, int largura, int altura, int vidaAtual, int vidaMaxima, Color cor, const char *nomeJogador);
void DesenharBarraPoder(int x, int y, int largura, int altura, int poderAtual, int poderMaximo, Color corPersonagem);
void DesenharHUD(EstadoJogo *estado, Font fonte);
void DesenharTelaSelecaoMapa(Mapa mapas[], int mapaAtual, Font fonte);
void DesenharTelaOpcoes(ConfiguracaoJogo *config, int opcaoSelecionada, bool aguardandoTecla, Font fonte);

#endif // UI_H
