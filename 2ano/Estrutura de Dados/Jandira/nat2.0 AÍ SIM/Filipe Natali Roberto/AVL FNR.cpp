//DESENVOLVIDO NO CODE::BLOCKS 10.05
//Alunos: Filipe Polina Affonso
//        Natali Silva Honda
//        Roberto Malcher de Barros
#include <cstdlib>
#include <iostream>

using namespace std;
template <class T>
class Node;
template <class T>
class Tree;

template <class T>
class Node
{
    Node<T>* parent;
    Node<T>* right;
    Node<T>* left;
    int BF;
    T element;
    Node(T elem)
    {
        left=right=parent=NULL;
        element=elem;
    }
    Node(T elem, Node<T>* a)
    {
        element=elem;
        right=left=NULL;
        parent=a;
    };
public:
    friend class Tree<T>;
};

template <class T>
class Tree
{
    Node<T>* root;
    Node<T>* last;
public:
    Tree();
    ~Tree();
    void destruct(Node<T>*);
    int Height(Node<T>*);
    int BalanceFactor(Node<T>*);
    bool Empty()
    {
        if(root==NULL)
            return true;
        else
            return false;
    }
    void CBF(Node<T>*);
    Node<T>* finder(Node<T>*);
    void AVL();
    void Insert(T);
    void InsertRec(T, Node<T>*);
    void Delete(T);
    Node<T>* DeleteRec(T, Node<T>*);
    void PreO()
    {
        if(Empty())
        {
            cout<<"\nEMPTY TREE\n";
        }
        else
        {
            cout<<"\n PreOrder\n\t";
            PreOrder(root);
            cout<<"\n";
        }
    };
    void PreOrder(Node<T>*);
    void PosO()
    {
        if(Empty())
        {
            cout<<"\nEMPTY TREE\n";
        }
        else
        {
            cout<<"\n PosOrder\n\t";
            PosOrder(root);
            cout<<"\n";
        }
    };
    void PosOrder(Node<T>*);
    void InO()
    {
        if(Empty())
        {
            cout<<"\nEMPTY TREE\n";
        }
        else
        {
            cout<<"\n InOrder \n\t";
            InOrder(root);
            cout<<"\n";
        }
    };
    void InOrder(Node<T>*);
    //void InOrder2(Node<T>*);
    //void Print(Node<T>*);
};

/*template <class T>
void Tree<T>::Print(Node<T>* ptr)
{
    cout<<"dado: "<<ptr->element<<" ptr->right: "<<ptr->right<<" ptr->left: "<<ptr->left<<"ptr: "<<ptr<<"pai:"<<ptr->parent <<"\n";
};

template <class T>
 void Tree<T>::InOrder2(Node<T>* ptr){
      Print(ptr);
      if(ptr->left!=NULL)
         InOrder2(ptr->left);
      if(ptr->right!=NULL)
          InOrder2(ptr->right);
}*/
template <class T>
int Tree<T>::BalanceFactor (Node<T> *ptr)
{
    int hd, he, factor;
    hd=Height(ptr->right);
    he=Height(ptr->left);
    factor=(hd - he);
	return factor;
};

template <class T>
int Tree<T>::Height (Node<T>* p)
{
	int hl,hr;
	if (p== NULL)
		return -1;
	else
	{
		hl = Height(p->left);
		hr = Height(p->right);

		if (hl > hr)
			return (1 + hl);
		else
			return (1 + hr);
	}

};

template <class T>
Tree<T>::Tree()
{
    root=last=NULL;

};
template <class T>
void Tree<T>::destruct(Node<T>* ptr)
 {
    if(ptr->left!=NULL)
    {
        destruct(ptr->left);
    }
    if(ptr->right!=NULL)
    {
        destruct(ptr->right);
    }
    delete ptr;
 };
template <class T>
Tree<T>::~Tree()
{
    if(Empty()){}
    else
    {
        destruct(root);
    }
};
template <class T>
void Tree<T>::Insert(T elem)
{

    if(root == NULL)
    {
        root = new Node<T>(elem);
        last=root;
    }
    else
    {
        InsertRec(elem,root);
    }
    CBF(root);
    AVL();
    CBF(root);
};

