#include <stdio.h>
#include <corecrt_malloc.h>
#include <string.h>
#include<Windows.h>
#include <string>
#include <iostream>
using namespace std;
void destroy(char* fileName, int cut)
{
    FILE* fp = NULL;
    int size = 0;
    fp = fopen(fileName, "rb");
    if (NULL == fp)
    {
        printf("failed!\n");
        return;
    }
    printf("open file %s sucess!\n", fileName);
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    printf("this file has %d words!\n", size);

    char* tmp;
    int read_size;
    char ch;
    char temp[256];
    fclose(fp);
    char del[256] = "del ";
    strcat(del, fileName);
    system(del);
    printf("delete %s sucess!\n",fileName);
}
void findFile(char* pathName)
{
    char findFileName[256];
    memset(findFileName, 0, 256);
    sprintf(findFileName, "%s\\*.*", pathName);
    printf("the filename that you want to find:%s\n", findFileName);

    WIN32_FIND_DATA findData;
    HANDLE hFile = FindFirstFile((LPWSTR)(LPCWSTR)findFileName, &findData);
    printf("%s", (LPWSTR)(LPCWSTR)findFileName);
    //printf("%s", strcat(findFileName, "\\out.txt"));
    if (INVALID_HANDLE_VALUE == hFile)
    {
        // printf("%d,%s",INVALID_HANDLE_VALUE);
        printf("failed!\n");
        return;
    }

}
char* change(LPCTSTR buff)
{
    char newBuff[256];
    for (int i = 0; i < 256; i++)
    {

        if (buff[i] == '\0')
        {
            newBuff[i] = '\0';
            break;
        }
        newBuff[i] = buff[i];

    }
    return newBuff;
}
void findFolder(LPCTSTR folder, char fol[256])
{
    wchar_t Lfol[256];
    for (int i = 0; i < 256; i++)
    {
        Lfol[i] = fol[i];
        if (fol[i] == '\0')
            break;
    }
    folder = Lfol;
    for (int i = 0; i < 256; i++)
    {
        printf("%c", folder[i]);
        if (folder[i] == '\0')
            break;
    }
    printf("\n");
    WIN32_FIND_DATA findData;
    LPCTSTR lpFileName = folder;
    HANDLE hFile = FindFirstFile(folder, &findData);
    int cut = 0;
    int cut2 = 0;
    // fopen("C:\\test\\gg.txt","w");

    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("there are no files in this folder\n");
        return;
    }
    while (FindNextFile(hFile, &findData))
    {
        if (findData.cFileName[0] == '.')
            continue;
        if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            for (int i = 0; i < 256; i++)
            {
                if (fol[i] == '*')
                {
                    cut = i;
                    fol[i] = '\0';
                    break;
                }

            }
            printf("find folder:");
            //strcat(fol,"");
            strcat(fol, change(findData.cFileName));
            strcat(fol, "\\*.*");
            findFolder(((LPCWSTR)(fol)), fol);
            fol[cut] = '*';
            fol[cut + 1] = '.';
            fol[cut + 2] = '*';
            fol[cut + 3] = '\0';
        }
        else {
            for (int i = 0; i < 256; i++)
            {
                if (fol[i] == '*')
                {
                    cut2 = i;
                    break;
                }
            }
            int counter = 0;
            for (int i = cut2; i < 256; i++)
            {
                fol[i] = findData.cFileName[counter];
                if (findData.cFileName[counter] == '\0')
                    break;
                counter++;
            }
            char* loc = strstr(fol, ".jpg");
            if (loc != NULL)
            {
                printf("find file:");
                printf("%s\n", fol);
                destroy(fol, cut2);
            }
            fol[cut2] = '*';
            fol[cut2 + 1] = '.';
            fol[cut2 + 2] = '*';
            fol[cut2 + 3] = '\0';

        }
    }
}
int main()
{
    //jiami((char*)"C:\\test\\example.txt");

    char buff[256] = { 0 };
    char fol[256] = "C:\\test\\*.*";
    LPCTSTR folder = L"C:\\test\\*.*";
    findFolder(folder, fol);
    //findFile(buff);
    //fopen("");
}