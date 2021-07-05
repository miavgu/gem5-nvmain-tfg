/*
* Esta clase es la representación del elemento "SRAM Cache Tags"
* del HMC
*/
#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <list> 
#include <iterator>
#include <forward_list> //Al fin y al cabo, un stack es una lista en una direccion

class MyUIntStack
{
  public:
   /*
    * Crea un stack para UINT64_T
    */
    MyUIntStack( )
    {

    }
    ~MyUIntStack( )
    {
        
    }

    /*
    * Añade un elemento al stack
    *
    * @param el Valor para el nuevo elemento a insertar
    */
    inline void push(uint64_t el){

        if(exists(el))
        {
            stack_base.remove(el);
            stack_base.push_front(el);
            return;
        }

        ++mySize;
        stack_base.push_front(el);
    }

    /*
    * Elimina el elemento insertado más recientemente
    */
    inline void pop(){

        if(!mySize) return;

        --mySize;
        stack_base.pop_front();
    }

    /*
    * Elimina (y devuelve) el valor del elemento que hace más tiempo no se ha usado.
    *
    * @return El valor del elemento que hace más tiempo no se ha usado.
    */
    inline uint64_t popBottom()
    {
        uint64_t aEliminar;
        aEliminar = peekBottom();
        stack_base.remove(aEliminar);
        --mySize;
        return aEliminar;
    }
    
    /*
    * Consulta el valor del elemento insertado más recientemente
    *
    * @return El valor del elemento insertado más recientemente
    */
    inline uint64_t peek(){return stack_base.front();}

    /*
    * Consulta el valor del elemento que hace más tiempo no se ha usado.
    *
    * @return El valor del elemento que hace más tiempo no se ha usado.
    */
    inline uint64_t peekBottom()
    {
        uint64_t cont = 0;
        for(auto it = stack_base.begin(); it != stack_base.end(); ++it)
        {
            ++cont;
            if(cont == mySize){
                return *it;
            }
        }
        return 0;
    }

    /*
    * Mover elemento a la cabeza del stack. 
    * Si no existe el elemento, no se realizan cambios
    *
    * @param el El valor del elemento a mover a la cabeza
    */
    inline void mvToHead(uint64_t el)
    {
        for(auto it = stack_base.begin(); it != stack_base.end(); ++it)
        {
            if(*it == el)
            {
                stack_base.remove(el);
                stack_base.push_front(el);
            }
        }
    }

    /*
    * Busca si existe un elemento en el stack.
    *
    * @param el El valor del elemento a buscar
    * @return TRUE (>0) si existe. FALSE (0) si no
    */
    inline bool exists(uint64_t el)
    {
        for(auto it = stack_base.begin(); it != stack_base.end(); ++it)
        {
            if(*it == el)
            {
                return 1;
            }
        }
        return 0;
    }

    /*
    * Comprobar si el stack está vacío
    *
    * @return TRUE (> 0) si vacío. FALSE (0) si tiene al menos un elemento
    */
    inline bool empty(){return !mySize;}

    /*
    * Obtener el tamaño actual del stack
    *
    * @return El tamaño del stack
    */
    inline uint64_t size(){return mySize;}

    /*
    * Mostrar el estado del stack por salida estándar. El primer elemento añadido va a la derecha.
    */
    void print(){
        for ( auto it = stack_base.begin(); it != stack_base.end(); ++it )
            std::cout << ' ' << *it;

        std::cout << std::endl;
    }
    
  private:
    uint64_t mySize = 0;
    std::forward_list<uint64_t> stack_base;
  protected:
};