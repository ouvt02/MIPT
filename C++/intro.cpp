#include <stdio.h>

class Vector
{
public:
    int x;
    int y;
    Vector();
    Vector(int x, int y);
    ~Vector();
    
    Vector sum(vector);
private:
    long hash;
    
    bool check();
};

class 3DVector
{
    int x;
    int y;
    int z;
};






/*
Vector new_vect = sum(vector1, vector2);
new_vect = vector2 + vector1; //reverse of parametres 
*/


/* Creating new object
Vector new_vect = Vector(4, 5);
Vector new_vect(4, 5);

! You cant use last creation without parameters because of compiler see that as a func declaration

Vector* new_vect = new Vector(4, 5); //Not to use!
*/



/*
For class method:
Vector new_vect = vector1.sum(vector2);

in method:
    /////vector1 === this
    
    this -> x + vector2 -> x;
    
*/


// function(struct smth, parameters)
// {smth -> smthelse}

// smth.function(parameters)
// {this -> smthelse}






