#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}

	int capacity = 10;
	char **arr = malloc(capacity * sizeof(char *));
	int count = 0;
	char buf[COLS];

	while (fgets(buf, COLS, in))
	{
		// Trim newline
		char *nl = strchr(buf, '\n');
		if (nl) *nl = '\0';

		// Expand array if necessary
		if (count == capacity)
		{
			capacity *= 2;
			arr = realloc(arr, capacity * sizeof(char *));
		}

		// Allocate memory for the string and copy it
		char *str = malloc(strlen(buf) + 1);
		strcpy(str, buf);
		arr[count] = str;
		count++;
	}

	fclose(in);

	// The size should be the number of entries in the array.
	*size = count;

	// Return pointer to the array of strings.
	return arr;
}

char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}

	int capacity = 10;
	char (*arr)[COLS] = malloc(capacity * sizeof(*arr));
	int count = 0;
	char buf[COLS];

	while (fgets(buf, COLS, in))
	{
		// Trim newline
		char *nl = strchr(buf, '\n');
		if (nl) *nl = '\0';

		// Expand array if necessary
		if (count == capacity)
		{
			capacity *= 2;
			arr = realloc(arr, capacity * sizeof(*arr));
		}

		// Copy line into the 2D array
		strcpy(arr[count], buf);
		count++;
	}

	fclose(in);

	// The size should be the number of entries in the array.
	*size = count;

	// Return pointer to the array.
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (strstr(lines[i], target))
			return lines[i];
	}
	return NULL;
}

char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (strstr(lines[i], target))
			return lines[i];
	}
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for (int i = 0; i < size; i++)
		free(arr[i]);
	free(arr);
}

void free2D(char (*arr)[COLS])
{
	free(arr);
}