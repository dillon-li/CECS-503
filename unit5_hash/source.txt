/* Dillon Li
   Assignment 4, Unit 5: Hash Tables
   9/18/2016
*/


#include <iostream>
#include <stdio.h>

using namespace std;

//const int TABLE_SIZE = 128;

// HashEntry class after looking at how everything else is implemented
class HashEntry {
      friend class HashMap;
private:
      int key;
      int value;
      HashEntry* next;
public:
      HashEntry(int lowkey, int highvalue) {
          key = lowkey;
          value = highvalue;
          next = NULL;
      }
      int getKey() {
          return key;
      }
      
      int getValue() {
          return value;
      }
};

class HashMap {
private:
      HashEntry **table;
      int size;
public:
      HashMap(int set_size) {
            size = set_size;
            table = new HashEntry*[size];
            for (int i = 0; i < size; i++)
                  table[i] = NULL;
      }
      
      int get(int key) {
            int hash = (key % size);
            while (table[hash] != NULL && table[hash]->getKey() != key)
                  hash = (hash + 1) % size;
            if (table[hash] == NULL)
                  return -1;
            else
                  return table[hash]->getValue();
      }
 
      void insert(int value) {
            int hash = (value % size);
            /* Linear Probing strategy: Doesn't work with size = 7
            while ((table[hash] != NULL))
                  hash = (hash + 1) % size; */
            
            // Implemented collision handling with linked list stategy
            if (table[hash] == NULL) {
                  table[hash] = new HashEntry(value, value);
                  /* cout << "table[hash]->getValue() is " << table[hash]->getValue() << endl; */}
            else {
                  table[hash]->next = new HashEntry(value, value);
                  }
      }    
      
      // For displaying results
      void printhash()
      {
           for (int i = 0; i < size; i++)
           {
               cout << "In bin " << i << ": ";
               while(table[i] != NULL)
               {
                    cout << table[i]->getValue() << ", ";
                    table[i] = table[i]->next;
               }
               cout << endl;
           }
      }
 
      ~HashMap() {
            for (int i = 0; i < size; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};

main() {
    HashMap map(17);
    int inserted[] = {121, 81, 16, 100, 25, 0, 1, 9, 4, 36, 64, 49};
    for (int i = 0; i < 12; i++)
    {
        map.insert(inserted[i]);
    }
    /* Use the get function with the key (same as value in this case) 
    to print the numbers are inserted into the table to show they're inserted*/
    
    cout << "Printing hashtable for size of 17: " << endl;
    map.printhash();
    
    cout << endl;
    
    // Rehash
    HashMap newMap(7);
    for (int i = 0; i < 12; i++)
    {
        newMap.insert(inserted[i]);
    }
    
    cout << "Printing hashtable for size of 7: " << endl;
    newMap.printhash();
    system("pause");
}
