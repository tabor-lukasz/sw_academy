import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Judge {

	static void read(Scanner s, char[] res) {
		String ss = s.next();
		for (int i=0; i<ss.length(); ++i)
			res[i] = ss.charAt(i);
		res[ss.length()] = 0;
	}

	static public void run(DRZ solution) {
		Scanner s = new Scanner(System.in);
		int mode = s.nextInt();

		char[] info = new char[256];
		char[] info2 = new char[256];

		while (true) {
			int cmd = s.nextInt();
			if (0 == cmd) {
				break;
			} else if (1 == cmd) {
				read(s, info);
				//int res = solution.addCitizenInfo(info);
				solution.addCitizenInfo(info);
				int res = 999999999;
				System.out.println(res);
			} else if (2 == cmd) {
				read(s, info);
				int res = solution.delCitizenInfo(info);
				System.out.println(res);
			} else if (3 == cmd) {
				read(s, info);
				read(s, info2);
				solution.modifyCitizen(info, info2);
			} else if (4 == cmd) {
				read(s, info);
				int res = solution.familyMemberCount(info);
				System.out.println(res);
			}
		}
	}
}

