/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);

    // main method starts here
int main(int argc, char** argv){

    if (argc < 3) {
        return 0;
    }
    FILE* trainData = fopen(argv[1], "r");
    if (trainData == NULL) {
        return 0;
    }
	FILE* testData = fopen(argv[2], "r");
    if (testData == NULL) {
        return 0;
    }

    int attributes, numExamples, numTest;
    fscanf(trainData, "%d\n%d", &attributes, &numExamples);
    fscanf(testData, "%d", &numTest);

    //allocating memory for trainMatrix
    double** trainMatrix = malloc(numExamples*sizeof(double*));
    for (int i = 0; i < numExamples; i++) {
        trainMatrix[i] = malloc((attributes+1)*sizeof(double));
    }
    //allocating memory for house prices matrix (Y)
    double** Y = malloc(numExamples*sizeof(double*));
    for (int i = 0; i < numExamples; i++) {
        Y[i] = malloc(sizeof(double));
    }
    //allocating memory for testMatrix
    double** testMatrix = malloc(numTest*sizeof(double*));
    for (int i = 0; i < numTest; i++) {
        testMatrix[i] = malloc((attributes+1)*sizeof(double));
    }
    
    //first column of trainMatrix is 1
    for (int i = 0; i < numExamples; i++) {
        trainMatrix[i][0] = 1;
    }
    //scan train data into trainMatrix
    for (int i = 0; i < numExamples; i++) {
        for (int j = 0; j <= attributes; j++) {
            if (j != attributes) {
                fscanf(trainData, "%lf,", &trainMatrix[i][j+1]);
            }
            else {
                fscanf(trainData, "%lf,", &Y[i][0]);
            }
        }
    }

    //first column of testMatrix is 1
    for (int i = 0; i < numTest; i++) {
        testMatrix[i][0] = 1;
    }
    //scan test data into testMatrix
    for (int i = 0; i < numTest; i++) {
        for (int j = 0; j < attributes; j++) {
            fscanf(testData, "%lf,", &testMatrix[i][j+1]);
        }
    }

    double** Xt = transposeMatrix(trainMatrix, numExamples, attributes+1);
    double** XtX = multiplyMatrix(Xt, trainMatrix, attributes+1, numExamples, numExamples, attributes+1);
    double** invXtX = inverseMatrix(XtX, attributes+1);
    double** XtY = multiplyMatrix(Xt, Y, attributes+1, numExamples, numExamples, 1); 
    double** W = multiplyMatrix(invXtX, XtY, attributes+1, attributes+1, attributes+1, 1);
    double** Yprime = multiplyMatrix(testMatrix, W, numTest, attributes+1, attributes+1, 1);

    for (int i = 0; i < numTest; i++) {
        printf("%0.0lf\n", Yprime[i][0]);
    }


    // //prints trainMatrix
    // printf("X\n");
    // for (int i = 0; i < numExamples; i++) {
    //     for (int j = 0; j <= attributes; j++) {
    //         printf("%lf ", trainMatrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // //prints Y
    // printf("Y\n");
    // for (int i = 0; i < numExamples; i++) {
    //     printf("%lf\n", Y[i][0]);
    // }
    // //prints Xt
    // printf("Xt\n");
    // for (int i = 0; i <= attributes; i++) {
    //     for (int j = 0; j < numExamples; j++) {
    //         printf("%lf ", Xt[i][j]);
    //     }
    //     printf("\n");
    // }
    // //prints XtX
    // printf("XtX\n");
    // for (int i = 0; i <= attributes; i++) {
    //     for (int j = 0; j <= attributes; j++) {
    //         printf("%lf ", XtX[i][j]);
    //     }
    //     printf("\n");
    // }
    // //prints invXtX
    // printf("invXtX\n");
    // for (int i = 0; i <= attributes; i++) {
    //     for (int j = 0; j <= attributes; j++) {
    //         printf("%lf ", invXtX[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("XtY\n");
    // for (int i = 0; i <= attributes; i++) {
    //     printf("%lf\n", XtY[i][0]);
    // }
    // printf("Weights\n");
    // for (int i = 0; i <= attributes; i++) {
    //     printf("%lf\n", W[i][0]);
    // }
    // //prints testMatrix
    // printf("testMatrix\n");
    // for (int i = 0; i < numTest; i++) {
    //     for (int j = 0; j <= attributes; j++) {
    //         printf("%lf ", testMatrix[i][j]);
    //     }
    //     printf("\n");
    // }

    //free matricies
    for (int i = 0; i < numExamples; i++) {
        free(trainMatrix[i]);
    }
    free(trainMatrix);

    for (int i = 0; i < numExamples; i++) {
        free(Y[i]);
    }
    free(Y);
    for (int i = 0; i < numTest; i++) {
        free(testMatrix[i]);
    }
    free(testMatrix);
    for (int i = 0; i <= attributes; i++) {
        free(Xt[i]);
    }
    free(Xt);
    for (int i = 0; i <= attributes; i++) {
        free(XtX[i]);
    }
    free(XtX);
    for (int i = 0; i <= attributes; i++) {
        free(invXtX[i]);
    }
    free(invXtX);
    for (int i = 0; i <= attributes; i++) {
        free(XtY[i]);
    }
    free(XtY);
    for (int i = 0; i <= attributes; i++) {
        free(W[i]);
    }
    free(W);
    for (int i = 0; i < numTest; i++) {
        free(Yprime[i]);
    }
    free(Yprime);


	return 0;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*)); 
    for (int i = 0; i < r1; i++) {
        result[i] = malloc(c2*sizeof(double));
    }
    
    for (int i = 0; i < r1; i++) { 
        for (int j = 0; j < c2; j++) { 
            result[i][j] = 0; 
            for (int k = 0; k < c1; k++) {
                result[i][j] += matA[i][k]*matB[k][j];
            }
        }
    } 
    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
	double** matTran=malloc(col*sizeof(double*)); 
    for (int i = 0; i < col; i++) {
        matTran[i] = malloc(row*sizeof(double));
    }

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            matTran[i][j] = mat[j][i];
        }
    }
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension)
{

    double** matI=malloc(dimension*sizeof(double*)); 
    for (int i = 0; i < dimension; i++) {
        matI[i] = malloc(dimension*sizeof(double));
    }
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i == j) {
                matI[i][j] = 1;
            }
            else {
                matI[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < dimension; i++) {
        if (matA[i][i] != 1) {
            double pivot = matA[i][i];
            for (int j = 0; j < dimension; j++) {
                matA[i][j] /= pivot;
                matI[i][j] /= pivot;
            }
        }
        for (int k = i + 1; k < dimension; k++) {
            double temp = matA[k][i];
            for (int l = 0; l < dimension; l++) {
                matA[k][l] -= (temp*matA[i][l]);
                matI[k][l] -= (temp*matI[i][l]);
            }
        }
    }
    for (int i = dimension - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double temp = matA[j][i];
            for (int k = dimension - 1; k >= 0; k--) {
                matA[j][k] -= (temp*matA[i][k]);
                matI[j][k] -= (temp*matI[i][k]);
            }
        }
    }

	return matI;
}
