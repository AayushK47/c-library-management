# Library Management App using C
Created by Aayush Kurup

## About the App

This app was created as a mini project. It is made using C language. It can be used for library management by any organisation.
Using this app, you can store the details of a Member, Book and Issue Records.

## How to run the app

#### For  Windows :-
You'll need to install dev c++ or Code::Blocks to compile the source code. (Tested on dev c++).
Once you build the source code, You'll get an exe file which you can execute to run the application.

#### For Linux and Mac OS:-
You beed GCC complier to be installed on your system.

Before you compile the source code, make these changes in the source code :-
- Using "Find and Replace" find system('cls'); and replace it with system('clear');
- Also paste the following code in the file

```
// add this on the top of the file with other header files
#include <termios.h>
#include <stdio.h>
```
```
// add this anywhere before the main function
static struct termios old, new;
void initTermios(int echo) 
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}

void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getch(void) 
{
  return getch_(0);
}
```

Now simply open the terminal, cd to the directory where library.c file is kept and run the following commands one after the other

```
gcc library.c
./a.out
```

##### Imporant note : Make sure you have a folder named 'files' in the directory where you run the exe file.