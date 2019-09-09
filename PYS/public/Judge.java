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

	static final int MAX_N = 5000;
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

	static boolean partialVerify(int n, int cnt) {
		int x = 1 + (pseudoRand() % n);
		int y = x;
		while (x == y)
			y = 1 + (pseudoRand() % n);

		int posx = -1;
		int posy = -1;
		for (int i=0; i<n; ++i) {
			if (pancakesOrg[i] == x) posx = i;
			if (pancakesOrg[i] == y) posy = i;
		}

		for (int i=0; i<cnt; ++i) {
			if (posx >= moves[i])
				posx = n - 1 + moves[i] - posx;
			if (posy >= moves[i])
				posy = n - 1 + moves[i] - posy;
		}

		if (x + posx != n || y + posy != n) {
			System.out.println("Error. Pancakes are not sorted!");
			return false;
		}
		return true;
	}

	static void changeSeed() {
		// THE BODY OF THIS FUNCTION CAN BE DIFFERENT IN FINAL JUDGE
	}

	static int[] v = new int[200000];
	static int vn = 0;
	static void verify(int n, int cnt) {
		// THE BODY OF THIS FUNCTION CAN BE DIFFERENT IN FINAL JUDGE
		if (n > 0) {
		} else {
			v[vn++] = 0;
			for (int i=0; i<vn; ++i)
				System.out.print("" + v[i] + " ");
			System.out.println("");
		}
	}

	static public void run(PYS solution) {
		Scanner s = new Scanner(System.in);
		int mode = s.nextInt();
		int TC = s.nextInt();
		int n = s.nextInt();
		seed = s.nextLong();
		changeSeed();

		int[] fullVerify = new int[TC]; for (int i=0; i<TC; ++i) fullVerify[i] = 0;
		fullVerify[pseudoRand() % TC] = 1;
		fullVerify[pseudoRand() % TC] = 1;
		fullVerify[pseudoRand() % TC] = 1;

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
				continue;
			}
			if (fullVerify[tc] != 0)
				verify(n, cnt);

			hhash = (hhash * 10007 + (partialVerify(n, cnt) ? (tc+1) : 0)) % 1000000007;
		}
		System.out.println("Final hash: " + hhash);
		verify(0, 0);
	}
}
