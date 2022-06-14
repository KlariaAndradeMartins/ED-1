#include <stdio.h>
#include <stdlib.h>

//Definindo estrutura para matriz
struct matrice
{
    int numLines;
    int numColumns;
    int *data;
};
//Chamada das funções necessárias nas operações
//Tipo matriz sendo definido para as funções subsequentes
typedef struct matrice matrice;

//(a)Criação da matriz
matrice *create_matrice(int numLines, int numColumns);

//(b)Liberar a memória associada a matriz
void free_matrice(matrice *mat);

//Associando valores à matriz
void set_matrice_data(matrice *mat, int line, int column, int val);

//Retornando valores da matriz
int get_matrice_data(matrice *mat, int line, int column, int *val);

//Numero de linhas
int matrice_lines(matrice *mat);

//Numero de colunas
int matrice_columns(matrice *mat);

//Preenche a matriz
void fill_matrice(matrice *mat,int numLines,int numColumns);

//Imprime a matriz na linha de comando
void print_matrice(matrice *mat,int numLines,int numColumns);

//(d) Função de transposição
matrice* matrice_transp(matrice *mat);

//(e) SOma de matrizes 
matrice* matrice_sum(matrice *mat, matrice *mat2);

//(f)Produto de matrizes
matrice* matrice_mult(matrice *mat, matrice*mat2);

//(g)Protudo por um inteiro
matrice* prod_escalar_matrice(int l,matrice* mat);

int main(){

    //(c)Ler o numero de linhas e de colunas e os elementos da matriz
    // Inicializando variáveis utilizadas no projeto
    int numLines, numColumns, k;

    //Matrizes iniciais
    matrice *matriceA, *matriceB, *matriceC;

    //Matrizes resultantes das operações
    matrice *sum_matrice,*mult_matrice,*transp_matrice,*transp_matrice2,*prod_esc_matrice;

    //Recebendo os dados e o inteiro K e em seguida criando da matriz A
    scanf("%d",&k);
    scanf("%d %d",&numLines,&numColumns);
    matriceA = create_matrice(numLines,numColumns);
    if(matriceA != NULL){
        fill_matrice(matriceA, numLines, numColumns);
    }

    //Recebendo os dados da matriz B
    scanf("%d %d",&numLines,&numColumns);
    matriceB = create_matrice(numLines,numColumns);
    if(matriceB != NULL){
        fill_matrice(matriceB, numLines, numColumns);
    }

    //Recebendo os dados da matriz C
    scanf("%d %d",&numLines,&numColumns);
    matriceC = create_matrice(numLines,numColumns);
    if(matriceC != NULL){
        fill_matrice(matriceC, numLines, numColumns);
    }

    //Realizando a soma A + B (1)
    sum_matrice=matrice_sum(matriceA,matriceB);
    if(sum_matrice != NULL){
            print_matrice(sum_matrice, matrice_lines(sum_matrice), matrice_columns(sum_matrice));
    }

    //Realizando a multiplicação A x B (2)
    mult_matrice=matrice_mult(matriceA,matriceC);
    if(mult_matrice !=NULL){
        print_matrice(mult_matrice, matrice_lines(mult_matrice), matrice_columns(mult_matrice));
    }

    //Realizando a multiplicação pelo escalar k (3)
    prod_esc_matrice = matrice_mult(matriceB,matriceC);
    if(prod_esc_matrice != NULL){
        prod_esc_matrice = prod_escalar_matrice(k,prod_esc_matrice);
    }
    if(prod_esc_matrice != NULL){
        print_matrice(prod_esc_matrice, matrice_lines(prod_esc_matrice), matrice_columns(prod_esc_matrice));
    }

    //Realizando a operação: Transposta da matriz C + a matriz B(4)
    transp_matrice=matrice_sum(matrice_transp(matriceC),matriceB);
    if(transp_matrice !=NULL){
        print_matrice(transp_matrice, matrice_lines(transp_matrice), matrice_columns(transp_matrice));
    }

    
    //Realizando a operação : transposta da matriz b + transposta da matriz A(5)
    transp_matrice2=matrice_sum(matrice_transp(matriceB),matrice_transp(matriceA));
    if(transp_matrice2!=NULL){
        print_matrice(transp_matrice2, matrice_lines(transp_matrice2), matrice_columns(transp_matrice2));
    }
    

    //liberando a memoria alocada;
    free_matrice(matriceA);
    free_matrice(matriceB);
    free_matrice(matriceC);
    free_matrice(transp_matrice);
    free_matrice(transp_matrice2);
    free_matrice(sum_matrice);
    free_matrice(prod_esc_matrice);

    return 0;
}

//Implementações das funções enunciadas no começo do código

