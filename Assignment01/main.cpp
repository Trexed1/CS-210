#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
//Brute force approach where we check all possible pairs.
std::pair<int,int> twoSumBruteForce(
    const std::vector<int>& nums,
    int target) {
        //Traverses all possible pairs and checks if any reach the target
        for (int i = 0; i < nums.size(); ++i){
            for (int j = i + 1; j < nums.size(); ++j){
                if(nums[i] + nums[j] == target){
                    return {i,j};
                }
            }
        }
        //if no good pairs were found
        return {-1,-1};
}

std::pair<int,int> twoSumHash(
    const std::vector<int>& nums,
    int target
) {
    std::unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); ++i){
        int need = target - nums[i];
        //if the search result is not the end marker, then its found
        if(seen.find(need) != seen.end()) return {seen[need],i};
        seen[nums[i]] = i;

    }
    //if no good pairs were found
    return {-1,-1};  
}
//Helper function to reduce redundant code in main
void testFunc(
    const std::vector<int>& nums,
    int target) {
        bool valid = true;
        std::cout << "Given Vector: ";
        for (int i = 0; i < nums.size(); ++i) {
            std::cout << nums[i] << " ";
        }
        std::cout << "" << std::endl;
        std::cout << "Given Target: " << target << std::endl;

        std::pair<int,int> result1 = twoSumBruteForce(nums,target);
        std::cout << "Brute Force: " << std::endl;
        //prints indicies
        std::cout << "Indices: " << std::endl;
        std::cout << "[ " << result1.first << ", " << result1.second <<" ]" << std::endl;
        //prints values
         std::cout << "Values: " << std::endl;
        std::cout << "[ " << nums[result1.first] << ", " << nums[result1.second] <<" ]" << std::endl;
        valid = (result1.first != result1.second) && (nums[result1.first] + nums[result1.second] == target);
        std::cout << "Valid: " << std::boolalpha << valid << std::endl;

        std::pair<int,int>  result2 = twoSumHash(nums,target);
        std::cout << "SumHash: " << std::endl;
        //prints indicies
        std::cout << "Indices: " << std::endl;
        std::cout << "[ " << result2.first << ", " << result2.second <<" ]" << std::endl;
        //prints values
        std::cout << "Values: " << std::endl;
        std::cout << "[ " << nums[result2.first] << ", " << nums[result2.second] <<" ]" << std::endl;
        valid = (result2.first != result2.second) && (nums[result2.first] + nums[result2.second] == target);
        std::cout << "Valid: " << std::boolalpha << valid << std::endl;

}

int main() {
    //Test Case 1: Given (Assume only one valid pair exists but there are two pairs???)
    std::vector<int> nums = {15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9};
    int target = 24;    
    testFunc(nums, target);

    //Test Case 2: Basic Test
    nums = {2, 6, 11, 15};
    target = 8;    
    testFunc(nums, target);

    //Test Case 3: Duplicate Values
    nums = {2, 2, 11, 15};
    target = 4;    
    testFunc(nums, target);

    //Test Case 4: Negative Number
    nums = {-2, 6, 11, 15};
    target = 4;    
    testFunc(nums, target);

    //Test Case 5: Endpoints
    nums = {3, 6, 11, 15};
    target = 18;    
    testFunc(nums, target);
}