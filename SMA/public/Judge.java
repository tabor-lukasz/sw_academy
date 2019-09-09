import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class Judge {
	static long seed = 0;
	static int pseudoRand() {
		seed = seed * 13477581 + 1;
		return (((int)seed) & 0x7FFFFFFF) % 1000000007;
	}

	static final int MAX_N = 500;
	static final int MAX_MOVES = 15 * MAX_N;
	static int[] pancakes = new int[MAX_N];
	static int[] pancakesOrg = new int[MAX_N];
	static int[] moves = new int[MAX_MOVES];

	static void randomShuffle(int n) {
		for (; n>1; --n) {
			int pos = pseudoRand() % n;
			int tt = pancakes[pos];
			pancakes[pos] = pancakes[n-1];
			pancakes[n-1] = tt;
		}
	}

	static boolean verify(int n, int cnt) {
		for (int i=0; i<cnt; ++i) {
			int a = moves[i];
			int b = n-1;
			if (a < 0 || a >= n) {
				System.out.println("Error. Move not in range [0, n-1].");
				a = n-1;
			}
			while (a < b) {
				int tt = pancakesOrg[a];
				pancakesOrg[a] = pancakesOrg[b];
				pancakesOrg[b] = tt;
				++a;
				--b;
			}
		}
		for (int i=0; i<n; ++i) {
			if (i + pancakesOrg[i] != n) {
				System.out.println("Error. Pancakes are not sorted!");
				return false;
			}
		}
		return true;
	}

	static void changeSeed() {
		// THE FINAL JUDGE WILL BE THE SAME AS THIS ONE...
		// EXCEPT THE BODY OF THIS FUNCTION
	}

	static public void run(SMA solution) {
		Scanner s = new Scanner(System.in);
		int mode = s.nextInt();
		int TC = s.nextInt();
		int n = s.nextInt();
		seed = s.nextLong();
		changeSeed();

		int[] needVerify = new int[TC]; for (int i=0; i<TC; ++i) needVerify[i] = 1;

		long hhash = 0L;
		for (int tc=0; tc<TC; ++tc) {
			for (int i=0; i<n; ++i)
				pancakes[i] = i+1;
			randomShuffle(n);
			for (int i=0; i<n; ++i)
				pancakesOrg[i] = pancakes[i];
			int cnt = solution.sortPancakes(n, pancakes, moves);
			if (cnt < 0 || cnt > MAX_MOVES) {
				System.out.println("Error. Number of moves negative or exceeds the limit.");
				needVerify[tc] = 0;
			}
			if (needVerify[tc] != 0)
				hhash = (hhash * 10007 + (verify(n, cnt) ? (tc+1) : 0)) % 1000000007;
		}
		System.out.println("Final hash: " + hhash);
	}
}
