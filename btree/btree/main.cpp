#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <stdexcept>
typedef long long PageID;
using namespace std;

class Page {

private:
  int size;
  PageID id;
  char * data;

public:
  Page(int nSize) {
    size = nSize;
    data = new char[size];
  };

  ~Page() {
    delete[] data;
  };

  int getSize() {
    return size;
  };

  void setId(PageID nId) {
    id = nId;
  };

  PageID getId() {
    return id;
  };

  // setData é feito diretamente pelo ponteiro retornado por getData()
  // Portanto, cuidado ao gerenciar externamente esse ponteiro!
  char * getData() {
    return data;
  };
};//end class Page

//---------------------------------------------------------------------------------------

class PageManager {

private:
  fstream * dataFile;
  int pageSize;
  int nPages;
  int headerSize;

public:
  PageManager(string fileName,int nPageSize)
  {
    dataFile = new fstream (fileName.data(), ios::in | ios::out);
    pageSize = nPageSize;
  };
  // Cria/abre o arquivo que armazena a estrutura e define o tamanho de página

  ~PageManager()
  {
  };
  // Atualiza o header, se necessário, fecha o arquivo e libera os recursos

  Page * getNewPage()
  {
    Page * p = new Page(pageSize);
    dataFile->seekg(0,fstream::end);
    dataFile->write(p->getData(),pageSize);
    p->setId(++nPages);
    return p;
  };
  // Reserva espaço no arquivo e retorna uma nova página

  Page * getPage(PageID pageId)
  {
    Page * p = new Page(pageSize);
    dataFile->seekp(fstream::beg+headerSize+(pageId-1)*pageSize);
    dataFile->read(p->getData(),pageSize);
    p->setId(pageId);
    return p;
  };
  // Carrega do arquivo a página com o pageId indicado e retorna

  void writePage(Page * page)
  {
    dataFile->seekg(fstream::beg+headerSize+(page->getId()-1)*pageSize);
    dataFile->write(page->getData(),pageSize);
  };
  // Escreve a página no arquivo, na posição indicada pelo seu pageId

  void releasePage(Page * page);
  // Destrói a instância de page, liberando memória

  void deletePage(Page * page);
  // Remove (ou marca como removida) a página do arquivo

  PageID getRootPageId();
  // Retorna o identificador da raiz da estrutura

  void setRootPageId();
  // Atualiza o identificador da raiz da estrutura
};//end class PageManager

//---------------------------------------------------------------------------------------

template < class KeyType, int OBJECT_SIZE >
class BNode {

private:
  int maxEntries;
  int * numEntries;
  PageID * pointers;
  KeyType * keys;
  char * objects;

public:
  BNode(Page * page, bool isNew) {
    int entrySize = sizeof(PageID) + sizeof(KeyType) + OBJECT_SIZE;
    maxEntries = (page->getSize() - sizeof(PageID)) / entrySize;

    numEntries = (int *) page->getData();
    pointers = (PageID *) (page->getData() + sizeof(int));
    keys = (KeyType *) (page->getData() + sizeof(int) + (maxEntries * sizeof(PageID)));
    objects = (char *) page->getData() + sizeof(int) + (maxEntries * (sizeof(PageID) + sizeof(KeyType)));

    if (isNew) {
      *numEntries = 0;
      pointers[0] = 0; //indica que o nó não tem filhos
    }
  }

  void setPointer(int i, PageID pageId) {
    if ((i < 0) || (i >= maxEntries))
      throw out_of_range("Index out of range");
    pointers[i] = pageId;
  }

  PageID getPointer(int i) {
    if ((i < 0) || (i >= maxEntries))
      throw out_of_range("Index out of range");
    return pointers[i];
  }

  void setKey(int i, KeyType key) {
    if ((i < 0) || (i >= maxEntries))
      throw out_of_range("Index out of range");
    keys[i] = key;
  }

  KeyType getKey(int i) {
    if ((i < 0) || (i >= maxEntries))
      throw out_of_range("Index out of range");
    return keys[i];
  }

