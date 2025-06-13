#include "ui.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "config.h" // For ObterNomeTecla

void DesenharSelecaoPersonagem(Personagem personagens[], int selecionado, int inicioX, int inicioY, int larguraArea, int alturaArea, Color corDestaque)
{
    int espacamento = 35;
    int larguraPers = 150;
    int alturaPers = 150;

    int colunas = 3;
    int linhas = 2;

    int larguraTotal = colunas * larguraPers + (colunas - 1) * espacamento;
    int alturaTotal = linhas * alturaPers + (linhas - 1) * espacamento;

    int posXInicial = inicioX + (larguraArea - larguraTotal) / 2;
    int posYInicial = inicioY + (alturaArea - alturaTotal) / 2;

    for (int i = 0; i < MAX_PERSONAGENS; i++)
    {
        int linha = i / colunas;
        int coluna = i % colunas;

        int x = posXInicial + coluna * (larguraPers + espacamento);
        int y = posYInicial + linha * (alturaPers + espacamento);

        Rectangle destino = {(float)x, (float)y, (float)larguraPers, (float)alturaPers};
        Color cor = WHITE;

        if (i == selecionado)
        {
            destino.width *= 1.2f;
            destino.height *= 1.2f;
            DrawRectangleLines(x - 5, y - 5, (int)(larguraPers * 1.2f) + 10, (int)(alturaPers * 1.2f) + 10, corDestaque);
        }

        DrawTexturePro(personagens[i].textura,
                       (Rectangle){0, 0, (float)personagens[i].textura.width, (float)personagens[i].textura.height},
                       destino,
                       (Vector2){0, 0},
                       0.0f,
                       cor);
    }
}

void DesenharInfoPersonagem(Personagem personagem, int x, int y, int largura, int altura, Font fonte)
{
    // Painel de fundo com gradiente
    DrawRectangleRounded((Rectangle){x, y, largura, altura}, 0.1f, 10, Fade(BLACK, 0.85f));
    DrawRectangleRoundedLines((Rectangle){x, y, largura, altura}, 0.1f, 10, personagem.corHabilidade);

    int posY = y + 25;
    int espacamento = 45;

    // Nome do personagem com fonte ainda maior
    DrawTextEx(fonte, personagem.nome, (Vector2){x + 25, posY}, 42, 2, WHITE);
    posY += espacamento + 20;

    // Habilidade com fonte maior e melhor destaque
    const char *habilidadeTexto = TextFormat("Habilidade: %s", personagem.habilidade);
    DrawTextEx(fonte, habilidadeTexto, (Vector2){x + 25, posY}, 32, 2, personagem.corHabilidade);
    posY += espacamento;

    // História com fonte maior
    const char *historiaTexto = "História:";
    DrawTextEx(fonte, historiaTexto, (Vector2){x + 25, posY}, 28, 2, LIGHTGRAY);
    posY += 35;

    // Texto da história com fonte maior e melhor formatação
    int larguraTexto = largura - 50;
    const char *historia = personagem.historia;
    int tamanhoFonte = 24; // Aumentado de 20 para 24

    char linha[250]; // Aumentado o buffer
    int posicao = 0;
    int caracteresPorLinha = (larguraTexto / (tamanhoFonte * 0.55f)); // Ajustado para fonte maior

    if (caracteresPorLinha <= 0)
        caracteresPorLinha = 25; // Aumentado

    while (historia[posicao] != '\0' && posY < y + altura - 35)
    {
        int fim = posicao + caracteresPorLinha;
        int tamanhoHistoria = strlen(historia);

        if (fim >= tamanhoHistoria)
        {
            fim = tamanhoHistoria;
        }
        else
        {
            // Procurar quebra de palavra mais inteligente
            while (fim > posicao && historia[fim] != ' ' && historia[fim] != '.' && historia[fim] != ',')
            {
                fim--;
            }
            // Se não encontrou espaço, quebra na palavra mesmo
            if (fim == posicao)
            {
                fim = posicao + caracteresPorLinha;
            }
        }

        int tamanho = fim - posicao;
        if (tamanho > 0 && tamanho < 249)
        {
            strncpy(linha, &historia[posicao], tamanho);
            linha[tamanho] = '\0';

            // Remover espaços no início da linha
            char *linhaLimpa = linha;
            while (*linhaLimpa == ' ')
                linhaLimpa++;

            DrawTextEx(fonte, linhaLimpa, (Vector2){x + 25, posY}, tamanhoFonte, 2, WHITE);
            posY += 30; // Aumentado o espaçamento entre linhas
            posicao = (fim < tamanhoHistoria && (historia[fim] == ' ' || historia[fim] == '.' || historia[fim] == ',')) ? fim + 1 : fim;
        }
        else
        {
            break;
        }
    }
}

