public class IMI {

	public static void main(String[] args) {

		int population = Judge.getPopulation();
		int n = Judge.getQueryCount();

		for (int ___=0; ___<n; ++___) {
			char[] login = new char[8];
			Judge.getCitizenLogin(login);
			char[] name = new char[16];
			int id = ___ % population;
			Judge.getCitizenName(id, name);
			Judge.replyCitizenName(name);
		}

	}

}

