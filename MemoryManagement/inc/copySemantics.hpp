#ifndef COPYSEMANTICS_HPP
#define COPYSEMANTICS_HPP
class DefaultCopy
{
private:
    /* data */
    int *_myInt;

public:
    DefaultCopy(/* args */);
    ~DefaultCopy();
    void printOwnAddress();
    void printMemberAddress();
};

class NoCopy
{
private:
    /* data */
    // NoCopy(const NoCopy &);            // Another Way
    // NoCopy &operator=(const NoCopy &); // Another Way

public:
    NoCopy(/* args */);
    ~NoCopy();
    NoCopy(const NoCopy &) = delete;
    NoCopy &operator=(const NoCopy &) = delete;
};

class ExclusiveCopy
{
private:
    /* data */
    int *_myInt;

public:
    ExclusiveCopy(/* args */);
    ~ExclusiveCopy();
    ExclusiveCopy(ExclusiveCopy &source);
    ExclusiveCopy &operator=(ExclusiveCopy &source);
    ExclusiveCopy(ExclusiveCopy &&source);
    ExclusiveCopy &operator=(ExclusiveCopy &&source);
    void printOwnAddress();
    void printMemberAddress();
};

class DeepCopy
{
private:
    /* data */
    int *_myInt;

public:
    DeepCopy(int val);
    ~DeepCopy();
    DeepCopy(DeepCopy &source);
    DeepCopy &operator=(DeepCopy &source);
    DeepCopy(DeepCopy &&source);
    DeepCopy &operator=(DeepCopy &&source);
};

class SharedCopy
{
private:
    /* data */
    int *_myInt;
    static int _cnt;

public:
    SharedCopy(int val);
    ~SharedCopy();
    SharedCopy(SharedCopy &source);
    SharedCopy &operator=(SharedCopy &source);
    SharedCopy(SharedCopy &&source);
    SharedCopy &operator=(SharedCopy &&source);
};

#endif /* COPYSEMANTICS_HPP */
       /*
       class MyMovableClass
       {
       private:
           int _size;
           int *_data;
       
       public:
           MyMovableClass(size_t size) // constructor
           {
               _size = size;
               _data = new int[_size];
               std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
           }
       
           ~MyMovableClass() // 1 : destructor
           {
               std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
               delete[] _data;
           }
       
           MyMovableClass(const MyMovableClass &source) // 2 : copy constructor
           {
               _size = source._size;
               _data = new int[_size];
               *_data = *source._data;
               std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
           }
       
           MyMovableClass &operator=(const MyMovableClass &source) // 3 : copy assignment operator
           {
               std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
               if (this == &source)
                   return *this;
               delete[] _data;
               _data = new int[source._size];
               *_data = *source._data;
               _size = source._size;
               return *this;
           }
            MyMovableClass(MyMovableClass &&source) // 4 : move constructor
           {
               std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
               _data = source._data;
               _size = source._size;
               source._data = nullptr;
               source._size = 0;
           }
            MyMovableClass &operator=(MyMovableClass &&source) // 5 : move assignment operator
           {
               std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
               if (this == &source)
                   return *this;
       
               delete[] _data;
       
               _data = source._data;
               _size = source._size;
       
               source._data = nullptr;
               source._size = 0;
       
               return *this;
           }
       };
       */