#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct Pomiar {
    char data[11];
    char godzina[6];
    float temperatura;
    float cisnienie;
    float wilgotnosc;
};

struct Stacja {
    int id;
    char nazwa[40];
    char lokalizacja[60];
};

struct Rekord {
    struct Stacja stacja;
    struct Pomiar pomiar;
};

int main() {
    struct Stacja st[2] = {{1, "Wrzeszcz", "Dymowskiego 2"}, {2, "Przymorze", "Kołobrzeska 7"}};
    struct Pomiar p1 = {"2026-10-20", "09:50", 10.0, 1005.0, 60.0};
    struct Rekord dane[50];
    int n = 10;

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        dane[i].stacja = st[i % 2];
        dane[i].pomiar.temperatura = rand() % 60 - 30;
        dane[i].pomiar.cisnienie = 900 + rand() % 40;
        dane[i].pomiar.wilgotnosc = 30 + rand() % 60;
       strcpy(dane[i].pomiar.data, "2026.10.20");
       sprintf(dane[i].pomiar.godzina, "%02d:00", 8 + i);
       
    }

    printf("id: %d, nazwa: %s, lokalizacja: %s\n", st[0].id, st[0].nazwa, st[0].lokalizacja);
    printf("id: %d, nazwa: %s, lokalizacja: %s\n", st[1].id, st[1].nazwa, st[1].lokalizacja);
    printf("%s %s t: %.2f, h: %.2f, p: %.2f\n\n", p1.data, p1.godzina, p1.temperatura, p1.wilgotnosc, p1.cisnienie);

    float min_temp = dane[0].pomiar.temperatura;
    float max_temp = dane[0].pomiar.temperatura;
    float suma_wilg = 0.0f;
    float suma_cisn = 0.0f;

    for (int i = 0; i < n; i++) {
        if (dane[i].pomiar.temperatura < min_temp) {
            min_temp = dane[i].pomiar.temperatura;
        }
        if (dane[i].pomiar.temperatura > max_temp) {
            max_temp = dane[i].pomiar.temperatura;
        }
        suma_wilg += dane[i].pomiar.wilgotnosc;
        suma_cisn += dane[i].pomiar.cisnienie;
    }
    printf("%-15s | %-10s | %-7s | %-8s | %-8s | %-8s\n",
           "Nazwa (ID)", "Data", "Godzina", "T [C]", "RH [%]", "P [hPa]");
    for (int i = 0; i < n; i++) {
        char id_nazwa[45];
        sprintf(id_nazwa, "%s (%d)", dane[i].stacja.nazwa, dane[i].stacja.id);

        printf("%-15s | %-10s | %-7s | %8.2f | %8.2f | %8.2f\n",
               id_nazwa,
               dane[i].pomiar.data,
               dane[i].pomiar.godzina,
               dane[i].pomiar.temperatura,
               dane[i].pomiar.wilgotnosc,
               dane[i].pomiar.cisnienie);
    }
    
    printf("Minimalna temperatura: %.2f C\n", min_temp);
    printf("Maksymalna temperatura: %.2f C\n", max_temp);
    printf("Srednia wilgotnosc:     %.2f %%\n", suma_wilg / n);
    printf("Srednie cisnienie:      %.2f hPa\n", suma_cisn / n);
    return 0;
}