#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
template <class data> class nod;
template <class data> class nod_avl;
template <class data, class nodt > class arbore;
template <class data> class abc;
template <class data> class avl;
template <class data> void stergere_inlocuire_nod (nod<data>** root);



template <typename data>
class nod
{
    data info;
    nod* st;
    nod* dr;
public:
    nod() {st=dr=nullptr;}
    nod(data inf) {info=inf; st=dr=nullptr;};
    nod(const nod& n) {
        info=n.info;
        st=dr=nullptr;
        if(n.st){
            st=new nod(*(n.st));
        }
        if(n.dr){
            dr=new nod(*(n.dr));
        }
     };
    virtual ~nod(){
        cout<<"Destructor nod."<<endl;
        if(st) {
            delete st;
        }
        if(dr) {
            delete dr;
        }
        return;
    }
    friend class arbore <data, nod<data> >;
    friend class abc <data>;
    friend class nod_avl <data>;
    friend class avl <data>;
    friend class arbore <data, nod_avl<data> >;
    friend void avl<data>::avl_maker (nod_avl<data>** root, data inf);
    friend void stergere_inlocuire_nod<data>(nod<data>** root);
    virtual nod& operator=(const nod& n) {
        if (this != &n) {
            stergere_subarbore_rec();
            copiere_rec(n);
        }
        return (*this);
    };
     data get() {return info;};
     bool operator>(nod& n) {return info>n.info;};
     bool operator<(nod& n) {return info<n.info;};
     bool operator==(nod& n) {return info==n.info;};
     virtual void stergere_subarbore_rec() {
        if (st) delete st;
        if (dr) delete dr;
        return;
    }

    virtual nod* cauta_frunza_min () {
        if (st) {
            if (st->st) {
                return st->cauta_frunza_min();
            }
        }
        else return this;
    }



     void copiere_rec (nod a) {
        info=a.info;
        st=dr=nullptr;
        if(a.st){
            st=new nod(*(a.st));
            //st->copiere_rec();
        }
        if(a.dr){
            dr=new nod(*(a.dr));
            //dr->copiere_rec();
        }
        return;
     }
     virtual void afisare_rec (ostream& o) {
        o<<info<<" ";
        if (st) {
            st->afisare_rec(o);
        }
        if (dr) {
            dr->afisare_rec(o);
        }
        return;
     }
};
