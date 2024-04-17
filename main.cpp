#include <iostream>

#include <vector>

#include <map>

#include <cmath>

using namespace std;

class Polynomial {

  private: vector < int > coefficients;

  public: Polynomial() {}

  Polynomial(vector < int > coeffs): coefficients(coeffs) {}

  void display() const {

    int degree = coefficients.size() - 1;

    for (int i = 0; i < coefficients.size(); ++i)

    {

      cout << coefficients[i] << "x^" << degree;

      if (i < coefficients.size() - 1)

        cout << " + ";

      degree--;

    }

    cout << endl;

  }

  Polynomial add(const Polynomial & other) const {

    int maxSize = max(coefficients.size(), other.coefficients.size());

    vector < int > resultCoeffs(maxSize, 0);

    for (int i = 0; i < coefficients.size(); ++i)

      resultCoeffs[i] += coefficients[i];

    for (int i = 0; i < other.coefficients.size(); ++i)

      resultCoeffs[i] += other.coefficients[i];

    return Polynomial(resultCoeffs);

  }

  Polynomial multiply(const Polynomial & other) const {

    vector <

      int > resultCoeffs(coefficients.size() + other.coefficients.size() -

        1, 0);

    for (int i = 0; i < coefficients.size(); ++i)

    {

      for (int j = 0; j < other.coefficients.size(); ++j)

      {

        resultCoeffs[i + j] +=
          coefficients[i] * other.coefficients[j];

      }
    }
    return Polynomial(resultCoeffs);

  }

  Polynomial subtract(const Polynomial & other) const {

    int maxSize = max(coefficients.size(), other.coefficients.size());

    vector < int > resultCoeffs(maxSize, 0);

    for (int i = 0; i < coefficients.size(); ++i)

      resultCoeffs[i] += coefficients[i];

    for (int i = 0; i < other.coefficients.size(); ++i)

      resultCoeffs[i] -= other.coefficients[i];

    return Polynomial(resultCoeffs);

  }

  Polynomial reverse() const {

    vector < int > resultCoeffs(coefficients.rbegin(),

      coefficients.rend());

    return Polynomial(resultCoeffs);

  }

  const vector < int > & getCoefficients() const {

    return coefficients;

  }

  double evaluate(double x) const {

    double result = 0.0;

    for (int i = 0; i < coefficients.size(); ++i)

    {

      result +=
        coefficients[i] * pow(x, coefficients.size() - 1 - i);

    }
    return result;

  }

};

