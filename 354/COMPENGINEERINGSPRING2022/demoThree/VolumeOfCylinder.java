import java.util.Scanner;

/* Java program to calculate the volume of a cylinder. */
public class VolumeOfCylinder {
	
	/**
	 * Program execution begins here.
	 * @param args UNUSED
	 */
	public static void main(String[] args) {
	
		// declare a constant for PI
		final double PI = Math.PI;
		
		//Create a Scanner to get input from the user.
		Scanner input = new Scanner(System.in);
		
		// Declare a variable for the radius of the cylinder
		double radius;
		
		System.out.print("Enter the radius of the cylinder:");
		
		// assign the radius entered by the user to the variable radius
		radius = input.nextDouble();
		
		System.out.print("Enter the height of the cylinder:");
		
		// declare a variable for height of the cylinder
		// and assign it with the value that the user enters
		double height = input.nextDouble();
		
		// declare a variable for the volume of the cylinder
		double volume;
		
		// calculate the volume of the cylinder
		// volume of cylinder = PI * r * r * h
		volume = PI * radius * radius * height;
		
		// print the volume of the cylinder to the console
		System.out.printf("The volume of the cylinder = %.2f\n", volume);
		
		// close the scanner to avoid resource leak
		input.close();
	}

}