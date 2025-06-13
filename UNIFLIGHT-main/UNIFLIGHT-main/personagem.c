#include "personagem.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// ===== FUNÇÕES DE MOVIMENTO E SPRITES =====

void InicializarPosicaoPersonagem(Personagem *p, float x, float y, bool viradoDireita)
{
    p->posicao.x = x;
    p->posicao.y = y;
    p->velocidade.x = 0;
    p->velocidade.y = 0;
    p->velocidadeMaxima = 200.0f;
    p->viradoParaDireita = viradoDireita;
    p->podeAtacar = true;
    p->podeSeMovimentar = true;

    // Configurar hitbox
    p->hitbox.width = 80;
    p->hitbox.height = 220; // Aumentado para cobrir mais do personagem
    p->hitbox.x = p->posicao.x - p->hitbox.width / 2;
    p->hitbox.y = p->posicao.y - p->hitbox.height;

    // Configurar alcances de ataque
    p->alcanceSoco = 90.0f;
    p->alcanceChute = 110.0f;
    p->alcancePoder = 150.0f;

    // Sistema de sprites melhorado
    p->frameAtual = 0;
    p->totalFrames = 4;
    p->timerFrame = 0.0f;
    p->duracaoFrame = 0.12f;                    // Animação mais rápida
    p->frameSource = (Rectangle){0, 0, 64, 64}; // Tamanho padrão do frame
}

void AtualizarHitbox(Personagem *p)
{
    p->hitbox.x = p->posicao.x - p->hitbox.width / 2;
    p->hitbox.y = p->posicao.y - p->hitbox.height;
}

void AtualizarAlcanceAtaque(Personagem *p)
{
    float alcance = 0;
    switch (p->poseAtual)
    {
    case POSE_SOCO:
        alcance = p->alcanceSoco;
        break;
    case POSE_CHUTE:
        alcance = p->alcanceChute;
        break;
    case POSE_PODER:
        alcance = p->alcancePoder;
        break;
    default:
        alcance = 0;
        break;
    }

    if (p->viradoParaDireita)
    {
        p->alcanceAtaque.x = p->posicao.x;
        p->alcanceAtaque.y = p->posicao.y - 60;
        p->alcanceAtaque.width = alcance;
        p->alcanceAtaque.height = 80;
    }
    else
    {
        p->alcanceAtaque.x = p->posicao.x - alcance;
        p->alcanceAtaque.y = p->posicao.y - 60;
        p->alcanceAtaque.width = alcance;
        p->alcanceAtaque.height = 80;
    }
}

bool VerificarProximidade(Personagem *atacante, Personagem *alvo)
{
    AtualizarAlcanceAtaque(atacante);
    return CheckCollisionRecs(atacante->alcanceAtaque, alvo->hitbox);
}

void MoverPersonagem(Personagem *p, float deltaTime, float limiteEsquerdo, float limiteDireito)
{
    if (!p->podeSeMovimentar || p->animando)
        return;

    // Aplicar movimento
    p->posicao.x += p->velocidade.x * deltaTime;

    // Verificar limites da arena
    if (p->posicao.x < limiteEsquerdo + p->hitbox.width / 2)
    {
        p->posicao.x = limiteEsquerdo + p->hitbox.width / 2;
        p->velocidade.x = 0;
    }
    if (p->posicao.x > limiteDireito - p->hitbox.width / 2)
    {
        p->posicao.x = limiteDireito - p->hitbox.width / 2;
        p->velocidade.x = 0;
    }

    // Atualizar hitbox
    AtualizarHitbox(p);

    // Determinar direção que está virado
    if (p->velocidade.x > 0)
        p->viradoParaDireita = true;
    else if (p->velocidade.x < 0)
        p->viradoParaDireita = false;
}

void ProcessarMovimentoPlayer1(Personagem *p, ConfiguracaoJogo *config)
{
    if (!p->podeSeMovimentar || p->animando)
        return;

    p->velocidade.x = 0;
    bool movendo = false;

    // Movimento mais responsivo estilo Street Fighter
    if (IsKeyDown(config->teclaEsquerdaP1))
    {
        p->velocidade.x = -p->velocidadeMaxima;
        movendo = true;
    }
    else if (IsKeyDown(config->teclaDireitaP1))
    {
        p->velocidade.x = p->velocidadeMaxima;
        movendo = true;
    }

    // Atualizar pose baseada no movimento
    if (movendo && p->poseAtual == POSE_IDLE)
    {
        p->poseAtual = POSE_WALK;
    }
    else if (!movendo && p->poseAtual == POSE_WALK && !p->animando)
    {
        p->poseAtual = POSE_IDLE;
    }
}

