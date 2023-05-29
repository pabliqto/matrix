#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

int get(int cols, int row, int col, const int *A) {
    int n = cols * row + col;
    return A[n];

}

void set(int cols, int row, int col, int *A, int value) {
    int n = cols * row + col;
    A[n] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {
    for(int i=0;i<rowsA;i++){
        for(int j=0;j<colsB;j++){
            int val=0;
            for(int k=0;k<colsA;k++){
                val += get(colsA,i,k,A) * get(colsB,k,j,B);
            }
            set(colsB,i,j,AB,val);
        }
    }
}

void read_mat(int rows, int cols, int *t) {
    int n = rows*cols;
    for(int i=0;i<n;i++){
        scanf("%d",&t[i]);
    }
}

void print_mat(int rows, int cols, int *t) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i * cols + j;
            printf("%d ", t[index]);
        }
        printf("\n");
    }
}

int read_char_lines(char *array[]) {
    char tab[BUF_SIZE];
    int i=0;
    while (fgets(tab, BUF_SIZE, stdin) != NULL){
        array[i] = malloc((strlen(tab) + 1) * sizeof(char));
        strcpy(array[i], tab);
        i++;
    }
    return i;
}

void write_char_line(char *array[], int n) {
    printf("%s",array[n]);
}

void delete_lines(char *array[]) {
    int i = 0;
    while (array[i] != NULL) {
        free(array[i]);
        i++;
    }
}

int read_int_lines_cont(int *ptr_array[]) {
    int n=0,i=0;
    char ch[BUF_SIZE];
    char* x;
    const char del[] = " ";
    while (fgets(ch, BUF_SIZE, stdin) != NULL) {
        x = strtok(ch, del);
        ptr_array[n][i] = atoi(x);
        while(x != NULL){
            i++;
            x = strtok(NULL, del);
            if(x!=NULL){
                ptr_array[n][i] = atoi(x);
            }
        }
        n++;
        ptr_array[n] = &ptr_array[n-1][i];
        i=0;

    }
    return n;
}

void write_int_line_cont(int *ptr_array[], int n) {
    int i=0;
    while (&ptr_array[n][i]!=&ptr_array[n+1][0]){
        printf("%d ",ptr_array[n][i]);
        i++;
    }
}

typedef struct {
	int *values;
	int len;
	double average;
} line_type;

void sort_by_average(line_type lines_array[], int line_count);

int read_int_lines(line_type lines_array[]) {
    int n=0,i=0;
    double avg=0;
    char ch[BUF_SIZE];
    char* x;
    int num[TAB_SIZE];
    const char del[] = " ";
    while (fgets(ch, BUF_SIZE, stdin) != NULL) {
        x = strtok(ch, del);
        num[i] = atoi(x);
        avg+=num[i];
        while(x != NULL){
            i++;
            x = strtok(NULL, del);
            if(x!=NULL){
                num[i] = atoi(x);
                avg+=num[i];
            }
        }
        avg /= i;
        lines_array[n].values = malloc((i+1)*sizeof(int));
        memcpy(lines_array[n].values,num,sizeof(int)*i);
        lines_array[n].average = avg;
        lines_array[n].len = i;
        n++;
        i=0;
        avg=0;
    }
    sort_by_average(lines_array, n);
    return n;
}

void write_int_line(line_type lines_array[], int n) {
    int l = lines_array[n].len;
    for(int i=0;i<l;i++){
        printf("%d ",lines_array[n].values[i]);
    }
    printf("\n%.2f",lines_array[n].average);
}

void delete_int_lines(line_type array[], int line_count) {
    int i = 0;
    while (i<line_count) {
        free(array[i].values);
        i++;
    }
}

int cmp (const void *a, const void *b) {
    const line_type *fa = (const line_type *) a;
    const line_type *fb = (const line_type *) b;
    return fa->average - fb->average;
}

void sort_by_average(line_type lines_array[], int line_count) {
    qsort(lines_array, line_count, sizeof(line_type),&cmp);
}

typedef struct {
	int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
    for(int i=0;i<n_triplets;i++){
        scanf("%d %d %d",&triplet_array[i].r, &triplet_array[i].c, &triplet_array[i].v);
    }
    return n_triplets;
}

int cmp_triplets(const void *t1, const void *t2) {
    const triplet *ta = (const triplet *) t1;
    const triplet *tb = (const triplet *) t2;
    if(ta->r != tb->r){return ta->r - tb->r;}
    else{return ta->c - tb->c;}
}

void make_CSR(triplet *triplet_array, int n_triplets, int rows, int *V, int *C, int *R) {
    int temp=0,j=0, el=0;
    qsort(triplet_array,n_triplets,sizeof(triplet),&cmp_triplets);
    for(int i=0;i<n_triplets;i++){
        V[i] = triplet_array[i].v;
        C[i] = triplet_array[i].c;
    }
    for(int row=0;row<rows;row++){
        R[row]=el;
        while(row==triplet_array[j].r){
            temp++;
            j++;
        }
        el = temp;
    }
    R[rows] = n_triplets;
}

void multiply_by_vector(int rows, const int *V, const int *C, const int *R, const int *x, int *y) {
    for(int i=0;i<rows;i++){
        y[i] = 0;
        for(int j=R[i];j<R[i+1];j++){
            y[i] += V[j] * x[C[j]];
        }
    }
}

void read_vector(int *v, int n) {
    for(int i=0;i<n;i++){
        scanf("%d",&v[i]);
    }
}

void write_vector(int *v, int n) {
    for(int i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}

int read_int() {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, lines_counter, rowsA, colsA, rowsB, colsB;
	int rows, cols, n_triplets;
	char *char_lines_array[TAB_SIZE] = { NULL };
	int continuous_array[TAB_SIZE];
	int *ptr_array[TAB_SIZE];
	triplet triplet_array[TAB_SIZE];
	int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
	int x[TAB_SIZE], y[TAB_SIZE];
	line_type int_lines_array[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d", &rowsA, &colsA);
			read_mat(rowsA, colsA, A);
			scanf("%d %d", &rowsB, &colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA, colsA, colsB, A, B, AB);
			print_mat(rowsA, colsB, AB);
			break;
		case 2:
			n = read_int() - 1; // we count from 1 :)
			ptr_array[0] = continuous_array;
			read_int_lines_cont(ptr_array);
			write_int_line_cont(ptr_array, n);
			break;
		case 3:
			n = read_int() - 1;
			read_char_lines(char_lines_array);
			write_char_line(char_lines_array, n);
			delete_lines(char_lines_array);
			break;
		case 4:
			n = read_int() - 1;
			lines_counter = read_int_lines(int_lines_array);
			sort_by_average(int_lines_array, lines_counter);
			write_int_line(int_lines_array, n);
			delete_int_lines(int_lines_array, lines_counter);
			break;
		case 5:
			scanf("%d %d %d", &rows, &cols, &n_triplets);
			n_triplets = read_sparse(triplet_array, n_triplets);
			read_vector(x, cols);
			make_CSR(triplet_array, n_triplets, rows, V, C, R);
			multiply_by_vector(rows, V, C, R, x, y);
			write_vector(V, n_triplets);
			write_vector(C, n_triplets);
			write_vector(R, rows + 1);
			write_vector(y, rows);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}