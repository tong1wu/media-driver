// Disable deprecated
#pragma warning(disable : 4995)

#include <assert.h>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "linkfile.h"

#ifdef LINUX_
#include <dirent.h>
#include <sys/stat.h>
#include <strings.h>
#include <cstring>
#endif

using namespace std;

// Defaults
#define KERNEL                      "kernel"
#define KERNEL_HEADER_FILE_NAME     "krnheader.h"

char KERNEL_COMPONENT_DIR[MAX_STRING_SIZE]        = "";
char KERNEL_HEADER_FILE[MAX_STRING_SIZE]        = "";
char KERNEL_TEMP_HEADER_FILE[MAX_STRING_SIZE]    = "";
char KERNEL_BINARY_FILE[MAX_STRING_SIZE]        = "";
char KERNEL_SEARCH_DIR[MAX_STRING_SIZE]            = "";

char  KERNEL_HEADER_PREFIX[8]       = "";
char  KERNEL_HEADER_GEN[8]          = "";
char  KERNEL_HEADER_KIND[16]        = "";
char  KERNEL_HEADER_PREFIX_UPPER[8] = "";
char  KERNEL_HEADER_SENTRY[64]      = "";
char  KERNEL_IDR[16]                = "";

static const char *COPYRIGHT        =
    "/*\n"
    " * Copyright (c) 2019, Intel Corporation\n"
    " *\n"
    " * Permission is hereby granted, free of charge, to any person obtaining a\n"
    " * copy of this software and associated documentation files (the\n"
    " * 'Software'), to deal in the Software without restriction, including\n"
    " * without limitation the rights to use, copy, modify, merge, publish,\n"
    " * distribute, sublicense, and/or sell copies of the Software, and to\n"
    " * permit persons to whom the Software is furnished to do so, subject to\n"
    " * the following conditions:\n"
    " *\n"
    " * The above copyright notice and this permission notice shall be included\n"
    " * in all copies or substantial portions of the Software.\n"
    " *\n"
    " * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS\n"
    " * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
    " * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n"
    " * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY\n"
    " * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,\n"
    " * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE\n"
    " * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n"
    "*/\n"
    "\n"
    "////////////////////////////////////////////////////////////////////////////////\n"
    "// !!! WARNING - AUTO GENERATED FILE. DO NOT EDIT DIRECTLY. !!!\n"
    "// Generated by GenKrnBin.exe tool\n"
    "////////////////////////////////////////////////////////////////////////////////\n"
;

#define INDEX_OPEN_FORMAT_STRING         "#ifndef %s\n#define %s\n\n\0",              \
    KERNEL_HEADER_SENTRY,                                                                   \
    KERNEL_HEADER_SENTRY
#define INDEX_ENTRY_FORMAT_STRING(index) "#define %s_%s %d\n\0",                          \
    KERNEL_IDR, index, dwKernelCount
#define INDEX_CLOSE_FORMAT_STRING        "\n#endif // %s\0", KERNEL_HEADER_SENTRY
#define INDEX_ENTRY_FORMAT_INT(index,i)  "#define %s_%s %d\n\0",                          \
    KERNEL_IDR, index, i
#define KERNEL_NAME_DEFINE(index)        "#define %s_%s   \\\n",                          \
    KERNEL_IDR, index
#define KERNEL_NAME_ENTRY(index)         "    _" "T(\"%s\"),\\\n",                        \
    index
#define KERNEL_ID_ENTRY(index)           "    _" "T(\"%03d\"),\\\n",                      \
    index

#ifdef LINUX_
#define StrCmp strncasecmp
#else
#define StrCmp strnicmp
#endif

void ConcatenateKernelBinary(char *pKernelName, bool bVerbose);

// scratch global variables for writing files
char    g_Buffer[MAX_STRING_SIZE];
bool    g_bReturn;

// size_t is integral data type returned by the language operator sizeof and is defined in the <cstring> header file (among others) as an unsigned integral type
unsigned int   g_SizetOfTextToWrite;
unsigned int   g_dwNumBytesWritten;

// globals used in multiple functions
FILE          *g_hKernelBinary        = NULL;
unsigned int   g_dwTotalKernelCount   = 0;
unsigned int   g_dwCurrentKernelCount = 0;

