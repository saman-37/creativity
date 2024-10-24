public class Producer implements Runnable {

    // Instance Fields
    private static final int DELAY = 1;
    private Bucket bucket;

    // Constructor
    public Producer(Bucket abucket) {
        bucket = abucket;
    }

    @Override
    public void run() {
        try {
            while (!Thread.currentThread().isInterrupted()) {
                int randNumber = (int) (Math.random() * 256);
                bucket.add(randNumber);
                Thread.sleep(DELAY);
            }

        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

    }
}
