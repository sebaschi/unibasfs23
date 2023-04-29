template <class T> class Darray {
    private:
        T* arr; // Pointer to array
        int len; // Size of array
        int cap; // Capacity of allocated memory space

        void resize(); // 
    public:
        // Constructor
        Darray();       // Default constructor
        Darray(int c); // With initial capacity 
        Darray(const Darray<T>& ref);  // Copy ctor    
        
        // Assignment operator
        Darray& operator=(const Darray<T>& ref);
        // Destructor
        ~Darray();

        // User Methods
        void add(T item);
        T get(int index);
        void removeLast();
        //Set item at index index with item
        void set(int index, T item);

        // Utilities
        void printArr() const;
};