int
main() {

  cout <<

    "\n------------------------------------------------------------------------------------------------------------------------\n";

  cout <<

    "\n\t\t ************ Welcome to Real Time Polynomial Calculator Project ************\n\n";

  cout << "\t\t\t\t\t Supervisor : Mr.Ali Bazghandi\n";

  cout << "\t\t\t\t\t Course : Data Structure \n";

  cout << "\t\t\t\t\t Student : Yasin Rezvani \n";

  cout << "\t\t\t\t\t Date : Spring 2024 \n\n";

  cout << "\t\t\t\t\t Shahrood University of Technology \n\n";

  cout <<

    "------------------------------------------------------------------------------------------------------------------------"

    <<
    endl;

  map < char, Polynomial > polynomials;

  char next_name = 'A';

  int choice;

  while (true)

  {

    cout << "\nMenu: Please choose your section: \n\n";

    cout << "1. Add Polynomial\n";

    cout << "2. Display Polynomial\n";

    cout << "3. Add Polynomials\n";

    cout << "4. Subtract Polynomials\n";

    cout << "5. Multiply Polynomials\n";

    cout << "6. Reverse Polynomial\n";

    cout << "7. Evaluate Polynomial at a Point\n";

    cout << "0. Exit\n";

    cout << "\n# Enter your choice: ";

    cin >> choice;

    cout << "\n";

    switch (choice)

    {

    case 1:

    {

      vector < int > coeffs;

      int degree, coef;

      cout << "\n# Enter the degree of Polynomial: ";

      cin >> degree;

      for (int i = 0; i <= degree; ++i)

      {

        cout << "\n# Coefficient of x^" << degree - i << ": ";

        cin >> coef;

        coeffs.push_back(coef);

      }

      polynomials[next_name] = Polynomial(coeffs);

      cout << "\n            -----------    Polynomial " <<
        next_name << " added successfully.   -----------\n";

      next_name++;

      break;

    }

    case 2:

    {

      if (polynomials.empty())

      {

        cout <<
          "\n            -----------     No polynomials to display.     -----------\n";

      } else

      {

        char name;

        cout <<

          "\n# Enter the name of Polynomial you want to display (A, B, etc.): ";

        cin >> name;

        if (polynomials.find(name) == polynomials.end())

        {

          cout <<
            "\n          -----------     Polynomial not found.     -----------\n";

        } else

        {

          polynomials[name].display();

        }

      }

      break;

    }

    case 3:

    {

      if (polynomials.size() < 2)

      {

        cout <<

          "\n                -----------    At least two polynomials are required to perform addition.     -----------\n";

      } else

      {

        char name1, name2;

        cout << "\n# Enter the name of Polynomial 1: ";

        cin >> name1;

        cout << "\n# Enter the name of Polynomial 2: ";

        cin >> name2;

        if (polynomials.find(name1) == polynomials.end() ||
          polynomials.find(name2) == polynomials.end())

        {

          cout <<

            "\n                   -----------     One or both of the specified polynomials not found.     -----------";

        } else

        {

          Polynomial sum =

            polynomials[name1].add(polynomials[name2]);

          cout << "\n# Sum of Polynomial " << name1 <<

            " and Polynomial " << name2 << ": ";

          sum.display();

          polynomials[next_name] = sum;

          next_name++;

        }

      }

      break;

    }

    case 4:

    {

      if (polynomials.size() < 2)

      {

        cout <<

          "\n                   -----------       At least two polynomials are required to perform subtraction.        -----------";

      } else

      {

        char name1, name2;

        cout << "\n# Enter the name of Polynomial 1: ";

        cin >> name1;

        cout << "\n# Enter the name of Polynomial 2: ";

        cin >> name2;

        if (polynomials.find(name1) == polynomials.end() ||
          polynomials.find(name2) == polynomials.end())

        {

          cout <<

            "\n                        -----------      One or both of the specified polynomials not found.       -----------";

        } else

        {

          Polynomial difference =

            polynomials[name1].subtract(polynomials[name2]);

          cout << "\n# Difference of Polynomial " << name1 <<

            " and Polynomial " << name2 << ": ";

          difference.display();

          polynomials[next_name] = difference;

          next_name++;

        }

      }

      break;

    }

    case 5:

    {

      if (polynomials.size() < 2)

      {

        cout <<

          "\n                           -----------       At least two polynomials are required to perform multiplication.       -----------";

      } else

      {

        char name1, name2;

        cout << "\n# Enter the name of Polynomial 1: ";

        cin >> name1;

        cout << "\n# Enter the name of Polynomial 2: ";

        cin >> name2;

        if (polynomials.find(name1) == polynomials.end() ||
          polynomials.find(name2) == polynomials.end())

        {

          cout <<

            "\n                  -----------      One or both of the specified polynomials not found.     -----------\n";

        } else

        {

          Polynomial product =

            polynomials[name1].multiply(polynomials[name2]);

          cout << "\n# Product of Polynomial " << name1 <<

            " and Polynomial " << name2 << ": ";

          product.display();

          polynomials[next_name] = product;

          next_name++;

        }

      }

      break;

    }

    case 6:

    {

      if (polynomials.empty())

      {

        cout << "\n                      -----------      No polynomials to reverse.     -----------";

      } else

      {

        char name;

        cout << "\n# Enter the name of Polynomial: ";

        cin >> name;

        if (polynomials.find(name) == polynomials.end())

        {

          cout << "\n                     -----------        Polynomial not found.        -----------";

        } else

        {

          Polynomial reversed = polynomials[name].reverse();

          cout << "\n# Reverse of Polynomial " << name << ": ";

          reversed.display();

          polynomials[next_name] = reversed;

          next_name++;

        }

      }

      break;

    }

    case 7:

    {

      if (polynomials.empty())

      {

        cout << "\n                         -----------      No polynomials to evaluate.       -----------";

      } else

      {

        char name;

        double x;

        cout << "\n# Enter the name of Polynomial: ";

        cin >> name;

        cout << "\n# Enter the value of x: ";

        cin >> x;

        if (polynomials.find(name) == polynomials.end())

        {

          cout << "\n                       -----------       Polynomial not found.        -----------";

        } else

        {

          double result = polynomials[name].evaluate(x);

          cout << "\n# Value of Polynomial " << name << " at x = " <<
            x <<
            ": " << result << endl;

        }
      }
      break;

    }

    case 0:

    {

      cout << "\n# bye ^_^ Exiting ...:)\n";

      return 0;

    }

    default:

    {

      cout << "\n                        -----------       Invalid choice. Please try again.       -----------";

      break;

    }

    }

  }

  return 0;

}
