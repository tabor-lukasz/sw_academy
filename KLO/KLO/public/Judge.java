import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Judge {
	public static void run(KLO solution) {
		final int N = 7;
		int[] a = new int[N];
		int[] b = new int[N];
		int[] c = new int[N];
		Scanner s = new Scanner(System.in);
		int tc = s.nextInt();
		for (int t=0; t<tc; ++t) {
			int n = s.nextInt();
			for (int i=0; i<n; ++i) {
				a[i] = s.nextInt();
				b[i] = s.nextInt();
				c[i] = s.nextInt();
			}
			int res = solution.maxTowerHeight(n, a, b, c);
			System.out.println("#" + t + ": " + res);
		}
	}
}