void DesenharBarraVida(int x, int y, int largura, int altura, int vidaAtual, int vidaMaxima, Color cor, const char *nomeJogador)
{
    // Fundo da barra com gradiente
    DrawRectangleGradientV(x, y, largura, altura, Fade(DARKGRAY, 0.8f), DARKGRAY);

    // Barra de vida com gradiente baseado na porcentagem
    float porcentagem = (float)vidaAtual / (float)vidaMaxima;
    int larguraVida = (int)(largura * porcentagem);

    // Cor da vida baseada na porcentagem com gradiente
    Color corVida;
    if (porcentagem > 0.6f)
        corVida = ColorLerp(YELLOW, GREEN, (porcentagem - 0.6f) / 0.4f);
    else if (porcentagem > 0.3f)
        corVida = ColorLerp(RED, ORANGE, (porcentagem - 0.3f) / 0.3f);
    else
        corVida = ColorLerp((Color){128, 0, 0, 255}, RED, porcentagem / 0.3f); // Substituindo DARKRED por cor RGB

    // Desenhar barra com efeito de gradiente
    DrawRectangleGradientH(x, y, larguraVida, altura, corVida, Fade(corVida, 0.7f));

    // Efeito de brilho na barra
    if (porcentagem > 0.8f)
    {
        float brilho = 0.3f + 0.2f * sin(GetTime() * 6);
        DrawRectangleGradientH(x, y, larguraVida, altura / 3, Fade(WHITE, brilho), BLANK);
    }

    // Borda estilizada
    DrawRectangleLines(x - 1, y - 1, largura + 2, altura + 2, BLACK);
    DrawRectangleLines(x, y, largura, altura, WHITE);

    // Texto da vida centralizado e estilizado
    const char *textoVida = TextFormat("%d/%d", vidaAtual, vidaMaxima);
    int larguraTexto = MeasureText(textoVida, 16);

    // Sombra do texto
    DrawText(textoVida, x + largura / 2 - larguraTexto / 2 + 1, y + altura / 2 - 8 + 1, 16, BLACK);
    // Texto principal
    DrawText(textoVida, x + largura / 2 - larguraTexto / 2, y + altura / 2 - 8, 16, WHITE);

    // Nome do jogador acima da barra
    int larguraNome = MeasureText(nomeJogador, 20);
    DrawText(nomeJogador, x + largura / 2 - larguraNome / 2 + 1, y - 26, 20, BLACK); // Sombra
    DrawText(nomeJogador, x + largura / 2 - larguraNome / 2, y - 25, 20, cor);
}

