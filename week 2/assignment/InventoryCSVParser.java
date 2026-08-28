import java.util.Scanner;

public class InventoryCSVParser {

    public static void parseInventoryRecord(String csvLine) {

        String[] fields = csvLine.split(",");

        if (fields.length != 3) {
            System.out.println("Invalid Record");
            return;
        }

        String productName = fields[0];
        String sku = fields[1];
        String quantity = fields[2];

        System.out.println(
            "Product: " + productName +
            " | SKU: " + sku +
            " | Qty: " + quantity
        );
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print(
            "Enter ProductName,SKU,Quantity: "
        );

        String csvLine = sc.nextLine();

        parseInventoryRecord(csvLine);

        sc.close();
    }
}