/*
 * Problem: https://open.kattis.com/problems/programmingtutors
 * Author: Donald Dong
 *
 * Perform a binary search on the distance space and see if we can do a full
 * matching given the distance limit.
 *
 * Runtime: 0.03s
 */
#include <bits/stdc++.h>
using namespace std;

struct pt {
  int x, y;
};

int N; // The number of students/tutors
vector<pt> S, T; // Points for all students (S) and tutors (T)
vector<int> vis, match; // global vars for finding the augmenting path

bool reach(int s, int t, int k) {
  int dx = S[s].x - T[t].x, dy = S[s].y - T[t].y;
  return (dx < 0 ? -dx : dx) + (dy < 0 ? - dy : dy) <= k;
}

bool aug(int s, int k) { // finding an augmenting path for a student
  if (vis[s]) return false;
  vis[s] = true;
  for (int t = 0; t < N; ++t) { // try all tutors
    if (!reach(s, t, k)) continue; // dist > K
    if (match[t] < 0 || aug(match[t], k)) {
      match[t] = s;
      return true;
    }
  }
  return false;
}

bool possible(int k) { // No pair has distance greater than K
  int count = 0;
  match.assign(N, -1);
  for (int i = 0; i < N; ++i) {
    vis.assign(N, 0);
    count += aug(i, k);
  }
#ifdef DEBUG
  printf("%d is %s\n", k, count == N ? "good" : "bad");
#endif
  return count == N;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0); // Fast IO
  cin >> N;
  S.resize(N), T.resize(N); // Allocate memory for two vectors
  for (auto &p : S) cin >> p.x >> p.y; // Read in students
  for (auto &p : T) cin >> p.x >> p.y; // Read in tutors
  int lo = 0, hi = 4e8, mid; // max_diff = 2e8, 2 * max_diff
  while (lo < hi) {
    mid = (lo + hi) >> 1;
    if (possible(mid)) hi = mid;
    else lo = mid + 1;
  }
  printf("%d\n", lo);
  return 0;
}
