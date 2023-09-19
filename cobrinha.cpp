#ifdef _WIN32
#define WINDOWS_SYSTEM
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream> //Funções para "printar" coisas.
#include <stdlib.h> //Funções para randomização.
#include <time.h>  //Funções para checar o tempo atual.
#include <conio.h> //Funções para usar o teclado.

using namespace std;

//Usado para criar a cobra.
struct Cobra
{
    int x;
    int y;
    char estencao;
};
struct Cobra cobra[50];
int tamanho = 1;

//Informações da Grid.
const int gridLenght = 20;
const int gridHeight = 20;
char grid[gridLenght][gridHeight];

bool endGame = false;
bool gameOver = false;
char direcao = 'd';
int score = 0;
int bestScore = 0;

//Cria a grid inicial.
void criarGrid() {
    for (int i = 0; i < gridLenght; i++) {
        for (int ii = 0; ii < gridHeight; ii++) {
            switch (i) {
            case 0:
                switch (ii) {
                case 0:
                    grid[i][ii] = '-';
                    break;
                case gridHeight - 1:
                    grid[i][ii] = '-';
                    break;

                default:
                    grid[i][ii] = '|';
                }
                break;
            case gridLenght - 1:
                switch (ii) {
                case 'a':
                    if (direcao != 'd') {
                        direcao = 'a';
                    } break;  case 0:
                        grid[i][ii] = '-';
                        break;
                    case gridHeight - 1:
                        grid[i][ii] = '-';
                        break;

                    default:
                        grid[i][ii] = '|';
                }
                break;

            default:
                switch (ii) {
                case 0:
                    grid[i][ii] = '-';
                    break;
                case gridHeight - 1:
                    grid[i][ii] = '-';
                    break;

                default:
                    grid[i][ii] = ' ';
                }
            }
        }
    }
}

//Gera a frutinha para ser comida.
void gerarFruta() {
    int i = rand() % 10;
    int ii = rand() % 10;

    while (grid[i][ii] != ' ') {
        i = rand() % 10;
        ii = rand() % 10;
    }
    if (grid[i][ii] == ' ') {
        grid[i][ii] = 'o';
    }
}

void crescerCobra() {
    if (grid[cobra[tamanho - 2].x - 1][cobra[tamanho - 2].y - 1] == ' ') {
        cobra[tamanho - 1].x = cobra[tamanho - 2].x - 1;
        cobra[tamanho - 1].y = cobra[tamanho - 2].y - 1;
    }
    else {
        if (grid[cobra[tamanho - 2].x + 1][cobra[tamanho - 2].y + 1] == ' ') {
            cobra[tamanho - 1].x = cobra[tamanho - 2].x + 1;
            cobra[tamanho - 1].y = cobra[tamanho - 2].y + 1;
        }
        else {
            if (grid[cobra[tamanho - 2].x - 1][cobra[tamanho - 2].y + 1] == ' ') {
                cobra[tamanho - 1].x = cobra[tamanho - 2].x - 1;
                cobra[tamanho - 1].y = cobra[tamanho - 2].y + 1;
            }
            else {
                if (grid[cobra[tamanho - 2].x + 1][cobra[tamanho - 2].y - 1] == ' ') {
                    cobra[tamanho - 1].x = cobra[tamanho - 2].x + 1;
                    cobra[tamanho - 1].y = cobra[tamanho - 2].y - 1;
                }
            }
        }
    }
    cobra[tamanho - 1].estencao = '-';
}

void LerTeclado() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'd':
            if (direcao != 'a') {
                direcao = 'd';
                cobra[0].estencao = '>';
            } break;

        case 'a':
            if (direcao != 'd') {
                direcao = 'a';
                cobra[0].estencao = '<';
            } break;

        case 'w':
            if (direcao != 's') {
                direcao = 'w';
                cobra[0].estencao = '^';
            } break;

        case 's':
            if (direcao != 'w') {
                direcao = 's';
                cobra[0].estencao = 'v';
            } break;

        default:
            break;
        }
    }
}

