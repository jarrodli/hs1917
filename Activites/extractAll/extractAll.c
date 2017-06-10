//  Created by Matthew Di Meglio on 25/05/2016.
#include <assert.h>
#include "extractAll.h"

/* Must move all nodes in the FROM list which meet the condition

   onto the front of the TO list, maintaining the order they were in the FROM list.

   The TO list may not be empty, and all existing nodes of the TO list should remain unchanged at its end.

   You cannot call malloc or free.

   Note the condition function is implemented in the testFile - you can just call it.

   Example:
   int condition(Link n) {return n->value < 5;}

   Before:
   FROM->[3]->[7]->[2]->[1]->[8]->[0]->X
   TO->[11]->[-1]->X

   After:
   FROM->[7]->[8]->X
   TO->[3]->[2]->[1]->[0]->[11]->[-1]->X

*/

void extractAll(List from, List to) {

}