#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

vector<vector<int>> normalMatrixMul(vector<vector<int>> &A, vector<vector<int>> &B){
    int m = A.size();        // A 的行数
    int n = A[0].size();     // A 的列数 (B 的行数)
    int k = B[0].size();     // B 的列数
    vector<vector<int>> C(m, vector<int>(k, 0)); // 初始化结果矩阵

    // 进行矩阵乘法
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            int temp = 0;
            for(int q = 0; q < n; q++){
                temp += A[i][q] * B[q][j];   
            }  
            C[i][j] = temp;
        }
    }

    return C;
}


// 打印矩阵,并且有固定的长度
void printMatrix(const vector<vector<int>>& matrix){
    for(const auto& row : matrix){
        for(const auto& element :row){
            cout << setw(3) << element << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    int m, n, k;

    cout << "Please input the dimensions of the matrices: " << endl;
    cin >> m >> n >> k; // 输入矩阵的维度
    cout << endl;

    vector<vector<int>> A(m, vector<int>(n, 0));
    vector<vector<int>> B(n, vector<int>(k, 0));

    srand(time(0));

    // 生成矩阵 A
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = rand() % 10;
        }
    }        
   
    // 打印矩阵 A
    cout << "The matrix A is: " << endl;
    printMatrix(A);

    // 生成矩阵 B
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            B[i][j] = rand() % 10;
        }
    }  

   // 打印矩阵 B
    cout << "The matrix B is: " << endl;
    printMatrix(B);

    // 进行矩阵乘法
    auto C = normalMatrixMul(A, B);

    // 输出结果矩阵 C
    cout << "The result of normal matrix multiplication is: " << endl;
    printMatrix(C);

    return 0;           
}
