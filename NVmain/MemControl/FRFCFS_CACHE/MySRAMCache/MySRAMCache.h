/*
* Esta clase es la representación del elemento "SRAM Cache Tags"
* del HMC
*/
#include "MyUIntStack.h"
#include <math.h>
#include <assert.h>

#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <list> 
#include <iterator>
#include <unordered_map>
#include <bitset>

#define OUT

/*
*   Clase auxiliar que representa un byte de una línea de caché
*/
class MySRAMCacheEntry
{
  public:
    MySRAMCacheEntry( )
    {
      dato = 0;
      val[0] = 0; 

    };

    MySRAMCacheEntry( uint8_t data )
    {
      dato = data;
      val[0] = 1;
    };

    ~MySRAMCacheEntry( )
    {
      
    };

    uint8_t getDato() const { return dato; }
    void setDato(const uint8_t &dato_) { dato = dato_; }

    void setVal() {val[0] = 1;}
    void resetVal() {val[0] = 0;}
    bool getVal() {return val[0];}

  private:
    uint8_t dato;
    std::bitset<1> val;

};

/*
*   Clase que implementa la funcionalidad de la caché
*/
class MySRAMCache
{

  typedef std::unordered_map<uint64_t, std::vector<MySRAMCacheEntry>> memoria_cache;
  public:
   /*
    * Crea una caché con máximo 2^n líneas (de 64 bits cada una)
    * y lat ciclos de latencia
    *
    * @param n exponente del tamaño máximo de memoria.
    * @param lat ciclos de latencia de la caché  
    */
  public:
    MySRAMCache( uint64_t n, uint64_t lat ) : currSize(0)
    {
      //LRU = new MyUIntStack();
      maxSize = pow(2, n);
      latenciaCiclos = lat;
      srand(2021);
      dirArray.resize(maxSize);
    };
    ~MySRAMCache( );

   /*
    * Comprueba si una dirección de memoria tiene datos válidos.
    *
    * @param addr Dirección a comprobar si tiene dato
    * @return TRUE si tiene un dato. FALSE si no.
    */
    bool hasData(uint64_t addr, uint64_t size);

   /*
    * Devuelve la palabra que se encuentra en una dirección de memoria
    *
    * 
    * @param addr Dirección de memoria a leer
    * @param size Numero de bytes a leer desde la dirección de memoria
    * @return Un array de uint8_t o nullptr si no existe una entrada en memoria.
    */
    uint8_t* readData(uint64_t addr, uint64_t size);

   /*
    * Guarda una cantidad de bytes desde una dirección de memoria
    * 
    * @param addr Dirección de memoria donde guardar el dato
    * @param data Dato a guardar (como uint64_t)
    * @param size Numero de bytes a guardar
    * @return TRUE si no ha habido problemas. FALSE si no.
    */
    bool writeData(uint64_t addr, uint8_t* data, uint64_t size);

   /*
    * Invalida la palabra de una dirección de memoria
    *
    * @param addr Dirección cuya palabra se quiere invalidar.
    * @return TRUE si no ha habido problemas. FALSE si no.
    */
    bool invalidateData(uint64_t addr, uint64_t size);

   /*
    * Getters y Setters
    */
    inline void setMaxSize(uint64_t maxSize_) {maxSize = maxSize_;}
    inline void setCurrSize(uint64_t currSize_) {currSize = currSize_;}

    inline uint64_t getMaxSize() {return maxSize;}
    inline uint64_t getCurrSize(){return currSize;}
    
    inline uint64_t getLatenciaCiclos(){return latenciaCiclos;}
  private:
    memoria_cache memoria;                        //Variable que almacena los datos
    //MyUIntStack *LRU;                             //Variable que representa LRU
    const uint64_t mascaraDir =    18446744073709551552ULL;  //Variable para la etiqueta
    const uint64_t mascaraDesplz = 0x000000000000003F;  //Variable para el desplazamiento
    uint64_t maxSize, currSize;                   //Variables para gestionar el tamaño
    uint64_t latenciaCiclos;                      //Variable que contiene la latencia
    std::vector<uint64_t> dirArray;
	  uint64_t conteoLlamadas = 0;				  //Variables para ayudar con el debug		
  protected:
};
