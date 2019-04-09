#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "nod.h"
using namespace std;

template <class data, class nodt  >
class arbore;
template <class data> class abc;
template <class data> class avl;
template <class data> void echilibreaza (nod_avl<data>** root);
template <class data> void rotatie_stanga (nod_avl<data>** root);
template <class data> void rotatie_dreapta (nod_avl<data>** root);
template <class data> void rotatie_dreapta_stanga (nod_avl<data>** root);
template <class data> void rotatie_stanga_dreapta (nod_avl<data>** root);

template <typename data>
class nod_avl:public nod<data> {
    nod_avl* st;
    nod_avl* dr;
    int bal;
    int h;
public:
    nod_avl():nod<data>() {bal=0; h=1;}
    nod_avl(data inf):nod<data>(inf) {bal=0; h=1;}
    nod_avl(const nod_avl<data>& n) {
        bal=n.bal;
        h=n.h;
        nod<data>::info=n.info;
        st=dr=nullptr;
        if(n.st){
            st=new nod_avl(*(n.st));
        }
        if(n.dr){
            dr=new nod_avl(*(n.dr));
        }
    }
    ~nod_avl() {
        cout<<"Destructor nod_avl."<<endl;
        if(st) {
            delete st;
        }
        if(dr) {
            delete dr;
        }
        return;
    }
    friend class arbore <data, nod_avl<data> >;
    friend class avl <data>;
    friend void avl<data>::avl_maker (nod_avl<data>** root, data inf);
    friend void rotatie_stanga<data>(nod_avl<data>** root);
    friend void rotatie_dreapta<data>(nod_avl<data>** root);
    friend void rotatie_stanga_dreapta<data>(nod_avl<data>** root);
    friend void rotatie_dreapta_stanga<data>(nod_avl<data>** root);
    friend void echilibreaza<data>(nod_avl<data>** root);

    int det_h() {
        if (dr == nullptr && st==nullptr) return 1;
        else if (dr == nullptr) return (st)->h+1;
        else if (st == nullptr) return (dr)->h+1;
        else return max ( st->h, dr->h ) + 1 ;
    }

    int det_bal () {
        if (dr == nullptr && st==nullptr) return 0;
        else if (dr == nullptr) return (st)->h;
        else if (st == nullptr) return -(dr)->h;
        else return (st->h - dr->h) ;
    }

    void copiere_rec (nod_avl a) {
        bal=a.bal;
        h=a.h;
        nod<data>::info=a.info;
        st=dr=nullptr;
        if(a.st){
            st=new nod_avl(*(a.st));
            //st->copiere_rec(*(a.st));
        }
        if(a.dr){
            dr=new nod_avl(*(a.dr));
            //dr->copiere_rec(*(a.dr));
        }
        return;
     }

     void stergere_subarbore_rec() {
        if (st) delete st;
        if (dr) delete dr;
        return;
     }
    void afisare_rec (ostream& o) {
        o<<"("<<nod<data>::info<<",b"<<bal<<"), ";
        if (st) {
            st->afisare_rec(o);
        }
        if (dr) {
            dr->afisare_rec(o);
        }
        return;
     }

    nod_avl& operator=(const nod_avl& n) {
        nod<data>::operator=(n);
        if (this != &n) {
            stergere_subarbore_rec();
            copiere_rec(n);
        }
        return (*this);
    }
};