  void setObject(int i, char * obj) {
    if ((i < 0) || (i >= *numEntries))
      throw out_of_range("Index out of range");
    memcpy(objects[i * OBJECT_SIZE], obj, OBJECT_SIZE);
  }

  char * getObject(int i) {
    if ((i < 0) || (i >= maxEntries))
      throw out_of_range("Index out of range");
    char * outObj = new char[OBJECT_SIZE];
    memcpy(outObj, objects[i * OBJECT_SIZE], OBJECT_SIZE);
    return outObj; //outObj deve ser destruido por quem chama essa funcao
  }

  void setNumEntries(int nEntries) {
    *numEntries = nEntries;
  }

  int getNumEntries() {
    return *numEntries;
  }

  void incNumEntries(int increment = 1) {
    if (*numEntries == maxEntries)
      throw runtime_error("Node full");
    *numEntries += increment;
  }

  void decNumEntries(int decrement = 1) {
    if (*numEntries == 0)
      throw runtime_error("Node empty");
    *numEntries -= decrement;
  }

  int nodeSearch(KeyType key) {
    // busca binária retornando a posição onde a chave está ou onde deveria ser inserida
  }

};//end class BNode

//---------------------------------------------------------------------------------------

/*template < class KeyType, int OBJECT_SIZE >
class BTree {

private:
  enum status{InsertNotComplete, Success, DuplicateKey, Underflow, NotFound}

  PageManager * pageManager;

  status ins(PageID pageId, KeyType key, char * obj, KeyType & keyUp, char ** objUp, PageID & pointerUp);
  status rem(PageID pageId, KeyType key);

public:
  BTree(PageManager * pManager) {
    pageManager = pManager;
  }
  ~BTree();

  void insert(KeyType key, char * obj);
  void remove(KeyType key) ;

}//end class BTree

//---------------------------------------------------------------------------------------

void BTree::insert(KeyType key, char * obj) {
  PageID pointerUp;
  KeyType keyUp;
  char * objUp;

  status code = ins(pageManager->getRootPageID(), key, obj, keyUp, &objUp, pointerUp);

  if (code == DuplicateKey) {
    cout << "Duplicate key ignored.\n";
    return;
  }

  if (code == InsertNotComplete) {
    Page * newPage;
    newPage = pageManager->getNewPage();
    BNode newRootNode(newPage, true);

    newRootNode.setPointer(0, pageManager->getRootPageID());
    newRootNode.setKey(0, keyUp);
    newRootNode.setObject(0, objUp);
    newRootNode.incNumEntries();
    newRootNode.setPointer(1, pointerUp);

    pageManager->setRootPageID(newPage->getId());
    pageManager->writePage(newPage);
    pageManager->releasePage(newPage);
  }

  cout << "Success.\n";
}//end BTree::insert()

//---------------------------------------------------------------------------------------

status BTree::ins(PageID pageId, KeyType key, char * obj, KeyType & keyUp, char ** objUp, PageID & pointerUp) {

  int i, j;
  status code;

  if (PageID == 0) {
    keyUp = key;
    *objUp = obj;
    pointerUp = 0;
    return InsertNotComplete;
  }

  Page * page = pageManager->getPage(pageId);
  BNode node(page, false);

  i = node.search(key);

  if (i < node.getNumEntries() && key == node.getKey(i))
    return DuplicateKey;

  status code = ins(node.getPointer(i), key, obj, keyUp, objUp, pointerUp);
  if (code != InsertNotComplete)
    return code;

  // VERIFIQUE SE AINDA CABE NO NÓ CORRENTE
  if (node.getNumEntries() < node.getMaxEntries()) {
    for (j = node.getNumEntries(); j > i, j--) {
      node.setKey(j, node.getKey(j - 1));
      node.setObject(j, node.getObject(j - 1));
      node.setPointer(j + 1, node.getPointer(j));
    }
    node.setKey(i, keyUp);
    node.setObject(i, objUp);
    node.setPointer(i + 1, pointerUp);
    node.incNumEntries();
    pageManager->writePage(page);
    pageManager->releasePage(page);

    return Success;
  }

  //O NÓ CORRENTE ESTÁ CHEIO E SOFRERÁ SPLIT.
  Page * newPage = pageManager->getNewPage();
  BNode newNode(newPage, true);

  KeyType lastKey;
  char * lastObj;
  PageID lastPointer;

  if (i == node.getNumEntries()) { //O OVERFLOW (lastKey, lastObj, lastPointer) ESTÁ NA CHAVE/PONTEIRO QUE SUBIRAM
    lastKey = keyUp;
    lastObj = objUp;
    lastPointer = pointerUp;
  }
  else { //O OVERFLOW NÃO ESTÁ NA CHAVE/PONTEIRO QUE SUBIRAM, DESLOQUE AS ENTRADAS DO NÓ
    lastKey = node.getKey(node.getNumEntries() - 1);
    lastObj = node.getObject(node.getNumEntries() - 1);
    lastPointer = node.getPointer(node.getNumEntries());
    for (j = node.getMaxEntries() - 1; j > i; j--) {
      node.setKey(j, node.getKey(j - 1));
      node.setObject(j, node.getObject(j - 1));
      node.setPointer(j + 1, node.getPointer(j));
    }
    node.setKey(i, keyUp);
    node.setObject(i, objUp);
    node.setPointer(i + 1, pointerUp);
  }

  int median = node.getMaxEntries() / 2; // IDENTIFIQUE O ÍNDICE DO ELEMENTO CENTRAL QUE IRÁ "SUBIR"
  keyUp = node.getKey(median); // ELEMENTO CENTRAL
  objUp = node.getObject(median); // ELEMENTO CENTRAL
  pointerUp = newPage->getId(); // RETORNE O "PONTEIRO" PARA O NOVO NÓ

  // MOVA AS ENTRADAS A PARTIR DE median + 1 DO NÓ ATUAL (LEFT) PARA O NOVO NÓ (RIGHT), E ACRESCENTE O OVERFLOW NO NOVO NÓ
  newNode.setNumEntries(node.getNumEntries() - median); //p[median+1],k[median+1],...,k[numEntries()-1],p[numEntries()],lastKey,lastPointer VAO PARA O NOVO NÓ (RIGHT)
  for (j = 0; j < newNode.getNumEntries(); j++) {
    newNode.setPointer(j, node.getPointer(j + median + 1));
    if (j < newNode.getNumEntries() - 1) {
      newNode.setKey(j, node.getKey(j + median + 1));
      newNode.setObject(j, node.getObject(j + median + 1));
    }
    else {
      newNode.setKey(j, lastKey);
      newNode.setObject(j, lastObj);
    }
  }
  newNode.setPointer(newNode.getNumEntries(), lastPointer);

  // "REMOVER" DO NÓ ATUAL (LEFT) AS ENTRADAS QUE FORAM PARA O NOVO NÓ (RIGHT)
  node.setNumEntries(median); // p[0],k[0],p[1],...,k[median-1],p[median] CONTINUAM NESTE NÓ (LEFT)

  // ATUALIZE OS NÓS (ANTIGO (LEFT) E NOVO (RIGHT)) EM DISCO
  pageManager->writePage(page);
  pageManager->releasePage(page);
  pageManager->writePage(newPage);
  pageManager->releasePage(newPage);

  return InsertNotComplete;
}//end BTree::ins()

//---------------------------------------------------------------------------------------

void BTree::remove(KeyType key) {
  status code = rem(pageManager->getRootPageID(), key);
  if (status == NotFound) {
    cout << "Not found.\n";
    return;
  }

  if (status == Underflow) {
    Page * page;
    page = pageManager->getPage(pageManager->getRootPageID());
    BNode oldRootNode(page, false);
    pageManager->setRootPageID(oldRootNode.getPointer(0)); //Nova raiz é filha de oldRootNode
    pageManager->deletePage(page);
  }

  cout << "Success.\n";
}//end BTree::delete()

//---------------------------------------------------------------------------------------

status BTree::rem(PageID pageId, KeyType key) {
  if (pageId == 0)
    return NotFound; // (SUB)ARVORE VAZIA

  int i, j;
  status code;
  Page * page = pageManager->getPage(pageId);
  BNode node(page, false);

  i = node.search(key);

  // O nó corrente é folha?
  if (node.getPointer(0) == 0) {
    // A chave a ser removida está em node?
    if (i >= node.getNumEntries() || key != node.getKey(i)) {
      // Não, chave não encontrada
      pageManager->releasePage(page);
      return NotFound;
    }

    // Sim, a chave a ser removida é node.getKey(i)
    for (j = i; j < node.getNumEntries() - 1; j++) {
      node.setKey(j, node.getKey(j + 1));
      node.setObject(j, node.getObject(j + 1));
      node.setPointer(j + 1, node.getPointer(j + 2));
    }
    node.decNumEntries();

    status ret;
    // O nó corrente é a raiz?
    if (pageId == pageManager->getRootPageID()) {
      if (node.getNumEntries() >= 1)
	ret = Success;
      else
	ret = Underflow;
    }
    else {
      if (node.getNumEntries() >= (int) (node.getMaxEntries() / 2))
	ret = Success;
      else
	ret = Underflow;
    }

    pageManager->writePage(page);
    pageManager->releasePage(page);
    return ret;
  }

  // O nó corrente é um nó interno
  // A CHAVE A SER REMOVIDA está em node?
  if (i < node.getNumEntries() && key == node.getKey(i)) {
    // Encontre a maior chave menor que key (filho mais à direita da subárvore à esquerda de key[i])
    PageID nextPageId = node.getPointer(i);
    Page * pageFilho;
    BNode * nodeFilho;

    for (;;) {
      pageFilho = pageManager->getPage(nextPageId);
      nodeFilho = new BNode(pageFilho, false);

      // Encontrou a folha mais à direita?
      if (nodeFilho->getPointer(0) == 0) {
	break;
      }
      else {
	// Visite o nó mais à direita de nodeFilho
	nextPageId = nodeFilho->getPointer(nodeFilho->getNumEntries());
	pageManager->releasePage(pageFilho);
	delete nodeFilho;
      }
    }//end for

    // TROQUE A CHAVE A SER REMOVIDA DO NÓ INTERNO PELA MAIOR CHAVE DE nodeFilho
    KeyType tmpKey;
    char * tmpObj;

    tmpKey = node.getKey(i);

    node.setKey(i, nodeFilho.getKey(nodeFilho.getNumEntries() - 1));
    node.setObject(i, nodeFilho.getObject(nodeFilho.getNumEntries() - 1));
    nodeFilho.setKey(nodeFilho.getNumEntries() - 1, tmpKey);
    pageManager->writePage(page);
    pageManager->writePage(pageFilho);
    pageManager->releasePage(pageFilho);
    delete nodeFilho;
  }

  // Visite o próximo filho
  code = rem(node.getPointer(i), key);

  if (code != Underflow) {
    pageManager->releasePage(page);
    return code;
  }

  // O NÓ APONTADO POR node.getPointer(i) SOFREU UM UNDERFLOW
  Page * underflowPage = pageManager->getPage(node.getPointer(i));
  BNode underflowNode(underflowPage, false);

  // underflowNode tem irmão à esquerda?
  if (i > 0) {
    Page * leftBrotherPage = pageManager->getPage(node.getPointer(i - 1));
    BNode leftBrotherNode(leftPage, false);

    // leftBrotherNode pode emprestar para underflowNode?
    if (leftBrotherNode.getNumEntries() > (int) (leftBrotherNode.getMaxEntries() / 2)) {

      // libere espaço em underflowNode para a entrada emprestada, deslocando as entradas existentes para a direita
      underflowNode.setPointer(underflowNode.getNumEntries() + 1, node.getPointer(underflowNode.getNumEntries()));
      for (j = underflowNode.getNumEntries(); j > 0; j--) {
	underflowNode.setKey(j, node.getKey(j - 1));
        underflowNode.setObject(j, node.getObject(j - 1));
        underflowNode.setPointer(j, node.getPointer(j - 1));
      }

      // desça node.getKey(i - 1) para underflowNode
      underflowNode.setKey(0, node.getKey(i - 1));
      underflowNode.setObject(0, node.getObject(i - 1));

      // coloque a subárvore mais à direita de leftBrotherNode como a subárvore mais à esquerda de underflowNode
      underflowNode.setPointer(0, leftBrotherNode.getPointer(leftBrotherNode.getNumEntries()));

      // suba leftBrotherNode.getKey(leftBrotherNode.getNumEntries() - 1) para node
      node.setKey(i - 1, leftBrotherNode.getKey(leftBrotherNode.getNumEntries() - 1));
      node.setObject(i - 1, leftBrotherNode.getObject(leftBrotherNode.getNumEntries() - 1));

      // atualize as quantidades de entradas de leftBrotherNode e underflowNode
      leftBrotherNode.decNumEntries();
      underflowNode.incNumEntries();

      // escreva em disco os nós alterados e libere os recursos
      pageManager->writePage(leftBrotherPage);
      pageManager->releasePage(leftBrotherPage);
      pageManager->writePage(underflowPage);
      pageManager->releasePage(underflowPage);
      pageManager->writePage(page);
      pageManager->releasePage(page);
      return Success;
    }//end if (leftBrotherNode pode emprestar)

    // se underflowNode não tiver irmão à direita, underflowNode e leftBrotherNode sofrerão unsplit
    if (i >= node.getNumEntries()) {
      // desça node.getKey(i - 1) para leftBrotherNode
      leftBrotherNode.setKey(leftBrotherNode.getNumEntries(), node.getKey(i - 1));
      leftBrotherNode.setObject(leftBrotherNode.getNumEntries(), node.getObject(i - 1));

      // desloque as entradas restantes em node para a esquerda
      for (j = 0; j < node.getNumEntries(); j++) {
        node.setKey(j, node.getKey(j + 1));
        node.setObject(j, node.getObject(j + 1));
        node.setPointer(j, node.getPointer(j + 1));
      }
      node.setPointer(node.getNumEntries(), node.getNumEntries() + 1);

      // atualize a quantidade de entradas de node
      node.decNumEntries();

      // copie as entradas de underflowNode para leftBrotherNode
      for (j = 0; j < underflowNode.getNumEntries(); j++) {
        leftBrotherNode.setKey(j + leftBrotherNode.getNumEntries() + 1, underflowNode.getKey(j));
        leftBrotherNode.setObject(j + leftBrotherNode.getNumEntries() + 1, underflowNode.getObject(j));
        leftBrotherNode.setPointer(j + leftBrotherNode.getNumEntries() + 1, underflowNode.getPointer(j));
      }
      leftBrotherNode.setPointer(underflowNode.getNumEntries() + leftBrotherNode.getNumEntries() + 1, underflowNode.getPointer(underflowNode.getNumEntries()));

      // atualize a quantidade de entradas de leftBrotherNode
      leftBrotherNode.setNumEntries(underflowNode.getNumEntries() + leftBrotherNode.getNumEntries() + 1);

      // remova o nó underflowNode da árvore
      pageManager->deletePage(underflowPage);

      status ret;
      // O nó corrente é a raiz?
      if (pageId == pageManager->getRootPageID()) {
        if (node.getNumEntries() >= 1)
	  ret = Success;
        else
  	ret = Underflow;
      }
      else {
        if (node.getNumEntries() >= (int) (node.getMaxEntries() / 2))
	  ret = Success;
        else
          ret = Underflow;
      }

      // escreva em disco os nós alterados e libere os recursos
      pageManager->writePage(leftBrotherPage);
      pageManager->releasePage(leftBrotherPage);
      pageManager->writePage(page);
      pageManager->releasePage(page);

      return ret;

    }//end unsplit underflowNode e leftBrotherNode

  }//end if (tem irmão à esquerda)

  // carregue irmão à direita de underflowNode
  Page * rightBrotherPage = pageManager->getPage(node.getPointer(i + 1));
  BNode rightBrotherNode(leftPage, false);

  // rightBrotherNode pode emprestar para underflowNode?
  if (rightBrotherNode.getNumEntries() > (int) (rightBrotherNode.getMaxEntries() / 2)) {

    // desça node.getKey(i) para underflowNode
    underflowNode.setKey(underflowNode.getNumEntries(), node.getKey(i));
    underflowNode.setObject(underflowNode.getNumEntries(), node.getObject(i));

    // coloque a subárvore mais à esquerda de rightBrotherNode como a subárvore mais à direita de underflowNode
    underflowNode.setPointer(underflowNode.getNumEntries() + 1, rightBrotherNode.getPointer(0));

    // suba rightBrotherNode.getKey(0) para node
    node.setKey(i, rightBrotherNode.getKey(0));
    node.setObject(i, rightBrotherNode.getObject(0));

    // desloque as entradas restantes em rightBrotherNode para a esquerda
    for (j = 0; j < rightBrotherNode.getNumEntries(); j++) {
      rightBrotherNode.setKey(j, rightBrotherNode.getKey(j + 1));
      rightBrotherNode.setObject(j, rightBrotherNode.getObject(j + 1));
      rightBrotherNode.setPointer(j, rightBrotherNode.getPointer(j + 1));
    }
    rightBrotherNode.setPointer(rightBrotherNode.getNumEntries(), rightBrotherNode.getNumEntries() + 1);

    // atualize as quantidades de entradas de rightBrotherNode e underflowNode
    rightBrotherNode.decNumEntries();
    underflowNode.incNumEntries();

    // escreva em disco os nós alterados e libere os recursos
    pageManager->writePage(rightBrotherPage);
    pageManager->releasePage(rightBrotherPage);
    pageManager->writePage(underflowPage);
    pageManager->releasePage(underflowPage);
    pageManager->writePage(page);
    pageManager->releasePage(page);
    return Success;
  }//end if (rightBrotherNode pode emprestar)

  // underflowNode e rightNode sofrerão unsplit
  // desça node.getKey(i) para underflowNode
  underflowNode.setKey(underflowNode.getNumEntries(), node.getKey(i));
  underflowNode.setObject(underflowNode.getNumEntries(), node.getObject(i));

  // desloque as entradas restantes em node para a esquerda
  for (j = 0; j < node.getNumEntries(); j++) {
    node.setKey(j, node.getKey(j + 1));
    node.setObject(j, node.getObject(j + 1));
    node.setPointer(j, node.getPointer(j + 1));
  }
  node.setPointer(node.getNumEntries(), node.getNumEntries() + 1);

  // atualize a quantidade de entradas de node
  node.decNumEntries();

  // copie as entradas de rightBrotherNode para underflowNode
  for (j = 0; j < rightBrotherNode.getNumEntries(); j++) {
    underflowNode.setKey(j + underflowNode.getNumEntries() + 1, rightBrotherNode.getKey(j));
    underflowNode.setObject(j + underflowNode.getNumEntries() + 1, rightBrotherNode.getObject(j));
    underflowNode.setPointer(j + underflowNode.getNumEntries() + 1, rightBrotherNode.getPointer(j));
  }
  underflowNode.setPointer(rightBrotherNode.getNumEntries() + underflowNode.getNumEntries() + 1, rightBrotherNode.getPointer(rightBrotherNode.getNumEntries()));

  // atualize a quantidade de entradas de underflowNode
  underflowNode.setNumEntries(rightBrotherNode.getNumEntries() + underflowNode.getNumEntries() + 1);

  // remova o nó rightBrotherNode da árvore
  pageManager->deletePage(rightBrotherPage);

  status ret;
  // O nó corrente é a raiz?
  if (pageId == pageManager->getRootPageID()) {
    if (node.getNumEntries() >= 1)
      ret = Success;
    else
      ret = Underflow;
  }
  else {
    if (node.getNumEntries() >= (int) (node.getMaxEntries() / 2))
      ret = Success;
    else
      ret = Underflow;
  }

  // escreva em disco os nós alterados e libere os recursos
  pageManager->writePage(underflowPage);
  pageManager->releasePage(underflowPage);
  pageManager->writePage(page);
  pageManager->releasePage(page);

  return ret;
}//end BTree::rem()
*/
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
