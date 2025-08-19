300. Longest Increasing Subsequence

바이나리 서치 LIS문제
int lengthOfLIS(vector<int>& nums) {
    vector<int> lis;
    for (int x : nums) {
        if (lis.empty() || x > lis.back()) {
            lis.push_back(x);
        } else {
            auto it = lower_bound(lis.begin(), lis.end(), x); // 처음으로 >= x
            *it = x;
        }
    }
    return (int)lis.size();
}
lower_bound쓰는게 더 쉬움 바퀴를 두 번 발명하지 말 것