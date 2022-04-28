class primeNumbers extends Thread {
    public synchronized void run()
    {
        int i = 0;
        int num = 0;
        String primeNumbers = "";

        for (i = 1; i <= 100; i++) {
            int counter = 0;
            for (num = i; num >= 1; num--) {
                if (i % num == 0) {
                    counter = counter + 1;
                }
            }

            if (counter == 2) {
                primeNumbers = primeNumbers + i + " ";
            }
        }
        System.out.println("\nPrime numbers from 0 to 100 : \n" + primeNumbers);
        System.out.println();
    }
  }

  class palindrome extends Thread {
    public synchronized void run()
    {
        int N = 100;
        String s1;
        StringBuffer s2;
        System.out.println("Palindrome numbers from 10 to 1000 : ");
        for (int i = 10; i <= N; i++) {
            s1 = "" + i;
            s2= new StringBuffer(s1);
            s2.reverse();
            if (s1.equals(s2.toString())) {
                System.out.print(i + " ");
            }
        }
    }
  }

  public class PrimePalindromeThread {

    public static void main(String[] args)
    {
      primeNumbers pn = new primeNumbers();
      pn.start();
      palindrome pal = new palindrome();
      pal.start();
    }
  }
