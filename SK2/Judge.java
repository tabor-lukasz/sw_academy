import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {
	static long seed = 0;
	static int pseudo_rand() {
		seed = seed * 13477581 + 1;
		return (((int)seed) & 0x7FFFFFFF) % 1000000007;
	}

	static int[][][] db = new int[100][100][100];
	static int[][] q = new int[8][8];
	static final int mod = 256;

	static final int MAX_QUERY_COUNT = 500000;

	static public void run(SK2 solution) {
		Scanner s = new Scanner(System.in);
		seed = s.nextLong();
		int count = s.nextInt();
		if (count > MAX_QUERY_COUNT) {
			System.err.println("Input data corrupted. Given query count: " + count);
			System.exit(1);
		}
		for (int i=0; i<100; ++i)
			for (int j=0; j<100; ++j)
				for (int k=0; k<100; ++k)
					db[i][j][k] = pseudo_rand() % mod;

		solution.database(db);

		long hash1 = 123987L;
		long hash2 = hash1;
		for (int tc=0; tc<count; ++tc) {
			int id = pseudo_rand() % 100;
			int x = pseudo_rand() % 93;
			int y = pseudo_rand() % 93;
			for (int i=0; i<8; ++i)
				for (int j=0; j<8; ++j)
					q[i][j] = db[id][x+i][y+j];
			x = pseudo_rand() % 4;
			y = pseudo_rand() % 4;
			for (int i=0; i<5; ++i)
				for (int j=0; j<5; ++j)
					q[x+i][y+j] = pseudo_rand() % mod;

			int result = solution.query(q);

			hash1 = (hash1 * 1337 +     id) % 1000000007;
			hash2 = (hash2 * 1337 + result) % 1000000007;
		}

		if (hash1 == hash2) {
			System.out.println("Solution correct! Congratulations! " + hash2);
		} else {
			System.out.println("Something went wrong! Try again... " + hash2);
		}
	}
}

