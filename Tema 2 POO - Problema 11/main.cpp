#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

//NOF.H
template <class data> class nod_avl;
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
    virtual nod& operator=(const nod& n) {
        if (this != &n) {
            stergere_subarbore_rec();
            copiere_rec(n);
        }
        return (*this);
    };
     data get() {return info;};
     //void aloca_st (nod* n) {delete st; st=new nod; st->info=n->info; st->st=n->st; st->dr=n->dr;};
     //void aloca_dr (nod* n) {delete dr; dr=new nod; dr->info=n->info; dr->st=n->st; dr->dr=n->dr;};
     bool operator>(nod& n) {return info>n.info;};
     bool operator<(nod& n) {return info<n.info;};
     bool operator==(nod& n) {return info==n.info;};
     virtual void stergere_subarbore_rec() {
        //cout<<"Sunt in "<<info<<" si sterg recursiv."<<endl;
        if (st) delete st;
        if (dr) delete dr;
        /*if(st) {
            //cout<<"Sterg recursiv si o sa merg in stanga: "<<st->info<<endl;
            st->stergere_subarbore_rec();
            delete st;
        }*/
        /*if (dr) {
            //cout<<"Sterg recursiv si o sa merg in dreapta: "<<dr->info<<endl;
            dr->stergere_subarbore_rec();
            delete dr;
        }*/
        return;
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

template <class data> ostream& operator<<(ostream& o, nod<data>& n) {
    n.afisare_rec(o);
    return o;
}


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


//NOD_AVL.CPP

//ARBORE>H

template <class data, class nodt  >
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
        if (rad) {
            delete rad;
        }
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
};

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


//abc.h

template <class data>
class abc: public arbore <data, nod<data> > {
public:
    abc():arbore<data, nod<data> >() {};
    abc(data inf):arbore<data, nod<data> >(inf) {};
    abc(const abc<data>& arb):arbore<data, nod<data> >(arb) {};
    ~abc() {
        cout<<"Destructor arbore binar."<<endl;
        arbore<data, nod<data> >::~arbore();
    };
    void adauga (data inf) {
        if (arbore<data, nod<data> >::rad==nullptr) {
            arbore<data, nod<data> >::rad=new nod<data>;
            arbore<data, nod<data> >::rad->info=inf;
            arbore<data, nod<data> >::rad->st=arbore<data, nod<data> >::rad->dr=nullptr;
            return;
        }
        nod<data>* t=arbore<data, nod<data> >::rad;
        while (1) {
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
};


//avl.h

template <class data>
class avl:public arbore<data, nod_avl<data> > {
    public:
    avl():arbore<data, nod_avl<data> >() {};
    avl(data inf):arbore<data, nod_avl<data> >(inf) {};
    avl(const avl<data>& arb):arbore<data, nod_avl<data> >(arb) {};
    ~avl() {
        cout<<"Destructor avl."<<endl;
        arbore<data, nod_avl<data> >::~arbore();
    };

    //friend void rotatie_stanga(nod_avl<data>** root);
    //friend void rotatie_dreapta(nod_avl<data>** root);
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




int main()
{
    // i1=3, i2=5;
    nod<int> n1(3), n2(5), n3(7);
    cout<<"n2>n1: "<<(n2>n1)<<endl;
    cout<<"n2==n1: "<<(n2==n1)<<endl;
    arbore <int, nod<int> > arb1(3), arb2(arb1);
    cout<<"arb1: "<<arb1<<endl;
    cout<<"arb2: "<<arb2<<endl;
    arb2=arb2+11+12;
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

    return 0;
}
