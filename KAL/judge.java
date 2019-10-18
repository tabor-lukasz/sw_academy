import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class judge {
	static void run(KAL solution) {
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		try {
			String line = r.readLine();
			int N = Integer.parseInt(line);
			char[] buffer = new char[6666];

			for (int i = 0; i < N; i++) {
				String[] data = r.readLine().split(" ");
				int pos = Integer.parseInt(data[1]);
				int len = Integer.parseInt(data[2]);
				if (data[0].charAt(0) == 'I') {
					char[] input = (data[3] + "\0").toCharArray();
					solution.insert(input, pos, len, buffer);
				} else {
					solution.remove(pos, len, buffer);
				}
				int buffLen = 0;
				while (buffer[buffLen] != 0)
					buffLen++;
				System.out.println(String.valueOf(buffer, 0, buffLen));
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
