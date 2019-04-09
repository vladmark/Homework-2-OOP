#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "arbore.h"
#include "nod_avl.h"
using namespace std;

template <class data> void echilibreaza (nod_avl<data>** root);
template <class data> void rotatie_stanga (nod_avl<data>** root);
template <class data> void rotatie_dreapta (nod_avl<data>** root);
template <class data> void rotatie_dreapta_stanga (nod_avl<data>** root);
template <class data> void rotatie_stanga_dreapta (nod_avl<data>** root);

template <class data>
class avl:public arbore<data, nod_avl<data> > {
    public:
    avl():arbore<data, nod_avl<data> >() {};
    avl(data inf):arbore<data, nod_avl<data> >(inf) {};
    avl(const avl<data>& arb):arbore<data, nod_avl<data> >(arb) {};
    ~avl() {
        cout<<"Destructor avl."<<endl;
    };
    friend void echilibreaza<data>(nod_avl<data>**);
    friend void rotatie_stanga<data>(nod_avl<data>** root);
    friend void rotatie_dreapta<data>(nod_avl<data>** root);
    friend void rotatie_stanga_dreapta<data>(nod_avl<data>** root);
    friend void rotatie_dreapta_stanga<data>(nod_avl<data>** root);
    void avl_maker (nod_avl<data>** root, data inf) {
        if ((*root)==NULL) {
            (*root)=new nod_avl<data>;
            (*root)->info=inf;
            (*root)->st=(*root)->dr=nullptr;
            (*root)->bal=0;
            (*root)->h=1; /* !!!!!!!!!!!!!!!! */
            return;
        }
        else if (inf < (*root)->info) {
            avl_maker ( &((*root)->st) , inf );
        }
        else if (inf > (*root)->info) {
            avl_maker ( &((*root)->dr) , inf );
        }
        (*root)->h = (*root)->det_h();
        echilibreaza(root); //functiile de rotatie se vor ocupa si de o eventuala realocare a inaltimii
        return;
    }

    void adauga (data inf) {
        avl_maker(&(arbore<data, nod_avl<data> >::rad), inf);
        return;
    }

    avl& operator+(data inf){
        arbore<data, nod_avl<data> >::operator+(inf);
        return (*this);
    }
    avl& operator=(const avl& Acopiat) {
        arbore<data, nod_avl<data> >::operator=(Acopiat);
        return (*this);
    }
};
