import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {
	static long seed = 0;
	static final int MOD = 1000000007;

	static int pseudo_rand() {
		seed = seed * 13477581 + 1;
		return (((int)seed) & 0x7FFFFFFF) % MOD;
	}

	static Scanner s = new Scanner(System.in);

	static int mode;

	static int n;
	static int[] x = new int[1000001];
	static int[] y = new int[1000001];
	static int minDist;
	static int rangeDist;


	static double singleTestCase(BFC solution) {
		n = s.nextInt();
		minDist = s.nextInt();
		rangeDist = s.nextInt();
		for (int i=0; i<n; ++i) {
			x[i] = s.nextInt();
			y[i] = s.nextInt();
		}
		return solution.minFiberCableLength(n, x, y, minDist, rangeDist);
	}


	static public void run(BFC solution) {
		mode = s.nextInt();
		int testCount = s.nextInt();
		seed = s.nextLong();

		double[] results = new double[testCount];
		for (int tc=0; tc<testCount; ++tc) {
			results[tc] = singleTestCase(solution);
		}

		for (int tc=0; tc<testCount; ++tc)
			System.out.println("#" + (tc+1) + ": " + String.format("%.6f", results[tc]));
	}
}

