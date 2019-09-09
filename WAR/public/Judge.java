import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {

	static final int MAX_WORKSHOPS = 5;
	static final int MAX_LEVELS = 5;
	static final int MAX_KNOX_ID = 20 * 1000 * 1000;
	static final int MAX_CALLS = 500 * 1000;

	static char[][] levels = {
		{'n','o','n','e','l','i','g','i','b','l','e'},
		{'i','n','t','e','r','m','e','d','i','a','t','e'},
		{'a','d','v','a','n','c','e','d'},
		{'p','r','o','f','e','s','s','i','o','n','a','l'},
		{'e','x','p','e','r','t'}
	};

	static public void run(WAR w) {
		Scanner s = new Scanner(System.in);
		int typ = s.nextInt();
		char[] level = new char[15];
		int[] preferences = new int[MAX_WORKSHOPS];

		int workshopsNum = s.nextInt();
		int maxParticipants = s.nextInt();
		int callsNum = s.nextInt();
		w.init(workshopsNum, maxParticipants);
		for (int i = 0; i < callsNum; ++i) {
			int op = s.nextInt();
			if (op == 0) {
				int byteid = s.nextInt();
				String lvl = s.next();
				for (int j=0; j<lvl.length(); ++j) level[j] = lvl.charAt(j);
				for (int j = 0; j < workshopsNum; ++j)
					preferences[j] = s.nextInt();
				System.out.println(w.registration(byteid, level, preferences));
			} else {
				int byteid = s.nextInt();
				System.out.println(w.unregistration(byteid));
			}
		}
	}
}

