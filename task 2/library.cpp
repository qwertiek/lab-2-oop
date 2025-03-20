#include "library.hpp"

namespace template_library {
    int longest_duplicate_subarray(const std::vector<int>& nums) {
        // Инициализация границ бинарного поиска
        int low = 1;
        int high = nums.size() - 1;
        int max_length = 0;

        // Бинарный поиск по длине подмассива
        while (low <= high) {
            int mid = low + (high - low) / 2;
            std::unordered_set<std::string> seen_subarrays;
            bool duplicate_found = false;

            // Проверка всех подмассивов длины mid
            for (int i = 0; i <= static_cast<int>(nums.size()) - mid; ++i) {
                // 1. Создайте строковое представление подмассива
                //    Формат: "элемент1,элемент2,...,элементN"
                //    Пример: для {2,3,4} -> "2,3,4,"
                std::string subarray_str;

                // 2. Заполните subarray_str значениями подмассива [i..i+mid)
                //    (реализуйте цикл)
                for (int j = i; j < i + mid; j++) {
                    subarray_str += std::to_string(nums[j]) + ",";
                }

                // 3. Проверьте наличие подмассива в сете
                if (seen_subarrays.find(subarray_str) != seen_subarrays.end()) {
                    duplicate_found = true;
                    break;
                }
                // 4. Добавьте подмассив в сет
                seen_subarrays.insert(subarray_str);
            }

            // Обновление границ бинарного поиска
            if (duplicate_found) {
                max_length = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return max_length;
    }
}
