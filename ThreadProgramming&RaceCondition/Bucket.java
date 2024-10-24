import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * class Bucket manages an ArrayList of integer numbers
 */
public class Bucket {

	private ArrayList<Integer> bucket;
	// creating lock instance to critical section, which is Bucket class
	private Lock listChangeLock;
	private Condition specificElementsCondition;

	/** Default constructor */
	public Bucket() {
		bucket = new ArrayList<Integer>();
		listChangeLock = new ReentrantLock();
		specificElementsCondition=listChangeLock.newCondition();
	}

	/**
	 * add an element to the bucket
	 * 
	 * @param n: an integer number
	 */
	public void add(int n) {
		listChangeLock.lock();
		try {
			bucket.add(n);
			specificElementsCondition.signalAll();
		} finally {
			listChangeLock.unlock();
		}
	}

	/**
	 * Calculates and returns the average of the elements of the bucket and removes
	 * all of the elements from the bucket
	 * 
	 * @return the an array of integers. The first element of the array is the
	 *         median value of the bucket, and second one is the size of the bucket.
	 *         post condition: the elements of the bucket are removed
	 * @throws InterruptedException 
	 */
	public int[] median() throws InterruptedException {

		listChangeLock.lock();
		try {
			while(bucket.size() != 50)
				specificElementsCondition.await();
			int[] data = { 0, 0 };
			if (bucket.size() == 0)
				return data;
			Collections.sort(bucket);
			int median = bucket.get(bucket.size() / 2);
			data[0] = median;
			data[1] = bucket.size();
			reset();
			return data;

		} finally {
			listChangeLock.unlock();
		}

	}

	/**
	 * Returns size of the bucket
	 */
	public int getSize() {
		return bucket.size();
	}

	/**
	 * Removes all of elements from the bucket
	 */
	private void reset() {
		bucket.clear();
	}
}