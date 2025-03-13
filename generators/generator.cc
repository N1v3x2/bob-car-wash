#include <fstream>
#include <iostream>
#include <random>
#include <unistd.h>
using namespace std;
using param_type = uniform_int_distribution<>::param_type;

constexpr char nl = '\n';

int c;
const string TEST_DIR = "../data/secret/";

int main(int argc, char *argv[]) {
    // Seed random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib;

    int n, N, m, M, a, A, t, T, p, P;
    string o;

    auto genTestCase = [&]() {
        fstream fs(o, ios_base::out);

        // n m
        distrib.param(param_type{ n, N });
        int x = distrib(gen);
        distrib.param(param_type{ m, M });
        int y = distrib(gen);
        fs << x << ' ' << y << nl;

        auto genRow = [&](int l, int r) {
            distrib.param(param_type{ l, r });
            for (int i = 0; i < x; ++i) {
                fs << distrib(gen);
                if (i < x - 1) fs << ' ';
            }
            fs << nl;
        };

        // a_i
        genRow(a, A);

        // t_i
        genRow(t, T);

        // p_i
        genRow(p, P);
    };

    // Case 5: Sum of all valid a_i results in 32-bit integer overflow
    N = 1e3, n = N - 100;
    M = 1e3, m = M - 100;
    A = 1e8, a = A - 10000;
    T = t = 0;
    P = 1e3, p = P - 100;
    o = TEST_DIR + "5.in";
    genTestCase();

    // Case 6: randomized small test case
    N = 100, n = 1;
    M = 100, m = 1;
    A = T = P = 100, a = t = p = 0;
    o = TEST_DIR + "6.in";
    genTestCase();

    for (c = 0; c < 32; ++c) {
        N = ((c >> 4) & 1) ? 10 : 1e3; n = N / 10 + 1;
        M = ((c >> 3) & 1) ? 10 : 1e3; m = M / 10 + 1;
        A = ((c >> 2) & 1) ? 9 : 1e8; a = A / 10;
        T = ((c >> 1) & 1) ? 9 : 1e3; t = T / 10;
        P = (c & 1) ? 9 : 1e3; p = P / 10;
        o = "../data/secret/" + to_string(7 + c) + ".in";
        genTestCase();
    }
}
