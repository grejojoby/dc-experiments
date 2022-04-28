import java.util.Scanner;

class LoadBalancer {

    static void printLoad(int servers, int Processes) {
        int each = Processes / servers;
        int extra = Processes % servers;
        int total = 0;
        System.out.println();
        for (int i = 0; i < servers; i++) {

            if (extra-- > 0)
                total = each + 1;
            else

                total = each;

            System.out.println("Server " + (char) ('A' + i) + " has " + total + " Processes");

        }

    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of Servers : ");
        int servers = sc.nextInt();
        System.out.print("Enter the number of Processes : ");

        int Processes = sc.nextInt();
        while (true) {
            printLoad(servers, Processes);

            System.out.println("\n1.Add Servers \n2.Remove Servers \n3.Add Processes \n4.Remove Processes \n5.Exit");
            System.out.print("Select a Option : ");
            switch (sc.nextInt()) {
                case 1:

                    System.out.print("How many more Servers ?  : ");
                    servers += sc.nextInt();
                    break;
                case 2:
                    System.out.print("How many servers to Remove ? : ");

                    servers -= sc.nextInt();
                    break;
                case 3:

                    System.out.print("How many more Processes ? : ");
                    Processes += sc.nextInt();
                    break;

                case 4:

                    System.out.print("How many Processes to Remove ? : ");
                    Processes -= sc.nextInt();
                    break;
                case 5:
                    sc.close();

                    return;

            }
        }

    }

}
