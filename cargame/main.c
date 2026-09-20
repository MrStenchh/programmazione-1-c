/*
    INFORMAZIONI UTILI: La cartella deve contenere:
    Un file (word o altro) che è il documento di testo con contenuti multimediali;
    Una cartella C contenente i file sorgente del progetto (.c, .h);
    Il testo della prova inviata dal docente in formato .pdf;
    Altre cartelle eventualmente generate per il documento;

    LA RELAZIONE DEVE CONTENERE NECESSARIAMENTE ALMENO:
    Il testo della prova inviata dal docente;
    Il testo dei programmi C (sorgente);
    L'output e la descrizione dei test di esecuzione;

    I test devono essere almeno tre per ogni programma, devono essere salvati come "print screen" e come
    figure nel documento di testo. Devono essere corredati da una descrizione per l'interpretazione dei risultati del test.
*/

/*
    GIOCO AUTO
    Si vuole sviluppare un programma per la simulazione di un gioco che prevede un’auto su un percorso che deve evitare degli ostacoli. 
    Si suppone di aver un percorso come in figura dove sul fondo è presente un’auto (rossa) che può andare a destra o sinistra. 
*/


#include <stdio.h> // LIBRERIA STANDARD DI C PER INPUT/OUTPUT
#include <stdlib.h> // LIBRERIA PER FUNZIONI STANDARD (RAND, SRAND)
#include <time.h> // LIBRERIA PER GESTIRE IL TEMPO
#include <stdbool.h> // LIBRERIA PER UTILIZZARE IL TIPO DI DATO BOOLEAN
#include <windows.h> // LIBRERIA SPECIFICA WINDOWS PER LA FUNZIONE SLEEP

#define RIGHE 6 // DEFINISCE L'ALTEZZA DELLA MATRICE
#define COLONNE 5 // DEFINISCE LA LARGHEZZA DELLA MATRICE
#define MAX_PASSI 100 // DEFINISCE LA DURATA MASSIMA DELLA PARTITA

#define VUOTO 0 // PER LA CELLA LIBERA
#define AUTO 1 // PER L'AUTO
#define OSTACOLO 2 // PER L'OSTACOLO

/*# FUNZIONE PER PREPARARE IL CAMPO DI GIOCO
FUNZIONE CHE HA COME PARAMETRI D'INGRESSO LA MATRICE CAMPO CON LE RIGHE E LE COLONNE E IL PUNTATORE AUTOX,
QUESTA FUNZIONE PREPARA IL CAMPO DI GIOCO ASSEGNANDO ALLA POSIZIONE 5/2 L'AUTO, MENTRE NELLE ALTRE CELLE CI SONO SPAZI VUOTI.
*/

void inizializzazioneGioco(int campo[RIGHE][COLONNE], int *autoX){
    for (int i = 0; i < RIGHE; i++)
    {
        for (int j = 0; j < COLONNE; j++)
        {
            campo[i][j] = VUOTO;
        }
    }
    *autoX = 2;
    campo[RIGHE - 1][*autoX] = AUTO;
}

/*
### FUNZIONE PER STAMPARE L'INTERFACCIA GRAFICA DEL GIOCO
QUESTA FUNZIONE CHE HA COME PARAMETRI D'INGRESSO LA MATRICE DEL CAMPO CON RIGHE E COLONNE E LA VARIABILE INTERA PASSI
E' SEMPLICEMENTE L'INTERFACCIA DI GIOCO, QUINDI STAMPERA' A SCHERMO LE ENTITA' CHE ABBIAMO CREATO IN PRECEDENZA,
DOVE TROVERA' L'AUTO STAMPERA A, L'OSTACOLO O, E SE NON TROVA NULLA UNO SPAZIO VUOTO.
*/

void interfacciaGioco(int campo[RIGHE][COLONNE], int passi){
    printf("ROUND: %d/%d\n", passi, MAX_PASSI);
    printf("--------\n");
    for (int i = 0; i < RIGHE; i++)
    {
        printf("|");
        for (int j = 0; j < COLONNE; j++)
        {
            if (campo[i][j] == AUTO)
            {
                printf("A");
            } 
            else if (campo[i][j] == OSTACOLO)
            {
                printf("O");
            } 
            else printf(" ");
        }
        printf("|\n");
    }
    printf("--------\n");
}

/*
### FUNZIONE CHE GENERA L'OSTACOLO 
FUNZIONE CHE HA COME PARAMETRO DI INPUT LA MATRICE CAMPO. QUESTA FUNZIONE DA ALL'OSTACOLO UNA POSIZIONE DI PARTENZA
GENERANDO RANDOMICAMENTE LA SUA POSIZIONE DATA DALL'OPERAZIONE DI MODULO (RESTO) TRA LA FUNZIONE RAND E LE COLONNE.
*/

void ostacolo(int campo[RIGHE][COLONNE]){
    int posizione = rand() % COLONNE;
    campo[0][posizione] = OSTACOLO;
}

