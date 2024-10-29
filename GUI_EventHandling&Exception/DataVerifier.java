public class DataVerifier {

    public static void verifyDate(String date, String type) throws BadDateException {

        // Check for valid format with regex: allows 1-2 digits for day and month, 4
        // digits for year
        if (!date.matches("(0?[1-9]|[12][0-9]|3[01])/(0?[1-9]|1[0-2])/(\\d{4})")) {
            throw new BadDateException(type + ": Date format must be DD/MM/YYYY");
        }

        // Split into parts, to verify individual components
        String[] parts = date.split("/");
        if (parts.length != 3)
            throw new BadDateException(type + ": missing or too many fields. The correct format is DD/MM/YYYY");

        String day = parts[0];
        String month = parts[1];
        String year = parts[2];

        // Check if only digits
        if (!day.matches("\\d+") || !month.matches("\\d+") || !year.matches("\\d+"))
            throw new BadDateException(type + ": only digits are allowed. D, M, and Y are digits in DD/MM/YYYY");

        // Convert parts to integers
        int dayInt = Integer.parseInt(day);
        int monthInt = Integer.parseInt(month);
        int yearInt = Integer.parseInt(year);

        // Verify month
        if (monthInt < 1 || monthInt > 12) {
            throw new BadDateException(type + ": incorrect \"month digits\" - " + month);
        }

        // Check for valid days per month
        int maxDays = getMaxDaysInMonth(monthInt, yearInt);
        if (dayInt < 1 || dayInt > maxDays) {
            throw new BadDateException(type + ": incorrect \"day digits\" - " + day);
        }

        // Verify year
        if (yearInt < 1000 || yearInt > 3000) {
            throw new BadDateException(type + ": maximum year is 3000");
        }
    }

    // Helper method to determine max days in a month
    private static int getMaxDaysInMonth(int month, int year) {
        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12: // 31 days
                return 31;
            case 4:
            case 6:
            case 9:
            case 11: // 30 days
                return 30;
            case 2: // February, check for leap year
                return (isLeapYear(year)) ? 29 : 28;
            default:
                return 0; // should never reach here
        }
    }

    // Helper method to check if a year is a leap year
    private static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
}
