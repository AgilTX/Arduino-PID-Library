# Arduino PID Library - Version 1.3.1
 
by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
additional edits by Josh DeWitt <dotdash32@gmail.com>, Agil Therapeutics
 This Library is licensed under the MIT License

For an ultra-detailed explanation of why the code is the way it is, please visit:

- http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/

For function documentation see:

- http://playground.arduino.cc/Code/PIDLibrary

Update - Version 1.3.  Before including the library, use

```cpp
#define USE_64bit_FLOATINGPOINT
```

to use `double`s rather than `float`s.
This was included for low overhead processors, or those that have a 32 bit FPU,
but not a 64 bit one and that time optimization is worth it.
