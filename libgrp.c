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
bool createKenSilvermanHeader(FILE *grpFile, struct grpFileStructure *grpData, uint32_t numberOfFiles)
{
	char *header = "KenSilverman";

	// check to see if requesting more than maximum allowed in a .grp file.
	if (numberOfFiles > MAXFILESINGRP)
	{
		fprintf(stderr, "Error: maximum number of files in a .grp file is 4096...\n");
		return true;
	}

	rewind(grpFile);

	// Write KenSilverman.
	if (fwrite(header, sizeof(char), 12, grpFile) != 12)
		return true;
	
	// Write file quantity.
	if (fwrite(&numberOfFiles, sizeof(uint32_t), 1, grpFile) != 1)
		return true;

	for (int intCounter = 0; intCounter < numberOfFiles; intCounter++)
	{
		// Write file name.
		if (fwrite(grpData->fileName, sizeof(char), 12, grpFile) != 12)
			return true;

		// Write file Size.
		if (fwrite(&grpData->fileSize, sizeof(uint32_t), 1, grpFile) != 1)
			return true;
	};

	return false;
}
