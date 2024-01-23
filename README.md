# Trading Toolkit

This repo is a set of tools to improve trading performance.

## Commands

### psc - Position Size Calculator

Calculates the position size that you should open in both monetary value and the number of units. This command makes sure that your risk is always the maximum risk set for your account size.

#### Inputs

**Open Price** - The trade open price.

**Trade Risk** - The distance between the open price and the stop loss.

#### Extra Info

**Max Risk Per Trade** - The maximum risk per trade based off your trading account size. By default this is set to 1%.

**Leverage** - The leverage of what you are trading.

### pt - Prep Trade

Add trade to a prepped trade list that can be either activated or cancelled later. This command returns both the monetary value and the number of units for the trade that you are prepping in line with your trade account size and maximum risk.

#### Inputs

**Open Price** - The trade open price.

**Trade Risk** - The distance between the open price and the stop loss.

#### Extra Info

**Max Risk Per Trade** - The maximum risk per trade based off your trading account size. By default this is set to 1%.

**Leverage** - The leverage of what you are trading.

### lt - List Trades

List all prepped and active trades.

### ct - Cancel Trade

Cancel previously prepped trades.

#### Inputs

**Trade ID** - The ID of the prepped trade that you want to cancel. A list of all prepped trades is displayed to choose from.

### at - Activate Trade

Activate a trade from your list of prepped trades.

#### Inputs

**Trade ID** - The ID of the prepped trade that you want to activate. A list of all prepped trades is displayed to choose from.

### et - End Trade

End an active trade.

#### Inputs

**Trade ID** - The ID of the active trade that you want to end. A list of all active trades is displayed to choose from.

**Close Price** - The close price for the trade.

### st - Set Risk

Set the risk that you are wanting to take for future trade calculations. **This data is not persistent and will be reset to 1% after restarting the program.**

#### Inputs

**Risk** - The risk to be set as a percentage. For example, if you want to risk 5% of your trading account you enter **5**.

### rc - Risk Calculator

The potential downside risk in monetary value. This command overrides the max trade risk so that you can calculate potential loss if you choose to increase risk size.

#### Inputs

**Open Price** - The trade open price.

**Position Size** - The trade position size in monetary value.

**Risk** - The distance between the open price and the stop loss.

### ? - Help

List all available commands

### q - Quit

Quit the program