// offset table
unsigned int  *g_pOffsetTable;
unsigned int   g_dwOffsetTableSize;
unsigned int   g_dwCurrentKernel;

#ifdef LINUX_
char strupr(char *str) 
{ 
    char *ptr = str;

    while (*ptr != '\0') 
    { 
        if (islower(*ptr)) 
        *ptr = toupper(*ptr); 
        ptr++; 
    }
}

#define _strupr_s strupr
#endif

int main(int argc, char *argv[])
{
    // list template class is based on a doubly-linked list
    list <string> KernelList; // creates an empty list for elements of type "string"
    list <string>::const_iterator iterator; // allows iterating over list <string>
    FILE *hKernelDirs, *hKernels, *hHeaderFile, *hTempHeaderFile;

    // TCHAR data type is char string used to represent a string of either the WCHAR or char type
    char SearchString[MAX_STRING_SIZE];
    char KernelNameNoExt[MAX_STRING_SIZE];
    char KernelNameFull[MAX_STRING_SIZE];
    char KernelBinName[MAX_STRING_SIZE];
    bool  bKernelNames, bVerbose;
    char* pcHeaderFile, pcTempHeaderFile;
    unsigned int dwKernelCount, dwHeaderSize, dwTempHeaderSize, dwBytesRead;

    bVerbose = false;
    if (argc < 5)
    {
        fprintf(stderr, "Usage: GenKrnBin.exe <kernel root dir> <component> [-verbose]\n");
        exit (-1);
    }

    int idx = 5;        // scan the command-line options from index 3
    while (idx < argc)
    {
        if (StrCmp(argv[idx], "-verbose", 8) == 0)
        {
            bVerbose = true;
        }
        ++idx;
    }

#ifdef LINUX_
    sprintf(KERNEL_COMPONENT_DIR,"%s", argv[1]);
    strncpy(KERNEL_HEADER_PREFIX, argv[2], sizeof(KERNEL_HEADER_PREFIX));
    strncpy(KERNEL_HEADER_GEN, argv[3], sizeof(KERNEL_HEADER_GEN));
    strncpy(KERNEL_HEADER_KIND, argv[4], sizeof(KERNEL_HEADER_KIND));
    strncpy(KERNEL_HEADER_PREFIX_UPPER, argv[2], sizeof(KERNEL_HEADER_PREFIX));
   _strupr_s(KERNEL_HEADER_PREFIX_UPPER);

    sprintf(KERNEL_HEADER_FILE, "%s/ig%skrn_%s_%s.h", KERNEL_COMPONENT_DIR, KERNEL_HEADER_PREFIX, KERNEL_HEADER_GEN, KERNEL_HEADER_KIND);
    sprintf(KERNEL_TEMP_HEADER_FILE, "%s/%stemp%s", KERNEL_COMPONENT_DIR, KERNEL_HEADER_PREFIX, KERNEL_HEADER_FILE_NAME);
    sprintf(KERNEL_BINARY_FILE, "%s/ig%skrn_%s_%s.bin", KERNEL_COMPONENT_DIR, KERNEL_HEADER_PREFIX, KERNEL_HEADER_GEN, KERNEL_HEADER_KIND);
    sprintf(KERNEL_SEARCH_DIR, "%s/g*", KERNEL_COMPONENT_DIR);
    sprintf(KERNEL_HEADER_SENTRY, "__%sKRNHEADER_H__", KERNEL_HEADER_PREFIX_UPPER);
    sprintf(KERNEL_IDR, "IDR_%s", KERNEL_HEADER_PREFIX_UPPER);
#else
    sprintf(KERNEL_COMPONENT_DIR,"%s", argv[1]);
    strncpy(KERNEL_HEADER_PREFIX, argv[2], sizeof(KERNEL_HEADER_PREFIX));
    strncpy(KERNEL_HEADER_PREFIX_UPPER, argv[2], sizeof(KERNEL_HEADER_PREFIX));
    _strupr_s(KERNEL_HEADER_PREFIX_UPPER);

    sprintf(KERNEL_HEADER_FILE, "%s\\ig%skrn_g11_icllp.h", KERNEL_COMPONENT_DIR, KERNEL_HEADER_PREFIX);
    sprintf(KERNEL_TEMP_HEADER_FILE, "%s\\%stemp%s", KERNEL_COMPONENT_DIR, KERNEL_HEADER_PREFIX, KERNEL_HEADER_FILE_NAME);
    sprintf(KERNEL_BINARY_FILE, "%s\\ig%skrn_g11_icllp.bin", KERNEL_COMPONENT_DIR, KERNEL_HEADER_PREFIX);
    sprintf(KERNEL_SEARCH_DIR, "%s\\g*", KERNEL_COMPONENT_DIR);
    sprintf(KERNEL_HEADER_SENTRY, "__%sKRNHEADER_H__", KERNEL_HEADER_PREFIX_UPPER);
    sprintf(KERNEL_IDR, "IDR_%s", KERNEL_HEADER_PREFIX_UPPER);
#endif
    bKernelNames = true;

    /////////////////////////////////////////////////
    // Generate a superset list of all the kernels //
    /////////////////////////////////////////////////


#ifdef LINUX_
    sprintf(SearchString, "%s", KERNEL_COMPONENT_DIR);
 
    struct dirent* ent = NULL;

    DIR *pDir=NULL;
    pDir=opendir(SearchString);
    int n;

    while (NULL != (ent=readdir(pDir)))
    {      
        n = strlen(ent->d_name);
        //printf("kernel name  = %s; ent->d_reclen = %d\n", ent->d_name, n);
        //printf("kernel offset= %s\n", ent->d_name + n - 4);

        if ((StrCmp(ent->d_name + n - 4, ".krn", 4) == 0) ||
            (StrCmp(ent->d_name + n - 4, ".hex", 4) == 0))
        {
            KernelList.push_back(string(ent->d_name));
            continue;
        }
        else
        {
            continue;
        }
    };

    closedir(pDir);
#endif

    // include LinkFile.txt
    KernelList.push_back(string("LinkFile.krn"));

    // remove duplicate entries from the list (create superset)
    KernelList.sort();

    // assumes list is sorted. removes subsequent consecutive equal values.
    KernelList.unique();

    ///////////////////////////////////////////////////////////////////
    // Create a temp header that defines the indicies into the table //
    ///////////////////////////////////////////////////////////////////

    // create the header file that will define the kernel IDs
    hHeaderFile = fopen(KERNEL_HEADER_FILE, "w");
    if (hHeaderFile == NULL)
    {
        fprintf(stderr, "Failed to open Temp Header File\n");
        exit (-1);
    }

    // print the copyright comment text to the file
    fwrite(COPYRIGHT, 1, strlen(COPYRIGHT), hHeaderFile);

    fprintf(hHeaderFile, INDEX_OPEN_FORMAT_STRING);
    fprintf(hHeaderFile, INDEX_ENTRY_FORMAT_INT("LINKFILE_VERSION", LINKFILE_VERSION));
    fprintf(hHeaderFile, INDEX_ENTRY_FORMAT_INT("LINKFILE_HEADER" , sizeof(LinkFileHeader)));
    fprintf(hHeaderFile, "\n");

    for (iterator = KernelList.begin(), dwKernelCount = 0;
        iterator != KernelList.end(); iterator++, dwKernelCount++)
    {
        strncpy(KernelNameNoExt, iterator->c_str(), MAX_STRING_SIZE);

        *(strrchr(KernelNameNoExt, '.')) = '\0';
        char *c;
 
        while ((c = strchr(KernelNameNoExt, '.')) != NULL) *c = '_';
        fprintf(hHeaderFile, INDEX_ENTRY_FORMAT_STRING(KernelNameNoExt));
    }

    fprintf(hHeaderFile, INDEX_ENTRY_FORMAT_STRING("TOTAL_NUM_KERNELS"));

    // kernel names are defined in the same sequence as they are loaded
    if (bKernelNames)
    {
        fprintf(hHeaderFile, "\n#if _DEBUG || _RELEASE_INTERNAL\n");
        fprintf(hHeaderFile, KERNEL_NAME_DEFINE("KERNEL_NAMES"));
        for (iterator = KernelList.begin(), dwKernelCount = 0;
        iterator != KernelList.end(); iterator++, dwKernelCount++)
        {
            strncpy(KernelNameNoExt, iterator->c_str(), MAX_STRING_SIZE);
            *(strrchr(KernelNameNoExt, '.')) = '\0';
            char *c;
            while ((c = strchr(KernelNameNoExt, '.')) != NULL) *c = '_';
            fprintf(hHeaderFile, KERNEL_NAME_ENTRY(KernelNameNoExt));
        }
        fprintf(hHeaderFile, "    _" "T(\"\")\n");
        fprintf(hHeaderFile, "#else // !_DEBUG\n");
        fprintf(hHeaderFile, KERNEL_NAME_DEFINE("KERNEL_NAMES"));
        for (int i = 0; i < dwKernelCount; i++)
        {
            fprintf(hHeaderFile, KERNEL_ID_ENTRY(i));
        }
        fprintf(hHeaderFile, "    _" "T(\"\")\n");
        fprintf(hHeaderFile, "#endif // _DEBUG\n");
    }

    fprintf(hHeaderFile, INDEX_CLOSE_FORMAT_STRING);
    fprintf(hHeaderFile, "\n");
    g_dwTotalKernelCount = dwKernelCount;
    fclose(hHeaderFile);

    ///////////////////////////////////////////////////////////////////
    // Create bin containing kernel table and actual kernel binaries //
    ///////////////////////////////////////////////////////////////////
    // allocate kernel offset table
    g_dwOffsetTableSize = (g_dwTotalKernelCount + 1) * sizeof(unsigned int);
    g_pOffsetTable      = (unsigned int *)malloc(g_dwOffsetTableSize);
    if (!g_pOffsetTable)
    {
        fprintf(stderr, "Failed to allocate offset table\n");
        exit (-1);
    }

    // do for every family specific folder
    // create the file that will be the concatenation of all kernel binaries
    sprintf(KernelBinName, "%s", KERNEL_BINARY_FILE);
    g_hKernelBinary = fopen(KernelBinName, "wb");
    if (g_hKernelBinary == NULL)
    {
        fprintf(stderr, "Failed to open Kernel Bin File\n");
        exit (-1);
    }

    // write empty offset table
    memset(g_pOffsetTable,  0, g_dwOffsetTableSize);
    fwrite( g_pOffsetTable, 1, g_dwOffsetTableSize, (FILE *)g_hKernelBinary);

    // create link information for the current family folder
#ifdef LINUX_
    sprintf(KernelNameFull, "%s", KERNEL_COMPONENT_DIR);
#else
    sprintf(KernelNameFull, "%s", KERNEL_COMPONENT_DIR);
#endif
    CreateLinkFile(KernelNameFull, KernelList);

    // for every kernel in the superset list
    g_dwCurrentKernel = 0;
    for (iterator = KernelList.begin(); iterator != KernelList.end(); iterator++, g_dwCurrentKernel++)
    {
        // check if this kernel exists for this platform
        // cFileName contains file name
#ifdef LINUX_
        sprintf(KernelNameFull, "%s/%s", KERNEL_COMPONENT_DIR, iterator->c_str());
#else
        sprintf(KernelNameFull, "%s\\%s", KERNEL_COMPONENT_DIR, iterator->c_str());
#endif
        // add kernel binary, update offset table
        ConcatenateKernelBinary(KernelNameFull, bVerbose);
    }

    // write offset table
    fseek(g_hKernelBinary, 0, SEEK_SET);
    fwrite(g_pOffsetTable, 1, g_dwOffsetTableSize, g_hKernelBinary);

    fclose(g_hKernelBinary);

#ifdef LINUX_
    sprintf(KernelNameFull, "%s", KERNEL_COMPONENT_DIR);
#else
    sprintf(KernelNameFull, "%s", KERNEL_COMPONENT_DIR);
#endif

    DeleteLinkFile(KernelNameFull);

    // free offset table
    if (g_pOffsetTable)
    {
        free(g_pOffsetTable);
    }

    return 0;
}

