#include <iostream>;

template<class T>
class mat {
    int row, col;
    T **data;
public:
    mat(int r, int c) {
        row = r;
        col = c;
        data = new T *[row];
        for (int i = 0; i < row; i++) {
            data[i] = new T[col];
        }
    }

    mat(mat *b) {
        row = b->row;
        col = b->col;
        data = new T *[row];
        for (int i = 0; i < row; i++) {
            data[i] = new T[col];
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[i][j] = b->data[i][j];
            }
        }

    }

    mat(mat const &b) {
        row = b.row;
        col = b.col;
        data = new T *[row];
        for (int i = 0; i < row; i++) {
            data[i] = new T[col];
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[i][j] = b.data[i][j];
            }
        }
    }

    ~mat() {
        for (int i = 0; i < row; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    bool  set(int r, int c, T value) {
        data[r][c] = value;
        return true;
    }

    T get(int r, int c) {
        return &data[r][c];
    }

    bool set_all(T value) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                data[i][j] = value;
            }
        }
        return true;
    }

    mat *operator*(T dot) {
        if (this->col != dot.rol) {
            std::cerr << "Error: row != col" << std::endl;
            return NULL;
        }
        mat *result = new mat(this->row, dot.col);
        result->set_all(0);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < dot.col; j++) {
                for (int k = 0; k < this->col; k++) {
                    result->data[i][j] += this->data[i][k] * dot.data[k][j];
                }
            }
        }
        return result;
    }

    mat *operator+(T add) {
        if (this->row != add.row || this->col != add.col) {
            std::cerr << "Error: row != col" << std::endl;
            return NULL;
        }
        mat *result = new mat(this->row, this->col);
        result->set_all(0);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                result->data[i][j] = this->data[i][j] + add.data[i][j];
            }
        }
        return result;
    }

    T *get_row(int r) {
        return &data[r];
    }

    T *get_col(int c) {
        T *result = new T[row];
        for (int i = 0; i < row; i++) {
            result[i] = &data[i][c];
        }


    }
};