void ProcessarMovimentoPlayer2(Personagem *p, ConfiguracaoJogo *config)
{
    if (!p->podeSeMovimentar || p->animando)
        return;

    p->velocidade.x = 0;
    bool movendo = false;

    // Movimento mais responsivo estilo Street Fighter
    if (IsKeyDown(config->teclaEsquerdaP2))
    {
        p->velocidade.x = -p->velocidadeMaxima;
        movendo = true;
    }
    else if (IsKeyDown(config->teclaDireitaP2))
    {
        p->velocidade.x = p->velocidadeMaxima;
        movendo = true;
    }

    // Atualizar pose baseada no movimento
    if (movendo && p->poseAtual == POSE_IDLE)
    {
        p->poseAtual = POSE_WALK;
    }
    else if (!movendo && p->poseAtual == POSE_WALK && !p->animando)
    {
        p->poseAtual = POSE_IDLE;
    }
}

void AtualizarAnimacaoSprite(Personagem *p, float deltaTime)
{
    // Atualizar timer do frame
    p->timerFrame += deltaTime;

    if (p->timerFrame >= p->duracaoFrame)
    {
        p->timerFrame = 0.0f;
        p->frameAtual++;

        // Configurar frames por pose com animações mais suaves
        int maxFrames = 1;
        switch (p->poseAtual)
        {
        case POSE_IDLE:
            maxFrames = 4; // Respiração suave
            p->duracaoFrame = 0.25f;
            break;
        case POSE_WALK:
            maxFrames = 6; // Caminhada fluida
            p->duracaoFrame = 0.15f;
            break;
        case POSE_SOCO:
            maxFrames = 4; // Soco rápido
            p->duracaoFrame = 0.08f;
            break;
        case POSE_CHUTE:
            maxFrames = 5; // Chute com preparação
            p->duracaoFrame = 0.1f;
            break;
        case POSE_PODER:
            maxFrames = 8; // Poder especial elaborado
            p->duracaoFrame = 0.12f;
            break;
        case POSE_DANO:
            maxFrames = 3; // Reação ao dano
            p->duracaoFrame = 0.15f;
            break;
        case POSE_DEFESA:
            maxFrames = 2; // Posição defensiva
            p->duracaoFrame = 0.2f;
            break;
        }

        if (p->frameAtual >= maxFrames)
        {
            p->frameAtual = 0;

            // Se é uma animação de ataque, voltar ao idle
            if (p->animando && (p->poseAtual == POSE_SOCO || p->poseAtual == POSE_CHUTE ||
                                p->poseAtual == POSE_PODER || p->poseAtual == POSE_DANO))
            {
                // A animação será finalizada pela função AtualizarAnimacao
            }
        }
    }

    // Configurar source rectangle para sprite
    int frameWidth = 64;
    int frameHeight = 64;

    p->frameSource.x = p->frameAtual * frameWidth;
    p->frameSource.y = (int)p->poseAtual * frameHeight;
    p->frameSource.width = frameWidth;
    p->frameSource.height = frameHeight;
}

Texture2D ObterTexturaAtual(Personagem *p)
{
    switch (p->poseAtual)
    {
    case POSE_WALK:
        return p->texturaWalk.id > 0 ? p->texturaWalk : p->texturaLuta;
    case POSE_SOCO:
        return p->texturaSoco.id > 0 ? p->texturaSoco : p->texturaLuta;
    case POSE_CHUTE:
        return p->texturaChute.id > 0 ? p->texturaChute : p->texturaLuta;
    case POSE_PODER:
        return p->texturaPoder.id > 0 ? p->texturaPoder : p->texturaLuta;
    case POSE_DEFESA:
        return p->texturaDefesa.id > 0 ? p->texturaDefesa : p->texturaLuta;
    case POSE_DANO:
        return p->texturaDano.id > 0 ? p->texturaDano : p->texturaLuta;
    case POSE_IDLE:
    default:
        return p->texturaLuta;
    }
}

