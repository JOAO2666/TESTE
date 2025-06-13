#include "efeitos.h"
#include "raylib.h"
#include <stdio.h> // For GetRandomValue (though it's a raylib macro, good to have for general C utilities)

void CriarEfeitoImpacto(SistemaParticulas *sistema, Vector2 posicao, Color cor, int numParticulas)
{
    sistema->ativo = true;
    sistema->timer = 0.0f;
    sistema->numParticulas = numParticulas;

    for (int i = 0; i < numParticulas && i < 50; i++)
    {
        sistema->particulas[i].posicao = posicao;
        sistema->particulas[i].velocidade = (Vector2){
            (float)(GetRandomValue(-200, 200)),
            (float)(GetRandomValue(-200, 200))};
        sistema->particulas[i].cor = cor;
        sistema->particulas[i].vida = 1.0f;
        sistema->particulas[i].vidaMaxima = 1.0f;
        sistema->particulas[i].tamanho = (float)GetRandomValue(3, 8);
    }
}

void AtualizarParticulas(SistemaParticulas *sistema, float deltaTime)
{
    if (!sistema->ativo)
        return;

    sistema->timer += deltaTime;

    for (int i = 0; i < sistema->numParticulas; i++)
    {
        Particula *p = &sistema->particulas[i];

        p->posicao.x += p->velocidade.x * deltaTime;
        p->posicao.y += p->velocidade.y * deltaTime;

        p->velocidade.y += 300.0f * deltaTime; // Gravity effect

        p->vida -= deltaTime * 2.0f; // Life decay

        // Update alpha based on life
        float alpha = p->vida / p->vidaMaxima;
        p->cor.a = (unsigned char)(255 * alpha);
    }

    // Deactivate system after a certain time (e.g., 1 second)
    if (sistema->timer > 1.0f)
    {
        sistema->ativo = false;
    }
}

void DesenharParticulas(SistemaParticulas *sistema)
{
    if (!sistema->ativo)
        return;

    for (int i = 0; i < sistema->numParticulas; i++)
    {
        Particula *p = &sistema->particulas[i];
        if (p->vida > 0)
        {
            DrawCircleV(p->posicao, p->tamanho, p->cor);
        }
    }
}
