package GAL;
import java.util.Scanner;

public class judge {
	int SIZE = 100;
	int PRINT_SIZE = 100;
	int MOD = 1000000097;

	enum Type {
		Produkcja, Handel, Przetwarzanie, Ataki, Podatki
	};

	enum Print {
		None, Hash, Full
	};

	long[][] outputArray = new long[SIZE][SIZE];
	char[] command = new char[100];
	GAL program = null;

	long seed = 0;

	int _rand() {
		seed = seed * 134775813 + 1;
		return (int) ((seed & 0x7FFFFFFF) % 100000007);
	}

	void testSummary(Print print) {
		int hash = 0;
		outputArray[_rand() % SIZE][_rand() % SIZE] = 123;
		if (program != null)
			program.summary(outputArray);
		for (int i = 0; i < PRINT_SIZE; i++) {
			for (int j = 0; j < PRINT_SIZE; j++) {
				long x = outputArray[i][j];
				if (print == Print.Full)
					System.out.printf("%03d ", x % 1000);
				hash *= 13;
				hash += (int) (outputArray[i][j] % MOD);
			}
			if (print == Print.Full)
				System.out.printf("\n");
		}
		if (print != Print.None)
			System.out.printf("%d\n", hash);
		if (print == Print.Full)
			System.out.printf("\n");
	}

	void run(GAL solution) {
		program = solution;
		Scanner sc = new Scanner(System.in);
		int mode = Integer.parseInt(sc.nextLine().trim());

		PRINT_SIZE = 10;
		int n = Integer.parseInt(sc.nextLine());
		for (int i = 0; i < n; i++) {
			int type = sc.nextInt();
			if (type == 0) {
				testSummary(Print.Full);
				sc.nextLine();
				continue;
			}
			char[] command = (sc.nextLine().substring(1) + " ").toCharArray();
			command[command.length - 1] = 0;
			solution.report(command);
			System.out.println(String.copyValueOf(command, 0, command.length - 1));
		}
	}
}
