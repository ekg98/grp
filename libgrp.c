// libgrp.c - Contains various functions to handle .grp files designed by Ken Silverman.
//
// by William English

#include "libgrp.h"
#include <string.h>

// isKenSilvermanHeader(): *kenSilverman is a pointer to a 12 byte array.  This function will evaluate the array and determine if it's the correct header for a .grp file.
// returns true(1) on success or false(0) on failure.
bool isKenSilvermanHeader(char *kenSilverman)
{
	if(strncmp(kenSilverman,"KenSilverman", 12) == 0)
		return true;
	else
		return false;
}

// createKenSilvermanHeader(): Create a Ken Silverman header inside a file.  Returns true on failure(1) or false on success(0).
bool createKenSilvermanHeader(int fd, struct grpFileStructure *grpData, uint32_t numberOfFiles)
{
	char *header = "KenSilverman";

	// check to see if requesting more than maximum allowed in a .grp file.
	if (numberOfFiles > MAXFILESINGRP)
	{
		fprintf(stderr, "Error: maximum number of files in a .grp file is 4096...\n");
		return true;
	}

	if (lseek(fd, 0, SEEK_SET) == -1)
		return true;

	// Write KenSilverman.
	if (write(fd, header, 12) != 12)
		return true;
	
	// Write file quantity.
	if (write(fd, &numberOfFiles, 4) != 4)
		return true;

	for (int intCounter = 0; intCounter < numberOfFiles; intCounter++)
	{
		// Write file name.
		if (write(fd, grpData[intCounter].fileName, 12) != 12)
			return true;

		// Write file Size.
		if (write(fd, &grpData[intCounter].fileSize, 4) != 4)
			return true;
	};

	return false;
}
