public class dfs {
    public int solution(int[] numbers, int target) {                                    //숫자를 세는 구조가 이진트리(트리) 형식일때
        int sum1 = numbers[0];
        int sum2 = -numbers[0];                                                             // -numbers[0]              +numbers[0]
        int answer =0;                                                       //  -numbers[1]        +numbers[1]        -numbers[1]      +numbers[1] 
        answer += dfs(sum1, 1, numbers, target);                            //  ....
        answer += dfs(sum2, 1, numbers, target);                            // ....
        return answer;                                                     //       |                   |                   |                 |
    }                                                                   
    
    
    
                                                                        //     이진트리 맨 끝 가지 == target이면 return 1(센다)
    
    public int dfs(int prevSum, int index, int[] numbers, int target){
        if(index >=numbers.length){
            if(target == prevSum){
                return 1;
            }
            return 0;
        }       
        else{
            int sum1 = prevSum + numbers[index];
            int sum2 = prevSum - numbers[index];
            int answer = 0;
            answer += dfs(sum1, index+1, numbers, target);
            answer += dfs(sum2, index+1, numbers, target);
            return answer;
        }
    }
}
