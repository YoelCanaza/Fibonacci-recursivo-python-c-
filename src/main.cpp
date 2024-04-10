#include <iostream>
#include <vector>
#include <string> 
#include "raylib.h"

using namespace std;

unsigned long long fibonacciRecursivo(int n) {
    if (n <= 0) return 0;
    else if (n == 1) return 1;
    else return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

double medirTiempoFibonacci(int n) {
    double startTime = GetTime();
    fibonacciRecursivo(n);
    double endTime = GetTime();
    return endTime - startTime;
}

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 1024;

    InitWindow(screenWidth, screenHeight, "Tiempo de Ejecucion de Fibonacci Recursivo");

    
    const int maxTerm = 45; // Analizaremos hasta el término 40 por motivos de tiempo
    vector<int> nValues;
    vector<double> executionTimes;

    for (int n = 1; n <= maxTerm; ++n) {
        nValues.push_back(n);
        double executionTime = medirTiempoFibonacci(n);
        executionTimes.push_back(executionTime);
        cout << "Termino " << n << ": Tiempo = " << executionTime << " segundos" << endl;
    }

    SetTargetFPS(60); 

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar gráfico de tiempo de ejecución vs término enésimo
        int margin = 50;
        int plotWidth = screenWidth - 2 * margin;
        int plotHeight = screenHeight - 2 * margin;

        // Dibujar ejes
        DrawLine(margin, screenHeight - margin, screenWidth - margin, screenHeight - margin, BLACK); // Eje X
        DrawLine(margin, margin, margin, screenHeight - margin, BLACK); // Eje Y

        // Dibujar puntos y mostrar valores
        for (size_t i = 0; i < nValues.size(); ++i) {
            float x = margin + static_cast<float>(i) * (plotWidth / static_cast<float>(nValues.size() - 1));
            float y = screenHeight - margin - static_cast<float>(executionTimes[i]) * (plotHeight / static_cast<float>(executionTimes.back()));
            DrawCircle(static_cast<int>(x), static_cast<int>(y), 5, RED);


            string termText = to_string(nValues[i]);
            DrawText(termText.c_str(), static_cast<int>(x) - MeasureText(termText.c_str(), 10) / 2, screenHeight - margin + 10, 10, BLACK);
           
            string timeText = to_string(static_cast<int>(executionTimes[i])) + "s";
            DrawText(timeText.c_str(), margin - 40, static_cast<int>(y) - 5, 10, BLACK);
        }

        
        DrawText("Termino enesimo (n)", screenWidth / 2 - 100, screenHeight - margin + 20, 12, BLACK); // Etiqueta eje X
        DrawText("Tiempo de ejecucion (segundos)", margin - 120, margin + 20, 12, BLACK); // Etiqueta eje Y

        EndDrawing();
    }

    CloseWindow();
    return 0;
}