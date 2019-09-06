import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {
	static final int COLOR_UNKNOWN = 0;
	static final int COLOR_WHITE = 1;
	static final int COLOR_BLACK = 2;

	static final int MAX = 100;

	static int[][] data =  new int[MAX][MAX];
	static NON[] rows = new NON[MAX];
	static NON[] columns = new NON[MAX];
	static int[] tmp = new int[MAX];

	static int height;
	static int width;

	static void show() {
		for (int row=0; row<height; ++row) {
			for (int col=0; col<width; ++col) {
				if (COLOR_UNKNOWN == data[row][col]) System.out.print("?");
				if (COLOR_WHITE == data[row][col]) System.out.print(".");
				if (COLOR_BLACK == data[row][col]) System.out.print("#");
			}
			System.out.println("");
		}
		System.out.println("");
	}

	static public void run(NON factory) {
		Scanner s = new Scanner(System.in);
		int type = s.nextInt();
		height = s.nextInt();
		width = s.nextInt();

		for (int row=0; row<height; ++row) for (int col=0; col<width; ++col) data[row][col] = COLOR_UNKNOWN;
		for (int row=0; row<height; ++row) {
			int k = s.nextInt();
			for (int i=0; i<k; ++i) tmp[i] = s.nextInt();
			rows[row] = factory.createLine(width, k, tmp);
		}
		for (int col=0; col<width; ++col) {
			int k; k = s.nextInt();
			for (int i=0; i<k; ++i) tmp[i] = s.nextInt();
			columns[col] = factory.createLine(height, k, tmp);
		}

		boolean anyChange = true;
		while (anyChange) {
			anyChange = false;
			for (int row=0; row<height; ++row) {
				for (int col=0; col<width; ++col) {
					if (COLOR_UNKNOWN == data[row][col]) {
						int color = rows[row].getColor(col);
						if (COLOR_UNKNOWN != color) {
							data[row][col] = color;
							columns[col].setColor(row, color);
							anyChange = true;
						}
					}
				}
			}
			for (int col=0; col<width; ++col) {
				for (int row=0; row<height; ++row) {
					if (COLOR_UNKNOWN == data[row][col]) {
						int color = columns[col].getColor(row);
						if (COLOR_UNKNOWN != color) {
							data[row][col] = color;
							rows[row].setColor(col, color);
							anyChange = true;
						}
					}
				}
			}
		}

		show();
	}
}

