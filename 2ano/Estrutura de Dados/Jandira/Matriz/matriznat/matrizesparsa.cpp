#include <cstdlib>
#include <iostream>
#include <cstdio>
using namespace std;
template <class X>
class no;
template <class X>
class matriz;
template <class X>
class no
{
    int lin;
    int col;
    X dado;
    no<X>* prox;
    no<X>* ant;
    no<X>* cima;
    no<X>* baixo;
    no(){ prox=NULL;ant=NULL;cima=NULL;baixo=NULL;dado=0;lin= -1;col= -1;}
    no(int lin, int col, X d){
        prox=NULL;ant=NULL;cima=NULL;baixo=NULL;
        dado = d;
        this->lin = lin;
        this->col = col;
    }
public:
    friend class matriz<X>;
};

template <class X>
class matriz
{
    int maiorl;
    int maiorc;
    no<X> *starter;
public:
    matriz()
    {
        starter=NULL;
        maiorl = (-1);
        maiorc = (-1);
    }
    bool vazio(){
        if(starter==NULL)
            return true;
        else
            return false;
    }
    ~matriz(){
        no<X>* aux;
        no<X>* aux2;
        no<X>* ptr = starter;
        while(ptr->baixo != NULL ){
            ptr = ptr->baixo;
            aux = ptr->prox;
            while(aux != NULL){
                aux2 = aux;
                aux = aux->prox;
                delete aux2;
            }
        }
        ptr = starter->prox;
        while(ptr != NULL ){
            aux = ptr;
            ptr = ptr->prox;
            delete aux;
        }
        ptr = starter->baixo;
        while(ptr != NULL ){
            aux = ptr;
            ptr = ptr->baixo;
            delete aux;
        }
        delete starter;
    };
    void inserir (int,int,X);
    void excluir (int,int);
    void imprimir();
    void RecMax();
};

template <class X>
void matriz<X>:: inserir(int linha, int coluna, X d){
    if(maiorc < coluna)
        maiorc = coluna;
    if(maiorl < linha)
        maiorl = linha;

    no<X>* temp = new no<X>(linha, coluna, d);
    no<X>* NoLinha;
    no<X>* ptrL;
    no<X>* NoColuna;
    no<X>* ptrC;
    if(!vazio()){
        NoLinha = this->starter->baixo;
        ptrL = this->starter;
        while( NoLinha->lin < linha ){
            ptrL = NoLinha;
            NoLinha = NoLinha->baixo;
        }
        if(NoLinha->lin == linha){
            NoColuna = this->starter->prox;
            ptrC = this->starter;
            while( NoColuna->col < coluna ){
                ptrC = NoColuna;
                NoColuna = NoColuna->prox;
            }
            if(NoColuna->col == coluna){
                while(NoColuna->lin < linha){
                    ptrC = NoColuna;
                    NoColuna = NoColuna->baixo;
                }
                while(NoLinha->col < coluna){
                    ptrL = NoLinha;
                    NoLinha = NoLinha->prox;
                }
                if(NoLinha->col == coluna && NoColuna->lin == linha)
                    NoLinha->dado = d;
                else{
                    ptrC->baixo = temp;
                    ptrC->baixo->cima = ptrC;
                    temp->baixo = NoColuna;
                    NoColuna->cima = temp;

                    ptrL->prox = temp;
                    ptrL->prox->ant = ptrL;
                    temp->prox = NoLinha;
                    NoLinha->ant = temp;
                }
            }
            else{
                ptrC->prox = new no<X>(-1, coluna, 0);
                ptrC->prox->baixo = temp;
                ptrC->prox->ant = ptrC;
                temp->cima = ptrC->prox;
                ptrC->prox->prox = NoColuna;
                NoColuna->ant = ptrC->prox;

                while(NoLinha->col < coluna){
                    ptrL = NoLinha;
                    NoLinha = NoLinha->prox;
                }
                ptrL->prox = temp;
                ptrL->prox->ant = ptrL;
                temp->prox = NoLinha;
                NoLinha->ant = temp;
            }
        }
        else{
            ///------------------------------
            NoColuna = this->starter->prox;
            ptrC = this->starter;
            while( NoColuna->col < coluna ){
                ptrC = NoColuna;
                NoColuna = NoColuna->prox;
            }
            if(NoColuna->col == coluna){
                while(NoColuna->baixo->lin < linha){
                    ptrC = NoColuna;
                    NoColuna = NoColuna->baixo;
                }
                ptrC->baixo = temp;
                ptrC->baixo->cima = ptrC;
                temp->baixo = NoColuna;
                NoColuna->cima = temp;

                ptrL->baixo = new no<X>(linha, -1, 0);
                ptrL->baixo->prox = temp;
                ptrL->baixo->cima = ptrL;
                temp->ant = ptrL->baixo;
                ptrL->baixo->baixo = NoLinha;
                NoLinha->cima = ptrL->baixo;
            }
            else{
                ptrC->prox = new no<X>(-1, coluna, 0);
                ptrC->prox->baixo = temp;
                ptrC->prox->ant = ptrC;
                temp->cima = ptrC->prox;
                ptrC->prox->prox = NoColuna;
                NoColuna->ant = ptrC->prox;

                ptrL->baixo = new no<X>(linha, -1, 0);
                ptrL->baixo->prox = temp;
                ptrL->baixo->cima = ptrL;
                temp->ant = ptrL->baixo;
                ptrL->baixo->baixo = NoLinha;
                NoLinha->cima = ptrL->baixo;
            }
            ///------------------
        }
    }
    else{
        this->starter  = new no<X>(-1, -1, 0);
        NoLinha = new no<X>(linha, -1, 0);
        NoColuna = new no<X>(-1, coluna, 0);

        this->starter->prox = NoColuna;
        NoColuna->ant = this->starter;
        this->starter->baixo = NoLinha;
        NoLinha->cima = this->starter;

        temp->cima = NoColuna;
        NoColuna->baixo = temp;
        temp->ant = NoLinha;
        NoLinha->prox = temp;
    }
}