/*
### FUNZIONE PER IL MOVIMENTO VERSO IL BASSO DELL'OSTACOLO
FUNZIONE CHE HA COME PARAMETRO D'INGRESSO LA MATRICE CAMPO. LA FUNZIONE MUOVE L'OSTACOLO DI 1 O 2 POSIZIONE RANDOM, GRAZIE ALLA
FUNZIONE RAND, CHE ATTRAVERSO L'OPERAZIONE DI MODULO CON 2 RESTITUIRA' 0 OPPURE 1 CHE SI SOMMERA' CON 1, COSI' L'OSTACOLO POTRA'
SPOSTARSI DI 1 O 2 CASELLE IN GIU' RANDOMICAMENTE.
*/

void muoviOstacolo(int campo[RIGHE][COLONNE]){
    for (int i = RIGHE -1; i >= 0; i--)
    {
        for (int j = 0; j < COLONNE; j++)
        {
            if (campo[i][j] == OSTACOLO)
            {
                int movimento = (rand() % 2)+1; // numero casuale tra 0 e 1 + 1
                campo[i][j] = VUOTO;
                if (i + movimento < RIGHE)
                {
                    campo[i + movimento][j] = OSTACOLO;
                }
            }
        }
    }
}

/*
### FUNZIONE PER LA GESTIONE DELL'INTELLIGENZA ARTIFICIALE DELLA MACCHINA
FUNZIONE CHE COME PARAMETRO D'INGRESSO HA LA MATRICE CAMPO E IL PUNTATORE AUTOX. 
LA FUNZIONE E' "L'INTELLIGENZA" DELL'AUTO, IN PRATICA LA ZONA VERDE, L'AUTO PUO' "VEDERE" 2 CASELLE D'AVANTI A LEI
SE TROVA L'OSTACOLO SI SPOSTA A DESTRA O SINISTRA SEMPRE RANDOMICAMENTE, QUESTO PERCHE' SI SUPPONE CHE NON DEBBA SAPERE LA POSIZIONE
DEGLI ALTRI OSTACOLI MA SOLO QUELLI DAVANTI A SE.
*/

void muoviAuto(int campo[RIGHE][COLONNE], int *autoX){
    int x = *autoX;
    int rigaAuto = RIGHE -1;
    int rigaSuperiore = RIGHE -2;
    int rigaSuperiore2 = RIGHE -3;

    if (campo[rigaSuperiore][x] == OSTACOLO || campo[rigaSuperiore2][x] == OSTACOLO){
        
        if(x == 0){
            campo[rigaAuto][x] = VUOTO;
            (*autoX)++;
            campo[rigaAuto][*autoX] = AUTO;

        } else if(x < COLONNE -1){
            campo[rigaAuto][x] = VUOTO;
            (*autoX)--;
            campo[rigaAuto][*autoX] = AUTO;

        } else{
            int movimento = (rand() % 2)+1;
            campo[rigaAuto][x] = VUOTO;
            if(movimento == 1){
                (*autoX)--;
            } else if(movimento == 2){
                (*autoX)++;
            }
            
            campo[rigaAuto][*autoX] = AUTO;
        }
    }
}

/*
### FUNZIONE CHE CONTROLLA SE L'AUTO E' STATA COLPITA, RESITUISCE TRUE SE NELLA POSIZIONE DELL'AUTO SI TROVA UN OSTACOLO
*/
bool controlloCollisione(int campo[RIGHE][COLONNE], int autoX){
    return campo[RIGHE -1][autoX] == OSTACOLO;
}

/*
NEL MAIN C'E' UN DO WHILE CHE PERMETTE DI GIOCARE FINCHE' NON C'E' UNA COLLISIONE O LA PARTITA ARRIVA AL ROUND 100,
ALLA FINE DEL GIOCO CI SARA' UN WHILE PER POTER RIGIOCARE.
HO UTILIZZATO \033[H\033[J PER PULIRE LO SCHERMO E SLEEP PER AVERE LA SENSAZIONE DI UN GIOCO FLUIDO
*/

int main(){

    char scelta;
    do{

    int campo[RIGHE][COLONNE];
    int autoX;
    int passi = 1;
    bool collisione = false;
    srand((unsigned int)time(NULL));

    inizializzazioneGioco(campo, &autoX);

    while (passi <= MAX_PASSI && !collisione)
    {
        printf("\033[H\033[J");
        muoviAuto(campo, &autoX);
        muoviOstacolo(campo);

        if (controlloCollisione(campo, autoX))
        {
            collisione = true;
            break;
        }

        ostacolo(campo);
        interfacciaGioco(campo, passi);
        passi++;
        Sleep(300);
        
    }

    if (collisione)
    {
        printf("\n--- GAME OVER! L'OSTACOLO HA COLPITO L'AUTO, SEI ARRIVATO AL ROUND: %d ---\n", passi);
    }
    else {
        printf("\n--- HAI VINTO! L'AUTO HA RAGGIUNTO IL TRAGUARDO SENZA ESSERE COLPITA!\n");
    }

    printf("VUOI GIOCARE ANCORA? DIGITA 1");
    scanf(" %C", &scelta);

    } while (scelta == '1');
    

    printf("\n PREMI INVIO PER USCIRE");
    while (getchar() != '\n' && getchar() != EOF);
    getchar();
    
    
    return 0;
}
