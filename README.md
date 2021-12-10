# Boa

## Table of Contents
- [Variables](#Variables)
- [Functions](#Functions)

## Variables
Variables are useful with many operations. The store a value and can be called in expressions.

### Variable Declaration
Variables are declared by creating an identifier and a following equal sign. The value you want goes after the equal sign.
```
a = 12          //Variable a is assigned the value 12
b = a + 5       //Variable b is assigned the value 17
x = y = z = 9   //Variables x, y, and z are assigned the value 9

```

### Variable operations
Variables have operations that can be used to modify their values, these operations can be used inside of expressions.
```
c = 90
c += 25         //Variable c is now 115
d = 2
x = 45 + d += 20 //Variable d is now 22 and x is 67
y = 3
y--             //Variable y is now 2
y-=2            //Variable y is now 0
```

# Functions
Functions are used to perform operations on arguments passed through them.

### Function Declaration
Functions are declared by using the 'op' keyword, followed by a (optional) identifer and then parenthesis with the arguments inside, followed by the 'do' keyword and then an expression.
```
op add(a, b) do a + b
```

### Function Calls
Functions are called by using the function identifier followed by parenthesis with the arguments inside.
```
add(1, 2) //Returns 3
```