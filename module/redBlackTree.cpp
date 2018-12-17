#include <iostream>
using namespace std;

template <class Type>
class RedBlackTree{
    struct RedBlackNode
	{  Type           data;
             RedBlackNode   *left;
             RedBlackNode   *right;
             int            colour;  // 0 -- Red, 1 -- Black
    
         RedBlackNode(const Type &element , RedBlackNode *lt,
                   RedBlackNode *rt, int h=0)
                        : data(element), left(lt), right(rt), colour(h) { }
       };

    RedBlackNode *root;	
public:
	  RedBlackTree(RedBlackNode *t = NULL) {root = t;}
        ~RedBlackTree() { makeEmpty(root); }
        bool find(const Type & x) const;
        void insert(const Type & x) ;
        void remove(const Type & x) ;
private:
       void makeEmpty(RedBlackNode * & t);
  	  void LL(RedBlackNode * & t);
	  void LR(RedBlackNode * & t);
	  void RL(RedBlackNode * & t);
	  void RR(RedBlackNode * & t);
	  void reLink(RedBlackNode *oldp, RedBlackNode *newp, 
                    linkStack<RedBlackNode *> &path);
        void insertReBalance(RedBlackNode *t, 
                    linkStack<RedBlackNode *> &path );
        void removeReBalance(RedBlackNode *t, 
                    linkStack<RedBlackNode *> &path );
}; 

template <class Type>
void RedBlackTree<Type>::reLink(RedBlackNode *oldp, 
                                RedBlackNode *newp, 
                                linkStack<RedBlackNode *> &path)
{ if (path.isEmpty()) root = newp;
    else {
	  RedBlackNode *grandParent = path.pop();
	  if (grandParent->left == oldp)
                     grandParent->left = newp;
 	       else grandParent->right = newp;
	  path.push(grandParent);
     }
}

template <class Type>
void RedBlackTree<Type>::insert(const Type & x) 
{ linkStack<RedBlackNode *> path;
  RedBlackNode *t, *parent;
  if(root == NULL) {
     root = new RedBlackNode(x, NULL, NULL, 1);
	 return;
 }
 t = root;
 while (t != NULL && t->data != x) {
	 path.push(t);
	 if (t->data < x) t = t->right; else t = t->left;
 } 

 if (t != NULL) return;
 t = new RedBlackNode(x, NULL, NULL);
 parent = path.pop();
 if (x < parent->data) parent->left = t; else parent->right = t;
 if (parent->colour == 1) return;
 path.push(parent);
 insertReBalance(t, path); 
} 

template <class Type>
void RedBlackTree<Type>::insertReBalance
          (RedBlackNode *t,  
            linkStack<RedBlackNode *> &path ) 
{ RedBlackNode  *parent, *grandParent, *uncle, 
                              *rootOfSubTree;

 parent = path.pop(); 

while (parent->colour == 0) {
     if (parent == root) {parent->colour = 1; return;}
	 grandParent = rootOfSubTree = path.pop();     
	 if (grandParent->data > parent->data) 
	     uncle = grandParent->right; else uncle = grandParent->left;
    
     if (uncle == NULL || uncle->colour == 1) { //情况一的处理｝
  	  else { //情况二
	 	  grandParent->colour = 0;
		  parent->colour = 1;
		  uncle->colour = 1;
		  if (root == grandParent) { root->colour = 1; return;}
	           t = grandParent;
		 parent = path.pop();
	 }
 }
} 

If  (grandParent->left == parent) 
	 if (t == parent->left) {  //LLb
                 parent->colour = 1;    grandParent ->colour = 0;    
                 LL(grandParent);       }
	 else { //LRb
	           grandParent->colour = 0;   t->colour = 1;
                 LR(grandParent);      }
 else if  (t == parent->right) { //RRb
            parent->colour = 1;   grandParent ->colour = 0;
            RR(grandParent);	  }
	 else { //RLb
	     grandParent->colour = 0;  t->colour = 1;   
          RL(grandParent);  }
 reLink(rootOfSubTree, grandParent, path);
 return;
}

template <class Type>
void RedBlackTree<Type>::remove(const Type & x)
{ linkStack<RedBlackNode *> path;
  RedBlackNode *t = root, *old, *parent = NULL;
  while (t!=NULL && t->data != x) {
	 path.push(t);
	 if (t->data > x) t = t->left; else t = t->right;
  }
 if (t==NULL) return ;
  //找替代结点并替代
 if (t->left != NULL && t->right != NULL) { 
	 path.push(t); old = t; t = t->right;
	 while (t->left !=NULL) { path.push(t); t = t->left;}
	 old->data = t->data;
 } 

// 执行删除
 if (t == root) {//删除根结点
	 root = (t->left ? t->left : t->right);
	 if (root != NULL) root->colour = 1;
	 return;
 } 
 parent = path.pop();
 old = t;
 t = (t->left ? t->left : t->right);
 if (parent->left == old) parent->left = t; else parent->right = t;
 if (old->colour == 0) {delete old; return;} //删除红叶结点
 delete old;
 if (t != NULL) { //有一个红儿子
	 t->colour = 1;  return;  }
 path.push(parent);
 removeReBalance(t, path);
} 

template <class Type>
void RedBlackTree<Type>::removeReBalance
              (RedBlackNode *t, 
                linkStack<RedBlackNode *> &path) 
{ RedBlackNode *parent, *sibling, *rootOfSubTree;
 
   parent = rootOfSubTree = path.pop(); 

while (parent != NULL) {
	 if (parent->left == t) sibling = parent->right; 
         else sibling = parent->left;
	 if (sibling->colour == 0) { //情况二
		 sibling->colour = 1;
		 parent->colour = 0;
		 if (parent->left == t) RR(parent); else LL(parent);
                 reLink(rootOfSubTree, parent, path) ;		
		 path.push(parent);
		 parent = rootOfSubTree;    }
	   else { //兄弟是黑结点
	            if ((sibling->left == NULL || sibling->left->colour == 1) && 
                     (sibling->right == NULL || sibling->right->colour == 1)) { //L0 or R0
 		     sibling->colour = 0;
		     if (parent->colour == 0) { parent->colour =1; return; }
		           else {   t = parent; 
  			       if  (t == root) return;
			           else  parent = rootOfSubTree = path.pop();  }
		     }
		 else break;
	     } 
      }  // end of while 

// 情况一的处理
if (parent->left == t) { //兄弟是右孩子
	  if (sibling->left != NULL && sibling->left->colour == 0) {//R1L or R2
                sibling->left->colour = parent->colour;     parent->colour = 1;
	           RL(parent);    reLink(rootOfSubTree, parent, path) ;   }
	   else {//R1R
                 sibling->colour = parent->colour;      sibling->right->colour = 1;
	           parent->colour = 1;     RR(parent);
	           reLink(rootOfSubTree, parent, path) ;    }
               }
   else { //兄弟是左孩子
	 if (sibling->right != NULL && sibling->right->colour == 0) {//L1R or L2
                 sibling->right->colour = parent->colour;  parent->colour = 1;
  	            LR(parent); 	 reLink(rootOfSubTree, parent, path) ;    }
	   else {//L1L
                sibling->colour = parent->colour;
	          sibling->left->colour = 1;    parent->colour = 1;
	          LL(parent);     reLink(rootOfSubTree, parent, path) ;    }
     }  
} 