//Transfere o corpo da cobra na direção da cabeça.
void moverCobra() {
    grid[cobra[tamanho - 1].x][cobra[tamanho - 1].y] = ' ';
    for (int i = tamanho - 1; i > 0; i--) {
        cobra[i].x = cobra[i - 1].x;
        cobra[i].y = cobra[i - 1].y;
    }
}

//Move a cobra conforma a direção atual.
void cobraAndando() {
    switch (direcao) {
    case 'd':
        if (grid[cobra[0].x + 1][cobra[0].y] == ' ') {
            moverCobra();
            cobra[0].x++;
        }
        else if (grid[cobra[0].x + 1][cobra[0].y] == 'o') {
            moverCobra();
            cobra[0].x++;
            score++;
            tamanho++;
            gerarFruta();
            crescerCobra();
        }
        else {
            gameOver = true;
        }
        break;

    case 'a':
        if (grid[cobra[0].x - 1][cobra[0].y] == ' ') {
            moverCobra();
            cobra[0].x--;
        }
        else if (grid[cobra[0].x - 1][cobra[0].y] == 'o') {
            moverCobra();
            cobra[0].x--;
            score++;
            tamanho++;
            gerarFruta();
            crescerCobra();
        }
        else {
            gameOver = true;
        }
        break;

    case 'w':
        if (grid[cobra[0].x][cobra[0].y - 1] == ' ') {
            moverCobra();
            cobra[0].y--;
        }
        else if (grid[cobra[0].x][cobra[0].y - 1] == 'o') {
            moverCobra();
            cobra[0].y--;
            score++;
            tamanho++;
            gerarFruta();
            crescerCobra();
        }
        else {
            gameOver = true;
        }
        break;

    case 's':
        if (grid[cobra[0].x][cobra[0].y + 1] == ' ') {
            moverCobra();
            cobra[0].y++;
        }
        else if (grid[cobra[0].x][cobra[0].y + 1] == 'o') {
            moverCobra();
            cobra[0].y++;
            score++;
            tamanho++;
            gerarFruta();
            crescerCobra();
        }
        else {
            gameOver = true;
        }
        break;

    default:
        break;
    }
}

//Coloca a cobra na grid.
void realocarCobra() {
    for (int i = 0; i < tamanho; i++) {
        grid[cobra[i].x][cobra[i].y] = cobra[i].estencao;
    }
}

//Desenha a grid.
void desenhar() {
    for (int i = 0; i < gridHeight; i++) {
        for (int ii = 0; ii < gridLenght; ii++) {
            cout << grid[ii][i];
        }
        cout << "\n";
    }
    cout << "Pontos atuais: " << score;
}

int main()
{
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, A SEGUIR.
    //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    //IN�CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

    //Recebe a entrada e saída padrão.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    do {
        //Semente para a randomização.
        srand((unsigned)time(NULL));

        //Cabeça da cobra.
        cobra[0].x = 6;
        cobra[0].y = 3;
        cobra[0].estencao = '>';

        //Começo.
        criarGrid();
        gerarFruta();
        realocarCobra();
        desenhar();

        do {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            LerTeclado();
            cobraAndando();
            realocarCobra();
            desenhar();
#ifdef WINDOWS_SYSTEM
            Sleep(50);
#else
            usleep(50);
#endif
        } while (!gameOver);

        if (score > bestScore) {
            bestScore = score;
        }

        cout << "\nClique 'n' para encerrar e 's' para reinciar o jogo.";
        cout << "\nMelhor pontuacao: " << bestScore << "!\n";

        char tecla = ' ';
        do {
            if (_kbhit()) {
                tecla = _getch();
                if (tecla == 'n') {
                    endGame = true;
                }
                else if (tecla == 's') {
                    gameOver = false;
                    tamanho = 1;
                    direcao = 'd';
                    score = 0;
                    system("cls");
                }
            }
        } while (tecla != 's' && tecla != 'n');

    } while (!endGame);

    return 0;
}
