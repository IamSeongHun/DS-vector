#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept> //예외클래스 정의하는 헤더
#include "dsexceptions.h"

using namespace std;

template <typename Object>//제네릭프로그래밍 위한 template
class Vector
{
  public:
      //생성자 선언->Vector( int initSize = 0 ) 매개변수가 0으로 기본적으로 설정되어 있어서 인자를 전달안하고도 객체생성 가능
    explicit Vector( int initSize = 0 )//explicit <> implicit 명시적인 생정자임을 나타낸다. 암시적 형변환 방지.
      : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }//멤버 이니셜라이저,,생성자에서 멤버변수 초기화위함.
      { objects = new Object[ theCapacity ]; }//생성자의 몸체,objects멤버변수를 동적으로 할당된 배열로 초기화.new로 theCapacity만큼크기 가지는 Object타입의 배열을 생성하고 objects멤버변수에 할당한다. 이로써 Vector객체가 생성될때, 배열 메모리도 함께 하당되어 초기화 된다.

      
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
        // 실행 결과를 참고해서 적당한 코드를 추가해주세요. 
        //-----------------------------------------------------------------------------//
        
        Vector<Object> operator+(const Vector& rhs)
        {
            Vector<Object> retVal; 
            //this->push_back(0)
            int sizeOfFirst=this->size();
            int sizeOfSecond = rhs.size();
        
            int count = (sizeOfFirst >= sizeOfSecond) ? sizeOfFirst : sizeOfSecond;//count의 값은 제일큰 벡터 사이즈
            this->reserve(count);
            
            

            for (int i = 0; i < count; i++) {
                retVal.push_back(objects[i] + rhs[i]);
            }

            return retVal;
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
            
            // 새로운 요소를 추가하기 위해 빈 공간을 만듭니다.
            if (theSize == theCapacity)
                reserve(2 * theCapacity + 1);

            // itr을 포함한 뒤쪽 요소들을 한 칸씩 오른쪽으로 옮깁니다.
            iterator dest = end();
            iterator src = dest - 1;
            while (dest != itr) {
                *dest-- = *src--;
            }

            // itr 위치에 x를 삽입합니다.
            *itr = x;
            ++theSize;

            // 삽입된 요소의 위치를 반환합니다.
            return itr;
        }

        iterator erase(iterator itr)
        {
            // itr을 제외한 뒤쪽 요소들을 한 칸씩 왼쪽으로 이동합니다.
            iterator dest = itr;
            iterator src = itr + 1;
            while (src != end()) {
                *dest++ = *src++;
            }

            // 마지막 요소를 제거합니다.
            --theSize;

            // 제거된 요소의 위치를 반환합니다.
            return itr;
        }

        //-----------------------------------------------------------------------------//
        // 실행 결과를 참고해서 적당한 코드를 추가해주세요.
        //-----------------------------------------------------------------------------//
};

#endif