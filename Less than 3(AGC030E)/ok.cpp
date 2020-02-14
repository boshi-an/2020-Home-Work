#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int N;

char S[MAX_N], T[MAX_N];
vector<int> digestS, digestT;
int cnt2S, cnt2T;
int ans = INT_MAX;

vector<int> getDigest(char A[]) {
    vector<int> digest;
    int curr = 1;
    for (int i = 2; i <= N; i++) {
        if (A[i] != A[i - 1]) {
            digest.push_back(curr);
            curr = 1;
        } else {
            curr++;
        }
    }
    digest.push_back(curr);
    return digest;
}

void init() {
    scanf("%d", &N);
    scanf("%s", S + 1);
    scanf("%s", T + 1);
    if (N <= 2) {
        int ans = 0;
        for (int i = 1; i <= N; i++)
            if (S[i] != T[i]) ans++;
        printf("%d\n", ans);
        exit(0);
    }
    digestS = getDigest(S);
    digestT = getDigest(T);
    for (int i : digestS)
        if (i == 2) cnt2S++;
    for (int i : digestT)
        if (i == 2) cnt2T++;
}

void gather(vector<int> &digest, int cnt, int target, int &res) {
    int obst = 0;
    for (int i = 0, j = 0; i < digest.size() && cnt; i++) {
        if (digest[i] == target) {
            res += obst;
            swap(digest[j++], digest[i]);
            cnt--;
        } else obst++;
    }
    if (cnt) res = -1;
}

void convert(vector<int> &digest, int delta, int &res) {
    if (delta > 0) {
        gather(digest, 2 * delta, 1, res);
        if (res == -1) return;
        digest.erase(digest.begin(), digest.begin() + 2 * delta);
        digest.insert(digest.begin(), delta, 2);
        res += delta * (delta - 1) + delta;
    }
    if (delta < 0) {
        gather(digest, -delta, 2, res);
        if (res == -1) return;
        digest.erase(digest.begin(), digest.begin() + (-delta));
        digest.insert(digest.begin(), -delta * 2, 1);
        res += (-delta) * (-delta - 1) + (-delta);
    }
}

vector<int> get_2pos(const vector<int> &digest) {
    vector<int> res;
    for (int i = 0; i < digest.size(); i++) {
        if (digest[i] == 2) res.push_back(i);
    }
    return res;
}

void solve(int delta_l, int delta_r) {
    int res = 0;
    vector<int> digest = digestS;
    convert(digest, delta_l, res);
    if (res == -1) return;
    reverse(digest.begin(), digest.end());
    convert(digest, delta_r, res);
    if (res == -1) return;
    reverse(digest.begin(), digest.end());
    vector<int> pos_curr = get_2pos(digest);
    vector<int> pos_target = get_2pos(digestT);
    for (int i = 0; i < pos_curr.size(); i++)
        res += abs(pos_curr[i] - pos_target[i]);
    ans = min(ans, res);
}

int main() {
    init();
    for (int i = -N / 2; i <= N / 2; i++) {
        if ((i & 1) ^ (S[1] == T[1])) {
            solve(i, cnt2T - cnt2S - i);
        }
    }
    printf("%d\n", ans);
}
