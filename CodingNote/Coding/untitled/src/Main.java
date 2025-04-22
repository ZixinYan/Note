import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
// 注意类名必须为 Main, 不要有任何 package xxx 信息
public class Main {
    static class Point {
        int x, y;
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public double distance(Point a) {
            return Math.sqrt(Math.pow(this.x - a.x, 2) + Math.pow(this.y - a.y, 2));
        }
    }

    private static double calc(List<Point> points) {
        double res = 0;
        for (int i = 0; i < points.size(); i++) {
            Point curr = points.get(i);
            Point next = points.get((i + 1) % points.size());
            res += curr.distance(next);
        }
        return res;
    }



    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int speedInSpace = in.nextInt();

        int[] speedInPrint = new int[n];
        for (int i = 0; i < n; i++) {
            speedInPrint[i] = in.nextInt();
        }
        List<List<Point>> shapes = new ArrayList<>();
        List<Point> startNodes = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int m = in.nextInt();
            List<Point> points = new ArrayList<>();
            Point min = new Point(Integer.MAX_VALUE, Integer.MAX_VALUE);
            for (int j = 0; j < m; i++) {
                int x = in.nextInt();
                int y = in.nextInt();
                if (Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2)) < Math.sqrt(Math.pow(min.x,2) + Math.pow(min.y, 2))) {
                    min.x = x;
                    min.y = y;
                }
                points.add(new Point(x, y));
            }
            shapes.add(points);
            startNodes.add(min);
        }
        double totalTime = 0;

        double permutation = 0;
        for (int i = 0; i < n; i++) {
            permutation = calc(shapes.get(i));
            totalTime += permutation*speedInPrint[i];
        }
        Point min = new Point(Integer.MAX_VALUE, Integer.MAX_VALUE);
        for(int i = 0;i<n;i++){
            if(Math.sqrt(Math.pow(startNodes.get(i).x, 2) + Math.pow(startNodes.get(i).y, 2)) < Math.sqrt(Math.pow(min.x,2) + Math.pow(min.y, 2)) ){
                min.x = startNodes.get(i).x;
                min.y = startNodes.get(i).y;
            }
        }
        double startPermutation = calc(startNodes);
        totalTime += startPermutation * speedInSpace;

        totalTime += Math.sqrt(Math.pow(min.x,2) + Math.pow(min.y, 2)) * speedInSpace;

        System.out.print(totalTime);

    }
}