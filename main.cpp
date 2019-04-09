#pragma once
#include <iostream>
#include <fstream>
#include <math.h>

#include "nod.h"
#include "nod_avl.h"
#include "arbore.h"
#include "abc.h"
#include "avl.h"
using namespace std;

template <class data> void stergere_inlocuire_nod (nod<data>** root) {
    //se presupune ca radacina are macar subarbore stang sau drept: de cazul in care e frunza ma ocup in functia mai mare care o apeleaza pe asta
    /*plan:
    Caz 1. subarborele drept exista si primul lui nod are subarbore stang
    1- gasesc cea mai mica frunza mai mare decat root (cauta_frunza_min) si returnez pointer la TATAL ei
    2- schimb valoarea radacinii cu valoarea frunzei gasite si las radacina in pace (n-am nevoie de mai mult)
    3- creez un nod pointer aux si copiez in el (cu noi alocari) tot subarborele drept al frunzei celei mai mici (constructorul de copiere al nod copiaza recursiv)
    4- sterg subarborele stang al TATALUI frunzei celei mai mici
    5- pun TATA->st=aux;
    Caz 2. subarborele drept exista si primul lui nod nu are subarbore stang
    1- copiez (aloc) recursiv un nou nod pointer aux care incepe cu primul nod al subarborelui drept
    2- copiez in nodul stang al lui aux nodul stang al radacinii
    3- delete root
    4- root=aux (ca pointer)
    Caz 3. radacina nu are subarbore drept:
    1- copiez (aloc) recursiv un nou nod pointer aux care incepe cu primul nod al subarborelui stang
    2- delete root
    3- root=aux
    */
    if ((*root)->dr) {
        if ((*root)->dr->st) { //Caz 1
            //1
            nod<data>* nmin_tata=((*root)->dr)->cauta_frunza_min();
            //2
            (*root)->info=(nmin_tata->st)->info;
            //3
            nod<data>* aux;
            if ((nmin_tata->st)->dr) aux=new nod<data>(*( (nmin_tata->st)->dr));
            else aux=nullptr;
            //4
            delete nmin_tata->st;
            //5
            nmin_tata->st=aux; //e suficient pentru ca aux a fost alocat deja recursiv
        }
        else { //Caz 2
            //1
            nod<data>* aux;
            aux=new nod<data>(*((*root)->dr));
            //2
            aux->st=new nod<data>(*((*root)->st));
            //3
            delete (*root);
            //4
            (*root)=aux;
        }
    } else { //Caz 3
        //1
        nod<data>* aux=new nod<data> (*((*root)->st));
        delete (*root);
        (*root)=aux;
    }
    return;
}


template <class data> ostream& operator<<(ostream& o, nod<data>& n) {
    n.afisare_rec(o);
    return o;
}

template <class data> void rotatie_stanga(nod_avl<data>** root) {
    cout<<"Rotatie stanga pe "<<(*root)->get()<<endl;
    nod_avl<data>* newroot;
    newroot=new nod_avl<data>;
    newroot=(*root)->dr;
    (*root)->dr=newroot->st;
    (*root)->h=(*root)->det_h();
    newroot->st=(*root);
    newroot->h=newroot->det_h();
    (*root)=newroot;
    return;
}

template <class data> void rotatie_dreapta(nod_avl<data>** root) {
    cout<<"Rotatie dreapta pe "<<(*root)->get()<<endl;
    nod_avl<data>* newroot;
    newroot=new nod_avl<data>;
    newroot=(*root)->st;
    (*root)->st=newroot->dr;
    (*root)->h=(*root)->det_h();
    newroot->dr=(*root);
    newroot->h=newroot->det_h();
    (*root)=newroot;
    return;
}

template <class data> void rotatie_dreapta_stanga (nod_avl<data>** root) {
    cout<<"Rotatie dreapta-stanga pe "<<(*root)->get()<<endl;
    rotatie_dreapta(&((*root)->dr));
    rotatie_stanga(root);
}

template <class data> void rotatie_stanga_dreapta (nod_avl<data>** root) {
    cout<<"Rotatie stanga-dreapta pe "<<(*root)->get()<<endl;
    rotatie_stanga(&((*root)->st));
    rotatie_dreapta(root);
}

