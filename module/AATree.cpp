#include <iostream>
using namespace std;


template <class Type>
class AATree
{ private:
    struct AANode
     { Type   data;
        AANode *left;
        AANode *right;
        int    level;
        AANode(const Type & thedata, AANode *lt, AANode *rt,
                         int lv = 1)
         : data(thedata), left(lt), right(rt) , level(lv) { }
    }; 

     AANode *root; 
public:
    AATree(AANode *t = NULL) {root = t;}
    ~AATree() { makeEmpty(root); }
    bool find(const Type & x) const { return find(x, root); }
    void insert(const Type & x) { insert(x, root);   }
    void remove(const Type & x) { remove(x, root);  }
 private:
    void insert(const Type & x, AANode * & t) ;
    void remove(const Type & x, AANode * & t) ;
    bool find(const Type & x, AANode *t) const;
    void makeEmpty(AANode * & t);
	void LL(AANode *&t);
	void RR(AANode *&t);
    int min (int a, int b) {return a>b?b:a;}
}; 

template <class Type>
void AATree<Type>::LL(AANode *&t)
{  if (t->left != NULL && t->left->level == t->level)  {
       AANode *t1 = t->left;       t->left = t1->right;
       t1->right = t;       t = t1;      }
}

template <class Type>
void AATree<Type>::RR(AANode *&t)
{  if (t->right != NULL && t->right->right != NULL
       && t->right->right->level == t->level) {
         AANode *t1 = t->right;       t->right = t1->left;
         t1->left = t;       t = t1;   t->level++;      }
} 

template <class Type>
void AATree<Type>::insert(const Type & x, AANode *&t)
{ if(t == NULL)
      t = new AANode(x, NULL, NULL);
    else if(x < t->data)
            insert(x, t->left);
           else if(t->data < x)
                         insert(x, t->right);
		         else return;
  LL(t);
  RR(t);
 }

void AATree<Type>::remove(const Type & x, AANode * & t) 
{ if (t == NULL)     return;   
   if (x < t->data)   remove(x, t->left);
   else if (t->data < x)    remove(x, t->right);
          else if (t->left != NULL && t->right != NULL) {
		          AANode *tmp = t->right;
		          while(tmp->left != NULL) tmp = tmp->left; 
                      t->data = tmp->data;   
                      remove(t->data, t->right);   
                     }
                   else {  AANode *oldNode = t;
                             t = (t->left != NULL) ? t->left : t->right;
                             delete oldNode;  return;
                          }

 if (t->left ==NULL || t->right == NULL) t->level = 1 ;
     else t->level = min(t->left->level, t->right->level) + 1;
 if (t->right != NULL && t->right->level > t->level)
       t->right->level = t->level;
 LL(t);
 if (t->right != NULL) LL(t->right);
 if (t->right != NULL && t->right->right != NULL)
          LL(t->right->right);
 RR(t);
 if (t->right != NULL) RR(t->right);
 } 
