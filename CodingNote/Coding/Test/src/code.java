public class code {
    public static int remove(int[] nums){
        if(nums.length <= 2){
            return nums.length;
        }
        int i = 1;
        int count = 1;
        for(int j = 1;j< nums.length;j++){
            if(nums[j] == nums[j-1]){
                count++;
            }else{
                count = 1;
            }
            if(count <= 2){
                nums[i++] = nums[j];
            }
        }
        return i;
    }

    public static void main(String[] args) {
        int[] nums = {1,1,1,2,2,3};
        System.out.println(remove(nums));
        for(int i: nums){
            System.out.print(i + " ");
        }
    }

}
