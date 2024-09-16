#include <iostream>
#include <vector>
#include <fstream>
#define SIZE 9

class Sudoku {
    private:
    bool valid;

    bool has_dublicate(const std::vector<std::vector<int>> &matrix, int i, int j) const {
        for(int row = 0; row < 9; row++) if(row != j && matrix[i][j] == matrix[i][row] && matrix[i][j] > 0 && matrix[i][row] > 0) return true;
        //Verify row dublicates
        for(int column = 0; column < 9; column++) if(column != i && matrix[i][j] ==matrix[column][j] && matrix[i][j] > 0 && matrix[column][j] > 0)return true;
        //Verify box dublicates
        int krow = i/3, kcolumn = j/3;

        for(int row = 3*krow; row < krow*3 + 3; row++){
            for(int column = 3*kcolumn; column < kcolumn*3 + 3; column++){
                if(column!=j && row!=i && matrix[i][j] == matrix[row][column] && matrix[i][j] > 0 && matrix[row][column] > 0) return true;
            }
        }
        return false;
    }
    public:
    std::vector<std::vector<int>> matrix;
    

    
    bool get_valid() { return valid; };
    void set_valid(bool value) { valid = value; };
    Sudoku(const std::string& name);
    bool is_valid() const { 
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(has_dublicate(matrix, i, j)) return false;
            }
        }
        return true;
    };
    

    
    friend std::ifstream & operator>>(std::ifstream&, Sudoku&);
    friend std::ostream & operator<<(std::ostream&, Sudoku&);
    friend std::ofstream & operator<<(std::ofstream&, Sudoku&);
};
void solve_a_puzzle();

int main(){
    char ch;
    while(1){
        std::cout << "Want to solve(y/n): ";
        std::cin >> ch;
        if(ch == 'n' || ch == 'N') {
            std::cout << "Exiting..." << std::endl;
            exit(0);
        } else if(ch == 'y' || ch == 'Y') {
            solve_a_puzzle();
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
            continue;
        }
    }
    return 0;
}

Sudoku::Sudoku(const std::string& name): matrix(SIZE, std::vector<int>(SIZE, 0)){
    std::ifstream inputFile(name);

    try {
        if(!inputFile.is_open())
            throw std::string("Cannot open input file");

        inputFile >> *this;
        this->set_valid(true);
        inputFile.close();
    } catch (const std::string& message){
        std::cerr << "Error: " << message << std::endl;
        this->set_valid(false);
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
void solve_a_puzzle(){
    std::cout << "Enter filename: " << std::endl;
    std::string filename;
    std::cin >> filename;

    Sudoku sudoku(filename);

    if(!sudoku.get_valid()) return;

    if(!sudoku.is_valid()) {
        std::cout << "The given Sudoku puzzle is not valid." << std::endl;
        return;
    }

    std::cout << "Original Sudoku puzzle:" << std::endl;
    std::cout << sudoku << std::endl;

    std::cout << "Solving..." << std::endl;

    std::cout << "Solved Sudoku puzzle:" << std::endl;
    std::cout << sudoku << std::endl;
}