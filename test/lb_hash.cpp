#include <cassert>
#include <vector>

#include "../lb_common/lb_hash.h"

void test_hash() {
    std::vector<int> input1 = {1, 2, 3};
    std::vector<int> input2 = {1, 2, 2};

    size_t hash1 = hash_range(input1.cbegin(), input1.cend());
    size_t hash2 = hash_range(input2.cbegin(), input2.cend());

    assert(hash1 != hash2);
}

int main() {
    test_hash();
}
