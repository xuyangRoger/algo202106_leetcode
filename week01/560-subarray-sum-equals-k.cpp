class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int len = nums.size();
        int cnt = 0, sum = 0;
        map<int, int> preSums;
        preSums.insert(pair(0,1));
        for(auto num : nums)
        {
            sum += num;
            if(preSums.find(sum-k) != preSums.end())
            {
                cnt += preSums[sum-k];
            }
            preSums[sum]++;
        }
        return cnt;

    }
};