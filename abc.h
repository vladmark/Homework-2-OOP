#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "arbore.h"
#include "nod.h"
using namespace std;

template <class data> void stergere_inlocuire_nod (nod<data>** root);

template <class data> class abc: public arbore <data, nod<data> > {
public:
    abc():arbore<data, nod<data> >() {};
    abc(data inf):arbore<data, nod<data> >(inf) {};
    abc(const abc<data>& arb):arbore<data, nod<data> >(arb) {};
    ~abc() {
        cout<<"Destructor arbore binar."<<endl;
    };
    friend void stergere_inlocuire_nod<data>(nod<data>** root);

    void adauga (data inf) {
        if (arbore<data, nod<data> >::rad==nullptr) {
            arbore<data, nod<data> >::rad=new nod<data>;
            arbore<data, nod<data> >::rad->info=inf;
            arbore<data, nod<data> >::rad->st=arbore<data, nod<data> >::rad->dr=nullptr;
            return;
        }
        nod<data>* t=arbore<data, nod<data> >::rad;
        while (t) {
            if (t->info > inf) {
                if (t->dr==nullptr) {
                    t->dr=new nod<data>;
                    t=t->dr;
                    t->dr=t->st=nullptr;
                    t->info=inf;
                    return;
                }
                t=t->dr;
            }
            else if (t->info < inf) {
                if (t->st==nullptr) {
                    t->st=new nod<data>;
                    t=t->st;
                    t->st=t->dr=nullptr;
                    t->info=inf;
                    return;
                }
                t=t->st;
            }
        }
    }
    abc& operator+(data inf){
        arbore<data, nod<data> >::operator+(inf);
        return (*this);
    }
    abc& operator=(const abc& Acopiat) {
        arbore<data, nod<data> >::operator=(Acopiat);
        return (*this);
    }

    void stergere (data inf) {
        if (arbore<data, nod<data> >::rad) {
            if(arbore<data, nod<data> >::rad->info==inf) {
                if (arbore<data, nod<data> >::rad->st || arbore<data, nod<data> >::rad->dr) {
                    stergere_inlocuire_nod<data> (&(arbore<data, nod<data> >::rad));
                    return;
                }
                else delete arbore<data, nod<data> >::rad;
            }
            nod<data>* t=arbore<data, nod<data> >::rad;
            while (t->st || t->dr) {
                if (t->st) {
                    if ((t->st)->info==inf) {
                        if ((t->st)->st || (t->st)->dr) {
                            //daca nodul de sters are macar subarbore stang sau drept, atunci apelez stergere inlocuire; altfel e frunza si il sterg pur si simplu
                            stergere_inlocuire_nod(&(t->st));
                            return;
                        }
                        else {
                            delete t->st;
                            return;
                        }
                    }
                }
                if (t->dr) { //analog ca mai sus
                    if ((t->dr)->info==inf) {
                        if ((t->dr)->st || (t->dr)->dr) {
                            stergere_inlocuire_nod(&(t->dr));
                            return;
                        }
                        else {
                            delete t->dr;
                            return;
                        }
                    }
                }
                if (inf < t->info) {
                    if (t->st) t=t->st;
                    else return; //nu am cum sa gasesc nodul
                }
                if (inf > t->info) {
                    if (t->dr) t=t->dr;
                    else return; //nu am cum sa gasesc nodul
                }
            }
            return;
    }

};
