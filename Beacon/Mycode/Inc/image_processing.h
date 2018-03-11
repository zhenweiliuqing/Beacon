#ifndef _RUNS_TEST_H_
#define _RUNS_TEST_H_

#include "VCAN_OV7725_Eagle.h"
#include "common.h"
#define ROWS OV7725_EAGLE_H
#define COLS OV7725_EAGLE_W
#define RunsNumbers 10
#define EqualNumbers 5
#define TreeNumbers 5
#define FruitNumbers 10
#define LabelsNumbers 5
#define TARGET 1

typedef struct
{
    char *imagedata;
    int imagerows;
    int imagecols;
} ImageContent;

typedef struct
{
    int NumberOfRuns;
    int stRun[RunsNumbers];
    int enRun[RunsNumbers];
    int RowRun[RunsNumbers];
} RunContent;

typedef struct
{
    int equ_first;
    int equ_second;
} Equiva_Content;

typedef struct
{
    int runLabels[RunsNumbers];
    int NumberOfEquals;
    Equiva_Content equal[EqualNumbers];
} Equiva_Pair;

typedef struct
{
    int fruitsize;
    int fruitList[FruitNumbers];
} FruitList;

typedef struct
{
    FruitList treeList[TreeNumbers];
    int treesize;
} TreeList;

typedef struct
{
    int row;
    int col;
} Location;

extern int catchBiggestLabel(Equiva_Pair *pair, RunContent *runs);
extern void fillRuns(ImageContent *image, RunContent *runs);
extern void firstPass(RunContent *runs, Equiva_Pair *pair);
extern void replaceSameLabel(Equiva_Pair *pair, TreeList *tree, RunContent *runs);
extern void replaceArray(ImageContent *image, RunContent *runs, Equiva_Pair *pair);
extern void extractCenter(ImageContent *image, Location *center);
extern void image_processing(uint8 *imagepre_array);

#endif 