void DesenharBarraPoder(int x, int y, int largura, int altura, int poderAtual, int poderMaximo, Color corPersonagem)
{
    // Fundo da barra
    DrawRectangleGradientV(x, y, largura, altura, Fade(DARKGRAY, 0.8f), DARKGRAY);

    // Barra de poder com efeito pulsante quando disponível
    float porcentagem = (float)poderAtual / (float)poderMaximo;
    int larguraPoder = (int)(largura * porcentagem);

    // Cor do poder com efeito especial
    Color corPoder;
    if (poderAtual >= 50)
    {
        // Efeito pulsante quando especial está disponível
        float pulso = 0.6f + 0.4f * sin(GetTime() * 10);
        corPoder = ColorLerp(BLUE, YELLOW, pulso);

        // Efeito de partículas visuais
        for (int i = 0; i < 3; i++)
        {
            float offset = i * 2.0f;
            float alpha = 0.3f * sin(GetTime() * 8 + offset);
            DrawRectangle(x + larguraPoder - 5, y - 2, 10, altura + 4, Fade(YELLOW, alpha));
        }
    }
    else
    {
        corPoder = ColorLerp(DARKBLUE, BLUE, porcentagem);
    }

    DrawRectangleGradientH(x, y, larguraPoder, altura, corPoder, Fade(corPoder, 0.6f));

    // Linha indicadora dos 50 pontos (metade da barra)
    int linhaMeio = x + largura / 2;
    DrawLine(linhaMeio, y, linhaMeio, y + altura, Fade(WHITE, 0.8f));
    DrawLine(linhaMeio - 1, y, linhaMeio - 1, y + altura, Fade(BLACK, 0.5f));

    // Borda estilizada
    DrawRectangleLines(x - 1, y - 1, largura + 2, altura + 2, BLACK);
    DrawRectangleLines(x, y, largura, altura, WHITE);

    // Texto do poder
    const char *textoPoder = TextFormat("%d/%d", poderAtual, poderMaximo);
    int larguraTexto = MeasureText(textoPoder, 14);

    // Sombra do texto
    DrawText(textoPoder, x + largura / 2 - larguraTexto / 2 + 1, y + altura / 2 - 7 + 1, 14, BLACK);
    DrawText(textoPoder, x + largura / 2 - larguraTexto / 2, y + altura / 2 - 7, 14, WHITE);

    // Indicador de poder especial disponível
    if (poderAtual >= 50)
    {
        const char *textoEspecial = "ESPECIAL PRONTO!";
        float alpha = 0.7f + 0.3f * sin(GetTime() * 6);
        Color corTexto = ColorLerp(YELLOW, WHITE, alpha);

        DrawText(textoEspecial, x + largura + 15 + 1, y + altura / 2 - 7 + 1, 14, BLACK); // Sombra
        DrawText(textoEspecial, x + largura + 15, y + altura / 2 - 7, 14, corTexto);
    }
}

void DesenharHUD(EstadoJogo *estado, Font fonte)
{
    // Verificar se os jogadores existem
    if (!estado->jogador1 || !estado->jogador2)
        return;

    // Painel superior para HUD
    DrawRectangleGradientV(0, 0, LARGURA_TELA, 180, Fade(BLACK, 0.7f), Fade(BLACK, 0.3f));
    DrawLine(0, 180, LARGURA_TELA, 180, Fade(WHITE, 0.5f));

    // === PLAYER 1 HUD (lado esquerdo) ===
    int margemEsquerda = 30;
    int larguraBarra = 350;
    int alturaBarra = 25;

    DesenharBarraVida(margemEsquerda, 45, larguraBarra, alturaBarra,
                      estado->jogador1->vidaAtual, estado->jogador1->vidaMaxima,
                      BLUE, estado->jogador1->nome);

    // Barra de poder do Player 1
    DesenharBarraPoder(margemEsquerda, 85, larguraBarra, 20,
                       estado->jogador1->poderAtual, estado->jogador1->poderMaximo,
                       estado->jogador1->corHabilidade);

    // Habilidade do Player 1
    const char *habilidadeP1 = TextFormat("Habilidade: %s", estado->jogador1->habilidade);
    DrawTextEx(fonte, habilidadeP1, (Vector2){margemEsquerda, 115}, 18, 2, estado->jogador1->corHabilidade);

    // === PLAYER 2 HUD (lado direito) ===
    int margemDireita = LARGURA_TELA - larguraBarra - 30;

    DesenharBarraVida(margemDireita, 45, larguraBarra, alturaBarra,
                      estado->jogador2->vidaAtual, estado->jogador2->vidaMaxima,
                      RED, estado->jogador2->nome);

    // Barra de poder do Player 2
    DesenharBarraPoder(margemDireita, 85, larguraBarra, 20,
                       estado->jogador2->poderAtual, estado->jogador2->poderMaximo,
                       estado->jogador2->corHabilidade);

    // Habilidade do Player 2
    const char *habilidadeP2 = TextFormat("Habilidade: %s", estado->jogador2->habilidade);
    Vector2 tamanhoHab2 = MeasureTextEx(fonte, habilidadeP2, 18, 2);
    DrawTextEx(fonte, habilidadeP2, (Vector2){margemDireita + larguraBarra - tamanhoHab2.x, 115}, 18, 2, estado->jogador2->corHabilidade);

    // === INFORMAÇÕES CENTRAIS ===
    // Round atual
    const char *textoRound = TextFormat("ROUND %d/%d", estado->roundAtual, MAX_ROUNDS);
    Vector2 tamanhoRound = MeasureTextEx(fonte, textoRound, 32, 2);
    DrawTextEx(fonte, textoRound, (Vector2){LARGURA_TELA / 2 - tamanhoRound.x / 2, 25}, 32, 2, YELLOW);

    // Timer com efeito de urgência
    Color corTempo = WHITE;
    if (estado->tempoRound <= 10.0f)
    {
        float intensidade = 0.5f + 0.5f * sin(GetTime() * 8);
        corTempo = ColorLerp(WHITE, RED, intensidade);
    }

    const char *textoTempo = TextFormat("%.0f", estado->tempoRound);
    Vector2 tamanhoTempo = MeasureTextEx(fonte, textoTempo, 48, 2);
    // Sombra do tempo
    DrawTextEx(fonte, textoTempo, (Vector2){LARGURA_TELA / 2 - tamanhoTempo.x / 2 + 2, 62}, 48, 2, BLACK);
    DrawTextEx(fonte, textoTempo, (Vector2){LARGURA_TELA / 2 - tamanhoTempo.x / 2, 60}, 48, 2, corTempo);

    // Indicador VS entre os jogadores
    const char *textoVS = "VS";
    Vector2 tamanhoVS = MeasureTextEx(fonte, textoVS, 24, 2);
    DrawTextEx(fonte, textoVS, (Vector2){LARGURA_TELA / 2 - tamanhoVS.x / 2, 135}, 24, 2, Fade(WHITE, 0.8f));
}

