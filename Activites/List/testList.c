//
//  main.c
//  Week10
//
//  Created by Matthew Di Meglio on 13/05/2016.
//  Copyright © 2016 Matthew Di Meglio. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

#include "List.h"

int main(int argc, const char * argv[]) {
    
    List myList = newList();
    
    insertAtFront(myList, 10);
    assert(removeFromFront(myList) == 10);
    
    insertAtFront(myList, 10);
    insertAtFront(myList, 3);
    insertAtFront(myList, 5);
    insertAtFront(myList, 7);
    assert(removeFromFront(myList) == 7);
    assert(removeFromFront(myList) == 5);
    insertAtEnd(myList, 16);
    insertAtEnd(myList, 19);
    assert(removeFromFront(myList) == 3);
    assert(removeFromFront(myList) == 10);
    assert(removeFromFront(myList) == 16);
    assert(removeFromFront(myList) == 19);
    
    insertAtEnd(myList, 4);
    assert(removeFromFront(myList) == 4);
    
    printf("Awesome!\n");
    
    
    return 0;
}
