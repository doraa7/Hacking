// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_map>
using namespace std;

// The following solution is from my leetcode solution to the same problem
class Solution {
private:
    typedef pair<int, int> t_IndRat; //(index, rating) pair

    int candyAllotments(vector<int>& ratings, vector<t_IndRat>& sIndRats) {
        unordered_map<int, int> candies; // index -> candies
        
        //lowest rating guy has to get 1
        candies.insert(make_pair(sIndRats[0].first, 1)); 
        int totalCandies = 1;
        
        //handle others
        for (unsigned int i=1; i<sIndRats.size(); i++) {
            // start off assuming this
            int candiesForMe = 1;     
            
            //these are my neighbors
            int leftNeighborInd  = sIndRats[i].first - 1;
            int rightNeighborInd = sIndRats[i].first + 1;
            
            //see if neighbors were already assigned candies
            auto lit = candies.find(leftNeighborInd);
            auto rit = candies.find(rightNeighborInd);
            int candiesLeftNeighbor  = (sIndRats[i].first == 0                   || (lit == candies.end())) ? 0 : lit->second;
            int candiesRightNeighbor = (sIndRats[i].first == (sIndRats.size()-1) || (rit == candies.end())) ? 0 : rit->second;
            
            //gets ratings of my neighbors
            int ratsLeftNeighbor  = (sIndRats[i].first == 0)                   ? std::numeric_limits<int>::max(): ratings[leftNeighborInd];
            int ratsRightNeighbor = (sIndRats[i].first == (sIndRats.size()-1)) ? std::numeric_limits<int>::max(): ratings[rightNeighborInd];
            
            //if my neighbors have less rating than me, I better get more candies
            if (sIndRats[i].second > ratsLeftNeighbor && candiesForMe <= candiesLeftNeighbor) {
                candiesForMe = candiesLeftNeighbor + 1;
            }
            if (sIndRats[i].second > ratsRightNeighbor && candiesForMe <= candiesRightNeighbor) {
                candiesForMe = candiesRightNeighbor + 1;
            }
            
            //bookkeeping
            totalCandies += candiesForMe;
            candies.insert(make_pair(sIndRats[i].first, candiesForMe));
        }
        return totalCandies;
    }
    
public:
    int candy2(vector<int>& ratings) {
        vector<t_IndRat> sIndRats;
        for (unsigned int i=0; i<ratings.size(); i++) {
            sIndRats.push_back(make_pair(i, ratings[i]));
        }
        std::sort(sIndRats.begin(), sIndRats.end(), [] (const t_IndRat& lhs, const t_IndRat& rhs) -> bool {
            return (lhs.second < rhs.second);
        });
        return candyAllotments(ratings, sIndRats);
    }
};

int main() {
    vector<int> ratings;
    int n;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        int rating;
        std::cin >> rating;
        ratings.push_back(rating);
    }

    Solution sln;
    int answer = sln.candy2(ratings);
    std::cout << answer << std::endl;
}

