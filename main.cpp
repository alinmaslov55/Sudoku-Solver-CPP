#include <iostream>
#include <vector>
#include <fstream>
#define SIZE 9

class Sudoku {
    public:
    std::vector<std::vector<int>> matrix;
    Sudoku(const std::string& name);
    friend std::ifstream & operator>>(std::ifstream&, Sudoku&);
    friend std::ostream & operator<<(std::ostream&, Sudoku&);
    friend std::ofstream & operator<<(std::ofstream&, Sudoku&);
};


int main(){

    return 0;
}

Sudoku::Sudoku(const std::string& name): matrix(SIZE, std::vector<int>(SIZE, 0)){
    std::ifstream inputFile(name);

    try {
        if(!inputFile.is_open())
            throw std::string("Cannot open input file");

        inputFile >> *this;
        inputFile.close();
    } catch (const std::string& message){
        std::cerr << "Error: " << message << std::endl;
        exit(1);   
    }
}
std::ifstream & operator>>(std::ifstream& filein, Sudoku& sudoku){
    int digit;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            filein >> sudoku.matrix[i][j];
        }
    }
    return filein;
}
std::ostream & operator<<(std::ostream& out, Sudoku& sudoku){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            out << sudoku.matrix[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}
std::ofstream & operator<<(std::ofstream& out, Sudoku& sudoku){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            out << sudoku.matrix[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}