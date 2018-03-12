#include "image_processing.h"
#include "common.h"

/*char imagepre_array[25] =
    {
        0, 0, 1, 0, 0,
        0, 0, 1, 1, 1,
        0, 1, 0, 0, 1,
        1, 1, 0, 1, 0,
        0, 1, 0, 1, 0   }; //原始图像
*/

int finalrow,finalrow;

int catchBiggestLabel(Equiva_Pair *pair,RunContent *runs)
{
    int max = pair->runLabels[0];
    for (int i = 0; i <= runs->NumberOfRuns; i++)
    {
        if (max < pair->runLabels[i])
        {
            max = pair->runLabels[i];
        }
    }
    return max;
}
void fillRuns(ImageContent *image, RunContent *runs)
{
    for (int i = 0; i < image->imagerows; i++)
    {
        const uint8 *rowdata = &image->imagedata[i * image->imagecols]; //能将它第一行的首地址赋过来吗

        if (rowdata[0] == WHITE)//第一个像素是白
        {
            runs->NumberOfRuns++;
            runs->stRun[runs->NumberOfRuns] = 0;
            runs->RowRun[runs->NumberOfRuns] = i;
        }

        for (int j = 1; j < image->imagecols; j++)
        {
            if (rowdata[j - 1] == BLACK && rowdata[j] == WHITE)//左黑右白
            {
                runs->NumberOfRuns++;
                runs->stRun[runs->NumberOfRuns] = j;
                runs->RowRun[runs->NumberOfRuns] = i;
            }
            else if (rowdata[j - 1] == WHITE && rowdata[j] == BLACK)//左白右黑
            {
                runs->enRun[runs->NumberOfRuns] = j - 1;
            }
        }

        if (rowdata[image->imagecols - 1])//这一行最后一个像素是白
        {
            runs->enRun[runs->NumberOfRuns] = image->imagecols - 1;
        }
    }
    //printf("%d\n", runs->NumberOfRuns+1);
}

void firstPass(RunContent *runs, Equiva_Pair *pair)//执行完后会把上下两行邻近的团标记成一个标号 同时将等效的团标记进入等价对
{       
    int i, j;

    for (i = 0; i <= runs->NumberOfRuns; i++)//<=
    {
        pair->runLabels[i] = 0;//将所有团的标号都标为0
    }

    int idxLabel = 1;
    int curRowIdx = 0;
    int firstRunOnCur = 0;
    int firstRunOnPre = 0;
    int lastRunOnPre = -1;

    for (i = 0; i <= runs->NumberOfRuns; i++)//<=
    {
        if (runs->RowRun[i] != curRowIdx)
        {
            curRowIdx = runs->RowRun[i];
            firstRunOnPre = firstRunOnCur;
            lastRunOnPre = i - 1;
            firstRunOnCur = i;
        }

        for (j = firstRunOnPre; j <= lastRunOnPre; j++)
        {
            if (runs->stRun[i] <= runs->enRun[j] && runs->enRun[i] >= runs->stRun[j] && runs->RowRun[i] == runs->RowRun[j] + 1)
            {
                if (pair->runLabels[i] == 0)
                {
                    pair->runLabels[i] = pair->runLabels[j];
                }
                else if (pair->runLabels[i] != pair->runLabels[j])
                {
                    pair->NumberOfEquals++;
                    pair->equal[pair->NumberOfEquals].equ_first = pair->runLabels[i];
                    pair->equal[pair->NumberOfEquals].equ_second = pair->runLabels[j];
                }
            }
        }

        if (pair->runLabels[i] == 0)
        {
            pair->runLabels[i] = idxLabel++;
        }
    }
    //printf("%d\t", pair->NumberOfEquals);
}
void replaceSameLabel(Equiva_Pair *pair,TreeList *tree,RunContent *runs)//替换掉相同的等价对 把等价的团标记成同一个标号
{
    int i, j;
    int k = 0;
    int maxLabel = catchBiggestLabel(pair,runs);
    int matrix[LabelsNumbers][LabelsNumbers];
    for (i = 0; i < LabelsNumbers;i++)
    {
        for (j = 0; j < LabelsNumbers;j++)
        {
            matrix[i][j] = 0;
        }
    }
    for (i = 0; i < maxLabel; i++)
    {
        for (j = i; j < maxLabel; j++)
        {
            for (k = 0; k <= pair->NumberOfEquals; k++)
            {

                if ((pair->equal[k].equ_first - 1) == i && (pair->equal[k].equ_second - 1) == j)
                {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                    break;
                }
            }
        }
    } //初始化邻接矩阵

    int labelFlag[LabelsNumbers] = {0}; //

    for (i = 1; i <= maxLabel;i++)
    {
        if(labelFlag[i - 1])
        {
            continue;
        }

        labelFlag[i - 1] = tree->treesize + 1;

        //tree->treeList[tree->treesize].fruitsize++;//结入第一个果子！
        tree->treeList[tree->treesize].fruitList[tree->treeList[tree->treesize].fruitsize] = i;//第0棵树的 第0个果子就是i

        for (j = 0; j <= tree->treeList[tree->treesize].fruitsize;j++)
        {
            for (k = 0; k < maxLabel;k++)
            {
                if (!labelFlag[k] && matrix[tree->treeList[tree->treesize].fruitList[tree->treeList[tree->treesize].fruitsize] - 1][k])
                {
                    //j指的就是那个果子
                    tree->treeList[tree->treesize].fruitsize++; //第一棵树的果子又结了一个
                    tree->treeList[tree->treesize].fruitList[tree->treeList[tree->treesize].fruitsize] = k + 1;//果子就是k+1
                    labelFlag[k] = tree->treesize + 1;//这个果子标上号
                }
            }
        }
        
        tree->treesize++;//树又多了一棵！
    }
    for (i = 0; i < runs->NumberOfRuns;i++)
    {
        pair->runLabels[i] = labelFlag[pair->runLabels[i] - 1];
    }
}
void replaceArray(ImageContent *image, RunContent *runs,Equiva_Pair *pair)//这是把imagedata中的数据标记成团的标号
{
    int i, j;
    int rowNum = 0;

    for (i = 0; i <= runs->NumberOfRuns;i++)
    {
        if(runs->RowRun[i] != rowNum)
        {
            rowNum = runs->RowRun[i];
        }

        for (j = runs->stRun[i]; j <= runs->enRun[i];j++)
        {
            image->imagedata[rowNum * image->imagecols + j] = (char)(pair->runLabels[i]);
        }
    }
}

