// E-- programming language
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  // open the input file
  FILE* input = fopen(argv[1], "r");
  // See if the user did something wrong
  if (!input) {
    printf("you did something wrong\n");
    return 1;
  }

  // read the input file one character at a time
  char c;
  while ((c = fgetc(input)) != EOF) {
    // check for printf
    if (c == 'p' && fgetc(input) == 'r' && fgetc(input) == 'i' && fgetc(input) == 'n' && fgetc(input) == 't' && fgetc(input) == 'f') {
      // read the entire line into a buffer
      char line[256];
      fgets(line, sizeof(line), input);

      // parse the format string and arguments
      char formatString[256];
      if (sscanf(line, "printf %[^\n]", formatString) == 1) {
        printf(formatString);
      }
    } else if (c == 'v' && fgetc(input) == 'a' && fgetc(input) == 'r') {
      // read a variable
      char type[256];
      char name[256];
      int i = 0;
      while ((c = fgetc(input)) != ' ' && c != '=') {
        type[i++] = c;
      }
      type[i] = '\0';
      i = 0;
      while ((c = fgetc(input)) != '=') {
        name[i++] = c;
      }
      name[i] = '\0';
      // skip the '=' and any whitespace before the value
      while (isspace(c = fgetc(input))) {}
      if (strcmp(type, "int") == 0) {
        // read an integer value
        int value;
        if (fscanf(input, "%d", &value) == 1) {
          printf("Read integer variable '%s' with value %d\n", name, value);
        } else {
          printf("Error reading integer variable '%s'\n", name);
        }
      } else if (strcmp(type, "float") == 0) {
        // read a floating point value
        float value;
        if (fscanf(input, "%f", &value) == 1) {
          printf("Read float variable '%s' with value %f\n", name, value);
        } else {
          printf("Error reading float variable '%s'\n", name);
        }
      } else if (strcmp(type, "string") == 0) {
        // read a string value
        char value[256];
        if (fscanf(input, "%s", value) == 1) {
          printf("Read string variable '%'s' with value '%s'\n", name, value);
        } else {
          printf("Error reading string variable '%s'\n", name);
        }
      } else {
        printf("Error: unknown variable type '%s'\n", type);
      }
    }
  }
  fclose(input);
  return 0;
}