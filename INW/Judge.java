import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {

	static int mode;
	static int[][] map = new int[1000][1000];
	static Scanner s = new Scanner(System.in);


	static void generateMap(int h, int w) {
		for (int i=0; i<h; ++i) for (int j=0; j<w; ++j) {
			map[i][j] = s.nextInt();
		}
	}

	static void singleCase(INW sol, int nr) {
		int h = s.nextInt();
		int w = s.nextInt();
		generateMap(h, w);

		sol.init(h, w, map);
		int res1 = sol.getInvasionDuration();
		int res2 = sol.getFinalArea();
		System.out.println("#" + nr + ": " + res1 + " " + res2);
	}

	static public void run(INW solution) {
		mode = s.nextInt();
		int tc = s.nextInt();

		for (int i=0; i<tc; ++i)
			singleCase(solution, i+1);
	}
}

