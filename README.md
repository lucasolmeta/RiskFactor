# lucasolmeta/cppbettingengine

A quantitative C++ betting engine designed to process odds, remove bookmaker vig, and calculate optimal bet sizing using the Kelly Criterion. 

## Core Features
*   **Odds Conversion:** Parses American odds strings and calculates raw implied probabilities.
*   **Vig Removal:** Calculates the total overround of a given market and normalizes the probabilities to represent fair value.
*   **Kelly Sizing:** Computes the recommended fraction of a bankroll to wager based on model edge versus the bookmaker's implied probability.

## Usage
The `OddsEngine` class serves as the primary interface. Instantiate the class to evaluate vectors of market odds strings. The engine will strip the vig, compare the fair probabilities against your proprietary model, and output the recommended Kelly bet sizes for execution.

## Compilation
Compile the engine using standard C++17 or higher. 

```bash
g++ -std=c++17 -o engineApp main.cpp RiskFactor.cpp
./engineApp
```
