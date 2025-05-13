// libgrp.h - Header file for definitions to handle grp files designed by Ken Silverman
//
// by William English

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXFILESINGRP	4096

// enumeration for sort
enum sortGrp {
	NONE,
	ASCENDING,
	DECENDING
};

// grpFileStructure:  Structure containing information about the file located inside a .grp file.
struct grpFileStructure
{
	int fd;
	char fileName[13];
	uint32_t fileSize;
	long offset;

	// for sorting later
	struct grpFileStructure *next;
	
};

// isKenSilvermanHeader(): *kenSilverman is a pointer to a 12 byte ASCII array.  Function determines if array contains the header for Ken Silverman's .grp files.
bool isKenSilvermanHeader(char* kenSilverman);

// createKenSilvermanHeader(): Create a Ken Silverman header inside a file.  Returns failure(0) on success or true(0) on failure.
bool createKenSilvermanHeader(int fd, struct grpFileStructure* grpData, uint32_t numberOfFiles);

// sortGrpFileStructure(): Sorts the list of files deposited inside the .grp file depending on selection of enum sort.
bool sortGrpFileStructure(struct grpFileStructure* grpData, enum sortGrp attribute);