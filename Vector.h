#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept> //����Ŭ���� �����ϴ� ���
#include "dsexceptions.h"

using namespace std;

template <typename Object>//���׸����α׷��� ���� template
class Vector
{
  public:
      //������ ����->Vector( int initSize = 0 ) �Ű������� 0���� �⺻������ �����Ǿ� �־ ���ڸ� ���޾��ϰ� ��ü���� ����
    explicit Vector( int initSize = 0 )//explicit <> implicit ������� ���������� ��Ÿ����. �Ͻ��� ����ȯ ����.
      : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }//��� �̴ϼȶ�����,,�����ڿ��� ������� �ʱ�ȭ����.
      { objects = new Object[ theCapacity ]; }//�������� ��ü,objects��������� �������� �Ҵ�� �迭�� �ʱ�ȭ.new�� theCapacity��ŭũ�� ������ ObjectŸ���� �迭�� �����ϰ� objects��������� �Ҵ��Ѵ�. �̷ν� Vector��ü�� �����ɶ�, �迭 �޸𸮵� �Բ� �ϴ�Ǿ� �ʱ�ȭ �ȴ�.

      
    Vector(initializer_list<Object> init)
        : theSize{ int(init.size()) }, theCapacity{ theSize + SPARE_CAPACITY }
    {
        objects = new Object[theCapacity]; 
        
        int k = 0;
        for (auto itr = init.begin(); itr != init.end(); itr++)
        {
            objects[k++] = *itr;
        }

    }

    Vector( const Vector & rhs )
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    { 
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }
    
    Vector & operator= ( const Vector & rhs )
    {
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    ~Vector( )
      { delete [ ] objects; }

    Vector( Vector && rhs )
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
   
    Vector & operator= ( Vector && rhs )
    {    
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );
        
        return *this;
    }
    
    bool empty( ) const
      { return size( ) == 0; }
    int size( ) const
      { return theSize; }
    int capacity( ) const
      { return theCapacity; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ];
    }

    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }

    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;

        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );

        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }

      // Stacky stuff
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
      // Stacky stuff
    void push_back( Object && x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }

    void pop_back( )
    {
        if( empty( ) )
            throw UnderflowException{ };
        --theSize;
    }

    const Object & back ( ) const
    {
        if( empty( ) )
            throw UnderflowException{ };
        return objects[ theSize - 1 ];
    }

      // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin( )
      { return &objects[ 0 ]; }
    const_iterator begin( ) const
      { return &objects[ 0 ]; }
    iterator end( )
      { return &objects[ size( ) ]; }
    const_iterator end( ) const
      { return &objects[ size( ) ]; }

    static const int SPARE_CAPACITY = 2;

    private:
        int theSize;
        int theCapacity;
        Object * objects;



    public:
        void print(ostream& out = cout) const
        {
            out << "Vector[ " << size() << " ] = { ";

            for (Vector<Object>::const_iterator itr = begin(); itr != end(); itr++)
            {
                out << *itr;
                if (itr + 1 != end()) 
                    out << " , ";
            }          
            out << " }" << endl;
        }
        
        iterator insert(iterator itr, Object&& x)
        {
            return insert(itr, x);
        }

        //-----------------------------------------------------------------------------//
        // ���� ����� �����ؼ� ������ �ڵ带 �߰����ּ���. 
        //-----------------------------------------------------------------------------//
        
        Vector<Object> operator+(const Vector& rhs) 
        {
            Vector<Object> retVal;
        

            int sizeOfFirst = this->size();
            int sizeOfSecond = rhs.size();

            if(sizeOfFirst== sizeOfSecond){
                for (int i = 0; i < sizeOfFirst; i++) {
                    retVal.push_back(objects[i] + rhs[i]);
                }
                return retVal;
            }

            else {
                int count = (sizeOfFirst <= sizeOfSecond) ? sizeOfFirst : sizeOfSecond;//count�� ���� �� ���� ���� ������



                for (int i = 0; i < count; i++) {
                    retVal.push_back(objects[i] + rhs[i]);
                }

                //���������� ���� ��ҵ� pushback�Ѵ�.
                if (sizeOfFirst > sizeOfSecond) {
                    for (int i = sizeOfSecond; i < sizeOfFirst; ++i) {
                        retVal.push_back(objects[i]);
                    }

                }
                else {
                    for (int i = sizeOfFirst; i < sizeOfSecond; ++i) {
                        retVal.push_back(rhs[i]);
                    }
                }

                return retVal;
            }
        }

        Vector<Object> operator+(const Object& rhs)
        {
            if (theSize == theCapacity)
                reserve(2 * theCapacity + 1);

            Vector<Object> retVal;

            int sizeOfFirst = this->size();
            for (int i = 0; i < sizeOfFirst; i++) {
                retVal.push_back(objects[i] + rhs);
            }
           
            return retVal;
        }

        Vector<Object> operator+(Object&& rhs)
        {
            Vector<Object> retVal;
            int sizeOfFirst = this->size();
            for (int i = 0; i < sizeOfFirst; i++) {
                retVal.push_back(objects[i] + rhs);
            }

            return retVal;
        }



        iterator insert(iterator itr, const Object& x)
        {      
            
            // ���ο� ��Ҹ� �߰��ϱ� ���� �� ������ ����ϴ�.
            if (theSize == theCapacity)
                reserve(2 * theCapacity + 1);

            // itr�� ������ ���� ��ҵ��� �� ĭ�� ���������� �ű�ϴ�.
            iterator dest = end();
            iterator src = dest - 1;
            while (dest != itr) {
                *dest-- = *src--;
            }

            // itr ��ġ�� x�� �����մϴ�.
            *itr = x;
            ++theSize;

            // ���Ե� ����� ��ġ�� ��ȯ�մϴ�.
            return itr;
        }

        iterator erase(iterator itr)
        {
            // itr�� ������ ���� ��ҵ��� �� ĭ�� �������� �̵��մϴ�.
            iterator next = itr;
            iterator prev = itr + 1;
            while (prev != end()) {
                *next = *prev;
                ++next;
                ++prev;
            }

            // ������ ��Ҹ� �����մϴ�.
            --theSize;

            // ���ŵ� ����� ��ġ�� ��ȯ�մϴ�.
            return itr;
        }

        //-----------------------------------------------------------------------------//
        // ���� ����� �����ؼ� ������ �ڵ带 �߰����ּ���.
        //-----------------------------------------------------------------------------//
};

#endif