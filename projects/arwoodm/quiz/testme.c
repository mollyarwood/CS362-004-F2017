#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    char c;
    char array[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
    int r = rand() % 9;

    c = array[r];
    return c;
}

char *inputString()
{
    // TODO: rewrite this function
    int i;
    int array[26];
    char stringArr[6];
    char *s = malloc(6 * sizeof(char *));
    int r;


    for (i = 0; i < 26; i++) {
      array[i] = i + 97;
    }


    for (i = 0; i < 6; i++) {
      stringArr[i] = '\0';
    }

    for (i = 0; i < 5; i++) {
      r = rand() % 26;
      stringArr[i] = array[r];
    }

    strcpy(s, stringArr);
    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  //s = inputString();
  //printf("%s \n", s);
  
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
  
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    //const char *s;
    //s = inputString();
    return 0;
}
