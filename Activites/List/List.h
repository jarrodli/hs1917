//
//  List.h
//  Week10
//
//  Created by Matthew Di Meglio on 18/05/2016.
//  Copyright © 2016 Matthew Di Meglio. All rights reserved.
//

#ifndef List_h
#define List_h

#include <stdio.h>

typedef struct _list *List;

List newList();
void freeList(List l);

void insertAtFront(List l, int value);
int removeFromFront(List l);
void insertAtEnd(List l, int value);
#endif /* List_h */
