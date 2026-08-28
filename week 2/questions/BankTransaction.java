import java.util.Scanner;
public class BankTransaction{
    static String normalizeReference(String raw) {
        String reference = raw.trim();
        if (reference.length() < 3) {
            return reference;
        }
        String bankCode = reference.substring(0, 3).toUpperCase();
        String rest = reference.substring(3);
        return bankCode + rest;
    }
    static String validateAndFormat(String reference) {
        if (reference.length() != 14) {
            return "Invalid: wrong length";
        }
        for (int i = 0; i < 3; i++) {
            if (!Character.isLetter(reference.charAt(i))) {
                return "Invalid: bank code must be 3 letters";
            }
        }
        for (int i = 3; i < 14; i++) {
            if (!Character.isDigit(reference.charAt(i))) {
                return "Invalid: body must contain only digits";
            }
        }
        String bankCode = reference.substring(0, 3);
        String day = reference.substring(3, 5);
        String month = reference.substring(5, 7);
        String year = reference.substring(7, 9);
        String sequence = reference.substring(9, 14);
        StringBuilder result = new StringBuilder();
        result.append("[");
        result.append(bankCode);
        result.append("] DATE: ");
        result.append(day);
        result.append("/");
        result.append(month);
        result.append("/");
        result.append(year);
        result.append(" | SEQ: ");
        result.append(sequence);
        return result.toString();
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter transaction reference: ");
        String raw = sc.nextLine();
        String normalized = normalizeReference(raw);
        System.out.println(validateAndFormat(normalized));
        sc.close();
    }
}