#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct ProbaMocy {
    char czas[30];
    float moc_w;
};
int main() {
    struct ProbaMocy p[8];
    int n = 8;
    float dt = 15.0;
    float e_trapezy = 0.0;
    float suma_mocy = 0.0;

    srand(time(NULL));


    for (int i = 0; i < n; i++) {

        p[i].moc_w = 100 + rand() % 701;

        time_t currentTime;
        time(&currentTime);
        strcpy(p[i].czas, ctime(&currentTime));
        p[i].czas[strcspn(p[i].czas, "\n")] = '\0';

        suma_mocy += p[i].moc_w;
    }

    for (int i = 0; i <= n - 2; i++) {
        e_trapezy += ((p[i].moc_w + p[i + 1].moc_w) / 2.0) * (dt / 60.0) * (1.0 / 1000.0);
    }

    float srednia_moc = suma_mocy / n;
    float calkowity_czas_h = ((n - 1) * dt) / 60.0;
    float e_srednia = (srednia_moc * calkowity_czas_h) / 1000.0;
    printf("Nr  Data i godzina            Moc [W]\n");
    for (int i = 0; i < n; i++) {
        printf("%-2d  %-25s  %6.1f W\n", i + 1, p[i].czas, p[i].moc_w);
    }


    printf("\nPODSUMOWANIE\n");
    printf("Energia (metoda trapezow):   %.4f kWh\n", e_trapezy);
    printf("Energia (ze sredniej mocy):  %.4f kWh\n", e_srednia);

    return 0;
}