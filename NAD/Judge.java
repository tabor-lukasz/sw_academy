import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {

	static public void run(NAD solution) {
		Scanner s = new Scanner(System.in);
		int mode = s.nextInt();

		int tc = s.nextInt();
		long[][] cost = new long[15][8];

		for (int t=1; t<=tc; ++t) {
			int n = s.nextInt();
			int k = s.nextInt();
			for (int i=0; i<n; ++i) for (int j=0; j<k; ++j) cost[i][j] = s.nextLong();

			long res = solution.getMinimumCost(n, k, cost);
			System.out.println("#" + t + " " + res);
		}
	}

}

