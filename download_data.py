import yfinance as yf

# Download Apple stock data
apple = yf.download('AAPL', start='2001-01-01', end='2021-01-01')
apple.to_csv('AAPL.csv')

# Print the downloaded data
print(apple)