void DesenharTelaSelecaoMapa(Mapa mapas[], int mapaAtual, Font fonte)
{

    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(BLACK, 0.8f));

    const char *titulo = "ESCOLHA O MAPA DE LUTA";
    Vector2 tamanhoTitulo = MeasureTextEx(fonte, titulo, 52, 2);
    DrawTextEx(fonte, titulo, (Vector2){LARGURA_TELA / 2 - tamanhoTitulo.x / 2, 100}, 52, 2, WHITE);

    int larguraMapa = 800;
    int alturaMapa = 450;
    int xMapa = (LARGURA_TELA - larguraMapa) / 2;
    int yMapa = 200;

    DrawTexturePro(mapas[mapaAtual].textura,
                   (Rectangle){0, 0, mapas[mapaAtual].textura.width, mapas[mapaAtual].textura.height},
                   (Rectangle){xMapa, yMapa, larguraMapa, alturaMapa},
                   (Vector2){0, 0}, 0.0f, WHITE);

    DrawRectangleLines(xMapa - 5, yMapa - 5, larguraMapa + 10, alturaMapa + 10, YELLOW);

    const char *nomeMapa = mapas[mapaAtual].nome;
    Vector2 tamanhoNome = MeasureTextEx(fonte, nomeMapa, 40, 2);
    DrawTextEx(fonte, nomeMapa, (Vector2){LARGURA_TELA / 2 - tamanhoNome.x / 2, yMapa + alturaMapa + 30}, 40, 2, YELLOW);

    const char *descricao = mapas[mapaAtual].descricao;
    Vector2 tamanhoDesc = MeasureTextEx(fonte, descricao, 28, 2);
    DrawTextEx(fonte, descricao, (Vector2){LARGURA_TELA / 2 - tamanhoDesc.x / 2, yMapa + alturaMapa + 80}, 28, 2, LIGHTGRAY);

    DrawTextEx(fonte, "← → para navegar mapas", (Vector2){50, ALTURA_TELA - 100}, 28, 2, WHITE);
    DrawTextEx(fonte, "ENTER para confirmar", (Vector2){50, ALTURA_TELA - 70}, 28, 2, GREEN);
    DrawTextEx(fonte, "BACKSPACE para voltar", (Vector2){50, ALTURA_TELA - 40}, 28, 2, GRAY);
}

