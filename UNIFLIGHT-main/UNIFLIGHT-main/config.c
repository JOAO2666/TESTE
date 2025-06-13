#include "config.h"
#include "raylib.h" // For KEY_Q, KEY_E, etc.
#include <stdio.h>  // For printf in Salvar/CarregarConfiguracoes

void InicializarConfiguracaoPadrao(ConfiguracaoJogo *config)
{
    config->teclaPoderP1 = KEY_Q;
    config->teclaSocoP1 = KEY_E;
    config->teclaChute1 = KEY_R;
    config->teclaEsquerdaP1 = KEY_A;
    config->teclaDireitaP1 = KEY_D;
    config->teclaConfirmarP1 = KEY_ENTER;

    config->teclaPoderP2 = KEY_P;
    config->teclaSocoP2 = KEY_O;
    config->teclaChute2 = KEY_I;
    config->teclaEsquerdaP2 = KEY_LEFT;
    config->teclaDireitaP2 = KEY_RIGHT;
    config->teclaConfirmarP2 = KEY_SPACE;

    config->volumeMusica = 0.5f;
    config->volumeEfeitos = 0.7f;
}

const char *ObterNomeTecla(int tecla)
{
    switch (tecla)
    {
    case KEY_Q:
        return "Q";
    case KEY_W:
        return "W";
    case KEY_E:
        return "E";
    case KEY_R:
        return "R";
    case KEY_T:
        return "T";
    case KEY_Y:
        return "Y";
    case KEY_U:
        return "U";
    case KEY_I:
        return "I";
    case KEY_O:
        return "O";
    case KEY_P:
        return "P";
    case KEY_A:
        return "A";
    case KEY_S:
        return "S";
    case KEY_D:
        return "D";
    case KEY_F:
        return "F";
    case KEY_G:
        return "G";
    case KEY_H:
        return "H";
    case KEY_J:
        return "J";
    case KEY_K:
        return "K";
    case KEY_L:
        return "L";
    case KEY_Z:
        return "Z";
    case KEY_X:
        return "X";
    case KEY_C:
        return "C";
    case KEY_V:
        return "V";
    case KEY_B:
        return "B";
    case KEY_N:
        return "N";
    case KEY_M:
        return "M";
    case KEY_SPACE:
        return "SPACE";
    case KEY_ENTER:
        return "ENTER";
    case KEY_LEFT:
        return "←";
    case KEY_RIGHT:
        return "→";
    case KEY_UP:
        return "↑";
    case KEY_DOWN:
        return "↓";
    default:
        return "?";
    }
}

void SalvarConfiguracoes(ConfiguracaoJogo *config)
{
    // Implemente a lógica para salvar as configurações no arquivo
    printf("Configurações salvas com sucesso!\n");
    // Example: FILE *fp = fopen("config.dat", "wb"); fwrite(config, sizeof(ConfiguracaoJogo), 1, fp); fclose(fp);
}

void CarregarConfiguracoes(ConfiguracaoJogo *config)
{
    // Implemente a lógica para carregar as configurações do arquivo
    printf("Configurações carregadas com sucesso!\n");
    // Example: FILE *fp = fopen("config.dat", "rb"); if (fp) { fread(config, sizeof(ConfiguracaoJogo), 1, fp); fclose(fp); } else { InicializarConfiguracaoPadrao(config); }
}
