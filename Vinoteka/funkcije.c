#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "vinoteka.h"


int izbornik(void) {

	int odabir = -1;

	printf("====EVIDENCIJA VINOTEKE====\n");
	printf("1) Dodaj vino\n");
	printf("2) Ispisi sva vina\n");
	printf("3) Pretrazi vino\n");
	printf("4) Sortiraj vina\n");
	printf("5) Obrisi vino\n");
	printf("0) Izlaz\n");
	printf("Vas odabir: ");
	do {
		scanf("%d", &odabir);
	} while (odabir < 0 || odabir>5);

	return odabir;

}


void dodajNovoVino(VINO** katalogVina, int* brojVina)
{
    if (katalogVina == NULL || brojVina == NULL) {
        printf("Greska s pokazivacima!\n");
        return;
    }

    VINO* temp = realloc(*katalogVina, (*brojVina + 1) * sizeof(VINO));

    if (temp == NULL) {
        perror("Neuspjesna alokacija memorije");
        return;
    }

    *katalogVina = temp;

    VINO* novoVino = &((*katalogVina)[*brojVina]);

    novoVino->id = *brojVina + 1;

    printf("\nUnesite naziv vina: ");
    scanf(" %49[^\n]", novoVino->naziv);

    printf("Unesite naziv vinarije: ");
    scanf(" %49[^\n]", novoVino->vinarija);

    printf("Unesite godinu vina: ");
    scanf("%d", &novoVino->godina);

    printf("Unesite cijenu vina: ");
    scanf("%f", &novoVino->cijena);

    printf("Unesite kolicinu vina: ");
    scanf("%d", &novoVino->kolicina);

    (*brojVina)++;

    printf("\nVino uspjesno dodano!\n");
}

int usporediCijene(const void* a, const void* b)
{
    const VINO* vinoA = (const VINO*)a;
    const VINO* vinoB = (const VINO*)b;

    if (vinoA->cijena > vinoB->cijena)
        return 1;

    if (vinoA->cijena < vinoB->cijena)
        return -1;

    return 0;
}

void sortirajVinaPoCijeni(VINO* katalogVina, int brojVina)
{
    if (katalogVina == NULL || brojVina <= 0) {
        printf("Nema vina za sortiranje!\n");
        return;
    }

    qsort(
        katalogVina,
        brojVina,
        sizeof(VINO),
        usporediCijene
    );

    printf("\nVina uspjesno sortirana po cijeni!\n");
}

void ispisiSvaVina(const VINO* katalogVina, int brojVina)
{
    if (katalogVina == NULL || brojVina <= 0) {
        printf("\nVinoteka je prazna!\n");
        return;
    }

    printf("\n===== POPIS VINA =====\n");

    for (int i = 0; i < brojVina; i++) {

        printf("\nVino %d\n", i + 1);
        printf("ID: %d\n", katalogVina[i].id);
        printf("Naziv: %s\n", katalogVina[i].naziv);
        printf("Vinarija: %s\n", katalogVina[i].vinarija);
        printf("Godina: %d\n", katalogVina[i].godina);
        printf("Cijena: %.2f EUR\n", katalogVina[i].cijena);
        printf("Kolicina: %d\n", katalogVina[i].kolicina);
    }

    printf("\n======================\n");
}

void obrisiJednoVino(VINO** katalogVina, int* brojVina)
{
    if (katalogVina == NULL || brojVina == NULL || *katalogVina == NULL) {
        printf("\nNema vina za brisanje!\n");
        return;
    }

    if (*brojVina <= 0) {
        printf("\nVinoteka je prazna!\n");
        return;
    }

    int id;
    int pronaden = 0;

    printf("\nUnesite ID vina za brisanje: ");
    scanf("%d", &id);

    for (int i = 0; i < *brojVina; i++) {

        if ((*katalogVina)[i].id == id) {

            pronaden = 1;

            for (int j = i; j < *brojVina - 1; j++) {
                (*katalogVina)[j] = (*katalogVina)[j + 1];
            }

            (*brojVina)--;

            if (*brojVina == 0) {

                free(*katalogVina);
                *katalogVina = NULL;
            }
            else {

                VINO* temp = realloc(*katalogVina, (*brojVina) * sizeof(VINO));

                if (temp != NULL) {
                    *katalogVina = temp;
                }
            }

            printf("\nVino uspjesno obrisano!\n");
            break;
        }
    }

    if (!pronaden) {
        printf("\nVino s tim ID-em ne postoji!\n");
    }
}