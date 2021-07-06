#include "MySRAMCache.h"
#define TAMANYO 64

MySRAMCache::~MySRAMCache( )
{
  
}

bool MySRAMCache::hasData(uint64_t addr, uint64_t size)
{
  uint64_t moddedAddr = addr;
  uint64_t tag = moddedAddr & mascaraDir;
  uint64_t desplz = moddedAddr & mascaraDesplz;
  uint64_t porLeer = size;
  std::vector<MySRAMCacheEntry> linea;
  while(porLeer)
  {
    if(!memoria.count(tag))
    return false;

    //Leer datos de la dirección (alineada a TAMANYO Bytes)
    linea = memoria[tag];

    //Comprobar que todos los valores son válidos
    int i = 0;
    for(;i + desplz < TAMANYO && porLeer; ++i)
    {
      if(!(linea[i+desplz].getVal())) return false;
      --porLeer;
    }

    /*
    *   Actualizar la dirección añadiendo los bytes que hemos escrito + 1
    *   para indicar que queremos empezar a leer la primera palabra del 
    *   siguiente bloque alineado con TAMANYO bytes.
    */
    moddedAddr +=  i;

    //Calcular la nueva etiqueta y el nuevo desplazamiento
    tag = moddedAddr & mascaraDir;
    desplz = moddedAddr & mascaraDesplz;

  }

  return true;
}

uint8_t* MySRAMCache::readData(uint64_t addr, uint64_t size)
{
  uint64_t moddedAddr = addr;
  uint64_t tag = moddedAddr & mascaraDir;
  uint64_t desplz = moddedAddr & mascaraDesplz;
  uint64_t porLeer = size;
  uint8_t *rv = new uint8_t[size];
  uint64_t posBaseRV = 0;
  std::vector<MySRAMCacheEntry> linea;

  while(porLeer)
  {
    //Leer datos de la dirección (alineada a TAMANYO Bytes)
    linea = memoria[tag];

    //Copiar los valores al vector de retorno
    int i = 0;
    for(;i + desplz < TAMANYO && porLeer; i++)
    {
      rv[posBaseRV + i] = linea[i + desplz].getDato();
      --porLeer;
    }
    posBaseRV = i;

    //Actualizar LRU
    LRU->push(tag);
    
    /*
    *   Actualizar la dirección añadiendo los bytes que hemos escrito + 1
    *   para indicar que queremos empezar a leer la primera palabra del 
    *   siguiente bloque alineado con TAMANYO bytes.
    */
    moddedAddr +=  i;

    //Calcular la nueva etiqueta y el nuevo desplazamiento
    tag = moddedAddr & mascaraDir;
    desplz = moddedAddr & mascaraDesplz;
 }
  //Devolver el puntero al primer elemento (array) con los datos leidos.
  return rv;
}

bool MySRAMCache::writeData(uint64_t addr, uint8_t* data, uint64_t size)
{
  assert(data != 0x0);
  
  uint64_t moddedAddr = addr;
  uint64_t tag = moddedAddr & mascaraDir;
  uint64_t desplz = moddedAddr & mascaraDesplz;
  uint64_t porEscribir = size;
  uint64_t posBaseData = 0;


  while(porEscribir)
  {
    if(hasData(tag,porEscribir)) //Actulizar una linea ya existente
    {
      //Leer datos de la dirección (alineada a TAMANYO Bytes)
      std::vector<MySRAMCacheEntry>linea = memoria[tag];

      /*
      *   Insertar modificaciones hasta que no quepa más en la linea de cache
      *   (que corresponde a un bloque de TAMANYO Bytes)
      */
      int i = 0;
      for(; i + desplz < TAMANYO && porEscribir; ++i)
      {
        MySRAMCacheEntry datoAGuardar(data[i + posBaseData]);
        linea[i + desplz] = datoAGuardar;  
        --porEscribir;               
      }
      posBaseData = i;

      //Guardar la linea modificada
      memoria[tag] = linea;

      //Actualizar LRU
      LRU->push(tag);

      /*
      *   Actualizar la dirección añadiendo los bytes que hemos escrito + 1
      *   para indicar que queremos empezar a leer la primera palabra del 
      *   siguiente bloque alineado con TAMANYO bytes.
      */
      moddedAddr +=  i;

      //Calcular la nueva etiqueta y el nuevo desplazamiento
      tag = moddedAddr & mascaraDir;
      desplz = moddedAddr & mascaraDesplz;
    }
    else //Añadir una linea nueva
    {

      //Crear una línea nueva de TAMANYO entradas
      std::vector<MySRAMCacheEntry> wv(TAMANYO);

      //Añadir los datos a esta nueva línea
      int i = 0;
      for(; i + desplz < TAMANYO && porEscribir ; ++i)
      {
        wv[i+desplz] = MySRAMCacheEntry(data[i]);
        --porEscribir;
      }

      /*
       * No cabría una linea nueva y por lo tanto
       * habría que sustituir una existente por la nueva
       */
      if(currSize + 1 > maxSize)
      {
        uint64_t toBeReplaced = LRU->peekBottom();
        invalidateData(toBeReplaced);

        assert(currSize < maxSize);
      }

      //Incrementar el tamaño
      ++currSize;

      //Guardar la línea nueva
      memoria[tag] = wv;

      //Actualizar LRU
      LRU->push(tag);

      /*
      *   Actualizar la dirección añadiendo los bytes que hemos escrito + 1
      *   para indicar que queremos empezar a leer la primera palabra del 
      *   siguiente bloque alineado con TAMANYO bytes.
      */
      moddedAddr +=  i;

      //Calcular la nueva etiqueta y el nuevo desplazamiento
      tag = moddedAddr & mascaraDir;
      desplz = moddedAddr & mascaraDesplz;
    }
  }

  return true;
}

bool MySRAMCache::invalidateData(uint64_t addr)
{
  uint64_t tag = addr & mascaraDir;
  
  if(!memoria.count(tag))
    return false;

  /* Eliminar de LRU.*/
  LRU->mvToHead(tag);
  LRU->pop();

  /* Eliminar de memoria*/
  memoria.erase(tag);
  --currSize;
  return true;

}
