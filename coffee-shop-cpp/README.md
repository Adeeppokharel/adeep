# Adeep's Coffee Shop ☕

A beginner-friendly C++ terminal application inspired by working as a barista.
Choose drinks, add quantities, review an order, and print a receipt in the terminal.

## Features

- Six main menu choices with sample USD prices
- A Latte submenu with Caramel, Salted Caramel, Mocha, White Mocha, and Matcha
- Separate flavor quantities on receipts and a Back option in the submenu
- Multiple drinks per order; repeat selections combine quantities
- Itemized receipt with quantities, unit prices, and a total
- View or clear an order, and start a fresh order after checkout
- Whole-number input validation and a limit of 99 of each drink
- Exact calculations using integer cents

This is a learning project. It does not process payments, calculate tax or tips,
save orders to disk, or manage inventory. Orders disappear when the program exits.

## Run on a Mac

1. Download or clone this repository and open its `coffee-shop-cpp` folder in VS Code.
2. Select **Terminal → New Terminal**. Make sure the terminal is in the folder
   containing `main.cpp`.
3. Compile:

   ```bash
   clang++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp -o coffee_shop
   ```

4. Run:

   ```bash
   ./coffee_shop
   ```

If your Mac does not have a compiler, run `xcode-select --install`, finish the
installation, and try compiling again. Recompile after editing the source.

On Linux, replace `clang++` with `g++`. No additional libraries are required.

## Try an order

Enter these values one at a time:

| Input | Action |
| --- | --- |
| `3` | Select Latte |
| `1` | Select Caramel Latte |
| `2` | Add two lattes |
| `1` | Select Espresso |
| `1` | Add one espresso |
| `8` | Checkout |
| `0` | Exit |

The receipt will show two Caramel Lattes at $4.50 each and one espresso at $3.00,
for a total of **$12.00**. Checkout clears the order for the next customer.

## Clone this project

```bash
git clone https://github.com/Adeeppokharel/adeep.git
cd adeep/coffee-shop-cpp
clang++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp -o coffee_shop
./coffee_shop
```

This is a terminal app; GitHub displays the source and documentation, rather
than running it as a website. Recompile after saving changes to `main.cpp`.
All latte flavors currently cost $4.50; edit `lattePrices` to change them.

## Project files

| File | Purpose |
| --- | --- |
| `main.cpp` | Complete application |
| `LEARNING.md` | Walkthrough and practice changes |
| `.gitignore` | Keeps generated files out of Git |
| `README.md` | Setup and project overview |

## Concepts practiced

Variables, constants, arrays, loops, conditionals, functions, references,
formatted output, and string streams for input validation.

## Possible next steps

- Add drink sizes
- Allow removing one drink from an order
- Save receipts to a text file
- Track daily sales

Built with assistance from ChatGPT as a personal learning project.
