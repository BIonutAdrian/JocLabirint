#include <iostream>
#include <cmath>
using namespace std;

int labirint[13][13], senzor[4],linie,coloana,vecini[3][5],d=0,puncte=0,OK=1;
char actiune;

int limite() { //folosit pentru a nu iesi din limitele matricei
    if (vecini[0][d] < 12 && vecini[0][d] >= 0 && vecini[1][d] < 12 && vecini[1][d] >= 0)
        return 0;
    else
        return 1;
}

void afisare_labirint() { //afisare labirintului impreuna cu punctele si exploratorul
    labirint[linie][coloana] = 5;
    for (int i = 0;i < 12;i++) {
        for (int j = 0;j < 12;j++)
            cout << labirint[i][j] << " ";
        cout << endl;
    }
    labirint[linie][coloana] = 0;
    if (d == 0)
        cout << "Va uitati in sus." << endl;
    if (d == 1)
        cout << "Va uitati in dreapta." << endl;
    if (d == 2)
        cout << "Va uitati in jos" << endl;
    if (d == 3)
        cout << "Va uitati in stanga" << endl;
    cout << "Puncte: " << puncte << endl << endl;
}

void modificare_vecini() { //modificarea pozitiilor unde se poate deplasa exploratorul
    vecini[0][0] = linie - 1;
    vecini[1][0] = coloana;
    vecini[0][1] = linie;
    vecini[1][1] = coloana + 1;
    vecini[0][2] = linie + 1;
    vecini[1][2] = coloana;
    vecini[0][3] = linie;
    vecini[1][3] = coloana - 1;
}

void rezolva_actiune() {
    if (actiune == 'w') {
        if (labirint[vecini[0][d]][vecini[1][d]] == 0) { //verific daca camera este goala si intru in ea
            linie = vecini[0][d];
            coloana = vecini[1][d];
            modificare_vecini();
            int i = limite();
            if (i)
                cout << "Nu va puteti deplasa in acea directie" << endl;
        }
        else
        if (labirint[vecini[0][d]][vecini[1][d]] == 1) { //verific daca am dat intr-un zid
            senzor[1] = 1;
        }
        else
        if (labirint[vecini[0][d]][vecini[1][d]] == 2) { //verific daca am intrat intr-o camera cu monstru
            senzor[2] = 1;
            puncte = puncte - 1000;
            linie = vecini[0][d];
            coloana = vecini[1][d];
            modificare_vecini();
            int i = limite();
            if (i)
                cout << "Nu va puteti deplasa in acea directie" << endl;
        }
        else
        if (labirint[vecini[0][d]][vecini[1][d]] == 3) { //verific daca am intrat intr-o camera cu comoara
            senzor[3] = 1;
            puncte = puncte + 100;
            linie = vecini[0][d];
            coloana = vecini[1][d];
            modificare_vecini();
            int i = limite();
            if (i)
                cout << "Nu va puteti deplasa in acea directie" << endl;
        }
    }
    if (actiune == 'd') { //roteste caracterul la dreapta
        if (d == 3)
            d = 0;
        else
            d = d + 1;
        int i = limite();
        if (i)
            cout << "Nu va puteti deplasa in acea directie" << endl;
    }
    if (actiune == 'a') { //roteste caracterul la stanga
        if (d == 0)
            d = 3;
        else
            d = d - 1;
        int i = limite();
        if (i)
            cout << "Nu va puteti deplasa in acea directie" << endl;
    }
    if (actiune == 's') { //actiunea de a impusca in camera din fata
        puncte = puncte - 25;
        if (labirint[vecini[0][d]][vecini[1][d]] == 2) {
            puncte = puncte + 50;
            labirint[vecini[0][d]][vecini[1][d]] = 0;
            cout << "Monstrul a fost ucis." << endl;
        }
        else {
            cout << "Camera era goala." << endl;
        }
    }
    if (actiune == 'o') //oprirea programului
        OK = 0;
    puncte = puncte - 1;
}

void parcrurgere() {
    while (OK) {
        afisare_labirint();

        //verificarea senzorilor
        if (senzor[1] == 1)
            cout << "V-ati lovit de un perete." << endl;
        if (senzor[2] == 1)
            cout << "Ati intrat intr-o camera cu un monstru." << endl;
        if (senzor[3] == 1)
            cout << "Ati gasit o comoara." << endl;

        //resetarea senzorilor
        senzor[1] = senzor[2] = senzor[3] = 0;

        //cererea unei actiuni si citirea acesteia
        cout << "Alegeti o actiune: ";
        cin >> actiune;
        rezolva_actiune();
    }
    cout << "Punctele acumulate sunt: " << puncte;
}

int main() {
    for (int i = 0;i < 12;i++)
        for (int j = 0;j < 12;j++)
            labirint[i][j] = 0;

    //Stabilesc zidurile din labirint
    for (int i = 1;i <= 9;i++)
        labirint[i][1] = 1;

    for (int i = 1;i <= 4;i++) {
        labirint[i][4] = 1;
        labirint[4][i] = 1;
    }

    labirint[3][6] = 1;
    labirint[3][7] = 1;

    for (int i = 2;i <= 6;i++)
        labirint[i][9] = 1;

    for (int i = 3;i <= 6;i++)
        labirint[10][i] = 1;

    for (int i = 7;i <= 10;i++)
        labirint[8][i] = 1;

    //Stabilesc locatiile monstrilor
    labirint[11][5] = 2;
    labirint[1][7] = 2;
    labirint[5][11] = 2;

    //Stabilesc locatiile comorilor
    labirint[2][2] = 3;
    labirint[1][10] = 3;
    labirint[10][8] = 3;

    for (int i = 0;i < 12;i++) {
        for (int j = 0;j < 12;j++)
            cout << labirint[i][j] << " ";
        cout << endl;
    }

    linie = 11;
    coloana = 0;
    modificare_vecini();

    //afisarea comenzilor ce pot fi folosite
    printf("Comenzile pentru actiuni sunt:\n- Mers in fata: w\n- Intoarcere la dreapta: d\n- Intoarcere la stanga: a\n- Impusca: s\n- Oprire: o\n\n");
    cout << "Incepeti cu directia in sus." << endl;
    cout << "Exploratorul este reprezentat de numarul 5." << endl;

    parcrurgere();

    getchar();
    getchar();

    return 0;
}