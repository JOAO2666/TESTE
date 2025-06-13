#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "structs.h"
#include "defines.h"
#include "personagem.h"
#include "ui.h"
#include "efeitos.h"
#include "config.h"

// All helper functions have been moved to their respective .c files.
// unifight.c now only contains the main game loop and initialization.

int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    // ===== INICIALIZAÇÃO =====
    InitWindow(LARGURA_TELA, ALTURA_TELA, "UNI-FIGHT");
    SetTargetFPS(60);
    InitAudioDevice();

    Font fontePixel = LoadFont("fontes/Pixelify_Sans/PixelifySans-VariableFont_wght.ttf");
    Texture2D fundoMenu = LoadTexture("./fundoMenu2.jpg");
    Texture2D fundoSelecao = LoadTexture("./fundo.png");
    Texture2D logo = LoadTexture("./logoUnifight3.png");

    Music musicaFundo = LoadMusicStream("musicas/menu_background.mp3");
    PlayMusicStream(musicaFundo);

    ConfiguracaoJogo config = {0};
    InicializarConfiguracaoPadrao(&config);

    int opcaoSelecionada = 0;
    bool aguardandoTecla = false;
    int teclaParaConfigurar = -1;

    OpcaoMenu menu[OPCOES_MENU] = {
        {"JOGAR", 600},
        {"OPCOES", 700},
        {"SAIR", 800}};
    int menuSelecionado = 0;

    Personagem personagens[MAX_PERSONAGENS] = {
        {.textura = LoadTexture("./personagens/kaelPerfil.jpg"),
         .nome = "Kael",
         .habilidade = "Fogo",
         .historia = "Homem de pele morena, corpo forte e definido. Treinou com monges e feiticeiros, aprendendo a controlar o fogo. Agora é caçador de monstros e artefatos arcanos.",
         .corHabilidade = RED,
         .texturaLuta = LoadTexture("./personagens/kael.jpg"),
         .texturaWalk = LoadTexture("./personagens/kael.jpg"),
         .texturaSoco = LoadTexture("./personagens/kael.jpg"),
         .texturaChute = LoadTexture("./personagens/kael.jpg"),
         .texturaPoder = LoadTexture("./personagens/kael.jpg"),
         .texturaDefesa = LoadTexture("./personagens/kael.jpg"),
         .texturaDano = LoadTexture("./personagens/kael.jpg")},
        {.textura = LoadTexture("./personagens/milenaPerfil.jpg"),
         .nome = "Dandara",
         .habilidade = "Gelo",
         .historia = "Mulher esbelta com cabelos rosas. Ex-mercenária abandonada por seu grupo, tornou-se caçadora de recompensas. Guerreira experiente e astuta.",
         .corHabilidade = SKYBLUE,
         .texturaLuta = LoadTexture("./personagens/milenaCerta.png"),
         .texturaWalk = LoadTexture("./personagens/milenaCerta.png"),
         .texturaSoco = LoadTexture("./personagens/milenaCerta.png"),
         .texturaChute = LoadTexture("./personagens/milenaCerta.png"),
         .texturaPoder = LoadTexture("./personagens/milenaCerta.png"),
         .texturaDefesa = LoadTexture("./personagens/milenaCerta.png"),
         .texturaDano = LoadTexture("./personagens/milenaCerta.png")},
        {.textura = LoadTexture("./personagens/juliaPerfil.jpg"),
         .nome = "Valéria",
         .habilidade = "Gelo",
         .historia = "Porte ágil, cabelos castanho-escuros curtos. Após assassinato dos pais, trabalhou como mensageira e espiã. Hoje é caçadora de segredos.",
         .corHabilidade = SKYBLUE,
         .texturaLuta = LoadTexture("./personagens/juliaCerta.png"),
         .texturaWalk = LoadTexture("./personagens/juliaCerta.png"),
         .texturaSoco = LoadTexture("./personagens/juliaCerta.png"),
         .texturaChute = LoadTexture("./personagens/juliaCerta.png"),
         .texturaPoder = LoadTexture("./personagens/juliaCerta.png"),
         .texturaDefesa = LoadTexture("./personagens/juliaCerta.png"),
         .texturaDano = LoadTexture("./personagens/juliaCerta.png")},
        {.textura = LoadTexture("./personagens/kaykPerfil.jpg"),
         .nome = "Tim",
         .habilidade = "Gelo",
         .historia = "Jovem guerreiro das montanhas. Treinado pelo avô, carrega kimono herdado. Promessa de usar força apenas para proteger outros.",
         .corHabilidade = SKYBLUE,
         .texturaLuta = LoadTexture("./personagens/kaykCerta.png"),
         .texturaWalk = LoadTexture("./personagens/kaykCerta.png"),
         .texturaSoco = LoadTexture("./personagens/kaykCerta.png"),
         .texturaChute = LoadTexture("./personagens/kaykCerta.png"),
         .texturaPoder = LoadTexture("./personagens/kaykCerta.png"),
         .texturaDefesa = LoadTexture("./personagens/kaykCerta.png"),
         .texturaDano = LoadTexture("./personagens/kaykCerta.png")},
        {.textura = LoadTexture("./personagens/joaoPerfil.jpg"),
         .nome = "Joana",
         .habilidade = "Fogo",
         .historia = "Perita em artes marciais. Quando vê pessoas em perigo, usa suas habilidades e domínio sobre o fogo para deter inimigos.",
         .corHabilidade = RED,
         .texturaLuta = LoadTexture("./personagens/joao.png"),
         .texturaWalk = LoadTexture("./personagens/joao.png"),
         .texturaSoco = LoadTexture("./personagens/joao.png"),
         .texturaChute = LoadTexture("./personagens/joao.png"),
         .texturaPoder = LoadTexture("./personagens/joao.png"),
         .texturaDefesa = LoadTexture("./personagens/joao.png"),
         .texturaDano = LoadTexture("./personagens/joao.png")},
        {.textura = LoadTexture("./personagens/yuriPerfil.jpg"),
         .nome = "Yuri",
         .habilidade = "Fogo",
         .historia = "Físico construído para combate. Ex-capitão da guarda, foi traído e preso. Fugiu e vive como mercenário e guarda-costas.",
         .corHabilidade = RED,
         .texturaLuta = LoadTexture("./personagens/yuri.jpg"),
         .texturaWalk = LoadTexture("./personagens/yuri.jpg"),
         .texturaSoco = LoadTexture("./personagens/yuri.jpg"),
         .texturaChute = LoadTexture("./personagens/yuri.jpg"),
         .texturaPoder = LoadTexture("./personagens/yuri.jpg"),
         .texturaDefesa = LoadTexture("./personagens/yuri.jpg"),
         .texturaDano = LoadTexture("./personagens/yuri.jpg")}};

    for (int i = 0; i < MAX_PERSONAGENS; i++)
    {
        InicializarPersonagem(&personagens[i], personagens[i].nome);
    }

    Mapa mapas[MAX_MAPAS] = {
        {LoadTexture("./frames/frame-1.png"), "Arena Vulcânica", "Arena cercada por lava e rochas ígneas. Ideal para lutadores de fogo."},
        {LoadTexture("./frames/frame-2.png"), "Caverna Cristalina", "Caverna mística com cristais de gelo brilhantes. Favorece usuários de gelo."},
        {LoadTexture("./frames/frame-3.png"), "Templo Gelado", "Antigo templo nas montanhas geladas. Ambiente sagrado e equilibrado."},
        {LoadTexture("./frames/frame-4.png"), "Floresta Ancestral", "Floresta antiga com ruínas místicas. Energia natural balanceada."},
        {LoadTexture("./frames/frame-5.png"), "Coliseu Neutro", "Arena equilibrada sem vantagens elementais para todos os lutadores."},
        {LoadTexture("./frames/frame-6.png"), "Santuário Perdido", "Ruínas de um antigo santuário com poderes místicos adormecidos."}};

    int selecionadoJogador1 = 0;
    int selecionadoJogador2 = MAX_PERSONAGENS - 1;
    int mapaAtual = 0;

    EstadoJogo estado = {0};
    estado.roundAtual = 1;
    estado.tempoRound = TEMPO_ROUND;
    estado.jogador1Confirmado = false;
    estado.jogador2Confirmado = false;
    estado.mapaConfirmado = false;

    // Configurar limites da arena
    estado.limiteEsquerdo = 100.0f;
    estado.limiteDireito = LARGURA_TELA - 100.0f;
    estado.chao = ALTURA_TELA - 100.0f;

    Tela telaAtual = TELA_MENU;
    int tamanhoFonte = 44;

    while (!WindowShouldClose())
    {

        UpdateMusicStream(musicaFundo);
        SetMusicVolume(musicaFundo, config.volumeMusica);

        if (telaAtual == TELA_MENU)
        {
            if (IsKeyPressed(KEY_DOWN))
                menuSelecionado = (menuSelecionado + 1) % OPCOES_MENU;
            if (IsKeyPressed(KEY_UP))
                menuSelecionado = (menuSelecionado - 1 + OPCOES_MENU) % OPCOES_MENU;

            if (IsKeyPressed(KEY_ENTER))
            {
                if (menuSelecionado == 0)
                {
                    telaAtual = TELA_SELECAO;
                }
                else if (menuSelecionado == 1)
                {
                    telaAtual = TELA_OPCOES;
                    opcaoSelecionada = 0;
                }
                else if (menuSelecionado == 2)
                {
                    break;
                }
            }
        }
        else if (telaAtual == TELA_OPCOES)
        {
            if (!aguardandoTecla)
            {

                if (IsKeyPressed(KEY_DOWN))
                    opcaoSelecionada = (opcaoSelecionada + 1) % OPCOES_CONFIG;
                if (IsKeyPressed(KEY_UP))
                    opcaoSelecionada = (opcaoSelecionada - 1 + OPCOES_CONFIG) % OPCOES_CONFIG;

                if (opcaoSelecionada == 2)
                {
                    if (IsKeyPressed(KEY_LEFT))
                        config.volumeMusica = fmaxf(0.0f, config.volumeMusica - 0.1f);
                    if (IsKeyPressed(KEY_RIGHT))
                        config.volumeMusica = fminf(1.0f, config.volumeMusica + 0.1f);
                }
                else if (opcaoSelecionada == 3)
                {
                    if (IsKeyPressed(KEY_LEFT))
                        config.volumeEfeitos = fmaxf(0.0f, config.volumeEfeitos - 0.1f);
                    if (IsKeyPressed(KEY_RIGHT))
                        config.volumeEfeitos = fminf(1.0f, config.volumeEfeitos + 0.1f);
                }

                if (IsKeyPressed(KEY_ENTER))
                {
                    if (opcaoSelecionada == 0)
                    {
                        aguardandoTecla = true;
                        teclaParaConfigurar = 0;
                    }
                    else if (opcaoSelecionada == 1)
                    {
                        aguardandoTecla = true;
                        teclaParaConfigurar = 3;
                    }
                    else if (opcaoSelecionada == 4)
                    {
                        InicializarConfiguracaoPadrao(&config);
                    }
                    else if (opcaoSelecionada == 7)
                    {
                        telaAtual = TELA_MENU;
                    }
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    telaAtual = TELA_MENU;
                }
            }
            else
            {

                int tecla = GetKeyPressed();
                if (tecla != 0)
                {

                    switch (teclaParaConfigurar)
                    {
                    case 0:
                        config.teclaPoderP1 = tecla;
                        break;
                    case 1:
                        config.teclaSocoP1 = tecla;
                        break;
                    case 2:
                        config.teclaChute1 = tecla;
                        break;
                    case 3:
                        config.teclaPoderP2 = tecla;
                        break;
                    case 4:
                        config.teclaSocoP2 = tecla;
                        break;
                    case 5:
                        config.teclaChute2 = tecla;
                        break;
                    }

                    teclaParaConfigurar++;

                    if ((teclaParaConfigurar == 3 && opcaoSelecionada == 0) ||
                        (teclaParaConfigurar == 6 && opcaoSelecionada == 1))
                    {
                        aguardandoTecla = false;
                        teclaParaConfigurar = -1;
                    }
                }

                if (IsKeyPressed(KEY_ESCAPE))
                {
                    aguardandoTecla = false;
                    teclaParaConfigurar = -1;
                }
            }
        }
        else if (telaAtual == TELA_SELECAO)
        {

            if (IsKeyPressed(KEY_D))
                selecionadoJogador1 = (selecionadoJogador1 + 1) % MAX_PERSONAGENS;
            if (IsKeyPressed(KEY_A))
                selecionadoJogador1 = (selecionadoJogador1 - 1 + MAX_PERSONAGENS) % MAX_PERSONAGENS;

            if (IsKeyPressed(KEY_RIGHT))
                selecionadoJogador2 = (selecionadoJogador2 + 1) % MAX_PERSONAGENS;
            if (IsKeyPressed(KEY_LEFT))
                selecionadoJogador2 = (selecionadoJogador2 - 1 + MAX_PERSONAGENS) % MAX_PERSONAGENS;

            if (IsKeyPressed(KEY_UP))
                mapaAtual = (mapaAtual - 1 + MAX_MAPAS) % MAX_MAPAS;
            if (IsKeyPressed(KEY_DOWN))
                mapaAtual = (mapaAtual + 1) % MAX_MAPAS;

            if (IsKeyPressed(KEY_ENTER) && !estado.jogador1Confirmado)
            {
                estado.jogador1Confirmado = true;
                estado.jogador1 = &personagens[selecionadoJogador1];
                printf("Jogador 1 escolheu: %s (Habilidade: %s)\n",
                       personagens[selecionadoJogador1].nome,
                       personagens[selecionadoJogador1].habilidade);
            }
            if (IsKeyPressed(KEY_SPACE) && !estado.jogador2Confirmado)
            {
                estado.jogador2Confirmado = true;
                estado.jogador2 = &personagens[selecionadoJogador2];
                printf("Jogador 2 escolheu: %s (Habilidade: %s)\n",
                       personagens[selecionadoJogador2].nome,
                       personagens[selecionadoJogador2].habilidade);
            }

            if (estado.jogador1Confirmado && estado.jogador2Confirmado)
            {
                telaAtual = TELA_SELECAO_MAPA;
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                telaAtual = TELA_MENU;
                estado.jogador1Confirmado = false;
                estado.jogador2Confirmado = false;
            }
        }
        else if (telaAtual == TELA_SELECAO_MAPA)
        {

            if (IsKeyPressed(KEY_LEFT))
                mapaAtual = (mapaAtual - 1 + MAX_MAPAS) % MAX_MAPAS;
            if (IsKeyPressed(KEY_RIGHT))
                mapaAtual = (mapaAtual + 1) % MAX_MAPAS;

            if (IsKeyPressed(KEY_ENTER))
            {
                estado.mapaAtual = &mapas[mapaAtual];
                estado.mapaConfirmado = true;

                // Inicializar posições dos personagens na arena
                InicializarPosicaoPersonagem(estado.jogador1, 300.0f, estado.chao, true);
                InicializarPosicaoPersonagem(estado.jogador2, LARGURA_TELA - 300.0f, estado.chao, false);

                // Fazer os personagens se virarem um para o outro
                VirarPersonagemParaOponente(estado.jogador1, estado.jogador2);

                telaAtual = TELA_LUTA;
                printf("Mapa selecionado: %s\n", mapas[mapaAtual].nome);
                printf("Posições inicializadas - P1: (%.0f, %.0f) P2: (%.0f, %.0f)\n",
                       estado.jogador1->posicao.x, estado.jogador1->posicao.y,
                       estado.jogador2->posicao.x, estado.jogador2->posicao.y);
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                telaAtual = TELA_SELECAO;
                estado.jogador1Confirmado = false;
                estado.jogador2Confirmado = false;
            }
        }
        else if (telaAtual == TELA_LUTA)
        {
            float deltaTime = GetFrameTime();

            estado.tempoRound -= deltaTime;
            if (estado.tempoRound <= 0)
            {
                estado.tempoRound = TEMPO_ROUND;
                estado.roundAtual++;
                if (estado.roundAtual > MAX_ROUNDS)
                {

                    telaAtual = TELA_MENU;
                    estado.roundAtual = 1;
                    estado.jogador1Confirmado = false;
                    estado.jogador2Confirmado = false;
                    estado.mapaConfirmado = false;
                }
            }

            // Processar movimento dos personagens
            ProcessarMovimentoPlayer1(estado.jogador1, &config);
            ProcessarMovimentoPlayer2(estado.jogador2, &config);

            // Mover personagens
            MoverPersonagem(estado.jogador1, deltaTime, estado.limiteEsquerdo, estado.limiteDireito);
            MoverPersonagem(estado.jogador2, deltaTime, estado.limiteEsquerdo, estado.limiteDireito);

            // Fazer personagens se virarem um para o outro automaticamente
            VirarPersonagemParaOponente(estado.jogador1, estado.jogador2);

            // Atualizar animações
            AtualizarAnimacao(estado.jogador1, deltaTime);
            AtualizarAnimacao(estado.jogador2, deltaTime);
            AtualizarAnimacaoSprite(estado.jogador1, deltaTime);
            AtualizarAnimacaoSprite(estado.jogador2, deltaTime);

            AtualizarParticulas(&estado.particulasImpacto, deltaTime);
            if (estado.flashTela > 0)
                estado.flashTela -= deltaTime * 3.0f;
            if (estado.tremor > 0)
                estado.tremor -= deltaTime * 5.0f;

            // Ataques Player 1
            if (IsKeyPressed(config.teclaPoderP1) && estado.jogador1->poderAtual >= 50 && estado.jogador1->podeAtacar)
            {
                if (ExecutarAtaque(estado.jogador1, estado.jogador2, POSE_PODER, estado.jogador1->danoPoder))
                {
                    estado.jogador1->poderAtual = 0;
                    Vector2 posImpacto = {estado.jogador2->posicao.x, estado.jogador2->posicao.y - 50};
                    CriarEfeitoImpacto(&estado.particulasImpacto, posImpacto, estado.jogador1->corHabilidade, 30);
                    estado.flashTela = 0.4f;
                    estado.tremor = 0.3f;
                }
            }
            if (IsKeyPressed(config.teclaSocoP1) && estado.jogador1->podeAtacar)
            {
                if (ExecutarAtaque(estado.jogador1, estado.jogador2, POSE_SOCO, estado.jogador1->danoSoco))
                {
                    estado.jogador1->poderAtual += 10;
                    if (estado.jogador1->poderAtual > PODER_MAXIMO)
                        estado.jogador1->poderAtual = PODER_MAXIMO;
                    Vector2 posImpacto = {estado.jogador2->posicao.x, estado.jogador2->posicao.y - 50};
                    CriarEfeitoImpacto(&estado.particulasImpacto, posImpacto, YELLOW, 15);
                    estado.tremor = 0.1f;
                }
            }
            if (IsKeyPressed(config.teclaChute1) && estado.jogador1->podeAtacar)
            {
                if (ExecutarAtaque(estado.jogador1, estado.jogador2, POSE_CHUTE, estado.jogador1->danoChute))
                {
                    estado.jogador1->poderAtual += 15;
                    if (estado.jogador1->poderAtual > PODER_MAXIMO)
                        estado.jogador1->poderAtual = PODER_MAXIMO;
                    Vector2 posImpacto = {estado.jogador2->posicao.x, estado.jogador2->posicao.y - 50};
                    CriarEfeitoImpacto(&estado.particulasImpacto, posImpacto, ORANGE, 20);
                    estado.tremor = 0.15f;
                }
            }

            // Ataques Player 2
            if (IsKeyPressed(config.teclaPoderP2) && estado.jogador2->poderAtual >= 50 && estado.jogador2->podeAtacar)
            {
                if (ExecutarAtaque(estado.jogador2, estado.jogador1, POSE_PODER, estado.jogador2->danoPoder))
                {
                    estado.jogador2->poderAtual = 0;
                    Vector2 posImpacto = {estado.jogador1->posicao.x, estado.jogador1->posicao.y - 50};
                    CriarEfeitoImpacto(&estado.particulasImpacto, posImpacto, estado.jogador2->corHabilidade, 30);
                    estado.flashTela = 0.4f;
                    estado.tremor = 0.3f;
                }
            }
            if (IsKeyPressed(config.teclaSocoP2) && estado.jogador2->podeAtacar)
            {
                if (ExecutarAtaque(estado.jogador2, estado.jogador1, POSE_SOCO, estado.jogador2->danoSoco))
                {
                    estado.jogador2->poderAtual += 10;
                    if (estado.jogador2->poderAtual > PODER_MAXIMO)
                        estado.jogador2->poderAtual = PODER_MAXIMO;
                    Vector2 posImpacto = {estado.jogador1->posicao.x, estado.jogador1->posicao.y - 50};
                    CriarEfeitoImpacto(&estado.particulasImpacto, posImpacto, YELLOW, 15);
                    estado.tremor = 0.1f;
                }
            }
            if (IsKeyPressed(config.teclaChute2) && estado.jogador2->podeAtacar)
            {
                if (ExecutarAtaque(estado.jogador2, estado.jogador1, POSE_CHUTE, estado.jogador2->danoChute))
                {
                    estado.jogador2->poderAtual += 15;
                    if (estado.jogador2->poderAtual > PODER_MAXIMO)
                        estado.jogador2->poderAtual = PODER_MAXIMO;
                    Vector2 posImpacto = {estado.jogador1->posicao.x, estado.jogador1->posicao.y - 50};
                    CriarEfeitoImpacto(&estado.particulasImpacto, posImpacto, ORANGE, 20);
                    estado.tremor = 0.15f;
                }
            }

            // Verificar fim de jogo
            if (estado.jogador1->vidaAtual <= 0 || estado.jogador2->vidaAtual <= 0)
            {
                // Mostrar vencedor por 2 segundos antes de voltar ao menu
                const char *vencedor = estado.jogador1->vidaAtual <= 0 ? estado.jogador2->nome : estado.jogador1->nome;
                Color corVencedor = estado.jogador1->vidaAtual <= 0 ? RED : BLUE;

                DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(BLACK, 0.7f));

                const char *textoVitoria = TextFormat("%s VENCEU!", vencedor);
                Vector2 tamanhoTexto = MeasureTextEx(fontePixel, textoVitoria, 72, 2);
                DrawTextEx(fontePixel, textoVitoria, (Vector2){LARGURA_TELA / 2 - tamanhoTexto.x / 2, ALTURA_TELA / 2 - 50}, 72, 2, corVencedor);

                DrawTextEx(fontePixel, "Voltando ao menu em instantes...", (Vector2){LARGURA_TELA / 2 - 200, ALTURA_TELA / 2 + 50}, 28, 2, WHITE);

                // Delay antes de voltar ao menu
                static float timerVitoria = 0;
                timerVitoria += GetFrameTime();

                if (timerVitoria > 3.0f || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
                {
                    timerVitoria = 0;
                    telaAtual = TELA_MENU;
                    estado.roundAtual = 1;
                    estado.tempoRound = TEMPO_ROUND;
                    estado.jogador1Confirmado = false;
                    estado.jogador2Confirmado = false;
                    estado.mapaConfirmado = false;

                    // Resetar todos os personagens
                    for (int i = 0; i < MAX_PERSONAGENS; i++)
                    {
                        InicializarPersonagem(&personagens[i], personagens[i].nome);
                    }
                }
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                telaAtual = TELA_MENU;
                estado.roundAtual = 1;
                estado.tempoRound = TEMPO_ROUND;
                estado.jogador1Confirmado = false;
                estado.jogador2Confirmado = false;
                estado.mapaConfirmado = false;

                // Resetar personagens ao sair da luta
                for (int i = 0; i < MAX_PERSONAGENS; i++)
                {
                    InicializarPersonagem(&personagens[i], personagens[i].nome);
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (telaAtual == TELA_MENU)
        {

            DrawTexturePro(fundoMenu,
                           (Rectangle){0, 0, (float)fundoMenu.width, (float)fundoMenu.height},
                           (Rectangle){0, 0, LARGURA_TELA, ALTURA_TELA},
                           (Vector2){0, 0}, 0.0f, WHITE);

            float escala = 0.5f;
            int posX = (LARGURA_TELA - (int)(logo.width * escala)) / 2;
            int posY = 70;

            DrawTexturePro(logo, (Rectangle){0, 0, (float)logo.width, (float)logo.height},
                           (Rectangle){posX, posY, logo.width * escala, logo.height * escala},
                           (Vector2){0, 0}, 0.0f, RAYWHITE);

            for (int i = 0; i < OPCOES_MENU; i++)
            {
                Color corTexto = (i == menuSelecionado) ? BLACK : WHITE;
                Color corCaixa = (i == menuSelecionado) ? Fade(YELLOW, 0.7f) : Fade(WHITE, 0.2f);

                const char *texto = menu[i].texto;
                int paddingY = 20;
                int larguraCaixa = 400;
                int alturaCaixa = tamanhoFonte + paddingY * 2;
                int bx = (LARGURA_TELA - larguraCaixa) / 2;
                int by = menu[i].posY - paddingY;

                DrawRectangleRounded((Rectangle){bx, by, larguraCaixa, alturaCaixa}, 0.3f, 10, corCaixa);

                Vector2 tamTexto = MeasureTextEx(fontePixel, texto, tamanhoFonte, 2);
                DrawTextEx(fontePixel, texto, (Vector2){(LARGURA_TELA - tamTexto.x) / 2, menu[i].posY}, tamanhoFonte, 2, corTexto);
            }
        }
        else if (telaAtual == TELA_OPCOES)
        {
            DesenharTelaOpcoes(&config, opcaoSelecionada, aguardandoTecla, fontePixel);
        }
        else if (telaAtual == TELA_SELECAO)
        {

            DrawTexturePro(fundoSelecao,
                           (Rectangle){0, 0, (float)fundoSelecao.width, (float)fundoSelecao.height},
                           (Rectangle){0, 0, LARGURA_TELA, ALTURA_TELA},
                           (Vector2){0, 0}, 0.0f, WHITE);

            DrawRectangleGradientV(0, 0, LARGURA_TELA, ALTURA_TELA,
                                   Fade(BLACK, 0.3f), Fade(BLACK, 0.6f));

            int metadeLargura = LARGURA_TELA / 2;
            int alturaPersonagens = 500;

            DrawRectangleRounded((Rectangle){20, 130, metadeLargura - 40, alturaPersonagens + 40}, 0.1f, 10, Fade(BLACK, 0.7f));
            DrawRectangleRounded((Rectangle){metadeLargura + 20, 130, metadeLargura - 40, alturaPersonagens + 40}, 0.1f, 10, Fade(BLACK, 0.7f));

            DrawRectangleRoundedLines((Rectangle){20, 130, metadeLargura - 40, alturaPersonagens + 40}, 0.1f, 10, estado.jogador1Confirmado ? GREEN : BLUE);
            DrawRectangleRoundedLines((Rectangle){metadeLargura + 20, 130, metadeLargura - 40, alturaPersonagens + 40}, 0.1f, 10, estado.jogador2Confirmado ? GREEN : RED);

            DesenharSelecaoPersonagem(personagens, selecionadoJogador1, 0, 150, metadeLargura, alturaPersonagens, estado.jogador1Confirmado ? GREEN : BLUE);
            DesenharSelecaoPersonagem(personagens, selecionadoJogador2, metadeLargura, 150, metadeLargura, alturaPersonagens, estado.jogador2Confirmado ? GREEN : RED);

            DrawRectangleRounded((Rectangle){20, 20, LARGURA_TELA - 40, 80}, 0.2f, 10, Fade(BLACK, 0.8f));
            DrawRectangleRoundedLines((Rectangle){20, 20, LARGURA_TELA - 40, 80}, 0.2f, 10, WHITE);

            const char *titulo = "SELECIONE SEU PERSONAGEM";
            Vector2 tamanhoTitulo = MeasureTextEx(fontePixel, titulo, 54, 2);
            DrawTextEx(fontePixel, titulo, (Vector2){LARGURA_TELA / 2 - tamanhoTitulo.x / 2, 40}, 54, 2, WHITE);

            // Status de confirmação com fontes melhoradas e estilização
            // Player 1 - Painel estilizado
            int larguraPainel = 350;
            int alturaPainel = 45;
            int xPlayer1 = 50;
            int yPlayer1 = 105;

            Color corFundoP1 = estado.jogador1Confirmado ? Fade(GREEN, 0.3f) : Fade(BLUE, 0.3f);
            Color corBordaP1 = estado.jogador1Confirmado ? GREEN : BLUE;
            Color corTextoP1 = estado.jogador1Confirmado ? GREEN : BLUE;

            DrawRectangleRounded((Rectangle){xPlayer1, yPlayer1, larguraPainel, alturaPainel}, 0.2f, 10, corFundoP1);
            DrawRectangleRoundedLines((Rectangle){xPlayer1, yPlayer1, larguraPainel, alturaPainel}, 0.2f, 10, corBordaP1);

            if (estado.jogador1Confirmado)
            {
                DrawTextEx(fontePixel, "✓ PLAYER 1 CONFIRMADO!", (Vector2){xPlayer1 + 15, yPlayer1 + 8}, 32, 2, corTextoP1);
            }
            else
            {
                DrawTextEx(fontePixel, "PLAYER 1 (A / D)", (Vector2){xPlayer1 + 15, yPlayer1 + 8}, 32, 2, corTextoP1);
            }

            // Player 2 - Painel estilizado
            int xPlayer2 = metadeLargura + 50;
            int yPlayer2 = 105;

            Color corFundoP2 = estado.jogador2Confirmado ? Fade(GREEN, 0.3f) : Fade(RED, 0.3f);
            Color corBordaP2 = estado.jogador2Confirmado ? GREEN : RED;
            Color corTextoP2 = estado.jogador2Confirmado ? GREEN : RED;

            DrawRectangleRounded((Rectangle){xPlayer2, yPlayer2, larguraPainel, alturaPainel}, 0.2f, 10, corFundoP2);
            DrawRectangleRoundedLines((Rectangle){xPlayer2, yPlayer2, larguraPainel, alturaPainel}, 0.2f, 10, corBordaP2);

            if (estado.jogador2Confirmado)
            {
                DrawTextEx(fontePixel, "✓ PLAYER 2 CONFIRMADO!", (Vector2){xPlayer2 + 15, yPlayer2 + 8}, 32, 2, corTextoP2);
            }
            else
            {
                DrawTextEx(fontePixel, "PLAYER 2 (← / →)", (Vector2){xPlayer2 + 15, yPlayer2 + 8}, 32, 2, corTextoP2);
            }

            int posYInfo = 680;
            DrawRectangleRounded((Rectangle){30, posYInfo, LARGURA_TELA - 60, 300}, 0.1f, 10, Fade(BLACK, 0.8f));
            DrawRectangleRoundedLines((Rectangle){30, posYInfo, LARGURA_TELA - 60, 300}, 0.1f, 10, WHITE);

            DrawLine(LARGURA_TELA / 2, posYInfo + 20, LARGURA_TELA / 2, posYInfo + 280, WHITE);

            DesenharInfoPersonagem(personagens[selecionadoJogador1], 50, posYInfo + 20, metadeLargura - 80, 260, fontePixel);
            DesenharInfoPersonagem(personagens[selecionadoJogador2], metadeLargura + 30, posYInfo + 20, metadeLargura - 80, 260, fontePixel);

            DrawRectangleRounded((Rectangle){30, ALTURA_TELA - 80, LARGURA_TELA - 60, 50}, 0.1f, 10, Fade(BLACK, 0.9f));
            DrawRectangleRoundedLines((Rectangle){30, ALTURA_TELA - 80, LARGURA_TELA - 60, 50}, 0.1f, 10, GRAY);

            if (!estado.jogador1Confirmado)
                DrawTextEx(fontePixel, "ENTER: Confirmar Player 1", (Vector2){50, ALTURA_TELA - 60}, 22, 2, BLUE);
            if (!estado.jogador2Confirmado)
                DrawTextEx(fontePixel, "SPACE: Confirmar Player 2", (Vector2){400, ALTURA_TELA - 60}, 22, 2, RED);

            if (estado.jogador1Confirmado && estado.jogador2Confirmado)
            {
                const char *textoTransicao = "Aguarde... Indo para seleção de mapa!";
                Vector2 tamanhoTexto = MeasureTextEx(fontePixel, textoTransicao, 28, 2);
                DrawTextEx(fontePixel, textoTransicao, (Vector2){LARGURA_TELA / 2 - tamanhoTexto.x / 2, ALTURA_TELA - 55}, 28, 2, YELLOW);
            }
            else
            {
                const char *textoVoltar = "BACKSPACE: Voltar ao menu";
                Vector2 tamanhoTexto = MeasureTextEx(fontePixel, textoVoltar, 22, 2);
                DrawTextEx(fontePixel, textoVoltar, (Vector2){LARGURA_TELA / 2 - tamanhoTexto.x / 2, ALTURA_TELA - 40}, 22, 2, WHITE);
            }
        }
        else if (telaAtual == TELA_SELECAO_MAPA)
        {
            DesenharTelaSelecaoMapa(mapas, mapaAtual, fontePixel);
        }
        else if (telaAtual == TELA_LUTA)
        {
            int offsetTremor = 0;
            if (estado.tremor > 0)
            {
                offsetTremor = (int)(estado.tremor * 20 * sin(GetTime() * 50));
            }

            DrawTexturePro(estado.mapaAtual->textura,
                           (Rectangle){0, 0, (float)estado.mapaAtual->textura.width, (float)estado.mapaAtual->textura.height},
                           (Rectangle){offsetTremor, offsetTremor, LARGURA_TELA, ALTURA_TELA},
                           (Vector2){0, 0}, 0.0f, WHITE);

            // === RENDERIZAÇÃO MELHORADA DOS PERSONAGENS ===

            // Configurações base para renderização
            float larguraPersonagemBase = 200.0f; // Aumentado para melhor visibilidade
            float alturaPersonagemBase = 280.0f;  // Aumentado para melhor visibilidade

            // Player 1 - Posicionamento e renderização
            float larguraP1 = larguraPersonagemBase;
            float alturaP1 = alturaPersonagemBase;

            // Centralizar personagem no chão
            float renderXP1 = estado.jogador1->posicao.x - larguraP1 / 2;
            float renderYP1 = estado.chao - alturaP1;

            Rectangle destP1 = {renderXP1, renderYP1, larguraP1, alturaP1};
            Vector2 origemP1 = {0, 0};

            // Aplicar flip horizontal se necessário
            if (!estado.jogador1->viradoParaDireita)
            {
                destP1.width = -larguraP1;
                origemP1.x = larguraP1;
            }

            // Player 2 - Posicionamento e renderização
            float larguraP2 = larguraPersonagemBase;
            float alturaP2 = alturaPersonagemBase;

            float renderXP2 = estado.jogador2->posicao.x - larguraP2 / 2;
            float renderYP2 = estado.chao - alturaP2;

            Rectangle destP2 = {renderXP2, renderYP2, larguraP2, alturaP2};
            Vector2 origemP2 = {0, 0};

            if (!estado.jogador2->viradoParaDireita)
            {
                destP2.width = -larguraP2;
                origemP2.x = larguraP2;
            }

            // === EFEITOS VISUAIS MELHORADOS ===

            // Sombras dos personagens (mais visíveis)
            Color corSombra = Fade(BLACK, 0.4f);
            DrawEllipse((int)estado.jogador1->posicao.x, (int)(estado.chao + 5), (int)(larguraP1 * 0.5f), 20, corSombra);
            DrawEllipse((int)estado.jogador2->posicao.x, (int)(estado.chao + 5), (int)(larguraP2 * 0.5f), 20, corSombra);

            // Obter texturas corretas - usar sempre a texturaLuta que é a principal
            Texture2D texturaPlayer1 = estado.jogador1->texturaLuta;
            Texture2D texturaPlayer2 = estado.jogador2->texturaLuta;

            // Source rectangle simples - usar textura completa
            Rectangle sourcePlayer1 = {0, 0, (float)texturaPlayer1.width, (float)texturaPlayer1.height};
            Rectangle sourcePlayer2 = {0, 0, (float)texturaPlayer2.width, (float)texturaPlayer2.height};

            // Cores dos personagens
            Color corPlayer1 = WHITE;
            Color corPlayer2 = WHITE;

            // Renderizar personagens com as texturas corretas
            DrawTexturePro(texturaPlayer1, sourcePlayer1, destP1, origemP1, 0.0f, corPlayer1);
            DrawTexturePro(texturaPlayer2, sourcePlayer2, destP2, origemP2, 0.0f, corPlayer2);

            // Auras de poder melhoradas
            if (estado.jogador1->poseAtual == POSE_PODER && estado.jogador1->animando)
            {
                float raioAura = 60 + 15 * sin(GetTime() * 12);
                Vector2 centroAura = {estado.jogador1->posicao.x, estado.jogador1->posicao.y - 80};

                // Múltiplos círculos para efeito de aura
                for (int i = 0; i < 3; i++)
                {
                    float alpha = (0.4f - i * 0.1f) * sin(GetTime() * 8 + i);
                    DrawCircleLines((int)centroAura.x, (int)centroAura.y, raioAura + i * 10,
                                    Fade(estado.jogador1->corHabilidade, fabs(alpha)));
                }
            }

            if (estado.jogador2->poseAtual == POSE_PODER && estado.jogador2->animando)
            {
                float raioAura = 60 + 15 * sin(GetTime() * 12);
                Vector2 centroAura = {estado.jogador2->posicao.x, estado.jogador2->posicao.y - 80};

                for (int i = 0; i < 3; i++)
                {
                    float alpha = (0.4f - i * 0.1f) * sin(GetTime() * 8 + i);
                    DrawCircleLines((int)centroAura.x, (int)centroAura.y, raioAura + i * 10,
                                    Fade(estado.jogador2->corHabilidade, fabs(alpha)));
                }
            }

            // Desenhar hitboxes para debug (opcional - remover depois)
            if (true) // Mude para true para ver as hitboxes
            {
                DrawRectangleLines((int)estado.jogador1->hitbox.x, (int)estado.jogador1->hitbox.y,
                                   (int)estado.jogador1->hitbox.width, (int)estado.jogador1->hitbox.height, GREEN);
                DrawRectangleLines((int)estado.jogador2->hitbox.x, (int)estado.jogador2->hitbox.y,
                                   (int)estado.jogador2->hitbox.width, (int)estado.jogador2->hitbox.height, RED);

                // Desenhar alcance de ataque se atacando
                if (estado.jogador1->poseAtual == POSE_SOCO || estado.jogador1->poseAtual == POSE_CHUTE || estado.jogador1->poseAtual == POSE_PODER)
                {
                    AtualizarAlcanceAtaque(estado.jogador1);
                    DrawRectangleLines((int)estado.jogador1->alcanceAtaque.x, (int)estado.jogador1->alcanceAtaque.y,
                                       (int)estado.jogador1->alcanceAtaque.width, (int)estado.jogador1->alcanceAtaque.height, BLUE);
                }
                if (estado.jogador2->poseAtual == POSE_SOCO || estado.jogador2->poseAtual == POSE_CHUTE || estado.jogador2->poseAtual == POSE_PODER)
                {
                    AtualizarAlcanceAtaque(estado.jogador2);
                    DrawRectangleLines((int)estado.jogador2->alcanceAtaque.x, (int)estado.jogador2->alcanceAtaque.y,
                                       (int)estado.jogador2->alcanceAtaque.width, (int)estado.jogador2->alcanceAtaque.height, YELLOW);
                }
            }

            DesenharParticulas(&estado.particulasImpacto);

            DesenharHUD(&estado, fontePixel);

            if (estado.flashTela > 0)
            {
                Color corFlash = Fade(WHITE, estado.flashTela);
                DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, corFlash);
            }

            // Painel de controles melhorado
            DrawRectangleRounded((Rectangle){30, ALTURA_TELA - 140, LARGURA_TELA - 60, 110}, 0.1f, 10, Fade(BLACK, 0.8f));
            DrawRectangleRoundedLines((Rectangle){30, ALTURA_TELA - 140, LARGURA_TELA - 60, 110}, 0.1f, 10, WHITE);

            const char *controlesP1 = TextFormat("P1: %s/%s=Mover | %s=Soco | %s=Chute | %s=ESPECIAL",
                                                 ObterNomeTecla(config.teclaEsquerdaP1),
                                                 ObterNomeTecla(config.teclaDireitaP1),
                                                 ObterNomeTecla(config.teclaSocoP1),
                                                 ObterNomeTecla(config.teclaChute1),
                                                 ObterNomeTecla(config.teclaPoderP1));
            DrawTextEx(fontePixel, controlesP1, (Vector2){50, ALTURA_TELA - 125}, 16, 2, BLUE);

            const char *controlesP2 = TextFormat("P2: %s/%s=Mover | %s=Soco | %s=Chute | %s=ESPECIAL",
                                                 ObterNomeTecla(config.teclaEsquerdaP2),
                                                 ObterNomeTecla(config.teclaDireitaP2),
                                                 ObterNomeTecla(config.teclaSocoP2),
                                                 ObterNomeTecla(config.teclaChute2),
                                                 ObterNomeTecla(config.teclaPoderP2));
            DrawTextEx(fontePixel, controlesP2, (Vector2){50, ALTURA_TELA - 105}, 16, 2, RED);

            DrawTextEx(fontePixel, "APROXIME-SE do oponente para atacar! Acumule poder com ataques básicos!", (Vector2){50, ALTURA_TELA - 85}, 18, 2, YELLOW);

            DrawTextEx(fontePixel, "ESC: Voltar ao menu", (Vector2){LARGURA_TELA / 2 - 100, ALTURA_TELA - 45}, 16, 2, LIGHTGRAY);
        }

        EndDrawing();
    }

    for (int i = 0; i < MAX_PERSONAGENS; i++)
    {
        UnloadTexture(personagens[i].textura);
        UnloadTexture(personagens[i].texturaLuta);
    }

    for (int i = 0; i < MAX_MAPAS; i++)
    {
        UnloadTexture(mapas[i].textura);
    }

    UnloadTexture(fundoMenu);
    UnloadTexture(fundoSelecao);
    UnloadTexture(logo);
    UnloadFont(fontePixel);

    UnloadMusicStream(musicaFundo);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}