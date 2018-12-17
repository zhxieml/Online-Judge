#include <iostream>
#include "AvlTree.h"
using namespace std;

template <class Type>
bool AvlTree<Type>::find(const Type &x) const
{
    AvlNode *t = root;
    while (t!=NULL &&t->data != x) 
    {
        if (t->data > x) t = t->left; 
        else t = t->right;
    }

    if (t==NULL) return false;
    else return true;
} 

template <class Type>
void AvlTree<Type>::makeEmpty(AvlNode *&x)
{
    if (x != NULL)
    {
        makeEmpty(x->left);
        makeEmpty(x->right);
        delete x;
    }

    x = NULL;
}

template <class Type>
void AvlTree<Type>::insert(const Type &x, AvlNode *&t)
{ 
    if(t == NULL) t = new AvlNode(x, NULL, NULL);
    else if(x < t->data) 
    {
        insert(x, t->left);
        
        if(height(t->left) - height(t->right) == 2)
        {
                if(x < t->left->data) LL(t); 
                else LR(t);
        }
    }        
    else if(t->data < x)  
    {
        insert(x, t->right);
        
        if(height(t->right) - height(t->left) == 2)
        {
                if(t->right->data < x) RR(t); 
                else RL(t);
        }
    }
    
    t->height = max(height(t->left) , height(t->right)) + 1;    // 重新计算高度
} 

template <class Type>
void AvlTree<Type>::LL(AvlNode *&t)
{
    AvlNode *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t)) + 1;
    t = t1;
} 

template <class Type>
void AvlTree<Type>::RR(AvlNode *&t)
{
    AvlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->right), height(t)) + 1;
    t = t1;
 } 

template <class Type>
void AvlTree<Type>::LR(AvlNode *&t)
{
    RR(t->left);
    LL(t);
}

template <class Type>
void AvlTree<Type>::RL(AvlNode *&t)
{
    LL(t->right);
    RR(t);
} 

template <class Type>
bool AvlTree<Type>::remove(const Type &x, AvlNode *&t) 
{ 
    bool stop =false;
    int subTree;  // 1表示删除发生在左子树上， 
                        // 2表示删除发生在右子树上
    if(t == NULL)     return true;     

    if(x < t->data)   
    {
        stop = remove(x, t->left); 
        subTree = 1;
    }
    else if(t->data < x)   
    { 
        stop = remove(x, t->right); 
        subTree = 2;
    }
    else if(t->left != NULL &&t->right != NULL) 
    {
        AvlNode *tmp = t->right;
        while(tmp->left != NULL) tmp = tmp->left; 
        t->data = tmp->data;
        stop = remove(t->data, t->right);
        subTree = 2;
    }
    else   
    { 
        AvlNode *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
        return false;
    }
 
    if (stop) return true;
    int bf;
    switch(subTree) 
    {
 	    case 1: 
            bf = height(t->left) - height(t->right) + 1;
	        if (bf == 0) return true; //情况一
		    if (bf == 1)  return false; //情况二
		    if (bf ==-1) //情况三
            { 
		        int bfr = height(t->right->left) - height(t->right->right);
		        switch (bfr) 
                {
                    case 0: 
                        RR(t); 
                        return true;
                    case -1: 
                        RR(t); 
                        return false;
                    default: 
                        RL(t); 
                        return false;
		        }
		    }

		    break;

	    case 2: 
            bf = height(t->left) - height(t->right) -1;
                if (bf == 0) return true; //情况一
		        if (bf == -1) return false; //情况二
		        if (bf == 1) //情况三
                { 
		            int bfl = height(t->right->left) - height(t->right->right);
   		            switch (bfl) 
                    {
			            case 0: 
                            LL(t); 
                            return true;
			            case 1: 
                            LL(t); 
                            return false;
			            default: 
                            LR(t); 
                            return false;
                    }  
                }   
    } 
} 