template <class X>
void matriz<X>:: excluir (int linha, int coluna){

    no<X>* aux;
    no<X>* ptr;
    aux = starter;
    while(aux!=NULL && aux->lin !=linha)
        aux = aux->baixo;
    if(aux!=NULL && linha == aux->lin)
    {
        while(aux != NULL && aux->col != coluna )
            aux=aux->prox;
        if(aux != NULL && aux->col==coluna)
        {
            aux->cima->baixo=aux->baixo;
            if(aux->baixo != NULL)
                aux->baixo->cima=aux->cima;
            if(aux->prox != NULL)
                aux->prox->ant=aux->ant;
            aux->ant->prox=aux->prox;
            delete aux;
        }
    }
    RecMax();
}

template <class X>
void matriz<X>:: RecMax(){
    no<X>* aux = starter;
    while(aux->baixo!=NULL)
        aux = aux->baixo;
    while(aux!= starter && aux->prox == NULL)
        aux = aux->cima;
    maiorl = aux->lin;

    aux = starter;
    while(aux->prox!=NULL)
        aux = aux->prox;
    while(aux!= starter && aux->baixo == NULL)
        aux = aux->ant;
    maiorc = aux->col;
}

template <class X>
void matriz<X>:: imprimir(){
    no <X>* auxl;
    no <X>* aux;

   // cout << "Maior L: "<<maiorl << " Maior C: " << maiorc << endl;

    auxl=starter->baixo;
    for(int i=0;i<=maiorl;i++)
    {
        if(auxl->lin==i)
        {
            aux=auxl->prox;
            for(int j=0;j<=maiorc;j++)
            {
                if(aux->col==j)
                {
                    cout << aux->dado <<" ";
                    if(aux->prox!=NULL)
                    {
                        aux=aux->prox;
                    }
                }
                else
                {
                    cout<<"0 ";
                }
            }
            if(auxl->baixo!=NULL)
            {
                auxl=auxl->baixo;
            }
        }
        else
        {
            for(int j=0;j<=maiorc;j++)
            {
                cout<<"0 ";
            }
        }
        cout << endl;
    }

    /*
    no <X>* auxLinha;
    no <X>* auxCol;

    for( auxLinha = starter ; auxLinha != NULL ; auxLinha = auxLinha->baixo){
         printf("Linha -> meu %d lin %d col %d ((cima %d, baixo %d) dado %d (ant %d, prox %d))\n", auxLinha, auxLinha->lin, auxLinha->col, auxLinha->cima, auxLinha->baixo, auxLinha->dado, auxLinha->ant, auxLinha->prox);
         for( auxCol = auxLinha->prox ; auxCol != NULL ; auxCol = auxCol->prox){
              printf(" \t meu %d lin %d col %d ((cima %d, baixo %d) dado %d (ant %d, prox %d))\n", auxCol, auxCol->lin, auxCol->col, auxCol->cima, auxCol->baixo, auxCol->dado, auxCol->ant, auxCol->prox);
         }
         printf("\n");
    }*/
}

int main(int argc, char *argv[])
{
    matriz<int> teste;
    teste.inserir(3,3,1);
    teste.imprimir();
    cout<<"\n";
    teste.inserir(2,2,9);
    teste.imprimir();
    cout<<"\n";
    teste.inserir(2,1,8);
    teste.imprimir();
    cout<<"\n";
    teste.inserir(1,2,7);
    teste.imprimir();
    cout<<"\n";
    teste.inserir(1,1,6);
    teste.imprimir();
    cout<<"\n";
    teste.excluir(3,3);
    teste.imprimir();
    system("PAUSE");

}

