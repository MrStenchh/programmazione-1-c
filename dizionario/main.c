#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/***************************************************************************************
 * FINALITA' DEL PROGRAMMA:
 * IL PROGRAMMA SIMULA LA FESTIONE DI UN DIZIONARIO DELLA LINGUA ITALIANA
 * LE PAROLE SONO ORGANIZZATE IN MODO MATRICIALE IN BASE ALLA LETTERA INIZIALE
 * OGNI PAROLA PUO' CONTENERE FINO AD UN MAX DI 5 CONTRARI
 * IL PROGRAMMA PERMETTE LA RICERCA DEI CONTRARI TRAMITE L'ALGORITMO DI RIERCA BINARIA
 * *************************************************************************************/
 
/* DEFINISCO LE STRUTTURE CHE MI OCCORRONO */

typedef struct{
    char termine[30];
    char contrari[5][30];
    int n_contrari;
} Parola;

typedef struct{
    Parola voci[100];
    int n_voci;
} Sezione;

typedef struct{
    Sezione lettere[30];
} Dizionario;

/* FUNZIONE DIZIONARIO
INIZIALIZZA IL DIZIONARIO, IMPOSTA A ZERO IL CONTATORE DI PAROLE PER OGNI SEZIONE DEL DIZIONARIO
COME INPUT ABBIAMO DIZIONARIO *D OVVERO UN PUNTATORE ALLA STRUTTURA DATI CHE INIZIALIZZIAMO
*/

void dizionario(Dizionario *d){
    for (int i = 0; i < 26; i++)
    {
        d->lettere[i].n_voci = 0;
    }
}

/* FUNZIONE OTTIENI INDICE
HA COME SCOPO QUELLO DI CALCOLARE L'INDICE NUMERICO CHE CORRISPONDE ALLA LETTERA INIZIALE
IN INPUT ABBIAMO CHAR C OVVERO IL CARATTERE INIZIALE DELLA PAROLA E COME OUTPUT UN INTERO CHE IN REALTA' E' LA TRASFORMAZIONE DEL CARATTERE
DA FORMATO CHAR A FORMATO NUMERICO 
*/
int ottieniIndice(char c){
    return tolower(c) - 'a';
}

/* FUNZIONE INSERISCI VOCE
LA FUNZIONE HA L'UTILITA' DI POPOLARE LA STRUTTURA DIZIONARIO, IN ORDINE ALFABETICO, CON I DATI CHE INSERIAMO, COME PARAMETRI D'INGRESSO ABBIAMO
IL PUNTATORE AL NUOVO DIZIONARIO D, IL PUNTATORE TERMINE E SUOI CONTRARI ED INFINE NUM_C CHE INDICA QUANTI CONTRARI CI SONO.
*/

void inserisciVoce(Dizionario *d, char *termine, char contrari[][30], int num_c){
    int indice = ottieniIndice(termine[0]);
    int pos = d->lettere[indice].n_voci;

    Parola nuova;
    strcpy(nuova.termine, termine);
    nuova.n_contrari = num_c;
    for (int i = 0; i < num_c; i++)
    {
        strcpy(nuova.contrari[i], contrari[i]);
    }

    d->lettere[indice].voci[pos] = nuova;
    d->lettere[indice].n_voci++;
}

/* FUNZIONE CERCA CONTRARI
FUNZIONE CHE HA COME PARAMETRI DI INPUT IL PUNTATORE ALLA STRUTTURA DEL NUOVO DIZIONARIO E IL PUNTATORE TERMINE,
QUESTA FUNZIONE RICERCA ATTRAVERSO L'IMPLEMENTAZIONE DI UN ALGORITMO DI RICERCA BINARIA I CONTRARI DELLA PAROLA, IN PARTICOLARE
LA FUNZIONE NON CERCA IN TUTTO IL DIZIONARIO MA SOLO NELLA SEZIONE DELLA LETTERA INIZIALE DEL TERMINE, COSA FA:
HO DEFINITO UN INTERVALLO, BASSO E ALTO, L'ALGORITMO CALCOLA IL PUNTO MEDIO ATTRAVERSO QUESTE DUE VARIABILI, SE CORRISPONDONO LA PAROLA
E' STATA TROVATA, ALTRIMENTI SE LA PAROLA E' PIU' GRANDE, SCARTA LA META' SINISTRA E RESTRINGE IL CAMPO ALLA META' DESTRA, SE E' PIU' PICCOLA
INVECE FA IL CONTRARIO. QUANDO LA TROVA LA VARIABILE TROVATO CAMBIA IL VALORE E NON E' PIU' -1 QUINDI STAMPA I CONTRARI TROVATI.
*/

void cercaContrari(Dizionario *d, char *termine){
    int indice = ottieniIndice(termine[0]);
    int basso = 0;
    int alto = d->lettere[indice].n_voci - 1;
    int trovato = -1;

    while (basso <= alto)
    {
        int medio = (basso + alto) / 2;
        int comp = strcmp(d->lettere[indice].voci[medio].termine, termine);

        if (comp == 0)
        {
            trovato = medio;
            break;
        } else if (comp < 0){
            basso = medio + 1;
        } else {
            alto = medio - 1;
        }
    }

    if (trovato != -1)
    {
        printf("\n Contrari di '%s': \n", termine);
        for (int i = 0; i < d->lettere[indice].voci[trovato].n_contrari; i++)
        {
            printf("- %s\n", d->lettere[indice].voci[trovato].contrari[i]);
        }
    } else {
        printf("\nParola '%s' non trovata nel dizionario.\n", termine);
    }
}


 /*
 NEL MAIN C'E' SEMPLICEMENTE UN DO WHILE CON ALL'INTERNO UNO SWITCH PER IL MENU
 */   

void menu(){
    printf("\n--- GESTIONE DIZIONARIO ---");
    printf("\n 1. Cerca contrari di una parola");
    printf("\n 2. Esci");
    printf("\n Scelta: ");
}

int main(){
    Dizionario nuovoDizionario;
    dizionario(&nuovoDizionario);

    int scelta;
    char bufferTermine[30];

    char c1[5][30] = {"chiuso", "serrato"};
    char c2[5][30] = {"cattivo", "perfido", "maligno"};
    char c3[5][30] = {"piccolo", "minimo"};

    inserisciVoce(&nuovoDizionario, "aperto", c1, 2);
    inserisciVoce(&nuovoDizionario, "buono", c2, 3);
    inserisciVoce(&nuovoDizionario, "grande", c3, 2);

    do
    {
        menu();
        scanf("%d", &scelta);
        getchar();

        switch (scelta)
        {
        case 1:
            printf("Inserisci la parola da cercare:");
            scanf("%s", bufferTermine);
            cercaContrari(&nuovoDizionario, bufferTermine);
            break;
        case 2:
            printf("Uscita...\n");
            break;
        default:
            printf("Scelta non valida!\n");
            break;
        }
    } while (scelta != 2);
    return 0;
}