template <class T>
void Tree<T>::InsertRec(T elem, Node<T>* ptr)
{
    if(elem<ptr->element)
    {
        if(ptr->left == NULL)
        {
            ptr->left= new Node<T>(elem,ptr);
            last=ptr->left;
        }
        else
        {
            InsertRec(elem,ptr->left);
        }
    }
    if(elem>ptr->element)
    {
        if(ptr->right == NULL)
        {
            ptr->right= new Node<T>(elem,ptr);
            last=ptr->right;
        }
        else
        {
            InsertRec(elem,ptr->right);
        }
    }
};

template <class T>
Node<T>* Tree<T>::DeleteRec(T elem,Node<T>* ptr)
{
    Node<T>* ptr2;
    if(elem==ptr->element)
    {
        ptr2=ptr;
    }
    else
    {
        if(elem<ptr->element)
        {
            ptr2=DeleteRec(elem,ptr->left);
        }
        else
        {
            ptr2=DeleteRec(elem,ptr->right);
        }
    }
    return ptr2;
};

template <class T>
void Tree<T>::Delete(T elem)
{
    Node<T>* ptr;
    Node<T>* aux;
    if(root->element == elem)
    {
        ptr=root;
        if(ptr->right == NULL || ptr->left == NULL)
        {
            if(ptr->right != NULL)
            {
                aux=ptr;
                ptr=ptr->right;
                delete aux;
                root=last=ptr;
                ptr->parent=NULL;
            }
            else
            {
                if(ptr->left != NULL)
                {
                    aux=ptr;
                    ptr=ptr->left;
                    delete aux;
                    root=last=ptr;
                    ptr->parent=NULL;
                }
                else
                {
                    root=last=NULL;
                    delete ptr;
                    return;
                }
            }

        }
        else
        {
            if(ptr->right->left!=NULL)
            {
                aux=ptr;
                ptr=ptr->right->left;
                aux->left->parent=ptr;
                aux->right->left=NULL;
                ptr->parent->parent=ptr;
                ptr->right=aux->right;
                ptr->left=aux->left;
                last=aux->right;
                ptr->parent=NULL;
                delete aux;
                root=ptr;

            }
            else
            {
                if(ptr->left->right != NULL)
                {
                        aux=ptr;
                        ptr=ptr->left->right;
                        aux->right->parent=ptr;
                        aux->left->right=NULL;
                        ptr->parent->parent=ptr;
                        ptr->right=aux->right;
                        ptr->left=aux->left;
                        last=aux->left;
                        ptr->parent=NULL;
                        delete aux;
                        root=ptr;
                }
                else
                {
                    aux=ptr;
                    ptr=ptr->left;
                    aux->right->parent=ptr;
                    ptr->right=aux->right;
                    delete aux;
                    ptr->parent=NULL;
                    root=ptr;
                }
            }
        }
    }
    else
    {
        ptr=DeleteRec(elem,root);
        if(ptr->right != NULL)
        {
            if(ptr->right->left!=NULL)
            {
                aux=ptr;
                ptr=ptr->right->left;
                ptr->parent->parent=ptr;
                ptr->parent->left=ptr->right;
                if(ptr->left != NULL)
                    ptr->left->parent=ptr->right;
                ptr->right=aux->right;
                ptr->left=aux->left;
                last=ptr->parent;
                ptr->parent=aux->parent;
                if(ptr->element < aux->parent->element)
                {
                    aux->parent->left=ptr;
                }
                else
                {
                    aux->parent->right=ptr;
                }
                delete aux;
            }
            else
            {
                if(ptr->left != NULL)
                {
                    if(ptr->left->right!=NULL)
                    {
                        aux=ptr;
                        ptr=ptr->left->right;
                        aux->left->parent=ptr;
                        ptr->parent->parent=ptr;
                        ptr->parent->right=ptr->left;
                        if(ptr->right != NULL)
                            ptr->right->parent=ptr->left;
                        ptr->left=aux->left;
                        ptr->right=aux->right;
                        last=ptr->parent;
                        ptr->parent=aux->parent;
                        if(aux->element < aux->parent->element)
                        {
                            aux->parent->left=ptr;
                        }
                        else
                        {
                            aux->parent->right=ptr;
                        }
                        delete aux;
                    }
                    else
                    {
                        aux=ptr;
                        ptr=ptr->right;
                        ptr->parent=aux->parent;
                        ptr->right=aux->right;
                        aux->right->parent=ptr;
                        if(aux->element<aux->parent->element)
                        {
                            aux->parent->left=ptr;
                        }
                        else
                        {
                            aux->parent->right=ptr;
                        }
                        delete aux;
                        last=ptr;
                    }
                }
                else
                {

                    aux=ptr;
                    ptr=ptr->right;
                    ptr->parent=aux->parent;
                    if(ptr->element<aux->parent->element)
                    {
                        aux->parent->left=ptr;
                    }
                    else
                    {
                        aux->parent->right=ptr;
                    }
                    delete aux;
                    last=ptr;
                }
            }
        }
        else
        {
            if(ptr->left != NULL)
                {
                    if(ptr->left->right!=NULL)
                    {
                        aux=ptr;
                        ptr=ptr->left->right;
                        aux->left->parent=ptr;
                        ptr->parent->parent=ptr;
                        ptr->parent->right=ptr->left;
                        if(ptr->right != NULL)
                            ptr->right->parent=ptr->left;
                        ptr->left=aux->left;
                        ptr->right=aux->right;
                        last=ptr->parent;
                        ptr->parent=aux->parent;
                        if(aux->element < aux->parent->element)
                        {
                            aux->parent->left=ptr;
                        }
                        else
                        {
                            aux->parent->right=ptr;
                        }
                        delete aux;
                    }
                    else
                    {
                        aux=ptr;
                        ptr=ptr->left;
                        ptr->parent=aux->parent;
                        ptr->right=aux->right;
                        aux->right->parent=ptr;
                        if(aux->element<aux->parent->element)
                        {
                            aux->parent->left=ptr;
                        }
                        else
                        {
                            aux->parent->right=ptr;
                        }
                        delete aux;
                        last=ptr;
                    }
                }
                else
                {
                    aux=ptr;
                    ptr=ptr->parent;
                    if(ptr->left != NULL)
                    {
                        if(ptr->left->element == aux->element)
                        {
                            ptr->left=NULL;
                            delete aux;
                        }
                        else
                        {
                            ptr->right=NULL;
                            delete aux;
                        }
                    }
                    else
                    {
                        ptr->right=NULL;
                        delete aux;
                    }

                }
                    last=ptr;
            }
    }
    CBF(root);
    AVL();
    CBF(root);
};

