#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

template <class data> class nod_avl;
template <class data> class abc;
template <class data> class avl;

template <class data, class nodt>
class arbore {
    nodt * rad;
    int nr_noduri;
public:
    friend class abc<data>;
    friend class avl<data>;

    arbore() {rad=nullptr; nr_noduri=0;}
    arbore(data inf) {
        rad=new nodt ;
        rad->info=inf;
        rad->st=rad->dr=nullptr;
        nr_noduri=1;
    }
    arbore(const arbore& arb) {
        cout<<"CC arbore."<<endl;
        nr_noduri=arb.nr_noduri;
        rad=nullptr;
        if (arb.rad) {
            rad=new nodt ;
            rad->copiere_rec(*(arb.rad));
        }
    }
    virtual ~arbore() {
        cout<<"Destructor arbore."<<endl;
        if (rad) delete rad;
    }
    virtual arbore& operator=(const arbore& arb) {
        if (this!=(&arb)) {
            nr_noduri=arb.nr_noduri;
            if (rad) {
                rad->stergere_subarbore_rec();
                delete rad;
            }
            cout<<"Arborele de egalizat e: "<<*(arb.rad)<<endl;
            if (arb.rad) {
                rad=new nodt;
                rad->copiere_rec(*(arb.rad));
            }
        }
        return (*this);
    }

    void afisare (ostream& o) {
        rad->afisare_rec(o);
        return;
    }

    virtual void adauga (data inf) {
        if (rad==nullptr) {
            nr_noduri++;
            rad=new nodt;
            rad->info=inf;
            rad->st=rad->dr=nullptr;
            return;
        }
        nodt* t=rad;
        while (t->st) {
            t=t->st;
        }
        t->st=new nodt;
        t=t->st;
        t->info=inf;
        t->st=t->dr=nullptr;
        nr_noduri++;
        cout<<"Adaug "<<inf<<" si obtin: "<<(*rad)<<endl;
        return;
    }

    virtual arbore& operator+(data inf) {
        adauga(inf);
        return (*this);
    }

    virtual void stergere (data inf) {
        if (rad) {
            if (rad->info==inf) {
                nodt* aux;
                if (rad->st) aux=new nodt(*(rad->st));
                else aux=nullptr;
                delete rad;
                rad=aux;
                return;
            }
        } else return;
        nodt* t=rad;
        while (t->st) {
            if ((t->st)->info==inf) {
                    nodt* aux;
                    if ((t->st)->st) nodt* aux=new nodt(* ((t->st)->st));
                    else aux=nullptr;
                    delete t->st;
                    t->st=aux;
                }
                t=t->st;
            }
        return;
    }
};
