#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"

#define TRUE 1
#define FALSE 0
#define NUM_POINTS 54

// ===================== PATH SYS ===================== 

// DONE              
// returns the point behind the current vertex
int behind(int current, int previous) {
    return previous;
}

// DONE
// checks what column a position is in
int findColumn(int pos) {
    
    int col = -1;
    
    if(pos >= 0 && pos <= 6) {
        col = 0;
    } else if (pos >= 7 && pos <= 15) {
        col = 1;
    } else if (pos >= 16 && pos <= 26) {
        col = 2;
    } else if (pos >= 27 && pos <= 37) {
        col = 3;
    } else if (pos >= 38 && pos <= 46) {
        col = 4;
    } else if (pos >= 47 && pos <= 53) {
        col = 5;
    }
    
    return col;
    
}

// DONE
// checks if it is possible to move right from a position
int checkRight(int pos) {
    int status = FALSE;
    int col = findColumn(pos);
    
    if (col == 0 || col == 2 || col == 3 || col == 5) {
        if (pos % 2 == 0) {
            status = TRUE;
        } 
    } else if (col == 1 || col == 4) {
        if (pos % 2 == 1) {
            status = TRUE;
        }
    }
    return status;
}

// DONE
// checks what the position is of a point to the right of a position
int posRight(int pos) {
    int add = 0;
    int col = findColumn(pos);
    
    if (col == 0) {
        add = 8;
    } else if (col == 1) {
        add = 10;
    } else if (col == 2) {
        add = 11;
    } else if (col == 3) {
        add = 10;
    } else if (col == 4) {
        add = 8;
    } else if (col == 5) {
        return -1; // right moves off the map
    }
    
    return pos + add;
}

// DONE
// checks what the position is of a point the the left of a position
int posLeft(int pos) {
    int add = 0;
    int col = findColumn(pos);
    
    if (col == 0) {
        return -1; // left moves off the map
    } else if (col == 1) {
        add = 8;
    } else if (col == 2) {
        add = 10;
    } else if (col == 3) {
        add = 11;
    } else if (col == 4) {
        add = 10;
    } else if (col == 5) {
        add = 8;
    }
    
    return pos - add;
}

// DONE 
// check to see if two point lie in the same column
int checkColumn(int point1, int point2) {
    return findColumn(point1) == findColumn(point2);
}

// DONE
// find the point right of the position
//
// LOGIC TEST
// we are currently at point 17 and want to move right (should be point 7)
// previous - current = -1 :: therefore we are facing down
// checkRight(current) == checkright(17) == FALSE 
// therefore next = posLeft(17) == 7
int moveRight(int current, int previous) {
    int next = -1; // assumes off the map
    // test direction
    if (previous - current == 1) {
        // upwards
        if(checkRight(current)) {
            next = posRight(current);
        } else if (checkColumn(current, current - 1)) {
            next = current - 1;
        }
    } else if (previous - current == -1) {
        // downwards
        if(checkRight(current) && checkColumn(current, current + 1)) {
            next = current + 1;
        } else {
            next = posLeft(current);
        }
    } else if (previous < current && checkColumn(current, current + 1)) {
        // right
        next = current + 1;
    } else if (previous > current && checkColumn(current, current - 1)) {
        // left
        next = current - 1; // p = 35 c = 24 :: p > c && TRUE moves to 23
    }
    return next;
}

// DONE
// finds the point left of a position
int moveLeft(int current, int previous) {
    int next = -1;
    
    // test direction
    if (previous - current == 1) {
        // upwards
        if(checkRight(current) && checkColumn(current, current - 1)) {
            next = current - 1;
        } else {
            next = posLeft(current);
        }
    } else if (previous - current == -1) {
        // downwards
        if(checkRight(current)) {
            next = posRight(current); 
        } else if (checkColumn(current, current + 1)) {
            next = current + 1;
        }
        
    } else if (previous < current && checkColumn(current, current -1)) {
        next = current - 1;
    } else if (previous > current && checkColumn(current, current + 1)) {
        next = current + 1;
    }
    return next;
}

// DONE
// converts the path system to the pos/point system
int convert(path p) {
    int len = strlen(p);
    int current = -1;   // current pos off the board
    int previous = 16; // starting pos on the board
    int i = 1;

    if (len == 0) {
        return previous;   
    }   
    
    if (p[0] == 'R') {
        current = 17;
    } else if (p[0] == 'L') {
        current = 27;
    }
    
    while (len > 1 && i < len && current <= NUM_POINTS && current >= 0) {
        int temp = current;
        if (p[i] == 'R') {
            current = moveRight(current, previous);
        } else if (p[i] == 'L') {
            current = moveLeft(current, previous);
        } else if (p[i] == 'B') {
            current = behind(current, previous);
        }
        previous = temp;
        ++i;
    }
    return current;
}