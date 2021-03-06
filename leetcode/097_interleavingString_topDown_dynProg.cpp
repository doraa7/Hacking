// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Using top down dynamic programming for a change!
class Solution {
    //dynamic programming cache
    unordered_map<unsigned long long, bool> cache;

    //make a hash that uniquely defines the 3 strings
    unsigned long long makeHash(string s1, string s2, string s3) {
        return (( ((unsigned long long)(s1.length())) << 32) | 
                ( ((unsigned long long)(s2.length())) << 16) | 
                ( ((unsigned long long)(s3.length())) ));}

    //enter the memoized results in the cache
    void setCache(string s1, string s2, string s3, bool val) {cache.insert(make_pair(makeHash(s1, s2, s3), val));}
public:
    bool isInterleave(string s1, string s2, string s3) {
        //first check the cache, if found, just return it
        auto it = cache.find(makeHash(s1, s2, s3));
        if (it != cache.end()) return it->second;

        //now check the strings for match
        int s1p=0, s2p=0, s3p=0;
        for (;s3p<s3.length(); s3p++ ) {
	    //if both s1p and s2p characters match s3p character, then I have to 
	    //recurse on both possibilities
            if (s1p < s1.length() && s2p < s2.length() && s1[s1p] == s2[s2p] && s1[s1p] == s3[s3p]) {
                bool ret = (isInterleave(s1.substr(s1p+1), s2.substr(s2p), s3.substr(s3p+1)) ||
                           isInterleave(s1.substr(s1p), s2.substr(s2p+1), s3.substr(s3p+1)));
                setCache(s1, s2, s3, ret);
                return ret;
            } else if (s1p < s1.length() && s1[s1p] == s3[s3p]){
                //only s1p matched, therefore just consume it
                s1p++;
            } else if (s2p < s2.length() && s2[s2p] == s3[s3p]) {
                //only s2p matched, therefore just consume it
                s2p++;
            } else {
                //neither match, this is not going to match
                bool ret = false;
                setCache(s1, s2, s3, ret);
                return ret;
            }
        }
        //in the end, if I consumed all of all strings, then matching!
        bool ret = (s1p == s1.length() && s2p == s2.length() && s3p == s3.length());
        setCache(s1, s2, s3, ret);
        return ret;
    }
};
