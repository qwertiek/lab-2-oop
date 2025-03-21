#include "library.hpp"

namespace template_library {
    int josephus_problem(const std::vector<int>& nums, int k) {
        std::deque<int> dq(nums.begin(), nums.end());

        while (dq.size() > 1) {
            for (int i = 0; i < k - 1; ++i) {
                dq.push_back(dq.front());
                dq.pop_front();
            }
            dq.pop_front();
        }

        return dq.front();
    }
}