template <class T>
Node<T>* Tree<T>::finder(Node<T>* ptr)
{
    Node<T>* ptr2;
    ptr2=NULL;
    if(ptr->BF==2 || ptr->BF==-2)
    {
        ptr2=ptr;
    }
    else if(ptr->parent!=NULL)
        ptr2=finder(ptr->parent);
    return ptr2;
};

template <class T>
void Tree<T>::AVL()
{

        Node<T>* ptr;
        ptr=finder(last);
    if(ptr != NULL){
            if(ptr->BF==2 || ptr->BF==-2)
            {
                Node<T>* aux;
                if(ptr==root)
                {
                    if((ptr->BF)<0)
                    {
                        if((ptr->left->BF)<=0)
                        {
                            aux=ptr->left;
                            ptr->left=NULL;
                            aux->right=ptr;
                            ptr->parent=aux;
                            //rot simples
                        }
                        else
                        {
                            aux=ptr->left->right;
                            ptr->left->right=NULL;
                            ptr->left->parent=aux;
                            aux->left=ptr->left;
                            ptr->left=aux->right;
                            aux->right=ptr;
                            ptr->parent=aux;
                            //rot dupla
                        }
                        root=aux;
                        aux->parent=NULL;
                    }
                    else if((ptr->BF)>0)
                    {
                        if((ptr->right->BF)>=0)
                        {
                            aux=ptr->right;
                            ptr->right=aux->left;
                            aux->left=ptr;
                            ptr->parent=aux;
                            //rot simples
                        }
                        else
                        {
                            aux=ptr->right->left;
                            ptr->right->left=NULL;
                            ptr->right->parent=aux;
                            aux->right=ptr->right;
                            ptr->right=aux->left;
                            aux->left=ptr;
                            ptr->parent=aux;
                            //rot dupla
                        }
                        root=aux;
                        aux->parent=NULL;
                    }
                }
                else
                {
                   if((ptr->BF)<0)
                    {
                        if(ptr->left != NULL && (ptr->left->BF)<=0)
                        {
                            aux=ptr->left;
                            ptr->left=aux->right;
                            aux->right=ptr;
                            aux->parent = ptr->parent;
                            ptr->parent->left = aux;
                            ptr->parent=aux;
                            if(ptr->left != NULL)
                                ptr->left->parent = ptr;
                                //rot simples
                        }
                        else
                        {
                            aux=ptr->left->right;
                            ptr->parent->left = aux;
                            aux->parent = ptr->parent;
                            ptr->left->right=aux->left;
                            if(aux->left != NULL)
                                aux->left->parent = ptr->left;
                            aux->left=ptr->left;
                            ptr->left->parent = aux;
                            ptr->left=aux->right;
                            if(aux->right != NULL)
                                aux->right->parent = ptr;
                            aux->right=ptr;
                            ptr->parent = aux;
                            //rot dupla
                        }
                    }

                    else if((ptr->BF)>0)
                    {
                        if((ptr->right->BF)>=0)
                        {
                            aux=ptr->right;
                            ptr->right=aux->left;
                            aux->left=ptr;
                            aux->parent = ptr->parent;
                            ptr->parent->right = aux;
                            ptr->parent=aux;
                            if(ptr->right != NULL)
                                ptr->right->parent = ptr;
                            //rot simples
                        }
                        else
                        {
                            aux=ptr->right->left;
                            ptr->parent->right = aux;
                            aux->parent = ptr->parent;
                            ptr->right->left=aux->right;
                            if(aux->right != NULL)
                                aux->right->parent = ptr->right;
                            aux->right=ptr->right;
                            ptr->right->parent = aux;
                            ptr->right=aux->left;
                            if(aux->left != NULL)
                                aux->left->parent = ptr;
                            aux->left=ptr;
                            ptr->parent = aux;
                            //rot dupla
                        }
                    }
                }
            }
    }
};

