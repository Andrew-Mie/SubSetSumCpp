// SubSetSumCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


struct Stick {
    int height;
    int weight;
};

int main() {
    std::vector<Stick> sticks = {
        {3, 2}, {5, 4}, {7, 6}, {2, 1}, {8, 5},
        {4, 3}, {6, 7}, {9, 9}, {1, 2}, {5, 4},
        {7, 6}, {8, 8}, {3, 3}, {4, 5}, {6, 7},
        {2, 1}, {1, 2}, {5, 4}, {8, 6}, {9, 7}
    };

    std::sort(sticks.begin(), sticks.end(), [](const Stick& a, const Stick& b) {
        return a.weight < b.weight;
        });


    int n = sticks.size();
    std::vector<int> dp(51);
    std::vector<std::vector<int>> sticksUsed(51);

    for (int i = 0; i < n; i++) {
        for (int j = 50; j >= sticks[i].weight; j--) {
            if (dp[j] < dp[j - sticks[i].weight] + sticks[i].height) {
                dp[j] = dp[j - sticks[i].weight] + sticks[i].height;
                sticksUsed[j] = sticksUsed[j - sticks[i].weight];
                sticksUsed[j].push_back(i);
            }
        }
    }

    int maxSum = dp[50];
    std::vector<int> usedSticks = sticksUsed[50];
    int usedWeight = 0;
    for (int i = 0; i < usedSticks.size(); i++) {
        usedWeight += sticks[usedSticks[i]].weight;
    }

    std::cout << "Max sum of heights: " << maxSum << std::endl;
    std::cout << "Sticks used: ";
    for (int i = 0; i < usedSticks.size(); i++) {
        std::cout << "(" << sticks[usedSticks[i]].height << ", " << sticks[usedSticks[i]].weight << ")";
        if (i != usedSticks.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Sum of weights of used sticks: " << usedWeight << std::endl;

    return 0;
}