void ConcatenateKernelBinary(char *pKernelName, bool bVerbose)
{
    FILE *hKernel;
    char pBuffer[MAX_STRING_SIZE];
    unsigned int dwBytesRead, dwBytesWritten, dwBinaryPos, dwFileSize;
    int   iLength;

    // update offset table
    dwBinaryPos = ftell(g_hKernelBinary) - g_dwOffsetTableSize;
    g_pOffsetTable[g_dwCurrentKernel] = dwBinaryPos;

    // the function opens an existing file and returns a handle that can be used to access the object
    // open .krn/.hex file
    hKernel = fopen(pKernelName, "r");

    if (hKernel == NULL)
    {
        fclose(hKernel);
        g_pOffsetTable[g_dwCurrentKernel + 1] = dwBinaryPos;
        return;
    }
    else
    {
        fseek(hKernel, 0, SEEK_END);
        dwFileSize = ftell(hKernel);
        fseek(hKernel, 0, SEEK_SET);
    }

    // print kernel name processed
    if (bVerbose)
    {
        fprintf(stderr, "%s\n", pKernelName);
    }

    // .hex file
    iLength = strlen(pKernelName);
    if (StrCmp(&pKernelName[iLength-4], ".hex", 4) == 0)
    {
        int    iLine = 1;
        char   pBinBuffer[MAX_STRING_SIZE];
        int    iBinLeft = MAX_STRING_SIZE;
        unsigned int * pBinCurrent = (unsigned int *)pBinBuffer;
        char  *pBuffCurrent = pBuffer;
        int    iBuffLeft  = 0;

        dwBytesRead = 0;
        do
        {
            // shift and read hex data
            if (iBuffLeft < 35)
            {
                // move incomplete line to the beginning of the buffer
                if (iBuffLeft)
                {
                    memcpy(pBuffer, pBuffCurrent, iBuffLeft);
                }

                // fill buffer (leave room for 0 at the end of the string)
                pBuffCurrent = pBuffer;
                if (dwBytesRead = fread(pBuffCurrent + iBuffLeft, 1, sizeof(pBuffer) - iBuffLeft - 1, hKernel))
                {
                    // add data
                    iBuffLeft += dwBytesRead;

                    // terminate string with 0 to avoid parsing issues
                    pBuffCurrent[iBuffLeft] = 0;

                    // no data to read - EOF
                    if (dwBytesRead == 0)
                    {
                        iBuffLeft = -1;
                    }
                }
                else
                {
                    iBuffLeft = -1;
                }
            }

            // process hex data one line at a time (35 chars => "xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx")
            while (iBuffLeft >= 35 && iBinLeft > 0)
            {
                // skip CR/LF/TAB (control characters)
                while (iBuffLeft > 35 && *pBuffCurrent < 32)
                {
                    pBuffCurrent++;
                    iBuffLeft--;
                }

                // convert hex to bin (4 DW = 16 B = 128 bits/line)
                if ( 4 != sscanf(pBuffCurrent, "%08x %08x %08x %08x", pBinCurrent, pBinCurrent+1, pBinCurrent+2, pBinCurrent+3) )
                {
                    fprintf(stderr, "Fail to process file %s at line %d\n", pKernelName, iLine);
                    exit(-1);
                }

                // line counter
                iLine++;

                // increment hex buffer
                pBuffCurrent += 35;
                iBuffLeft    -= 35;

                // increment bin buffer
                pBinCurrent += 4;
                iBinLeft    -= 4 * sizeof(unsigned int);

            }

            if (iBinLeft == 0 || iBuffLeft < 0)
            {
                // get actual size of binary buffer
                dwBytesRead = sizeof(pBinBuffer) - iBinLeft;

                dwBinaryPos = ftell(g_hKernelBinary);
                fwrite(pBinBuffer, 1, dwBytesRead, g_hKernelBinary);

                if (iBuffLeft >= 0)
                {
                    pBinCurrent = (unsigned int *)pBinBuffer;
                    iBinLeft    = sizeof(pBinBuffer);
                }
            }
        } while (dwBytesRead > 0 && iBuffLeft >= 0);
    }
    else
    {
        if (fread(pBuffer, 1, sizeof(pBuffer), hKernel))
        {
            dwBinaryPos = ftell(g_hKernelBinary);
            fwrite(pBuffer, 1, dwFileSize, g_hKernelBinary);
        }
    }

    dwBinaryPos = ftell(g_hKernelBinary) - g_dwOffsetTableSize;
    g_pOffsetTable[g_dwCurrentKernel+1] = dwBinaryPos;

    // close kernel file
    if (hKernel != NULL) fclose(hKernel);
}