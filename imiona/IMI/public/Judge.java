import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {
	static int mode;
	static int population = 0;
	static int queryCount = 0;
	static int nextQuery = 0;

	static char[][] names = new char[32768][16];
	static char[][] logins = new char[65536][8];
	static char[] buf = new char[32];


	static boolean doInit = true;
	static Scanner s;
	static void init() {
		if (doInit == false) return;
		doInit = false;
		s = new Scanner(System.in);
		mode = s.nextInt();

		population = s.nextInt();
		queryCount = s.nextInt();
		s.nextLine();
		for (int i=0; i<population; ++i) {
			String line = s.nextLine();
			for (int j=0; j<16; ++j) names[i][j] = line.charAt(j);
		}
		for (int i=0; i<queryCount; ++i) {
			String line = s.nextLine();
			for (int j=0; j<8; ++j) logins[i][j] = line.charAt(j);
		}
	} // init()

	static public int getPopulation() {
		init();
		return population;
	}

	static public void getCitizenName(int id, char[] name) {
		init();
		for (int j=0; j<16; ++j)
			name[j] = names[id][j];
	}

	static public int getQueryCount() {
		init();
		return queryCount;
	}

	static public void getCitizenLogin(char[] login) {
		init();
		for (int j=0; j<8; ++j)
			login[j] = logins[nextQuery][j];
		++nextQuery;
	}

	static public void replyCitizenName(char[] name) {
		init();
		for (int i=0; i<16; ++i) System.out.print(name[i]);
		System.out.println("");
	}
}