template <class data> void echilibreaza (nod_avl<data>** root) {
        (*root)->bal=(*root)->det_bal();
        if ((*root)->bal == -2) {
            cout<<"Se executa o echilibrare de -2 pe "<<(*root)->get()<<endl;
            if ( (*root)->dr->bal == 1) {
                rotatie_dreapta_stanga(root);
                return;
            } else if ( (*root)->dr->bal == -1 ) {
                rotatie_stanga (root);
                return;
            } else {
                cout<<"Nu-i bine. Am -2 sus si altceva decat 1 sau -1 in dreapta."<<endl;
                return;
            }
        } else if ( (*root)->bal == 2 ) {
            cout<<"Se executa o echilibrare de 2 pe "<<(*root)->get()<<endl;
            if ( (*root)->st->bal == -1) {
                cout<<"bal=-1. Ar trebui sa fac rot st dr."<<endl;
                rotatie_stanga_dreapta(root);
                return;
            } else if ( (*root)->st->bal == 1 ) {
                cout<<"bal=1. Ar trebui sa fac rot dr."<<endl;
                rotatie_dreapta (root);
                return;
            } else {
                cout<<"Nu-i bine. Am 2 sus si altceva decat 1 sau -1 in stanga."<<endl;
                return;
            }
        } else if ( (*root)->bal == 1 || (*root)->bal == -1 || (*root)->bal == 0 ) {
            return; //nu-i nevoie de echilibrare
        } else {
            cout<<"Nu-i bine. x->bal nu e -2,2,1,-1 sau 0."<<endl;
            return;
        }
}

template <class data, class nodt> ostream& operator<<(ostream& o, arbore<data, nodt>& arb) {
    arb.afisare(o);
    return o;
}

template <class data, class nodt> istream& operator>>(istream& i, arbore<data, nodt>& arb) {
    data inf;
    i>>inf;
    arb.adauga(inf);
    return i;
}







int main()
{
    int i1=3, i2=5;
    nod<int> n1(3), n2(5), n3(7);
    cout<<"n2>n1: "<<(n2>n1)<<endl;
    cout<<"n2==n1: "<<(n2==n1)<<endl;
    arbore <int, nod<int> > arb1(3), arb2(arb1);
    cout<<"arb1: "<<arb1<<endl;
    cout<<"arb2: "<<arb2<<endl;
    arb2=arb1+11+12;
    cout<<"arb2+11+12: "<<arb2<<endl;
    cout<<"(arb2+11+12)+13 adaugat in cout: "<<arb2+13<<endl;
   cout<<"arb2 acum: "<<arb2<<endl;
    abc<int> arbin(7);
    arbin=arbin+3+256+23+12+1+5;

    cout<<"arbin: "<<arbin<<endl;
    avl<int> avl1(1);
    cout<<"avl: "<<avl1<<endl;
    avl1=avl1+23;
    cout<<"avl+23: "<<avl1<<endl;
    avl1=avl1+14;
    cout<<"avl+23+14: "<<avl1<<endl;
    avl1=avl1+9;
    cout<<"avl+23+14+19: "<<avl1<<endl;
    avl1=avl1+19;
    avl<int> avl2;
    cout<<"Introduceti in avl2: "<<endl;
    cin>>avl2;
    cout<<endl<<"avl2: "<<avl2<<endl;
    //Demonstrarea virtualizarii:
    ifstream fin("tema2.in");
    int n;
    fin>>n;
    arbore<int, nod<int> >* arb_abc;
    cout<<"Introduceti 1 pentru arbore si 2 pentru abc: "<<endl;
    int opt1;
    cin>>opt1;
    if (opt1==1) {
        arb_abc=new arbore<int, nod<int> >;
        for (int i=0; i<n; i++) fin>>arb_abc;
        cout<<arb_abc;
    } else if (opt1==2) {
        arb_abc=new abc<int>;
        for (int i=0; i<n; i++) fin>>arb_abc;
        cout<<arb_abc;
    }
    arbore<int, nod_avl<int> >* arb_avl;
    cout<<"Introduceti 3 pentru arbore si 4 pentru avl: "<<endl;
    cin>>opt1;
    if (opt1==3) {
        arb_avl=new arbore<int, nod<int> >;
        for (int i=0; i<n; i++) fin>>arb_avl;
        cout<<arb_avl;
    } else if (opt1==4) {
        arb_avl=new avl<int>;
        for (int i=0; i<n; i++) fin>>arb_avl;
    }

    return 0;
}
