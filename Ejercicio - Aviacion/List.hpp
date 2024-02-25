#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct List
{
   Node<T>* p;
   Node<T>* aux;
   int len;
   int curr;
};

template<typename T>
List<T> list()
{
   List<T> lst;
   lst.p = NULL;
   lst.aux = NULL;
   lst.len = 0;
   lst.curr = 0;
   return lst;
}

template<typename T>
T* listAdd(List<T>& lst,T e)
{
   Node<T>* aux = add(lst.p,e);
   T* dir = &(aux->info);
   lst.len++;
   return dir;
}

template<typename T>
T* listAddFirst(List<T>& lst,T e)
{
   Node<T>* aux = addFirst(lst.p,e);
   T* dir = &(aux->info);
   lst.len++;
   return dir;
}

template<typename T,typename K>
T listRemove(List<T>& lst,K k,int cmpTK(T,K))
{
   T elm = remove(lst.p,k,cmpTK);
   lst.len--;
   return elm;
}

template<typename T>
T listRemoveFirst(List<T>& lst)
{
   T elm = removeFirst(lst.p);
   lst.len--;
   return elm;
}

template<typename T,typename K>
T* listFind(List<T> lst,K k,int cmpTK(T,K))
{
   T* elm = NULL;
   Node<T>* aux = find(lst.p,k,cmpTK);
   if ( aux!=NULL )
   {
      elm = &(aux->info);
   }
   return elm;
}

template<typename T>
bool listIsEmpty(List<T> lst)
{
   bool empty = isEmpty(lst.p);
   return empty;
}

template<typename T>
int listSize(List<T> lst)
{
   return lst.len;
}

template<typename T>
void listFree(List<T>& lst)
{
   free(lst.p);
}

template<typename T>
T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
{
   Node<T>* aux = orderedInsert(lst.p,t,cmpTT);
   T* elm = &(aux->info);
   lst.len++;
   return elm;
}

template<typename T>
void listSort(List<T>& lst,int cmpTT(T,T))
{
   sort(lst.p,cmpTT);
}

template<typename T>
void listReset(List<T>& lst)
{
   lst.aux = NULL;
   lst.curr = 0;
}

template<typename T>
bool listHasNext(List<T> lst)
{
   bool next = lst.curr < listSize(lst);
   return next;
}

template<typename T>
T* listNext(List<T>& lst)
{
   T* elm = NULL;

   if ( lst.aux==NULL )
   {
      lst.aux = lst.p;
      elm = &(lst.aux->info);
      lst.curr++;

   } else {

      lst.aux = lst.aux->sig;
      elm = &(lst.aux->info);
      lst.curr++;
   }

   return elm;
}

template<typename T>
T* listNext(List<T>& lst,bool& endOfList)
{
   T* dir = NULL;
   dir = listNext<T>(lst);
   endOfList = lst.aux->sig == NULL;
   return 0;
}

#endif
