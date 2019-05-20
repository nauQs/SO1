#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

p_meta_data first_element = NULL;
p_meta_data last_element  = NULL;

#define ALIGN8(x) (((((x)-1)>>3)<<3)+8)
#define MAGIC     0x12345678

p_meta_data search_available_space(size_t size_bytes) {
    p_meta_data current = first_element;

    while (current && !(current->available && current->size_bytes >= size_bytes)) {
        current = current->next;
    }
    return current;
}

p_meta_data request_space(size_t size_bytes) 
{
    p_meta_data meta_data;

    meta_data = (void *) sbrk(0);

    if (sbrk(SIZE_META_DATA + size_bytes) == (void *) -1)
        return (NULL);

    meta_data->size_bytes = size_bytes;
    meta_data->available = 0;
    meta_data->magic = MAGIC;
    meta_data->next = NULL;
    meta_data->previous = NULL;

    return meta_data;
}

void free(void *ptr)
{
    //fprintf(stderr, "Free\n");
    p_meta_data meta_data;
    if(ptr!= NULL){
        meta_data = ptr - SIZE_META_DATA;
        if(meta_data->magic != MAGIC){
            fprintf(stderr, "Error: el magic no coincideix\n");
        }else{
            meta_data->available = 1;
            //fprintf(stderr, "S'ha alliberat l'espai de memòria: %d bytes\n", meta_data->size_bytes);
        }
    }
}


void *malloc(size_t size_bytes) 
{
    void *p;
    p_meta_data meta_data;

    if (size_bytes <= 0) {
        return NULL;
    }

    // We allocate a size of bytes multiple of 8
    size_bytes = ALIGN8(size_bytes);
    //fprintf(stderr, "Malloc %zu bytes\n", size_bytes);

    meta_data = search_available_space(size_bytes);

    if (meta_data) { // free block found 
      meta_data->available = 0;
    } else {     // no free block found 
      meta_data = request_space(size_bytes);
      if (!meta_data)
        return (NULL);

      if (last_element)
          last_element->next = meta_data;
      meta_data->previous = last_element;
      last_element = meta_data;

      if (first_element == NULL) // Is this the first element ?
      	first_element = meta_data;
    }

    p = (void *) meta_data;

    // We return the user a pointer to the space
    // that can be used to store data

    return (p + SIZE_META_DATA); 
}

void *calloc(size_t nelem, size_t elsize)
{
    void *p;
    p = malloc(nelem*elsize);
    p_meta_data meta_data;
    meta_data = p - SIZE_META_DATA;
    memset(p, 0, nelem*elsize);
    
    return p;
}

void *realloc(void *ptr, size_t size_bytes)
{
    if(ptr!=NULL){
        p_meta_data meta_data;
        meta_data = ptr - SIZE_META_DATA;
        if(meta_data->magic == MAGIC && meta_data->size_bytes >= size_bytes){
            return ptr;
            //fprintf(stderr, "realloc: enough space already\n");
        }else{
            void *p;
            p = malloc(size_bytes);
            memcpy(p,ptr,meta_data->size_bytes);
            //fprintf(stderr, "realloc: memory reallocated\n");
            return p;
            
        }
    }
    return malloc(size_bytes);
}



