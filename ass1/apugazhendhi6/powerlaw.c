// Declaring the Header files for Standard Input/Output and library for mathematical functions
#include <stdio.h> // Standard input and output functions
#include <math.h> //math function

// Calling the main excetution function
double main()
{
// //inputing the data : Body mass(kg) & Maximum Speed(km/hr) 
double mass[] = { 4.22E-04, 4.50E-04, 3.90E-04,  0.0138, 5.22E-06,  6.86E-06, 1.30E-06, 1.76E-07, 7.47E-07,  7.89E-08,  2.05E-07,  9.00E-05,  1.70E-04,  0.0015, 4.73E-05, 0.002, 0.002, 6.52E-05,  1.01E-04 };
double maxSpeed[] = { 36, 27, 25.92, 36, 6.48, 4.8, 3.6, 3.24, 6.84, 3.06, 4.32, 36, 36, 25.56, 6, 19.08, 18, 10.8, 23.76  } ;

// Validation case for a simple known parabola y = 1 * x ^ 2:
// double mass[] = { 1,2,3,4,5,6,7,8,9,10 }; // X
// double maxSpeed[]={ 1,4,9,16,25,36,49,64,81,100}; // Y

//Calculating length of array mass(or maxSpeed)  using the sizeof function.

int size = sizeof(mass)/sizeof(mass[0]); 

//Declaring the variables (elements) of the inverse Matrix M^-1
double m11 = size, m12 = 0,m21 = 0,m22 = 0,b1 = 0,b2 = 0;

//determination of matrix (M^-1) & vector(b) elements (elemen-wise using for loop)
for ( int i=0; i < size; i++)
    {
        mass[i] = log(mass[i]);
        maxSpeed[i] = log(maxSpeed[i]);
        m12 = m12 + mass[i];
        m21 = m21 + mass[i];
        m22 = m22 + mass[i]*mass[i];
        b1 = b1 + maxSpeed[i];
        b2 = b2 + mass[i]*maxSpeed[i];
    }
//Calculating co-efficent and exponents for the relationship between BodyMass and their Maxspeed
double c = exp(((m22*b1)+(-m12*b2))/((m11*m22)-(m12*m21))); 
double a = ((-m21*b1)+(m11*b2))/((m11*m22)-(m12*m21));

// Output Design

printf("\n\n ###############################################################################################");
printf("\n Welcome to CSE 6010 : Computational Problem Solving\n");
printf("\n Fall 2020 \n");
printf("\n Assignment 1 :");
printf(" Power Law with Least Squares Fitting \n");
printf(" ###############################################################################################");
printf("\n \n Exponential Least Squares Curve fitting for the Animal's Bodymass and their Max Speeds \n");
printf("\n Taxonomical Group considered : Flying Arthropods (ie. jointed leg flying insects) \n \n");
printf("\n \t|-----------------------------------------------|");
printf("\n \t| Body Mass[kg] \t|   max.speed[km/h]     |");
printf("\n \t|-----------------------------------------------|\n");

 // for loop for printing body mass and max.speed
for ( int j=0; j < size; j++)
  {    
    printf("\t|\t %f \t|\t %f \t|\t \n",exp(mass[j]),exp(maxSpeed[j]));
  }
printf("\t|-----------------------------------------------|\n");
printf("\n The power law exponent is %.3f and the coefficient is %.3f\n", a, c);
printf("\n The physical relationship between the Bodymass and Max.speed is given the equation: \n" );
printf("\n Max.Speed = %.3f * BodyMass ^  %.3f\n", c,a );
printf("\n programed by Amirtha Ganesh Pugazhendhi \n");
printf("\n \n");



}