template <class Type>
class linkStack
{
private:
    struct node
    {
        Type data;

        node *next;

        node(const Type &x, node *n = NULL)
        {
            data = x;
            next = n;
        }

        node(): next(NULL){}
        ~node(){}
    };
    node *top_p;
public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    void push(const Type &x);
    Type pop();
    Type top() const;
};

template <class Type>
linkStack<Type>::linkStack()
{
    top_p = NULL;
}

template <class Type>
linkStack<Type>::~linkStack()
{
    node *tmp;
    while (top_p != NULL)
    {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}

template <class Type>
bool linkStack<Type>::isEmpty() const
{
    return top_p == NULL;
}

template <class Type>
void linkStack<Type>::push(const Type &x)
{
    top_p = new node(x, top_p);
}

template <class Type>
Type linkStack<Type>::pop()
{
    node *tmp = top_p;
    Type x = tmp->data;
    top_p = top_p->next;
    delete tmp;
    return x;
}

template <class Type>
Type linkStack<Type>::top() const
{
    return top_p->data;
}

///////////////////////////////////////////////////////////////////////////////////////

template <class Type>
class linkQueue
{
private:
    struct node
    {
        Type data;

        node *next;

        node(const Type &x, node *n = NULL)
        {
            data = x;
            next = n;
        }

        node(): next(NULL){}
        ~node(){}
    };

    node *front, *rear;

public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
};

template <class Type>
linkQueue<Type>::linkQueue()
{
    front = rear = NULL;
}

template <class Type>
linkQueue<Type>::~linkQueue()
{
    node *tmp;
    while (front != NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

template <class Type>
bool linkQueue<Type>::isEmpty() const
{
    return front == NULL;
}

template <class Type>
Type linkQueue<Type>::getHead() const
{
    return front->data;
}

template <class Type>
void linkQueue<Type>::enQueue(const Type &x)
{
    if (rear == NULL) front = rear = new node(x);
    else rear = rear->next = new node(x);
}

template <class Type>
Type linkQueue<Type>::deQueue()
{
    node *tmp = front;
    Type value = front->data;
    front = front->next;
    if (front == NULL) rear = NULL; // empty
    delete tmp;
    return value;
}

///////////////////////////////////////////////////////////////////////////////////////

template <class Type> 
class binaryTree 
{
private:
    struct node 
    {  
        Type data;
        node *left, *right;
        
        node(): left(NULL), right(NULL) {}
        node(Type item, node *l = NULL, node *r = NULL): data(item), left(l), right(r) {}
        ~node() {} 
    };

    
    struct stNode
    {
        node *oriNode;
        int timePop;

        stNode(node *N = NULL): oriNode(N), timePop(0) {}
    };

    node *root;

public: 
    binaryTree():root(NULL) {}
    binaryTree(const Type &value) {root = new node(value);} 
    binaryTree(node *p) {root = p;}
    ~binaryTree() {clear();}

    Type getRoot() const {return root->data;}
    Type getLeft() const {return root->left->data;}
    Type getRight() const {return root->right->data;}
    void makeTree(const Type &x, binaryTree &lt, binaryTree &rt);
    void delLeft();
    void delRight();
    bool isEmpty() const {return root == NULL;}
    void clear();
    int size() const {return size(root);} 
    int height() const {return height(root);}
    void preTraveral() const;
    void postTraveral() const;
    void midTraveral() const;
   	void createTree(Type flag);

private:
    void clear(node *t);
    int height(node *t) const;
    int size(node *t) const;
    void preTraveral(node *t) const;
    void postTraveral(node *t) const;
    void midTraveral(node *t) const;
 }; 

template <class Type> 
void binaryTree<Type>::makeTree(const Type &x, binaryTree &lt, binaryTree &rt)
{
    root = new node(x, lt.root, rt.root);
    lt.root = NULL; 
    rt.root = NULL;	  
}

template <class Type> 
void binaryTree<Type>::delLeft()
{
    binaryTree tmp = root->left;
    root->left = NULL; 
    tmp.clear();
}

template <class Type> 
void binaryTree<Type>::delRight()
{
    binaryTree tmp = root->right;
    root->right = NULL;  
    tmp.clear();	  
}

template <class Type> 
void binaryTree<Type>::clear()
{
    if (root != NULL) clear(root); 
    root = NULL;
}

template <class Type>
void binaryTree<Type>::clear(node *t) 
{ 
    if (t->left != NULL) clear(t->left); 
    if (t->right != NULL) clear(t->right);
    delete t;
}

template <class Type> 
int binaryTree<Type>::size(node *t) const
{ 
    if (t == NULL) return 0;
    return 1 + size(t->left) + size(t->right);
}

template <class Type> 
int binaryTree<Type>::height(node *t) const
{ 
    if (t == NULL) return 0; 

    else 
    {
        int lt = height(t->left), rt = height(t->right);
	    return 1 + ( (lt > rt) ? lt : rt);
	}
}

template <class Type>
void binaryTree<Type>::createTree(Type flag)
{ 
    linkQueue<node *> que;
    node *tmp;
    Type x, ldata, rdata;

    cout << "Input root: ";
    cin >> x;
    root = new node(x);
    que.enQueue(root);	
    while (!que.isEmpty()) 
    {
        tmp = que.deQueue();
        cout << "\nInput" << tmp->data << "'s two sons(" << flag 
                << "as empyt node)：";
        cin >> ldata >> rdata;
        if (ldata != flag) que.enQueue(tmp->left = new node(ldata));
        if (rdata != flag) que.enQueue(tmp->right = new node(rdata));
    }
    cout << "create completed!\n";
}

template <class Type>
void binaryTree<Type>::preTraveral() const
{
    linkStack<node *> s;
    node *tmp;
    s.push(root);

    while (!s.isEmpty())
    {
        tmp = s.pop();

        cout << tmp->data << ' ';
        if (tmp->right != NULL) s.push(tmp->right);
        if (tmp->left != NULL) s.push(tmp->left);
    }
}

template <class Type>
void binaryTree<Type>::midTraveral() const
{
    linkStack<stNode> s;
    stNode tmp(root);
    s.push(tmp);

    while (!s.isEmpty())
    {
        tmp = s.pop();

        if (++tmp.timePop == 2)
        {
            cout << tmp.oriNode->data << ' ';
            if (tmp.oriNode->right != NULL) s.push(stNode(tmp.oriNode->right));
        }

        else
        {
            s.push(tmp);
            
            if (tmp.oriNode->left != NULL) s.push(stNode(tmp.oriNode->left));
        }
    }
}

template <class Type>
void binaryTree<Type>::postTraveral() const
{
    linkStack<stNode> s;  
    stNode tmp(root);
    s.push(tmp);

    while (!s.isEmpty())
    {
        tmp = s.pop();

        if (++tmp.timePop == 3)
        {
            cout << tmp.oriNode->data << ' ';
            continue;
        }

        s.push(tmp);

        if (tmp.timePop == 1)
        {
            if (tmp.oriNode->left != NULL) s.push(stNode(tmp.oriNode->left));
        }

        else
        {
            if (tmp.oriNode->right != NULL) s.push(stNode(tmp.oriNode->right));
        }
    }
}