matrice *create_matrice(int numLines, int numColumns){
    if(numLines < 0 || numColumns < 0){
        return NULL;
    } 
    matrice *mat;
    mat =(matrice*) malloc(sizeof(matrice));
    if(mat != NULL){
        //Alocando a memória correpondente aos dados da matriz utilizando o (nuprod_esc_matricero de linhas x nuprod_esc_matricero de colunas x o tipo de dado (int))
        mat->data = malloc(numLines * numColumns * sizeof(int));
        //Caso a alocação da prod_esc_matricemória para os dados tenha ocorrido corretaprod_esc_matricente, os valores para linhas e colunas são setados
        if(mat->data != NULL){
            mat->numLines=numLines;
            mat->numColumns=numColumns;
        }else {
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void free_matrice(matrice *mat){
//Liberando a prod_esc_matricemória dos dados dentro da struct matriz e depois da própria matriz
    if(mat != NULL){
        free(mat->data);
        free(mat);
    }
}

void set_matrice_data(matrice *mat, int line, int column, int val){
    if(mat == NULL) {
        return;
    }
    int index; //Indice onde o dado será colocado

    if(line < 0 || column < 0 || line > mat->numLines || column > mat->numColumns){
        return;
    }
    index = line*mat->numColumns + column;
    mat->data[index] = val;
}

int get_matrice_data(matrice *mat, int line, int column, int *val){
    if(mat == NULL) {
        return 0;
    }
    int index;//Indice onde o dado será lido

    if(line < 0 || column < 0 || line > mat->numLines || column > mat->numColumns){
        return 0;
    }
    index = line*mat->numColumns+column;
    //Variável que será passada por referência para receber o dado procurado
    *val = mat->data[index];
    return 1;
}

int matrice_lines(matrice *mat){
    return mat->numLines;
}

int matrice_columns(matrice *mat){
    return mat->numColumns;
}

void fill_matrice(matrice *mat,int numLines,int numColumns){
    int i,j,val;
    for(i=0;i<numLines;i++){
        for(j=0;j<numColumns;j++){
            scanf("%d",&val);
            set_matrice_data(mat,i,j,val);
        }
    }
}

void print_matrice(matrice *mat,int numLines,int numColumns){
    int i,j,var_aux,var_test;
    for(i=0;i<numLines;i++){
        for(j=0;j<numColumns;j++){
            var_test=get_matrice_data(mat,i,j,&var_aux);
            if(var_test==1){
                printf("%d\n",var_aux);
            }
        }
    }
}

matrice* matrice_transp(matrice *mat){
    if (mat == NULL) {
        return NULL;
    }
    matrice* mat_transp;
    int i,j,k=0,aux;
    mat_transp=create_matrice(matrice_columns(mat),matrice_lines(mat));
    aux=mat->numLines*mat->numColumns;
    for(j=0;j<mat->numColumns;j++){
        for(i=0;i<aux;i=i+mat->numColumns){
                mat_transp->data[k]=mat->data[i+j];
                k++;
        }
    }
    return mat_transp;
}

matrice* matrice_sum(matrice*mat, matrice*mat2){

    matrice*mat_sum;

    mat_sum= create_matrice(matrice_lines(mat),matrice_columns(mat));

    if(mat==NULL || mat2 == NULL) {
        return NULL;
    }
    int i,j,k;

    if(mat->numLines != mat2->numLines || mat->numColumns != mat2->numColumns){
        return NULL;
    } 
    mat_sum->numColumns=mat->numColumns;
    for(i=0;i<mat->numLines;i++){
        for(j=0;j<mat->numColumns;j++){
            k=i*mat->numColumns+j;
            mat_sum->data[k] = mat->data[k]+mat2->data[k];
        }
    }
    return mat_sum;
}

matrice* matrice_mult(matrice *mat, matrice*mat2){
    matrice*mat_mult;
    if(mat==NULL || mat2 == NULL) return NULL;
    if(mat->numColumns != mat2->numLines) return NULL;
    mat_mult= create_matrice(matrice_lines(mat),matrice_columns(mat2));

    int i,j,k=0,l=0;
    int var_aux1=0,var_aux2=0,var_aux3=0;

    for(i=0;i<mat->numLines;i++){
        for(j=0;j<mat2->numColumns;j++){
            for(l=0;l<mat->numColumns*mat->numLines;l=l+mat2->numColumns,var_aux3++){
                var_aux2+=(mat->data[var_aux3+k]*mat2->data[l+j]);
            }
            mat_mult->data[var_aux1] = var_aux2;
            var_aux1++;
            var_aux2=0;
            var_aux3=0;
        }
        k+=mat->numColumns;
    }
    
    return mat_mult;
}

matrice* prod_escalar_matrice(int l,matrice* mat){
    if(mat == NULL) return NULL;
    matrice*mat_prod_escalar;
    mat_prod_escalar=create_matrice(mat->numLines,mat->numColumns);
    int i,j,k;
    for(i=0;i<mat_prod_escalar->numLines;i++){
        for(j=0;j<mat_prod_escalar->numColumns;j++){
            k=i*mat_prod_escalar->numColumns+j;
            mat_prod_escalar->data[k]=mat->data[k]*l;
        }
    }
    
    return mat_prod_escalar;
}