#include "file_list.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int compare(void const* a, void const* b)
{
    char const* const* pa = (char const * const*) a;
    char const* const* pb = (char const * const*) b;
    return strcmp(*pa, *pb);
}

int sortedFileList(const char* const dirName,
                   char*** fileList,
                   unsigned int nbMax)
{
	unsigned int count = 0;

    DIR* pDir = opendir(dirName);

    if (pDir == NULL)
        fprintf(stderr, "Couldn't open the directory for input patterns: %s\n", dirName);
    struct dirent* pFile;

    // Count the number of files
    while ((pFile = readdir(pDir))) {
        if (pFile->d_name[0] == '.')
            continue;

        ++count;
    }
	//
    // Allocate enough space
    (*fileList) = (char**) malloc(count * sizeof(*(*fileList)));

    if ((*fileList) == NULL) {
        closedir(pDir);
        fprintf(stderr, "sortedFileList(): 'list' memory allocation failed\n");
        return -1;
    }

    count = 0;

    rewinddir(pDir); /* reset position */

    while ((pFile = readdir(pDir)) && (nbMax == 0 || count < nbMax)) {
        if (pFile->d_name[0] == '.')
            continue;

        /* + 2 because of the '/' and the terminating 0 */
        (*fileList)[count] = (char*)malloc((strlen(dirName) + strlen(pFile->d_name)
                                     + 2) * sizeof(*(*fileList)[count]));

        if ((*fileList)[count] == NULL) {
            closedir(pDir);
            fprintf(stderr, "sortedFileList(): 'fileName' memory allocation failed\n");
            return -1;
        }

        sprintf((*fileList)[count], "%s/%s", dirName, pFile->d_name);
        ++count;
    }

    closedir(pDir);

    if (nbMax > 0) {
        printf("sortedFileList(): warning: nbMax > 0 may lead to globally unsorted stimuli!\n");
    }

    qsort((*fileList), count, sizeof(*(*fileList)), compare);
    return count;
}

