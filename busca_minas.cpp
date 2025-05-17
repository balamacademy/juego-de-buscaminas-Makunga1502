#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX = 10; 
int tablero[MAX][MAX];        
char visible[MAX][MAX];       
int filas, columnas, minas;


void inicializarTableros() {
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = 0;
            visible[i][j] = '-';
        }
}


void generarMinas() {
    int colocadas = 0;
    while (colocadas < minas) {
        int f = rand() % filas;
        int c = rand() % columnas;
        if (tablero[f][c] != -1) {
            tablero[f][c] = -1;
            colocadas++;
        }
    }
}


void contarAdyacentes() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tablero[i][j] == -1) continue;
            int cuenta = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas && tablero[ni][nj] == -1)
                        cuenta++;
                }
            }
            tablero[i][j] = cuenta;
        }
    }
}


void mostrarVisible() {
    cout << "   ";
    for (int j = 0; j < columnas; j++) cout << j << " ";
    cout << "\n";
    for (int i = 0; i < filas; i++) {
        cout << i << "  ";
        for (int j = 0; j < columnas; j++) {
            cout << visible[i][j] << " ";
        }
        cout << "\n";
    }
}


void mostrarTableroReal() {
    cout << "   ";
    for (int j = 0; j < columnas; j++) cout << j << " ";
    cout << "\n";
    for (int i = 0; i < filas; i++) {
        cout << i << "  ";
        for (int j = 0; j < columnas; j++) {
            if (tablero[i][j] == -1)
                cout << "* ";
            else
                cout << tablero[i][j] << " ";
        }
        cout << "\n";
    }
}


void destapar(int f, int c) {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) return;
    if (visible[f][c] != '-') return;

    if (tablero[f][c] == -1) {
        visible[f][c] = '*';
    } else {
        visible[f][c] = tablero[f][c] + '0';
        if (tablero[f][c] == 0) {
            visible[f][c] = ' ';
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if (di != 0 || dj != 0)
                        destapar(f + di, c + dj);
        }
    }
}


bool jugadorGana() {
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            if (visible[i][j] == '-' && tablero[i][j] != -1)
                return false;
    return true;
}

int main() {
    srand(time(NULL));
    cout << "Ingrese las dimensiones del tablero (filas columnas): ";
    cin >> filas >> columnas;

    if (filas > MAX || columnas > MAX || filas <= 0 || columnas <= 0) {
        cout << "Dimensiones invalidas (maximo " << MAX << "x" << MAX << ")\n";
        return 1;
    }

    minas = columnas + 1;
    inicializarTableros();
    generarMinas();
    contarAdyacentes();

    cout << "\nTablero generado (oculto)... presiona Enter para comenzar...";
    cin.ignore();
    cin.get();
    system("cls");

    int fila, columna;
    while (true) {
        mostrarVisible();
        cout << "Ingresa la coordenada para destapar (fila y columna): ";
        cin >> fila >> columna;

        if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
            cout << "Coordenadas invalidas.\n";
            continue;
        }

        if (tablero[fila][columna] == -1) {
            system("cls");
            cout << "Explotaste\n";
            mostrarTableroReal();
            break;
        }

        destapar(fila, columna);
        system("cls");

        if (jugadorGana()) {
            cout << "Ganaste\n";
            mostrarTableroReal();
            break;
        }
    }

    return 0;
}
