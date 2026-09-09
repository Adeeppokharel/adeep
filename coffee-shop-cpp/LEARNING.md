# Understand your project

Start by running the example in the README, then read the code in this order.

## 1. Menu constants

`DRINKS` stores six names and `PRICES` stores their matching prices in cents.
Both arrays use the same positions: position `0` describes Espresso.
The menu shows numbers starting at 1, so `choice - 1` converts a selection
into an array index.

`const` means these values cannot be reassigned. They are global here because
they are declared outside every function; `const` alone does not mean global.

## 2. The order

`int quantities[MENU_SIZE] = {};` starts every quantity at zero.
Choosing a drink adds to its quantity. The maximum is 99 per drink, including
repeat selections. The program caps each addition at the remaining allowance.

## 3. Functions

| Function | Job |
| --- | --- |
| `money` | Format cents as a dollar amount, such as `$4.50` |
| `readNumber` | Keep asking until a valid whole number is entered |
| `showMenu` | Display drinks, prices, and actions |
| `showOrder` | Print regular drinks and flavored lattes, then return the combined total in cents |
| `main` | Repeat menu actions until the customer exits |

`readNumber` takes `int& value`, a reference. That allows the function to put
the validated number directly into the caller's variable. Its Boolean return
value tells the caller whether reading succeeded or the input stream closed.

`getline` reads the whole response. `istringstream` tries to read a number
and then checks for an extra character. This rejects input such as `2abc`
and `1.5`. You can study this helper after you understand the ordering loop.

## 4. Exact prices

Two lattes cost `2 * 450 = 900` cents. Integer division `900 / 100` gives
9 dollars and the remainder `900 % 100` gives 0 cents. Formatting pads the
cents to two digits. Storing whole cents avoids decimal rounding surprises.

## 5. Checkout and reset

An empty order cannot be checked out. After a receipt is printed, each quantity
is reset to zero. The loop `for (int& quantity : quantities)` visits each array
element by reference, so assigning zero updates the original array.

## Practice changes

1. Change the welcome message and compile again.
2. Change the latte price to 475 cents and check the receipt.
3. Add a seventh drink. Update `MENU_SIZE`, both arrays, action numbers, and
   the input range so the new drink does not conflict with View order.
4. Explain why the code subtracts 1 from the drink selection.

## Quick manual checks

- Two lattes and one espresso should total $12.00.
- Enter `hello`, `1.5`, `2abc`, or a huge number: it should ask again.
- Enter 0 or a negative quantity: it should ask again.
- Add 98 of a drink, then try to add 2: only 1 more is allowed.
- View an empty order and try checking out: no sale should be completed.
- Checkout, then view the next order: it should be empty.
- Press Ctrl+D at a prompt on Mac/Linux: the program should exit cleanly.

## 6. Latte submenu

Selecting main-menu option 3 enters the flavor submenu. A flavor choice starts
at 1, so `flavor - 1` converts it into an array index. For White Mocha (choice 4),
index 3 connects `latteFlavors[3]`, `lattePrices[3]`, and `latteQuantities[3]`.
Adding two updates `latteQuantities[3] += 2`. Both order arrays are declared
before the main loop so they persist between selections.

`continue` returns to the top of the ordering loop, preventing the regular drink
code from also adding a plain latte. `break` exits the loop entirely. Choosing
0 inside the submenu returns to the main menu without adding a drink.

The receipt visits both arrays. Checkout and Clear order reset both arrays.
Check that two White Mocha Lattes plus one Espresso total $12.00, and that an
order containing only a flavored latte can be checked out.
