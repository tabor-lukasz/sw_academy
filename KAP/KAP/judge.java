import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class judge {

	static void run(KAP s) {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		try {
			int T = Integer.parseInt(reader.readLine());
			for (int t = 1; t <= T; t++) {
				int n = Integer.parseInt(reader.readLine());
				int[][] data = new int[n][5];
				for (int i = 0; i < n; i++) {
					String line = reader.readLine();
					for (int j = 0; j < 5; j++) {
						data[i][j] = line.charAt(2 * j) - '0';
					}
				}
				System.out.println("#" + t + " " + s.maxScore(n, data));
			}
		} catch (NumberFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}