class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        vector<string> ans;
        unordered_map<string, int> cnt;
        for(auto& words: cpdomains)
        {
            int index = words.find(' ');
            int num = stoi(words.substr(0, index));
            string dmName = words.substr(index+1);

            while(index > 0)
            {
                cnt[dmName] += num;
                index = dmName.find('.');
                dmName = dmName.substr(index+1);
            }
            
        }

        for(auto& it: cnt)
        {
            ans.push_back(to_string(it.second) + " " + it.first);
        }
        return ans;
    }
};