void IniciarAnimacao(Personagem *p, TipoPose pose, float duracao)
{
    p->poseAtual = pose;
    p->timerAnimacao = 0.0f;
    p->duracaoAnimacao = duracao;
    p->animando = true;
    p->frameAtual = 0; // Resetar frame para início da animação
    p->timerFrame = 0.0f;

    // Bloquear movimento durante ataques
    if (pose == POSE_SOCO || pose == POSE_CHUTE || pose == POSE_PODER)
    {
        p->podeSeMovimentar = false;
        p->podeAtacar = false;
    }
}

void AtualizarAnimacao(Personagem *p, float deltaTime)
{
    if (p->animando)
    {
        p->timerAnimacao += deltaTime;
        if (p->timerAnimacao >= p->duracaoAnimacao)
        {
            p->poseAtual = POSE_IDLE;
            p->animando = false;
            p->timerAnimacao = 0.0f;
            p->frameAtual = 0;
            p->timerFrame = 0.0f;

            // Restaurar capacidades
            p->podeSeMovimentar = true;
            p->podeAtacar = true;
        }
    }
}

Rectangle ObterSourceRectSprite(Personagem *p)
{
    return p->frameSource;
}

void VirarPersonagemParaOponente(Personagem *p1, Personagem *p2)
{
    // Só virar se não estiver atacando
    if (!p1->animando || (p1->poseAtual != POSE_SOCO && p1->poseAtual != POSE_CHUTE && p1->poseAtual != POSE_PODER))
    {
        if (p2->posicao.x > p1->posicao.x)
            p1->viradoParaDireita = true;
        else
            p1->viradoParaDireita = false;
    }

    if (!p2->animando || (p2->poseAtual != POSE_SOCO && p2->poseAtual != POSE_CHUTE && p2->poseAtual != POSE_PODER))
    {
        if (p1->posicao.x > p2->posicao.x)
            p2->viradoParaDireita = true;
        else
            p2->viradoParaDireita = false;
    }
}

bool ExecutarAtaque(Personagem *atacante, Personagem *alvo, TipoPose tipoAtaque, int dano)
{
    if (!atacante->podeAtacar || atacante->animando)
        return false;

    // Verificar se está próximo o suficiente
    if (!VerificarProximidade(atacante, alvo))
        return false;

    // Executar ataque
    alvo->vidaAtual -= dano;
    if (alvo->vidaAtual < 0)
        alvo->vidaAtual = 0;

    // Iniciar animações
    float duracaoAtaque = 0.4f;
    if (tipoAtaque == POSE_SOCO)
        duracaoAtaque = 0.3f;
    else if (tipoAtaque == POSE_CHUTE)
        duracaoAtaque = 0.5f;
    else if (tipoAtaque == POSE_PODER)
        duracaoAtaque = 0.8f;

    IniciarAnimacao(atacante, tipoAtaque, duracaoAtaque);
    IniciarAnimacao(alvo, POSE_DANO, 0.3f);

    // Empurrar o alvo para trás
    float forcaEmpurrao = 30.0f;
    if (tipoAtaque == POSE_CHUTE)
        forcaEmpurrao = 45.0f;
    else if (tipoAtaque == POSE_PODER)
        forcaEmpurrao = 60.0f;

    if (atacante->viradoParaDireita)
    {
        alvo->posicao.x += forcaEmpurrao;
    }
    else
    {
        alvo->posicao.x -= forcaEmpurrao;
    }

    return true;
}

void InicializarPersonagem(Personagem *p, const char *nomePersonagem)
{
    p->vidaMaxima = VIDA_MAXIMA;
    p->vidaAtual = VIDA_MAXIMA;
    p->poderMaximo = PODER_MAXIMO;
    p->poderAtual = PODER_MAXIMO; // Começar com poder no máximo
    p->danoSoco = 20;
    p->danoChute = 30;
    p->danoPoder = 50;

    p->poseAtual = POSE_IDLE;
    p->timerAnimacao = 0.0f;
    p->duracaoAnimacao = 0.0f;
    p->animando = false;

    // Inicializar sistema de movimento e sprites
    p->velocidade = (Vector2){0, 0};
    p->velocidadeMaxima = 200.0f;
    p->viradoParaDireita = true;
    p->podeAtacar = true;
    p->podeSeMovimentar = true;

    // Inicializar sprites
    p->frameAtual = 0;
    p->totalFrames = 4;
    p->timerFrame = 0.0f;
    p->duracaoFrame = 0.12f;
    p->frameSource = (Rectangle){0, 0, 64, 64};

    p->texturaDefesa = p->texturaLuta;
    p->texturaDano = p->texturaLuta;
}
