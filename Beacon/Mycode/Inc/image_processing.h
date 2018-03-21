#ifndef _RUNS_TEST_H_
#define _RUNS_TEST_H_

#include "VCAN_OV7725_Eagle.h"
#include "common.h"

#define camera_h 60
#define camera_w 80
#define camera_size camera_h * camera_w
#define half_camera_h camera_h/2
#define half_camera_w camera_w/2

#define ROWS camera_h
#define COLS camera_w

#define RunsNumbers 200
#define EqualNumbers 50
#define TreeNumbers 50
#define FruitNumbers 50
#define LabelsNumbers 50
#define TARGET 1

#define BLACK 0
#define WHITE 255

typedef struct
{
    uint8 *imagedata;
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