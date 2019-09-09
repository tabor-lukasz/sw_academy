import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {

	static int mmax(int a, int b) { return a > b ? a : b; }

	static int task_rand(int n, int typ) {
		if (typ == 0)
			return pseudo_rand() % n;
		else if (typ == 1)
			return pseudo_rand() % mmax(1, n / 2);
		else if (typ == 2)
			return pseudo_rand() % mmax(1, n / 4);
		else if (typ == 3)
			return pseudo_rand() % mmax(1, n / 8);
		else
			return 0;
	}

	static public void run(KOD solution) {
		Scanner s = new Scanner(System.in);
		int typ = s.nextInt();
		int n;
		int[] codeLengths = new int[20];
		n = s.nextInt();
		for (int i = 0; i < n; ++i)
			codeLengths[i] = s.nextInt();
		long res = solution.countCodes(n, codeLengths);
		System.out.println(res);
	}

}

