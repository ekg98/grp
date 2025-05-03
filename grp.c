// grp.c - grp - Program to create a .grp file.  Format designed by Ken Silverman.  Thank you for a wonderful build engine.
// Written by William English

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgrp.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("grp - This program creates .grp files\n");
		printf("Usage: grp <file> <file> <file> -o output.grp\n");
		printf("-o may be omitted.  Default filename is untitled.grp\n");
		exit(EXIT_FAILURE);
	}

	// it works it works.  Now to finish the rest of it.

	struct grpFileStructure grpFileData[1];

	FILE* grpFile = fopen("untitled.grp", "wb");

	strcpy(grpFileData[0].fileName, "hello.txt");
	grpFileData[0].fileSize = 6;

	

	if (createKenSilvermanHeader(grpFile, grpFileData, 1) == 1)
		fprintf(stderr, "Failure!\n");

	fclose(grpFile);

	/*if (argc > 4)
		struct grpFileStructure grpFile[argc - 3];*/

	return EXIT_SUCCESS;
}