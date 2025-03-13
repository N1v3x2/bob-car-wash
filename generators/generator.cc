#include <fstream>
#include <iostream>
#include <random>
#include <unistd.h>
using namespace std;
using param_type = uniform_int_distribution<>::param_type;

constexpr char nl = '\n';

int main(int argc, char *argv[]) {
    if (argc < 12) {
        cout << "Expected 11 arguments, got " << argc << endl;
        cout << "Usage: ./generator "
             << "-n <n> -N <n> "
             << "-m <m> -M <m> "
             << "-a <a> -A <a> "
             << "-t <t> -T <t> "
             << "-p <p> -P <p> "
             << "-o <output file>" << endl;
        return 0;
    }

    int n, N, m, M, a, A, t, T, p, P;
    string o;

    int opt;
    while ((opt = getopt(argc, argv, "n:N:m:M:a:A:t:T:p:P:o:")) != -1) {
        switch (opt) {
            case 'n': n = (int)pow(10, atoi(optarg)); break;
            case 'N': N = (int)pow(10, atoi(optarg)); break;
            case 'm': m = (int)pow(10, atoi(optarg)); break;
            case 'M': M = (int)pow(10, atoi(optarg)); break;
            case 'a': a = (int)pow(10, atoi(optarg)); break;
            case 'A': A = (int)pow(10, atoi(optarg)); break;
            case 't': t = (int)pow(10, atoi(optarg)); break;
            case 'T': T = (int)pow(10, atoi(optarg)); break;
            case 'p': p = (int)pow(10, atoi(optarg)); break;
            case 'P': P = (int)pow(10, atoi(optarg)); break;
            case 'o': o = optarg; break;
            case '?':
            default:
                cout << "Invalid argument" << endl;
                return 0;
        }
    }

    // Seed random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(n, N);

    fstream fs(o, ios_base::out);

    // n m
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
}
