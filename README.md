# algolympics-solutions

2020 Problems:
https://codeforces.com/group/fDKsZH3HKS/contest/270098

## Problem A: The Slowden Files
Equivalent to computing the edit distance. of two strings But edit distance computation takes O(N * M) time with DP where N and M are the lengths of the strings. Remove memoization from the DP to get an exhaustive search and add state K = difference so far to effectively prune. This is enough to AC.

## Problem B: C.U.P.S
Think of the problem in terms of flipping a fixed number of bits every time until you get all 1's. Order of the bits does not matter. What matters is how many 1's and how many 0's. So given a fixed number of 1's and 0's, determine if it's possible to get all 1's by just flipping m bits. Do a recursion with a visited array to effectively bruteforce all ways to flip the bits. It looks something like this.

f(ones, zeroes) = 

  // for all k, select ones and m - k zeroes and flip em
  f(ones - k + (m - k), zeroes + k + (m - k)
  
 Eventually, you find a sequence of flips needed. Just construct an answer given the sequence of flips.
 
## Problem L: Break the Pattern
Construct the polynomial given the roots r1, r2, r3, rn using naive multiplication: (x - r1) (x - r2) ... (x - rn).
Then just multiply different constants to generate more polynomials.

## Problem H: Maggie and Dana's Mass Supper
Equivalent to finding binary strings (F's and D's) corresponding to forward and downward movements, such that count(F) >= count(D) and count(F) - count(D) <= L - W. This is a variant of the Bertrand's Ballot Problem. The original variant satisifying only the first constraint has a closed form but satisfying the two constraint needs something more complex. The problem is also equivalent to finding the number of lattice paths that don't exceed the line y = x + 1 and y = x - L - W + 1. The best formula to compute the answer has O(n + m) terms and is explained in detail here: https://arxiv.org/pdf/1503.05930.pdf It also includes an more generalized formula for arbtirary starting positions and ending positions.

## Problem E: Floor of Many Doors
Dijkstra. Add another state which is the number of open doors. 

## Problem M: Thin Ice
Can be solved by combining zigzags per quadrant. A lot of if based on the parity of the coordinates and logic. Multiple cases can be combined and code can be reduced using tricks like flipping the board by swapping L and R or U and D character.

2019 and before:
https://algo2020.upacm.net/past-problems
