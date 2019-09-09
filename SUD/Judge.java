import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {
	static public void run(SUD solution) {
		Scanner s = new Scanner(System.in);
		int mode = s.nextInt();

		int[][] board = new int[9][9];

		for (int i=0; i<9; ++i) {
			String ss = s.next();
			for (int j=0; j<9; ++j) board[i][j] = ((int)ss.charAt(j)) - 48;
		}

		solution.solve(board);

		for (int i=0; i<9; ++i) {
			for (int j=0; j<9; ++j)
				System.out.print(board[i][j]);
			System.out.println("");
		}
	}
}

