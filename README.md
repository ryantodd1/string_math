# string_math

This code adds a class titled "nstr". 
Standing for number-string.

It allows for large number computation with strings, and it allows for controllable decimal precision.

Four contructors:
  nstr a(); // Sets a = "0";
  nstr a(const char*);
  nstr a(const std::string&);
  nstr(const nstr&);
  
 The arguments for the contructors are expecting a string that represents a floating point number.
 
 It also theoretically, has no limit on the size of numbers, and the decimal precision.
  
 Whenever an object is created, two static variables are set.
 The variables control decimal precision, and output precision.
 
 Example with multiplication.
 
  nstr num1("12.0236");
  std::cout << num1 * "-2.36" << "\n";
  
  output: -28.375696

When multiplying two floating point numbers together, the decimal size of the result increases by size.

If the above code was run and the static variable "precision" was set to say 5.

The output would then be: -28.37569

But there is nothing stopping a user from setting the precision to a masive number to avoid this error

To increase the precision variable:
  nstr::set_precision(int);  
  This sets the precision variable when doing calculations
  
When doing division, it actually does newton methd and finds the root of the equation (1/x)-a.
Because of this, the accuracy for the division is completely dependent on the precision variable.

The precision variable needs to be at least on larger then the largest power of ten that fits in the divisor.
If the user is dividing by 87980, then the precision needs to be at least 6.

The logic operators that are overloaded are shown below:
  { == , != , >= , <= , > , < }
  
  
