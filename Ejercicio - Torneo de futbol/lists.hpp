#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node* sig;
};

template <typename T>
Node<T>* add(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>;
   nuevo->info = e;
   nuevo->sig = NULL;

   if ( p != NULL )
   {
      Node<T>* aux = p;
      while( aux->sig != NULL )
      {
         aux = aux->sig;
      }
      aux->sig = nuevo;
   } else {
      p = nuevo;
   }

   return nuevo;
}

template <typename T>
Node<T>* addFirst(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>;
   nuevo->info = e;
   nuevo->sig = NULL;

   if( p != NULL )
   {
      Node<T>* aux = p;
      p = nuevo;
      nuevo->sig = aux;
   } else {
      p = nuevo;
   }

   return nuevo;
}

template <typename T, typename K>
T remove(Node<T>*& p,K k,int cmpTK(T,K))
{
   Node<T>* aux = p;
   Node<T>* ant = NULL;

   T elm = aux->info;
   while ( cmpTK(elm,k) != 0 )
   {
      ant = aux;
      aux = aux->sig;
      elm = aux->info;
   }

   ant->sig = aux->sig;
   delete aux;

   return elm;
}

template <typename T>
T removeFirst(Node<T>*& p)
{
   Node<T>* aux = p;
   T elm = aux->info;
   p = aux->sig;
   delete aux;
   return elm;
}

template <typename T, typename K>
Node<T>* find(Node<T>* p,K k,int cmpTK(T,K))
{
   Node<T>* aux = p;
   if(p != NULL)
   {
      T elm = aux->info;
      while(cmpTK(elm,k) != 0 and aux != NULL)
      {
         aux = aux->sig;
         if(aux!=NULL)
         {
            elm = aux->info;
         }
      }
   }
   return aux;
}

template <typename T>
Node<T>* orderedInsert(Node<T>*& p,T e,int cmpTT(T,T))
{
   Node<T>* nuevo = new Node<T>;
   nuevo->info = e;
   nuevo->sig = NULL;

   Node<T>* aux1 = p;
   Node<T>* aux2 = NULL;

   while(aux1 != NULL) {
      T elm = aux1->info;
      if(cmpTT(e,elm) < 0) {
         break;
      }
      aux2 = aux1;
      aux1 = aux1->sig;
      }

   if(aux1 == p) {
      p = nuevo;
   } else {
      aux2->sig = nuevo;
   }

   nuevo->sig = aux1;

   return nuevo;
}

template <typename T>
Node<T>* searchAndInsert(Node<T>*& p,T e,bool& enc,int cmpTT(T,T))
{
   Node<T>* aux = p;
   enc = aux->info == e;

   while(!enc and aux != NULL) {
      aux = aux->sig;
      if(aux != NULL) {
         enc = aux->info == e;
      }
   }

   if(!enc) {
      aux = orderedInsert(p,e,cmpTT);
   }

   return aux;
}

template <typename T>
void sort(Node<T>*& p,int cmpTT(T,T))
{
   Node<T>* auxLst = NULL;
   while(p != NULL) {
      T elm = removeFirst(p);
      orderedInsert(auxLst,elm,cmpTT);
   }
   p = auxLst;
}

template <typename T>
bool isEmpty(Node<T>* p)
{
   bool empty = true;
   if(p != NULL) {
      empty = false;
   }
   return empty;
}

template <typename T>
void free(Node<T>*& p)
{
   while(!isEmpty(p)) {
      removeFirst(p);
   }
   p = NULL;
}

template <typename T>
Node<T>* push(Node<T>*& p,T e)
{
   return addFirst(p,e);
}

template <typename T>
T pop(Node<T>*& p)
{
   return removeFirst(p);
}

template <typename T>
Node<T>* enqueue(Node<T>*& p,Node<T>*& q,T e)
{
   Node<T>* aux = NULL;
   if(p == NULL) {
      aux = push<T>(p,e);
      q = aux;
   } else {
      aux = push<T>(p,e);
   }
   return aux;
}

template <typename T>
Node<T>* enqueue(Node<T>*& q,T e)
{
   Node<T>* nuevo = new Node<T>;
   nuevo->info = e;
   nuevo->sig = NULL;

   if(q == NULL) {
      q = nuevo;
      nuevo->sig = q;
   } else {

      Node<T>* aux = q;
      nuevo->sig = aux->sig;
      aux->sig = nuevo;
      q = nuevo;
   }
   return nuevo;
}

template <typename T>
T dequeue(Node<T>*& p, Node<T>*& q)
{
   T elm = pop(p);
   if ( p == NULL )
   {
      q = NULL;
   }
   return elm;
}

template <typename T>
T dequeue(Node<T>*& q)
{
   Node<T>* aux = q;
   Node<T>* f = aux->sig;

   T elmFirst = f->info;
   aux->sig = f->sig;
   delete f;

   return elmFirst;
}

#endif
