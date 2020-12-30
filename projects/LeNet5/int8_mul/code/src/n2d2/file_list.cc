#include "file_list.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int compare(void const* a, void const* b)
{
    char const* const* pa = (char const * const *) a;
    char const* const* pb = (char const * const *) b;
    return strcmp(*pa, *pb);
}

int sortedFileList(const char* const dirName,
                   char*** fileList,
                   unsigned int nbMax)
{
    int count = 0;

#ifndef NO_DIRENT
    DIR* pDir = opendir(dirName);

    if (pDir == NULL)
        fprintf(stderr,
                "Couldn't open the directory for input patterns: %s\n",
                dirName);

    struct dirent* pFile;

    // Count the number of files
    while ((pFile = readdir(pDir))) {
        if (pFile->d_name[0] == '.')
            continue;

        ++count;
    }
#else
    char* listName = malloc((strlen(dirName) + strlen(".list")
                                     + 1) * sizeof(char));
    sprintf(listName, "%s.list", dirName);

    FILE *fList = fopen(listName, "r");
    free(listName);

    if (fList == NULL) {
        printf("Error opening .list file!\n");
        exit(1);
    }

    char* line = NULL;
    size_t len = 0;
    int read;

    /* Count the number of files */
    while (((read = getline(&line, &len, fList)) != -1)
        && (nbMax == 0 || count < nbMax))
    {
        ++count;
    }
#endif

    // Allocate enough space
    (*fileList) = (char **) malloc(count * sizeof(*(*fileList)));

    if ((*fileList) == NULL) {
#ifndef NO_DIRENT
        closedir(pDir);
#else
        fclose(fList);
#endif
        fprintf(stderr, "sortedFileList(): 'list' memory allocation failed\n");
        return -1;
    }

    count = 0;

#ifndef NO_DIRENT
    rewinddir(pDir); /* reset position */

    while ((pFile = readdir(pDir)) && (nbMax == 0 || count < nbMax)) {
        if (pFile->d_name[0] == '.')
            continue;

        /* + 2 because of the '/' and the terminating 0 */
        (*fileList)[count] = (char*) malloc((strlen(dirName) + strlen(pFile->d_name)
                                     + 2) * sizeof(*(*fileList)[count]));

        if ((*fileList)[count] == NULL) {
            closedir(pDir);
            fprintf(stderr,
                    "sortedFileList(): 'fileName' memory allocation failed\n");
            return -1;
        }

        sprintf((*fileList)[count], "%s/%s", dirName, pFile->d_name);
        ++count;
    }

    closedir(pDir);

    if (nbMax > 0) {
        printf("sortedFileList(): warning: nbMax > 0 may lead to globally"
               " unsorted stimuli!\n");
    }
#else
    rewind(fList);

    while (((read = getline(&line, &len, fList)) != -1)
        && (nbMax == 0 || count < nbMax))
    {
        (*fileList)[count] = malloc(read * sizeof(*(*fileList)[count]));
        line[read - 1] = '\0'; // skip \n

        sprintf((*fileList)[count], "%s", line);
        ++count;
    }

    fclose(fList);
    free(line);
#endif

    qsort((*fileList), count, sizeof(*(*fileList)), compare);
    return count;
}

