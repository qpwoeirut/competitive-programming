class Drink {
	enum Sizes {SMALL, MEDIUM, LARGE}
	enum Flavors {LEMONADE, SMOOTHIE, HOT_CHOCOLATE}
	Sizes size;
	Flavors flavor;
}

class Person {
	String name;
	int age;
	public Person(String name, int age) {
		this.name = name;
		this.age = age;
	}
	
	public void changeName(String name) {
		System.out.println("Changing name from " + this.name + " to " + name);
		this.name = name;
	}
	
	public void birthday() {
		this.age++;
	}
	
	public Person getInfo() {
		System.out.println("Name: " + this.name);
		System.out.println("Age: " + this.age);
		return this;
	}
}

public class ClassTest {
	public static void main(String args[]) {
		Drink drink = new Drink();
		drink.size = Drink.Sizes.LARGE;
		drink.flavor = Drink.Flavors.SMOOTHIE;
		System.out.println("Drink size, flavor: " + drink.size + " " + drink.flavor);
		Person person = new Person("Stanley", 13);
		person.birthday();
		person.getInfo();
	}
}
