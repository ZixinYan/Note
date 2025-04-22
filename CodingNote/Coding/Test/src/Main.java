import java.util.HashMap;
import java.util.Map;

public class Main {
    /*
    public long maximumSubarraySum(int[] nums, int k) {
        long sum = 0;
        long ans = 0;
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < k - 1; i++) {
            sum += nums[i];
            map.merge(nums[i], 1, Integer::sum);
        }
        for (int i = k - 1; i < nums.length; i++) {
            sum += nums[i];
            map.merge(nums[i], 1, Integer::sum);
            if (map.size() == k) {
                ans = Math.max(ans, sum);
            }
            sum -= nums[i - k + 1];
            if (map.merge(nums[i - k + 1], -1, Integer::sum) == 0) {
                map.remove(nums[i - k + 1]);
            }
        }
        return ans;
    }

     */

//    public long maximumSubarraySum(int[] nums, int k){
//        int n = nums.length;
//        long res = 0;
//        long sum = 0;
//        Map<Integer, Integer> map = new HashMap<>();
//        int left = 0,right =0;
//        while(right < n){
//            // if the map contains the key, then clear the map and put the key in the map
//            if(map.containsKey(nums[right])){
//
//                while(nums[left] != nums[right] && left < right){
//                    sum -= nums[left];
//                    map.remove(nums[left]);
//                    left++;
//                }
//                left++;
//                right++;
//                continue;
//            }
//
//            sum += nums[right];
//            map.put(nums[right], map.getOrDefault(nums[right], 0) + 1);
//            if(right - left == k - 1){
//                res = Math.max(res, sum);
//                sum -= nums[left];
//                map.remove(nums[left]);
//                left++;
//            }
//            right++;
//        }
//        return res;
//    }



    public static void main(String[] args) {
    }
}