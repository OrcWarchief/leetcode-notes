300. Longest Increasing Subsequence

���̳��� ��ġ LIS����
int lengthOfLIS(vector<int>& nums) {
    vector<int> lis;
    for (int x : nums) {
        if (lis.empty() || x > lis.back()) {
            lis.push_back(x);
        } else {
            auto it = lower_bound(lis.begin(), lis.end(), x); // ó������ >= x
            *it = x;
        }
    }
    return (int)lis.size();
}
lower_bound���°� �� ���� ������ �� �� �߸����� �� ��