template <class T>
void Tree<T>::CBF(Node<T>* ptr)
{
    if(ptr->left!=NULL)
        CBF(ptr->left);
    ptr->BF=BalanceFactor(ptr);
    if(ptr->right!=NULL)
        CBF(ptr->right);
    ptr->BF=BalanceFactor(ptr);
}

template <class T>
 void Tree<T>::InOrder(Node<T>* ptr)
 {

 if(ptr->left!=NULL)
 InOrder(ptr->left);
 cout<<ptr->element<<"\t";
 if(ptr->right!=NULL)
 InOrder(ptr->right);
 }
template <class T>
void Tree<T>::PreOrder(Node<T>* ptr)
{
    cout<<ptr->element<<"\t";
    if(ptr->left!=NULL)
        PreOrder(ptr->left);
    if(ptr->right!=NULL)
        PreOrder(ptr->right);
}
template <class T>
 void Tree<T>::PosOrder(Node<T>* ptr)
 {
 if(ptr->left!=NULL)
 PosOrder(ptr->left);
 if(ptr->right!=NULL)
 PosOrder(ptr->right);
 cout<<ptr->element<<"\t";
 }
int main(int argc, char *argv[])
{
    Tree<int> t;
    t.Insert(1);
    t.Insert(2);
    t.Insert(3);
    t.Insert(4);
    t.Insert(5);
    t.InO();
    t.PreO();
    t.PosO();
    t.Delete(1);
    t.InO();
    t.PreO();
    t.PosO();
    t.Delete(2);
    t.InO();
    t.PreO();
    t.PosO();
    t.Delete(3);
    t.InO();
    t.PreO();
    t.PosO();
    t.Delete(4);
    t.InO();
    t.PreO();
    t.PosO();
    t.Delete(5);
    t.InO();
    t.PreO();
    t.PosO();
    cout<<"\n";
    system("pause");
}
