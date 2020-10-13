// Matriz super-legal

#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;
#define endl "\n";
#define MAXLC 1010

int l, c;
int a[MAXLC][MAXLC];
int b[MAXLC][MAXLC];

int hist(int x) {
  int *linha = b[x];
  stack<int> s;

  int area = 0, res=0;
  int topo;
  
  int i = 0;
  while (i < c) {
    if (s.empty() || linha[s.top()] <= linha[i])
      s.push(i++);
    else {
      topo = linha[s.top()]; s.pop();
      area = s.empty()? (topo+1) * (i+1) : (topo+1) * (i - s.top());
      res = max(res, area);
    }
  }

  while (!s.empty()) {
    topo = linha[s.top()]; s.pop();
    area = s.empty()? (topo+1) * (i+1) : (topo+1) * (i - s.top());
    res = max(res, area);
  }

  return res;
}

int solve() {
  int res = hist(1);
  
  for (int i = 2; i < l; i++)
    for (int j = 1; j < c; j++) {
      if (b[i][j]) b[i][j] += b[i-1][j];
      res = max(res, hist(i));
    }

  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  cin >> l >> c;
  for (int i = 1; i <= l; i++)
    for (int j = 1; j <= c; j++)
      cin >> a[i][j];

  for (int i = 1; i < l; i++)
    for (int j = 1; j < c; j++)
      b[i][j] = a[i][j] + a[i+1][j+1] <= a[i+1][j] + a[i][j+1];

  cout << solve() << endl;
}
