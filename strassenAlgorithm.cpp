# include <iostream>
# include <vector>
# include <ctime>
# include <iomanip>
using namespace std;

//计算两个矩阵相加
vector<vector <int>> add(const vector<vector <int>> A,const vector<vector <int>> B){
    int m = A.size();
    int n = A[0].size();
    vector<vector<int>> C(m,vector<int>(n,0));

    for(int i =0 ; i < m ; i++){
        for(int j =0 ; j < n ; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    } 

   return C;
}

//计算两个矩阵相减
vector<vector <int>> subtract(const vector<vector <int>> A,const vector<vector <int>> B){
    int m = A.size();
    int n = A[0].size();
    vector<vector<int>> C(m,vector<int>(n,0));

    for(int i =0 ; i < m ; i++){
        for(int j =0 ; j < n ; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
   
   return C;

}

//若矩阵的行数或者列数为奇数，则扩容为偶数行偶数列
vector<vector<int>>padMatrix(const vector <vector<int>> &A){
    int m = A.size();
    int n = A[0].size();

    int newM = (m%2 == 0) ? m : m+1;
    int newN = (n%2 == 0) ? n : n+1;

    vector<vector<int>> paddedA(newM,vector<int>(newN,0));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            paddedA[i][j] = A[i][j];
        }
    }

    return paddedA;
}

//去除扩容的部分
vector<vector<int>> unpadMatrix(const vector <vector<int>> &A,int orignalM,int orignalN){
   vector<vector<int>> result(orignalM,vector<int>(orignalN,0));

   for(int i = 0; i < orignalM; i++){
        for(int j = 0; j < orignalN; j++){
            result[i][j] = A[i][j];
        }
   }

   return result;
}
   
//利用strassen算法计算两个矩阵的乘积
vector<vector<int>> strassen(vector<vector <int>> A,vector<vector <int>> B){
    int orignalM = A.size();
    int orignalN = A[0].size();
    int orignalK = B[0].size();

    //基准情况：如果矩阵规模为1x1x1，直接返回A*B
    if(orignalM == 1 && orignalN == 1 && orignalK == 1){
        return {{A[0][0]*B[0][0]}};
    }
    
    //如果是奇数行或者奇数列，扩容为偶数行偶数列
    A = padMatrix(A); 
    B = padMatrix(B);

    int m = A.size();
    int n = A[0].size();
    int k = B[0].size();
  
     vector<vector<int>> A11(m/2,vector<int>(n/2,0));
     vector<vector<int>> A12(m/2,vector<int>(n/2,0));
     vector<vector<int>> A21(m/2,vector<int>(n/2,0));
     vector<vector<int>> A22(m/2,vector<int>(n/2,0));

     vector<vector<int>> B11(n/2,vector<int>(k/2,0));
     vector<vector<int>> B12(n/2,vector<int>(k/2,0));
     vector<vector<int>> B21(n/2,vector<int>(k/2,0));
     vector<vector<int>> B22(n/2,vector<int>(k/2,0));

     int horizontalOffsetOfA = n/2;   //A的横向偏移
     int verticalOffsetOfA = m/2;     //A的纵向偏移
     int horizontalOffsetOfB = k/2;   //B的横向偏移
     int verticalOffsetOfB = n/2;     //B的纵向偏移

    //分割,把A和B分别分成四个子矩阵
     for(int i = 0; i < m /2 ; i++){
        for(int j = 0 ; j < n /2 ; j++){
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+horizontalOffsetOfA];
            A21[i][j] = A[i+verticalOffsetOfA][j];
            A22[i][j] = A[i+verticalOffsetOfA][j+horizontalOffsetOfA];
        }
     }

     for(int i = 0; i < n /2 ; i++){
        for(int j = 0 ; j < k /2 ; j++){
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+horizontalOffsetOfB];
            B21[i][j] = B[i+verticalOffsetOfB][j];
            B22[i][j] = B[i+verticalOffsetOfB][j+horizontalOffsetOfB];
        }
     }

     //计算7个子矩阵的乘积

    auto P1 = strassen(add(A11,A22),add(B11,B22));
    auto P2 = strassen(add(A21,A22),B11);
    auto P3 = strassen(A11,subtract(B12,B22));
    auto P4 = strassen(A22,subtract(B21,B11));
    auto P5 = strassen(add(A11,A12),B22);
    auto P6 = strassen(subtract(A21,A11),add(B11,B12));
    auto P7 = strassen(subtract(A12,A22),add(B21,B22));

    //计算C矩阵的四个子矩阵

     auto C12 = add(P3,P5);
     auto C21 = add(P2,P4);
     auto C11 = add(subtract(add(P1,P4),P5),P7);
     auto C22 = add(subtract(add(P1,P3),P2),P6);

    //合并C矩阵的四个子矩阵

    vector<vector<int>> C(m,vector<int>(k,0));
    int horizontalOffsetOfC = k/2;   //C的横向偏移
    int verticalOffsetOfC = m/2;     //C的纵向偏移

    for(int i = 0; i < m /2 ; i++){
        for(int j = 0 ; j < k /2 ; j++){
            C[i][j] = C11[i][j];
            C[i][j+horizontalOffsetOfC] = C12[i][j];
            C[i+verticalOffsetOfC][j] = C21[i][j];
            C[i+verticalOffsetOfC][j+horizontalOffsetOfC] = C22[i][j];
        }
    }

    //去除扩容的部分
    C = unpadMatrix(C,orignalM,orignalK);

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
    cout << endl;  // 换行

    vector<vector<int>> A(m, vector<int>(n, 0));
    vector<vector<int>> B(n, vector<int>(k, 0));

    srand(time(0));

    // 生成矩阵 A
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = rand() % 10;
        }
    }        

    //打印矩阵A        
    cout << "The matrix A is: " << endl;
    printMatrix(A);

    // 生成矩阵 B
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            B[i][j] = rand() % 10;      
        }
    }  

   //打印矩阵B
    cout << "The matrix B is: " << endl;
    printMatrix(B);

    // 进行矩阵乘法 
    vector<vector<int>> C = strassen(A, B);

    // 打印矩阵C
    cout << "The result of strassen matrix multiplication is: " << endl;
    printMatrix(C);
    
    return 0;           
}
