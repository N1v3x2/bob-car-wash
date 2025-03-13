from sys import exit
import re

MAX_N, MAX_M = 1e3, 1e3
MAX_A, MAX_T, MAX_P = 1e8, 1e3, 1e3

line = input()
assert re.match(r"[1-9]\d* [1-9]\d*", line), f"{line} only contain positive integers"

(n, m) = map(int, line.split())
assert 1 <= n <= MAX_N, f"{n} be in the range [1, {MAX_N}]"
assert 1 <= m <= MAX_M, f"{m} be in the range [1, {MAX_M}]"

line = input().split()
assert len(line) == n, f"Second line must contain {n} integers"
for num in line:
    assert re.match(r"0|([1-9]\d*)", num), "Second line must only contain integers"
    assert 0 <= int(num) <= MAX_A, f"{num} must be in the range [0, {MAX_A}]"

line = input().split()
assert len(line) == n, f"Third line must contain {n} integers"
for num in line:
    assert re.match(r"0|([1-9]\d*)", num), "Third line must only contain integers"
    assert 0 <= int(num) <= MAX_T, f"{num} must be in the range [0, {MAX_T}]"

line = input().split()
assert len(line) == n, f"Fourth line must contain {n} integers"
for num in line:
    assert re.match(r"0|([1-9]\d*)", num), "Foruth line must only contain integers"
    assert 0 <= int(num) <= MAX_P, f"{num} must be in the range [0, {MAX_P}]"

try:
    input()
    exit(1)
except EOFError:
    exit(42)