void extractCenter(ImageContent *image,Location *center)//
{
    int i, j;
    int sumrow[3] = {0}, sumcol[3] = {0};
    int num[3] = {0};
    int max;

    for (i = 0; i < image->imagerows;i++)
    {
        for (j = 0; j < image->imagecols;j++)
        {
            if (image->imagedata[i * image->imagecols + j] == 1)//关键是怎么找到这个2并排除其他干扰
            {
                sumrow[0] += i;
                sumcol[0] += j;
                num[0]++;
            }
            if (image->imagedata[i * image->imagecols + j] == 2)//关键是怎么找到这个2并排除其他干扰
            {
                sumrow[1] += i;
                sumcol[1] += j;
                num[1]++;
            }
            if (image->imagedata[i * image->imagecols + j] == 3)//关键是怎么找到这个2并排除其他干扰
            {
                sumrow[2] += i;
                sumcol[2] += j;
                num[2]++;
            }
        }
    }

    max = num[0];
    for (i = 0; i < 3;i++)
    {
        if(max <= num[i])
        {
            max = num[i];
            j = i;
        } 
    }

    center->row = (int)(sumrow[j] / max);
    center->col = (int)(sumcol[j] / max);
}

void labelCross(uint8 *image,int row,int col)
{
    image[COLS * (row - 1) + col] = WHITE;
    image[COLS * (row - 1) + col + 1] = BLACK;
    image[COLS * (row - 1) + col - 1] = BLACK;
    image[COLS * (row - 2) + col] = BLACK;
    image[COLS * row + col] = BLACK;
}

void image_processing(uint8 *imagepre_array)
{
    int i, j, k;
    ImageContent image_test;
    RunContent run_test;
    Equiva_Pair equival_test;
    TreeList tree_test;
    Location center_test;

    image_test.imagedata = imagepre_array;
    image_test.imagerows = ROWS;
    image_test.imagecols = COLS;
    run_test.NumberOfRuns = -1;
    equival_test.NumberOfEquals = -1;
    tree_test.treesize = 0;
    center_test.col = 0;
    center_test.row = 0;

    for (i = 0; i < 10;i++)
    {
        run_test.stRun[i] = -1;
        run_test.enRun[i] = -1;
        run_test.RowRun[i] = -1;
        equival_test.runLabels[i] = -1;
    }

    for (j = 0; j < 5;j++)
    {
        equival_test.equal[j].equ_first = -1;
        equival_test.equal[j].equ_second = -1;
        tree_test.treeList[j].fruitsize = 0;
        for (k = 0; k < 10; k++)
        {
            tree_test.treeList[j].fruitList[k] = -1;
        }
    }

    fillRuns(&image_test, &run_test);
    firstPass(&run_test, &equival_test);//至此上述代码测试成功！！
    //到了最关键的消除等价对的时候了！！！
    replaceSameLabel(&equival_test, &tree_test, &run_test);//上述代码全部测试成功！！2018.3.3  19:45
    replaceArray(&image_test, &run_test, &equival_test);//可以成功输出连通的图象！！ 20:25!
    extractCenter(&image_test, &center_test);
    labelCross(imagepre_array,center_test.row,center_test.col);
    finalrow = center_test.row;
    finalcol = center_test.col;
    
    /*for (i = 0; i < 5;i++)
    {
        for (j = 0; j < 5;j++)
        {
            printf("%d\t", imagepre_array[i * COLS + j]);
        }
        printf("\n");
    }
    printf("%d\t%d\t", center_test.row, center_test.col);
    */
}
