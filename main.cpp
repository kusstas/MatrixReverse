#include <QCoreApplication>

#include <iostream>
#include <iomanip>

#include <memory>
#include <utility>
#include <algorithm>

size_t toLineIndex(size_t i, size_t j, size_t n)
{
    return i * n + j;
}

std::pair<size_t, size_t> toMatrixIndex(size_t i, size_t n)
{
    return std::make_pair(i / n, i % n);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    size_t m, n;

    std::cout << "Enter size of matrix (m, n): ";
    std::cin >> m >> n;

    size_t s = m * n;
    std::unique_ptr<int[]> matrix(new int[s]);

    std::iota(matrix.get(), matrix.get() + s, 1);

    size_t i0, j0;
    std::cout << "Enter position of submatrix (i0, j0): ";
    std::cin >> i0 >> j0;
    assert(i0 < m && j0 < n);

    size_t w, h;
    std::cout << "Enter size of submatrix (h, w): ";
    std::cin >> h >> w;
    assert(i0 + h <= m && j0 + w <= n && h > 0 && w > 0);

    size_t sizeSubmatrix = w * h;
    size_t lastIndexSubMatrix = sizeSubmatrix - 1;
    size_t nSwaps = sizeSubmatrix / 2;
    for (size_t i = 0; i < nSwaps; i++) {
        auto const& local1 = toMatrixIndex(i, w);
        auto const& local2 = toMatrixIndex(lastIndexSubMatrix - i, w);

        size_t i1 = toLineIndex(i0 + local1.first, j0 + local1.second, n);
        size_t i2 = toLineIndex(i0 + local2.first, j0 + local2.second, n);
        std::swap(matrix[i1], matrix[i2]);
    }

    // print matrix
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << std::setw(4) << matrix[toLineIndex(i, j, n)];
        }
        std::cout << std::endl;
    }

    return a.exec();
}
