import tkinter as tk
from tkinter import simpledialog, PhotoImage, Scrollbar
from tkinter import messagebox, Canvas, Label, Frame, Text, Button

class Polynomial:
    def __init__(self, coefficients=None):
        if coefficients is None:
            coefficients = []
        self.coefficients = coefficients

    def display(self):
        degree = len(self.coefficients) - 1
        polynomial_str = ""
        for i, coef in enumerate(self.coefficients):
            polynomial_str += f"{coef}x^{degree}"
            if i < len(self.coefficients) - 1:
                polynomial_str += " + "
            degree -= 1
        return polynomial_str

    def add(self, other):
        max_size = max(len(self.coefficients), len(other.coefficients))
        result_coeffs = [0] * max_size
        for i in range(len(self.coefficients)):
            result_coeffs[i] += self.coefficients[i]
        for i in range(len(other.coefficients)):
            result_coeffs[i] += other.coefficients[i]
        return Polynomial(result_coeffs)

    def multiply(self, other):
        result_coeffs = [0] * (len(self.coefficients) + len(other.coefficients) - 1)
        for i in range(len(self.coefficients)):
            for j in range(len(other.coefficients)):
                result_coeffs[i + j] += self.coefficients[i] * other.coefficients[j]
        return Polynomial(result_coeffs)

    def subtract(self, other):
        max_size = max(len(self.coefficients), len(other.coefficients))
        result_coeffs = [0] * max_size
        for i in range(len(self.coefficients)):
            result_coeffs[i] += self.coefficients[i]
        for i in range(len(other.coefficients)):
            result_coeffs[i] -= other.coefficients[i]
        return Polynomial(result_coeffs)

    def reverse(self):
        return Polynomial(self.coefficients[::-1])

    def evaluate(self, x):
        result = 0.0
        degree = len(self.coefficients) - 1
        for coef in self.coefficients:
            result += coef * (x ** degree)
            degree -= 1
        return result

class PolynomialApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Polynomial Calculator")
        self.root.state('zoomed')
        self.root.iconphoto(False, tk.PhotoImage(file='Data/Icon.png'))
        self.polynomials = {}
        self.next_name = 'A'
        self.create_widgets()

    def create_widgets(self):
        self.header_frame = tk.Frame(self.root, bg="#004080")
        self.header_frame.pack(side=tk.TOP, fill=tk.X)
        self.logo_image = PhotoImage(file='Data/Logo.png')
        self.logo_label = tk.Label(self.header_frame, image=self.logo_image, bg="#004080")
        self.logo_label.pack(side=tk.LEFT, padx=10, pady=10)
        self.header_label = tk.Label(
            self.header_frame,
            text="Welcome to Real Time Polynomial Calculator Project\n"
                 "Supervisor: Mr. Ali Bazghandi\n"
                 "Course: Data Structure\n"
                 "Student: Yasin Rezvani, Amir Reza Torabi\n"
                 "Date: Spring 2024\n"
                 "Shahrood University of Technology",
            font=("Arial", 16, "bold"),
            bg="#004080",
            fg="white",
            pady=10,
        )
        self.header_label.pack(side=tk.TOP, fill=tk.X, padx=(0, 200), pady=10)
        self.menu_frame = Frame(self.root, bg="#e6f7ff")
        self.menu_frame.pack(side=tk.TOP, fill=tk.X, pady=10)
        self.create_button("Add Polynomial", self.add_polynomial)
        self.create_button("Display Polynomial", self.display_polynomial)
        self.create_button("Add Polynomials", self.add_polynomials)
        self.create_button("Subtract Polynomials", self.subtract_polynomials)
        self.create_button("Multiply Polynomials", self.multiply_polynomials)
        self.create_button("Reverse Polynomial", self.reverse_polynomial)
        self.create_button("Evaluate Polynomial", self.evaluate_polynomial)
        self.output_frame = Frame(self.root, bg="lightgray")
        self.output_frame.pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True, pady=10)
        self.output_text = Text(self.output_frame, height=20, width=80, bg="#ffffe0", font=("Arial", 14), state=tk.DISABLED, wrap=tk.WORD)
        self.output_text.pack(side=tk.LEFT, padx=20, pady=20, fill=tk.BOTH, expand=True)
        self.scrollbar = Scrollbar(self.output_frame, command=self.output_text.yview)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.output_text.config(yscrollcommand=self.scrollbar.set)

    def create_button(self, text, command):
        button = Button(
            self.menu_frame,
            text=text,
            command=command,
            font=("Arial", 12, "bold"),
            bg="#004080",
            fg="white",
            activebackground="#0059b3",
            activeforeground="white",
            relief=tk.RAISED,
            borderwidth=4,
            width=20
        )
        button.pack(side=tk.LEFT, padx=10, pady=5)

    def display_message(self, message):
        self.output_text.config(state=tk.NORMAL)
        self.output_text.insert(tk.END, f"{message}\n\n")
        self.output_text.see(tk.END)
        self.output_text.config(state=tk.DISABLED)

    def add_polynomial(self):
        degree = self.ask_integer("Input", "Enter the degree of Polynomial:")
        if degree is None:
            return
        coefficients = []
        for i in range(degree + 1):
            coef = self.ask_integer("Input", f"Coefficient of x^{degree - i}:")
            if coef is None:
                return
            coefficients.append(coef)
        self.polynomials[self.next_name] = Polynomial(coefficients)
        self.display_message(f"Polynomial {self.next_name} added successfully.")
        self.next_name = chr(ord(self.next_name) + 1)

    def display_polynomial(self):
        name = self.ask_string("Input", "Enter the name of Polynomial to display (A, B, etc.):")
        if name is None:
            return
        if name in self.polynomials:
            poly_str = self.polynomials[name].display()
            self.display_message(f"{name}: {poly_str}")
        else:
            self.display_message("Polynomial not found.")

    def add_polynomials(self):
        name1 = self.ask_string("Input", "Enter the name of Polynomial 1:")
        name2 = self.ask_string("Input", "Enter the name of Polynomial 2:")
        if name1 in self.polynomials and name2 in self.polynomials:
            result = self.polynomials[name1].add(self.polynomials[name2])
            self.display_message(f"Sum of {name1} and {name2}: {result.display()}")
        else:
            self.display_message("One or both polynomials not found.")

    def subtract_polynomials(self):
        name1 = self.ask_string("Input", "Enter the name of Polynomial 1:")
        name2 = self.ask_string("Input", "Enter the name of Polynomial 2:")
        if name1 in self.polynomials and name2 in self.polynomials:
            result = self.polynomials[name1].subtract(self.polynomials[name2])
            self.display_message(f"Difference of {name1} and {name2}: {result.display()}")
        else:
            self.display_message("One or both polynomials not found.")

    def multiply_polynomials(self):
        name1 = self.ask_string("Input", "Enter the name of Polynomial 1:")
        name2 = self.ask_string("Input", "Enter the name of Polynomial 2:")
        if name1 in self.polynomials and name2 in self.polynomials:
            result = self.polynomials[name1].multiply(self.polynomials[name2])
            self.display_message(f"Product of {name1} and {name2}: {result.display()}")
        else:
            self.display_message("One or both polynomials not found.")

    def reverse_polynomial(self):
        name = self.ask_string("Input", "Enter the name of Polynomial to reverse (A, B, etc.):")
        if name is None:
            return
        if name in self.polynomials:
            reversed_poly = self.polynomials[name].reverse()
            self.display_message(f"Reverse of {name}: {reversed_poly.display()}")
        else:
            self.display_message("Polynomial not found.")

    def evaluate_polynomial(self):
        name = self.ask_string("Input", "Enter the name of Polynomial to evaluate (A, B, etc.):")
        if name is None:
            return
        x = self.ask_float("Input", "Enter the value of x:")
        if x is None:
            return
        if name in self.polynomials:
            result = self.polynomials[name].evaluate(x)
            self.display_message(f"Value of {name} at x={x}: {result}")
        else:
            self.display_message("Polynomial not found.")

    def ask_integer(self, title, prompt):
        return simpledialog.askinteger(title, prompt, parent=self.root, minvalue=0)

    def ask_string(self, title, prompt):
        return simpledialog.askstring(title, prompt, parent=self.root)

    def ask_float(self, title, prompt):
        return simpledialog.askfloat(title, prompt, parent=self.root)

if __name__ == "__main__":
    root = tk.Tk()
    app = PolynomialApp(root)
    root.mainloop()
