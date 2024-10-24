/**
*   This class reports bad date data.
*/
public class BadDateException extends Exception {
	public BadDateException() {}
	public BadDateException(String message)  {
		super(message);
	}
}
