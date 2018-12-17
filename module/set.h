#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
    template <class Type>
    class set
    {
        template <class T>
        friend set<T> operator*(const set<T> &s1, const set<T> &s2);
        template <class T>
        friend set<T> operator+(const set<T> &s1, const set<T> &s2);
        template <class T>
        friend set<T> operator-(const set<Type> &s1, const set<T> &s2);
        // friend set<Type> operator*(const set<Type> &s1, const set<Type> &s2);
        // friend set<Type> operator+(const set<Type> &s1, const set<Type> &s2);
        // friend set<Type> operator-(const set<Type> &s1, const set<Type> &s2);

    private:
        Type *elem;
        int currentSize;
        int maxSize;
        void doubleSpace();
        bool exist(Type x) const;

    public:
        set(int volume = 20);
        set(const set<Type> &s);
        ~set();
    
        set &operator=(const set<Type> &s);
        int getSize(){return currentSize;}
        bool insert(Type x);
        bool erase(Type x);
        void display();
    };

#endif