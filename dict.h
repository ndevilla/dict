
/*-------------------------------------------------------------------------*/
/**
   @file    dict.h
   @author  N. Devillard
   @date    Apr 2011
   @brief   Dictionary object

   This file implements a basic string/string associative array that
   grows when needed to store all inserted key/value pairs. The implementation
   is very closely based on the Python dictionary, without the associated
   Pythonisms and with specification on string/string.
*/
/*--------------------------------------------------------------------------*/
#ifndef _DICT_H_
#define _DICT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>

/*---------------------------------------------------------------------------
                            Additional types
 ---------------------------------------------------------------------------*/

/** Keypair: holds a key/value pair. Key must be a hashable C string */
typedef struct _keypair_ {
    char    * key ;
    char    * val ;
    unsigned  hash ;
} keypair ;

/** Dict is the only type needed for clients of the dict object */
typedef struct _dict_ {
    unsigned  fill ;
    unsigned  used ;
    unsigned  size ;
    keypair * table ;
} dict ;

/*-------------------------------------------------------------------------*/
/**
  @brief    Allocate a new dictionary object
  @return   Newly allocated dict, to be freed with dict_free()

  Constructor for the dict object.
 */
/*--------------------------------------------------------------------------*/
dict * dict_new(void);


/*-------------------------------------------------------------------------*/
/**
  @brief    Deallocate a dictionary object
  @param    d   dict to deallocate
  @return   void

  This function will deallocate a dictionary and all data it holds.
 */
/*--------------------------------------------------------------------------*/
void   dict_free(dict * d);

/*-------------------------------------------------------------------------*/
/**
  @brief    Add an item to a dictionary
  @param    d       dict to add to
  @param    key     Key for the element to be inserted
  @param    val     Value to associate to the key
  @return   0 if Ok, something else in case of error

  Insert an element into a dictionary. If an element already exists with
  the same key, it is overwritten and the previous associated data are freed.
 */
/*--------------------------------------------------------------------------*/
int    dict_add(dict * d, char * key, char * val);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get an item from a dictionary
  @param    d       dict to get item from
  @param    key     Key to look for
  @param    defval  Value to return if key is not found in dict
  @return   Element found, or defval

  Get the value associated to a given key in a dict. If the key is not found,
  defval is returned.
 */
/*--------------------------------------------------------------------------*/
char * dict_get(dict * d, char * key, char * defval);

/*-------------------------------------------------------------------------*/
/**
  @brief    Delete an item in a dictionary
  @param    d       dict where item is to be deleted
  @param    key     Key to look for
  @return   0 if Ok, something else in case of error

  Delete an item in a dictionary. Will return 0 if item was correctly
  deleted and -1 if the item could not be found or an error occurred.
 */
/*--------------------------------------------------------------------------*/
int dict_del(dict * d, char * key);

/*-------------------------------------------------------------------------*/
/**
  @brief    Enumerate a dictionary
  @param    d       dict to browse
  @param    rank    Rank to start the next (linear) search
  @param    key     Enumerated key (modified)
  @param    val     Enumerated value (modified)
  @return   int rank of the next item to enumerate, or -1 if end reached

  Enumerate a dictionary by returning all the key/value pairs it contains.
  Start the iteration by providing rank=0 and two pointers that will be
  modified to references inside the dict.
  The returned value is the immediate successor to the one being returned,
  or -1 if the end of dict was reached.
  Do not free or modify the returned key/val pointers.

  See dict_dump() for usage example.
 */
/*--------------------------------------------------------------------------*/
int dict_enumerate(dict * d, int rank, char ** key, char ** val);

/*-------------------------------------------------------------------------*/
/**
  @brief    Dump dict contents to an opened file pointer
  @param    d       dict to dump
  @param    out     File to output data to
  @return   void

  Dump the contents of a dictionary to an opened file pointer.
  It is Ok to pass 'stdout' or 'stderr' as file pointers.

  This function is mostly meant for debugging purposes.
 */
/*--------------------------------------------------------------------------*/
void   dict_dump(dict * d, FILE * out);

#endif

