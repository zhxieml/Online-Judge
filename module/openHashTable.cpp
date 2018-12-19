template <class Type>
class openHashTable:public hashTable<Type>
{ private:
      struct node {
                Type data;
		  struct node *next;
		  node (const Type &d) { data = d; next = NULL;}
		  node () {next = NULL;}
	  };
      node **array;
      int  size;
  public: 
      openHashTable(int length = 101, int (*f)(const Type &x) = defaultKey);
      ~openHashTable() ;
      bool find(const Type &x) const;
      bool insert(const Type &x);
      bool remove(const Type &x) ;
}; 

template <class Type>
openHashTable<Type>::openHashTable(int length, int (*f)(const Type  &x) )
{
	size = length;
	array = new node*[size];
	key = f;
	for (int i = 0; i< size; ++i) array[i] = new node;
} 

template <class Type>
openHashTable<Type>::~openHashTable()
{ node *p, *q;
   for (int i = 0; i< size; ++i){
	p = array[i]; 
	do { q= p->next;  delete p;  
               p = q; }   while (p!=NULL);
       }
  delete [] array;
}	 

template <class Type>
bool openHashTable<Type>::insert(const Type &x)
{ int pos ;
  node *p;
  pos = key(x) % size;
  p = array[pos]->next;
  while (p != NULL && !(p->data == x)) p = p->next;
  if (p == NULL) {
       p = new node(x); 
       p->next = array[pos]->next; 
       array[pos]->next = p;
       return true;  }
   return false;
} 

template <class Type>
bool openHashTable<Type>::remove(const Type &x) 
{int  pos ;
 node *p, *q;
 pos = key(x) % size;
 p = array[pos];
 while (p->next != NULL && !(p->next->data == x) ) 
        p = p->next;
 if (p->next == NULL) return false;
   else { q = p->next;
             p->next = q->next;
	     delete q;
		 return true;   }
} 

template <class Type>
bool openHashTable<Type>::find(const Type &x) const
{int pos ;
 node *p;
 pos = key(x) % size;
 p = array[pos];
 while (p->next != NULL && !(p->next->data == x) ) 
          p = p->next;
 if (p->next != NULL) return true;
   else return false;
} 
