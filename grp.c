// grp.c - grp - Program to create a .grp file.  Format designed by Ken Silverman.  Thank you for a wonderful build engine.
// Written by William English

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
		
	char grpFileName[13] = "untitled.grp";
	int grpFileQuantity = 0;

	// look for a argument switch string and set the options to process the .grp file
	for (int intArgCounter = 0; intArgCounter < argc; intArgCounter++)
	{
		// only count files and not the program lol
		if(intArgCounter > 0)
			grpFileQuantity++;

		// look for the switch
		if (strncmp(argv[intArgCounter], "-", 1) == 0)
		{
			// walk through the string
			for (int intCounter = 0; intCounter < strlen(argv[intArgCounter]); intCounter++)
			{
				// evaluate each character in the switch
				switch (*(argv[intArgCounter] + intCounter ))
				{
				case '-':
					// ignore the - Could be obtained by intCounter+1 but I think this is more readable.
					break;
				case 'o':
					if (intArgCounter < (argc - 1))
						strncpy(grpFileName, argv[intArgCounter + 1], 13);
					else
					{
						fprintf(stderr, "Error: No output filename specified...\n");
						exit(EXIT_FAILURE);
					}
					grpFileQuantity = argc - 3;
					break;
				case 'h':
					printf("Your seeking some help...  None Found yet!\n");
					exit(EXIT_SUCCESS);
					break;
				case '\0':
					// ignore the newline char
					break;
				default:
					fprintf(stderr, "Error: Unknown switch...  Exiting...\n");
					exit(EXIT_FAILURE);
					break;
				}
			}
			break;
		}
	}

	printf("Using output file name %s\n", grpFileName);
	printf("Grouping %d file(s)...\n", grpFileQuantity);

	struct grpFileStructure grpFileData[grpFileQuantity];
	

	// Add information to grpFileStructure grpFileData
	for (int intCounter = 0; intCounter < grpFileQuantity; intCounter++)
	{
		struct stat buffer;
		
		strncpy(grpFileData[intCounter].fileName, argv[intCounter + 1], 13);
		
		// do file size?
		if ((grpFileData[intCounter].fd = open(grpFileData[intCounter].fileName, O_RDONLY)) == -1)
			fprintf(stderr, "File %s not found...\n", grpFileData[intCounter].fileName);

		if (fstat(grpFileData[intCounter].fd, &buffer) == -1)
			fprintf(stderr, "Error obtaining file data.\n");

		grpFileData[intCounter].fileSize = buffer.st_size;

		printf("%s %d\n", grpFileData[intCounter].fileName, grpFileData[intCounter].fileSize);

		// we dont need these yet
		grpFileData[intCounter].offset = 0;
		grpFileData[intCounter].next = NULL;

		
	}
	
	// open the new group file
	int grpFile = open(grpFileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (createKenSilvermanHeader(grpFile, grpFileData, grpFileQuantity) == 1)
		fprintf(stderr, "Failure!\n");

	// transfer data.
	for (int intCounter = 0; intCounter < grpFileQuantity; intCounter++)
	{
		uint8_t byteBuf;
		
		for (long byteCounter = 0; byteCounter < grpFileData[intCounter].fileSize; byteCounter++)
		{
			read(grpFileData[intCounter].fd, &byteBuf, 1);
			write(grpFile, &byteBuf, 1);
		}
	}

	// close the files that were opened for reading.
	for (int intCounter = 0; intCounter < grpFileQuantity; intCounter++)
	{
		if (grpFileData[intCounter].fd != -1)
			close(grpFileData[intCounter].fd);
	}

	close(grpFile);
		
	return EXIT_SUCCESS;
}