void DesenharTelaOpcoes(ConfiguracaoJogo *config, int opcaoSelecionada, bool aguardandoTecla, Font fonte)
{

    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(BLACK, 0.9f));

    const char *titulo = "OPÇÕES";
    Vector2 tamanhoTitulo = MeasureTextEx(fonte, titulo, 64, 2);
    DrawTextEx(fonte, titulo, (Vector2){LARGURA_TELA / 2 - tamanhoTitulo.x / 2, 100}, 64, 2, WHITE);

    const char *opcoes[OPCOES_CONFIG] = {
        "CONTROLES PLAYER 1",
        "CONTROLES PLAYER 2",
        "VOLUME MÚSICA",
        "VOLUME EFEITOS",
        "RESETAR CONTROLES",
        "SALVAR CONFIGURAÇÕES",
        "CARREGAR CONFIGURAÇÕES",
        "VOLTAR"};

    int posY = 250;
    int espacamento = 80;

    for (int i = 0; i < OPCOES_CONFIG; i++)
    {
        Color corTexto = (i == opcaoSelecionada) ? YELLOW : WHITE;
        Color corCaixa = (i == opcaoSelecionada) ? Fade(YELLOW, 0.3f) : Fade(WHITE, 0.1f);

        int larguraCaixa = 800;
        int alturaCaixa = 60;
        int x = (LARGURA_TELA - larguraCaixa) / 2;
        int y = posY + i * espacamento - 10;

        DrawRectangleRounded((Rectangle){x, y, larguraCaixa, alturaCaixa}, 0.1f, 10, corCaixa);
        DrawRectangleRoundedLines((Rectangle){x, y, larguraCaixa, alturaCaixa}, 0.1f, 10, corTexto);

        DrawTextEx(fonte, opcoes[i], (Vector2){x + 20, posY + i * espacamento}, 36, 2, corTexto);

        if (i == 0)
        {
            const char *controles = TextFormat("Poder:%s Soco:%s Chute:%s",
                                               ObterNomeTecla(config->teclaPoderP1),
                                               ObterNomeTecla(config->teclaSocoP1),
                                               ObterNomeTecla(config->teclaChute1));
            DrawTextEx(fonte, controles, (Vector2){x + 20, posY + i * espacamento + 35}, 24, 2, LIGHTGRAY);
        }
        else if (i == 1)
        {
            const char *controles = TextFormat("Poder:%s Soco:%s Chute:%s",
                                               ObterNomeTecla(config->teclaPoderP2),
                                               ObterNomeTecla(config->teclaSocoP2),
                                               ObterNomeTecla(config->teclaChute2));
            DrawTextEx(fonte, controles, (Vector2){x + 20, posY + i * espacamento + 35}, 24, 2, LIGHTGRAY);
        }
        else if (i == 2)
        {
            int barraLargura = 200;
            int barraX = x + 400;
            int barraY = posY + i * espacamento + 15;

            DrawRectangle(barraX, barraY, barraLargura, 20, DARKGRAY);
            DrawRectangle(barraX, barraY, (int)(barraLargura * config->volumeMusica), 20, GREEN);
            DrawRectangleLines(barraX, barraY, barraLargura, 20, WHITE);

            const char *volumeTexto = TextFormat("%.0f%%", config->volumeMusica * 100);
            DrawTextEx(fonte, volumeTexto, (Vector2){barraX + barraLargura + 10, barraY}, 24, 2, WHITE);
        }
        else if (i == 3)
        {
            int barraLargura = 200;
            int barraX = x + 400;
            int barraY = posY + i * espacamento + 15;

            DrawRectangle(barraX, barraY, barraLargura, 20, DARKGRAY);
            DrawRectangle(barraX, barraY, (int)(barraLargura * config->volumeEfeitos), 20, BLUE);
            DrawRectangleLines(barraX, barraY, barraLargura, 20, WHITE);

            const char *volumeTexto = TextFormat("%.0f%%", config->volumeEfeitos * 100);
            DrawTextEx(fonte, volumeTexto, (Vector2){barraX + barraLargura + 10, barraY}, 24, 2, WHITE);
        }
    }

    if (aguardandoTecla)
    {
        const char *instrucao = "PRESSIONE UMA TECLA PARA CONFIGURAR...";
        Vector2 tamanhoInstrucao = MeasureTextEx(fonte, instrucao, 28, 2);
        DrawTextEx(fonte, instrucao, (Vector2){LARGURA_TELA / 2 - tamanhoInstrucao.x / 2, ALTURA_TELA - 100}, 28, 2, YELLOW);
    }
    else
    {
        const char *instrucoes = "↑/↓: Navegar | ENTER: Selecionar | ←/→: Ajustar Volume | BACKSPACE: Voltar";
        Vector2 tamanhoInstrucoes = MeasureTextEx(fonte, instrucoes, 24, 2);
        DrawTextEx(fonte, instrucoes, (Vector2){LARGURA_TELA / 2 - tamanhoInstrucoes.x / 2, ALTURA_TELA - 80}, 24, 2, LIGHTGRAY);
    }
}
