#pragma once

#include <ostream>
#include <vector>
#include <set>
#include <stdexcept>

template<typename T>
class DenseMatrix{
public:
    using elm_t = T;
    using idx_t = std::size_t;

private:

    std::vector<T> _data;
    idx_t _rowSize, _colSize;

    template<typename EL>
    friend std::vector<EL> operator*(const DenseMatrix<EL> &A, const std::vector<EL> &b);
public:

    DenseMatrix(const idx_t &h, const idx_t& w)
    {
        _rowSize = h;
        _colSize = w;
        _data.resize(h * w);
    }

    DenseMatrix(const idx_t &h, const idx_t& w, const std::vector<T>& data)
    {
        _rowSize = h;
        _colSize = w;
        _data.resize(h * w);
        for (int i = 0; i < data.size(); i++)
        {
            _data[i] = data.at(i);
        }
    }

    DenseMatrix(const idx_t &h, const idx_t& w, T fill)
    {
        _rowSize = h;
        _colSize = w;
        _data.resize(h * w);
        for (int i = 0; i < h * w; i++)
            _data[i] = fill;
    }


    elm_t& operator()(const idx_t& i, const idx_t& j)
    {
        return _data[i * _colSize + j];
    }

    const elm_t& operator()(const idx_t& i, const idx_t& j) const
    {
        return _data[i * _colSize + j];
    }

    void operator-=(const DenseMatrix<elm_t> &A){
        for(int i = 0; i < _data.size(); i++)
        {
            _data[i] -= A._data[i];
        }
    }
    
    DenseMatrix<T> inverse()
    {
        T temp;
        auto N = _colSize;

        DenseMatrix<T> E(N, N);
        DenseMatrix<T> ret = *this;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                E(i,j) = 0.0;

                if (i == j)
                    E(i, j) = 1.0;
            }

        for (int k = 0; k < N; k++)
        {
            temp = ret(k,k);

            for (int j = 0; j < N; j++)
            {
                ret(k, j) /= temp;
                E(k, j) /= temp;
            }

            for (int i = k + 1; i < N; i++)
            {
                temp = ret(i, k);

                for (int j = 0; j < N; j++)
                {
                    ret(i, j) -= ret(k, j) * temp;
                    E(i, j) -= E(k, j) * temp;
                }
            }
        }

        for (int k = N - 1; k > 0; k--)
        {
            for (int i = k - 1; i >= 0; i--)
            {
                temp = ret(i, k);

                for (int j = 0; j < N; j++)
                {
                    ret(i, j) -= ret(k, j) * temp;
                    E(i, j) -= E(k, j) * temp;
                }
            }
        }

        return E;
    }

    [[nodiscard]] const idx_t& rowSize() const
    {
        return _rowSize;
    }

    [[nodiscard]] const idx_t& colSize() const
    {
        return _colSize;
    }

    std::vector<T> column(unsigned i) const
    {
        std::vector<T> col(_rowSize);

        for (unsigned j = 0; j < _rowSize; j++)
            col[j] = _data[j * _colSize + i];

        return col;
    }

    void swap(const idx_t& first, const idx_t& second)
    {
        if (first == second)
        {
            throw std::exception();
        }

        if (first > _rowSize || second > _rowSize)
        {
            throw std::exception();
        }

        std::vector<T> tmp(_colSize);

        for (int i = 0; i < _colSize; ++i)
        {
            tmp[i] = _data[(first - 1) * _colSize + i];
        }

        for (int i = 0; i < _colSize; ++i)
        {
            _data[(first - 1) * _colSize + i] = _data[(second - 1) * _colSize + i];
        }

        for (int i = 0; i < _colSize; ++i)
        {
            _data[(second - 1) * _colSize + i] = tmp[i];
        }

    }

    DenseMatrix<T> transpose() {
        DenseMatrix<T> tr(_colSize, _rowSize);
        for (size_t i = 0; i < _rowSize; ++i) {
            for (size_t j = 0; j < _colSize; ++j) {
                tr(j, i) = _data[i * _colSize + j];
            }
        }
        return tr;
    }


    void deleteLastRow()
    {
        _data.erase(_data.end() - _colSize, _data.end());
        _rowSize--;
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const DenseMatrix<T> &A)
{
    for (int i = 0; i < A.rowSize(); ++i)
    {
        for (int j = 0; j < A.colSize(); ++j)
            os << A(i, j) << " ";
        os << std::endl;
    }

    return os;
}

template <typename T>
DenseMatrix<T> operator*(const DenseMatrix<T> &A, const DenseMatrix<T> &B) {
    DenseMatrix<T> result(A.rowSize(), B.colSize(), 0);

    for (int i = 0; i < A.rowSize(); i++) {
        for (int j = 0; j < B.colSize(); j++) {
            for (int k = 0; k < A.colSize(); k++)
                result(i, j) += A(i, k) * B(k, j);
        }
    }

    return result;
}

template <typename T>
std::vector<T> operator*(const DenseMatrix<T> &A, const std::vector<T> &b) {
    auto result = A;
    result = result * DenseMatrix<T>(b.size(), 1, b);
    return result._data;
}

template <typename T>
DenseMatrix<T> operator*(const T &a, const DenseMatrix<T> &A) {
    DenseMatrix<T> result(A.rowSize(), A.colSize(), 0);

    for (int i = 0; i < A.rowSize(); i++) {
        for (int j = 0; j < A.colSize(); j++) {
            result(i, j) = A(i, j) * a;
        }
    }

    return result;
}