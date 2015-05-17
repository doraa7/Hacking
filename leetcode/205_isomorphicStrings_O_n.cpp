class Solution {
    vector<int> returnEncoding_(string s) {
        vector<int> encoding;
        unordered_map<char, int> charMap;
        int ctr=0;
        for_each(s.begin(), s.end(), [&ctr, &encoding, &charMap] (const char& ch) -> void {
            auto it = charMap.find(ch);
            if (it == charMap.end()) {
                charMap.insert(make_pair(ch, ctr));
                encoding.push_back(ctr);
                ctr++;
            } else {
                encoding.push_back(it->second);
            }
        });
        return encoding;
    }
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) return false;
        vector<int> encS = returnEncoding_(s);
        vector<int> encT = returnEncoding_(t);
        for (int i=0; i<s.length(); i++) {
            if (encS[i] != encT[i]) return false;
        }
        return true;
    }
};
