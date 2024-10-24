public class Consumer implements Runnable {
    // Instance Fields
    // Very important: instance of object, on which it will perform action
    private Bucket bucket;
    private static final int DELAY = 5; // For Thread.sleep(DELAY)

    // Constructor
    public Consumer(Bucket abucket) {
        bucket = abucket;

    }

    public void run() {

        try {
            // repeat the process while the thread is not interrupted
            while (!Thread.currentThread().isInterrupted()) {
                int[] median = bucket.median();
                System.out.println("median : " + median[0] + ", size : " + median[1]);
                Thread.sleep(DELAY);
            }

        } catch (InterruptedException exception) {
            Thread.currentThread().interrupt();

        }
    }

}