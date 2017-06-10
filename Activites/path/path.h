#define PATH_LIMIT 150

typedef char path[PATH_LIMIT]; 

// returns the point behind the current vertex
int behind(int current, int previous);

// checks what column a position is in
int findColumn(int pos);

// checks if it is possible to move right from a position
int checkRight(int pos);

// checks what the position is of a point to the right of a position
int posRight(int pos);

// checks what the position is of a point the the left of a position
int posLeft(int pos);

// check to see if two point lie in the same column
int checkColumn(int point1, int point2);

// find the point right of the position
//
// LOGIC TEST
// we are currently at point 17 and want to move right (should be point 7)
// previous - current = -1 :: therefore we are facing down
// checkRight(current) == checkright(17) == FALSE 
// therefore next = posLeft(17) == 7
int moveRight(int current, int previous);

// finds the point left of a position
int moveLeft(int current, int previous);

// converts the path system to the pos/point system
int convert(path p);